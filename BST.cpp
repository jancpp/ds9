/*
 Author: Jan Polzer
 File:   BST.cpp
 Date:   2/12/2018
 Updated: 4/2/2018
 */

#include "BST.h"

BST::BST(): m_root(nullptr) {}
BST::~BST() {}

bool BST::insert(int value) {
    bool inserted = false;
    Node *newNode = new Node(value);
    m_root = InsertHelper(m_root, newNode);
    if (m_root != nullptr) {
        inserted = true;
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

bool BST::Delete(int value) {
    bool deleted = false;
    deleted = DeleteHelper(value, m_root);
    return deleted;
}

bool BST::deletemin() {
    if (m_root == nullptr) {
        return false;
    } else {
        int value = FindMin()->value();
        return DeleteHelper(value, m_root);
    }
}

bool BST::deletemax() {
    if (m_root == nullptr) {
        return false;
    } else {
        int value = FindMax()->value();
        return DeleteHelper(value, m_root);
    }
}
// Delete(x) – Should delete x from the BST. For consistency when deleting
// an element that has two children, use the smallest element from its right subtree
// to replace x (using deleteMin). Should delete the first occurrence of x
// if there are duplicated elements. Return error if x is not found or the BST is empty.
bool BST::DeleteHelper(int value, Node *root) {
    bool deleted = false;
    Node *parent = nullptr; // parent of node to be deleted
    if (root == nullptr) {
        return false;
    }
    while ((root != nullptr) && (root->value() != value)) {
        if (value < root->value()) { // search on left
            //            if (root->left() != nullptr)
            parent = root;
            root = root->left();
        } else if (value > root->value()) { // search on right
            parent = root;
            root = root->right();
        } else {
            // value == root->value()
            return false;
        }
    }
    if (root == nullptr) {
        return false;
    } else if ((m_root->value() == value) && (root->left() == nullptr) && (root->right() == nullptr)) { // one node in tree
        delete m_root;
        m_root = nullptr;
        return true;
    } else if ((root->left() == nullptr) && (root->right() == nullptr)) { // two nodes in tree
        if (parent->left() == root) {
            parent->setLeft(nullptr);
        } else if (parent->right() == root) {
            parent->setRight(nullptr);
        }
        delete root;
        root = nullptr;
        return true;
    } else if((root->right() != nullptr) && (root->left() == nullptr)) {
        if(parent->left() == root) {
            parent->setLeft(root->right());
        }
        else if(parent->right() == root) {
            parent->setRight(root->right());
        }
        delete root;
        root = nullptr;
        return true;
    }
    
    if((root->right() == nullptr) && (root->left() != nullptr)) {
        if(parent->left() == root) {
            parent->setLeft(root->left());
        }
        else if(parent->right() == root) {
            parent->setRight(root->left());
        }
        delete root;
        root = nullptr;
        return true;
        
        
    }// when deleting an element that has two children,
    // we delete using the smallest element from its right subtree
    // to replace x (using deleteMin).
    else if ((root->right() != nullptr) && (root->left() != nullptr)) {
        int min = FindMinHelper(root->right())->value();
        root->setValue(min);
        DeleteHelper(min, root->right());
        deleted = true;
    }
    return deleted;
}

Node *BST::FindMin() {
    if (m_root == nullptr) {
        return m_root;
    } else {
        return FindMinHelper(m_root);
    }
}

Node *BST::FindMinHelper(Node *root) {
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
        InorderHelper(root->left());
        InorderHelper(root->right());
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

