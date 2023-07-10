//
// Created by Junhyuk Ji on 7/9/23.
//
#include "PmergeMe.hpp"
#include <time.h>
#include <sys/time.h>
#include <list>

int main(int argc, const char *argv[]) {
    if (argc >= 3) {
        struct timeval startTime;
        struct timeval curTime;
        long elapsed_time = 0;
        try {
            PmergeMe::PmergeVector mergeVector(argc - 1);
            gettimeofday(&startTime, NULL);
            mergeVector.mergeSelectionSort(argv);
            gettimeofday(&curTime, NULL);
            elapsed_time = (curTime.tv_sec - startTime.tv_sec) * 1000000 + (curTime.tv_usec - startTime.tv_usec);
            std::cout << elapsed_time << "μs elapsed." << std::endl;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        try {
            PmergeMe::PmergeList mergeList(argc - 1);
            gettimeofday(&startTime, NULL);
            mergeList.mergeSelectionSort(argv);
            gettimeofday(&curTime, NULL);
            elapsed_time = (curTime.tv_sec - startTime.tv_sec) * 1000000 + (curTime.tv_usec - startTime.tv_usec);
            std::cout << elapsed_time << "μs elapsed." << std::endl;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}