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
    file.open("../graph.txt");
    int nodes, edges;
    file >> nodes >> edges;
    dist.resize(nodes+1);
    for (int i = 0; i < nodes+1; ++i)
        dist[i].resize(nodes+1, inf);
    for (int i = 0; i < edges; ++i) {
        int from, to, cost;
        file >> from >> to >> cost;
        dist[from][to] = cost;
        dist[to][from] = cost;
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
                int classroom; //ucebna v ktorej je hodina
                file >> classroom;
                schedules[i].schedule[day].push_back(classroom);
            }
        }
    }
    file.close();
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
