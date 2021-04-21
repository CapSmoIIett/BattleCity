all:
	clear
	g++ -g -c main.cpp
	g++ -g -c ObjectScene.cpp
	g++ -g -c Object.cpp
	g++ -g -c DrawScene.cpp
	g++ -g -c Controller.cpp
	g++ -g -c AI.cpp
	
	g++ -g main.o Object.o ObjectScene.o DrawScene.o Controller.o AI.o -lsfml-graphics -lsfml-window -lsfml-system -pthread	
	./a.out 
	#clear
