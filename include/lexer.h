#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

using namespace std;

struct token{};
vector<token> tokenize(string filename);
void initialise_token_list(string filename);
void print_tokens(vector<token> toks);


#endif