#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

template<typename T>
struct Node {
	T _value;
	Node<T>* _next;
	Node<T>* _prev;

	explicit Node<T>(const T&);
	explicit Node<T>(const T&, Node<T>*, Node<T>*);
};


template<typename T>
class DoublyLinkedList {
	Node<T>* _head;
	Node<T>* _tail;
	size_t _size;

	bool isHead(Node<T>*) const;
	bool isTail(Node<T>*) const;
	void swapValues(Node<T>*, Node<T>*) const;
	void quicksort(Node<T>*, Node<T>*) const ;
	Node<T>* partition(Node<T>*, Node<T>*) const;

public:
	explicit DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList&);
	DoublyLinkedList& operator=(const DoublyLinkedList&);
	DoublyLinkedList(DoublyLinkedList&&);
	DoublyLinkedList& operator=(DoublyLinkedList&&);
	void pushFront(const T&);
	void pushBack(const T&);
	void popFront();
	void popBack();
	void remove(const T&);
	void erase(Node<T>*);
	void insert(Node<T>*, const T&);
	Node<T>* find(const T&);
	void clear();
	size_t size() const;
	bool isEmpty() const;
	void reverse();
	void sort();

	friend std::ostream& operator<<(std::ostream& stream, const DoublyLinkedList<T>& dll){
		auto current = dll._head;
		while (current){
			stream << current->_value << " ";
			current = current->_next;
		}
		return stream;
	}
};

template<typename T>
inline bool DoublyLinkedList<T>::isHead(Node<T>* node) const {
	return _head == node;
}

template<typename T>
inline bool DoublyLinkedList<T>::isTail(Node<T>* node) const {
	return _tail == node;
}

template<typename T>
inline void DoublyLinkedList<T>::swapValues(Node<T>* one, Node<T>* two) const {
	auto temporary = one->_value;
	one->_value = two->_value;
	two->_value = temporary;
}

#endif