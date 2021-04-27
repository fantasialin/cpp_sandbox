
#ifndef __TEXTQUERY_EXAMPLE__
#define __TEXTQUERY_EXAMPLE__


#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream> //ifstream
#include <sstream> //istringstream

using namespace std;


class TextQuery{
public:
    typedef vector<string>::size_type line_no;

    void read_file(ifstream &is){ 
        store_file(is);
        build_map();
    }

    set<line_no> run_query(const string& ) const;
    string text_line(line_no) const;

    size_t size() const { return count; }
private:
    void store_file(ifstream& is);
    void build_map();
private:
    vector<string> lines_of_text;
    map<string, set<line_no>> word_map;
    size_t count;
};

#endif //__TEXTQUERY_EXAMPLE__