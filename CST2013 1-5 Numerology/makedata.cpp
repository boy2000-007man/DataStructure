#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int N = 24;
    printf("%d %d\n", N, rand() + 1);
    for (int i = 0; i < N; i++)
        printf("%d ", rand() % 9 + 1);
    putchar('\n');
    return 0;
}
