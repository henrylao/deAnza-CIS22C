/* Thomas Tang
 * Yuan Zheng
 * CIS22C Lab2 Stack Project
 * Stack.h 
 * .... implemented using LinkedList.h
 */

#ifndef STACK_H
#define STACK_H
#include "LinkedList.h"

template <class T>
class Stack : protected LinkedList<T> {
public:
	Stack() : LinkedList<T>() {}
	~Stack() { LinkedList<T>::~LinkedList(); }

	bool push(T data) { return LinkedList<T>::insert(0, data); }
	T pop() { T toPop = peek(); LinkedList<T>::remove(0); return toPop; }
	bool isEmpty() { return LinkedList<T>::isEmpty(); }
	T peek() { return LinkedList<T>::getEntry(0); }
	int size() { return LinkedList<T>::size(); }
};

#endif // STACK_H