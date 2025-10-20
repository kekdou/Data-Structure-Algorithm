#include <iostream>
#include <queue>
#include <stack>

using std::cout;
using std::endl;

struct Node {
    int data;
    Node *left;
    Node *right;
    Node(int val) : data(val), left(nullptr), right(nullptr){};
};

Node *insert(Node *root, int val) {
    if (!root) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

Node *findMin(Node *root) {
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

Node *remove(Node *root, int val) {
    if (!root) {
        return NULL;
    }
    if (val < root->data) {
        root->left = remove(root->left, val);
    } else if (val > root->data) {
        root->right = remove(root->right, val);
    } else {
        if (!root->left) {
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node *temp = root->left;
            delete root;
            return temp;
        } else {
            Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }
    return root;
}

void pre_order(Node *root) {
    if (!root) {
        return;
    }
    std::stack<Node *> s;
    s.push(root);
    while (!s.empty()) {
        Node *cur_node = s.top();
        s.pop();
        cout << cur_node->data << " ";
        if (cur_node->right) {
            s.push(cur_node->right);
        }
        if (cur_node->left) {
            s.push(cur_node->left);
        }
    }
    cout << endl;
}

void in_order(Node *root) {
    if (!root) {
        return;
    }
    std::stack<Node *> s;
    Node *cur_node = root;
    while (cur_node || !s.empty()) {
        while (cur_node) {
            s.push(cur_node);
            cur_node = cur_node->left;
        }
        cur_node = s.top();
        s.pop();
        cout << cur_node->data << " ";
        cur_node = cur_node->right;
    }
    cout << endl;
}

void post_order(Node *root) {
    if (!root) {
        return;
    }
    std::stack<Node *> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node *cur_node = s1.top();
        s1.pop();
        s2.push(cur_node);
        if (cur_node->left) {
            s1.push(cur_node->left);
        }
        if (cur_node->right) {
            s1.push(cur_node->right);
        }
    }
    while (!s2.empty()) {
        Node *cur_node = s2.top();
        cout << cur_node->data << " ";
        s2.pop();
    }
    cout << endl;
}

void level_order(Node *root) {
    if (!root) {
        return;
    }
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *cur_node = q.front();
        q.pop();
        cout << cur_node->data << " ";
        if (cur_node->left) {
            q.push(cur_node->left);
        }
        if (cur_node->right) {
            q.push(cur_node->right);
        }
    }
    cout << endl;
}

int Tree_Height(Node *root) {
    if (!root) {
        return 0;
    }
    int Left_Height = Tree_Height(root->left);
    int Right_Height = Tree_Height(root->right);
    return 1 + (Left_Height > Right_Height ? Left_Height : Right_Height);
}

int Tree_Node(Node *root) {
    if (!root) {
        return 0;
    }
    return 1 + Tree_Node(root->left) + Tree_Node(root->right);
}
