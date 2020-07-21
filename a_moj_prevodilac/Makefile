prevodilac: lex.yy.o parser.tab.o
	clang++ -Wall $^ -o $@
lex.yy.o: lex.yy.c
	clang++ -Wall -c $< 
lex.yy.c: lexer.lex parser.tab.hpp
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp
	clang++ -Wall -c $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $^
	
.PHONY: clean
clean:
	rm prevodilac *.tab.* *.output *.c *.o
