#ifndef __REF_COUNTING_STRING_REF__
#define __REF_COUNTING_STRING_REF__

#include <cstring>
#include <iostream>

using namespace std;

class String {
    friend ostream& operator<<(ostream& stream, const String& str);
public:
    struct StringValue {
        int refCount;
        int length;
        char* data;
        bool shareable;

        StringValue(const char* initValue): refCount(1), shareable(true){
            length = strlen(initValue);
            data = new char[length+1];
            strcpy(data, initValue);
        }
        ~StringValue(){
            delete[] data;
        }
    };
public:
    StringValue* value;
private:
    void shareItOrNot(const String& it){
        if(it.value->shareable){
            value = it.value;   //
            ++value->refCount;  //increase reference count
        }
        else{
            value = new StringValue(it.value->data);
        }
    }
public:
    const char& operator[](int index) const {
        cout << " [ operator[] const ] " << endl;
        if(index < value->length)
            return value->data[index];
        //else
        //    return nullptr;
    }
    char& operator[](int index){
        cout << " [ operator[] non-const ] " << endl;
        //if(index >= value->length)
        //    return nullptr;

        if(value->refCount > 1){
            --value->refCount;
            value = new StringValue(value->data);
        }
        value->shareable = false;
        return value->data[index];
    }
    String(const char* initValue = ""): value(new StringValue(initValue)){}
    ~String(){
        if(--value->refCount == 0)
            delete value;
    }
    String(const String& rhs){  //copy ctor
        shareItOrNot(rhs);
    }
    String& operator=(const String& rhs){
        if(value == rhs.value) //same object, just ignore
            return *this;

        if(--value->refCount == 0)
            delete value;

        shareItOrNot(rhs);
        return *this;
    }
};

ostream& operator<<(ostream& os, const String& str)
{
    return os << str.value->data;
}


#endif //__REF_COUNTING_STRING_REF__
