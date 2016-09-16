// Recursive descent parser for integer expressions

#include "mccommom.h"

// Keyword lookup table. 
// Keywords must be entered lowercase. 
struct commands
{
	char command[20];
	token_ireps tok;
} com_table[] =
{
	"if", IF,
	"else", ELSE,
	"for", FOR,
	"do", DO,
	"while", WHILE,
	"char", CHAR,
	"int", INT,
	"return", RETURN,
	"switch", SWITCH,
	"break", BREAK,
	"case", CASE,
	"cout", COUT,
	"cin", CIN,
	 "", END   // mark end of table 
};

// This structure links a library function name 
// with a pointer to that function. 

struct tern_func_type
{
	char *f_name; // function name 
	int(*p)();	// pointer to the function
} intern_func[] = 
{
	"getchar", call_getchar,
	"putchar", call_putchar,
	"abs", call_abs,
	"rand", call_rand,
	"", 0	// null terminate the list 
};

void eval_exp(int &value)
{
	get_token();

	if(!*token)
	{
		throw InterpExc(NO_EXP);
	}

	if (*token == ';')
	{
		value = 0;
		return;
	}

	eval_exp0(value);

	putback();
}

void eval_exp0(int &value)
{
	char temp[MAX_ID_LEN + 1];

	tok_types temp_tok;

	if (token_type == IDENTIFIER) 
	{
		if (is_var(token)) 
		{
			strcpy(temp, token);
			temp_tok = token_type;
			get_token();
			if (*token == '=') 
			{ 
				get_token();
				eval_exp0(value); 
				assign_var(temp, value); 
				return;
			}
			else 
			{ 
				putback(); 
				strcpy(token, temp);
				token_type = temp_tok;
			}
		}
	}
	eval_exp1(value);
}

// Process relational operators. 
void eval_exp1(int &value)
{
	int partial_value;
	char op;
	char relops[] = {
		LT, LE, GT, GE, EQ, NE, 0
	};

	eval_exp2(value);

	op = *token;
	if (strchr(relops, op)) {
		get_token();
		eval_exp2(partial_value);

		switch (op) { // perform the relational operation 
		case LT:
			value = value < partial_value;
			break;
		case LE:
			value = value <= partial_value;
			break;
		case GT:
			value = value > partial_value;
			break;
		case GE:
			value = value >= partial_value;
			break;
		case EQ:
			value = value == partial_value;
			break;
		case NE:
			value = value != partial_value;
			break;
		}
	}
}

// Add or subtract two terms. 
void eval_exp2(int &value)
{
	char  op;
	int partial_value;
	char okops[] = {
		'(', INC, DEC, '-', '+', 0
	};

	eval_exp3(value);

	while ((op = *token) == '+' || op == '-') {
		get_token();

		if (token_type == DELIMITER &&
			!strchr(okops, *token))
			throw InterpExc(SYNTAX);

		eval_exp3(partial_value);

		switch (op) { // add or subtract 
		case '-':
			value = value - partial_value;
			break;
		case '+':
			value = value + partial_value;
			break;
		}
	}
}

// Multiply or divide two factors. 
void eval_exp3(int &value)
{
	char  op;
	int partial_value, t;
	char okops[] = {
		'(', INC, DEC, '-', '+', 0
	};

	eval_exp4(value);

	while ((op = *token) == '*' || op == '/'
		|| op == '%') {
		get_token();

		if (token_type == DELIMITER &&
			!strchr(okops, *token))
			throw InterpExc(SYNTAX);

		eval_exp4(partial_value);

		switch (op) { // mul, div, or modulus 
		case '*':
			value = value * partial_value;
			break;
		case '/':
			if (partial_value == 0)
				throw InterpExc(DIV_BY_ZERO);
			value = (value) / partial_value;
			break;
		case '%':
			t = (value) / partial_value;
			value = value - (t * partial_value);
			break;
		}
	}
}

// Is a unary +, -, ++, or --. 
void eval_exp4(int &value)
{
	char  op;
	char temp;

	op = '\0';
	if (*token == '+' || *token == '-' ||
		*token == INC || *token == DEC)
	{
		temp = *token;
		op = *token;
		get_token();
		if (temp == INC)
			assign_var(token, find_var(token) + 1);
		if (temp == DEC)
			assign_var(token, find_var(token) - 1);
	}

	eval_exp5(value);
	if (op == '-') value = -(value);
}

// Process parenthesized expression. 
void eval_exp5(int &value)
{

	if ((*token == '(')) {
		get_token();

		eval_exp0(value); // get subexpression 

		if (*token != ')')
			throw InterpExc(PAREN_EXPECTED);
		get_token();
	}
	else
		atom(value);
}

void atom(int &value)
{
	int i;
	char temp[MAX_ID_LEN + 1];

	switch (token_type) {
	case IDENTIFIER:
		i = internal_func(token);
		if (i != -1) {
			// Call "standard library" function. 
			value = (*intern_func[i].p)();
		}
		else if (find_func(token)) {
			// Call programmer-created function. 
			call();
			value = ret_value;
		}
		else {
			value = find_var(token); // get var's value 
			strcpy(temp, token); // save variable name 

								 // Check for ++ or --. 
			get_token();
			if (*token == INC || *token == DEC) {
				if (*token == INC)
					assign_var(temp, find_var(temp) + 1);
				else
					assign_var(temp, find_var(temp) - 1);
			}
			else putback();
		}

		get_token();
		return;
	case NUMBER: // is numeric constant 
		value = atoi(token);
		get_token();

		return;
	case DELIMITER: // see if character constant 
		if (*token == '\'') {
			value = *prog;
			prog++;
			if (*prog != '\'')
				throw InterpExc(QUOTE_EXPECTED);

			prog++;
			get_token();

			return;
		}
		if (*token == ')') return; // process empty expression 
		else throw InterpExc(SYNTAX);  // otherwise, syntax error 
	default:
		throw InterpExc(SYNTAX); // syntax error 
	}
}

// Display an error message. 
void sntx_err(error_msg error)
{
	char *p, *temp;
	int linecount = 0;

	static char *e[] = {
		"Syntax error",
		"No expression present",
		"Not a variable",
		"Duplicate variable name",
		"Duplicate function name",
		"Semicolon expected",
		"Unbalanced braces",
		"Function undefined",
		"Type specifier expected",
		"Return without call",
		"Parentheses expected",
		"While expected",
		"Closing quote expected",
		"Division by zero",
		"{ expected (control statements must use blocks)",
		"Colon expected"
	};

	// Display error and line number. 
	cout << "\n" << e[error];
	p = p_buf;
	while (p != prog) { // find line number of error 
		p++;
		if (*p == '\r') {
			linecount++;
		}
	}
	cout << " in line " << linecount << endl;

	temp = p;
	while (p > p_buf && *p != '\n') p--;

	// Display offending line. 
	while (p <= temp)
		cout << *p++;

	cout << endl;
}

// Get a token. 
tok_types get_token()
{

	char *temp;

	token_type = UNDEFTT; tok = UNDEFTOK;

	temp = token;
	*temp = '\0';

	// Skip over white space. 
	while (isspace(*prog) && *prog) ++prog;

	// Skip over newline. 
	while (*prog == '\r') {
		++prog;
		++prog;
		// Again, skip over white space. 
		while (isspace(*prog) && *prog) ++prog;
	}

	// Check for end of program. 
	if (*prog == '\0') {
		*token = '\0';
		tok = END;
		return (token_type = DELIMITER);
	}

	// Check for block delimiters. 
	if (strchr("{}", *prog)) {
		*temp = *prog;
		temp++;
		*temp = '\0';
		prog++;
		return (token_type = BLOCK);
	}

	// Look for comments. 
	if (*prog == '/')
		if (*(prog + 1) == '*') { // is a /* comment 
			prog += 2;
			do { // find end of comment 
				while (*prog != '*') prog++;
				prog++;
			} while (*prog != '/');
			prog++;
			return (token_type = DELIMITER);
		}
		else if (*(prog + 1) == '/') { // is a // comment 
			prog += 2;
			// Find end of comment. 
			while (*prog != '\r' && *prog != '\0') prog++;
			if (*prog == '\r') prog += 2;
			return (token_type = DELIMITER);
		}

		// Check for double-ops. 
		if (strchr("!<>=+-", *prog)) {
			switch (*prog) {
			case '=':
				if (*(prog + 1) == '=') {
					prog++; prog++;
					*temp = EQ;
					temp++; *temp = EQ; temp++;
					*temp = '\0';
				}
				break;
			case '!':
				if (*(prog + 1) == '=') {
					prog++; prog++;
					*temp = NE;
					temp++; *temp = NE; temp++;
					*temp = '\0';
				}
				break;
			case '<':
				if (*(prog + 1) == '=') {
					prog++; prog++;
					*temp = LE; temp++; *temp = LE;
				}
				else if (*(prog + 1) == '<') {
					prog++; prog++;
					*temp = LS; temp++; *temp = LS;
				}
				else {
					prog++;
					*temp = LT;
				}
				temp++;
				*temp = '\0';
				break;
			case '>':
				if (*(prog + 1) == '=') {
					prog++; prog++;
					*temp = GE; temp++; *temp = GE;
				}
				else if (*(prog + 1) == '>') {
					prog++; prog++;
					*temp = RS; temp++; *temp = RS;
				}
				else {
					prog++;
					*temp = GT;
				}
				temp++;
				*temp = '\0';
				break;
			case '+':
				if (*(prog + 1) == '+') {
					prog++; prog++;
					*temp = INC; temp++; *temp = INC;
					temp++;
					*temp = '\0';
				}
				break;
			case '-':
				if (*(prog + 1) == '-') {
					prog++; prog++;
					*temp = DEC; temp++; *temp = DEC;
					temp++;
					*temp = '\0';
				}
				break;
			}

			if (*token) return(token_type = DELIMITER);
		}

		// Check for other delimiters. 
		if (strchr("+-*^/%=;:(),'", *prog)) {
			*temp = *prog;
			prog++;
			temp++;
			*temp = '\0';
			return (token_type = DELIMITER);
		}

		// Read a quoted string. 
		if (*prog == '"') {
			prog++;
			while (*prog != '"' && *prog != '\r' && *prog) {
				// Check for \n escape sequence. 
				if (*prog == '\\') {
					if (*(prog + 1) == 'n') {
						prog++;
						*temp++ = '\n';
					}
				}
				else if ((temp - token) < MAX_T_LEN)
					*temp++ = *prog;

				prog++;
			}
			if (*prog == '\r' || *prog == 0)
				throw InterpExc(SYNTAX);
			prog++; *temp = '\0';
			return (token_type = STRING);
		}

		// Read an integer number. 
		if (isdigit(*prog)) {
			while (!isdelim(*prog)) {
				if ((temp - token) < MAX_ID_LEN)
					*temp++ = *prog;
				prog++;
			}
			*temp = '\0';
			return (token_type = NUMBER);
		}

		// Read identifier or keyword. 
		if (isalpha(*prog)) {
			while (!isdelim(*prog)) {
				if ((temp - token) < MAX_ID_LEN)
					*temp++ = *prog;
				prog++;
			}
			token_type = TEMP;
		}

		*temp = '\0';

		// Determine if token is a keyword or identifier. 
		if (token_type == TEMP) {
			tok = look_up(token); // convert to internal form 
			if (tok) token_type = KEYWORD; // is a keyword 
			else token_type = IDENTIFIER;
		}

		// Check for unidentified character in file. 
		if (token_type == UNDEFTT)
			throw InterpExc(SYNTAX);

		return token_type;
}

// Return a token to input stream. 
void putback()
{
	char *t;

	t = token;
	for (; *t; t++) prog--;
}

// Look up a token's internal representation in the 
// token table. 
token_ireps look_up(char *s)
{
	int i;
	char *p;

	// Convert to lowercase. 
	p = s;
	while (*p) { *p = tolower(*p); p++; }

	// See if token is in table. 
	for (i = 0; *com_table[i].command; i++) {
		if (!strcmp(com_table[i].command, s))
			return com_table[i].tok;
	}

	return UNDEFTOK; // unknown command 
}

// Return index of internal library function or -1 if 
// not found. 
int internal_func(char *s)
{
	int i;

	for (i = 0; intern_func[i].f_name[0]; i++) {
		if (!strcmp(intern_func[i].f_name, s))  return i;
	}
	return -1;
}

// Return true if c is a delimiter. 
bool isdelim(char c)
{
	if (strchr(" !:;,+-<>'/*%^=()", c) || c == 9 ||
		c == '\r' || c == 0) return true;
	return false;
}
