#include "../include/PmergeMe.hpp"

template <class T>
PmergeMe<T>::PmergeMe() {}

template <class T>
PmergeMe<T>::PmergeMe(char** input) {
	if (!parseInput(input)) {
		std::cerr << "Error" << std::endl;
		return;
	}
	// printContainer();

	//Check for odd number of elements
	if (container_.size() % 2 == 1) {
		oddOneOut_ = container_.back();
		container_.pop_back();
		isOdd = true;
	} else {
		isOdd = false;
	}

	//Create pairs
	createPairs();

	//Sort pairs internally

	//Sort pairs externally

}

template <class T>
PmergeMe<T>::PmergeMe(const PmergeMe& other) {
	*this = other;
}

template <class T>
PmergeMe<T>::~PmergeMe() {

}

template <class T>
const PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe<T>& rhs) {

}

template <class T>
bool PmergeMe<T>::parseInput(char **input) {
	int i = 1;
	while (input[i]) {
		long res = std::atol(input[i]);
		if (res < 0 || res > INT_MAX) {
			return false;
		}
		container_.push_back(std::make_pair(res, 0));
		i++;
	}
	return true;
}

template<class T>
void PmergeMe<T>::printContainer(void) {
	typename T::iterator it = container_.begin();

	for (; it != container_.end(); ++it) {
		std::cout << it->first << " ";
	}
	std::cout << std::endl;
}

template<class T>
void PmergeMe<T>::mergeInsertSort() {

}

template<class T>
void PmergeMe<T>::createPairs(void) {
	int i = 0;

	int val1, val2;
	for (; i < container_.size() - 1; ++i) {
		sorted_.push_back(std::make_pair(container_[i], container_[i + 1]));
	}
}

template<class T>
void PmergeMe<T>::sortPairsInternal(void) {
	int temp;
	T::iterator it = sorted_.begin();
	
	for (; it != sorted_.end(); ++it) {
		if (it->first < it->second) {
			temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}



/*
1. Count the number of elements in sequence
2. If number is odd, keep the last value seperate and sort in at end
3. Divide the sequence into N/2 pairs and place into container (pairs_)
4. Recursively sort the pairs based on their highest value.
5. Push all of the sorted (largest) values from each pair into a new container (sorted_) in ascending order
6. Push the smaller value from the first pair at the start of the new container (sorted_)
7. Iterate trough the remaining pairs and insert values into sorted_
8. If there were an odd number of elements insert the remaining element.
*/