#include <iostream>

using std::cout;
using std::endl;

struct Node {
    int data;
    int height;
    Node *left;
    Node *right;
    Node(int val) : data(val), height(1), left(nullptr), right(nullptr){};
};

int max(int a, int b) { return (a > b ? a : b); }

int getHeight(Node *root) {
    if (!root) {
        return 0;
    }
    return root->height;
}

void updateHeight(Node *root) {
    if (!root) {
        return;
    }
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalanceFact(Node *root) {
    if (!root) {
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}

Node *RightRotate(Node *x) {
    Node *y = x->left;
    Node *z = y->right;
    y->right = x;
    x->left = z;
    return y;
}

Node *LeftRotate(Node *x) {
    Node *y = x->right;
    Node *z = y->left;
    y->left = x;
    x->right = z;
    return y;
}

Node *insert(Node *root, int val) {
    if (!root) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    } else {
        return root;
    }
    updateHeight(root);
    int fact = getBalanceFact(root);
    if (fact > 1 && val < root->left->data) {
        RightRotate(root);
    } else if (fact < -1 && val > root->right->data) {
        LeftRotate(root);
    } else if (fact > 1 && val > root->left->data) {
        LeftRotate(root->left);
        RightRotate(root);
    } else if (fact < -1 && val < root->right->data) {
        RightRotate(root->right);
        LeftRotate(root);
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
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            if (temp) {
                *root = *temp;
                delete temp;
            } else {
                return nullptr;
            }
        } else {
            Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }
    updateHeight(root);
    int fact = getBalanceFact(root);
    if (fact > 1 && val < root->left->data) {
        RightRotate(root);
    } else if (fact < -1 && val > root->right->data) {
        LeftRotate(root);
    } else if (fact > 1 && val > root->left->data) {
        LeftRotate(root->left);
        RightRotate(root);
    } else if (fact < -1 && val < root->right->data) {
        RightRotate(root->right);
        LeftRotate(root);
    }
    return root;
}

void display(Node *root) {
    if (root) {
        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }
    cout << endl;
}

