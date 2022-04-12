#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class printer
{
    public : 
    printer(){}
    ~printer(){}
    
    // add job to printer
    void addjob(string& in){
        queue.push_back(in);
    }

    // dump current all job in queue
    void dump_job_queue(){
        cout << "queue : " << queue.size() << endl;
        for(auto job : queue)
            cout << job << endl;

    }

    void add_to_top(string& in){
        queue.push_back(in);
        for(int i = queue.size()-1; i >= 1; i--){
            queue[i] = queue[i-1];
        }
        queue[0] = in;
    }

    private :
    vector<string> queue;
};

int main(int argc, char **argv){
    cout << "exercise - 0002" << endl;
    printer p;
    string j1 = string("This is first job");
    string j2 = string("This is second job");
    string j3 = string("This is third job");
    string j4 = string("This is fourth job");


    p.addjob(j1);
    p.addjob(j2);
    p.addjob(j3);


    p.dump_job_queue();

    p.add_to_top(j4);
    
    p.dump_job_queue();

    return 0;
};
