//
// Created by Junhyuk Ji on 7/9/23.
//
#include "PmergeMe.hpp"

int main(int argc, const char *argv[]) {
    if (argc >= 2) {
        PmergeMe PmergeVector(argc - 1);
        //PmergeMe PmergeDeque;
        // 시간 start
        PmergeVector.mergeSelectionSort(argv);
        // 시간 end 0148
//        PmergeVector.print(); // 정렬 전, 정렬 후
        // vector 시간 출력

        // 시간 start
        // PmergeDeque.sort();
        // 시간 end
        // deque 시간 출력
    }
}