#include <cstdio>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    bool status[n + 1];
    for (int i = 0; i <= n; i++)
        status[i] = false;
    int stack[n];
    int num = 0, currentMax = n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &stack[num++]);
        status[stack[num - 1]] = true;
        while (status[currentMax])
            currentMax--;
        while (num && stack[num - 1] > currentMax)
            printf("%d ", stack[--num]);
    }
    putchar('\n');

    return 0;
}
