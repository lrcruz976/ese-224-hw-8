
#include <iostream>
using namespace std;

struct FlagNode {
    unsigned int flags;
    FlagNode* next;
};

class FlagList {
private:
    FlagNode* head;
    FlagNode* tail;

public:
    FlagList() {
        head = nullptr;
        tail = nullptr;
    }

    ~FlagList() {
        FlagNode* current = head;

        // delete each node one at a time
        while(current != nullptr) {
            FlagNode* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
    }

    void append(unsigned int flags) {
        FlagNode* temp = new FlagNode;
        temp->flags = flags;
        temp->next = nullptr;

        // if the list is empty, this is the first node
        if(head == nullptr) {
            head = temp;
            tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
    }

    void makeReady() {
        FlagNode* current = head;

        while(current != nullptr) {
            // bit 2 is locked, so dont change locked nodes
            if((current->flags & 4) == 0) {
                // set bit 0 to 1 without changing the other bits
                current->flags = current->flags | 1;
            }

            current = current->next;
        }
    }

    void toggleSelected() {
        FlagNode* current = head;

        while(current != nullptr) {
            // only ready and unlocked nodes can be changed
            if((current->flags & 1) != 0 &&
               (current->flags & 4) == 0) {
                // xor flips bit 1
                current->flags = current->flags ^ 2;
            }

            current = current->next;
        }
    }

    void printForward(ostream& out) const {
        if(head == nullptr) {
            out << "(empty)";
            return;
        }

        FlagNode* current = head;

        while(current != nullptr) {
            out << current->flags;

            if(current->next != nullptr) {
                out << " ";
            }

            current = current->next;
        }
    }

    int countReady() const {
        int count = 0;
        FlagNode* current = head;

        while(current != nullptr) {
            if((current->flags & 1) != 0) {
                count++;
            }

            current = current->next;
        }

        return count;
    }

    int countSelected() const {
        int count = 0;
        FlagNode* current = head;

        while(current != nullptr) {
            if((current->flags & 2) != 0) {
                count++;
            }

            current = current->next;
        }

        return count;
    }

    int countLocked() const {
        int count = 0;
        FlagNode* current = head;

        while(current != nullptr) {
            if((current->flags & 4) != 0) {
                count++;
            }

            current = current->next;
        }

        return count;
    }
};


int main() {
    FlagList list;
    int n;
    cin >> n;

    unsigned int flags;

    for(int i = 0; i < n; i++) {
        cin >> flags;
        list.append(flags);
    }

    cout << "Initial: ";
    list.printForward(cout);
    cout << endl;

    list.makeReady();

    cout << "Ready: ";
    list.printForward(cout);
    cout << endl;

    list.toggleSelected();

    cout << "Selected: ";
    list.printForward(cout);
    cout << endl;

    list.toggleSelected();

    cout << "Selected again: ";
    list.printForward(cout);
    cout << endl;

    cout << "Ready count: " << list.countReady() << endl;
    cout << "Selected count: " << list.countSelected() << endl;
    cout << "Locked count: " << list.countLocked() << endl;

    return 0;
}
