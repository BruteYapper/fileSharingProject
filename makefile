
output: main.o easyFiles.o
	g++ main.o easyFiles.o -o fileShare -l stdc++fs -std=c++17


main.o: src/main.cpp
	g++ -c src/main.cpp -std=c++17

easyFiles.o: src/easyFiles.cpp include/easyFiles.h
	g++ -c src/easyFiles.cpp include/easyFiles.h -std=c++17

clean:
	rm *.o *.out include/*.h.gch fileShare