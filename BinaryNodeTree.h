#ifndef BINARY_NODE_TREE_H
#define BINARY_NODE_TREE_H

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"

// used for print and printNode
#include <iostream> 
#include <string>

template <class T>
class BinaryNodeTree : public BinaryTreeInterface<T> {
private:
	BinaryNode<T>* m_root;

protected:
	int getHeightHelper(BinaryNode<T>* subTree) const;
	int getNumberOfNodesHelper(BinaryNode<T>* subTree) const;

	void destroyTree(BinaryNode<T>* subTree);
	BinaryNode<T>* balancedAdd(BinaryNode<T>* subTree, BinaryNode<T>* newNode);
	BinaryNode<T>* removeValue(BinaryNode<T>* subTree, const T& target, bool& success);
	BinaryNode<T>* moveValuesUpTree(BinaryNode<T>* subTree);
	BinaryNode<T>* findNode(BinaryNode<T>* tree, const T& target, bool& success) const;
	BinaryNode<T>* copyTree(const BinaryNode<T>* tree) const;

	void preorder(void visit(T&), BinaryNode<T>* tree) const;
	void inorder(void visit(T&), BinaryNode<T>* tree) const;
	void postorder(void visit(T&), BinaryNode<T>* tree) const;

	void printNode(BinaryNode<T>* bn, std::string indent);

public:
	BinaryNodeTree();
	BinaryNodeTree(const T& rootData);
	BinaryNodeTree(const T& rootData,
		const BinaryNodeTree<T>* leftSubTree,
		const BinaryNodeTree<T>* rightSubTree);
	BinaryNodeTree(const BinaryNodeTree<T>& tree);
	virtual ~BinaryNodeTree();

	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	T getRootData() const;
	void setRootData(const T& newData);
	bool add(const T& newData);
	bool remove(const T& data);
	void clear();
	T getEntry(const T& anEntry) const;
	bool contains(const T& anEntry) const;

	void preorderTraverse(void visit(T&)) const;
	void inorderTraverse(void visit(T&)) const;
	void postorderTraverse(void visit(T&)) const;

	BinaryNodeTree& operator=(const BinaryNodeTree& rhs);

	void print();

};


// for debug and visualization purposes
template<class T>
void BinaryNodeTree<T>::printNode(BinaryNode<T>* bn, std::string indent) {
	std::string long_indent = "    " + indent;
	if (bn == nullptr) { std::cout << "[/]"; }
	else {
		if (bn->getRight() != nullptr){ printNode(bn->getRight(), long_indent); }
		std::cout << indent << bn->getData() << " ]" << std::endl;
		if (bn->getLeft() != nullptr){ printNode(bn->getLeft(), long_indent); }
	}
}

template<class T>
void BinaryNodeTree<T>::print() {
	printNode(m_root, "+---+[ ");
}


// ============================================================================================================
// IMPLEMENTATION
// ============================================================================================================



// ------------------------------------------------------
// HELPERS
// ------------------------------------------------------

// max is needed for getHeightHelper
// returns the higher of the two
int max(int x, int y) {
	if (x >= y) return x;
	else return y;
}

template <class T>
int BinaryNodeTree<T>::getHeightHelper(BinaryNode<T>* subTree) const {
	if (subTree == nullptr) return 0;
	else return 1 + max(getHeightHelper(subTree->getLeft()), getHeightHelper(subTree->getRight()));
}

template <class T>
int BinaryNodeTree<T>::getNumberOfNodesHelper(BinaryNode<T>* subTree) const {
	if (subTree == nullptr) return 0;
	else return 1 + getNumberOfNodesHelper(subTree->getLeft()) + getNumberOfNodesHelper(subTree->getRight());
}

template <class T>
void BinaryNodeTree<T>::destroyTree(BinaryNode<T>* subTree) {
	if (subTree != nullptr) {
		destroyTree(subTree->getLeft());
		destroyTree(subTree->getRight());
		delete subTree;
	}
}

template <class T>
BinaryNode<T>* BinaryNodeTree<T>::balancedAdd(BinaryNode<T>* subTree, BinaryNode<T>* newNode) {
	if (subTree == nullptr) return newNode;
	else {
		BinaryNode<T>* left = subTree->getLeft();
		BinaryNode<T>* right = subTree->getRight();

		if (getHeightHelper(left) > getHeightHelper(right)) {
			right = balancedAdd(right, newNode);
			subTree->setRight(right);
		}
		else {
			left = balancedAdd(left, newNode);
			subTree->setLeft(left);
		}

		return subTree;
	}
}



template <class T>
BinaryNode<T>* BinaryNodeTree<T>::removeValue(BinaryNode<T>* subTree, const T& target, bool& success) {
	if (subTree == nullptr) {
		success = false;
		return nullptr;
	}
	else {
		if (subTree->getData() == target) {
			success = true;
			return moveValuesUpTree(subTree);			
		}
		else {
			BinaryNode<T>* left = removeValue(subTree->getLeft(), target, success);
			if (success) {
				//subTree->setLeft(left);
				return left;
			}
			BinaryNode<T>* right = removeValue(subTree->getRight(), target, success);
			if (success) {
				//subTree->setRight(right);
				return right;
			}
		}
	}
	return nullptr;
}

template <class T>
BinaryNode<T>* BinaryNodeTree<T>::moveValuesUpTree(BinaryNode<T>* subTree) {
	if (subTree == nullptr) return nullptr;
	else {

		BinaryNode<T>* tree = subTree;
		BinaryNode<T>* left = subTree->getLeft();
		BinaryNode<T>* right = subTree->getRight();
		
		if (left == nullptr && right == nullptr) {
			if (subTree == m_root){
				m_root = nullptr;
			}
			subTree = nullptr;
			return subTree;
		}
		else {
			if (subTree->getLeft() != nullptr) {
				subTree->setData((subTree->getLeft())->getData());
				subTree->setLeft(moveValuesUpTree(subTree->getLeft()));
			}
			else {
				subTree->setData((subTree->getRight())->getData());
				subTree->setRight(moveValuesUpTree(subTree->getRight()));
			}
		}
	}
	return subTree;
}

template <class T>
BinaryNode<T>* BinaryNodeTree<T>::findNode(BinaryNode<T>* tree, const T& target, bool& success) const {
	if (tree == nullptr) {
		success = false;
		return nullptr;
	}
	else {
		if (tree->getData() == target) {
			success = true;
			return tree;
		}
		else {
			BinaryNode<T>* left = findNode(tree->getLeft(), target, success);
			if (left != nullptr) return left;

			BinaryNode<T>* right = findNode(tree->getRight(), target, success);
			if (right != nullptr) return right;
		}
	}
	return nullptr;
}

template <class T>
BinaryNode<T>* BinaryNodeTree<T>::copyTree(const BinaryNode<T>* tree) const {
	BinaryNode<T>* newTree = nullptr;

	if (tree != nullptr){
		newTree = new BinaryNode<T>(tree->getData(), nullptr, nullptr);
		newTree->setLeft(copyTree(tree->getLeft()));
		newTree->setRight(copyTree(tree->getRight()));
	}
	return newTree;
}

template <class T>
void BinaryNodeTree<T>::preorder(void visit(T&), BinaryNode<T>* tree) const {
	if (tree != nullptr) {
		T data = tree->getData();
		visit(data);
		preorder(visit, tree->getLeft());
		preorder(visit, tree->getRight());
	}
}

template <class T>
void BinaryNodeTree<T>::inorder(void visit(T&), BinaryNode<T>* tree) const {
	if (tree != nullptr) {
		inorder(visit, tree->getLeft());
		T data = tree->getData();
		visit(data);
		inorder(visit, tree->getRight());
	}
}

template <class T>
void BinaryNodeTree<T>::postorder(void visit(T&), BinaryNode<T>* tree) const {
	if (tree != nullptr) {
		postorder(visit, tree->getLeft());
		postorder(visit, tree->getRight());
		T data = tree->getData();
		visit(data);
	}
}


// ------------------------------------------------------
// PUBLIC MEMBERS
// ------------------------------------------------------

// constructor
template <class T>
BinaryNodeTree<T>::BinaryNodeTree() : m_root(nullptr) {
}

// constructor
template <class T>
BinaryNodeTree<T>::BinaryNodeTree(const T& rootData) {
	m_root = new BinaryNode<T>(rootData, nullptr, nullptr);
}

// constructor
template <class T>
BinaryNodeTree<T>::BinaryNodeTree(const T& rootData,
	const BinaryNodeTree<T>* leftSubTree,
	const BinaryNodeTree<T>* rightSubTree) {
	m_root = new BinaryNode<T>(rootData, copyTree(leftSubTree->m_root, copyTree(rightSubTree->m_root)));
}

// copy constructor
template <class T>
BinaryNodeTree<T>::BinaryNodeTree(const BinaryNodeTree<T>& tree) {
	m_root = copyTree(tree.m_root);
}

// destructor
template <class T>
BinaryNodeTree<T>::~BinaryNodeTree() {
	destroyTree(m_root);
}

template <class T>
bool BinaryNodeTree<T>::isEmpty() const {
	return m_root == nullptr;
}

template <class T>
int BinaryNodeTree<T>::getHeight() const {
	return getHeightHelper(m_root);
}

template <class T>
int BinaryNodeTree<T>::getNumberOfNodes() const {
	return getNumberOfNodesHelper(m_root);
}

template <class T>
T BinaryNodeTree<T>::getRootData() const {
	//if (m_root == nullptr) 
	return m_root->getData();
}

template <class T>
void BinaryNodeTree<T>::setRootData(const T& newData) {
	m_root->setData(newData);
}

template <class T>
bool BinaryNodeTree<T>::add(const T& newData) {
	BinaryNode<T>* newNode = new BinaryNode<T>(newData);
	m_root = balancedAdd(m_root, newNode);
	return true;
}

template <class T>
bool BinaryNodeTree<T>::remove(const T& data) {
	bool removed = false;
	removeValue(m_root, data, removed);
	return removed;
}

template <class T>
void BinaryNodeTree<T>::clear() {
	BinaryNode<T>* oldRoot = m_root;
	destroyTree(oldRoot);
	m_root = nullptr;
}

template <class T>
T BinaryNodeTree<T>::getEntry(const T& anEntry) const {
	bool exists = false;
	BinaryNode<T>* entry = findNode(m_root, anEntry, exists);
	if (exists)
		return entry->getData();
	return anEntry;
}

template <class T>
bool BinaryNodeTree<T>::contains(const T& anEntry) const {
	bool exists = false;
	findNode(m_root, anEntry, exists);
	return exists;
}


template <class T>
void BinaryNodeTree<T>::preorderTraverse(void visit(T&)) const {
	preorder(visit, m_root);
}

template <class T>
void BinaryNodeTree<T>::inorderTraverse(void visit(T&)) const {
	inorder(visit, m_root);
}

template <class T>
void BinaryNodeTree<T>::postorderTraverse(void visit(T&)) const {
	postorder(visit, m_root);
}


template <class T>
BinaryNodeTree<T>& BinaryNodeTree<T>::operator=(const BinaryNodeTree<T>& rhs) {
	clear();
	m_root = copyTree(rhs.m_root);
	return *this;
}


#endif // BINARY_NODE_TREE_H