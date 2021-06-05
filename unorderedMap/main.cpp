
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <tuple>
#include <functional>
#include <bitset>
#include <complex>

using namespace std;

using std::ostream;

constexpr int _debug_ = 0;

struct Customer {
    string firstName, lastName;
    unsigned int age;
  
    Customer(string f, string l, unsigned int a) {
        firstName = f;
        lastName = l;
        age = a;
    }
  
    // Match both first and last names in case of collisions.
    bool operator==(const Customer& p) const {
        #if _debug_
        cout << "operator== invoked" << endl;
        #endif
        return firstName == p.firstName && lastName == p.lastName;
    }

};

ostream& operator << (ostream& os, const Customer& c) {
    return os << '(' << c.firstName << ' ' << c.lastName << ", " << c.age << " )";
}

// custom hash can be a standalone function object:
struct CustomerHash
{
    std::size_t operator()(Customer const& c) const noexcept
    {
        #if 0
        std::size_t h1 = std::hash<std::string>{}(c.firstName);
        std::size_t h2 = std::hash<std::string>{}(c.lastName);
        #if _debug_
        cout << "hash value : " << (h1 ^ (h2 << 1)) << endl;
        #endif
        return h1 ^ (h2 << 1);
        #else
        auto hash_value = (hash<string>()(c.firstName)) ^ (hash<string>()(c.lastName));
        #if _debug_
        cout << "hash value : " << hash_value << endl;
        #endif
        return hash_value;
        #endif
    }
};

void printX(){
    cout << endl;
}

template <typename T, typename... Types>
void printX(const T& firstArg, const Types&... args){
    cout << firstArg << ' ';
    printX(args...);
}

template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
    print_tuple(std::ostream&, const tuple<T...>&)
{}

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
    print_tuple(ostream& os, const tuple<T...>& tup)
{
    if (n != 0)
        os << ", ";
    os << get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
ostream& operator<<(ostream& os, const tuple<T...>& tup)
{
    os << "[";
    print_tuple<0>(os, tup);
    return os << "]";
}

void func(int) { cout << __FUNCTION__ << endl; }

struct Functor { 
    void operator()(int) { cout << __FUNCTION__ << endl; }
};

struct ConvertToFuncPtr {
    using FuncType = void(*)(int);
    static void f(int) { cout << "static f() in class ConvertToFuncPtr, " << __FUNCTION__ << endl; }
    operator FuncType() const { return f; }
};

struct foo {
    static void memfunc(int) { cout << __FUNCTION__ << endl; }
};

int main(int argc, char **argv){
    //lambda, range-based for
    vector<int> vi { 5,28, 50, 83, 70, 590, 245, 59, 24};
    int x = 30;
    int y = 100;
    vi.erase(remove_if(vi.begin(), vi.end(), [x,y](int n) { return x < n && n < y; }), vi.end());
    for (auto i : vi )
        cout << i << ' ';
    cout << endl;

    //unordered_set, silver bullet for has function
    unordered_set<Customer, CustomerHash> mySet;
    mySet.insert(Customer("Ace", "Hou", 1961L));
    mySet.insert(Customer("Sabri", "Hou", 1998L));
    mySet.insert(Customer("Stacy", "Chen", 1967L));
    for (auto& elem : mySet){
        cout << elem;
    }
    cout << endl;

    //tuple, operator<< for tubple
    auto t = make_tuple(7.5, string("hello"), bitset<16>(377), complex<int>(1,3));
    cout << sizeof(t) << endl;
    cout << get<3>(t) << endl;
    cout << t << endl;

    //variadic templates function
    printX(7.5, string("hello"), bitset<16>(377), complex<int>(1,3));

    //std::bind
    vector<int> v {15, 35, 94, 50, 73, 58, 28,98};
    cout << count_if(v.cbegin(), v.cend(), [](int i){return i < 50;}) << endl;//lambda expression
    #ifndef WIN32
    cout << count_if(v.cbegin(), v.cend(), bind2nd(less<int>(), 50)) << endl;//c++11
    #endif
    using namespace std::placeholders;
    auto fn_ = bind(less<int>(), _1, 50);
    cout << count_if(v.begin(), v.end(), bind(less<int>(), _1, 50)) << endl;
    cout << count_if(v.begin(), v.end(), fn_) << endl;


    //std::function
    function<void(int)> FuncArray[4] {func, Functor(), ConvertToFuncPtr(), foo::memfunc };
    for (auto& i : FuncArray)
        i(928);
}