#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Schedule{
    string class_name;
    vector<int> schedule[5];
};

fstream file;
vector<vector<int>> G;
vector<Schedule> schedules;

void read_graph(){
    file.open("../graph.txt");
    int nodes, edges;
    file >> nodes >> edges;
    G.resize(nodes+1);
    for (int i = 0; i < edges; ++i) {
        int from, to;
        file >> from >> to;
        G[from].push_back(to);
        G[to].push_back(from);
    }
    file.close();
}

void read_schedules(){
    file.open("../schedules.txt");
    int n; //pocet tried
    file >> n;
    schedules.resize(n);
    for (int i = 0; i < n; ++i) {
        file >> schedules[i].class_name; //nazov triedy
        for (int day = 0; day < 5; ++day) {
            int periods; //pocet hodin v dany den
            file >> periods;
            for (int j = 0; j < periods; ++j) {
                int period; //ucebna v ktorej je hodina
                file >> period;
                schedules[i].schedule[day].push_back(period);
            }
        }
    }
    file.close();
}

void print_graph(){
    for(int i = 1; i < G.size(); ++i) {
        cout << "susedia vrcholu " << i << ": ";
        for (int j : G[i])
            cout << j << " ";
        cout << endl;
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

int main() {
    read_graph();
    read_schedules();
    //print_graph();
    //print_schedules();

    //TODO ceny ciest, floyd-warshall
    //TODO ?riesenie pre jednu triedu?
    //TODO prechadzanie vsetkych permutacii
    //TODO penalty pre kazdu permutaciu
    //TODO preskakovanie nevyhodnych permutacii
}