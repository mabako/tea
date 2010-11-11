all:
	g++ -o tea window.cpp main.cpp -O2 -DNDEBUG `pkg-config --cflags --libs gtk+-2.0` `curl-config --libs`
	strip tea
debug:
	g++ -Wall -g -o tea window.cpp main.cpp -DDEBUG `pkg-config --cflags --libs gtk+-2.0` `curl-config --libs`
