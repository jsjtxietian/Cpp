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


namespace Lexer
{
	using namespace std;
	
	enum Token_value
	{
	NAME,      NUMBER,     END,
	PLUS='+',  MINUS='-',  MUL='*',DIV='/',
	PRINT=';', ASSIGN='=', LP='(', RP=')'
	}; 
	Token_value curr_tok;
	double number_value;
	std::string string_value;
	
	Token_value get_token();
};

namespace Error
{
	using namespace std;
	
	struct Zero_divide{ };
	struct Syntax_error
	{
		const char *p;
		Syntax_error(const char *q) { p=q;}
	};
}

namespace Parser
{
	double expr(bool get);
	double term(bool get);
	double prim(bool get);
	
	using namespace  Lexer;
	using namespace Error;
	using namespace std;
} 


namespace Driver
{
	using namespace std;
	
	int no_of_errors;
	std::istream* input;
	void skip();
}

std::map<std::string,double> table;


int main(int argc,char *argv[])
{
	using namespace Driver;
	using namespace Lexer;
	using namespace Parser;
	
	switch(argc)//������� 
	{
		case 1:
			Driver::input=&cin;
			break;
		case 2:
			input=new istringstream(argv[1]);
			break;
		default:
			throw Error::Syntax_error("too many arguments");
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

double Parser::expr(bool get)
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

double Parser::term(bool get)
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

double Parser::prim(bool get)
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

Lexer::Token_value Lexer::get_token()
{
	char ch;
	
	do
	{
		if(!(*Driver::input).get(ch))
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
			(*Driver::input).putback(ch);
			(*Driver::input)>>number_value;
			return curr_tok=NUMBER;
		default:
			if(isalpha(ch))
			{
				string_value=ch;
				while((*Driver::input).get(ch) && isalnum(ch))
				   string_value.push_back(ch);
				(*Driver::input).putback(ch);
				return curr_tok=NAME;
			}
			throw Error::Syntax_error("bad token"); 
	}
}

void Driver::skip()
{
	no_of_errors++;
	
	while(*input)
	{
		char ch;//����һЩ�ַ�
		input->get(ch);
		
		switch(ch)
		{
			case '\n':
			case ':':
				return ;
		} 
	}
}
