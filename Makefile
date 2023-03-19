CXX=clang++

cpu.o: cpu.cpp
	${CXX} -c cpu.cpp

os.o: os.cpp
	${CXX} -c os.cpp

out: os.o cpu.o
	${CXX} os.o cpu.o -o out

run: out
	./out example_input/instructions.txt

clean: 
	/bin/rm -f *.o out
	clear