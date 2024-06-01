#include "blazingio.hpp"

using namespace std;

struct Node {
    string data;
    int count_left;
    Node* left;
    Node* right;
};

Node* new_Node(string x) {
    Node* new_node = new Node;
    new_node->data = x;
    new_node->count_left = 0;
    new_node->left = nullptr;
    new_node->right = nullptr;
    return new_node;
}

struct BST {

    Node* root = nullptr;

    void _insert(string x) {
        root = insert(x, root);
    }

    void _delete(string x) {
        root = method_delete(x, root);
    }

    void _find_k_min(int k) {
        string res = find_k_min(k, root);
        if (res != "-12345") {
            cout << res << '\n';
        }
    }

private:

    Node* insert(string x, Node* node) {
        if (node == nullptr) {
            node = new_Node(x);
        } else if (x < node->data) {
            node->left = insert(x, node->left);
            ++node->count_left;
        } else if (x > node->data) {
            node->right = insert(x, node->right);
        }
        else if (x == node->data) {
            ++node->count_left;
            node->left = insert(x, node->left);
        }
        return node;
    }

    Node* method_delete(string x, Node* node) {
        Node* temp;
        if (node == nullptr) {
            return nullptr;
        } else if (x < node->data) {
            node->left = method_delete(x, node->left);
            --node->count_left;
        } else if (x > node->data) {
            node->right = method_delete(x, node->right);
        } else if (node->left != nullptr && node->right != nullptr) {
            temp = find_min(node->right);
            node->data = temp->data;
            node->right = method_delete(node->data, node->right);
        } else {
            temp = node;
            if (node->left == nullptr) {
                node = node->right;
            } else if (node->right == nullptr) {
                node = node->left;
            }
            delete temp;
        }
        return node;
    }

    Node* find_min(Node* node) {
        if (node == nullptr) {
            return nullptr;
        } else if (node->left == nullptr) {
            return node;
        } else {
            return find_min(node->left);
        }
    }

    string find_k_min(int k, Node* node) {
        if (node == nullptr) {
            return "-12345";
        } else if (k < node->count_left) {
            return find_k_min(k, node->left);
        } else if (k > node->count_left) {
            return find_k_min(k - node->count_left - 1, node->right);
        } else {
            return node->data;
        }
    }

};

int main() {
    int n;
    cin >> n;

    BST library;

    for (int i = 0; i < n; ++i) {
        string input;
        cin >> input;

        if (isdigit(input[0])) {
            library._find_k_min(stoi(input) - 1);
        } else {
            library._insert(input);
        }
    }

    return 0;
}
