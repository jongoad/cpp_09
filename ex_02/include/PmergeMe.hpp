#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <stdlib.h>
#include <limits.h>

template <class T>
class PmergeMe {
    public:
        PmergeMe<T>();
		PmergeMe(char** input);
        PmergeMe(const PmergeMe& other);
        ~PmergeMe();

        const PmergeMe& operator=(const PmergeMe& rhs);


		bool parseInput(char **input);
		void vectorSort();
		void dequeSort();

    private:
		T container_;

};