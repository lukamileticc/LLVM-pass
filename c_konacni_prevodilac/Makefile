CPPFLAGS=$(shell llvm-config-14 --cxxflags)
LDFLAGS=$(shell llvm-config-14 --libs --ldflags)

prevodilac: lex.yy.o parser.tab.o ast.o
	clang++ -Wall $^ -o $@  $(LDFLAGS)
lex.yy.o: lex.yy.c
	clang++ -Wall -c $< -Wno-deprecated $(CPPFLAGS) -Wno-unused-command-line-argument  -Wno-unknown-warning-option
lex.yy.c: lexer.lex parser.tab.hpp ast.hpp
	flex $<
parser.tab.o: parser.tab.cpp parser.tab.hpp ast.hpp
	clang++ -Wall -c $< -Wno-deprecated  $(CPPFLAGS) -Wno-unused-command-line-argument -Wno-unknown-warning-option
parser.tab.cpp parser.tab.hpp: parser.ypp 
	bison -d -v $^
ast.o: ast.cpp ast.hpp
	clang++ -Wall -c $<  $(CPPFLAGS) -Wno-unused-command-line-argument -Wno-unknown-warning-option
	
.PHONY: clean
clean:
	rm prevodilac *.tab.* *.output *.c *.o
