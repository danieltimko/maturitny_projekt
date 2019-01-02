#include <vector>
#include <map>

using namespace std;

class Output{
public:
    static void print(map<string, map<string,int>>&);
    static void print(vector<Schedule>&);
    static void print(map<string,string>&, int);
};