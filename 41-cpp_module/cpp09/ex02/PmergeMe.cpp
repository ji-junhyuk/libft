//
// Created by Junhyuk Ji on 7/9/23.
//

#include "PmergeMe.hpp"

PmergeMe::PmergeVector::PmergeVector(int size) : mSize(size), mPairSize(size / 2), mTempVector(mPairSize) {
    memset(mMemo, 0, sizeof(mMemo));
    JacobsthalNumbers.reserve(32);
    mInitSequence.reserve(mSize);
    mPairSequence.reserve(mPairSize);
    mMainChain.reserve(mPairSize);
    mPendingElement.reserve(mPairSize);
    mSearchOrder.reserve(mPairSize);
    for (int i = 2; i < 33; ++i) {
        JacobsthalNumbers.push_back(generateJacobshalSequence(i));
    }
}

PmergeMe::PmergeVector::PmergeVector(const PmergeVector &other) {
    mSize = other.mSize;
    for (int i = 0; i < 50; ++i) {
        mMemo[i] = other.mMemo[i];
    }
    mPairSize = other.mPairSize;
    JacobsthalNumbers = other.JacobsthalNumbers;
    mInitSequence = other.mInitSequence;
    mPairSequence = other.mPairSequence;
    mMainChain = other.mMainChain;
    mPendingElement = other.mPendingElement;
    mSearchOrder = other.mSearchOrder;
}

PmergeMe::PmergeVector& PmergeMe::PmergeVector::operator=(const PmergeVector &other) {
    if (this != &other) {
        mSize = other.mSize;
        for (int i = 0; i < 50; ++i) {
            mMemo[i] = other.mMemo[i];
        }
        mPairSize = other.mPairSize;
        JacobsthalNumbers = other.JacobsthalNumbers;
        mInitSequence = other.mInitSequence;
        mPairSequence = other.mPairSequence;
        mMainChain = other.mMainChain;
        mPendingElement = other.mPendingElement;
        mSearchOrder = other.mSearchOrder;
    }
    return *this;
}

PmergeMe::PmergeVector::~PmergeVector() {

}

int PmergeMe::PmergeVector::generateJacobshalSequence(int n) {
    if (n <= 1)
        return n;
    if (mMemo[n])
        return mMemo[n];
    return mMemo[n] = (generateJacobshalSequence(n - 2) * 2 + generateJacobshalSequence(n - 1));
}

void PmergeMe::PmergeVector::getInitSequence(const char **argv) {
    int i = 0;
    long num = 0;
    char *lEndPtr = NULL;

    while (argv[++i]) {
        num = std::strtol(argv[i], &lEndPtr, 10);
        if (*lEndPtr != '\0' || num < 0 || num > std::numeric_limits<int>::max()) {
            throw InvalidDataFormat();
        }
        mInitSequence.push_back(num);
    }
}

void PmergeMe::PmergeVector::getPairSequence(const char **argv) {
    getInitSequence(argv);
    int idx = 0;

    for (int i = 0; i < mPairSize; ++i) {
        mPairSequence.push_back(std::make_pair(mInitSequence[idx], mInitSequence[idx + 1]));
        if (mPairSequence[i].first < mPairSequence[i].second)
            std::swap(mPairSequence[i].first, mPairSequence[i].second);
        idx += 2;
    }
}

void PmergeMe::PmergeVector::merge(int start, int end, std::vector<std::pair<int, int> >& tempVector) {
    int mid = (start + end) / 2;
    int leftIdx = start;
    int rightIdx = mid;
    for (int i = start; i < end; ++i) {
        if (rightIdx == end)
            tempVector[i] = mPairSequence[leftIdx++];
        else if (leftIdx == mid)
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

void PmergeMe::PmergeVector::mergeSort(int start, int end, std::vector<std::pair<int, int> >& tempVector) {
    if (end - start == 1)
        return ;
    int mid = (start + end) / 2;
    mergeSort(start, mid, tempVector);
    mergeSort(mid, end, tempVector);
    merge(start, end, tempVector);
}

void PmergeMe::PmergeVector::getSearchOrder() {
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
    }
}

void PmergeMe::PmergeVector::insertByBinarySearch() {
    std::vector<std::pair<int, int> >::iterator it;

    getSearchOrder();
    mMainChain.push_back(mPairSequence[0].second);
    for (int i = 0; i < mPairSize; ++i) {
        mMainChain.push_back(mPairSequence[i].first);
        mPendingElement.push_back(mPairSequence[i].second);
    }
    for (int i = 1; i < static_cast<int>(mSearchOrder.size()); ++i) {
        int key = mPendingElement[mSearchOrder[i]];
        std::vector<int>::iterator lowerBound = std::lower_bound(mMainChain.begin(), mMainChain.begin() + mSearchOrder[i] + i, key);
        mMainChain.insert(lowerBound, key);
    }
    if (mSize & 1) {
        int key = mInitSequence[mSize - 1];
        std::vector<int>::iterator lowerBound = std::lower_bound(mMainChain.begin(), mMainChain.end(), key);
        mMainChain.insert(lowerBound, key);
    }
}

void PmergeMe::PmergeVector::mergeSelectionSort(const char **argv) {
    getPairSequence(argv);
    mergeSort(0, mPairSize, mTempVector);
    insertByBinarySearch();
    printSequence();
}

void PmergeMe::PmergeVector::printSequence() {
    std::cout << "Before:    ";
    for (int i = 0; i < mSize; ++i) {
        std::cout << mInitSequence[i] << ' ';
    }
    std::cout << '\n';
    std::cout << "After:     ";
    for (int i = 0; i < mSize; ++i) {
        std::cout << mMainChain[i] << ' ';
    }
    std::cout << std::endl;
}

PmergeMe::PmergeList::PmergeList(int size) : mSize(size), mPairSize(size / 2), mTempList(mPairSize) {
    memset(mMemo, 0, sizeof(mMemo));
    for (int i = 2; i < 33; ++i) {
        JacobsthalNumbers.push_back(generateJacobshalSequence(i));
    }
}

PmergeMe::PmergeList::PmergeList(const PmergeList &other) {
    mSize = other.mSize;
    for (int i = 0; i < 50; ++i) {
        mMemo[i] = other.mMemo[i];
    }
    mPairSize = other.mPairSize;
    JacobsthalNumbers = other.JacobsthalNumbers;
    mInitSequence = other.mInitSequence;
    mPairSequence = other.mPairSequence;
    mMainChain = other.mMainChain;
    mPendingElement = other.mPendingElement;
    mSearchOrder = other.mSearchOrder;
}

PmergeMe::PmergeList& PmergeMe::PmergeList::operator=(const PmergeList &other) {
    if (this != &other) {
        mSize = other.mSize;
        for (int i = 0; i < 50; ++i) {
            mMemo[i] = other.mMemo[i];
        }
        mPairSize = other.mPairSize;
        JacobsthalNumbers = other.JacobsthalNumbers;
        mInitSequence = other.mInitSequence;
        mPairSequence = other.mPairSequence;
        mMainChain = other.mMainChain;
        mPendingElement = other.mPendingElement;
        mSearchOrder = other.mSearchOrder;
    }
    return *this;
}

PmergeMe::PmergeList::~PmergeList() {

}

int PmergeMe::PmergeList::generateJacobshalSequence(int n) {
    if (n <= 1)
        return n;
    if (mMemo[n])
        return mMemo[n];
    return mMemo[n] = (generateJacobshalSequence(n - 2) * 2 + generateJacobshalSequence(n - 1));
}

void PmergeMe::PmergeList::getInitSequence(const char **argv) {
    int i = 0;
    long num = 0;
    char *lEndPtr = NULL;

    while (argv[++i]) {
        num = std::strtol(argv[i], &lEndPtr, 10);
        if (*lEndPtr != '\0' || num < 0 || num > std::numeric_limits<int>::max()) {
            throw InvalidDataFormat();
        }
        mInitSequence.push_back(num);
    }
}

void PmergeMe::PmergeList::getPairSequence(const char **argv) {
    std::list<int>::iterator startIt;
    getInitSequence(argv);

    startIt = mInitSequence.begin();
    for (int i = 0; i < mPairSize; ++i) {
        std::list<int>::iterator curIt = startIt;
        std::advance(curIt, 1);
        mPairSequence.push_back(std::make_pair(*startIt, *curIt));
        ++startIt;
        ++startIt;
    }
    std::list<std::pair<int, int> >::iterator startPIt = mPairSequence.begin();
    for (std::list<std::pair<int, int> >::iterator it = startPIt; it != mPairSequence.end(); ++it) {
        if ((*it).first < (*it).second)
            std::swap((*it).first, (*it).second);
    }
    std::cout << std::endl;
}

void PmergeMe::PmergeList::merge(int start, int end) {
    int mid = (start + end) / 2;

    std::list<std::pair<int, int> >::iterator midIt = mPairSequence.begin();
    std::list<std::pair<int, int> >::iterator endIt = mPairSequence.begin();
    std::list<std::pair<int, int> >::iterator pairLeftIt;
    std::list<std::pair<int, int> >::iterator pairRightIt;
    std::list<std::pair<int, int> >::iterator tempIt;
    std::advance(midIt, mid);
    std::advance(endIt, end);
    int lIdx = 0;
    int rIdx = 0;
    for (int i = start; i < end; ++i) {
        pairLeftIt = mPairSequence.begin();
        pairRightIt = mPairSequence.begin();
        tempIt = mTempList.begin();
        std::advance(pairLeftIt, start + lIdx);
        std::advance(pairRightIt, mid + rIdx);
        std::advance(tempIt, i);
        if (pairRightIt == endIt) {
            *tempIt = *pairLeftIt;
            ++lIdx;
        }
        else if (pairLeftIt == midIt) {
            *tempIt = *pairRightIt;
            ++rIdx;
        }
        else if (pairLeftIt->first <= pairRightIt->first) {
            *tempIt = *pairLeftIt;
            ++lIdx;
        }
        else {
            *tempIt = *pairRightIt;
            ++rIdx;
        }
    }
    std::list<std::pair<int, int> >::iterator startIt = mPairSequence.begin();
    endIt = mPairSequence.begin();
    tempIt = mTempList.begin();
    std::advance(startIt, start);
    std::advance(tempIt, start);
    std::advance(endIt, end);
    for (std::list<std::pair<int, int> >::iterator it = startIt; it != endIt; ++it) {
        *it = *tempIt++;
    }
}

void PmergeMe::PmergeList::mergeSort(int start, int end) {
    if (end - start == 1)
        return ;
    int mid = (start + end) / 2;
    mergeSort(start, mid);
    mergeSort(mid, end);
    merge(start, end);
}

void PmergeMe::PmergeList::getSearchOrder() {
    std::list<int>::iterator upper_bound;
    upper_bound = std::upper_bound(JacobsthalNumbers.begin(), JacobsthalNumbers.end(), mPairSize);
    int last = -1;
    for (std::list<int>::iterator it = JacobsthalNumbers.begin(); it != upper_bound ; ++it) {
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
    }
}

void PmergeMe::PmergeList::insertByBinarySearch() {
    std::list<std::pair<int, int> >::iterator pairStartIt = mPairSequence.begin();

    getSearchOrder();
    mMainChain.push_back(pairStartIt->second);
    for (int i = 0; i < mPairSize; ++i) {
        mMainChain.push_back(pairStartIt->first);
        mPendingElement.push_back(pairStartIt->second);
        ++pairStartIt;
    }
    for (int i = 1; i < static_cast<int>(mSearchOrder.size()); ++i) {
        std::list<int>::iterator pendStartIt = mPendingElement.begin();
        std::list<int>::iterator chainEndIt = mMainChain.begin();
        std::list<int>::iterator orderStartIt = mSearchOrder.begin();
        std::advance(orderStartIt, i);
        std::advance(pendStartIt, *orderStartIt);
        std::advance(chainEndIt, *orderStartIt + i);
        int key = *pendStartIt;
        std::list<int>::iterator lowerBound = std::lower_bound(mMainChain.begin(), chainEndIt, key);
        mMainChain.insert(lowerBound, key);
    }
    if (mSize & 1) {
        int key = mInitSequence.back();
        std::list<int>::iterator lowerBound = std::lower_bound(mMainChain.begin(), mMainChain.end(), key);
        mMainChain.insert(lowerBound, key);
    }
}

void PmergeMe::PmergeList::printSequence() {
    std::list<int>::iterator initIt = mInitSequence.begin();
    std::list<int>::iterator chainIt = mMainChain.begin();
    std::cout << "Before:    ";
    for (std::list<int>::iterator it = initIt; it != mInitSequence.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\nAfter:     ";
    for (std::list<int>::iterator it = chainIt; it != mMainChain.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

void PmergeMe::PmergeList::mergeSelectionSort(const char **argv) {
    getPairSequence(argv);
    mergeSort(0, mPairSize);
    insertByBinarySearch();
    printSequence();
}

const char *PmergeMe::InvalidDataFormat::what() const throw() {
    return "InvalidDataFormat";
}