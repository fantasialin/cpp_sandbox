
template<typename... Values> class tup_ace;
template<> class tup_ace<> {};
template<typename Head, typename... Tail>
class tup_ace<Head, Tail...> {
    typedef tup_ace<Tail...> composited;
  protected:
    composited m_tail;
    Head m_head;
  public:
    tup_ace() {}
    tup_ace(Head v, Tail... vtail) : m_head(v), m_tail(vtail...){}

    Head head() { return m_head; }
    composited& tail() { return m_tail; }
};

int main(int argc, char** argv) {
    tup_ace<double, int, const char*> t(12.2, 42, "nico");
    return sizeof(t);
}