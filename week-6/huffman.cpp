#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Node structure for Huffman tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Compare structure for min-heap
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Recursive preorder traversal to print Huffman codes
void preorder(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    // If it's a leaf node, store its code
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    preorder(root->left, code + "0", huffmanCodes);
    preorder(root->right, code + "1", huffmanCodes);
}

int main() {
    string S;
    int N;
    cout << "Enter characters (string of distinct chars): ";
    cin >> S;

    N = S.size();
    vector<int> freq(N);
    cout << "Enter frequencies for each character: ";
    for (int i = 0; i < N; i++) cin >> freq[i];

    // Build priority queue
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < N; i++) {
        pq.push(new Node(S[i], freq[i]));
    }

    // Build Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* merged = new Node('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node* root = pq.top();

    // Generate codes
    unordered_map<char, string> huffmanCodes;
    preorder(root, "", huffmanCodes);

    cout << "\nHuffman Codes (Preorder Traversal):\n";
    for (auto& ch : S) {
        cout << ch << ": " << huffmanCodes[ch] << endl;
    }

    return 0;
}
