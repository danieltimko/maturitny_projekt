#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "../include/Schedule.h"
#include "../include/Classroom.h"
#include "../include/Input.h"
#include "../include/Output.h"

#define inf 0x3f3f3f3f


using namespace std;

map<string, map<string, int>> dist; // Floyd-Warshall matrix
vector<Schedule> schedules; // schedules of all classes
vector<Classroom> root_classrooms; // vector of root classrooms
map<string, map<string, int>> table; // table of precomputed distances, [class][classroom]
map<string,string> permutation, best_permutation; // {class, classroom}
int best_dist = inf;

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
    // if class X was assigned to classroom Y, they would walk a distance of: table[X][Y]
    for (int i = 0; i < schedules.size(); ++i)
        for (int j = 0; j < root_classrooms.size(); ++j) {
            table[schedules[i].class_name][root_classrooms[j].number] = 0;
            for (int k = 0; k < schedules[i].schedule.size(); ++k)
                table[schedules[i].class_name][root_classrooms[j].number] += dist[schedules[i].schedule[k]][root_classrooms[j].number];
        }
}

string one_class(string class_name){
    // solution for one specific class
    pair<int,string> min_cost = {inf, ""}; //{cost, classroom}
    int index;
    for (int i = 0; i < schedules.size(); ++i)
        if(schedules[i].class_name == class_name)
            index = i;
    for (int i = 0; i < root_classrooms.size(); ++i) {
        if(root_classrooms[i].assigned)
            continue;
        int cost = 0;
        for (int j = 0; j < schedules[index].schedule.size(); ++j)
            cost += dist[root_classrooms[i].number][schedules[index].schedule[j]];
        if(cost < min_cost.first)
            min_cost = {cost, root_classrooms[i].number};
    }
    return min_cost.second;
}

void add_null_classrooms(){
    // add null classrooms, so that count of classes = count of classrooms
    while(schedules.size() > root_classrooms.size())
        root_classrooms.push_back(Classroom());
}

int evaluate(map<string,string> &perm){
    // computes total travelled distance for given permutation
    int cost = 0;
    for (int i = 0; i < schedules.size(); ++i)
        if(!perm[schedules[i].class_name].empty())
            cost += table[schedules[i].class_name][perm[schedules[i].class_name]];
    return cost;
}

void all_permutations(int index = 0){
    // iterates through all possible permutations
    int current_dist = evaluate(permutation);
    if(index == schedules.size()){
        // complete permutation - all classes have a classroom assigned
        if(current_dist < best_dist){
            best_dist = current_dist;
            best_permutation = permutation;
        }
        return;
    }
    if(current_dist >= best_dist)
        return;
    string class_name = schedules[index].class_name;
    for (int i = 0; i < root_classrooms.size(); ++i)
        if(!root_classrooms[i].assigned) {
            permutation[class_name] = root_classrooms[i].number;
            root_classrooms[i].assigned = true;
            all_permutations(index+1);
            permutation[class_name].clear();
            root_classrooms[i].assigned = false;
        }
}

void heuristic_permutation(){
    // every class gets the classroom with the best distance (if that one is already taken, then second best and so on)
    for (int i = 0; i < schedules.size(); ++i) {
        best_permutation[schedules[i].class_name] = one_class(schedules[i].class_name);
        for (Classroom &c : root_classrooms)
            if(c.number == best_permutation[schedules[i].class_name])
                c.assigned = true;
    }
    best_dist = evaluate(best_permutation);
    for (Classroom &c : root_classrooms)
        c.assigned = false;
}

int main() {
    Input::read_graph(dist, root_classrooms);
    Input::read_schedules(schedules);
    make_floyd();
    make_sums_table();
    heuristic_permutation();
    Output::print(best_permutation, best_dist);
    add_null_classrooms();
    all_permutations();
    Output::print(best_permutation, best_dist);
}
