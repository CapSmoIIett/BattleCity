all:
	clear
	g++ -g -c main.cpp
	g++ -g -c ObjectScene.cpp
	g++ -g -c Object.cpp
	g++ -g -c DrawScene.cpp
	g++ -g -c Controller.cpp
	g++ -g -c AI.cpp
	g++ -g -c Server.cpp
	g++ -g -c Client.cpp
	g++ -g -c Posts.cpp
	
	g++ -g *.o -lsfml-graphics -lsfml-window -lsfml-system -pthread	
	./a.out 
	#clear
