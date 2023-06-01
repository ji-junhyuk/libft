//
// Created by ji junhyuk on 2023/06/01.
//

#ifndef CPP08_EASYFIND_H
#define CPP08_EASYFIND_H

#include <algorithm>

template <typename T>
typename T::iterator easyfind(T& container, int value) {
    return (std::find(container.begin(), container.end(), value));
}


#endif //CPP08_EASYFIND_H
