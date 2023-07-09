//
// Created by Junhyuk Ji on 7/9/23.
//

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(int size) : mSize(size), mPairSize(size / 2) {
    memset(mMemo, 0, sizeof(mMemo));
}

PmergeMe::PmergeMe(const PmergeMe &other) {
    mSize = other.mSize;
    mInitSequence = other.mInitSequence;
    mPairSequence = other.mPairSequence;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        mSize = other.mSize;
        mInitSequence = other.mInitSequence;
        mPairSequence = other.mPairSequence;
    }
    return *this;
}

PmergeMe::~PmergeMe() {

}

void PmergeMe::getInitSequence(const char **argv) {
    int i = 0;
    long num = 0;
    char *lEndPtr = NULL;
    mInitSequence.reserve(mSize);

    while (argv[++i]) {
        num = std::strtol(argv[i], &lEndPtr, 10);
        if (*lEndPtr != '\0' || num < 0 || num > std::numeric_limits<int>::max()) {
            std::cout << lEndPtr << '\n';
            throw InvalidDataFormat();
        }
        mInitSequence.push_back(num);
    }
}

void PmergeMe::getPairSequence(const char **argv) {
    getInitSequence(argv);
    int idx = 0;

    mPairSequence.reserve(mPairSize);
    for (int i = 0; i < mPairSize; ++i) {
        mPairSequence.push_back(std::make_pair(mInitSequence[idx], mInitSequence[idx + 1]));
        if (mPairSequence[i].first < mPairSequence[i].second)
            std::swap(mPairSequence[i].first, mPairSequence[i].second);
        idx += 2;
    }
    for (int i = 0; i < (int)mInitSequence.size(); ++i) {
        std::cout << mInitSequence[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < (int)mPairSequence.size(); ++i) {
        std::cout << mPairSequence[i].first << ',' << mPairSequence[i].second << ' ';
    }
    std::cout << '\n';
}

void PmergeMe::merge(int start, int end, std::vector<std::pair<int, int> >& tempVector) {
    int mid = (start + end) / 2;
    int leftIdx = start;
    int rightIdx = mid;
    for (int i = start; i < end; ++i) {
        if (rightIdx == end)
            tempVector[i] = mPairSequence[leftIdx++];
        else if (leftIdx == end)
            tempVector[i] = mPairSequence[rightIdx++];
        else if (mPairSequence[leftIdx].first <= mPairSequence[rightIdx].first)
            tempVector[i] = mPairSequence[leftIdx++];
        else
            tempVector[i] = mPairSequence[rightIdx++];
    }
    for (int i = start; i < end; ++i) {
        mPairSequence[i] = tempVector[i];
    }
}

void PmergeMe::mergeSort(int start, int end, std::vector<std::pair<int, int> >& tempVector) {
    std::cout << "===\n";
    std::cout << end << ' ' << start << '\n';
    if (end - start <= 1)
        return ;
    int mid = (start + end) / 2;
    mergeSort(start, mid, tempVector);
    mergeSort(mid, end, tempVector);
    merge(start, end, tempVector);
}

int PmergeMe::generateJacobshalSequence(int n) {
    if (n <= 1)
        return n;
    if (mMemo[n])
        return mMemo[n];
    return mMemo[n] = (generateJacobshalSequence(n - 2) * 2 + generateJacobshalSequence(n - 1));
}

void PmergeMe::insertBinarySearch() {
    int num;
    for (int i = 2; i < 33; ++i) {
        num = generateJacobshalSequence(i);
        JacobsthalNumbers.push_back(num);
    }
    for (int i = 0; i < (int)JacobsthalNumbers.size(); ++i) {
        std::cout << JacobsthalNumbers[i] << ' ';
    }
    std::cout << std::endl;
    std::vector<int>::iterator upper_bound;
    upper_bound = std::upper_bound(JacobsthalNumbers.begin(), JacobsthalNumbers.end(), mPairSize);

    int last = -1;
    for (std::vector<int>::iterator it = JacobsthalNumbers.begin(); it < upper_bound ; ++it) {
        int start = (*it - 1);
        for (int i = start; i > last; --i) {
            mSearchOrder.push_back(i);
        }
        last = (*it - 1);
    }
    if (upper_bound != JacobsthalNumbers.begin()) {
        --upper_bound;
        for (int i = mPairSize - 1; i >= *upper_bound; --i) {
            mSearchOrder.push_back(i);
        }
        std::cout << *upper_bound << '\n';
        std::cout << "mSearchorder\n";
        for (int i = 0; i < (int)mSearchOrder.size(); ++i) {
            std::cout << mSearchOrder[i] << ' ';
        }
        std::cout << std::endl;
    }
    // find_searchpos

//    std::vector<std::pair<int, int> >::iterator it;
//    mMainChain.push_back(mPairSequence[0].second);
//    for (int i = 0; i < mPairSize; ++i) {
//        mMainChain.push_back(mPairSequence[i].first);
//        mPendingElement.push_back(mPairSequence[i].second);
//    }
    // searchOrder
}

void PmergeMe::mergeSelectionSort(const char **argv) {
    getPairSequence(argv);
    std::vector<std::pair<int, int> > tempVector(mPairSequence);
    mergeSort(0, mPairSize, tempVector);
    insertBinarySearch();

//    for (int i = 0; i < (int)mPairSequence.size(); ++i) {
//        std::cout << mPairSequence[i].first << ',' << mPairSequence[i].second << ' ';
//    }
//    std::cout << '\n';
}

const char *PmergeMe::InvalidDataFormat::what() const throw() {
    return "InvalidDataFormat";
}
