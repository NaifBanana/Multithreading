#pragma once
#ifndef _NB_UTIL
#define _NB_UTIL

#include <array>

namespace nb{

template<unsigned int N, typename T>
struct Size {
    std::array<T, N> vals;
};

};
#endif