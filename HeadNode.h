/* Thomas Tang
 * Yuan Zheng
 * CIS22C 
 * HeadNode.h
 * .... implemented using Node.h
*/

#ifndef HEAD_NODE_H
#define HEAD_NODE_H

#include "Node.h"

template <class T>
class HeadNode : protected Node<T> {
public:
	HeadNode();
	HeadNode(Node<T>& _node);
	HeadNode(Node<T>* _head);

	Node<T>* head() const;
	void head(Node<T>* _head);
	
	Node<T>* tail() const;
	void tail(Node<T>* _tail);

	int getCount() const;
	void setCount(int _count);

private:
	Node<T>* m_tail;
	int m_count;
};

// creates a head node with pointing to nothing
template <class T>
HeadNode<T>::HeadNode() : Node<T>(), m_tail{ nullptr }, m_count{ 0 } {

}

// creates a head node pointing to a given node
template <class T>
HeadNode<T>::HeadNode(Node<T>& _node) : Node<T>(), m_tail{ &_node }, m_count{ 1 } {
	head(&_node);
}

// creates a head node pointing to a given node through a pointer
template <class T>
HeadNode<T>::HeadNode(Node<T>* _head) : Node<T>(), m_tail{ _head }, m_count{ 1 } {
	head(_head);
}

template <class T>
Node<T>* HeadNode<T>::head() const {
	return Node<T>::next();
}

template <class T>
void HeadNode<T>::head(Node<T>* _head) {
	Node<T>::next(_head);
}

template <class T>
Node<T>* HeadNode<T>::tail() const {
	return m_tail;
}

template <class T>
void HeadNode<T>::tail(Node<T>* _tail) {
	m_tail = _tail;
}

template <class T>
int HeadNode<T>::getCount() const {
	return m_count;
}

template <class T>
void HeadNode<T>::setCount(int _count) {
	m_count = _count;
}

#endif // HEAD_NODE_H