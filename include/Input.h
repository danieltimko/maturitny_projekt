#include <vector>
using namespace std;

class Input{
public:

    static void read_graph(vector<vector<int>>&);
    static void read_schedules(vector<Schedule>&, vector<Classroom>&);
};