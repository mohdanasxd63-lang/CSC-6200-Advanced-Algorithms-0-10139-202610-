#include <iostream>
using namespace std;

// Node structure for Linked List
struct Node {
    int row, col, value;
    Node* next;
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols;
    Node* head; // head of linked list

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), head(nullptr) {}

    // Insert a new non-zero element
    void insert(int r, int c, int val) {
        if (val == 0) return; // skip zeroes
        Node* newNode = new Node(r, c, val);

        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Display linked list representation
    void displayList() {
        cout << "Row Col Value" << endl;
        Node* temp = head;
        while (temp) {
            cout << temp->row << "   " << temp->col << "   " << temp->value << endl;
            temp = temp->next;
        }
    }

    // Display full matrix
    void displayMatrix() {
        Node* temp = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (temp && temp->row == i && temp->col == j) {
                    cout << temp->value << " ";
                    temp = temp->next;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    // Example 4x5 sparse matrix
    SparseMatrix sm(4, 5);

    sm.insert(0, 1, 5);
    sm.insert(1, 3, 8);
    sm.insert(2, 2, 10);
    sm.insert(3, 0, 2);

    cout << "Linked List Representation:" << endl;
    sm.displayList();

    cout << "\nFull Matrix Reconstruction:" << endl;
    sm.displayMatrix();

    return 0;
}
