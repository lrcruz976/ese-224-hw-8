
#include <iostream>
#include <string>
using namespace std;

template <typename Type>
class BinaryTree;

template <typename Type>
class Node {
private:
    friend class BinaryTree<Type>;

    Type data;
    Node<Type>* left;
    Node<Type>* right;

public:
    Node(const Type& value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }

    Type getData() const {
        return data;
    }

    Node<Type>* getLeft() const {
        return left;
    }

    Node<Type>* getRight() const {
        return right;
    }

    void setLeft(Node<Type>* child) {
        left = child;
    }

    void setRight(Node<Type>* child) {
        right = child;
    }
};

template <typename Type>
class BinaryTree {
private:
    Node<Type>* root;

    void insertHelper(Node<Type>*& current, const Type& value) {
        if (current == nullptr) {
            current = new Node<Type>(value);
        }
        else if (value < current->getData()) {
            insertHelper(current->left, value);
        }
        else if (value > current->getData()) {
            insertHelper(current->right, value);
        }
        // duplicate values are ignored
    }

    bool containsHelper(Node<Type>* current, const Type& value) const {
        if (current == nullptr) {
            return false;
        }

        if (value == current->getData()) {
            return true;
        }
        else if (value < current->getData()) {
            return containsHelper(current->left, value);
        }
        else {
            return containsHelper(current->right, value);
        }
    }

    void printHelper(Node<Type>* current, ostream& out, bool& first) const {
        if (current == nullptr) {
            return;
        }

        printHelper(current->left, out, first);

        if (!first) {
            out << " ";
        }

        out << current->getData();
        first = false;

        printHelper(current->right, out, first);
    }

    void clearHelper(Node<Type>*& current) {
        if (current == nullptr) {
            return;
        }

        clearHelper(current->left);
        clearHelper(current->right);

        delete current;
        current = nullptr;
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    ~BinaryTree() {
        clear();
    }

    bool empty() const {
        return root == nullptr;
    }

    void insert(const Type& value) {
        insertHelper(root, value);
    }

    bool contains(const Type& value) const {
        return containsHelper(root, value);
    }

    bool minimum(Type& result) const {
        if (root == nullptr) {
            return false;
        }

        Node<Type>* current = root;

        while (current->getLeft() != nullptr) {
            current = current->getLeft();
        }

        result = current->getData();
        return true;
    }

    bool maximum(Type& result) const {
        if (root == nullptr) {
            return false;
        }

        Node<Type>* current = root;

        while (current->getRight() != nullptr) {
            current = current->getRight();
        }

        result = current->getData();
        return true;
    }

    void printInOrder(ostream& out) const {
        if (root == nullptr) {
            out << "(empty)";
            return;
        }

        bool first = true;
        printHelper(root, out, first);
    }

    void clear() {
        clearHelper(root);
    }
};

int main() {
    string type;
    int n;

    cin >> type;
    cin >> n;

    if (type == "INT") {
        BinaryTree<int> tree;

        cout << boolalpha;
        cout << "Empty before insert: " << tree.empty() << endl;

        for (int i = 0; i < n; i++) {
            int value;
            cin >> value;
            tree.insert(value);
        }

        int searchValue;
        cin >> searchValue;

        cout << "Inorder: ";
        tree.printInOrder(cout);
        cout << endl;

        int result;

        if (tree.minimum(result)) {
            cout << "Minimum: " << result << endl;
        }

        if (tree.maximum(result)) {
            cout << "Maximum: " << result << endl;
        }

        cout << "Contains " << searchValue << ": "
             << tree.contains(searchValue) << endl;

        tree.clear();

        cout << "Empty after clear: " << tree.empty() << endl;

        if (tree.minimum(result)) {
            cout << "Minimum after clear: " << result << endl;
        }
        else {
            cout << "Minimum after clear: none" << endl;
        }

        if (tree.maximum(result)) {
            cout << "Maximum after clear: " << result << endl;
        }
        else {
            cout << "Maximum after clear: none" << endl;
        }

        cout << "Contains after clear: "
             << tree.contains(searchValue) << endl;

        tree.insert(99);

        cout << "After reuse: ";
        tree.printInOrder(cout);
        cout << endl;
    }
    else if (type == "STRING") {
        BinaryTree<string> tree;

        cout << boolalpha;
        cout << "Empty before insert: " << tree.empty() << endl;

        for (int i = 0; i < n; i++) {
            string value;
            cin >> value;
            tree.insert(value);
        }

        string searchValue;
        cin >> searchValue;

        cout << "Inorder: ";
        tree.printInOrder(cout);
        cout << endl;

        string result;

        if (tree.minimum(result)) {
            cout << "Minimum: " << result << endl;
        }

        if (tree.maximum(result)) {
            cout << "Maximum: " << result << endl;
        }

        cout << "Contains " << searchValue << ": "
             << tree.contains(searchValue) << endl;

        tree.clear();

        cout << "Empty after clear: " << tree.empty() << endl;

        if (tree.minimum(result)) {
            cout << "Minimum after clear: " << result << endl;
        }
        else {
            cout << "Minimum after clear: none" << endl;
        }

        if (tree.maximum(result)) {
            cout << "Maximum after clear: " << result << endl;
        }
        else {
            cout << "Maximum after clear: none" << endl;
        }

        cout << "Contains after clear: "
             << tree.contains(searchValue) << endl;

        tree.insert("reset");

        cout << "After reuse: ";
        tree.printInOrder(cout);
        cout << endl;
    }

    return 0;
}

