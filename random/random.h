#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED
#include "../common.h"
inline int bigrand() {
    return RAND_MAX*rand() + rand();
}

inline int randint(int l, int u) {
    return l + bigrand() % (u-l+1);
}
#endif // RANDOM_H_INCLUDED
