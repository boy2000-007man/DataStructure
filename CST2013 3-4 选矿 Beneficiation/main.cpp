#include "beneficiation.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int n_MAX = 10000;
int no[n_MAX + 1],
    result[n_MAX + 1];
template <typename T> void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
void sort(int l, int r) {
    if (r - l == 1)
        Report(no[l], l);
    if (r - l < 2)
        return ;
    swap(no[l], no[l + rand() % (r - l)]);
    memset(result + l, 0, (r - l) * sizeof(*result));
    for (int resultNum = 1, wait[3]; resultNum < r - l; resultNum += result[l] ? 3 : 2) {
        for (int i = 0; i < 3; i++)
            wait[i] = n_MAX;
        for (int i = l + 1, waitNum = 0; i < r && waitNum < 3; i++)
            if (!result[i])
                wait[waitNum++] = i;
        Measure(no[l], no[wait[0]], no[wait[1]], no[wait[2]], &result[l], &result[wait[0]], &result[wait[1]], &result[wait[2]]);
        if (result[l])
            for (int j = 0; j < 3; j++)
                result[wait[j]] = -result[l];
    }
    int i = l + 1;
    for (int j = r - 1; i < j; swap(no[i], no[j])) {
        while (result[i] == 1 && i < j)
            i++;
        while (result[j] != 1 && i < j)
            j--;
        swap(result[i], result[j]);
    }
    if (result[i] != 1)
        i--;
    swap(no[l], no[i]);
    Report(no[i], i);
    sort(l, i);
    sort(i + 1, r);
}
int main() {
    srand(time(NULL));

    no[n_MAX] = -1;
    for (int n; n = GetNumOfOre(); ) {
        for (int i = 0; i < n; i++)
            no[i] = i;
        sort(0, n);
    }

    return 0;
}
