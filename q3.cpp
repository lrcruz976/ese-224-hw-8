#include <iostream>
using namespace std;

template <typename Type>
struct ListNode {
    Type value;
    ListNode<Type>* next;
};

template <typename Type>
class Node {
private:
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

    // need these to change the child pointers in recursive functions
    Node<Type>*& getLeftRef() {
        return left;
    }

    Node<Type>*& getRightRef() {
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
        if(current == nullptr) {
            current = new Node<Type>(value);
        }
        else if(value < current->getData()) {
            insertHelper(current->getLeftRef(), value);
        }
        else if(value > current->getData()) {
            insertHelper(current->getRightRef(), value);
        }
        // duplicates are ignored
    }

    void printHelper(Node<Type>* current, ostream& out, bool& first) const {
        if(current == nullptr) {
            return;
        }

        printHelper(current->getLeft(), out, first);

        if(!first) {
            out << " ";
        }

        out << current->getData();
        first = false;

        printHelper(current->getRight(), out, first);
    }

    void clearHelper(Node<Type>*& current) {
        if(current == nullptr) {
            return;
        }

        // clear the children first
        clearHelper(current->getLeftRef());
        clearHelper(current->getRightRef());

        delete current;
        current = nullptr;
    }

    // go through the tree in inorder and copy the values in range
    void copyHelper(Node<Type>* current, const Type& low, const Type& high,
                    ListNode<Type>*& head, ListNode<Type>*& tail) const {
        if(current == nullptr) {
            return;
        }

        // smaller values are on the left
        if(current->getData() > low) {
            copyHelper(current->getLeft(), low, high, head, tail);
        }

        // check if this value should be in the list
        if(current->getData() >= low && current->getData() <= high) {
            ListNode<Type>* temp = new ListNode<Type>;
            temp->value = current->getData();
            temp->next = nullptr;

            // if this is the first node, head and tail are the same
            if(head == nullptr) {
                head = temp;
                tail = temp;
            }
            else {
                tail->next = temp;
                tail = temp;
            }
        }

        // only look right if values there could be in range
        if(current->getData() < high) {
            copyHelper(current->getRight(), low, high, head, tail);
        }
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

    void printInOrder(ostream& out) const {
        if(root == nullptr) {
            out << "(empty)";
            return;
        }

        bool first = true;
        printHelper(root, out, first);
    }

    void clear() {
        clearHelper(root);
    }

    bool copyRangeToList(const Type& low, const Type& high,
                         ListNode<Type>*& head,
                         ListNode<Type>*& tail) const {
        // reversed range is not valid
        if(low > high) {
            return false;
        }

        copyHelper(root, low, high, head, tail);
        return true;
    }
};


// print the linked list
template <typename Type>
void printList(ListNode<Type>* head) {
    if(head == nullptr) {
        cout << "(empty)";
        return;
    }

    ListNode<Type>* current = head;

    while(current != nullptr) {
        cout << current->value << " -> ";
        current = current->next;
    }

    cout << "NULL";
}

// delete the list nodes separately from the tree
template <typename Type>
void clearList(ListNode<Type>*& head, ListNode<Type>*& tail) {
    while(head != nullptr) {
        ListNode<Type>* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
}


int main() {
    BinaryTree<int> tree;

    int n;
    cin >> n;

    int value;
    for(int i = 0; i < n; i++) {
        cin >> value;
        tree.insert(value);
    }

    int low, high;
    cin >> low >> high;

    ListNode<int>* head = nullptr;
    ListNode<int>* tail = nullptr;

    bool valid = tree.copyRangeToList(low, high, head, tail);

    cout << "Valid range: " << (valid ? "true" : "false") << endl;

    cout << "Tree before copy: ";
    tree.printInOrder(cout);
    cout << endl;

    cout << "Tree after copy: ";
    tree.printInOrder(cout);
    cout << endl;

    cout << "List: ";
    printList(head);
    cout << endl;

    // clearing the tree should not change the list
    tree.clear();

    cout << "Tree empty after clear: "
         << (tree.empty() ? "true" : "false") << endl;

    cout << "List after tree clear: ";
    printList(head);
    cout << endl;

    // list has its own nodes so delete them separately
    clearList(head, tail);

    return 0;
}