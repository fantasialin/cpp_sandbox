
#include <iostream>
#include <algorithm>
#include <TextQuery.h>
#include <string.h>

using namespace std;

void TextQuery::store_file(ifstream& is){
    string textline;
    count = 0;
    while(getline(is, textline)){
        lines_of_text.push_back(textline);
        count++;
    }
    cout << "total " << count << " lines\n";
}

void TextQuery::build_map(){
    char chars[] = ",.?\"";
    for(line_no line_num =0;
        line_num != lines_of_text.size();
        ++line_num){
        
        istringstream line(lines_of_text[line_num]);

        string word;
        while(line >> word){
            for(unsigned int i = 0; i < strlen(chars); ++i){
                word.erase(remove(word.begin(), word.end(), chars[i] ), word.end());
            }
            word_map[word].insert(line_num);
        }
    }
}

set<TextQuery::line_no> TextQuery::run_query(const string& query_word) const {
    map<string, set<line_no>>::const_iterator loc = word_map.find(query_word);
    if(loc == word_map.end())
        return set<line_no>();
    else
        return loc->second;
}

string TextQuery::text_line(line_no line) const{
    if(line < lines_of_text.size())
        return lines_of_text[line];
    throw std::out_of_range("line number out of range.");
}

