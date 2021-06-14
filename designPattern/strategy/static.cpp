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

template <typename T>
class TextProcessor
{
  public :
    void clear() {
        oss.str("");
        oss.clear();
    }

    void append_list(const vector<string> items){
        list_strategy.start(oss);
        for (auto& item : items){
            list_strategy.add_list_item(oss, item);
        }
        list_strategy.end(oss);
    }

    string str() const { return oss.str(); }

  private :
    ostringstream oss;
    T list_strategy;
};


int main(int argc, char **argv){
    cout << "Strategy - dynamic test" << endl;

    //Markdonw
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list({"foo", "bar", "baz"});
    cout << tpm.str() << endl;

    //Html
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list({"foo", "bar", "baz"});
    cout << tph.str() << endl;

    return 0;
}