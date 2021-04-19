
#include <TextQuery.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream& open_file(ifstream& in, const string& file){
    in.close();
    in.clear();
    in.open(file.c_str());
    return in;
}

string make_plural(size_t ctr, const string& word, const string& ending){
    return (ctr <=1) ? word : word + ending;
}

void print_results(const set<TextQuery::line_no>& locs, const string& sought, const TextQuery& file){
    typedef set<TextQuery::line_no> line_num;
    line_num::size_type size = locs.size();
    cout << "\n" << sought << " occurs " << size << " " << make_plural(size, "time", "s") << endl;
    line_num::const_iterator it = locs.begin();
    for(; it != locs.end(); ++it){
        cout << "\t(line " << (*it)+1 << " ) " << file.text_line(*it) << endl;
    }
}

int main(int argc, char **argv){
    ifstream infile;
    if(argc < 2 || !open_file(infile, argv[1])){
        cerr << "No input file!\n";
        return EXIT_FAILURE;
    }
    TextQuery tq;
    tq.read_file(infile);

    while(true){
        cout << "Enter word to look for, or q to quit: ";
        string s;
        cin >> s;
        if(!cin || s=="q") break;

        set<TextQuery::line_no> locs = tq.run_query(s);
        print_results(locs, s, tq);
    }
    cout << "Program exit!\n";
    return EXIT_SUCCESS;
}