#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

//type definitions ==============================================================

//lexer
enum class tokentype {
    keyword,
    identifier,
    literal,
    op,
    punctuation,
    eof
};
struct token {
    tokentype type;
    string lexeme;
    int line;
};

//parser
enum class glsl_type {
    type_float, type_int, type_uint, type_bool, type_double,
    type_vec2, type_vec3, type_vec4,
    type_bvec2, type_bvec3, type_bvec4,
    type_ivec2, type_ivec3, type_ivec4,
    type_uvec2, type_uvec3, type_uvec4,
    type_dvec2, type_dvec3, type_dvec4,
    type_mat2, type_mat3, type_mat4,
    type_mat2x3, type_mat2x4, type_mat3x2,
    type_mat3x4, type_mat4x2, type_mat4x3,
    type_sampler2D, type_sampler3D, type_samplerCube,
    type_struct, type_void, type_array
};
enum class node_type {
    literal, variable, function_call, block,
    if_node, loop, return_node, discard_node,
    binary_op, unary_op, var_decl, function_decl,
    struct_decl, member_access, array_access, assign
};
enum class exec_result_type { normal, returned, discarded }; //results of function calls & node executions
struct glsl_struct_field {
    string name;
    glsl_type type;
    size_t size;
    string struct_type_name;
};
struct glsl_variable { //can be name-less (intermediate value) if needed 
    glsl_type type; //used in variables only, not in intermediate values
    void* data;
    size_t size;
    string name;
    string struct_type_name; //used in structs only
    unordered_map<string, glsl_variable*> fields;//used in structs only
};
struct ast_node {
    node_type type;
    string data;
    vector<ast_node*> children;
};




//global variable definitions ============================================================

//lexer
extern unordered_map<string, tokentype> keyword_names;
extern unordered_map<int, unordered_map<string, tokentype>> keyword_list;

//parser
extern unordered_map<string, vector<glsl_struct_field>> struct_definitions;
extern unordered_map<string, ast_node*> user_functions;
extern vector<string> parsing_errors;


#endif