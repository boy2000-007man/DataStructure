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
    if (n == 0)
        return D;
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
int main() {
    int N;
    long long int D;
    scanf("%d%lld", &N, &D);

    int id[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &id[i]);
    for (int i = 0; i < N; i++) {
        num[i][i] = id[i];
        for (int j = i + 1; j < N; j++)
            num[i][j] = num[i][j - 1] * 10 + id[j];
    }

    if (N == 1) {
        printf("%s%d\n", id[0] == D ? "" : "No\n", id[0] < D ? 0 : id[0]);
        return 0;
    }

    int middle = N >> 1;
    int leftNum = (int)pow(allOperatorsNum, middle - 1);
    int rightNum = (int)pow(allOperatorsNum, N - middle - 1);
    for (int i = 0; i < leftNum; i++)
        left[i].operators = i;
    long long int minNo = LLONG_MAX;
    for (int i = 0; middle + i <= N; i++) {
        for (int j = 0; j < leftNum; j++) {
            makeOperators(middle + i, left[j].operators, op);
            left[j].value = leftCalc(middle + i);
        }
        for (int j = 0; j < rightNum; j++) {
            makeOperators(N - middle - i, right[j << 1].operators = j * allOperatorsNum + 1, op);
            right[j << 1].value = rightCalc(N - middle - i, middle + i, D);
            op[0] = allOperators[2];
            right[j * 2 + 1].operators = j * allOperatorsNum + 2;
            right[j * 2 + 1].value = rightCalc(N - middle - i, middle + i, D);
        }
        qsort(left, leftNum, sizeof(*left), cmp);
        qsort(right, rightNum << 1, sizeof(*right), cmp);
        for (int l = 0, r = 0; r < rightNum * 2; r++) {
            while (l < leftNum && left[l].value < right[r].value)
                l++;
            if (leftNum <= l)
                break;
            makeOperators(middle + i, left[l].operators, op);
            makeOperators(N - middle - i, right[r].operators, op + middle + i - 1);
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
        if (rightNum != 1)
            rightNum /= allOperatorsNum;
    }
    if (minNo > D)
        printf("No\n%lld\n", minNo != LLONG_MAX ? minNo : 0);

    return 0;
}
