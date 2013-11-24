#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

string getName(const string &line) {
    int start = line.find_first_of('\"'), end = line.find_last_of('\"');
    return line.substr(start, end - start + 1);
}
int main() {
    string line;
    while (getline(cin, line) && line.find("<Behavior>") == string::npos);
    printf("{\"Behavior\":");
    for (bool hasBrother = false; getline(cin, line) && line.find("</Behavior>") == string::npos; )
        if (line.find("<Node") != string::npos) {
            if (hasBrother) {
                putchar(',');
                hasBrother = false;
            }
            printf("{\"Name\":%s", getName(line).c_str());
            if (line.find("/>") == string::npos)
                printf(",\"SonList\":[");
            else {
                putchar('}');
                hasBrother = true;
            }
        } else if (line.find("</Node>") != string::npos) {
            printf("]}");
            hasBrother = true;
        }
    printf("}\n");
    return 0;
}
