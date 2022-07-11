
output: main.o easyFiles.o
	g++ main.o easyFiles.o -o fileShare -l stdc++fs


main.o: src/main.cpp
	g++ -c src/main.cpp

easyFiles.o: src/easyFiles.cpp include/easyFiles.h
	g++ -c src/easyFiles.cpp include/easyFiles.h

clean:
	rm *.o *.out include/*.h.gch fileShare