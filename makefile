all:
	mkdir -p ./bin
	g++ -Wall -Werror -pedantic -ansi  ./src/rshell.cpp -o ../bin/rshell
rshell:
	mkdir -p ./bin
	g++ -Wall -Werror -pedantic -ansi  ./src/rshell.cpp -o ../bin/rshell


clean:
	rm -rf ./bin

