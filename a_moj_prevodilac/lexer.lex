%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>

using namespace std;
#include "parser.tab.hpp"

%}

%%
"begin" return begin_token;
"end"   return end_token;
"function" return function_token;
"print"   return print_token;
":=" 	return dodela_token;

[/][/]. { //ovo ignorisemo jer predstavljamo komentare na taj nacin
}

[a-zA-z][a-zA-z_0-9]* {
	return id_token;
}

-?[1-9][0-9]* {
	return num_token;
}

[-;,.+*/():] {
	return *yytext;
}

[ \t\n] {}

. {
	cerr << "Leksicka greska.Ne prepoznat karakter " << *yytext << endl;
	exit(EXIT_FAILURE);
}
%%
