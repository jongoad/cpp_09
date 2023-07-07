#include <vector>
#include <deque>
#include <iostream>
#include <utility>

#include "../src/PmergeMe.cpp"

int main (int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Usage: ./PmergeMe [sequence1] ... [sequenceN]" << std::endl;
	}
	PmergeMe<std::vector<std::pair<int,int> > > vec(argv);
	PmergeMe<std::deque<std::pair<int,int> > > deq(argv);
}