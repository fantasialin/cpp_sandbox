#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

void put_zero_to_end(vector<int>& in, vector<int>& ret)
{
    int zero_count = 0;
    for(int i=0; i < in.size(); i++){
        if(in[i] != 0){
            ret.push_back(in[i]);
        }
        else{
            zero_count++;
        }
    }
    for(int i = 0; i < zero_count; i++)
        ret.push_back(0);

    return;
}

void put_zero_to_end_1(vector<int>& in)
{
    int shift_count = 0;
    for(int i=0; i < in.size()-shift_count; i++){
        if(in[i] == 0){
            //shift all element
            shift_count++;
            for(int j=i; j< in.size()-shift_count; j++){
                in[j] = in[j+1];
            }
            in[in.size()-shift_count] = 0;

        }
        if(in[i] == 0)
          i--;
    }

    return;
}

void dump(vector<int>& in)
{
    cout << "array : ";
    for(auto i : in)
      cout << i << ", ";

    cout << endl;
}

int main(int argc, char **argv){
    cout << "exercise - 0001" << endl;
    //vector<int> vi={1,2,3,0,4,0,5,6,0,7};
    //vector<int> vi={0,1,0,2,3,4,5,6,0,7};
    vector<int> vi={0,0,0,1,0,0,2,0,3,0,0,4,5,0,6,0,7};
    vector<int> ret = {};

    dump(vi);

    put_zero_to_end(vi,ret);

    dump(ret);

    put_zero_to_end_1(vi);

    dump(vi);

    return 0;
};
