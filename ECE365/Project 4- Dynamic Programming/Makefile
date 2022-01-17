main.exe: main.o 
	g++ -o main.exe main.o

main.o: main.cpp
	g++ -c main.cpp

debug:
	g++ -g -o main.exe main.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups