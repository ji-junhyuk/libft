//
// Created by Junhyuk Ji on 7/9/23.
//
#ifndef CPP09_PMERGEME_HPP
#define CPP09_PMERGEME_HPP

#include <vector>
#include <iostream>

//static const int JacobsthalNumbers[20] = {
//        3, 5, 11, 21, 43, 85,
//        171, 341, 683, 1365, 2731,
//        5461, 10923, 21845, 43691, 87381,
//        174763, 349525, 699051, 1398101};
// 33 int overflow
class PmergeMe {
private:
    std::vector<int> JacobsthalNumbers;
    std::vector<int> mInitSequence;
    std::vector<std::pair<int, int> > mPairSequence;
    std::vector<int> mMainChain;
    std::vector<int> mPendingElement;
    std::vector<int> mSearchOrder;
    int mMemo[50];
    int mSize;
    int mPairSize;
    PmergeMe();

public:
    PmergeMe(int size);
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();
    void getInitSequence(const char *argv[]);
    void getPairSequence(const char *argv[]);
    void merge(int start, int end, std::vector<std::pair<int, int> >& tempVector);
    void mergeSort(int start, int end, std::vector<std::pair<int, int> >& tempVector);
    void insertBinarySearch();
    int generateJacobshalSequence(int n);
    void mergeSelectionSort(const char *argv[]);

public:
    class InvalidDataFormat : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

#endif //CPP09_PMERGEME_HPP