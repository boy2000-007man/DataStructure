#include <cmath>
#include <cstdio>
using namespace std;

const int m_MAX = 1000;
int set[m_MAX],
    link[m_MAX],
    linkNext[m_MAX];
const int n_MAX = 10000;
char wheel[m_MAX][n_MAX + 1];
const int primeNum = 0x10000;
int prime[primeNum];
const int hashNum = 0xFFFFFF;
int hash[hashNum];
int repeat(char trace[], int n, int loc) {
    for (int i = 1; i < n; i++)
        if (trace[(loc + i - 1) % n] != trace[(loc + i) % n])
            return i;
    return n;
}
int main() {
    int m, n;
    scanf("%d%d\n", &m, &n);

    prime[0] = 2;
    for (int i = 1, k = 3; i < primeNum; k += 2) {
        bool p = true;
        for (int j = 0, root = (int)sqrt(k); prime[j] <= root && p; j++)
            p = k % prime[j];
        if (p)
            prime[i++] = k;
    }

    for (int i = 0; i < hashNum; i++)
        hash[i] = -1;
    int linkNum = 0;
    for (int i = 0; i < m; i++) {
        gets(wheel[i]);

        unsigned int hashValue = 1;
        for (int j = 0; j < n; j++)
            hashValue *= prime[(wheel[i][j] << 8) + wheel[i][(j + 1) % n]];
        hashValue &= 0xFFF000;
        unsigned int tmp = wheel[i][0] != wheel[i][n - 1] ? prime[repeat(wheel[i], n, 0)] : 1;
        for (int j = repeat(wheel[i], n, 0), k; j < n; j += k) {
            k = repeat(wheel[i], n, j);
            tmp *= prime[k];
        }
        hashValue |= 0x000FFF & tmp;

        set[i] = -1;
        if (hash[hashValue] != -1) {
            int next[n];
            next[0] = 1;
            for (int j = 1; j < n; j++) {
                next[j] = next[j - 1];
                for (bool match = true; match = !match; )
                    for (int k = 0; k + next[j] < j && match; k++)
                        if (wheel[i][k] != wheel[i][k + next[j]]) {
                            next[j] += next[k];
                            match = false;
                        }
            }

            for (int j = hash[hashValue]; j != -1 && set[i] == -1; j = linkNext[j]) {
                int loc = 0;
                for (int k = 0; k < n; k++)
                    while (loc <= k && wheel[link[j]][k] != wheel[i][k - loc])
                        loc += next[k - loc];
                if (loc < n) {
                    bool match = true;
                    for (int k = 0; k < loc && match; k++)
                        match = wheel[link[j]][k] == wheel[i][n - loc + k];
                    if (match)
                        set[i] = link[j];
                }
            }
        }
        if (set[i] == -1) {
            link[linkNum] = i;
            linkNext[linkNum] = hash[hashValue];
            hash[hashValue] = linkNum++;
        }
        printf("%d\n", set[i] + 1);
    }

    return 0;
}
