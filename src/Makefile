SHELL=/bin/bash

all:
	g++ --std=c++0x main.cpp -o pixenity -I/usr/local/include -L/usr/local/lib $(IrrFlags) -lnoise

run:
	make all
	./pixenity &> log.txt

clean:
	rm pixenity log.txt
