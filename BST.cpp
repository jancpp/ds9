/*
 Author: Jan Polzer
 File:   BST.cpp
 Date:   2/12/2018
 */

#include "BST.h"

BST::BST(): m_root(nullptr), m_size(0) {}
BST::~BST() {}

int BST::getSize() {
    return m_size;
}

void BST::SetRoot(Node *root) {
    m_root = root;
}

bool BST::insert(int value) {
    bool inserted = false;
    Node *newNode = new Node(value);
    m_root = InsertHelper(m_root, newNode);
    if (m_root != nullptr) {
        inserted = true;
        m_size++;
    }
    return inserted;
}

Node *BST::InsertHelper(Node *root, Node *newNode) {
    // Base case - empty tree
    if ( root == nullptr) {
        return newNode;
    } else if (newNode->value() < root->value()) {
        Node *temp = new Node();
        temp = InsertHelper(root->left(), newNode);
        root->setLeft(temp);
    } else {
        Node *temp = new Node();
        temp = InsertHelper(root->right(), newNode);
        root->setRight(temp);
    }
    return root;
}

bool BST::deletemin() {
    if (m_root == nullptr) {
        return false;
    } else {
        return DeleteMinHelper(m_root);
    }
}

bool BST::DeleteMinHelper(Node *parent) {
    bool deleted = false;
    if (m_size == 1){
        delete m_root;
        m_root = nullptr;
        deleted = true;
        m_size--;
    } else if ((parent->right() == nullptr) && (parent->left() != nullptr) && (parent->left()->left() == nullptr) && (parent->left()->right() == nullptr)) {
        delete parent->left();
        parent->setLeft(nullptr);
        deleted = true;
        m_size--;
    } else if (parent->left() == nullptr) {
        SetRoot(parent->right());
        deleted = true;
        m_size--;
    }
    else if ((parent->left()->left() == nullptr) && (parent->left()->right() != nullptr)) {
        parent->setLeft(parent->left()->right());
        deleted = true;
        m_size--;
    }
    else if ((parent->left()->left() == nullptr) && (parent->left()->right() == nullptr)) {
        delete parent->left();
        parent->setLeft(nullptr);
        deleted = true;
        m_size--;
    }else {
        return DeleteMinHelper(parent->left());
    }
    return deleted;
}

bool BST::DeleteMaxHelper(Node *parent) {
    bool deleted = false;
    if (m_size == 1){
        delete m_root;
        m_root = nullptr;
        deleted = true;
        m_size--;
    } else if ((parent->left() == nullptr) && (parent->right() != nullptr) && (parent->right()->right() == nullptr) && (parent->right()->left() == nullptr)) {
        delete parent->right();
        parent->setRight(nullptr);
        deleted = true;
        m_size--;
    } else if (parent->right() == nullptr) {
        SetRoot(parent->left());
        deleted = true;
        m_size--;
    }
    else if ((parent->right()->right() == nullptr) && (parent->right()->left() != nullptr)) {
        parent->setRight(parent->right()->left());
        deleted = true;
        m_size--;
    }
    else if ((parent->right()->right() == nullptr) && (parent->right()->left() == nullptr)) {
        delete parent->right();
        parent->setRight(nullptr);
        deleted = true;
        m_size--;
    }else {
        return DeleteMaxHelper(parent->right());
    }
    return deleted;
}

bool BST::deletemax() {
    if (m_root == nullptr) {
        return false;
    } else {
        return DeleteMaxHelper(m_root);
    }
}

Node *BST::FindMin() {
    if (m_root == nullptr) {
        return m_root;
    } else {
        return FindMinHelper(m_root);
    }
}

Node *BST::FindMinHelper(Node *root) {
    //    if (root == nullptr){
    //        return nullptr;
    //    } else
    if (root->left() == nullptr) {
        return root;
    } else {
        return FindMinHelper(root->left());
    }
}

Node *BST::FindMax() {
    if (m_root == nullptr) {
        return m_root;
    } else {
        return FindMaxHelper(m_root);
    }
}

Node *BST::FindMaxHelper(Node *root) {
    if (root->right() == nullptr) {
        return root;
    } else {
        return FindMaxHelper(root->right());
    }
}

void BST::Preorder() {
    if (m_root == nullptr) {
        std::cout << "Tree is empty.\n";
    } else {
        PreorderHelper(m_root);
    }
}

void BST::PreorderHelper(Node *root) {
    if (root != nullptr) {
        std::cout << " " << root->value();
        PreorderHelper(root->left());
        PreorderHelper(root->right());
    }
}

void BST::Inorder() {
    if (m_root == nullptr) {
        std::cout << "Tree is empty.\n";
    } else {
        InorderHelper(m_root);
    }
}

void BST::InorderHelper(Node *root) {
    if (root != nullptr) {
        InorderHelper(root->left());
        std::cout << " " << root->value();
        InorderHelper(root->right());
    }
}

void BST::Postorder() {
    if (m_root == nullptr) {
        std::cout << "Tree is empty.\n";
    } else {
        PostorderHelper(m_root);
    }
}

void BST::PostorderHelper(Node *root) {
    if (root != nullptr) {
        PostorderHelper(root->left());
        PostorderHelper(root->right());
        std::cout << " " << root->value();
    }
}

