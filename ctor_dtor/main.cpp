#include <iostream>

using namespace std;


int gid = 0;

class X
{
public:
    X(){objId = ++gid;log("X ctor");}
    X(const X& rhs){objId = ++gid;log("X copy ctor");}
    X& operator = (const X& rhs){this->objId = rhs.objId; log("X copy assignment"); return *this;}
    ~X(){log("X dtor");}
private:
    void log(const char* msg){
        cout << "[" << this << ", " << objId <<" ] " << msg << "\n";
    }
    int objId;
};

class Y
{
public:
    Y(){objId = ++gid;log("Y ctor");}
    Y(const Y& rhs){objId = ++gid;log("Y copy ctor");}
    Y& operator = (const Y& rhs){this->objId = rhs.objId; log("Y copy assignment"); return *this;}
    ~Y(){log("Y dtor");}
private:
    void log(const char* msg){
        cout << "[" << this << ", " << objId <<" ] " << msg << "\n";
    }
    X xinst;
    int objId;
};

class B1
{
public:
    B1(){objId = ++gid;log("B1 ctor");}
    B1(const B1& rhs){objId = ++gid;log("B1 copy ctor");}
    B1& operator = (const B1& rhs){this->objId = rhs.objId; log("B1 copy assignment"); return *this;}
    ~B1(){log("B1 dtor");}
private:
    void log(const char* msg){
        cout << "[" << this << ", " << objId <<" ] " << msg << "\n";
    }
    Y yinst;
    int objId;
};

class B2 : public B1
{
public:
    B2(){objId = ++gid;log("B2 ctor");}
    B2(const B2& rhs){objId = ++gid;log("B2 copy ctor");}
    B2& operator = (const B2& rhs){this->objId = rhs.objId; log("B2 copy assignment"); return *this;}
    ~B2(){log("B2 dtor");}
private:
    void log(const char* msg){
        cout << "[" << this << ", " << objId <<" ] " << msg << "\n";
    }
    int objId;
};

class Foo : public B2
{
public:
    Foo(){objId = ++gid;log("Foo ctor");}
    Foo(const Foo& rhs){objId = ++gid;log("Foo copy ctor");}
    Foo& operator = (const Foo& rhs){this->objId = rhs.objId; log("Foo copy assignment"); return *this;}
    ~Foo(){log("Foo dtor");}
private:
    void log(const char* msg){
        cout << "[" << this << ", " << objId <<" ] " << msg << "\n";
    }
    X xinst;
    int objId;
};


int main(int argc, char **argv)
{
    cout << endl << "--------------B1 obj1;" << endl;
    B1 obj1;
    cout << endl << "--------B1 obj2(obj1);" << endl;
    B1 obj2(obj1);
    cout << endl << "-------B1 obj3 = obj1;" << endl;
    B1 obj3 = obj1;
    cout << endl << "----------obj3 = obj2;" << endl;
    obj3 = obj2;
    cout << endl << "-------------Foo foo1;" << endl;
    Foo foo1;
    cout << endl << "-------Foo foo2(foo1);" << endl;
    Foo foo2(foo1);
    cout << endl << "----------foo2 = foo1;" << endl;
    foo2 = foo1;
    cout << endl << "----------------------" << endl;
}