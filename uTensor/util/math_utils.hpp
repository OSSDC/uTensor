#ifndef __MATH_UTILS_HPP
#define __MATH_UTILS_HPP

#include <math.h>
#include <limits>
#include <string>
#include <vector>
#include "uTensor_util.hpp"
#include "tensor.hpp"

namespace utils {
template <typename U>
double meanAbsErr(Tensor* A, Tensor* B) {
    if (A->getSize() != B->getSize()) {
        ERR_EXIT("Test.meanAbsErr(): dimension mismatch\r\n");
    }

    const U* elemA = A->read<U>(0, 0);
    const U* elemB = B->read<U>(0, 0);

    double accm = 0.0;
    for (uint32_t i = 0; i < A->getSize(); i++) {
        accm += (double)fabs((float)elemB[i] - (float)elemA[i]);
    }

    return accm;
}

// A being the reference
template <typename U>
double sumPercentErr(Tensor* A, Tensor* B) {
    if (A->getSize() != B->getSize()) {
        ERR_EXIT("Test.sumPercentErr(): dimension mismatch\r\n");
    }


    double accm = 0.0;
    for (uint32_t i = 0; i < A->getSize(); i++) {
        const U* elemA = A->read<U>(i, 1);
        const U* elemB = B->read<U>(i, 1);
        if (elemA[0] != 0.0f) {
            accm += (double)fabs(((float)elemB[0] - (float)elemA[0]) /
                    fabs((float)elemA[0]));
        } else {
            if (elemB[0] != 0) {
                accm += std::numeric_limits<float>::quiet_NaN();
            }
        }
    }
    return accm;
}

template<typename U>
double meanPercentErr(Tensor* A, Tensor* B) {
    double sum = sumPercentErr<U>(A, B);
    return sum / A->getSize();
}

}
#endif /*__MATH_UTILS_HPP*/
