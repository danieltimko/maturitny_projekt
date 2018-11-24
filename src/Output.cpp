#include <iostream>
#include <vector>
#include <map>
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
            for (int j = 0; j < i.schedule.size(); ++j)
                cout << i.schedule[j] << " \n"[j==i.schedule.size()-1];
        cout << endl;
    }
    cout << endl;
}

void Output::print(map<string,int> permutation, int best_dist){
    for (auto i : permutation) {
        cout << "kmenova trieda pre triedu " << i.first << ": ";
        if(i.second < 0)
            cout << "bez kmenovej triedy";
        else cout << i.second;
        cout << endl;
    }
    cout << "Celkova prejdena vzdialenost: " << best_dist << endl << endl;
}
