#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
using namespace std;

const int n_MAX = 500000;
char mM[n_MAX + 1];
int edge[n_MAX], revEdge[n_MAX],
    heap[n_MAX], reflection[n_MAX],
    GG[n_MAX],
    DFN[n_MAX], LOW[n_MAX], link[n_MAX],
    set[n_MAX], value[n_MAX],
    MM[n_MAX];
const int m_MAX = 1200000;
int point[m_MAX], next[m_MAX],
    revPoint[m_MAX], revNext[m_MAX],
    stack[n_MAX + m_MAX];
//  int(log10(n) + 1) + 1 + int(log10(n) + 1) = 13
const int uv_LENGTH = 13;

#define moon(mM) ((mM) == 'M')
#define money(mM) ((mM) == 'm')
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))
template <typename T> void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
int main() {
    int n, m;
    scanf("%d%d\n", &n, &m);
    gets(mM);
    for (int i = 0; i < n; i++)
        revEdge[i] = edge[i] = -1;
    for (int i = 0; i < m; i++) {
        char uv[uv_LENGTH + 1];
        gets(uv);
        int u = atoi(uv), v = atoi(strchr(uv, ' '));
        point[i] = v;
        next[i] = edge[u];
        edge[u] = i;
        revPoint[i] = u;
        revNext[i] = revEdge[v];
        revEdge[v] = i;
    }

    int heapNum = 0;    // Dijkstra with binary heap, O((n + m) * log(n))
    GG[0] = moon(mM[0]);
    for (int i = 1; i < n; i++)
        GG[heap[reflection[i] = heapNum++] = i] = n;
    for (int u = 0; u != n - 1; ) {
        for (int i = edge[u]; i != -1; i = next[i]) {
            int v = point[i];
            if (GG[u] + moon(mM[v]) < GG[v]) {
                GG[v] = GG[u] + moon(mM[v]);
                for (int loc = reflection[v]; loc && GG[heap[loc]] < GG[heap[loc - 1 >> 1]]; loc = loc - 1 >> 1) {
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
                if ((root + 1 << 1) - i < heapNum && GG[heap[(root + 1 << 1) - i]] < GG[heap[min]])
                    min = (root + 1 << 1) - i;
            swap(reflection[heap[min]], reflection[heap[root]]);
            swap(heap[min], heap[root]);
        } while (root != min);
    }
    printf("%d\n", GG[n - 1]);

    for (int i = 0; i < n; i++) // Tarjan, O(n + m)
        set[i] = DFN[i] = -1;
    int stackNum = 0;
    stack[stackNum++] = 0;
    for (int time = 0, linkNum = 0; stackNum; ) {
        int u = stack[stackNum - 1];
        if (set[u] != -1)
            stackNum--;
        else {
            if (DFN[u] == -1)
                LOW[link[linkNum++] = u] = DFN[u] = time++;
            bool end = true;
            for (int i = edge[u]; i != -1; i = next[i]) {
                int v = point[i];
                if (DFN[v] == -1) {
                    stack[stackNum++] = v;
                    end = false;
                } else if (set[v] == -1)
                    LOW[u] = min(LOW[u], LOW[v]);
            }
            if (end) {
                stackNum--;
                if (LOW[u] == DFN[u]) {
                    value[set[u] = u] = money(mM[u]);
                    while (u != link[--linkNum]) {
                        int v = link[linkNum];
                        value[set[v] = u] += money(mM[v]);
                        if (revEdge[v] != -1) {
                            int tmp = revEdge[v];
                            while (revNext[tmp] != -1)
                                tmp = revNext[tmp];
                            revNext[tmp] = revEdge[u];
                            revEdge[u] = revEdge[v];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) // DP, O(n + m)
        if (i == set[i])
            MM[i] = -1;
    MM[set[0]] = value[set[0]];
    stackNum = 0;
    stack[stackNum++] = set[n - 1];
    while (stackNum) {
        int V = stack[stackNum - 1];
        bool end = true;
        if (MM[V] == -1) {
            for (int i = revEdge[V]; i != -1; i = revNext[i]) {
                int U = set[revPoint[i]];
                if (U != V && U != -1) {
                    if (MM[U] == -1) {
                        stack[stackNum++] = U;
                        end = false;
                    } else if (end)
                        MM[V] = max(MM[V], MM[U] + value[V]);
                }
            }
        }
        if (!end)
            MM[V] = -1;
        else
            stackNum--;
    }
    printf("%d\n", MM[set[n - 1]]);

    return 0;
}
