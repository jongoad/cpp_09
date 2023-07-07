#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <cstdlib>
#include <limits.h>

template <class T>
class PmergeMe {
    public:
        PmergeMe();
		PmergeMe(char** input);
        PmergeMe(const PmergeMe& other);
        ~PmergeMe();
        const PmergeMe& operator=(const PmergeMe& rhs);


		bool parseInput(char** input);
		void vectorSort();
		void dequeSort();

        void printContainer(void);

    private:
		T container_;

};