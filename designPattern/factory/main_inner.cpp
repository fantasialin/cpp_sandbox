#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <cmath>
 
using namespace std;
using std::ostream;

class Point
{
   private:
      Point(float x, float y) : x(x), y(y) {}
      float x, y;

      //inner Factory
      class PointFactory
      {
         private:
            PointFactory() {}
         public:
            static Point NewCartesian(float x, float y) { return {x, y}; }
            static Point NewPolar(float r, float theta) { return {r*cos(theta), r*sin(theta)}; }

      };

   public:
      float get_x () const {return x;}
      float get_y () const {return y;}
      static PointFactory Factory;
};



ostream&
operator << (ostream& os, const Point& x)
{
    return os << '(' << x.get_x() << ',' << x.get_y() << ')';
}

int main() {

   auto p1 = Point::Factory.NewCartesian(2.5, 3.6);
   auto p2 = Point::Factory.NewPolar(5.0, 45.0);

   std::cout << "p1 : " << p1 << "    p2 : " << p2 << "\n";

}


//end of file
