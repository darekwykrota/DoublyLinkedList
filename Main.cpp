#include "DoublyLinkedList.h"
#include "DoublyLinkedList.cpp"


int main(){

	DoublyLinkedList<int> dll;	
	
	dll.pushBack(4);
	dll.pushBack(8);
	dll.pushFront(-1);
	dll.pushBack(5);
	dll.pushFront(23);
	dll.pushBack(6);

	std::cout << dll << std::endl;
	dll.sort();
	std::cout << dll << std::endl;
	dll.popFront();

	auto node = dll.find(6);
	if (node){
		dll.erase(node);
	}

	std::cout << dll << std::endl;

	return 0;
}