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

long long int calc(int id[], char op[], int n) {
    long long int res = 0, tmp = id[0];
    char t = '+';
    for (int i = 0; i < n; i++)
        if (op[i] == ' ')
            tmp = 10 * tmp + id[i + 1];
        else {
            if (t == '+')
                res += tmp;
            else
                res *= tmp;
            tmp = id[i + 1];
            t = op[i];
        }
    return t == '+' ? res + tmp : res * tmp;
}
void no(int N, long long int D, int id[], char op[], int n, long long int d, long long int &minNo) {
    if (d >= minNo || minNo == D)
        return ;
    if (n + 1 == N) {
        if (d >= D) {
            minNo = d;
            if (d == D) {
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
        double tD = D / pow(10, N - n - 2);
        if (d * 20 <= tD)
            return ;
        op[n] = ' ';
        no(N, D, id, op, n + 1, calc(id, op, n + 1), minNo);
        if (d * (id[n + 1] + 1) <= tD)
            return ;
        op[n] = '*';
        no(N, D, id, op, n + 1, d * id[n + 1], minNo);
        if (d + id[n + 1] < tD)
            return ;
        op[n] = '+';
        no(N, D, id, op, n + 1, d + id[n + 1], minNo);
    } else {
        if (d == 1 || id[n + 1] == 1) {
            op[n] = '*';
            no(N, D, id, op, n + 1, d * id[n + 1], minNo);
        } else {
            op[n] = '+';
            no(N, D, id, op, n + 1, d + id[n + 1], minNo);
        }
    }
}
int main() {
    int N;
    long long int D;
    scanf("%d%lld", &N, &D);

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
