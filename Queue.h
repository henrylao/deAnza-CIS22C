#ifndef QUEUE_H
#define QUEUE_H
#include "LinkedList.h"

template <class T>
class Queue : protected LinkedList<T> {
public:
	Queue() : LinkedList<T>() {}
	~Queue() { LinkedList<T>::~LinkedList(); }

	bool enqueue(const T& data) { LinkedList<T>::insertBack(data); return true; }
	T dequeue() { T toDQ = peekFront(); LinkedList<T>::removeFront(); return toDQ; }
	bool isEmpty() { return LinkedList<T>::isEmpty(); }
	T peekFront() { return LinkedList<T>::getEntry(0); }
	int size() { return LinkedList<T>::size(); }
};

#endif // QUEUE_H