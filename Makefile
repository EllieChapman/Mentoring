top: run

run: main.exe
	./main.exe

main.exe: main.o lexer.o parser.o
	g++ $^ -l stdc++ -o $@

main.o: main.cpp lexer.h ast.h parser.h
	g++ -Wall -Werror $< -c -o $@

lexer.o: lexer.cpp lexer.h
	g++ -Wall -Werror $< -c -o $@

parser.o: parser.cpp parser.h lexer.h ast.h # ebc was it correct to add lexer.h here?
	g++ -Wall -Werror $< -c -o $@