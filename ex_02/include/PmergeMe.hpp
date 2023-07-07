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
		void vectorSort();
		void dequeSort();

        void printContainer(void);
        
        

        void mergeInsertSort(void);

    private:
		T       container_;
        T       sorted_;
        int     oddOneOut_;
        bool    isOdd;

};