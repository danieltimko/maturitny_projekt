#include <iostream>
#include <vector>
#include "../include/Schedule.h"
#include "../include/Output.h"
#define inf 0x3f3f3f3f

using namespace std;

void Output::print(vector<vector<int>> dist){
    for (int i = 1; i < dist.size(); ++i)
        for (int j = 1; j < dist.size(); ++j) {
            if (dist[i][j] == inf)
                cout << '-';
            else cout << dist[i][j];
            cout << " \n"[j == dist.size()-1];
        }
    cout << endl;
}

void Output::print(vector<Schedule> schedules){
    for(Schedule i : schedules){
        cout << i.class_name << endl;
        for (int j = 0; j < 5; ++j)
            for (int k = 0; k < i.schedule[j].size(); ++k)
                cout << i.schedule[j][k] << " \n"[k==i.schedule[j].size()-1];
        cout << endl;
    }
    cout << endl;
}
