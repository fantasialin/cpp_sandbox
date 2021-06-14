#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

#define _DEBUG_ 1
constexpr int _debug_ = 1;

enum class OutputFormat
{
    Markdown,
    Html
};

struct ListStrategy
{
  public :
    //~ListStrategy() { cout << "dtor - ListStrategy " << endl; }
    virtual ~ListStrategy() {}
    virtual void add_list_item(ostringstream& oss, const string& item) = 0;
    virtual void start(ostringstream& oss) = 0;
    virtual void end(ostringstream& oss) = 0;
};

struct MarkdownListStrategy : ListStrategy
{
  public :
    ~MarkdownListStrategy() { 
        #if _DEBUG_
        #ifndef WIN32
        cout << __PRETTY_FUNCTION__ << endl;
        #else
        cout << "dtor - MarkdownListStrategy " << endl; 
        #endif
        #endif
    }
    virtual void start(ostringstream& oss) override {}
    virtual void end(ostringstream& oss) override {}
    virtual void add_list_item(ostringstream& oss, const string& item) override {
        oss << " * " << item << endl;
    }
};

struct HtmlListStrategy : ListStrategy
{
  public :
    ~HtmlListStrategy() { 
        #if _DEBUG_
        #ifndef WIN32
        cout << __PRETTY_FUNCTION__ << endl;
        #else
        cout << "dtor - HtmlListStrategy " << endl; 
        #endif
        #endif
    }
    virtual void start(ostringstream& oss) override {
        oss << "<ul>" << endl;
    }
    virtual void end(ostringstream& oss) override {
        oss << "</ul>" << endl;
    }
    virtual void add_list_item(ostringstream& oss, const string& item) override {
        oss << "<li>" << item << "</li>" << endl;
    }

};

class TextProcessor
{
  public :
    void clear() {
        oss.str("");
        oss.clear();
    }

    void append_list(const vector<string> items){
        list_strategy->start(oss);
        for (auto& item : items){
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat format){
        switch(format){
          case OutputFormat::Markdown :
            list_strategy = make_unique<MarkdownListStrategy>();
            break;
          case OutputFormat::Html :
            list_strategy = make_unique<HtmlListStrategy>();
            break;
          default: 
            throw runtime_error("Unsupported strategy.");
        }
    }

    string str() const { return oss.str(); }

  private :
    ostringstream oss;
    unique_ptr<ListStrategy> list_strategy;
};


int main(int argc, char **argv){
    cout << "Strategy - dynamic test" << endl;

    //Markdonw
    TextProcessor tp;
    tp.set_output_format(OutputFormat::Markdown);
    tp.append_list({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    //Html
    tp.clear();
    tp.set_output_format(OutputFormat::Html);
    tp.append_list({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    return 0;
}