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
        names[i] = names[i].substr(1, names[i].size()-((i<nodes-1)?3:2));
    }
    for (int i = 0; i < nodes; ++i)
        for (int j = 0; j < nodes; ++j)
            dist[names[i]][names[j]] = i==j? 0 : inf;
    file >> ignore >> ignore >> ignore;
    for (int i = 0; i < edges; ++i) {
        string from, to;
        int cost;
        file >> ignore >> ignore >> from >> ignore >> to >> ignore >> cost >> ignore;
        from = from.substr(1, from.size()-3);
        to = to.substr(1, to.size()-3);
        /*from.pop_back();
        to.pop_back();*/
        dist[from][to] = cost;
        dist[to][from] = cost;
    }
    int n; //pocet kmenovych ucebni
    file >> ignore >> ignore >> n >> ignore >> ignore >> ignore;
    kmenove.resize(n);
    for (int i = 0; i < n; ++i) {
        string classroom;
        file >> classroom;
        classroom = classroom.substr(1, classroom.size()-((i<n-1)?3:2));
        /*if(i < n-1)
            classroom.pop_back();*/
        kmenove[i].number = classroom;

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
                classroom = classroom.substr(1, classroom.size()-((k<periods-1)?3:2));
                schedules[i].schedule.push_back(classroom);
            }
            file >> ignore >> ignore;
        }
        file >> ignore >> ignore;
    }
    file.close();
}
