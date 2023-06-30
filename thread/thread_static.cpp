#include <iostream>
#include <thread>
class Base 
{
public:
    static void fn(int i) {
        for (int ctr = i; ctr >= 0; ctr--)
            std::cout << ctr << " "; 
        std::cout << "\n";
    } 
};

int main() 
{
    std::thread t1(&Base::fn, 10);
    t1.join();
    return 0;
}