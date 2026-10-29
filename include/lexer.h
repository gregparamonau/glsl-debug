#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include "types.h"

using namespace std;

vector<token> tokenize(string filename);
void initialise_token_list(string filename);
void print_tokens(vector<token> toks);


#endif