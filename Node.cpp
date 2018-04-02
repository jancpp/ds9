/*
Author: Jan Polzer
File:   Node.cpp
Date:   2/12/2018
Updated: 4/2/2018
*/

#include "Node.h"

Node::Node() : m_left (nullptr ), m_right (nullptr ) {
}

Node::Node(const int &value) : m_left (nullptr ), m_right (nullptr ) {
        setValue(value);
}

Node::Node(const int &value, Node *left , Node *right ) {
        setValue(value);
        setLeft (left );
        setRight (right );
}

int Node::value() const {
        return m_value;
}

void Node::setValue (const int &value) {
        m_value = value;
}

void Node::setLeft (Node *node) {
        m_left  = node;
}

void Node::setRight (Node *node) {
        m_right  = node;
}

Node *Node::left () const {
        return m_left ;
}

Node *Node::right () const {
        return m_right ;
}
