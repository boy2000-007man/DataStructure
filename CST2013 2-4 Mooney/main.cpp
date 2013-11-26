#include <cstdio>
using namespace std;

const int n_MAX = 500000;
int edge[n_MAX];
char mM[n_MAX];
int GG[n_MAX];
int MM[n_MAX];
int DFN[n_MAX];
int LOW[n_MAX];
int link[n_MAX];
int set[n_MAX];
int value[n_MAX];
const int m_MAX = 1200000;
int point[m_MAX];
int next[m_MAX];
int stack[m_MAX];

#define moon(mM) ((mM) == 'M')
#define money(mM) ((mM) == 'm')
#define min(a, b) ((a) < (b) ? (a) : (b))
int main() {
    int n, m;
    scanf("%d%d%s", &n, &m, mM);
    for (int i = 0; i < n; i++)
        edge[i] = -1;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        point[i] = v;
        next[i] = edge[u];
        edge[u] = i;
    }

    GG[0] = moon(mM[0]);
    for (int i = 1; i < n; i++)
        GG[i] = n;
    int stackNum = 0;
    stack[stackNum++] = 0;
    while (stackNum) {
        int u = stack[--stackNum];
        for (int i = edge[u]; i != -1; i = next[i]) {
            int v = point[i];
            if (GG[u] + moon(mM[v]) < GG[v]) {
                GG[v] = GG[u] + moon(mM[v]);
                stack[stackNum++] = v;
            }
        }
    }
    printf("%d\n", GG[n - 1]);

    for (int i = 0; i < n; i++)
        DFN[i] = -1;
    for (int i = 0; i < n; i++)
        set[i] = -1;
    stackNum = 0;
    stack[stackNum++] = 0;
    int linkNum = 0;
    for (int time = 0; time < n || linkNum; ) {
        int u = stack[stackNum - 1];
        if (DFN[u] == -1) {
            LOW[u] = DFN[u] = time++;
            link[linkNum++] = u;
        }
        bool end = true;
        for (int i = edge[u]; i != -1; i = next[i]) {
            int v = point[i];
            if (DFN[v] == -1) {
                stack[stackNum++] = v;
                end = false;
            } else if (set[v] == -1)
                LOW[u] = min(LOW[u], LOW[v]);
        }
        if (!end)
            continue;
        stackNum--;
        if (LOW[u] == DFN[u]) {
            value[u] = 0;
            do {
                int v = link[linkNum - 1];
                value[u] += money(mM[v]);
                set[v] = u;
                if (u != v && edge[v] != -1) {
                    int tmp = edge[v];
                    while (next[tmp] != -1)
                        tmp = next[tmp];
                    next[tmp] = edge[u];
                    edge[u] = edge[v];
                }
            } while (u != link[--linkNum]);
        }
    }
    for (int i = 0; i < n; i++)
        if (set[i] == i)
            MM[i] = value[i];
    stackNum = 0;
    stack[stackNum++] = 0;
    while (stackNum) {
        int u = stack[--stackNum];
        for (int i = edge[u]; i != -1; i = next[i]) {
            int v = point[i];
            v = set[v];
            if (set[u] != set[v] && MM[set[v]] < MM[set[u]] + value[set[v]]) {
                MM[set[v]] = MM[set[u]] + value[set[v]];
                stack[stackNum++] = v;
            }
        }
    }
    printf("%d\n", MM[set[n - 1]]);

    return 0;
}
