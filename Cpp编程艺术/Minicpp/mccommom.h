#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <fstream> 
#include <new> 
#include <stack> 
#include <vector> 
#include <cctype> 

using namespace std;

// Common declarations used by parser.cpp, minicpp.cpp, 
// or libcpp.cpp, or by other files that you might add. 
// 
const int MAX_T_LEN = 128;   // max token length 
const int MAX_ID_LEN = 31;    // max identifier length 
const int PROG_SIZE = 10000; // max program size 
const int NUM_PARAMS = 31;    // max number of parameters 

							  // Enumeration of token types. 
enum tok_types {
	UNDEFTT, DELIMITER, IDENTIFIER,
	NUMBER, KEYWORD, TEMP, STRING, BLOCK
};

// Enumeration of internal representation of tokens. 
enum token_ireps {
	UNDEFTOK, ARG, CHAR, INT, SWITCH,
	CASE, IF, ELSE, FOR, DO, WHILE, BREAK,
	RETURN, COUT, CIN, END
};

// Enumeration of two-character operators, such as <=. 
enum double_ops { LT = 1, LE, GT, GE, EQ, NE, LS, RS, INC, DEC };

// These are the constants used when throwing a 
// syntax error exception. 
// 
// NOTE: SYNTAX is a generic error message used when 
// nothing else seems appropriate. 
enum error_msg
{
	SYNTAX, NO_EXP, NOT_VAR, DUP_VAR, DUP_FUNC,
	SEMI_EXPECTED, UNBAL_BRACES, FUNC_UNDEF,
	TYPE_EXPECTED, RET_NOCALL, PAREN_EXPECTED,
	WHILE_EXPECTED, QUOTE_EXPECTED, DIV_BY_ZERO,
	BRACE_EXPECTED, COLON_EXPECTED
};

extern char *prog;  // current location in source code 
extern char *p_buf; // points to start of program buffer 

extern char token[MAX_T_LEN + 1]; // string version of token 
extern tok_types token_type; // contains type of token 
extern token_ireps tok; // internal representation of token 

extern int ret_value; // function return value 

extern bool breakfound; // true if break encountered 

						// Exception class for Mini C++. 
class InterpExc {
	error_msg err;
public:
	InterpExc(error_msg e) { err = e; }
	error_msg get_err() { return err; }
};

// Interpreter prototypes. 
void prescan();
void decl_global();
void call();
void putback();
void decl_local();
void exec_if();
void find_eob();
void exec_for();
void exec_switch();
void get_params();
void get_args();
void exec_while();
void exec_do();
void exec_cout();
void exec_cin();
void assign_var(char *var_name, int value);
bool load_program(char *p, char *fname);
int find_var(char *s);
void interp();
void func_ret();
char *find_func(char *name);
bool is_var(char *s);
token_ireps find_var_type(char *s);

// Parser prototypes. 
void eval_exp(int &value);
void eval_exp0(int &value);
void eval_exp1(int &value);
void eval_exp2(int &value);
void eval_exp3(int &value);
void eval_exp4(int &value);
void eval_exp5(int &value);
void atom(int &value);
void sntx_err(error_msg error);
void putback();
bool isdelim(char c);
token_ireps look_up(char *s);
int find_var(char *s);
tok_types get_token();
int internal_func(char *s);
bool is_var(char *s);

// "Standard library" prototypes. 
int call_getchar();
int call_putchar();
int call_abs();
int call_rand();