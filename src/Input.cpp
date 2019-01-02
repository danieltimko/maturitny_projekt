#include <iostream>
#include <fstream>
#include "../include/Schedule.h"
#include "../include/Classroom.h"
#include "../include/Input.h"

#define inf 0x3f3f3f3f

using namespace std;

void Input::read_graph(map<string, map<string,int>> &dist, vector<Classroom> &kmenove){
    ifstream file;
    file.open("../graph.json");
    int nodes, edges;
    string ignore;
    file >> ignore >> ignore >> nodes >> ignore >> ignore >> edges >> ignore >> ignore >> ignore;
    vector<string> names(nodes);
    for (int i = 0; i < nodes; ++i) {
        file >> names[i];
        if(i < nodes-1)
            names[i].pop_back();
    }
    for (int i = 0; i < nodes; ++i)
        for (int j = 0; j < nodes; ++j)
            dist[names[i]][names[j]] = i==j? 0 : inf;
    file >> ignore >> ignore >> ignore;
    for (int i = 0; i < edges; ++i) {
        string from, to;
        int cost;
        file >> ignore >> ignore >> from >> ignore >> to >> ignore >> cost >> ignore;
        from.pop_back();
        to.pop_back();
        dist[from][to] = cost;
        dist[to][from] = cost;
    }
    int n; //pocet kmenovych ucebni
    file >> ignore >> ignore >> n >> ignore >> ignore >> ignore;
    kmenove.resize(n);
    for (int i = 0; i < n; ++i) {
        file >> kmenove[i].number;
        if(i < n-1)
            kmenove[i].number.pop_back();
    }
    file.close();
}

void Input::read_schedules(vector<Schedule> &schedules){
    ifstream file;
    file.open("../schedules.json");
    int n; //pocet tried
    string ignore;
    file >> ignore >> ignore >> n >> ignore >> ignore >> ignore;
    schedules.resize(n);
    for (int i = 0; i < n; ++i) {
        string name;
        file >> ignore >> ignore >> name >> ignore >> ignore;
        schedules[i].class_name = name.substr(1, name.size()-3); //nazov triedy
        for (int j = 0; j < 5; ++j) {
            int periods; //pocet hodin v dany den
            file >> ignore >> ignore >> periods >> ignore >> ignore >> ignore;
            for (int k = 0; k < periods; ++k) {
                string classroom; // ucebna v ktorej je hodina
                file >> classroom;
                if(k < periods-1)
                    classroom.pop_back();
                schedules[i].schedule.push_back(classroom);
            }
            file >> ignore >> ignore;
        }
        file >> ignore >> ignore;
    }
    file.close();
}
