//builds ast from the vector<tokens> that we created in lexer.cpp

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "lexer.h" //for tokens & shi
#include "builtin.h" //for builint glsl functions like sin & dot

using namespace std;

//variables & types
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


//AST elements specifically
enum class node_type {
    literal, variable, function_call, block,
    if_node, loop, return_node, discard_node,
    binary_op, unary_op, var_decl, function_decl,
    struct_decl, member_access, array_access, assign
};

enum class exec_result_type { normal, returned, discarded };

struct ast_node {
    node_type type;
    string data;
    vector<ast_node*> children;
};

//variable tables, struct declaration tables, etc.

//struct declaration table
unordered_map<string, vector<glsl_struct_field>> struct_definitions;

unordered_map<string, ast_node*> user_functions;

vector<string> parsing_errors; //compiler errors

//currently working on rest of parser


