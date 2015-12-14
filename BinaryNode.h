#ifndef BINARY_NODE_H
#define BINARY_NODE_H
template < class T >
class BinaryNode {
private:
	T m_data;
	BinaryNode* m_left;
	BinaryNode* m_right;
public:
	BinaryNode();
	BinaryNode(const T& _data);
	BinaryNode(const T& _data, BinaryNode<T>* _left, BinaryNode<T>* _right);

	T getData() const;
	void setData(const T& _data);

	BinaryNode* getLeft() const;
	void setLeft(BinaryNode<T>* _left);

	BinaryNode* getRight() const;
	void setRight(BinaryNode<T>* _right);

};

template <class T>
BinaryNode<T>::BinaryNode()
: m_left{ nullptr }, m_right{ nullptr } {
}

template <class T>
BinaryNode<T>::BinaryNode(const T& _data) 
: m_data{ _data }, m_left{ nullptr }, m_right{ nullptr } {
}

template <class T>
BinaryNode<T>::BinaryNode(const T& _data, BinaryNode<T>* _left, BinaryNode<T>* _right)
: m_data{ _data }, m_left{ _left }, m_right{ _right } {
}


template <class T>
T BinaryNode<T>::getData() const {
	return m_data;
}


template <class T>
void BinaryNode<T>::setData(const T& _data) {
	m_data = _data;
}


template <class T>
BinaryNode<T>* BinaryNode<T>::getLeft() const {
	return m_left;
}


template <class T>
void BinaryNode<T>::setLeft(BinaryNode<T>* _left) {
	m_left = _left;
}


template <class T>
BinaryNode<T>* BinaryNode<T>::getRight() const {
	return m_right;
}


template <class T>
void BinaryNode<T>::setRight(BinaryNode<T>* _right) {
	m_right = _right;
}



#endif // BINARY_NODE_H