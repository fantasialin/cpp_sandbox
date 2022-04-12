#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

int main(int argc, char **argv){
    cout << "exercise - 0003" << endl;
    double avg, sum=0.0, a[12] = {0};

    for(int i=0; i < 12; i++){
        cin >> a[i];
        sum +=a[i];
    }

    avg=sum/12;
    cout << fixed << setprecision(2) ;
    cout << "$" << avg << endl;

    return 0;
};
