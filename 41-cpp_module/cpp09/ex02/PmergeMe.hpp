//
// Created by Junhyuk Ji on 7/9/23.
//
#ifndef CPP09_PMERGEME_HPP
#define CPP09_PMERGEME_HPP

#include <vector>
#include <list>
#include <iterator>
#include <iostream>

class PmergeMe {
public:
    class PmergeVector {
    private:
        int mMemo[50];
        int mSize;
        int mPairSize;

        std::vector<int> JacobsthalNumbers;
        std::vector<int> mInitSequence;
        std::vector<std::pair<int, int> > mPairSequence;
        std::vector<std::pair<int, int> > mTempVector;
        std::vector<int> mMainChain;
        std::vector<int> mPendingElement;
        std::vector<int> mSearchOrder;

        PmergeVector();

    public:
        PmergeVector(int size);
        PmergeVector(const PmergeVector& other);
        PmergeVector& operator=(const PmergeVector& other);
        ~PmergeVector();
        int generateJacobshalSequence(int n);
        void getInitSequence(const char *argv[]);
        void getPairSequence(const char *argv[]);
        void merge(int start, int end, std::vector<std::pair<int, int> >& tempVector);
        void mergeSort(int start, int end, std::vector<std::pair<int, int> >& tempVector);
        void getSearchOrder();
        void insertByBinarySearch();
        void printSequence();
        void mergeSelectionSort(const char *argv[]);
    };

    class PmergeList {
    private:
        int mMemo[50];
        int mSize;
        int mPairSize;

        std::list<int> JacobsthalNumbers;
        std::list<int> mInitSequence;
        std::list<std::pair<int, int> > mPairSequence;
        std::list<std::pair<int, int> > mTempList;
        std::list<int> mMainChain;
        std::list<int> mPendingElement;
        std::list<int> mSearchOrder;

        PmergeList();

    public:
        PmergeList(int size);
        PmergeList(const PmergeList& other);
        PmergeList& operator=(const PmergeList& other);
        ~PmergeList();
        int generateJacobshalSequence(int n);
        void getInitSequence(const char *argv[]);
        void getPairSequence(const char *argv[]);

        void merge(int start, int end);
        void mergeSort(int start, int end);
        void getSearchOrder();
        void insertByBinarySearch();
        void printSequence();
        void mergeSelectionSort(const char *argv[]);
    };

public:
    class InvalidDataFormat : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

#endif //CPP09_PMERGEME_HPP