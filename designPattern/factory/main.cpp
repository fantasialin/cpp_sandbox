#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
 
using namespace std;
 
//#define MOTIF // WINDOWS
#define WINDOWS

class Widget {
public:
    virtual void draw() = 0;
};

class MotifButton : public Widget {
public:
   void draw() { cout << "MotifButton\n"; }
};
class MotifMenu : public Widget {
public:
   void draw() { cout << "MotifMenu\n"; }
};

class WindowsButton : public Widget {
public:
   void draw() { cout << "WindowsButton\n"; }
};
class WindowsMenu : public Widget {
public:
   void draw() { cout << "WindowsMenu\n"; }
};

//abstract factory
class Factory {
public:
   //factory methods.
   virtual Widget* create_button() = 0;
   virtual Widget* create_menu() = 0;
};

class MotifFactory : public Factory {
public:
   Widget* create_button() {
      return new MotifButton; }
   Widget* create_menu()   {
      return new MotifMenu; }
};

class WindowsFactory : public Factory {
public:
   Widget* create_button() {
      return new WindowsButton; }
   Widget* create_menu()   {
      return new WindowsMenu; }
};

Factory* factory;

void display_window_one() {
   Widget* w[] = { factory->create_button(),
                   factory->create_menu() };
   w[0]->draw();  w[1]->draw();
}

void display_window_two() {
   Widget* w[] = { factory->create_menu(),
                   factory->create_button() };
   w[0]->draw();  w[1]->draw();
}

int main() {
#ifdef MOTIF
   std::cout << "use MOTIF factory\n";
   factory = new MotifFactory;
#else // WINDOWS
   std::cout << "use WINDOWS factory\n";
   factory = new WindowsFactory;
#endif

   Widget* w = factory->create_button();
   w->draw();
   display_window_one();
   display_window_two();
}


//end of file
