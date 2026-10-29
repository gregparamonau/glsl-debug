
#include <unordered_map>
#include <string> 
#include "types.h"

using namespace std;

//lexer type definitions

unordered_map<string, tokentype> keyword_names = { //used to tell type of keyword
    {"keyword", tokentype::keyword},
    {"identifier", tokentype::identifier},
    {"literal", tokentype::literal},
    {"op", tokentype:: op},
    {"punctuation", tokentype::punctuation},
    {"eof", tokentype::eof}
};

unordered_map<int, unordered_map<string, tokentype>> keyword_list = {}; //initialise through text file

