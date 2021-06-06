
template<class... Ts> struct tuple_custom {};

template<class T, class... Ts>
struct tuple_custom<T, Ts...> : tuple_custom<Ts...> {
    tuple_custom(T t, Ts... ts) : tuple_custom<Ts...>(ts...), tail(t) {}

    T tail;
};

int main(int argc, char** argv) {
    tuple_custom<double, int, const char*> t1(12.2, 42, "big");
    return sizeof(t1);
}