#include <iostream>
#include <vector>
#include <map>
#include <fstream>
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

void Output::print(map<string, map<string, int>> &table, int dist, vector<int> &indexes){
    ofstream out;
    out.open("../output.txt");
    for (int i = 0; i < table.size(); ++i){
        auto temp1 = table.begin();
        advance(temp1, indexes[i]);
        if(indexes[i] == -1)
            continue;
        string class_name = temp1->first;
        auto temp2 = table.begin()->second.begin();
        advance(temp2, i);
        string classroom = temp2->first;
        if(classroom.substr(0, 4) == "null")
            classroom = "bez kmenovej ucebne";
        out << "Kmenova ucebna pre " << class_name << ": " << classroom << endl;
    }
    out << "Celkova prejdena vzdialenost: " << dist << endl << endl;
    out.close();
}
