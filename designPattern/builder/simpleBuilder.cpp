
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

struct HtmlFluentBuilder;
struct HtmlFluentPtrBuilder;

struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text)
        : name(name), text(text) {}
    
    string str(int indent = 0) const
    {
        // pretty-print the contents
        ostringstream oss;
        string i(indent_size*indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
        oss << string(indent_size*(indent + 1), ' ') << text << endl;

        for (const auto& e : elements)
        oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static unique_ptr<HtmlFluentBuilder> build(string root_name)
    {
        return make_unique<HtmlFluentBuilder>(root_name);
    }

    static unique_ptr<HtmlFluentPtrBuilder> build2(string root_name)
    {
        return make_unique<HtmlFluentPtrBuilder>(root_name);
    }
};


struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(string root_name){ root.name = root_name; }
    void add_child(string child_name, string child_text)
    {
        HtmlElement elm{ child_name, child_text};
        root.elements.emplace_back(elm);
    }

    string str() { return root.str(); }
};


struct HtmlFluentBuilder
{
    HtmlElement root;

    HtmlFluentBuilder(string root_name){ root.name = root_name; }
    // by returning a reference to the builder itself, the builder calls
    // can now be chained. This is what's called a fluent interface.
    HtmlFluentBuilder& add_child(string child_name, string child_text)
    {
        HtmlElement elm{ child_name, child_text};
        root.elements.emplace_back(elm);
        return *this;//return a reference of itself
    }

    string str() { return root.str(); }
};


struct HtmlFluentPtrBuilder
{
    HtmlElement root;

    HtmlFluentPtrBuilder(string root_name){ root.name = root_name; }
    // by returning a pointer to the builder itself, the builder calls
    // can now be chained. This is what's called a fluent interface.
    HtmlFluentPtrBuilder* add_child(string child_name, string child_text)
    {
        HtmlElement elm{ child_name, child_text};
        root.elements.emplace_back(elm);
        return this;//return a pointer of itself
    }

    string str() { return root.str(); }

    operator HtmlElement() const { return root; }
};

int main(int argc, char **argv){
    cout << "Builder - simple test" << endl;

    string words[] = { "hello", "world" };
    HtmlElement list{"ul", "" };

    for (auto w: words)
        list.elements.emplace_back(HtmlElement{ "li", w});

    cout << list.str() << endl;

    //simple builder
    cout << "simple builder\n";
    HtmlBuilder builder{ "ul" };
    builder.add_child( "li", "hello" );
    builder.add_child( "li", "world" );

    cout << builder.str() << endl;

    //fluent builder
    cout << "fluent interface builder\n";
    HtmlFluentBuilder flubuilder{ "ul" };
    flubuilder.add_child( "li", "hello" ).add_child( "li", "world" );

    cout << flubuilder.str() << endl;

    //fluent builder
    cout << "fluent interface with pointer builder\n";
    HtmlFluentPtrBuilder fluPtrbuilder{ "ul" };
    fluPtrbuilder.add_child( "li", "hello" )->add_child( "li", "world" );

    cout << fluPtrbuilder.str() << endl;

    //fluent builder
    cout << "add build interface int HtmlElement\n";
    auto fluPtrbuilder2 = HtmlElement::build("ul")->add_child( "li", "hello" ).add_child( "li", "world" );
    cout << fluPtrbuilder2.str() << endl;

    //fluent builder2
    cout << "add build2 interface int HtmlElement\n";
    auto fluPtrbuilder3 = HtmlElement::build2("ul")->add_child( "li", "hello" )->add_child( "li", "world" );
    cout << fluPtrbuilder3 << endl;

    return 0;
}