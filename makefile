all:
	clear
	g++ -g -c main.cpp
	g++ -g -c AbstractScene.cpp
	g++ -g -c Object.cpp
	g++ -g -c DrawScene.cpp
	
	g++ -g main.o Object.o AbstractScene.o DrawScene.o -lsfml-graphics -lsfml-window -lsfml-system
	./a.out 
	clear
