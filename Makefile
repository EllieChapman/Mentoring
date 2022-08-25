top: run

run: main.exe
	./main.exe

main.exe: main.o
	g++ $^ -l stdc++ -o $@

main.o: main.cpp
	g++ -Wall -Werror $< -c -o $@
