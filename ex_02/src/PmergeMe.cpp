#include "../include/PmergeMe.hpp"

template <class T>
PmergeMe<T>::PmergeMe() {}

template <class T>
PmergeMe<T>::PmergeMe(char** input) {
	if (!parseInput(input)) {
		std::cerr << "Error" << std::endl;
		return;
	}
	printContainer();
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
		container_.push_back(res);
		i++;
	}
	return true;
}

template<class T>
void PmergeMe<T>::printContainer(void) {
	typename T::iterator it = container_.begin();

	for (; it != container_.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}