#include <cmath>
#include <cstdio>
using namespace std;

const int m_MAX = 1000;
int set[m_MAX],
    link[m_MAX],
    next[m_MAX];
const int n_MAX = 10000;
char wheel[m_MAX][n_MAX + 1];
const int primeNum = 0xFFFF + 1;
int prime[primeNum];
const int hashNum = 1000003;
int hashTable[hashNum];
unsigned int hash(char key[], int n) {
    int loc = 1;
    while (key[loc - 1] == key[loc])
        if (++loc == n)
            return prime[(key[0] * 0x100 + n) % primeNum];
    unsigned int res = 1;
    for (int i = 0, num = 0; i < n; i++)
        if (key[(loc + i) % n] == key[(loc + i + 1) % n])
            num++;
        else {
            res *= prime[(key[(loc + i) % n] * 0x100 + num) % primeNum];
            num = 0;
            res *= prime[key[(loc + i) % n] * 0x100 + key[(loc + i + 1) % n]];
        }
    return res;
}
#define min(a, b) ((a) < (b) ? (a) : (b))
int main() {
    int m, n;
    scanf("%d%d\n", &m, &n);

    for (int i = 1, k = prime[0] = 3; i < primeNum; prime[i++] = k)
        for (bool p = false; p = !p; )
            for (int j = 0, root = (int)sqrt(k += 2); prime[j] <= root && p; p = k % prime[j++]);

    for (int i = 0; i < hashNum; i++)
        hashTable[i] = -1;
    int linkNum = 0;
    for (int i = 0; i < m; i++) {
        gets(wheel[i]);

        set[i] = -1;
        int hashValue = hash(wheel[i], n) % hashNum;
        if (hashTable[hashValue] != -1) {
            int next[n];
            next[0] = 1;
            for (int j = 1; j < n; j++)
                for (next[j] = next[j - 1]; next[j] < j && wheel[i][j - 1] != wheel[i][j - 1 - next[j]]; next[j] += next[j - 1 - next[j]]);

            for (int j = hashTable[hashValue]; j != -1 && set[i] == -1; j = ::next[j])
                for (int loc = 0, match = 0; loc < n && set[i] == -1; )
                    if (match == n)
                        set[i] = link[j];
                    else if (wheel[link[j]][(loc + match) % n] == wheel[i][match])
                        match++;
                    else {
                        loc += next[match];
                        match -= min(match, next[match]);
                    }
        }
        if (set[i] == -1) {
            link[linkNum] = i;
            next[linkNum] = hashTable[hashValue];
            hashTable[hashValue] = linkNum++;
        }
        printf("%d\n", set[i] + 1);
    }

    return 0;
}
