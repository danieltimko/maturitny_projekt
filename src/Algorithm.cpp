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

map<string, map<string, int>> dist;
vector<Schedule> schedules;
vector<Classroom> kmenove;
map<string, map<string, int>> table; // tabulka predpocitanych vzdialenosti, [trieda][ucebna]
map<string,string> permutation, best_permutation; // {class, classroom}
int best_dist = inf;

void make_floyd(){
    for (auto k = dist.begin(); k != dist.end(); ++k)
        for (auto i = dist.begin(); i != dist.end(); ++i)
            for (auto j = dist[i->first].begin(); j != dist[i->first].end(); ++j)
                if (dist[i->first][j->first] > dist[i->first][k->first] + dist[k->first][j->first])
                    dist[i->first][j->first] = dist[i->first][k->first] + dist[k->first][j->first];
}

void make_sums_table(){
    // predpocita sucty vzdialenosti pre kazdu triedu
    for (int i = 0; i < schedules.size(); ++i)
        for (int j = 0; j < kmenove.size(); ++j) {
            table[schedules[i].class_name][kmenove[j].number] = 0;
            for (int k = 0; k < schedules[i].schedule.size(); ++k)
                table[schedules[i].class_name][kmenove[j].number] += dist[schedules[i].schedule[k]][kmenove[j].number];
        }
}

string one_class(string &class_name){
    // riesenie pre jednu triedu
    pair<int,string> min_cost = {inf, ""}; //{cost, classroom}
    int index; // index danej triedy vo vektore schedules
    for (int i = 0; i < schedules.size(); ++i)
        if(schedules[i].class_name == class_name){
            index = i;
            break;
        }
    for (int i = 0; i < kmenove.size(); ++i) {
        int cost = 0;
        for (int j = 0; j < schedules[index].schedule.size(); ++j)
            cost += dist[kmenove[i].number][schedules[index].schedule[j]];
        if(cost < min_cost.first)
            min_cost = {cost, kmenove[i].number};
    }
    return min_cost.second;
}

void add_null_classrooms(){
    // ak je viac tried ako kmenovych ucebni, doplni ucebne o null_classrooms
    // ak je triede pridelena null_classroom, znamena to ze sa jej neusla kmenova ucebna
    while(schedules.size() > kmenove.size())
        kmenove.push_back(Classroom());
}

int evaluate(){
    // vypocita celkovu prejdenu vzdialenost pre dane rozlozenie
    int cost = 0;
    for (int i = 0; i < schedules.size(); ++i)
        if(!permutation[schedules[i].class_name].empty()) // ak triede este nie je priradena ucebna
            cost += table[schedules[i].class_name][permutation[schedules[i].class_name]];
    return cost;
}

void all_permutations(int index = 0){
    // prechadza vsetky mozne priradenia ucebni
    int current_dist = evaluate();
    if(index == schedules.size()){ // kompletna permutacia, vsetky triedy su pridelene
        if(current_dist < best_dist){
            best_dist = current_dist;
            best_permutation = permutation;
        }
        return;
    }
    if(current_dist >= best_dist)
        return;
    string class_name = schedules[index].class_name;
    for (int i = 0; i < kmenove.size(); ++i)
        if(!kmenove[i].assigned) {
            permutation[class_name] = kmenove[i].number;
            kmenove[i].assigned = true;
            all_permutations(index+1);
            permutation[class_name].clear();
            kmenove[i].assigned = false;
        }
}

int main() {
    Input::read_graph(dist, kmenove);
    //Output::print(dist);
    Input::read_schedules(schedules);
    //Output::print(schedules);
    make_floyd();
    make_sums_table();
    //Output::print(dist);
    //Output::print(table);
    //cout << one_class("1.F") << endl;
    add_null_classrooms();
    all_permutations();
    Output::print(best_permutation, best_dist);
    // TODO kmenove ucebne len pre 1. a 2. rocnik, 3. a 4. rocnik ignore
    //TODO poriesit ked sa v rozvrhu deli hodina na 2 skupiny
}
