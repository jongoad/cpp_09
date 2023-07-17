#include <vector>
#include <deque>
#include <iostream>
#include <utility>

#include "../src/PmergeMe.cpp"

int main (int argc, char** argv) {
	//Handle improper usage
	if (argc < 2) {
		std::cerr << "Usage: ./PmergeMe [sequence1] ... [sequenceN]" << std::endl;
		return EXIT_FAILURE;
	}

	//Print pre-sorted elements
	std::cout << "Before: ";
	for (int i = 1; i < argc; ++i) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;

	//Read and parse elements into set
	std::set<int> sorted;
	for (int i = 1; i < argc; ++i) {
		long num = atol(argv[i]);
		if (num < 0 || num > INT_MAX) {
			std::cerr << "Error: input values must be between 0 and INT_MAX" << std::endl;
			return EXIT_FAILURE;
		}
		if (sorted.insert(num).second == false) {
			std::cerr << "Error: duplicate values are not allowed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	//Print sorted elements
	std::cout << "After: ";
	for (std::set<int>::iterator it = sorted.begin(); it != sorted.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	//Run algorithm with std::vector
	clock_t begin = clock();
	PmergeMe<std::vector<std::pair<int,int> > > vec(argv);
	clock_t end = clock();
	double result = (double)(end - begin);
	std::cout << "Time to process a range of " << sorted.size() << " elements with std::vector: " << result << "us" << std::endl;

	//Run algorithm with std::dequeue
	begin = clock();
	PmergeMe<std::deque<std::pair<int,int> > > deq(argv);
	end = clock();
	result = (double)(end - begin);
	std::cout << "Time to process a range " << sorted.size() << " elements with std::dequeue: " << result << "us" << std::endl;

	return EXIT_SUCCESS;
}