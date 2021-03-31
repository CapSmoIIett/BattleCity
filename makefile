all:
	clear
	g++ -g -c main.cpp
	g++ -g -c AbstractScene.cpp
	g++ -g -c Object.cpp
	
	g++ main.o Object.o AbstractScene.o -lsfml-graphics -lsfml-window -lsfml-system
	./a.out 
	clear
