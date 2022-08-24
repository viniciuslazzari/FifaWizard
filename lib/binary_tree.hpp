#ifndef binary_tree_h
#define binary_tree_h

#include <iostream>

int max(int a, int b) { return (a > b) ? a : b; }

template <typename TKey, class TData>
class Node {
    public:
        TKey key;
        int height;
        TData data;
        Node<TKey, TData>* left;
        Node<TKey, TData>* right;

        Node(TKey key, TData data);
};

template <typename TKey, class TData>
Node<TKey, TData>::Node(TKey key, TData data){
    this->key = key;
    this->height = 1;
    this->data = data;
    this->right = this->left = nullptr;
}

template <typename TKey, class TData>
int getHeight(Node<TKey, TData>* root) {
    return (root == nullptr) ? 0 : root->height;
}

template <typename TKey, class TData>
Node<TKey, TData>* rightRotate(Node<TKey, TData>* root) {
    Node<TKey, TData>* x = root->left;
    Node<TKey, TData>* T2 = x->right;

    x->right = root;
    root->left = T2;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

template <typename TKey, class TData>
Node<TKey, TData>* leftRotate(Node<TKey, TData>* root) {
    Node<TKey, TData>* y = root->right;
    Node<TKey, TData>* T2 = y->left;

    y->left = root;
    root->right = T2;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

template <typename TKey, class TData>
int getBalanceFactor(Node<TKey, TData>* root) {
    if (root == nullptr) return 0;

    return getHeight(root->left) - getHeight(root->right);
}

template <typename TKey, class TData>
Node<TKey, TData>* insertNode(Node<TKey, TData>* root, const TKey key, const TData data){
    if (root == nullptr) return new Node<TKey, TData>(key, data);

    if (root->key < key)
        root->right = insertNode(root->right, key, data);
    else
        root->left = insertNode(root->left, key, data);
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1) {
        if (key < root->left->key) return rightRotate(root);
        
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balanceFactor < -1) {
        if (key > root->right->key) return leftRotate(root);

        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <typename TKey, class TData>
Node<TKey, TData>* getNodeAddress(Node<TKey, TData>* root, const TKey key){
    if (root == nullptr) return nullptr;
    
    if (root->key == key) return root;

    if (root->key < key) return getNodeAddress(root->right, key);

    return getNodeAddress(root->left, key);
}

template <typename TKey, class TData>
void printTree(const std::string& prefix, Node<TKey, TData>* root, bool isLeft)
{
    if(root == nullptr) return;

    std::cout << prefix;
    std::cout << (isLeft ? "|--" : "L--" );
    std::cout << root->key << std::endl;

    printTree(prefix + (isLeft ? "|   " : "    "), root->left, true);
    printTree(prefix + (isLeft ? "|   " : "    "), root->right, false);
}

template <typename TKey, class TData>
void printTree(Node<TKey, TData>* root)
{
    printTree("", root, false);    
}

#endif