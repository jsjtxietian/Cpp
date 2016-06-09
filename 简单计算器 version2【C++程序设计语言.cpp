/* 
program:
	END
	expr_list END
expr_list:
	expression PRINT
	expression PRINT exper_list
expression
	expression + term
	expression - term
	term
term:
	term / primary
	term * primary
	primary
primary
	NUMBER
	NAME
	NAME = expression
	-primary
	(expression)
*/ 
#include<iostream>
#include<string>
#include<map>
#include<cctype>
#include<sstream>

using namespace std;

enum Token_value
{
	NAME,      NUMBER,     END,
	PLUS='+',  MINUS='-',  MUL='*',DIV='/',
	PRINT=';', ASSIGN='=', LP='(', RP=')'
}; 

struct Zero_divide{ };
struct Syntax_error
{
	const char *p;
	Syntax_error(const char *q) { p=q;}
};

map<string,double> table;

Token_value curr_tok=PRINT;
double number_value;
string string_value;
istream* input;
int no_of_errors;

double expr(bool get);
double term(bool get);
double prim(bool get);
Token_value get_token();
void skip();

int main(int argc,char *argv[])
{
	switch(argc)//输入控制 
	{
		case 1:
			input=&cin;
			break;
		case 2:
			input=new istringstream(argv[1]);
			break;
		default:
			throw Syntax_error("too many arguments");
			return 1;
	}
	
	
	table["pi"]=3.14159;
	table["e"]=2.71828;
	
	while(*input)
	{
		try
		{
			get_token();
			if(curr_tok==END)
			  break;
			if(curr_tok==PRINT)
			  continue;
			cout<< "result: "<<expr(false) << '\n';
		}
		catch(Zero_divide)
		{
			cerr<<"attempt to divide by zero\n";
			if(curr_tok!=PRINT)  skip();
		}
		catch(Syntax_error e)
		{
			cerr<<"Syntax error :" << e.p << '\n';
			if(curr_tok!=PRINT) skip();
		}
	} 
	if(input!=&cin)
	   delete input;
	
	return no_of_errors;
}

double expr(bool get)
{
	double left=term(get);
	
	for(;;)
	{
		switch(curr_tok)
		{
			case PLUS:
				left+=term(true);
				break;
			case MINUS:
				left-=term(true);
				break;
			default:
				return left;
		}
	}
}

double term(bool get)
{
	double left=prim(get);
	
	for(;;)
	{
		switch(curr_tok)
		{
			case MUL:
				left*=term(true);
				break;
			case DIV:
				if(double d=prim(true))
				{
					left/=d;
					break;
				}
				throw Zero_divide();

			default:
				return left;
		}
	}
} 

double prim(bool get)
{
	if(get) get_token();
	switch(curr_tok)
	{
		case NUMBER:
		{
			double v=number_value;
			get_token();
			return v; 
		}
		case NAME:
		{
			double &v=table[string_value];
			if(get_token()==ASSIGN)
			  v=expr(true);
			return v;
		}
		case MINUS:
			return -prim(true);
		case LP:
		{
			double e=expr(true);
			if(curr_tok!=RP)
			  throw Syntax_error("')'expected!");
			get_token();
			return e;
		}
		default :
			throw Syntax_error("primary expected");
	}
}

Token_value get_token()
{
	char ch;
	
	do
	{
		if(!(*input).get(ch))
		   return curr_tok=END;
	}while(ch!='\n' && isspace(ch));
	
	switch(ch)
	{
		case ';':
		case '\n':
			return curr_tok=PRINT;
		case '*':
		case '/':
		case '+':
		case '-':
		case '(':
		case ')':
		case '=':
			return curr_tok=Token_value(ch);
		case '1':case '2':case '3':case '4':case '5':
		case '6':case '7':case '8':case '9':case '0':
		case '.':
			(*input).putback(ch);
			(*input)>>number_value;
			return curr_tok=NUMBER;
		default:
			if(isalpha(ch))
			{
				string_value=ch;
				while((*input).get(ch) && isalnum(ch))
				   string_value.push_back(ch);
				(*input).putback(ch);
				return curr_tok=NAME;
			}
			throw Syntax_error("bad token"); 
	}
}

void skip()
{
	no_of_errors++;
	
	while(*input)
	{
		char ch;//丢掉一些字符
		input->get(ch);
		
		switch(ch)
		{
			case '\n':
			case ':':
				return ;
		} 
	}
}
