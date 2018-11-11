#include <iostream>
#include <fstream>
#include <vector>

#define inf 0x3f3f3f3f

using namespace std;

struct Schedule{
    string class_name;
    vector<int> schedule[5];
};

fstream file;
vector<vector<int>> dist;
vector<Schedule> schedules;

void read_graph(){
    file.open("../graph.json");
    int nodes, edges;
    string ignore;
    file >> ignore >> ignore >> nodes >> ignore >> ignore >> edges >> ignore >> ignore >> ignore;
    dist.resize(nodes+1);
    for (int i = 0; i < nodes+1; ++i)
        dist[i].resize(nodes+1, inf);
    for (int i = 0; i < edges; ++i) {
        int from, to, cost;
        file >> ignore >> ignore >> from >> ignore >> ignore >> to >> ignore >> ignore >> cost >> ignore;
        dist[from][to] = cost;
        dist[to][from] = cost;
    }
    file.close();
    cout << "here" << endl;
}

void read_schedules(){
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
                schedules[i].schedule[j].push_back(classroom);
                //cout << schedules[i].schedule[j].size() << endl;
                if(k < periods-1)
                    file >> ignore;
            }
            file >> ignore >> ignore;
        }
        file >> ignore >> ignore;
    }
}

void print_graph(){
    for (int i = 1; i < dist.size(); ++i)
        for (int j = 1; j < dist.size(); ++j) {
            if (dist[i][j] == inf)
                cout << '-';
            else cout << dist[i][j];
            cout << " \n"[j == dist.size()-1];
        }
    cout << endl;
}

void print_schedules(){
    for(Schedule i : schedules){
        cout << i.class_name << endl;
        for (int j = 0; j < 5; ++j)
            for (int k = 0; k < i.schedule[j].size(); ++k)
                cout << i.schedule[j][k] << " \n"[k==i.schedule[j].size()-1];
        cout << endl;
    }
    cout << endl;
}

void make_floyd(){
    for (int k = 1; k < dist.size(); ++k)
        for (int i = 1; i < dist.size(); ++i)
            for (int j = 1; j < dist.size(); ++j)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int main() {
    read_graph();
    read_schedules();
    print_graph();
    print_schedules();
    make_floyd();
    print_graph();

    /*
    TODO riesenie pre jednu triedu
    TODO prechadzanie vsetkych permutacii
    TODO penalty pre kazdu permutaciu
    TODO zarezavanie nevyhodnych permutacii
    */
}
