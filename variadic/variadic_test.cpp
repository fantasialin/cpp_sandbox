// this example code is  reference https://eli.thegreenplace.net/2014/variadic-templates-in-c/
// and course from internal training

#include <iostream>
#include <string>


using namespace std;

#define _DEBUG_ 0
constexpr int _debug_ = 0;

template<typename T>
T adder(T v) {
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    return v;
}

template<typename T, typename... Args>
T adder(T first, Args... args){
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    return first + adder(args...);
}


template<typename T>
bool pair_comparer(T a){
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    //floating point might not correct to use "==" to compare
    return false;
}

template<typename T>
bool pair_comparer(T a, T b){
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    //floating point might not correct to use "==" to compare
    return a == b;
}

template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
    #ifndef WIN32
    #if _DEBUG_
    cout << __PRETTY_FUNCTION__ << endl;
    #endif
    #endif
    return a == b && pair_comparer(args...);
}


template<class... Ts> struct tuple_custom {};

template<class T, class... Ts>
struct tuple_custom<T, Ts...> : tuple_custom<Ts...> {
    tuple_custom(T t, Ts... ts) : tuple_custom<Ts...>(ts...), tail(t) {
        #ifndef WIN32
        #if _DEBUG_
        std::cout << __PRETTY_FUNCTION__ << endl;
        #endif
        #endif
    }

    T tail;
};

template<size_t, class> struct elem_type_holder;

template<class T, class... Ts>
struct elem_type_holder<0, tuple_custom<T, Ts...>> {
    typedef T type;
};

template <size_t k, class T, class... Ts>
struct elem_type_holder<k, tuple_custom<T, Ts...>> {
    typedef typename elem_type_holder<k-1, tuple_custom<Ts...>>::type type;
};

template <size_t k, class... Ts>
typename std::enable_if< k==0 , typename elem_type_holder<0, tuple_custom<Ts...>>::type&>::type get(tuple_custom<Ts...>& t) {
    return t.tail;
}

template <size_t k, class T, class... Ts>
typename std::enable_if< k!=0 , typename elem_type_holder<k, tuple_custom<T, Ts...>>::type&>::type get(tuple_custom<T, Ts...>& t) {
    tuple_custom<Ts...>& base = t;
    return get<k-1>(base);
}

template<typename...Values> class tuple_ace;
template<> class tuple_ace<> {};

template<typename Head, typename... Tail>
class tuple_ace<Head, Tail...> : private tuple_ace<Tail...> {
    typedef tuple_ace<Tail...> inherited;
  public:
    tuple_ace() {
        #ifndef WIN32
        #if _DEBUG_
        std::cout << __PRETTY_FUNCTION__ << endl;
        #endif
        #endif
    }
    tuple_ace(Head v, Tail... vtail) : m_head(v), inherited(vtail...) {
        #ifndef WIN32
        #if _DEBUG_
        std::cout << __PRETTY_FUNCTION__ << endl;
        #endif
        #endif
    }
    Head head() { return m_head; }
    inherited& tail() { return *this; }
  protected:
    Head m_head;
};


int main(int argc, char **argv){
    cout << "variadic template" << endl;

    long sum = adder(1, 2, 3, 4, 5, 6, 7, 8, 9);

    cout << " sum 1 + 2 + 3 + ... + 9 = " << sum << endl;

    string s1 ="A ", s2 ="Farewell ", s3 = "to ", s4="Arms.";

    string nNmae = adder(s1, s2, s3, s4);

    cout << "Novel = " << nNmae << endl;

    cout << "pair compare (1.5 , 1.5, 2, 2, 6, 6) : " << pair_comparer(1.5 , 1.5, 2, 2, 6, 6) << endl;
    // does not compile; the compiler complains that the base case expects 2 arguments but only 1 is provied (if 1 argument base case is not provided).
    cout << "pair compare (1.5 , 1.5, 2, 2, 6, 6, 7) : " << pair_comparer(1.5 , 1.5, 2, 2, 6, 6, 7) << endl; 


    tuple_custom<double, int, const char*> t1(12.2, 42, "big");
    cout << "size of (12.2, 42, \"big\") : " << sizeof(t1) << endl;

    cout << "0th elem is " << get<0>(t1) << "\n";
    cout << "1th elem is " << get<1>(t1) << "\n";
    cout << "2th elem is " << get<2>(t1) << "\n";

    //set 1th element as 103
    get<1>(t1) = 103;
    cout << "1th elem is " << get<1>(t1) << "\n";

    tuple_custom<int, float, const char*> t2(41, 6.3, "nico");
    cout << "size of (41, 6.3, \"nico\") : " << sizeof(t2) << endl;

    cout << "0th elem is " << get<0>(t2) << "\n";
    cout << "1th elem is " << get<1>(t2) << "\n";
    cout << "2th elem is " << get<2>(t2) << "\n";

    tuple_ace<int, float, string> t(41, 6.3, "nico");
    cout << "size of (41, 6.3, \"nico\") : " << sizeof(t) << endl;
    cout << "tuple (41, 6.3, \"nico\") : " << t.head() << " , " << t.tail().head() << " , " << t.tail().tail().head() << endl;

    return 0;
}