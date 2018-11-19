#include <vector>
using namespace std;

class Input{
public:
    static vector<vector<int>> read_graph();
    static vector<Schedule> read_schedules();
    static set<int> get_classrooms(vector<Schedule> schedules);
};