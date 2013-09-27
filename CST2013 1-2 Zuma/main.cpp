#include <cstdio>
using namespace std;

const int maxLength = 10000;

struct Bead {
    char type;
    Bead *prev, *next;
};

int main() {
    char initStatus[maxLength];
    scanf("%s", initStatus);
    if (initStatus[0] == '-')
        initStatus[0] = '\0';
    Bead *begin = new Bead;
    Bead *end = begin;
    for (int i = 0; ; i++) {
        Bead *tmp = end;
        end = new Bead;
        end->type = initStatus[i];
        end->prev = tmp;
        tmp->next = end;
        if (!initStatus[i])
            break;
    }

    int n;
    scanf("%d", &n);
    while (n--) {
        int k;
        char c;
        scanf("%d %c", &k, &c);
        Bead *loc = begin;
        while (k--)
            loc = loc->next;
        loc->next->prev = new Bead;
        loc->next->prev->type = c;
        loc->next->prev->prev = loc;
        loc->next->prev->next = loc->next;
        loc->next = loc->next->prev;

        loc = loc->next;
        for ( ; ; ) {
            int sameBeadNum = 1;
            Bead *prev = loc->prev;
            while (prev != begin && prev->type == loc->type) {
                prev = prev->prev;
                sameBeadNum++;
            }
            Bead *next = loc->next;
            while (next != end && next->type == loc->type) {
                next = next->next;
                sameBeadNum++;
            }
            if (sameBeadNum < 3)
                break;
            for (loc = prev->next; loc != next; loc = prev->next) {
                prev->next = loc->next;
                delete loc;
            }
            next->prev = prev;
            if (prev == begin && next == end)
                break;
            loc = (prev == begin ? next : prev);
        }
        if (begin->next == end)
            puts("-");
        else {
            for (Bead *tmp = begin->next; tmp != end; tmp = tmp->next)
                putchar(tmp->type);
            putchar('\n');
        }
    }

    for (Bead *tmp = begin->next; tmp != end; tmp = begin->next) {
        begin->next = tmp->next;
        delete tmp;
    }
    delete begin;
    delete end;

    return 0;
}
