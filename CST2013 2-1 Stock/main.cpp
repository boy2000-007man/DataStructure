#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

//  int(log10(2^31 - 1) + 1) + 1 + int(log10(10^3 - 1) + 1) + 1 = 15
const int DX_LENGTH = 15;
struct Stock {
    int X;
    Stock *prev, *next;
};
struct StockTop {
    int X, num;
    StockTop *prev, *next;
};
template <typename T>
void deleteHead(T *head) {
    head->next = head->next->next;
    delete head->next->prev;
    head->next->prev = head;
}
template <typename T>
void addEnd(T *end) {
    end->prev->next = new T;
    end->prev->next->next = end;
    end->prev->next->prev = end->prev;
    end->prev = end->prev->next;
}
int main() {
    int N;
    scanf("%d", &N);

    double sum = 0.0;
    int currentDay = 0;
    Stock *stockHead = new Stock, *stockEnd = new Stock;
    stockHead->next = stockEnd;
    stockEnd->prev = stockHead;
    StockTop *topHead = new StockTop, *topEnd = new StockTop;
    topHead->next = topEnd;
    topEnd->prev = topHead;
    topHead->next->X = 0;
    for (int i = 0, lastDay = -1; i < N << 1; i++) {
        char DX[DX_LENGTH];
        scanf(" %[^\n]", DX);
        currentDay += atoi(DX);
        if (lastDay == -1)
            lastDay = currentDay;
        if (strchr(DX, ' ') == NULL) {
            topHead->next->num--;
            if (topHead->next->num == 0) {
                sum += (currentDay - lastDay) * topHead->next->X;
                lastDay = currentDay;
                deleteHead(topHead);
            }
            deleteHead(stockHead);
        } else {
            addEnd(stockEnd);
            stockEnd->prev->X = atoi(strchr(DX, ' '));
            if (topHead->next->X < stockEnd->prev->X) {
                sum += (currentDay - lastDay) * topHead->next->X;
                lastDay = currentDay;
            }
            int num = 1;
            while (topEnd->prev != topHead && topEnd->prev->X < stockEnd->prev->X) {
                num += topEnd->prev->num;
                deleteHead(topEnd->prev->prev);
            }
            addEnd(topEnd);
            topEnd->prev->X = stockEnd->prev->X;
            topEnd->prev->num = num;
        }
    }
    printf("%.2lf\n", sum / currentDay);

    return 0;
}
