#include "beneficiation.h"
#include <cstdio>
#include <cstdlib>
using namespace std;

int cmp(const void *p1, const void *p2) {
    int wa, wb, wc, wd;
    Measure(*(int *)p1, *(int *)p2, -1, -1, &wa, &wb, &wc, &wd);
    return wb;
}
int main() {
    for (int n; n = GetNumOfOre(); ) {
        int no[n];
        for (int i = 0; i < n; i++)
            no[i] = i;
        qsort(no, n, sizeof(*no), cmp);
        for (int i = 0; i < n; i++)
            Report(no[i], i);
    }

    return 0;
}
