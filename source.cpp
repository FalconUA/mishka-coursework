#include "permutation.h"
#include <vector>
#include <ostream>
#include <iostream>

int main(){
	std::vector<int> v = {1, 2, 2, 4};
	finite::set<int> s(v);

	finite::print_powerset(std::cout, s);
	std::cout << std::endl;
	finite::print_k_sized(std::cout, s, 3);
	std::cout << std::endl;
	finite::print_permutations(std::cout, s);
	std::cout << std::endl;
	return 0;
}
