#include <iostream>
#include <thread>
class Base {
public:
    Base(){ start = 100; }
    void fn(int i)
    { 
        for (int ctr = i; ctr >= 0; ctr--)
            std::cout << ctr << " "; 
        std::cout << " start = " << start << "\n";
    } 
private:
    int start;
};
 
int main()
{
    Base b;
    std::thread t1(&Base::fn, &b, 10);
    t1.join();
    return 0;
}
