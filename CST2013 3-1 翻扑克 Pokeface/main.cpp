#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

//  (int)ceil(log2(10^6)) = 20
const int n_MAX = 1 << 20;
int number[n_MAX];
bool turn[n_MAX << 1],
     modified[n_MAX];
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))
int question(int loc, int l, int r, int i, int j) {
    if (l + 1 == r)
        return turn[loc];
    if (!modified[loc] && l == i && r == j)
        return turn[loc] ? r - l - number[loc] : number[loc];
    if (modified[loc]) {
        number[loc] = question((loc << 1) + 1, l, l + r >> 1, l, l + r >> 1) + question((loc << 1) + 2, l + r >> 1, r, l + r >> 1, r);
        modified[loc] = false;
    }
    int ans = 0;
    if (i < l + r >> 1)
        ans += question((loc << 1) + 1, l, l + r >> 1, i, min(l + r >> 1, j));
    if (l + r >> 1 < j)
        ans += question((loc << 1) + 2, l + r >> 1, r, max(l + r >> 1, i), j);
    return turn[loc] ? j - i - ans : ans;
}
void modify(int loc, int l, int r, int i, int j) {
    if (l == i && r == j)
        turn[loc] = !turn[loc];
    else {
        modified[loc] = true;
        if (i < l + r >> 1)
            modify((loc << 1) + 1, l, l + r >> 1, i, min(l + r >> 1, j));
        if (l + r >> 1 < j)
            modify((loc << 1) + 2, l + r >> 1, r, max(l + r >> 1, i), j);
    }
}
int main() {
    int n, p, q;
    scanf("%d%d%d", &n, &p, &q);

    int nFull = 1 << (int)ceil(log2(n));
    memset(number, 0, sizeof(*number) * nFull);
    memset(turn, 0, sizeof(*turn) * (nFull << 1));
    memset(modified, 0, sizeof(*modified) * nFull);
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
