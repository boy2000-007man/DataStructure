/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-11-30 00:10
* Filename      : main.cpp
* Description   : O(N)
*****************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

//  int(log10(2^31 - 1) + 1) + 1 + int(log10(10^3 - 1) + 1) = 14
const int DX_LENGTH = 14;
const int N_MAX = 10000000;
int stockX[N_MAX];
const int X_MAX = 1000; // avoid been full
int topX[X_MAX],
    topNum[X_MAX];

#define mod(a, b) (((a) % (b) + (b)) % (b))
int main() {
    int N;
    scanf("%d\n", &N);

    double sum = 0.0;
    int currentDay = 0,
        stockHead = 0, stockEnd = 0,
        topHead = 0, topEnd = 0;
    for (int i = 0, lastDay; i < N << 1; i++) {
        char DX[DX_LENGTH + 1];
        gets(DX);

        currentDay += atoi(DX);
        if (!strchr(DX, ' ')) {
            if (--topNum[topHead] == 0) {
                sum += (double)(currentDay - lastDay) * topX[topHead];
                lastDay = currentDay;
                topHead = mod(topHead + 1, X_MAX);
            }
            stockHead++;
        } else {
            stockX[stockEnd++] = atoi(strchr(DX, ' '));
            if (topHead == topEnd)
                lastDay = currentDay;
            else if (topX[topHead] < stockX[stockEnd - 1]) {
                sum += (double)(currentDay - lastDay) * topX[topHead];
                lastDay = currentDay;
            }
            int num = 1;
            while (topHead != topEnd && topX[mod(topEnd - 1, X_MAX)] <= stockX[stockEnd - 1]) {
                topEnd = mod(topEnd - 1, X_MAX);
                num += topNum[topEnd];
            }
            topX[topEnd] = stockX[stockEnd - 1];
            topNum[topEnd] = num;
            topEnd = mod(topEnd + 1, X_MAX);
        }
    }
    printf("%.2lf\n", sum / currentDay);

    return 0;
}
