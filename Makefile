CXX=clang++

cpu.o: cpu.cpp
	${CXX} -c cpu.cpp

main.o: main.cpp
	${CXX} -c main.cpp

main: main.o cpu.o
	${CXX} main.o cpu.o -o out

run: main
	./out

clean: 
	/bin/rm -f *.o out