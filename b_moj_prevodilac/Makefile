prevodilac: lex.yy.o parser.tab.o ast.o
	clang++ -Wall $^ -o $@
lex.yy.o: lex.yy.c
	clang++ -Wall -c $< -Wno-deprecated
lex.yy.c: lexer.lex parser.tab.hpp ast.hpp
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp ast.hpp
	clang++ -Wall -c $< -Wno-deprecated
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $^
ast.o: ast.cpp ast.hpp
	clang++ -Wall -c $< 
	
.PHONY: clean
clean:
	rm prevodilac *.tab.* *.output *.c *.o
