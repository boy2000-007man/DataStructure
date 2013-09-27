#include <cstdio>
#include <cmath>
using namespace std;

//const int MaxLength = int(log(pow(10, 10)) / log(2)) + 1;   // the length of 10^10 under binary
#define MaxLength 34

bool isPalindrome(long long int n, int k) {
    static int nInK[MaxLength];
    int length = 0;
    while (n) {
        nInK[length++] = n % k;
        n /= k;
    }
    for (int i = 0, j = length - 1; i < j; i++, j--)
        if (nInK[i] != nInK[j])
            return false;
    return true;
}
long long int palindromeAry(long long int n) {
    if (n == 0)
        return 2;
    if (n == 1 || n == 2)
        return n + 1;
    for (int i = 2; i <= sqrt(n); i++)
        if (isPalindrome(n, i))
            return i;
    for (int i = (int)sqrt(n); i > 0; i--)
        if (n % i == 0 && i < n / i - 1)
            return n / i - 1;
    printf("CAUTION: %lld not found ...\n", n);
    return -1;
}
int main() {
    int T = 1;
    scanf("%d", &T);
    while (T--) {
        long long int D;
        scanf("%lld", &D);
        printf("%lld\n", palindromeAry(D));
    }
}
