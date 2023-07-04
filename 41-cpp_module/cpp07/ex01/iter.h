#ifndef CPP07_ITER_H
#define CPP07_ITER_H

template<typename T, typename F>

void iter(T* array, int array_length, F func) {
    for (int i = 0; i < array_length; ++i) {
        func(array[i]);
    }
}

#endif //CPP07_ITER_H
