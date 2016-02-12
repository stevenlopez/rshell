all:
	mkdir -p ./bin
	g++ -Wall -Werror -pedantic -ansi  src/main.cpp -o bin/rshell
rshell:
	mkdir -p ./bin
	g++ -Wall -Werror -pedantic -ansi  src/main.cpp -o bin/rshell


clean:
	rm bin/rshell
	rm -rf ./bin

