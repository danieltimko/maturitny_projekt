#include <iostream>
#include <vector>
#include <map>
#include "../include/Schedule.h"
#include "../include/Output.h"

#define inf 0x3f3f3f3f

using namespace std;

void Output::print(map<string, map<string,int>> &dist){
    for (auto i = dist.begin(); i != dist.end(); ++i) {
        for (auto j = dist[i->first].begin(); j != dist[i->first].end(); ++j)
            if(j->second == inf)
                cout << "-  ";
            else cout << j->second << "  ";
        cout << endl;
        }
    cout << endl;
}

void Output::print(vector<Schedule> &schedules){
    for(Schedule i : schedules){
        cout << i.class_name << endl;
            for (int j = 0; j < i.schedule.size(); ++j)
                cout << i.schedule[j] << " \n"[j==i.schedule.size()-1];
        cout << endl;
    }
    cout << endl;
}

void Output::print(map<string,string> &permutation, int best_dist){
    for (auto i : permutation) {
        cout << "kmenova trieda pre triedu " << i.first << ": ";
        if(i.second == "")
            cout << "bez kmenovej triedy";
        else cout << i.second;
        cout << endl;
    }
    cout << "Celkova prejdena vzdialenost: " << best_dist << endl << endl;
}
