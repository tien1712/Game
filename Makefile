all:
	g++ -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 main.cpp -o main