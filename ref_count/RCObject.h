/******************************************************************************
*                                                                             *
*        Code from Item 29 ("Reference Counting") of MORE EFFECTIVE C++       *
*                                                                             *
*                               Scott Meyers                                  *   
*                                                                             *
*                             November 15, 1997                               *
*                                                                             *
*            Copyright 1996 (c) Addison-Wesley Publishing Company             *
*       You are free to use this code for non-commercial purposes only.       *
*                                                                             *
* This page contains the code for the classes and class templates making up   *
* the Reference Counting Item of MORE EFFECTIVE C++.  To use this code,       *
* either copy this page and paste it into a C++ source file or save the       *
* entire page as text into a C++ source file.  Don't save the HTML source     *
* and expect that to compile :-)                                              *
*                                                                             *
* Each class or template in this file follows a block comment that shows the  *
* corresponding pages in the book.  This page also contains a main function   *
* that performs a VERY limited test of the code in this file.  You can        *
* compile the code in this file as a stand-alone program, and you should get  *
* this output:                                                                *
*                                                                             *
*     String with no changes.                                                 *
*     String with    changes.                                                 *
*     10                                                                      *
*     -1                                                                      *
*                                                                             *
* The code here reflects all changes made to date in response to bug reports  *
* from readers of the book.  (To see a complete list of known bugs in MORE    *
* EFFECTIVE C++, as well as whether they've been fixed yet, visit the         *
* More Effective C++ Errata List.)  If you find any additional bugs, please   *
* send them to me.                                                            *
******************************************************************************/
#ifndef __RC_OBJECT__
#define __RC_OBJECT__

#include <iostream>    // The iostream facilities are not used in the classes
                         // in this file, but they are used in the code that 
                         // tests the classes.

#include <cstring>      // This includes the C string functions, e.g.,
                         // strlen, strcpy, etc.  They are used in the
                         // implementation of class String::StringValue.

// The following is for compilers that don't support bool.  Comment these
// lines out if your compilers do support bool.  For details on this emulation
// of bool, see More Effective C++, pp. 3-4.
//typedef int bool;
//const bool false = 0;
//const bool true = 1;

using namespace std;

/******************************************************************************
*                       Class RCObject (from pp. 204-205)                     *
******************************************************************************/
class RCObject {                       // base class for reference-
public:                                // counted objects
  void addReference();
  void removeReference();
  void markUnshareable();
  bool isShareable() const;
  bool isShared() const;

protected:
  RCObject();
  RCObject(const RCObject& rhs);
  RCObject& operator=(const RCObject& rhs);
  virtual ~RCObject() = 0;

private:
  int refCount;
  bool shareable;
};

RCObject::RCObject()
: refCount(0), shareable(true) {}

RCObject::RCObject(const RCObject&)
: refCount(0), shareable(true) {}

RCObject& RCObject::operator=(const RCObject&)
{
  return *this;
}  

RCObject::~RCObject() {}

void RCObject::addReference() 
{
  ++refCount;
}

void RCObject::removeReference()
{
  if (--refCount == 0) delete this;
}

void RCObject::markUnshareable()
{
  shareable = false;
}

bool RCObject::isShareable() const
{
  return shareable;
}

bool RCObject::isShared() const
{
  return refCount > 1;
}  


/******************************************************************************
*                 Template Class RCPtr (from pp. 203, 206)                    *
******************************************************************************/
template<class T>                      // template class for smart
class RCPtr {                          // pointers-to-T objects; T
public:                                // must support the RCObject interface
  RCPtr(T* realPtr = 0);
  RCPtr(const RCPtr& rhs);
  ~RCPtr();
  RCPtr& operator=(const RCPtr& rhs);                     
  T* operator->() const;
  T& operator*() const;

private:
  T *pointee;
  void init();
};

template<class T>
void RCPtr<T>::init()
{
  if (pointee == 0) return;
  
  if (pointee->isShareable() == false) {
    pointee = new T(*pointee);
  }
  
  pointee->addReference();
}

template<class T>
RCPtr<T>::RCPtr(T* realPtr)
: pointee(realPtr)
{
  init();
}

template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs)
: pointee(rhs.pointee)
{ 
  init();
}

template<class T>
RCPtr<T>::~RCPtr()
{
  if (pointee) pointee->removeReference();
}

template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
  if (pointee != rhs.pointee) {                   
    if (pointee) pointee->removeReference();                

    pointee = rhs.pointee;
    init(); 
  }
  
  return *this;
}

template<class T>
T* RCPtr<T>::operator->() const 
{
  return pointee;
}

template<class T>
T& RCPtr<T>::operator*() const
{
  return *pointee;
}


/******************************************************************************
*           Classes String and StringValue (from pp. 204, 206-207)            *
******************************************************************************/
class String {                          // class to be used by
public:                                 // application developers
  String(const char *value = "");

  char operator[](int index) const;       
  char& operator[](int index);

private:
  // class representing string values
  struct StringValue: public RCObject {
    char *data;
    
    StringValue(const char *initValue);
    StringValue(const StringValue& rhs);
    void init(const char *initValue);
    ~StringValue();
  };

  RCPtr<StringValue> value;                       

  // This function is not in the book, but it's convenient for testing the
  // class -- see below.
  friend ostream& operator<<(ostream& stream, const String& str);
};

void String::StringValue::init(const char *initValue)
{
  data = new char[strlen(initValue) + 1];
  strcpy(data, initValue);
}

String::StringValue::StringValue(const char *initValue)
{ 
  init(initValue);
}

String::StringValue::StringValue(const StringValue& rhs)
{
  init(rhs.data);
}

String::StringValue::~StringValue()
{
  delete [] data;
}


String::String(const char *initValue)
: value(new StringValue(initValue)) {}

char String::operator[](int index) const
{
  return value->data[index];
}

char& String::operator[](int index)
{ 
  if (value->isShared()) {      
    value = new StringValue(value->data);
  }

  value->markUnshareable();

  return value->data[index];
}

ostream& operator<<(ostream& stream, const String& str)
{
  return stream << str.value->data;
}


/******************************************************************************
*                  Template Class RCIPtr (from pp. 209-210)                   *
*                                                                             *
* The code for RCIPtr that appeared in the first three printings of More      *
* Effective C++ had bugs.  (For details, see the More Effective C++ errata,   *
* which is available at http://www.aw.com/cp/mec++.html or via anonymous FTP  *
* from ftp.aw.com in the directory cp/mec++.)  The bugs are fixed in the      *
* code below.  Each line of code that was added or modified (compared to what *
* appeared in the first three printings of the book) is flagged.  If you have *
* the fourth or later printings of More Effective C++, you can ignore these   *
* comments, as the corrected code already appears in your book.               *
******************************************************************************/
template<class T>
class RCIPtr {
public:
  RCIPtr(T* realPtr = 0);
  RCIPtr(const RCIPtr& rhs);
  ~RCIPtr();
  RCIPtr& operator=(const RCIPtr& rhs);
  T* operator->();                           // added
  const T* operator->() const;               // modified
  T& operator*();                            // added
  const T& operator*() const;                // modified

private:
  struct CountHolder: public RCObject {
    ~CountHolder() { delete pointee; }
    T *pointee;
  };
  
  CountHolder *counter;

  void init();
  void makeCopy();                           // added
};

template<class T>
void RCIPtr<T>::init()                       // modified (the test of count
{                                            // against 0 was unnecessary
                                             // and thus removed)
  if (counter->isShareable() == false) {
    T *oldValue = counter->pointee;          // added 
    counter = new CountHolder;
    counter->pointee = new T(*oldValue);     // modified
  }

  counter->addReference();
}

template<class T>
RCIPtr<T>::RCIPtr(T* realPtr)
: counter(new CountHolder)
{ 
  counter->pointee = realPtr;
  init();
}

template<class T>
RCIPtr<T>::RCIPtr(const RCIPtr& rhs)
: counter(rhs.counter)
{
  init();
}

template<class T>
RCIPtr<T>::~RCIPtr()
{
  counter->removeReference();                // modified
}

template<class T>
RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr& rhs)
{
  if (counter != rhs.counter) {                   
    counter->removeReference();              // modified
    counter = rhs.counter;
    init();
  }
  
  return *this;
}

template<class T>
T* RCIPtr<T>::operator->()                     // this whole function is added
{
  makeCopy();
  return counter->pointee;
}

template<class T>
const T* RCIPtr<T>::operator->() const         // modified
{
  return counter->pointee;
}

template<class T>
T& RCIPtr<T>::operator*()                      // this whole function is added
{
  makeCopy();
  return *(counter->pointee);
}

template<class T>
const T& RCIPtr<T>::operator*() const          // modified
{
  return *(counter->pointee);
}

template<class T>                              // This whole function is added.
void RCIPtr<T>::makeCopy()                     // Note that there is no need to
{                                              // test to see if counter->pointee
  if (counter->isShared()) {                   // is null, because this function
    T *oldValue = counter->pointee;            // is called only from 
    counter->removeReference();                // dereferencing operators
    counter = new CountHolder;
    counter->pointee = new T(*oldValue);
    counter->addReference();
  }
}


/******************************************************************************
*                          Class Widget (from p. 210)                         *
*                                                                             *
* This class is the same as that in the book, but I've added an               *
* implementation so that RCIPtr can be tested.                                *
******************************************************************************/
class Widget {
public:
  Widget(int size): value(size) {}
  Widget(const Widget& rhs): value(rhs.value) {}
  ~Widget() {}

  Widget& operator=(const Widget& rhs) { value = rhs.value;  return *this; }

  void doThis() { value = -1; }
  int showThat() const { return value; }
  
private:
  int value;
};


/******************************************************************************
*                         Class RCWidget (from p. 210)                        *
******************************************************************************/
class RCWidget {
public:
  RCWidget(int size)
  : value(new Widget(size)) {}

  void doThis() { value->doThis(); }

  int showThat() const { return value->showThat(); }

private:
  RCIPtr<Widget> value;
};

#endif //__RC_OBJECT__
