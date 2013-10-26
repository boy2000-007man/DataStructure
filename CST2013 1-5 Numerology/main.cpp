/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-09-29 10:01
* Filename      : main.cpp
* Description   : O(e ^ N)
*****************************************************************/
#include <cmath>
#include <cstdio>
#include <climits>
using namespace std;

const int N_MAX = 24;
double p10[N_MAX] = {1};
void no(int N, long long int D, int id[], char op[], int n, unsigned long long int d, long long int &minNo) {
    if (minNo <= d || minNo == D)
        return ;
    if (n + 1 == N) {
        if (D <= d) {
            minNo = d;
            if (D == minNo) {
                for (int i = 0; i < N - 1; i++) {
                    printf("%d", id[i]);
                    if (op[i] != ' ')
                        putchar(op[i]);
                }
                printf("%d\n", id[N - 1]);
            }
        }
        return ;
    }
    if (d < D) {
        double tD = D / p10[N - n - 2];
        if (n == 0 || op[n - 1] != ' ') {
            if (d * 20 <= tD)
                return ;
            unsigned long long int td = d, tmp = id[n];
            if (n == 0 || op[n - 1] == '+') {
                td -= tmp;
                for (int i = n + 1; i < N; i++) {
                    op[i - 1] = ' ';
                    tmp = tmp * 10 + id[i];
                    if (minNo <= (double)td + tmp)
                        break;
                    no(N, D, id, op, i, td + tmp, minNo);
                }
            } else {
                td /= tmp;
                for (int i = n + 1; i < N; i++) {
                    op[i - 1] = ' ';
                    tmp = tmp * 10 + id[i];
                    if (minNo <= (double)td * tmp)
                        break;
                    no(N, D, id, op, i, td * tmp, minNo);
                }
            }
        }
        if (d * (id[n + 1] + 1) <= tD)
            return ;
        op[n] = '*';
        no(N, D, id, op, n + 1, d * id[n + 1], minNo);
        if (d + id[n + 1] < tD)
            return ;
        op[n] = '+';
        no(N, D, id, op, n + 1, d + id[n + 1], minNo);
    } else if (d == 1 || id[n + 1] == 1) {
            op[n] = '*';
            no(N, D, id, op, n + 1, d * id[n + 1], minNo);
    } else {
            op[n] = '+';
            no(N, D, id, op, n + 1, d + id[n + 1], minNo);
    }
}
int main() {
    int N;
    long long int D;
    scanf("%d%lld", &N, &D);
    for (int i = 1; i < N - 1; i++)
        p10[i] = p10[i - 1] * 10;

    int id[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &id[i]);

    long long int minNo = LLONG_MAX;
    char op[N - 1];
    no(N, D, id, op, 0, id[0], minNo);
    if (minNo > D)
        printf("No\n%lld\n", minNo != LLONG_MAX ? minNo : 0);

    return 0;
}
