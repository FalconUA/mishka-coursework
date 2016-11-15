#ifndef __ADDITIONAL_TEMPlATE_HEADER__
#define __ADDITIONAL_TEMPLATE_HEADER__

#include <vector>
#include <bitset>
#include <ostream>

template <class number>
void print_vector(std::ostream& out, std::vector<number>& v, 
		std::string separator = ", ", std::string lbrackets = "[", std::string rbrackets = "]")
{
	out << lbrackets;
	for (typename std::vector<number>::iterator it = v.begin(); it != v.end()-1; it++)
		out << (*it) << separator;
	if (v.size() > 0)
		out << v.back();
	out << rbrackets;
}

template <class number>
void powerset_generator(std::ostream& out, std::vector<number>& s, std::vector<number>& v, 
		std::vector<bool>& bitmask, size_t k, bool first = true)
{
	if (k < s.size()){

		v.push_back(s[k]);
		bitmask[k] = true;

		if ((k == 0) || (k > 0 && s[k] != s[k-1]) || (k > 0 && s[k] == s[k-1] && bitmask[k-1])){
			if (first)
				first = false;
			else
				out << ", ";	
			print_vector(out, v);
			powerset_generator<number>(out, s, v, bitmask, k+1, false);
		}
		
		v.pop_back();
		bitmask[k] = false;

		powerset_generator<number>(out, s, v, bitmask, k+1, false);
	}
}

template <class number>
void k_sized_generator(std::ostream& out, std::vector<number>& s, std::vector<number>& v, 
		std::vector<bool>& bitmask, size_t k, size_t limit, bool first = true)
{
	if (v.size() + s.size() - k < limit)
		return ;

	if (k < s.size() && v.size() < limit){
		v.push_back(s[k]);
		bitmask[k] = true;

		if (k == 0 || (k > 0 && s[k] != s[k-1]) || (k > 0 && s[k] == s[k-1] && bitmask[k-1])){
			if (v.size() == limit){
				if (first)
					first = false;
				else
					out << ", ";
				print_vector(out, v);
			}

			k_sized_generator<number>(out, s, v, bitmask, k+1, limit, first);
		}
		
		v.pop_back();
		bitmask[k] = false;
		if (k+1 < s.size() && s[k] != s[k+1])
			k_sized_generator<number>(out, s, v, bitmask, k+1, limit, false);
	}
}

#endif
