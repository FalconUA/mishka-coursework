/* gcc -std=gnu++14 -O2 */

#ifndef __PERMUTATIONS_H__
#define __PERMUTATIONS_H__

#include <vector>
#include <ostream>
#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <utility>
#include "additional.h"

#define REGISTER_PARSE_TYPE(X) template <> struct TypeParseTraits<X> \
	    { static const char* name; } ; const char* TypeParseTraits<X>::name = #X

namespace __check_operator_existance {
	struct no_eq {};
	struct no_lt {};
	template <typename T, typename Arg> no_lt operator< (const T&, const Arg&);
	template <typename T, typename Arg> no_eq operator== (const T&, const Arg&); 

	template <typename T, typename Arg = T>
	struct __smaller_exists { 
		enum { value = !std::is_same<decltype(*(T*)(0) < *(Arg*)(0)), no_lt>::value };
	};
	template <typename T, typename Arg = T>
	struct __equal_exists {
		enum { value = !std::is_same<decltype(*(T*)(0) == *(Arg*)(0)), no_eq>::value };
	};
};

namespace dm {

	template <class number> class set;
	template <class number> void print_powerset(std::ostream& out, set<number>& s);	
	template <class number> void print_k_sized(std::ostream& out, set<number>& s, size_t limit);
	template <class number> void print_permutations(std::ostream& out, set<number>& s);

	template <class number> 
	void printexclude_powerset(std::ostream& out, set<number>& s, 
			const std::vector<set<number>>& excluding);
	template <class number>
	void printexclude_k_sized(std::ostream& out, set<number>& s, size_t limit, 
			const std::vector<set<number>>& excluding);
	template <class number>
	void printexclude_permutations(std::ostream& out, set<number>& s, 
			const std::vector<set<number>>& excluding);

	template <class number>
	class set {

	/* check if class "number" is a ordinal type */
	static_assert(__check_operator_existance::__equal_exists<number>::value, 
		"Class 'set' requires its template type to have an implementation of 'operator==' method.");
	static_assert(__check_operator_existance::__smaller_exists<number>::value, 
		"Class 'set' requires its template type to have an implementation of 'operator<' method.");

	/* class interface */
	private: 
		std::vector<number> container;
	public:
		set();
		set(const set& s);
		set(const std::vector<number>& elements);

		void add_element(const number& element);
		bool contains(const set& s) const;
		bool contains(number element) const;
		void exclude(const set& s);

		friend void print_powerset<number>(std::ostream& out, set& s);
		friend void print_k_sized<number>(std::ostream& out, set& s, size_t limit);
		friend void print_permutations<number>(std::ostream& out, set& s);

		friend void printexclude_powerset<number>(std::ostream& out, set& s, 
			const std::vector<set>& excluding);
		friend void printexclude_k_sized<number>(std::ostream& out, set& s, size_t limit, 
			const std::vector<set>& excluding);
		friend void printexclude_permutations<number>(std::ostream& out, set& s, 
			const std::vector<set>& excluding);

	}; // end of set class declaration
}; // end of namespace "dm"

template <class number>
dm::set<number>::set() {}

template <class number>
dm::set<number>::set(const std::vector<number>& elements): container(elements) {}

template <class number>
dm::set<number>::set(const dm::set<number>& s): container(s.container) {}

template <class number>
bool dm::set<number>::contains(number element) const {
	return (std::find(this->container.begin(), this->container.end(), element) != 
			this->container.end());
}

template <class number>
bool dm::set<number>::contains(const set<number>& s) const {
	bool answer = true;
	for (typename std::vector<number>::iterator it = s.container.begin(); 
			it != s.container.end(); it++)
		answer = answer && this->contains(*it);
	return answer;
}

template <class number>
void dm::set<number>::exclude(const set<number>& s){
	std::vector<number> v;
	for (typename std::vector<number>::iterator it = this->container.begin(); 
			it != this->container.end(); it++)
	if (!s.contains(*it))
		v.push_back(*it);
	this->container = v;
}





template <class number>
void dm::set<number>::add_element(const number& element) {
	this->container.push_back(element);
}

template <class number>
void dm::print_powerset(std::ostream& out, dm::set<number>& s) {
	std::sort(s.container.begin(), s.container.end());
	std::vector<number> v;
	std::vector<bool> bitmask(s.container.size(), false);

	out << "[[], ";
	powerset_generator(out, s.container, v, bitmask, 0);
	out << "]";
}

template <class number>
void dm::print_k_sized(std::ostream& out, dm::set<number>& s, size_t limit){
	std::sort(s.container.begin(), s.container.end());
	std::vector<number> v;
	std::vector<bool> bitmask(s.container.size(), false);

	out << "[";
	if (limit == 0 || limit > s.container.size())
		out << "[]";
	else
		k_sized_generator(out, s.container, v, bitmask, 0, limit);
	out << "]";
}

template <class number>
void dm::print_permutations(std::ostream& out, dm::set<number>& s){
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
void dm::printexclude_powerset(std::ostream& out, dm::set<number>& s, 
		const std::vector<dm::set<number>>& excluding)
{
	dm::set<number> a(s);
	for (typename std::vector<dm::set<number>>::const_iterator it = excluding.begin();
			it != excluding.end(); it++)
		a.exclude(*it);	
	dm::print_powerset(out, a);
}

template <class number>
void dm::printexclude_k_sized(std::ostream& out, dm::set<number>& s, size_t limit, 
		const std::vector<dm::set<number>>& excluding)
{
	dm::set<number> a(s);
	for (typename std::vector<dm::set<number>>::const_iterator it = excluding.begin();
			it != excluding.end(); it++)
		a.exclude(*it);
	dm::print_k_sized(out, a, limit);
}

template <class number>
void dm::printexclude_permutations(std::ostream& out, dm::set<number>& s, 
		const std::vector<dm::set<number>>& excluding)
{
	dm::set<number> a(s);
	for (typename std::vector<dm::set<number>>::const_iterator it = excluding.begin();
			it != excluding.end(); it++)
		a.exclude(*it);
	dm::print_permutations(out, a);
}




#endif
