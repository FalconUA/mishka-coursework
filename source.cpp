#include "permutation.h"
#include <vector>
#include <ostream>
#include <iostream>

class A{};

#ifdef DEBUG
int main(){
//  Try to uncomment this line and compile to see some metaprogramming magic :D 	
	dm::set<A> ss;

	std::vector<int> v = {1, 2, 2, 4};
	dm::set<int> s(v);

	std::cout << "a = ";
	dm::print_powerset(std::cout, s);
	std::cout << std::endl << "b = ";
	dm::print_k_sized(std::cout, s, 3);
	std::cout << std::endl << "c = ";
	dm::print_permutations(std::cout, s);
	std::cout << std::endl;

	return 0;
}
#else
int main(){
	std::vector<int> v;

	size_t n;
	std::cout << "Input the quantity of elements in the set: ";
	std::cin >> n;
	v.resize(n);
	std::cout << "Input " << n << " elements, separated by space: ";
	for (int i=0; i<n; i++)
		std::cin >> v[i];	
	std::cout << std::endl;

	dm::set<int> s(v);
	std::cout << std::endl << "1 - Powerset: ";
	dm::print_powerset(std::cout, s);
	std::cout << std::endl << "2 - k-sized sets.";
    std::cout << "Please enter the number k: ";
	int k;
	std::cin >> k;
	dm::print_k_sized(std::cout, s, k);
	std::cout << std::endl << "3 - All permutations:" << std::endl;
	dm::print_permutations(std::cout, s);
	std::cout << std::endl << "4 - Do the same operations (1-3), excluding the elements in the collection of sets Si, i in 0..m";
	std::cout << std::endl << "Please enter the quantity of excluding sets: ";
	int m;
	std::cin >> m;
	std::vector<dm::set<int>> e;

	for (int i=0; i<m; i++){
		std::vector<int> vi;
		int h;
		std::cout << "Enter the size of S" << i+1 << ": ";
		std::cin >> h;
		vi.resize(h);
		std::cout << "Enter the elements of S" << i+1 << ", separated by space: ";
		for (int j=0; j < h; j++)
			std::cin >> vi[j]; 
		dm::set<int> si(vi);
		e.push_back(si);
	}
	std::cout << std::endl << "1' - Powerset without the unity of Si: ";
	dm::printexclude_powerset(std::cout, s, e);	
	std::cout << std::endl << "2' - k-sized sets without the unity of Si: ";
	dm::printexclude_k_sized(std::cout, s, k, e);
	std::cout << std::endl << "3' - All permutations without the unity of Si: ";
	dm::printexclude_permutations(std::cout, s, e);
	std::cout << std::endl;
}
#endif
