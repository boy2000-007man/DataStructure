/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2014-01-02 23:47
* Filename      : main.cpp
* Description   : O((p + q) * log(n))
*****************************************************************/
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

//  (int)ceil(log2(10^6)) = 20
const int n_MAX = 1 << 20;
int number[n_MAX << 1];
bool turn[n_MAX << 1],
     modified[n_MAX << 1];
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))
#define left(loc) (((loc) << 1) + 1)
#define right(loc) (((loc) << 1) + 2)
#define middle(a, b) ((a) + (b) >> 1)
int question(int loc, int l, int r, int i, int j) {
    if (j <= l || r <= i)
        return 0;
    if (i <= l && r <= j) {
        if (modified[loc]) {
            number[loc] = question(left(loc), l, middle(l, r), l, r) + question(right(loc), middle(l, r), r, l, r);
            modified[loc] = false;
        }
        return turn[loc] ? r - l - number[loc] : number[loc];
    }
    int ans = question(left(loc), l, middle(l, r), i, j) + question(right(loc), middle(l, r), r, i, j);
    return turn[loc] ? min(r, j) - max(l, i) - ans : ans;
}
void modify(int loc, int l, int r, int i, int j) {
    if (i <= l && r <= j)
        turn[loc] = !turn[loc];
    else if (!(j <= l || r <= i)){
        modified[loc] = true;
        modify(left(loc), l, middle(l, r), i, j);
        modify(right(loc), middle(l, r), r, i, j);
    }
}
int main() {
    int n, p, q;
    scanf("%d%d%d", &n, &p, &q);

    int nFull = 1 << (int)ceil(log2(n));
    memset(number, 0, sizeof(*number) * (nFull << 1));
    memset(turn, 0, sizeof(*turn) * (nFull << 1));
    memset(modified, 0, sizeof(*modified) * (nFull << 1));
    modify(0, 0, nFull, 0, n);
    for (int k = 0; k < p + q; k++) {
        char HQ;
        int i, j;
        scanf(" %c%d%d", &HQ, &i, &j);

        if (HQ == 'H')
            modify(0, 0, nFull, i - 1, j);
        else
            printf("%d\n", question(0, 0, nFull, i - 1, j));
    }

    return 0;
}
