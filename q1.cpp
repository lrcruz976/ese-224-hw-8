
#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* makeNode(int value) {
    TreeNode* temp = new TreeNode;
    temp->data = value;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

void printAtLevel(const TreeNode* root, int level) {
    if(root == nullptr || level < 0) {
        return;
    }

    // level 0 means we found the node we want
    if(level == 0) {
        cout << root->data << " ";
        return;
    }

    // go down one level on each side
    printAtLevel(root->left, level - 1);
    printAtLevel(root->right, level - 1);
}

int countAtLevel(const TreeNode* root, int level) {
    if(root == nullptr || level < 0) {
        return 0;
    }

    if(level == 0) {
        return 1;
    }

    // add the number of nodes on both sides
    return countAtLevel(root->left, level - 1) +
           countAtLevel(root->right, level - 1);
}

int sumAtLevel(const TreeNode* root, int level) {
    if(root == nullptr || level < 0) {
        return 0;
    }

    if(level == 0) {
        return root->data;
    }

    // add the sums returned by the two recursive calls
    return sumAtLevel(root->left, level - 1) +
           sumAtLevel(root->right, level - 1);
}

void clearTree(TreeNode*& root) {
    if(root == nullptr) {
        return;
    }

    // delete the children first
    clearTree(root->left);
    clearTree(root->right);

    delete root;
    root = nullptr;
}

TreeNode* buildTree(string name) {
    if(name == "EMPTY") {
        return nullptr;
    }

    if(name == "SINGLE") {
        return makeNode(-6);
    }

    if(name == "ZERO") {
        return makeNode(0);
    }

    // build the common part of tree A and tree B
    TreeNode* root = makeNode(18);

    root->left = makeNode(7);
    root->right = makeNode(31);

    root->left->right = makeNode(12);

    root->right->left = makeNode(24);
    root->right->right = makeNode(40);

    // tree A has node 27, but tree B does not
    if(name == "A") {
        root->right->left->right = makeNode(27);
    }

    return root;
}

int main() {
    string name;
    int q;

    cin >> name;
    cin >> q;

    TreeNode* root = buildTree(name);

    cout << "Tree: " << name << endl;

    for(int i = 0; i < q; i++) {
        int level;
        cin >> level;

        cout << "Level " << level << ": ";
        printAtLevel(root, level);

        // printAtLevel prints a space after each value
        cout << "| Count: " << countAtLevel(root, level);
        cout << " | Sum: " << sumAtLevel(root, level) << endl;
    }

    clearTree(root);

    return 0;
}
