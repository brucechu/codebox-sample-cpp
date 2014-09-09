all: build run

build:
	g++ main.cpp -o sample

run:
	./sample

clean:
	rm -f *.o hello