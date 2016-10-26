/* gcc -std=gnu++14 -O2 */

#ifndef __PERMUTATIONS_H__
#define __PERMUTATIONS_H__

// if not defined in compilation parameters 
#ifndef __CRITICAL_SET_SIZE__ 
	// Check windows
	#if _WIN32 || _WIN64
	#if _WIN64
		#define __CRITICAL_SET_SIZE__ 64
	#else
		#define __CRITICAL_SET_SIZE__ 32
	#endif
	#endif

	// Check GCC
	#if __GNUC__
	#if __x86_64__ || __ppc64__
		#define __CRITICAL_SET_SIZE__ 64
	#else
		#define __CRITICAL_SET_SIZE__ 32
	#endif
	#endif
#endif

#include <vector>
#include <ostream>
#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "additional.h"


namespace finite {
	template <class number> class set;
	template <class number> void print_powerset(std::ostream& out, set<number>& s);	
	template <class number> void print_k_sized(std::ostream& out, set<number>& s, size_t limit);
	template <class number> void print_permutations(std::ostream& out, set<number>& s);

	template <class number> 
	void printexclude_powerset(std::ostream& out, set<number>& s, 
			const std::vector<set<number>&>& excluding);
	template <class number>
	void printexclude_k_sized(std::ostream& out, set<number>& s, size_t limit, 
			const std::vector<set<number>&>& excluding);
	template <class number>
	void printexclude_permutations(std::ostream& out, set<number>& s, 
			const std::vector<set<number>&>& excluding);

	template <class number>
	class set {
	private: 
		std::vector<number> container;
	public:
		set();
		set(const set& s);
		set(const std::vector<number>& elements);

		void add_element(const number& element);
		bool contains(set& s);
		bool contains(number element);
		void exclude(set& s);

		friend void print_powerset<number>(std::ostream& out, set& s);
		friend void print_k_sized<number>(std::ostream& out, set& s, size_t limit);
		friend void print_permutations<number>(std::ostream& out, set& s);

		friend void printexclude_powerset<number>(std::ostream& out, set& s, 
			const std::vector<set<number>&>& excluding);
		friend void printexclude_k_sized<number>(std::ostream& out, set<number>& s, size_t limit, 
			const std::vector<set<number>&>& excluding);
		friend void printexclude_permutations<number>(std::ostream& out, set<number>& s, 
			const std::vector<set<number>&>& excluding);

	};

};

template <class number>
finite::set<number>::set() {}

template <class number>
finite::set<number>::set(const std::vector<number>& elements): container(elements) {}

template <class number>
finite::set<number>::set(const finite::set<number>& s): container(s.container) {}

template <class number>
bool finite::set<number>::contains(number element){
	return (std::find(this->container.begin(), this->container.end(), element));
}

template <class number>
bool finite::set<number>::contains(set<number>& s){
	bool answer = true;
	for (typename std::vector<number>::iterator it = s.container.begin(); 
			it != s.container.end(); it++)
		answer = answer && this->contains(*it);
	return answer;
}

template <class number>
void finite::set<number>::exclude(set<number>& s){
	std::vector<number> v;
	for (typename std::vector<number>::iterator it = this->container.begin(); 
			it != this->container.end(); it++)
	if (!s.contains(*it))
		v.push_back(*it);
	this->container = v;
}





template <class number>
void finite::set<number>::add_element(const number& element) {
	this->container.push_back(element);
}

template <class number>
void finite::print_powerset(std::ostream& out, finite::set<number>& s) {
	std::sort(s.container.begin(), s.container.end());
	std::vector<number> v;

	out << "[[], ";
	powerset_generator(out, s.container, v, 0);
	out << "]";
}

template <class number>
void finite::print_k_sized(std::ostream& out, finite::set<number>& s, size_t limit){
	std::sort(s.container.begin(), s.container.end());
	std::vector<number> v;

	out << "[";
	if (limit == 0 || limit > s.container.size())
		out << "[]";
	else
		k_sized_generator(out, s.container, v, 0, limit);
	out << "]";
}

template <class number>
void finite::print_permutations(std::ostream& out, finite::set<number>& s){
	std::sort(s.container.begin(), s.container.end());
	std::vector<number> v(s.container);

	out << "[";
	print_vector(out, v);	
	while (std::next_permutation(v.begin(), v.end())) {
		out << ", ";
		print_vector(out, v);
	}
	out << "]";
}

template <class number> 
void finite::printexclude_powerset(std::ostream& out, finite::set<number>& s, 
		std::vector<finite::set<number>&>& excluding)
{
	finite::set<number> a(s);
	for (typename std::vector<finite::set<number>&>::iterator it = excluding.begin();
			it != excluding.end(); it++)
		a.exclude(*it);
	finite::print_powerset(out, a);
}

template <class number>
void printexclude_k_sized(std::ostream& out, finite::set<number>& s, size_t limit, 
		std::vector<finite::set<number>&>& excluding)
{
	finite::set<number> a(s);
	for (typename std::vector<finite::set<number>&>::iterator it = excluding.begin();
			it != excluding.end(); it++)
		a.exclude(*it);
	finite::print_k_sized(out, a, limit);
}

template <class number>
void printexclude_permutations(std::ostream& out, finite::set<number>& s, 
		std::vector<finite::set<number>&>& excluding)
{
	finite::set<number> a(s);
	for (typename std::vector<finite::set<number>&>::iterator it = excluding.begin();
			it != excluding.end(); it++)
		a.exclude(*it);
	finite::print_permutations(out, a);
}




#endif
