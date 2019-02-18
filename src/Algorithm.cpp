#include <iostream>
#include <vector>
#include <unordered_map>
#include "../include/Schedule.h"
#include "../include/Input.h"
#include "../include/Output.h"

#define inf 0x3f3f3f3f


using namespace std;

map<string, map<string, int>> dist; // Floyd-Warshall matrix
vector<Schedule> schedules; // schedules of all classes
vector<string> root_classrooms; // vector of root classrooms
map<string, map<string, int>> sum; // table of precomputed distances, [class][classroom]

void make_floyd(){
    // Floyd-Warshall algorithm
    for (auto k = dist.begin(); k != dist.end(); ++k)
        for (auto i = dist.begin(); i != dist.end(); ++i)
            for (auto j = dist[i->first].begin(); j != dist[i->first].end(); ++j)
                if (dist[i->first][j->first] > dist[i->first][k->first] + dist[k->first][j->first])
                    dist[i->first][j->first] = dist[i->first][k->first] + dist[k->first][j->first];
}

void make_sums_table(){
    // precomputes distance sum for every pair class-classroom
    // if class X was assigned to classroom Y, they would walk a total distance of: sum[X][Y]
    for (int i = 0; i < schedules.size(); ++i)
        for (int j = 0; j < root_classrooms.size(); ++j) {
            sum[schedules[i].class_name][root_classrooms[j]] = 0;
            for (int k = 0; k < schedules[i].schedule.size(); ++k)
                sum[schedules[i].class_name][root_classrooms[j]] += dist[schedules[i].schedule[k]][root_classrooms[j]];
        }
}

void add_null_classrooms() {
    // adds null classrooms, so that count of classes = count of classrooms
    while (schedules.size() > root_classrooms.size())
        root_classrooms.push_back("null" + to_string(schedules.size()-root_classrooms.size()));
}

void best_solution(){
    // finds best assignment of classrooms for minimal distance travelled
    int r = schedules.size(), s = root_classrooms.size();
    struct Permutation{
        int cost;
        vector<int> indexes;
    };
    vector<unordered_map<string, Permutation>> tab(r+1);
    string perm;
    for (int i = 0; i < s; ++i) perm += '0';
    tab[0][perm].cost = 0;
    tab[0][perm].indexes.resize(s, -1);
    for (int i = 0; i < r; ++i) {
        auto temp = sum.begin();
        advance(temp, i);
        string class_name = temp->first;
        for (int j = 0; j < tab[i].size(); ++j) {
            auto it = tab[i].begin();
            advance(it, j);
            string perm = it->first;
            for (int k = 0; k < s; ++k) {
                auto temp = sum[class_name].begin();
                advance(temp, k);
                string classroom = temp->first;
                if (perm[k] == '0') {
                    perm[k] = '1';
                    it->second.indexes[k] = i;
                    if (tab[i+1].find(perm) == tab[i+1].end() or it->second.cost + sum[class_name][classroom] < tab[i+1][perm].cost)
                        tab[i+1][perm] = {it->second.cost + sum[class_name][classroom], it->second.indexes};
                    perm[k] = '0';
                    it->second.indexes[k] = -1;
                }
            }
        }
    }
    Permutation min = {-1, {}};
    for (auto it = tab[r].begin(); it != tab[r].end(); ++it)
        if (min.cost == -1 or it->second.cost < min.cost)
            min = it->second;
    Output::print(sum, min.cost, min.indexes);
}

int main() {
    Input::read_graph(dist, root_classrooms);
    Input::read_schedules(schedules);
    //Output::print(dist);
    //Output::print(schedules);
    make_floyd();
    add_null_classrooms();
    make_sums_table();
    best_solution();
}
