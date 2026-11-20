
#include <iostream>
using namespace std;

class FourBit {
private:
    unsigned int value;

public:
    // default value is 0
    FourBit() {
        value = 0;
    }

    FourBit(unsigned int initial) {
        value = initial;
    }

    unsigned int getValue() const {
        return value;
    }

    FourBit operator|(const FourBit& other) const {
        return FourBit(value | other.value);
    }

    FourBit operator&(const FourBit& other) const {
        return FourBit(value & other.value);
    }

    FourBit operator^(const FourBit& other) const {
        return FourBit(value ^ other.value);
    }

    FourBit operator~() const {
        // only flip the last 4 bits
        return FourBit((~value) & 15);
    }

    void print(ostream& out) const {
        out << value << " ";

        // print bits from left to right
        for(int i = 3; i >= 0; i--) {
            if(value & (1u << i)) {
                out << "1";
            }
            else {
                out << "0";
            }
        }
    }
};

int main() {
    unsigned int a, b;
    cin >> a >> b;

    FourBit A(a);
    FourBit B(b);

    cout << "A: ";
    A.print(cout);
    cout << endl;

    cout << "B: ";
    B.print(cout);
    cout << endl;

    cout << "A | B: ";
    (A | B).print(cout);
    cout << endl;

    cout << "A & B: ";
    (A & B).print(cout);
    cout << endl;

    cout << "A ^ B: ";
    (A ^ B).print(cout);
    cout << endl;

    cout << "~A: ";
    (~A).print(cout);
    cout << endl;

    cout << "(A | B) & ~B: ";
    ((A | B) & ~B).print(cout);
    cout << endl;

    // check that the original objects are still the same
    cout << "A unchanged: ";
    A.print(cout);
    cout << endl;

    cout << "B unchanged: ";
    B.print(cout);
    cout << endl;

    return 0;
}
