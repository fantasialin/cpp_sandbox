
#include <iostream>
#include "RCObject.h"

using namespace std;

/******************************************************************************
* Functions to perform VERY simple test of the above.                         *
******************************************************************************/  
void testRCPtr()
{
  String s1 = "String with no changes.";
  String s2(s1);
  
  s2[12] = s2[13] = ' ';
  
  cout << s1 << '\n';      // prints "String with no changes."
  cout << s2 << '\n';      // prints "String with    changes."
}

void testRCIPtr()
{
  RCWidget w1(10);
  RCWidget w2(w1);

  w2.doThis();
  
  cout << w1.showThat() << '\n';       // prints 10
  cout << w2.showThat() << '\n';       // prints -1
}

int main()
{
  testRCPtr();
  testRCIPtr();

  return 0;
}