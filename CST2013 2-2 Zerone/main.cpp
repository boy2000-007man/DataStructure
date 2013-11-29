/*****************************************************************
* Author        : B
* Email         : boy2000_007man@163.com
* Last modified : 2013-11-30 00:24
* Filename      : main.cpp
* Description   : O(log(s01) * n)
*****************************************************************/
#include <cstdio>
using namespace std;

const int s01_LENGTH = 64;
const char *WINNER[2] = {"Adam", "Eve"};
struct Node {
    int winner;
    Node *root, *leaf[2];
    Node(Node *root_) {
        winner = -1;
        root = root_;
        leaf[0] = leaf[1] = NULL;
    }
};
void addLeaf(Node *root, char s01[]) {
    Node *leaf = root;
    for (int i = 0; s01[i] != '\0'; i++) {
        if (!leaf->leaf[s01[i] - '0'])
            leaf->leaf[s01[i] - '0'] = new Node(leaf);
        leaf = leaf->leaf[s01[i] - '0'];
    }
    if (leaf->winner == -1)
        do {
            leaf->winner = 1;
            for (int i = 0; i < 2; i++)
                if (leaf->leaf[i])
                    leaf->winner &= !leaf->leaf[i]->winner;
        } while (leaf = leaf->root);
}
int main() {
    int n;
    scanf("%d\n", &n);

    Node *root = new Node(NULL);
    for (int i = 0, winner = -1; i < n; i++) {
        char s01[s01_LENGTH + 1];
        gets(s01);

        addLeaf(root, s01);
        if (winner == -1)
            printf("%s %d", WINNER[winner = root->winner], i + 1);
        else if (winner != root->winner)
            printf(" %d\n%s %d", i, WINNER[winner = root->winner], i + 1);
    }
    printf(" %d\n", n);

    return 0;
}
