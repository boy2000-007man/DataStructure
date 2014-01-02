#include "beneficiation.h"
#include <cstdio>
#include <cstring>
using namespace std;

const int n_MAX = 10000;
int no[n_MAX + 1];
bool reported[n_MAX];
template <typename T> void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
#define Report(a, b)\
{\
    Report(a, b);\
    reported[b] = true;\
}
void sort(int l, int r) {
    printf("sort(%d, %d)\n", l, r);
    int result[4];
    if (r - l == 1)
        Report(no[l], l);
    if (r - l == 3) {
        Measure(no[l], no[l + 1], no[l + 2], -1, &result[0], &result[1], &result[2], &result[3]);
        for (int i = 0; i < 3; i++) {
            swap(no[l + i], no[l + 1 - result[i]]);
            swap(result[i], result[1 - result[i]]);
        }
        for (int i = l; i < r; i++)
            Report(no[i], i);
    }
    if (r - l == 4) {
        Measure(no[l], no[l + 1], no[l + 2], no[l + 3], &result[0], &result[1], &result[2], &result[3]);
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++)
                if (result[i] < result[j]) {
                    swap(no[l + i], no[l + j]);
                    swap(result[i], result[j]);
                }
        Report(no[l], l);
        Report(no[r - 1], r - 1);
        sort(l + 1, r - 1);
    }
    if (r - l < 5)
        return ;
    swap(no[l + 1], no[l + r >> 1]);
    swap(no[l + 2], no[r - 1]);
    Measure(no[l], no[l + 1], no[l + 2], -1, &result[0], &result[1], &result[2], &result[3]);
    for (int i = 0; i < 3; i++) {
        swap(no[l + i], no[l + 1 - result[i]]);
        swap(result[i], result[1 - result[i]]);
    }
    swap(no[l], no[l + 1]);
    int L = l + 2;
    for (int R = l + 3, wait[3]; R < r; R += result[3] ? 3 : 2) {
        for (int i = 0; i < 3; i++)
            wait[i] = R + i < r ? R + i : n_MAX;
        Measure(no[wait[0]], no[wait[1]], no[wait[2]], no[l], &result[0], &result[1], &result[2], &result[3]);
        if (result[3])
            for (int i = 0; i < 3; i++)
                result[i] = -result[3];
        else if (2 < r - R)
            for (int i = 0; i < 3; i++)
                if (!result[i]) {
                    swap(wait[i], wait[2]);
                    swap(result[i], result[2]);
                    break;
                }
        for (int i = 0; i < 3 && result[i]; i++)
            if (result[i] == 1)
                swap(no[L++], no[wait[i]]);
    }
    L--;
    swap(no[l], no[L]);
    Report(no[L], L);
    sort(l, L);
    sort(L + 1, r);
}
#undef Report
void sort2(int n) {
    int wait[4], result[4];
    for (int i = 0; i < 4; i++)
        wait[i] = n_MAX;
    for (int loc = 0, waitNum = 4; waitNum == 4;) {
        for (waitNum = 0; waitNum < 4 && loc < n; loc++)
            if (!reported[loc])
                wait[waitNum++] = loc;
        if (waitNum) {
            Measure(no[wait[0]], no[wait[1]], no[wait[2]], no[wait[3]], &result[0], &result[1], &result[2], &result[3]);
            if (result[0] < result[1])
                swap(no[wait[0]], no[wait[1]]);
            if (waitNum == 4 && result[2] < result[3])
                swap(no[wait[2]], no[wait[3]]);
        }
        for (int i = 0; i < waitNum; i++)
            Report(no[wait[i]], wait[i]);
    }
}
int main() {
    no[n_MAX] = -1;
    for (int n; n = GetNumOfOre(); ) {
        for (int i = 0; i < n; i++)
            no[i] = i;
        memset(reported, 0, sizeof(reported));
        sort(0, n);
        sort2(n);
    }

    return 0;
}
