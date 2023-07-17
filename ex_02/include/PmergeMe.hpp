#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cstdlib>
#include <limits.h>
#include <utility>

template <class T>
class PmergeMe {
    public:
        PmergeMe();
		PmergeMe(char** input);
        PmergeMe(const PmergeMe& other);
        ~PmergeMe();
        const PmergeMe& operator=(const PmergeMe& rhs);


		bool parseInput(char** input);
        void printContainer(void);
        void mergeInsertSort(void);
        void mergeInsertSortHelper(int left, int right);
        void merge(int left, int mid, int right);

    private:
		T       container_;
};