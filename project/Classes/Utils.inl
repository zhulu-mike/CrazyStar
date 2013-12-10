#ifndef _UTILS_H_
#define _UTILS_H_

int randLimit(int nMin, int nMax)
{
    assert(nMax != nMin);

    //include max value and min value
    return (rand() % (nMax - nMin + 1) + nMin);
}

#endif

