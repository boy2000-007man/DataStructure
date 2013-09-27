#include <cmath>
#include <cstdio>
#include <climits>
using namespace std;

int main() {
    int N;
    long long int D;
    scanf("%d%lld", &N, &D);

    int id[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &id[i]);

    long long int no = LLONG_MAX;
    for (int i = 0; i < (1 << N - 1); i++) {
        long long int tmp = id[0];
        for (int j = 1; j < N; j++) {
            //printf("%lld\n", tmp);
            if (tmp >= no)
                break;/*
            if (tmp >= D) {
                if (id[j] == 1 || tmp == 1) {
                    if (i & (1 << j - 1))
                        i = ((i >> j) | 1) << j;
                } else
                    i |= 1 << j - 1;
            }*/
            if (i & (1 << j - 1))
                tmp += id[j];
            else
                tmp *= id[j];
        }
        if (no > tmp)
            no = tmp;
        if (no == D) {
            printf("%d", id[0]);
            for (int j = 1; j < N; j++)
                printf("%c%d", i & (1 << j - 1) ? '+' : '*', id[j]);
            putchar('\n');
            break;
        }
    }
    if (no > D)
        printf("No\n%lld\n", no);
    printf("%lld\n", no);

    return 0;
}
