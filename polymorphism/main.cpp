#include <iostream>
#include <vector>
using namespace std;

class Shape
{
public: 
    virtual void draw() = 0;//pure virtual function
    //virtual ~Shape() = 0;
};

class Rect : public Shape
{
public:
    virtual void draw() { cout << "Rect" << endl;}
private:
    int height;
    int width;
};

class Square : public Rect
{
public:
    virtual void draw(){ cout << "Square" << endl;}
};

class Ellipse : public Shape
{
public:
    virtual void draw(){ cout << "Ellipse" << endl;}
private:
    int x, y;
    int r1, r2;
};

class Circle : public Ellipse
{
public:
    virtual void draw(){ cout << "Circle" << endl;}
};

void drawAll(const vector<Shape*> &v){
    for(auto& elem : v)
        elem->draw();
}


int main(int argc, char **argv)
{
    Rect r1;
    Square q1;
    r1.draw();
    q1.draw();

    Rect *Rptr = new Rect;
    Rptr->draw();
    delete Rptr;

    cout << "Shape size : " << sizeof(Shape) << endl;
    cout << "Rect size : " << sizeof(Rect) << endl;
    cout << "Square size : " << sizeof(Square) << endl;
    cout << "Ellipse size : " << sizeof(Ellipse) << endl;
    cout << "Circle size : " << sizeof(Circle) << endl;

    vector<Shape*> shapeIs;
    shapeIs.push_back(&r1);
    shapeIs.push_back(&q1);
    shapeIs.push_back(new Circle);
    shapeIs.push_back(new Ellipse);
    drawAll(shapeIs);

    return 0;
}