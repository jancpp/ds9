/*
Author: Jan Polzer
File:   Node.h
Date:   2/12/2018
Updated: 4/2/2018
*/

#ifndef NODE_H
#define NODE_H

class Node
{
private:
	int m_value;
	Node *m_left ;
	Node *m_right ;

public:
	// @pre:    None
	// @post:   Initialized BinarayNode class
	// @return  None
	Node();

	// @pre:    None
	// @post:   Initialized BinarayNode class
	// @return  None
	Node(const int &value);

	// @pre:    None
	// @post:   Initialized BinarayNode class
	// @return  None
	Node(const int &value, Node *left , Node *right );

	// @pre:    Node
	// @post:   None
	// @return  m_value
	int value() const;

	// @pre:    Node
	// @post:   Set value
	// @return  None
	void setValue(const int &value);

	// @pre:    Node
	// @post:   Set left child
	// @return  None
	Node *left () const;

	// @pre:    Node
	// @post:   Set right child
	// @return  None
	Node *right () const;

	// @pre:    Node
	// @post:   None
	// @return  m_left
	void setLeft (Node *left );

	// @pre:    Node
	// @post:   None
	// @return  m_right
	void setRight (Node *right );

};

#endif
