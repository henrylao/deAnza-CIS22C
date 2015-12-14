/* Thomas Tang
 * Yuan Zheng
 * CIS22C
 * LinkedList.h 
 * .... implemented using HeadNode.h
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "HeadNode.h"

template <class T>
class LinkedList {
public:
	LinkedList();
	virtual ~LinkedList();
	
	bool isEmpty() const;

	void insertFront(T data);
	void insertBack(T data);
	bool insert(int index, T data);

	void removeFront();
	void removeBack();
	bool remove(int index);

	void clear();

	int size();

	T getEntry(int index);
	void setEntry(int index, T data);

	Node<T>* traverse(int index);

private:
	HeadNode<T> m_list;
	Node<T>* m_traverse;
};

template <class T>
LinkedList<T>::LinkedList() {

}

template <class T>
LinkedList<T>::~LinkedList() {
	clear();
}

// returns true if the linked list is empty
template <class T>
bool LinkedList<T>::isEmpty() const {
	return m_list.head() == nullptr;
}

// adds to front of linked list and points head to new node
template <class T>
void LinkedList<T>::insertFront(T data) {
	Node<T>* toAdd = new Node<T>(data, nullptr);
	
	if (isEmpty()) {
		m_list.head(toAdd); // point head from nullptr to new node
		m_list.tail(toAdd); // point tail from nullptr to new node
		m_list.setCount(m_list.getCount() + 1); // size ++
		return;
	}

	toAdd->next(m_list.head()); // point new node's next to where head points to
	m_list.head(toAdd); // point headNode to new node
	m_list.setCount(m_list.getCount() + 1); // size ++
}

// adds to back of linked list and points tail to new node
template <class T>
void LinkedList<T>::insertBack(T data) {
	Node<T>* toAdd = new Node<T>(data, nullptr);
	if (isEmpty()) {
		insertFront(data);
		return;
	}
	m_list.tail()->next(toAdd); // point tail's next from nullptr to new node
	m_list.tail(m_list.tail()->next()); // point tail to new node
	m_list.setCount(m_list.getCount() + 1); // size ++
}

// adds to linked list at index.. starts with 0 as first index and size() - 1 as last index
template <class T>
bool LinkedList<T>::insert(int index, T data) {
	if (index < 0 || index > size())	return false;

	if (isEmpty() || index == 0) {
		insertFront(data);
		return true;
	}

	if (index == size()) {
		insertBack(data);
		return true;
	}
	
	Node<T>* toAdd = new Node<T>(data, nullptr);
	m_traverse = traverse(index - 1); // m_traverse points to prev of index
	toAdd->next(m_traverse->next()); // new node's next points to m_traverse's next
	m_traverse->next(toAdd); // m_traverse points to new node
	m_list.setCount(m_list.getCount() + 1); // size ++
	return true;
}

// removes the front node at index 0 and points head to its next node
template <class T>
void LinkedList<T>::removeFront() {
	if (isEmpty()) return;

	// if 1 entry
	if (size() == 1 || m_list.head() == m_list.tail()) {
		m_list.setCount(m_list.getCount() - 1); // size --
		delete m_list.head();
		m_list.head(nullptr);
		m_list.tail(nullptr);
		return;
	}

	Node<T>* toRemove(m_list.head());
	m_list.head(m_list.head()->next());
	m_list.setCount(m_list.getCount() - 1); // size --
	delete toRemove;
}

// removes tail node points tail to its prev node
template <class T>
void LinkedList<T>::removeBack() {
	if (isEmpty()) return;
	
	// if 1 entry
	if (size() == 1 || m_list.head() == m_list.tail()) {
		m_list.setCount(m_list.getCount() - 1); // size --
		delete m_list.head();
		m_list.head(nullptr);
		m_list.tail(nullptr);
		return;
	}

	m_list.tail(traverse(size() - 2)); // tail points to its prev
	m_list.setCount(m_list.getCount() - 1); // size --
	delete (m_list.tail())->next(); // delete what new tail's next
}

// removes the node at the index
template <class T>
bool LinkedList<T>::remove(int index) {
	if (index < 0 || index >= size())	return false;

	if (isEmpty())	return false;

	if (index == 0) {
		removeFront();
		return true;
	}

	if (index == size() - 1) {
		removeBack();
		return true;
	}

	m_traverse = traverse(index - 1); // points m_traverse to the prev of node to remove
	Node<T>* toRemove(m_traverse->next()); // point to node to remove
	m_traverse->next(toRemove->next()); // point m_traverse's next to node to remove's next
	m_list.setCount(m_list.getCount() - 1); // size --
	delete toRemove;
	return true;
}

// clears the linked list
template <class T>
void LinkedList<T>::clear() {
	int s = size();
	for (int i = 0; i < s; ++i) {
		removeFront();
	}
	m_list.setCount(0); // set size to 0
}

// returns the number of entries in the linked list
template <class T>
int LinkedList<T>::size() {
	return m_list.getCount();
}

// returns the data at the index
template <class T>
T LinkedList<T>::getEntry(int index) {
	return traverse(index)->data();
}

// sets the data at index
template <class T>
void LinkedList<T>::setEntry(int index, T data){
	traverse(index)->data(data);
}

// traverses through linked list and returns a pointer to the node at the given index
template <class T>
Node<T>* LinkedList<T>::traverse(int index) {
	if (isEmpty()){
		// TODO: throw index out of bounds exception
		return nullptr;
	}
	if (index < 0 || index >= m_list.getCount()) {
		// TODO: throw index out of bounds exception
		return nullptr;
	}

	m_traverse = m_list.head();
	for (int i = 0; i < index; ++i) {
		m_traverse = m_traverse->next();
	}
	return m_traverse;
}

#endif // LINKED_LIST_H