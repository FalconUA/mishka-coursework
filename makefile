all:
	g++ -O2 source.cpp -o perm

debug:
	g++ source.cpp -DDEBUG -o perm_debug

clean:
	rm perm
