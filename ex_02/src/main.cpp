#include <vector>
#include <deque>
#include <iostream>
#include "../include/PmergeMe.hpp"

int main (int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Usage: ./PmergeMe [sequence1] ... [sequenceN]" << std::endl;
	}
	PmergeMe<std::vector<int> > vec(argv);
	PmergeMe<std::deque<int> > deq(argv);
}