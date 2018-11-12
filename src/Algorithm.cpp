#include <iostream>
#include <vector>
#include "../include/Schedule.h"
#include "../include/Input.h"
#include "../include/Output.h"

#define inf 0x3f3f3f3f

using namespace std;

static vector<vector<int>> dist;
static vector<Schedule> schedules;

void make_floyd(){
    for (int k = 1; k < dist.size(); ++k)
        for (int i = 1; i < dist.size(); ++i)
            for (int j = 1; j < dist.size(); ++j)
                if (dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int main() {
    dist = Input::read_graph();
    schedules = Input::read_schedules();
    Output::print(dist);
    Output::print(schedules);
    make_floyd();
    Output::print(dist);

    /*
    TODO riesenie pre jednu triedu
    TODO prechadzanie vsetkych permutacii
    TODO penalty pre kazdu permutaciu
    TODO zarezavanie nevyhodnych permutacii
    */
}
