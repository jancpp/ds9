/*
Author: Jan Polzer
File:   BST.h
Date:   2/12/2018
Updated: 4/2/2018
*/


#ifndef BST_H
#define BST_H

#include "Node.h"
#include <iostream>

class BST {

private:
	Node *m_root;

	// @pre:    BST
	// @post:   Inserting node in root
	// @return: Node pointer of element to be inserted
	Node *InsertHelper(Node *root, Node *node);

	// @pre:    BST
	// @post:   Printed values in preorder traversal
	// @return: None
	void PreorderHelper(Node *root);

	// @pre:    BST
	// @post:   Printed values in inorder traversal
	// @return: None
	void InorderHelper(Node *root);

	// @pre:    BST
	// @post:   Printed values in postorder traversal
	// @return: None
	void PostorderHelper(Node *root);

	// @pre:    BST
	// @post:   Serching in root
	// @return: Node pointer of element to be found
	Node *FindMinHelper(Node *root);

	// @pre:    BST
	// @post:   Searching in root
	// @return: Node pointer of element to be found
	Node *FindMaxHelper(Node *root);

	// @pre:    BST
	// @post:   Deleted node from the tree
	// @return: True if deleted, false otherwise
	bool DeleteHelper(int value, Node *root);

public:
	BST();
	~BST();

	// @pre:    Binary search tree
	// @Post:   New node inserted into the tree:    as root if empty,
	//                                              as left node if value is smaller then root value
	//                                              as right node if value is same or larger then root
	// @Return: True if success, false otherwise
	bool insert(int value);

	// @pre:    BST
	// @post:   Deleted passed value
	// @return: True if deleted, false otherwise
	bool Delete(int value);

	// @pre:    BST
	// @post:   Deleted min value
	// @return: True if deleted, false otherwise
	bool deletemin();

	// @pre:    BST
	// @post:   Deleted max value
	// @return: True if deleted, false otherwise
	bool deletemax();

	// @pre:    BST
	// @post:   Found the smallest element in the BST
	// @return: A pointer to teh smallest node, nullptr if not found.
	Node *FindMin();

	// @pre:    BST
	// @post:   Found the largest element in the BST
	// @return: A pointer to the largest node, nullptr if not found.
	Node *FindMax();

	// @pre:    BST
	// @post:   Printed out all the elements of the BST using preorder traversal.
	// @return: None
	void Preorder();

	// @pre:    BST
	// @post:   Printed out all the elements of the BST using inorder traversal.
	// @return: None
	void Inorder();

	// @pre:    BST
	// @post:   Printed out all the elements of the BST using postorder traversal.
	// @return: None
	void Postorder();
};

#endif