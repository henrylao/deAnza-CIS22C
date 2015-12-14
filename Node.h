/* Thomas Tang
 * Yuan Zheng
 * CIS22C
 * Node.h
 */

#ifndef NODE_H
#define NODE_H

template <class T>
class Node{
public:
	Node();
	Node(Node<T>& _node);
	Node(T _data, Node<T>* _next);

	T data() const;
	void data(const T& _data);

	Node* next() const;
	void next(Node<T>* _next);

private:
	T m_data;
	Node* m_next;
};

template <class T>
Node<T>::Node() : m_next{ nullptr } {
}

template <class T>
Node<T>::Node(Node<T>& _node) : m_data{ _node.m_data }, m_next{ _node.m_next } {

}

template <class T>
Node<T>::Node(T _data, Node<T>* _next) : m_data{ _data }, m_next{ _next } {

}

template <class T>
T Node<T>::data() const {
	return m_data;
}

template <class T>
void Node<T>::data(const T& _data) {
	m_data = _data;
}

template <class T>
Node<T>* Node<T>::next() const {
	return m_next;
}

template <class T>
void Node<T>::next(Node<T>* _next) {
	m_next = _next;
}


#endif // NODE_H