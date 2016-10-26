#include "permutation.h"
#include <vector>
#include <ostream>
#include <iostream>

class A{};

int main(){
//  Try to uncomment this line and compile to see some metaprogramming magic :D 	
//	finite::set<A> ss;

	std::vector<int> v = {1, 2, 2, 4};
	finite::set<int> s(v);

	std::cout << "a = ";
	finite::print_powerset(std::cout, s);
	std::cout << std::endl << "b = ";
	finite::print_k_sized(std::cout, s, 3);
	std::cout << std::endl << "c = ";
	finite::print_permutations(std::cout, s);
	std::cout << std::endl;

	return 0;
}
