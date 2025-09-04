#include <iostream>
#include <vector>
using namespace std;

// Structure to store a non-zero element in sparse matrix
struct Element {
    int row;
    int col;
    int value;
};

class SparseMatrix {
private:
    int rows, cols;
    vector<Element> elements; // stores non-zero elements

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {}

    void addElement(int r, int c, int val) {
        if (val != 0) {
            elements.push_back({r, c, val});
        }
    }

    void display() {
        int k = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (k < elements.size() && elements[k].row == i && elements[k].col == j) {
                    cout << elements[k].value << " ";
                    k++;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }

    void displaySparse() {
        cout << "Row Col Value" << endl;
        for (auto &e : elements) {
            cout << e.row << "   " << e.col << "   " << e.value << endl;
        }
    }
};

int main() {
    // Example 4x5 sparse matrix
    SparseMatrix sm(4, 5);

    sm.addElement(0, 1, 5);
    sm.addElement(1, 3, 8);
    sm.addElement(2, 2, 10);
    sm.addElement(3, 0, 2);

    cout << "Sparse Matrix Representation (Triplets):" << endl;
    sm.displaySparse();

    cout << "\nFull Matrix Reconstruction:" << endl;
    sm.display();

    return 0;
}
