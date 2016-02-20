#include "DoublyLinkedList.h"


template<typename T>
Node<T>::Node(const T& value) : _value(value), _next(nullptr), _prev(nullptr){}

template<typename T>
Node<T>::Node(const T& value, Node<T>* next, Node<T>* prev) : _value(value), _next(next), _prev(prev){}



template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : _head(nullptr), _tail(nullptr), _size(0){}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
	clear();
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : _head(nullptr), _tail(nullptr), _size(0){
	auto current = other._head;
	while (current){
		pushBack(current->_value);
		current = current->_next;
	}
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs){
	if (this != &rhs){
		clear();
		auto current = rhs._head;
		while (current){
			pushBack(current->_value);
			current = current->_next;
		}
	}
	return *this;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& rhs){
	_head = rhs._head;
	_tail = rhs._tail;
	_size = rhs._size;
	rhs._head = rhs._tail = nullptr;
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& rhs){
	if (this != &rhs){
		clear();
		_head = rhs._head;
		_tail = rhs._tail;
		_size = rhs._size;

		rhs._head = rhs._tail = nullptr;
	}
	return *this;
}

template<typename T>
void DoublyLinkedList<T>::pushFront(const T& value){
	auto newNode = new Node<T>(value, _head, nullptr);
	if (isEmpty()) _head = _tail = newNode;
	else{
		_head->_prev = newNode;
		_head = newNode;
	}
	++_size;
}

template<typename T>
void DoublyLinkedList<T>::pushBack(const T& value){
	auto newNode = new Node<T>(value, nullptr, _tail);
	if (isEmpty()) _head = _tail = newNode;
	else{
		_tail->_next = newNode;
		_tail = newNode;
	}
	++_size;
}

template<typename T>
void DoublyLinkedList<T>::popFront(){
	if (isEmpty()) throw std::exception("Doubly linked list is empty");
	if (_head == _tail){		//check if there is just 1 node in the list
		delete _head;
		_head = _tail = nullptr;
	}
	else{
		auto temporary = _head;
		_head = _head->_next;
		_head->_prev = nullptr;
		delete temporary;
	}
	--_size;
}

template<typename T>
void DoublyLinkedList<T>::popBack(){
	if (isEmpty()) throw std::exception("Doubly linked list is empty");
	if (_head == _tail){		//check if there is just 1 node in the list
		delete _head;
		_head = _tail = nullptr;
	}
	else{
		auto temporary = _tail;
		_tail = _tail->_prev;
		_tail->_next = nullptr;
		delete temporary;
	}
	--_size;
}

template<typename T>
void DoublyLinkedList<T>::remove(const T& value){
	auto current = _head;
	while (current && current->_value != value){
		current = current->_next;
	}
	if (current){
		erase(current);
	}
}

template<typename T>
void DoublyLinkedList<T>::erase(Node<T>* node){
	if (isHead(node)) popFront();
	else if (isTail(node)) popBack();
	else{
		node->_prev->_next = node->_next;
		node->_next->_prev = node->_prev;
		delete node;
		--_size;
	}
}

//inserts new node before the node to which position points to
template<typename T>
void DoublyLinkedList<T>::insert(Node<T>* position, const T& value){
	if (isHead(position)) pushFront(value);
	else{
		auto newNode = new Node<T>(value, position, position->_prev);
		position->_prev->_next = newNode;
		position->_prev = newNode;
		++_size;
	}
}

template<typename T>
Node<T>* DoublyLinkedList<T>::find(const T& value){
	auto current = _head;
	while (current){
		if (current->_value == value) return current;
		current = current->_next;
	}
	return nullptr;
}

template<typename T>
void DoublyLinkedList<T>::clear(){
	auto current = _head;
	while (current){
		_head = _head->_next;
		delete current;
		current = _head;
	}
	_head = _tail = nullptr;
	_size = 0;
}

template<typename T>
size_t DoublyLinkedList<T>::size() const {
	return _size;
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const {
	return _size == 0;
}

template<typename T>
void DoublyLinkedList<T>::reverse(){
	Node<T>* temporary = nullptr;
	auto current = _head;

	while (current){
		current->_prev = current->_next;
		current->_next = temporary;
		temporary = current;
		current = current->_prev;
	}
	_tail = _head;
	_head = temporary;
}

template<typename T>
void DoublyLinkedList<T>::sort(){
	quicksort(_head, _tail);
}

template<typename T>
void DoublyLinkedList<T>::quicksort(Node<T>* low, Node<T>* high) const {
	if (low && high && low != high->_next){
		auto p = partition(low, high);
		quicksort(low, p->_prev);
		quicksort(p->_next, high);
	}
}

template<typename T>
Node<T>* DoublyLinkedList<T>::partition(Node<T>* low, Node<T>* high) const {
	const T& pivot = high->_value;
	auto wall = low;
	for (auto current = low; current != high; current = current->_next){
		if (current->_value < pivot){
			swapValues(current, wall);
			wall = wall->_next;
		}
	}
	swapValues(wall, high);
	return wall;
}