#include <stdlib.h>

int randint(int upper, int lower){
    int ret;
    // Generate a random intiger between upper and lower
    ret = rand() % (upper - lower + 1) + lower;
    return ret;
}
