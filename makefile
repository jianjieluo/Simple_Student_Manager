all: Student_Manager.o main.cpp
	g++ -Wall -g -std=c++11 $^ -o Student_Manager

Student_Manager.o: Student_Manager.cpp
	g++ -Wall -g -std=c++11 $^ -c -o $@

clean:
	rm -f *.o StudentManager
