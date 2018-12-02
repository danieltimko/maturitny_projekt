#include <iostream>
#include <vector>
#include <map>
#include "../include/Schedule.h"
#include "../include/Classroom.h"
#include "../include/Input.h"
#include "../include/Output.h"

#define inf 0x3f3f3f3f

using namespace std;

vector<vector<int>> dist;
vector<Schedule> schedules;
vector<Classroom> kmenove;
map<string,int> permutation, best_permutation; // {classroom, class}
int best_dist = inf;

void make_floyd(){
    for (int k = 1; k < dist.size(); ++k)
        for (int i = 1; i < dist.size(); ++i)
            for (int j = 1; j < dist.size(); ++j)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int one_class(string class_name){
    pair<int,int> min_cost = {inf, 0}; //{cost, classroom}
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
    // vsetky null_classroom maju cislo mensie ako 0
    for(int i = schedules.size(); i > kmenove.size(); ++i) {
        cout << "null_classroom added\n";
        Classroom null_classroom;
        null_classroom.number = kmenove.size()-i;
        kmenove.push_back(null_classroom);
    }
}

int evaluate(){
    // vypocita celkovu prejdenu vzdialenost pre dane rozlozenie
    int cost = 0;
    for (int i = 0; i < schedules.size(); ++i)
        for (int j = 0; j < schedules[i].schedule.size(); ++j)
            cost += dist[permutation[schedules[i].class_name]][schedules[i].schedule[j]];
    return cost;
}

void all_permutations(int index = 0){
    // prechadza vsetky mozne priradenia ucebni
    if(index == schedules.size()){ // kompletna permutacia
        int current_dist = evaluate();
        if(current_dist < best_dist){
            best_dist = current_dist;
            best_permutation = permutation;
        }
        return;
    }
    string class_name = schedules[index].class_name;
    for (int i = 0; i < kmenove.size(); ++i)
        if(!kmenove[i].assigned) {
            permutation[class_name] = kmenove[i].number;
            kmenove[i].assigned = true;
            all_permutations(index+1);
            kmenove[i].assigned = false;
        }

}

int main() {
    Input::read_graph(dist);
    Input::read_schedules(schedules, kmenove);
    Output::print(dist);
    Output::print(schedules);
    make_floyd();
    Output::print(dist);
    //cout << one_class("4.SA") << endl;
    //cout << one_class("3.F") << endl;
    add_null_classrooms();
    all_permutations();
    Output::print(best_permutation, best_dist);

    /*
    TODO kmenove ucebne len pre 1. a 2. rocnik
    TODO penalty pre kazdu permutaciu
    TODO zarezavanie nevyhodnych permutacii
    */
}
