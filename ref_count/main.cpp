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
    String x2(x1);  //x1 and x2 are share the same StringValue.
    String x3(x1);  //x1, x2 and x3 are share the same StringValue.
    String x4;
    x4 = x3;        //x1, x2, x3 and x4 are all share the same StringValue.
    detect(x1);detect(x2);detect(x3);detect(x4);
    cout << endl;

    cout << x1[3] << x2[6] << endl; //x1 and x2 are accessed then these two objects are separated from the share StringValue.
    detect(x1);detect(x2);detect(x3);detect(x4);
    cout << endl;

    x1[3] = x2[6] = 'x';            //x1 and x2 are not share the same StringValue, therefore the modification on the StringValue object doesn't affect each other.
    detect(x1);detect(x2);detect(x3);detect(x4);
    cout << endl;

    String x0(x2);//x2 is still not shareable, but x0 is newly created and shareable.
    detect(x0);detect(x1);detect(x2);detect(x3);detect(x4);
    cout << endl;

    char* p = &(x3[0]); //x3[0] will let x3 separate from x4 share StringValue object.
    detect(x3);
    cout << "x3 ... " << endl;
    String x5(x3);      //x3 is still not shareable, but x5 is newly created and shareable.
    *p = 'M';           //p points to x3's StringValue's data variable. This action will let x3's first char be changed to 'M'.
    detect(x0);detect(x1);detect(x2);detect(x3);detect(x4);detect(x5);
    cout << endl;

    String x6(x4);      //x4 and x6 are share the same StringValue object.
    detect(x4);detect(x6);
    cout << x4[0] << endl;  //x4 is separated from the share StringValue object, and marks as not sharealbe.
    detect(x4);detect(x6);
    cout << endl;

    // like x4, we doesn't want to modify the data, it should be a way to remain in the same share StringValue.
    const String cs1("const string");
    const String cs2(cs1);
    String s(cs1);
    detect(cs1);detect(cs2);detect(s);
    cout << endl;

    cout << cs1[0] << endl; // invoke op[] const function. The action will not separate the StringValue object from share.
    detect(cs1);detect(cs2);detect(s);
    cout << endl;

    cout << (s[0] = 'x') << endl;   //s is not const object, so op[] will invoke non-const version and separed from the share StringValue object.
    detect(cs1);detect(cs2);detect(s);
    cout << endl;

    //cs1[1] = 'x';   //cause compiling error due to the cs1 is read-only object.

    return 0;
}