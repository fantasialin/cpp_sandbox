#include <functional>
#include <iostream>
#include <string>

using namespace std::placeholders;

class RedundencyManager // incl. Typo ;-)
{
public:
    // std::function<return_type(list of argument_type(s))>
    std::string Init(std::function<std::string(std::string)> f) 
    {
        std::string myName = " ZOZO ";
        return f(myName);
    }
};

class CLoggersInfra
{
private:
    std::string member = "Hello from non static member callback!";
    
public:
    static std::string RedundencyManagerCallBack(std::string name)
    {
        return std::string("Hello from static member callback!") + name;
    }
    
    std::string NonStaticRedundencyManagerCallBack(std::string name)
    {
        return member + name;
    }
};

std::string NonMemberCallBack(std::string name)
{
    return std::string("Hello from non member function!") + name;
}

int main()
{
    auto instance = RedundencyManager();

    std::string myName = " XOXO ";
    
    //auto callback1 = std::bind(&NonMemberCallBack, myName);
    auto callback1 = std::bind(&NonMemberCallBack,  _1);
    std::cout << instance.Init(callback1) << "\n";
    
    // Similar to non member function.
    auto callback2 = std::bind(&CLoggersInfra::RedundencyManagerCallBack, myName);
    std::cout << instance.Init(callback2) << "\n";
    
    // Class instance is passed to std::bind as second argument.
    // (heed that I call the constructor of CLoggersInfra)
    CLoggersInfra test03;
    //auto callback3 = std::bind(&CLoggersInfra::NonStaticRedundencyManagerCallBack, &test03, myName); 
    auto callback3 = std::bind(&CLoggersInfra::NonStaticRedundencyManagerCallBack, &test03, _1); 
    std::cout << instance.Init(callback3) << "\n";
}