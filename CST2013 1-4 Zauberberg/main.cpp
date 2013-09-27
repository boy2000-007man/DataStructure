#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MaxNum = 100000;
int cmp(const void *n1, const void *n2) {
    return *(int *)n2 - *(int *)n1;
}
int main() {
    int N, H;
    scanf("%d%d", &N, &H);
    int ill[MaxNum + 1] = {H}, health[MaxNum + 1] = {-1};
    int illNum = 1, healthNum = 1;
    for (int i = 0; i < N; i++) {
        int height;
        char status;
        scanf("%d %c", &height, &status);
        if (status == '+')
            ill[illNum++] = height;
        else
            health[healthNum++] = height;
    }
    qsort(ill, illNum, sizeof(*ill), cmp);
    qsort(health, healthNum, sizeof(*health), cmp);
    int M;
    scanf("%d", &M);
    while (M--) {
        double Phit, Pfalse;
        scanf("%lf%lf", &Phit, &Pfalse);
        int hL = health[int(Pfalse * (healthNum - 1))] + 1;
        int hH = ill[int(ceil(Phit * (illNum - 1)))];
        if (hL <= hH)
            printf("%d %d\n", hL, hH);
        else
            printf("-1\n");
    }
    return 0;
}
