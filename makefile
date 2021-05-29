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
	
Nast:
	hpp2plantuml  -i ObjectScene.h -i Constants.h -i Controller.h -i DrawScene.h -o anastasiia.puml 
	
		#-i Object.h
Mat:
	hpp2plantuml  -i AI.h -i Client.h -i Constants.h -i Post.h -i Server.h -o matvey.puml 
