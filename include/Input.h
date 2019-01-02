#include <vector>
#include <map>

using namespace std;

class Input{
public:

    static void read_graph(map<string, map<string,int>>&, vector<Classroom>&);
    static void read_schedules(vector<Schedule>&);
};