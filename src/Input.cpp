#include <iostream>
#include <fstream>
#include <vector>
#include "../include/Schedule.h"
#include "../include/Classroom.h"
#include "../include/Input.h"


#define inf 0x3f3f3f3f

using namespace std;


bool contains(vector<Classroom> v, int key){
    for (int i = 0; i < v.size(); ++i)
        if(v[i].number == key)
            return true;
    return false;
}

void Input::read_graph(vector<vector<int>> &dist, vector<Classroom> &classrooms){
    ifstream file;
    file.open("graph.json");
    file.open("../graph.json");
    int nodes, edges;
    string ignore;
    file >> ignore >> ignore >> nodes >> ignore >> ignore >> edges >> ignore >> ignore >> ignore;
    dist.resize(nodes+1);
    for (int i = 0; i < nodes+1; ++i)
        dist[i].resize(nodes+1, inf);
    for (int i = 1; i < nodes+1; ++i)
        dist[i][i] = 0;
    for (int i = 0; i < edges; ++i) {
        int from, to, cost;
        file >> ignore >> ignore >> from >> ignore >> ignore >> to >> ignore >> ignore >> cost >> ignore;
        dist[from][to] = cost;
        dist[to][from] = cost;
        if(!contains(classrooms, from)) {
            classrooms.push_back({});
            classrooms[classrooms.size()-1].number = from;
        }
        if(!contains(classrooms, to)){
            classrooms.push_back({});
            classrooms[classrooms.size()-1].number = to;
        }
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
                int classroom; // ucebna v ktorej je hodina
                file >> classroom;
                schedules[i].schedule.push_back(classroom);
                if(k < periods-1)
                    file >> ignore;
            }
            file >> ignore >> ignore;
        }
        file >> ignore >> ignore;
    }
}
