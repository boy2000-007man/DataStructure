/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-11-30 01:46
* Filename      : main.cpp
* Description   : O(n * log(n))
*****************************************************************/
#include <cstdio>
#include <cstring>
using namespace std;

const int dX[] = {0, 1, 0, -1},
      dY[] = {1, 0, -1, 0},
      init[][3] = {
          {0, 1, 2},
          {1, 0, 3},
          {2, 0, 1},
          {3, 0, 4},
          {4, 0, 2},
          {5, 1, 3}
      };
const int block_NUM = 8 * 8,
      status_NUM = 6 * 4;
int transform[status_NUM][4];
const int point_NUM = block_NUM * status_NUM;
int edge[point_NUM],
    heap[point_NUM], reflection[point_NUM],
    cost[point_NUM];
const int edge_NUM = point_NUM << 2;
int point[edge_NUM],
    next[edge_NUM];
const int number_MAX = 11000000;
void change(int &a, int &b) {
    int tmp = a;
    a = b;
    b = 5 - tmp;
}
template <typename T> void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
#define in08(x) (0 <= (x) && (x) < 8)
#define min(a, b) ((a) < (b) ? (a) : (b))
int main() {
    int location[2];
    for (int i = 0; i < 2; i++) {
        char x, y;
        scanf(" %c%c", &x, &y);

        location[i] = (x - 'a' << 3) + y - '1';
    }
    int number[6];
    scanf("%d%d%d%d%d%d", &number[4], &number[1], &number[0], &number[2], &number[5], &number[3]);

    for (int i = 0; i < 6; i++) {
        int status[3];
        memcpy(status, init[i], sizeof(status));
        for (int j = 0; j < 4; j++) {
            for (int dxdy = 0; dxdy < 4; dxdy++) {
                int now[3];
                memcpy(now, status, sizeof(now));
                if (dxdy & 0x2)
                    change(now[0], now[dxdy - 1]);
                else
                    change(now[dxdy + 1], now[0]);
                int ans = now[0] << 2;
                while (init[now[0]][1] != now[1]) {
                    change(now[1], now[2]);
                    ans++;
                }
                transform[(i << 2) + j][dxdy] = ans;
            }
            change(status[2], status[1]);
        }
    }

    for (int i = 0; i < point_NUM; i++) {
        edge[i] = -1;
        int x = i >> 3 & 0x7, y = i & 0x7;
        for (int dxdy = 0; dxdy < 4; dxdy++) {
            int dx = dX[dxdy], dy = dY[dxdy];
            if (in08(x + dx) && in08(y + dy)) {
                point[(i << 2) + dxdy] = (transform[i >> 6][dxdy] << 6) + (x + dx << 3) + y + dy;
                next[(i << 2) + dxdy] = edge[i];
                edge[i] = (i << 2) + dxdy;
            }
        }
    }

    int heapNum = 0;
    cost[location[0]] = number[5];
    for (int i = 0; i < point_NUM; i++)
        if (i != location[0])
            cost[heap[reflection[i] = heapNum++] = i] = block_NUM * number_MAX;
    for (int u = location[0]; heapNum && cost[u] != block_NUM * number_MAX; ) {
        for (int i = edge[u]; i != -1; i = next[i]) {
            int v = point[i],
                weight = number[5 - (v >> 8)];
            if (cost[u] + weight < cost[v]) {
                cost[v] = cost[u] + weight;
                for (int loc = reflection[v]; loc && cost[heap[loc]] < cost[heap[loc - 1 >> 1]]; loc = loc - 1 >> 1) {
                    swap(reflection[heap[loc - 1 >> 1]], reflection[heap[loc]]);
                    swap(heap[loc - 1 >> 1], heap[loc]);
                }
            }
        }
        u = heap[0];
        reflection[heap[0] = heap[--heapNum]] = 0;
        int min = 0, root;
        do {
            root = min;
            for (int i = 0; i < 2; i++)
                if ((root + 1 << 1) - i < heapNum && cost[heap[(root + 1 << 1) - i]] < cost[heap[min]])
                    min = (root + 1 << 1) - i;
            swap(reflection[heap[min]], reflection[heap[root]]);
            swap(heap[min], heap[root]);
        } while (root != min);
    }

    int min = block_NUM * number_MAX;
    for (int i = 0; i < status_NUM; i++)
        min = min(min, cost[(i << 6) + location[1]]);
    printf("%d\n", min);

    return 0;
}
