all:
	g++ -std=c++11 -O2 source.cpp -o perm

debug:
	g++ -std=c++11 source.cpp -DDEBUG -o perm_debug

clean:
	rm perm perm_debug &> /dev/null
