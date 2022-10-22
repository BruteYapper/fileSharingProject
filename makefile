
output: main.o easyFiles.o easyScreens.o fileTransfer.o
	g++ main.o easyFiles.o easyScreens.o fileTransfer.o -o fileShare -std=c++17 -lncurses


main.o: src/main.cpp
	g++ -c src/main.cpp -std=c++17 -lncurses

easyFiles.o: src/easyFiles.cpp include/easyFiles.h
	g++ -c src/easyFiles.cpp include/easyFiles.h -std=c++17

easyScreens.o: src/easyScreens.cpp include/easyScreens.h
	g++ -c src/easyScreens.cpp include/easyScreens.h -std=c++17 -lncurses

fileTransfer.o: src/fileTransfer.cpp include/fileTransfer.h
	g++ -c src/fileTransfer.cpp include/fileTransfer.h -std=c++17 -lncurses

clean:
	rm *.o *.out include/*.h.gch fileShare