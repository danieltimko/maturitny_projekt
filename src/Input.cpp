#include <iostream>
#include <fstream>
#include "../include/Schedule.h"
#include "../include/Classroom.h"
#include "../include/Input.h"

#define inf 0x3f3f3f3f

using namespace std;

void Input::read_graph(map<string, map<string,int>> &dist, vector<Classroom> &root_classrooms){
    ifstream file;
    file.open("../graph.json");
    int nodes, edges; // numberOfNodes, numberOfEdges
    string ignore;
    file >> ignore >> ignore >> nodes >> ignore >> ignore >> edges >> ignore >> ignore >> ignore;
    vector<string> names(nodes); // nodeLabels
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
        dist[from][to] = cost;
        dist[to][from] = cost;
    }
    int n; // numberOfRootClassrooms
    file >> ignore >> ignore >> n >> ignore >> ignore >> ignore;
    root_classrooms.resize(n);
    for (int i = 0; i < n; ++i) { // rootClassrooms
        string classroom;
        file >> classroom;
        classroom = classroom.substr(1, classroom.size()-((i<n-1)?3:2));
        root_classrooms[i].number = classroom;
    }
    file.close();
}

void Input::read_schedules(vector<Schedule> &schedules){
    ifstream file;
    file.open("../schedules.json");
    int n; // numberOfClasses
    string ignore;
    file >> ignore >> ignore >> n >> ignore >> ignore >> ignore;
    schedules.resize(n);
    for (int i = 0; i < n; ++i) { // classes
        string name;
        file >> ignore >> ignore >> name >> ignore >> ignore;
        schedules[i].class_name = name.substr(1, name.size()-3); // className
        for (int j = 0; j < 5; ++j) { // days
            int periods; // numberOfLessons
            file >> ignore >> ignore >> periods >> ignore >> ignore >> ignore;
            for (int k = 0; k < periods; ++k) { // classrooms
                string classroom;
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
