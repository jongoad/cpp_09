#include "../include/PmergeMe.hpp"

template <class T>
PmergeMe<T>::PmergeMe() {}

template <class T>
PmergeMe<T>::PmergeMe(char** input) {
	for (int i = 1; input[i] != NULL; ++i) {
		int res = std::atoi(input[i]);
		//Need to use res,res because of pair use in container template
		container_.push_back(std::make_pair(res, res));
	}
	mergeInsertSort();
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

	//Create "pair" using two separate vectors
	std::vector<std::pair<int, int> > leftArr(n1);
	std::vector<std::pair<int, int> > rightArr(n2);
	
	//Copy all sorted elements into temp arrays
	for (int i = 0; i < n1; ++i) {
		leftArr[i] = container_[left + i];
	}

	for (int j = 0; j < n2; ++j) {
		rightArr[j] = container_[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;

	//Do pairwise comparison
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

	//Merge in remaining elements
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