#include <iostream>
#include <string>
#include <cstring>
#include <functional>

using namespace std;

class MyString {
  private:
    char* _data;
    size_t _len;

    void _init_data(const char* s) {
        _data = new char[_len+1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
  public:
    inline char const* get() const { return (char const*)_data; }
    //default ctor
    MyString() : _data(nullptr), _len(0) { ++DCtor; }

    //ctor
    MyString(const char* p) : _len(strlen(p)) {
        ++Ctor;
        _init_data(p);
    }

    //copy ctor
    MyString(const MyString& rhs) : _len(rhs._len) {
        ++CCtor;
        _init_data(rhs._data);//copy
    }

    //move ctor, with "noexcept"
    MyString(MyString&& rhs) noexcept : _data(rhs._data), _len(rhs._len) {
        ++MCtor;
        rhs._len = 0;
        rhs._data = nullptr;
    }

    //copy assignment
    MyString& operator=(const MyString& rhs) {
        ++CAsgn;
        if(this != &rhs){
            if(_data) delete[] _data;
            _len = rhs._len;
            _init_data(rhs._data);//copy
        }
        return *this;
    }

    //dtor
    virtual ~MyString() noexcept {
        ++Dtor;
        if(_data) {
            delete[] _data;
        }
    }

    bool
    operator<(const MyString& rhs) const {
        return std::string(this->_data) < std::string(rhs._data);
    }

    bool
    operator==(const MyString& rhs) const {
        return std::string(this->_data) == std::string(rhs._data);
    }

    //move assignment
    MyString& operator=(MyString&& rhs) noexcept {
        ++MAsgn;
        if(this != &rhs){
            if(_data) delete[] _data;
            _len = rhs._len;
            _data = rhs._data;
            rhs._len = 0;
            rhs._data = nullptr;
        }
        return *this;
    }


  private:
    // for recording BIG5 invoked count
    static size_t DCtor; // default ctor
    static size_t Ctor; // ctor
    static size_t CCtor; //copy ctor
    static size_t CAsgn; // copy assignment
    static size_t MCtor; // move ctor
    static size_t MAsgn; // move assignment
    static size_t Dtor; //dtor

  public:
    void BIG5_statistics_output() {
        cout << "Deft Ctor: " << DCtor << endl;
        cout << "     Ctor: " << Ctor << endl; 
        cout << "Copy Ctor: " << CCtor << endl;
        cout << "Copy Asgn: " << CAsgn << endl;
        cout << "Move Ctor: " << MCtor << endl;
        cout << "Move Asgn: " << MAsgn << endl;
        cout << "     Dtor: " << Dtor << endl; 

    }
    void BIG5_statistics_reset() {
         DCtor = Ctor = CCtor = CAsgn = MCtor = MAsgn = Dtor = 0;
    }

};

size_t MyString::DCtor = 0;
size_t MyString::Ctor = 0;
size_t MyString::CCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MCtor = 0;
size_t MyString::MAsgn = 0; 
size_t MyString::Dtor = 0;

namespace std
{
    template<>
    struct hash<MyString> {//for unordered container
        size_t operator()(const MyString& rhs) const noexcept {
            return hash<string>()(string(rhs.get()));
        }
    };

    ostream& operator<<(ostream& os, const MyString& rhs){
        return os << rhs.get() << " [" << (void*)(rhs.get()) << "]" << endl;
    }

}


#include <ctime>
#include <chrono>
#include <cstring>
#include <cstdio>

enum RV { Rvalue, Lvalue };


int main(int argc, char **argv){
    cout << "mystring - rvalue ref test" << endl;

    return 0;
}