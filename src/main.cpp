#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"

using namespace std;

string filename = "res/red.frag";
string tokens_file = "res/tokens.txt";

int main() {
    initialise_token_list(tokens_file);

    vector<token> temp = tokenize(filename);

    print_tokens(temp);

    return 0;
}