#include <functional>
#include <string>
#include <iostream>
 
void goodbye(const std::string& s)
{
    std::cout << "Goodbye " << s << '\n';
}
 
class Object {
public:
    void hello(const std::string& s)
    {
        std::cout << "Hello " << s << '\n';
    }
};
 
int main()
{
    using namespace std::placeholders;
 
    using ExampleFunction = std::function<void(const std::string&)>;
    Object instance;
    std::string str("World");
 
    ExampleFunction f = std::bind(&Object::hello, &instance, _1);
    f(str);  // equivalent to instance.hello(str)
 
    f = std::bind(&goodbye, std::placeholders::_1);
    f(str);  // equivalent to goodbye(str)
 
    auto lambda = [](std::string pre, char o, int rep, std::string post) {
        std::cout << pre;
        while (rep-- > 0) std::cout << o;
        std::cout << post << '\n';
    };
 
    // binding the lambda:
    std::function<void(std::string, char, int, std::string)> g =
        std::bind(&decltype(lambda)::operator(), &lambda, _1, _2, _3, _4);
    g("G", 'o', 'o'-'g', "gol");
}
