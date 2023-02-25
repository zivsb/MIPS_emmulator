CXX=clang++

cpu.o: cpu.cpp
	${CXX} -c cpu.cpp

os.o: os.cpp
	${CXX} -c os.cpp

os: os.o cpu.o
	${CXX} os.o cpu.o -o out

run: os
	./out

clean: 
	/bin/rm -f *.o out
	clear