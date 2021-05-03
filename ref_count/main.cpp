#include <iostream>
#include "String.h"

using namespace std;

void detect(const String& x)
{
    cout << x.value->refCount << ' ';
    cout << x.value->shareable << " [";
    cout << x.value->data << "] ";
    cout << &(x.value->data) << endl;
}

int main(int argc, char **argv)
{
    String x1 = "Looks Good";
    String x2(x1);
    String x3(x1);
    String x4;
    x4 = x3;
    detect(x1);detect(x2);detect(x3);detect(x4);
    cout << endl;

    return 0;
}