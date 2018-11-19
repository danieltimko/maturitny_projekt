#include <iostream>
#include <vector>
#include <set>
#include "../include/Schedule.h"
#include "../include/Input.h"
#include "../include/Output.h"

#define inf 0x3f3f3f3f

using namespace std;

vector<vector<int>> dist;
vector<Schedule> schedules;
set<int> classrooms;

void make_floyd(){
    for (int k = 1; k < dist.size(); ++k)
        for (int i = 1; i < dist.size(); ++i)
            for (int j = 1; j < dist.size(); ++j)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int one_class(string class_name){
    pair<int,int> min_cost = {inf, 0}; //{cost, classroom}
    int index;
    for (int i = 0; i < schedules.size(); ++i)
        if(schedules[i].class_name == class_name){
            index = i;
            break;
        }
    for (int i = 0; i < classrooms.size(); ++i) {
        int cost = 0;
        for (int j = 0; j < schedules[index].schedule.size(); ++j)
            cost += dist[*classrooms.begin()+i][schedules[index].schedule[j]];
        if(cost < min_cost.first)
            min_cost = {cost, *classrooms.begin() + i};
    }
    return min_cost.second;
}

int main() {
    dist = Input::read_graph();
    schedules = Input::read_schedules();
    Output::print(dist);
    Output::print(schedules);
    make_floyd();
    Output::print(dist);
    classrooms = Input::get_classrooms(schedules);
    cout << one_class("4.SA") << endl;
    cout << one_class("3.F") << endl;

    /*
    TODO prechadzanie vsetkych permutacii
    TODO penalty pre kazdu permutaciu
    TODO zarezavanie nevyhodnych permutacii
    */
}
