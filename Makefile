top: run

run: main.exe
	./main.exe

main.exe: main.o lexer.o
	g++ $^ -l stdc++ -o $@

main.o: main.cpp lexer.h
	g++ -Wall -Werror $< -c -o $@

lexer.o: lexer.cpp lexer.h
	g++ -Wall -Werror $< -c -o $@
