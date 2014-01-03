#include <cstdio>
using namespace std;

const int N_MAX = 2 * 100000;
int heap[2][N_MAX],
    reflection[2][N_MAX];
template <typename T> void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
#define root(loc) ((loc) - 1 >> 1)
#define swap(a, b) {\
    swap(reflection[!code][reflection[code][a]], reflection[!code][reflection[code][b]]);\
    swap(reflection[code][a], reflection[code][b]);\
    swap(heap[code][a], heap[code][b]);\
}
void sort(bool code, int heapNum, int loc) {
    for (; loc && heap[code][loc] < heap[code][root(loc)]; loc = root(loc))
        swap(loc, root(loc));
    int min = loc;
    do {
        loc = min;
        for (int i = 0; i < 2; i++)
            if ((loc + 1 << 1) - i < heapNum && heap[code][(loc + 1 << 1) - i] < heap[code][min])
                min = (loc + 1 << 1) - i;
        swap(loc, min);
    } while (loc != min);
}
#undef swap
int main() {
    int N;
    scanf("%d", &N);

    int heapNum = 0;
    for (int i = 0; i < N; i++) {
        char IHL;
        scanf(" %c", &IHL);

        if (IHL == 'I') {
            int pts;
            scanf("%d", &pts);

            heap[0][heapNum] = pts;
            heap[1][heapNum] = -pts;
            reflection[0][heapNum] = reflection[1][heapNum] = heapNum;
            heapNum++;
            sort(0, heapNum, heapNum - 1);
            sort(1, heapNum, heapNum - 1);
        } else if (heapNum) {
            bool H = IHL == 'H';
            printf("%d\n", H ? -heap[1][0] : heap[0][0]);
            reflection[H][reflection[!H][heapNum - 1]] = reflection[H][0];
            reflection[!H][reflection[H][0]] = reflection[!H][heapNum - 1];
            heap[!H][reflection[H][0]] = heap[!H][heapNum - 1];
            reflection[!H][reflection[H][heapNum - 1]] = 0;
            int loc = reflection[H][0];
            reflection[H][0] = reflection[H][heapNum - 1];
            heap[H][0] = heap[H][heapNum - 1];
            heapNum--;
            sort(H, heapNum, 0);
            sort(!H, heapNum, loc);
        } else
            printf("0\n");
    }

    return 0;
}
