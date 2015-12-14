#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <string>
#include "Queue.h" // used for breadth first
#include "BinaryNodeTree.h"

template <class T>
class BinarySearchTree : public BinaryNodeTree<T> {
private:
	BinaryNode<T>* m_root;
	Queue<BinaryNode<T>*> m_queue;
protected:
	BinaryNode<T>* insertInorder(BinaryNode<T>* subTree, BinaryNode<T>* newNode);
	BinaryNode<T>* removeValue(BinaryNode<T>* subTree, const T target, bool& success);
	BinaryNode<T>* removeNode(BinaryNode<T>* node);

	BinaryNode<T>* furthest_left(BinaryNode<T>* root);
	BinaryNode<T>* furthest_right(BinaryNode<T>* root);
	BinaryNode<T>* remove_furthest_left(BinaryNode<T>* root);
	BinaryNode<T>* remove_furthest_right(BinaryNode<T>* root);
	BinaryNode<T>* findNode(BinaryNode<T>* treePtr, const T& target) const;

	void BF_addChildren(BinaryNode<T>* tree);
	void BF_DQ(void visit(T&));
	void printNode(BinaryNode<T>* bn, std::string indent);

public:
	BinarySearchTree();
	BinarySearchTree(const T& rootItem);
	BinarySearchTree(const BinarySearchTree<T>& tree);
	virtual ~BinarySearchTree();
	
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	T getRootData() const;		// throw (PrecondViolatedExcep);
	void setRootData(const T& newData) const;// throw (PrecondViolatedExcep);
	bool add(const T& newEntry);
	bool remove(const T& anEntry);
	void clear();
	T getEntry(const T& anEntry) const; // throw (NotFoundException);
	bool contains(const T& anEntry) const;
	void preorderTraverse(void visit(T&)) const;
	void inorderTraverse(void visit(T&)) const;
	void postorderTraverse(void visit(T&)) const;
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& rhs);


	void breadthFirstTraverse(void visit(T&));
	void print();
};



template<class T>
void BinarySearchTree<T>::printNode(BinaryNode<T>* bn, std::string indent) {
	std::string long_indent = "    " + indent;
	if (bn == nullptr) { std::cout << "--+[/]" << std::endl; }
	else{
		if (bn->getRight() != nullptr){ printNode(bn->getRight(), long_indent); }
		std::cout << indent << bn->getData() << "]" << std::endl;
		if (bn->getLeft() != nullptr){ printNode(bn->getLeft(), long_indent); }
	}
}

template<class T>
void BinarySearchTree<T>::print() {
	printNode(m_root, "--+[");
}




// ============================================================================================================
// IMPLEMENTATION
// ============================================================================================================



// Recursively finds where the given node should be placed and
// inserts it in a leaf at that point.
template <class T>
BinaryNode<T>* BinarySearchTree<T>::insertInorder(BinaryNode<T>* tree_node, BinaryNode<T>* add_node) {
	if (tree_node == nullptr) 
		return add_node;
	else if (tree_node->getData() > add_node->getData()){
		BinaryNode<T>* temp_node = insertInorder(tree_node->getLeft(), add_node);
		tree_node->setLeft(temp_node);
	}
	else{
		BinaryNode<T>* temp_node = insertInorder(tree_node->getRight(), add_node);
		tree_node->setRight(temp_node);
	}
	return tree_node;
}

// Removes the given target value from the tree while maintaining a
// binary search tree.
template <class T>
BinaryNode<T>* BinarySearchTree<T>::removeValue(BinaryNode<T>* tree, const T target, bool& success) {
	if (tree == nullptr) {
		success = false;
		return nullptr;
	}
	else if (tree->getData() == target) {
		tree = removeNode(tree);
		success = true;
		return tree;
	}
	else if (tree->getData() > target)
	{
		BinaryNode<T>* temp = removeValue(tree->getLeft(), target, success);
		tree->setLeft(temp);
		return tree;
	}
	else {
		BinaryNode<T>* temp = removeValue(tree->getRight(), target, success);
		tree->setRight(temp);
		return tree;
	}
}

// Removes a given node from a tree while maintaining a
// binary search tree.
template <class T>
BinaryNode<T>* BinarySearchTree<T>::removeNode(BinaryNode<T>* root) {
	if (root == nullptr) { // is nullptr
		return nullptr;
	}
	else if (root->getLeft() == nullptr && root->getRight() == nullptr) { // is leaf | has no children
		root = nullptr;
	}
	else if (root->getLeft() != nullptr && root->getRight() == nullptr) { // has left child only
		root->setData(furthest_right(root->getLeft())->getData());
		root->setLeft(remove_furthest_right(root->getLeft()));
	}
	else if (root->getRight() != nullptr && root->getLeft() == nullptr) { // has right child only 
		root->setData(furthest_left(root->getRight())->getData());
		root->setRight(remove_furthest_left(root->getRight()));
	}
	else { // has both
		if (BinaryNodeTree<T>::getHeightHelper(root->getLeft()) <= BinaryNodeTree<T>::getHeightHelper(root->getRight())) {
			root->setData(furthest_left(root->getRight())->getData());
			root->setRight(remove_furthest_left(root->getRight()));
		}
		else {
			root->setData(furthest_right(root->getLeft())->getData());
			root->setLeft(remove_furthest_right(root->getLeft()));
		}
	}
	return root;
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::furthest_left(BinaryNode<T>* root) {
	if (root->getLeft() == nullptr)	{
		return root;
	}
	else {
		return furthest_left(root->getLeft());
	}
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::furthest_right(BinaryNode<T>* root) {
	if (root->getRight() == nullptr) {
		return root;
	}
	else {
		return furthest_right(root->getRight());
	}
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::remove_furthest_left(BinaryNode<T>* root) {

	if (root->getLeft() == nullptr)	{
		return removeNode(root);
	}
	else {
		root->setLeft(remove_furthest_left(root->getLeft()));
		return root;
	}
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::remove_furthest_right(BinaryNode<T>* root) {
	if (root->getRight() == nullptr) {
		return removeNode(root);
	}
	else {
		root->setRight(remove_furthest_right(root->getRight()));
		return root;
	}
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::findNode(BinaryNode<T>* tree_node, const T& target) const {
	if (tree_node == nullptr) {
		return nullptr;
	}
	else if (tree_node->getData() == target) {
		return tree_node;
	}
	else if (tree_node->getData() > target) {
		return findNode(tree_node->getLeft(), target);
	}
	else {
		return findNode(tree_node->getRight(), target);
	}
}

template <class T>
void BinarySearchTree<T>::BF_addChildren(BinaryNode<T>* tree) {
	if (tree->getLeft() != nullptr) {
		m_queue.enqueue(tree->getLeft());
	}
	if (tree->getRight() != nullptr) {
		m_queue.enqueue(tree->getRight());
	}
}

template <class T>
void BinarySearchTree<T>::BF_DQ(void visit(T&)) {
	BinaryNode<T>* node;
	if (!m_queue.isEmpty()) {
		node = m_queue.dequeue();
		visit(node->getData());
		BF_addChildren(node);
	}
}
// ------------------------------------------------------
// PUBLIC MEMBERS
// ------------------------------------------------------


// constructor
template <class T>
BinarySearchTree<T>::BinarySearchTree() : m_root(nullptr) {

}

// constructor with item
template <class T>
BinarySearchTree<T>::BinarySearchTree(const T& rootData) {
	m_root = new BinaryNode<T>(rootData, nullptr, nullptr);
}

// constructor with tree
template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree) {
	m_root = BinaryNodeTree<T>::copyTree(tree->m_root);
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	BinaryNodeTree<T>::destroyTree(m_root);
}
	
template <class T>
bool BinarySearchTree<T>::isEmpty() const {
	return BinaryNodeTree<T>::isEmpty();
}

template <class T>
int BinarySearchTree<T>::getHeight() const{
	return BinaryNodeTree<T>::getHeightHelper(m_root);
}

template <class T>
int BinarySearchTree<T>::getNumberOfNodes() const {
	return BinaryNodeTree<T>::getNumberOfNodesHelper(m_root);
}

template <class T>
T BinarySearchTree<T>::getRootData() const {		// throw (PrecondViolatedExcep);
	return m_root->getData();
}

template <class T>
void BinarySearchTree<T>::setRootData(const T& newData) const { // throw (PrecondViolatedExcep);
	m_root->setData(newData);
}

template <class T>
bool BinarySearchTree<T>::add(const T& newEntry) {
	BinaryNode<T>* newNode = new BinaryNode<T>(newEntry);
	m_root = insertInorder(m_root, newNode);
	return true;
}

template <class T>
bool BinarySearchTree<T>::remove(const T& anEntry) {
	bool success = false;
	m_root = removeValue(m_root, anEntry, success);
	return success;
}

template <class T>
void BinarySearchTree<T>::clear() {
	BinaryNode<T>* oldRoot = m_root;
	BinaryNodeTree<T>::destroyTree(oldRoot);
	m_root = nullptr;
}

template <class T>
T BinarySearchTree<T>::getEntry(const T& anEntry) const {// throw (NotFoundException);
	return BinaryNodeTree<T>::getEntry(anEntry);
}

template <class T>
bool BinarySearchTree<T>::contains(const T& anEntry) const {
	return (findNode(m_root, anEntry) != nullptr);
}

template <class T>
void BinarySearchTree<T>::preorderTraverse(void visit(T&)) const {
	BinaryNodeTree<T>::preorder(visit, m_root);
}
	
template <class T>
void BinarySearchTree<T>::inorderTraverse(void visit(T&)) const {
	BinaryNodeTree<T>::inorder(visit, m_root);
}

template <class T>
void BinarySearchTree<T>::postorderTraverse(void visit(T&)) const {
	BinaryNodeTree<T>::postorder(visit, m_root);
}

template <class T>
void BinarySearchTree<T>::breadthFirstTraverse(void visit(T&)) {
	m_queue.enqueue(m_root);
	while (!m_queue.isEmpty()) {
		BF_DQ(visit);
	}
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& rhs) {
	clear();
	m_root = BinaryNodeTree<T>::copyTree(rhs.m_root);
}


#endif // BINARY_SEARCH_TREE_H