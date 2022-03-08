
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class HtmlBuilder;
class HtmlElement;

class HtmlElement
{
  private:
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text)
        : name(name), text(text) {}
    friend class HtmlBuilder;

  public:
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
    static unique_ptr<HtmlBuilder> build(string root_name)
    {
        return make_unique<HtmlBuilder>(root_name);
    }
};

class HtmlBuilder
{
  public:
    HtmlBuilder(string root_name){ root.name = root_name; }
    HtmlBuilder* add_child(string child_name, string child_text)
    {
        HtmlElement elm{ child_name, child_text};
        root.elements.emplace_back(elm);
        return this;//return a pointer of itself
    }

    string str() { return root.str(); }

  private:
    HtmlElement root;
};

int main(int argc, char **argv){
    cout << "Builder - fluent test" << endl;
    auto builder = HtmlElement::build("ul");
    builder->add_child( "li", "hello" )->add_child( "li", "world" );
    cout << builder->str() << endl;
    return 0;
};
