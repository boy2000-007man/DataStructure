/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-09-29 10:01
* Filename      : main.cpp
* Description   : O(e ^ N)
*****************************************************************/
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
using namespace std;

const char allOperators[] = " *+";
const int allOperatorsNum = strlen(allOperators);
const int N_MAX = 24;
char op[N_MAX];
double p10[N_MAX] = {1};
double num[N_MAX][N_MAX];
//const int leftNum_MAX = (int)pow(allOperatorsNum, N_MAX / 2 - 1);
//const int rightNum_MAX = (int)pow(allOperatorsNum, (N_MAX + 1) / 2 - 1);
struct Data {
    int operators;
    double value;
} left[177147], right[177147 << 1];
int cmp(const void *d1, const void *d2) {
    return ((Data *)d1)->value > ((Data *)d2)->value ? 1 : -1;
}
void makeOperators(int num, int operators, char op[]) {
    for (int i = 0; i < num; i++)
        op[i] = allOperators[0];
    for (int i = 0; operators; i++) {
        op[i] = allOperators[operators % allOperatorsNum];
        operators /= allOperatorsNum;
    }
}
double leftCalc(int n) {
    int i = 1;
    while (i < n && op[i - 1] == ' ')
        i++;
    double res = num[0][i - 1];
    for (int j = i++; j < n; j = i++) {
        while (i < n && op[i - 1] == ' ')
            i++;
        if (op[j - 1] == '*')
            res *= num[j][i - 1];
        else
            res += num[j][i - 1];
    }
    return res;
}
unsigned long long int calc(int n) {
    int i = 1;
    while (i < n && op[i - 1] == ' ')
        i++;
    unsigned long long int res = num[0][i - 1];
    for (int j = i++; j < n; j = i++) {
        while (i < n && op[i - 1] == ' ')
            i++;
        if (op[j - 1] == '*')
            res *= (unsigned long long int)num[j][i - 1];
        else
            res += (unsigned long long int)num[j][i - 1];
    }
    return res;
}
double rightCalc(int n, int k, double D) {
    for (int i = n - 1, j = i; ; ) {
        while (op[i] == ' ')
            i--;
        if (op[i] == '*')
            D /= num[i + k][j + k];
        else
            D -= num[i + k][j + k];
        if (i == 0)
            return D;
        j = --i;
    }
}
void no(int N, long long int D, int id[], int n, unsigned long long int d, long long int &minNo) {
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
    if (N >> 1 < n && op[N / 2 - 1] != ' ')
        return ;
    if (d < D) {
        double tD = D / p10[N - n - 2];
        if (n == 0 || op[n - 1] != ' ') {
            if (d * 20 <= tD)
                return ;
            unsigned long long int td = d;
            if (n == 0 || op[n - 1] == '+') {
                td -= id[n];
                for (int i = n + 1; i < N; i++) {
                    op[i - 1] = ' ';
                    if (minNo <= td + num[n][i])
                        break;
                    no(N, D, id, i, td + num[n][i], minNo);
                }
            } else {
                td /= id[n];
                for (int i = n + 1; i < N; i++) {
                    op[i - 1] = ' ';
                    if (minNo <= td * num[n][i])
                        break;
                    no(N, D, id, i, td * num[n][i], minNo);
                }
            }
        }
        if (d * (id[n + 1] + 1) <= tD)
            return ;
        op[n] = '*';
        no(N, D, id, n + 1, d * id[n + 1], minNo);
        if (d + id[n + 1] < tD)
            return ;
        op[n] = '+';
        no(N, D, id, n + 1, d + id[n + 1], minNo);
    } else if (d == 1 || id[n + 1] == 1) {
        op[n] = '*';
        no(N, D, id, n + 1, d * id[n + 1], minNo);
    } else {
        op[n] = '+';
        no(N, D, id, n + 1, d + id[n + 1], minNo);
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

    if (N == 1) {
        printf("%s%d\n", id[0] == D ? "" : "No\n", id[0] < D ? 0 : id[0]);
        return 0;
    }

    for (int i = 0; i < N; i++) {
        num[i][i] = id[i];
        for (int j = i + 1; j < N; j++)
            num[i][j] = num[i][j - 1] * 10 + id[j];
    }
    int middle = N >> 1;
    int leftNum = (int)pow(allOperatorsNum, middle - 1);
    int rightNum = (int)pow(allOperatorsNum, N - middle - 1);
    for (int i = 0; i < leftNum; i++) {
        makeOperators(middle, left[i].operators = i, op);
        left[i].value = leftCalc(middle);
    }
    for (int i = 0; i < rightNum; i++) {
        makeOperators(N - middle, right[i << 1].operators = i * 3 + 1, op);
        right[i << 1].value = rightCalc(N - middle, middle, D);
        op[0] = allOperators[2];
        right[i * 2 + 1].operators = i * 3 + 2;
        right[i * 2 + 1].value = rightCalc(N - middle, middle, D);
    }
    qsort(left, leftNum, sizeof(*left), cmp);
    qsort(right, rightNum << 1, sizeof(*right), cmp);
    long long int minNo = LLONG_MAX;
    for (int l = 0, r = 0; r < rightNum * 2; r++) {
        while (l < leftNum && left[l].value < right[r].value)
            l++;
        if (leftNum <= l)
            break;
        makeOperators(middle, left[l].operators, op);
        makeOperators(N - middle, right[r].operators, op + middle - 1);
        unsigned long long int res = calc(N);
        if (res < minNo) {
            minNo = res;
            if (D == minNo) {
                for (int i = 0; i < N - 1; i++) {
                    printf("%d", id[i]);
                        if (op[i] != ' ')
                            putchar(op[i]);
                }
                printf("%d\n", id[N - 1]);
                return 0;
            }
        }
    }
    printf("%lld\n", minNo);
    no(N, D, id, 0, id[0], minNo);
    if (minNo > D)
        printf("No\n%lld\n", minNo != LLONG_MAX ? minNo : 0);

    return 0;
}
