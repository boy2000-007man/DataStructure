/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2014-01-04 13:45
* Filename      : main.cpp
* Description   : O((m + n) * log(n) ^ 2)
*****************************************************************/
#include "temperature.h"
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

//  (int)ceil(log2(50000)) = 16
const int n_MAX = 1 << 16;
struct Station {
    int x, y,
        temp;
} info[n_MAX];
int orderX[n_MAX];
template <typename T> int cmp(const T &a, const T &b) {
    if (a == b)
        return 0;
    return a < b ? -1 : 1;
}
int cmpX(const void *p1, const void *p2) {
    return cmp(info[*(int *)p1].x, info[*(int *)p2].x);
}
int cmpY(const void *p1, const void *p2) {
    return cmp(info[*(int *)p1].y, info[*(int *)p2].y);
}
#define left(loc) (((loc) << 1) + 1)
#define right(loc) (((loc) << 1) + 2)
#define middle(a, b) ((a) + (b) >> 1)
struct SegmentTree {
    int size, *orderY;
    long long int *tempSum;
    SegmentTree(int l, int r) {
        orderY = new int[size = r - l];
        memcpy(orderY, orderX + l, sizeof(*orderY) * size);
        qsort(orderY, size, sizeof(*orderY), cmpY);
        tempSum = new long long int[1 << (int)ceil(log2(size)) + 1];
        calcSum(0, 0, size);
    }
    long long int search(int loc, int l, int r, int ly, int ry, int &num) {
        if (info[orderY[r - 1]].y < ly || ry < info[orderY[l]].y)
            return 0;
        if (ly <= info[orderY[l]].y && info[orderY[r - 1]].y <= ry) {
            num += r - l;
            return tempSum[loc];
        }
        return search(left(loc), l, middle(l, r), ly, ry, num) +
            search(right(loc), middle(l, r), r, ly, ry, num);
    }
    ~SegmentTree() {
        delete[] orderY;
        delete[] tempSum;
    }
private:
    long long int calcSum(int loc, int l, int r) {
        return tempSum[loc] = 1 < r - l ?
            calcSum(left(loc), l, middle(l, r)) + calcSum(right(loc), middle(l, r), r) :
            info[orderY[l]].temp;
    }
} *rangeTree[n_MAX << 1];
void makeRangeTree(int loc, int l, int r) {
    rangeTree[loc] = new SegmentTree(l, r);
    if (1 < r - l) {
        makeRangeTree(left(loc), l, middle(l, r));
        makeRangeTree(right(loc), middle(l, r), r);
    }
}
long long int searchRangeTree(int loc, int l, int r, int x1, int y1, int x2, int y2, int &num) {
    if (info[orderX[r - 1]].x < x1 || x2 < info[orderX[l]].x)
        return 0;
    if (x1 <= info[orderX[l]].x && info[orderX[r - 1]].x <= x2)
        return rangeTree[loc]->search(0, 0, rangeTree[loc]->size, y1, y2, num);
    return searchRangeTree(left(loc), l, middle(l, r), x1, y1, x2, y2, num) +
        searchRangeTree(right(loc), middle(l, r), r, x1, y1, x2, y2, num);
}
int main() {
    int n = GetNumOfStation();
    for (int i = 0; i < n; i++)
        GetStationInfo(orderX[i] = i, &info[i].x, &info[i].y, &info[i].temp);

    qsort(orderX, n, sizeof(*orderX), cmpX);
    makeRangeTree(0, 0, n); // O(n * log(n) ^ 2)

    long long int res;
    for (int x1, y1, x2, y2, num; GetQuery(&x1, &y1, &x2, &y2); Response(num ? res / num : 0))
        res = searchRangeTree(0, 0, n, x1, y1, x2, y2, num = 0);    // O(log(n) ^ 2)

    return 0;
}
