#include "../include/PmergeMe.hpp"

template <class T>
PmergeMe<T>::PmergeMe() {}

template <class T>
PmergeMe<T>::PmergeMe(char** input) {
	if (!parseInput(input)) {
		std::cerr << "Error" << std::endl;
		return;
	}

	std::cout << "Before: ";
	printContainer();
	mergeInsertSort();
	std::cout << "After: ";
	printContainer();
}

template <class T>
PmergeMe<T>::PmergeMe(const PmergeMe& other) {
	*this = other;
}

template <class T>
PmergeMe<T>::~PmergeMe() {
	container_.clear();
}

template <class T>
const PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe<T>& rhs) {
	if (this != &rhs) {
		container_ = rhs.container_;
	}
	return *this;
}

template <class T>
bool PmergeMe<T>::parseInput(char **input) {
	int i = 1;
	while (input[i]) {
		long res = std::atol(input[i]);
		if (res < 0 || res > INT_MAX) {
			return false;
		}
		container_.push_back(std::make_pair(res, res));
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
	mergeInsertSortHelper(0, container_.size() - 1);
}

template <class T>
void PmergeMe<T>::mergeInsertSortHelper(int left, int right) {
    if (left < right) {
      int mid = left + (right - left) / 2;

      mergeInsertSortHelper(left, mid);
      mergeInsertSortHelper(mid + 1, right);
      merge(left, mid, right);
    }
}

template <class T>
void PmergeMe<T>::merge(int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<std::pair<int, int> > leftArr(n1);
	std::vector<std::pair<int, int> > rightArr(n2);

	for (int i = 0; i < n1; ++i) {
		leftArr[i] = container_[left + i];
	}

	for (int j = 0; j < n2; ++j) {
		rightArr[j] = container_[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (leftArr[i].first <= rightArr[j].first) {
		container_[k] = leftArr[i];
		++i;
		} else {
		container_[k] = rightArr[j];
		++j;
		}
		++k;
	}

	while (i < n1) {
		container_[k] = leftArr[i];
		++i;
		++k;
	}

	while (j < n2) {
		container_[k] = rightArr[j];
		++j;
		++k;
	}
}