
template<typename...Values> class tuple_ace;
template<> class tuple_ace<> {};

template<typename Head, typename... Tail>
class tuple_ace<Head, Tail...> : private tuple_ace<Tail...> {
    typedef tuple_ace<Tail...> inherited;
  public:
    tuple_ace() {}
    tuple_ace(Head v, Tail... vtail) : m_head(v), inherited(vtail...) { }
    Head head() { return m_head; }
    inherited& tail() { return *this; }
  protected:
    Head m_head;
};


int main(int argc, char** argv) {
    tuple_ace<double, int, const char*> t(12.2, 42, "nico");
    return sizeof(t);
}