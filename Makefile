CXX=g++

main: main.o
	${CXX} main.o -o out

run: main
	./out

clean: 
	/bin/rm -f *.o out