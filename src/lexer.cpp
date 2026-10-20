//file to split code into tokens (remove comments) so an AST can be built.
//glsl-debug/res/red.frag
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cassert>

using namespace std;

//define list of each type

enum class tokentype {
    keyword,
    identifier,
    literal,
    op,
    punctuation,
    eof
};

unordered_map<string, tokentype> keyword_names = { //used to tell type of keyword
    {"keyword", tokentype::keyword},
    {"identifier", tokentype::identifier},
    {"literal", tokentype::literal},
    {"op", tokentype:: op},
    {"punctuation", tokentype::punctuation},
    {"eof", tokentype::eof}
};
unordered_map<int, unordered_map<string, tokentype>> keyword_list = {}; //initialise through text file

struct token {
    tokentype type;
    string lexeme;
    int line;
};

vector<string> split_line(string line) {
    stringstream ss(line);
    string word;
    vector<string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;

}

vector<token> str_to_tok(string chunk, int line) {
    vector<token> out;
    string temp = chunk;
    //go through 

    while(temp.length() > 0) {
        bool found_chunk = false;

        if (isalnum(temp.at(0)) || temp.at(0) == '_' || (temp.at(0) == '.' && int(temp.length()) > 1 && isdigit(temp.at(1)))) {
            int length = 1;
            while(length < int(temp.length()) && (isalnum(temp.at(length)) || temp.at(length) == '_' || (temp.at(length) == '.' && isdigit(temp.at(length - 1)) && length + 1 < int(temp.length()) && isdigit(temp.at(length + 1))))) length ++;

            string lex = temp.substr(0, length);

            bool key = keyword_list.find(lex.length()) != keyword_list.end();
            if (key) key &= keyword_list[lex.length()].find(lex) != keyword_list[lex.length()].end();

            out.push_back(token{
                key ? keyword_list[lex.length()][lex] : (isalpha(lex.at(0)) ? tokentype::identifier : tokentype::literal),
                lex,
                line
            });
            found_chunk = true;
            temp = temp.substr(length);
        }

        if (found_chunk) continue;

        for (int x = temp.length(); x > 0; x--) {
            //if (keyword_list.find(x) == keyword_list.end()) continue; //if no tokens of specific length, skip

            //check keywords
            if (keyword_list[x].find(temp.substr(0, x)) != keyword_list[x].end()) {

                out.push_back(token{
                    keyword_list[x][temp.substr(0, x)], 
                    temp.substr(0, x), 
                    line
                });

                found_chunk = true;
                temp = temp.substr(x);
                break;
            } //if no tokens matching the text, skip
        }

        if (!found_chunk) {
            out.push_back(token{tokentype::identifier, temp, line});
            temp = temp.substr(temp.length());
        }
    }

    return out;
}

vector<token> remove_comments(vector<token> toks) {
    int remove_line = -1;
    bool removing = false;
    for (auto x = toks.begin(); x != toks.end();) {
        if (x -> lexeme == "//") remove_line = x -> line;
        if (x -> lexeme == "/*" && remove_line != x -> line) removing = true;

        string temp = x -> lexeme;

        if (x -> line == remove_line) {
            x = toks.erase(x);
            continue;
        }
        
        if (temp == "*/") {
            removing = false;
            x = toks.erase(x);
            continue;
        }

        if (removing) {
            x = toks.erase(x);
            continue;
        }

        x++;
    }
    return toks;
}

vector<token> tokenize(string filename) {
    ifstream file(filename);
    int linen = 0;

    vector<token> out;

    string line;

    while (getline(file, line)) {
        linen ++;

        vector<string> words = split_line(line);
        vector<token> toks;

        for (unsigned long x = 0; x<words.size(); x++) {
            //insert each token split accordingly.
            vector<token> split = str_to_tok(words[x], linen);
            toks.reserve(toks.size() + split.size());
            
            toks.insert(toks.end(), split.begin(), split.end());
        }

        out.reserve(out.size() + toks.size());
        out.insert(out.end(), toks.begin(), toks.end());

        cout << line << endl;
    }
    return remove_comments(out);
}

//debugging function
string tok_to_str(tokentype t) {
    switch(t) {
        case tokentype::keyword: 
            return "keyword";
        case tokentype::identifier: 
            return "identifier";
        case tokentype::literal: 
            return "literal";
        case tokentype::op: 
            return "op";
        case tokentype::punctuation: 
            return "punctuation";
        case tokentype::eof: 
            return "eof";
    }
}

void print_tokens(vector<token> toks) {
    for (unsigned long x = 0; x<toks.size(); x++) {
        cout << tok_to_str(toks[x].type) << ": " << toks[x].lexeme << " [" << toks[x].line << "]" << endl;
    }
}

void initialise_token_list(string filename) {
    ifstream file(filename);

    string line;

    while(getline(file, line)) {
        vector<string> temp = split_line(line);
        assert(temp.size() == 2);

        keyword_list[temp[0].length()][temp[0]] = keyword_names[temp[1]];
        
    }
}