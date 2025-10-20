#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using std::cerr;
using std::endl;
using std::getline;
using std::ifstream;
using std::map;
using std::priority_queue;
using std::string;
using std::vector;

struct Node {
    char data;
    int weight;
    Node *left;
    Node *right;
    Node(char s, int w) : data(s), weight(w), left(nullptr), right(nullptr){};
};

struct CompareNode {
    bool operator()(Node *a, Node *b) { return a->weight > b->weight; }
};

map<char, int> getFrequency(const string &filepath) {
    ifstream fin(filepath);
    if (!fin.is_open()) {
        cerr << "error" << endl;
        return map<char, int>();
    }
    string line;
    map<char, int> frequency;
    while (getline(fin, line)) {
        for (char c : line) {
            if (isalpha(c)) {
                c = tolower(c);
                frequency[c]++;
            }
        }
    }
    fin.close();
    return frequency;
}

Node *Build_HuffmanTree(const map<char, int> &frequency) {
    priority_queue<Node *, vector<Node *>, CompareNode> minheap;
    for (const auto &pair : frequency) {
        minheap.push(new Node(pair.first, pair.second));
    }
    while (minheap.size() > 1) {
        Node *left = minheap.top();
        minheap.pop();
        Node *right = minheap.top();
        minheap.pop();
        Node *new_node = new Node('\0', left->weight + right->weight);
        minheap.push(new_node);
    }
    return minheap.top();
}

void getCode(Node *root, const string &code, map<char, string> &huffman_code) {
    if (!root) {
        return;
    }
    if (!root->left && !root->right) {
        huffman_code[root->data] = code;
        return;
    }
    getCode(root->left, code + "0", huffman_code);
    getCode(root->right, code + "1", huffman_code);
}

