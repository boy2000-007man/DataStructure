#include <cstdio>
#include <cstring>
using namespace std;

const int line_LENGTH = 1024 * 1024;
char line[line_LENGTH + 1];
char* getName(char line[]) {
    *strrchr(line, '\"') = '\0';
    return strchr(line, '\"') + 1;
}
int main() {
    while (!strstr(gets(line), "<Behavior>"));
    printf("{\"Behavior\":");
    for (bool hasBrother = false; !strstr(gets(line), "</Behavior>"); )
        if (strstr(line, "<Node")) {
            if (hasBrother) {
                putchar(',');
                hasBrother = false;
            }
            if (!strstr(line, "/>"))
                printf("{\"Name\":\"%s\",\"SonList\":[", getName(line));
            else {
                printf("{\"Name\":\"%s\"}", getName(line));
                hasBrother = true;
            }
        } else if (strstr(line, "</Node>")) {
            printf("]}");
            hasBrother = true;
        }
    printf("}\n");

    return 0;
}
