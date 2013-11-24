#include <cstdio>
using namespace std;

const int n_MAX = 500000;
int edge[n_MAX];
char mM[n_MAX];
int GG[n_MAX];
const int m_MAX = 1200000;
int point[m_MAX];
int next[m_MAX];

#define moon(mM) (mM == 'M')
#define min(a, b) ((a) < (b) ? (a) : (b))
int main() {
    int n, m;
    scanf("%d%d%s", &n, &m, mM);
    for (int i = 0; i < n; i++)
        edge[i] = -1;
    GG[0] = moon(mM[0]);
    for (int i = 1; i < n; i++)
        GG[i] = n;
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        GG[v] = min(GG[v], GG[u] + moon(mM[v]));
        point[i] = v;
        next[i] = edge[u];
        edge[u] = i;
    }
    printf("%d\n", GG[n - 1]);
    return 0;
}
