/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2014-01-04 00:31
* Filename      : main.cpp
* Description   : O(m * n * log(n))
*****************************************************************/
#include "beneficiation.h"
#include <cstring>
using namespace std;

const int n_MAX = 10000;
int no[n_MAX],
    left[n_MAX], leftNum;
template <typename T> void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
#define Report(rank) Report(no[rank], rank)
void sort(int l, int r) {
    static int result[4];
    switch (r - l) {
        case 1:
            Report(l);
            return ;
        case 2:
            left[leftNum++] = l;
            return ;
        case 3:
        case 4:
            Measure(no[l], no[l + 1], no[l + 2], l + 3 < r ? no[l + 3] : -1, &result[0], &result[1], &result[2], &result[3]);
            for (int i = 0; i < r - l; i++)
                for (int j = i + 1; j < r - l; j++)
                    if (result[i] < result[j]) {
                        swap(no[l + i], no[l + j]);
                        swap(result[i], result[j]);
                    }
            Report(l);
            Report(r - 1);
            sort(l + 1, r - 1);
            return ;
    }
    swap(no[l + 1], no[l + r >> 1]);
    swap(no[l + 2], no[r - 1]);
    Measure(no[l], no[l + 1], no[l + 2], -1, &result[0], &result[1], &result[2], &result[3]);
    for (int i = 0; i < 3; i++) {
        swap(no[l + i], no[l + (result[i] + 3) % 3]);
        swap(result[i], result[(result[i] + 3) % 3]);
    }
    int L = l + 2;
    for (int R = l + 3; R < r; R += result[3] ? 3 : 2) {
        Measure(no[R], R + 1 < r ? no[R + 1] : -1, R + 2 < r ? no[R + 2] : -1, no[l], &result[0], &result[1], &result[2], &result[3]);
        if (result[3])
            for (int i = 0; i < 3 && R + i < r; i++)
                result[i] = -result[3];
        else if (2 < r - R)
            for (int i = 0; i < 2; i++)
                if (!result[i]) {
                    swap(no[R + i], no[R + 2]);
                    swap(result[i], result[2]);
                }
        for (int i = 0; i < 3 && result[i]; i++)
            if (result[i] == 1)
                swap(no[L++], no[R + i]);
    }
    swap(no[l], no[--L]);
    Report(L);
    sort(l, L);
    sort(L + 1, r);
}
int main() {
    for (int n; n = GetNumOfOre(); ) {
        for (int i = 0; i < n; i++)
            no[i] = i;
        leftNum = 0;
        sort(0, n);
        for (int i = 0, result[4]; i < leftNum; i += 2) {
            Measure(no[left[i]], no[left[i] + 1], 1 < leftNum - i ? no[left[i + 1]] : -1, 1 < leftNum - i ? no[left[i + 1] + 1] : -1, &result[0], &result[1], &result[2], &result[3]);
            for (int j = 0; j < 2 && i + j < leftNum; j++) {
                if (result[j << 1] < result[(j << 1) + 1])
                    swap(no[left[i + j]], no[left[i + j] + 1]);
                Report(left[i + j]);
                Report(left[i + j] + 1);
            }
        }
    }

    return 0;
}
