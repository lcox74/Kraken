#pragma once
#include <iostream>
namespace Kraken {

	/*
	    A data Node that has a reference to the node 
		infront of it and behind it. Can be any datatype.
	*/
	template <class T> struct Node {
		T data;
		struct Node* next;
		struct Node* prev;

		Node(T d) : data(d), next(nullptr), prev(nullptr) {}
	};

	/*
		A Bi-directional linear collection of data elements,
		each element points to the next and previous element
		therefore there is no order. This Linked list also 
		cycles around.
	*/
	template <class T>
	class LinkedList
	{
	private:
		Node<T>* head; // The Starting element of the linked list
		Node<T>* tail; // The Ending element of the linked list

	public:
		// Initialising an empty linked list
		LinkedList() : head(nullptr), tail(nullptr) {}

		/*
			Inserts a element with the passed in data to the front
			of the linked list.
		*/
		void prepend(T data)
		{
			// Create the new element
			Node<T>* temp = new Node<T>(data);

			// Check if the linked list is empty
			if (this->head == nullptr) {
				temp->next = temp;
				temp->prev = temp;

				this->head = temp;
				this->tail = temp;
			}
			else {
				// Set the new element as reference as the new Head
				this->head->prev = temp;
				this->tail->next = temp;

				// Set the links of the new element
				temp->next = this->head;
				temp->prev = this->tail;

				// Set the head as the new element
				this->head = temp;
			}
		}

		/*
			Appends a element with the passed in data to the end
			of the linked list.
		*/
		void append(T data)
		{
			// Create the new element
			Node<T>* temp = new Node<T>(data);

			// Check if the linked list is empty
			if (this->head == nullptr) {
				temp->next = temp;
				temp->prev = temp;

				this->head = temp;
				this->tail = temp;
			}
			else {
				// Set the new element as reference as the new Tail
				this->tail->next = temp;
				this->head->prev = temp;

				// Set the links of the new element
				temp->next = this->head;
				temp->prev = this->tail;

				// Set the tail as the new element
				this->tail = temp;
			}
		}

		/*
			Removes a given element from the linked list and repairs
			the broken links.
		*/
		void remove(T data)
		{
			// If the list is empty do nothing
			if (this->head == nullptr || this->tail == nullptr) return;

			// If there is only one element in the list, empty the list
			if (this->head->data == data && this->head == this->tail) {
				this->head = nullptr;
				this->tail = nullptr;
				return;
			}

			// If the element to remove is the head, set the head's next
			// element to the new head and repair links.
			if (this->head->data == data) {
				// Repair links
				this->tail->next = this->head->next;
				this->head->next->prev = this->tail;

				// Set new head
				this->head = this->head->next;
				return;
			}

			// If the element to remove is the tail, set the tail's previous
			// element to the new tail and repair links.
			if (this->tail->data == data) {
				// Repair links
				this->head->prev = this->tail->prev;
				this->tail->prev->next = this->head;

				// Set new head
				this->tail = this->tail->prev;
				return;
			}

			// Search the linked list from each end and narrow the search
			// Searching: head -> data <- tail
			Node<T>* current_front = this->head->next;
			Node<T>* current_back = this->tail->prev;
			do
			{
				// Check if data is in the list
				if (current_front->data == data) {
					current_front->prev->next = current_front->next;
					current_front->next->prev = current_front->prev;
					return;
				}
				if (current_back->data == data) {
					current_back->prev->next = current_back->next;
					current_back->next->prev = current_back->prev;
					return;
				}

				// Iterate
				current_front = current_front->next;
				current_back = current_back->prev;

				// Just incase it gets out of order
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);
		}

		bool contains(T data) {
			// If the list is empty then it's not in the list
			if (this->head == nullptr || this->tail == nullptr) return false;

			// Check head and tail
			if (this->head->data == data) return true;
			if (this->tail->data == data) return true;

			// Search the linked list from each end and narrow the search
			// Searching: head -> data <- tail
			Node<T>* current_front = this->head->next;
			Node<T>* current_back = this->tail->prev;
			do
			{
				// Check if data is in the list
				if (current_front->data == data) return true;
				if (current_back->data == data) return true;

				// Iterate
				current_front = current_front->next;
				current_back = current_back->prev;

				// Just incase it gets out of order
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);
			// Doens't contain data
			return false;
		}

		void insert_after(T key, T data) {
			// If the list is empty then it's not in the list
			if (this->head == nullptr || this->tail == nullptr)
			{
				this->append(data);
				return;
			}

			// Create the new element
			Node<T>* temp = new Node<T>(data);

			// If key is head
			if (this->head->data == key) {
				temp->next = this->head->next;
				temp->prev = this->head;

				this->head->next->prev = temp;
				this->head->next = temp;
				return;
			}

			// If key is tail
			if (this->head->data == key) {
				this->append(data);
				return;
			}

			// Searching: head -> data <- tail
			Node<T>* current_front = this->head->next;
			Node<T>* current_back = this->tail->prev;
			do
			{
				// Check if data is in the list
				if (current_front->data == key) {
					temp->next = current_front->next;
					temp->prev = current_front;

					current_front->next->prev = temp;
					current_front->next = temp;
					return;
				}
				if (current_back->data == key) {
					temp->next = current_back->next;
					temp->prev = current_back;

					current_back->next->prev = temp;
					current_back->next = temp;
					return;
				}

				// Iterate
				current_front = current_front->next;
				current_back = current_back->prev;

				// Just incase it gets out of order
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);

			// Key isn't in linked list
			return;
		}

		void insert_before(T key, T data) {
			// If the list is empty then it's not in the list
			if (this->head == nullptr || this->tail == nullptr)
			{
				this->prepend(data);
				return;
			}

			// Create the new element
			Node<T>* temp = new Node<T>(data);

			// If key is head
			if (this->head->data == key) {
				this->prepend(data);
				return;
			}

			// If key is tail
			if (this->head->data == key) {
				temp->next = this->head;
				temp->prev = this->tail;

				this->head->prev = temp;
				this->tail->next = temp;
				return;
			}

			// Searching: head -> data <- tail
			Node<T>* current_front = this->head->next;
			Node<T>* current_back = this->tail->prev;
			do
			{
				// Check if data is in the list
				if (current_front->data == key) {
					temp->next = current_front;
					temp->prev = current_front->prev;

					current_front->prev = temp;
					current_front->prev->next = temp;
					return;
				}
				if (current_back->data == key) {
					temp->next = current_back;
					temp->prev = current_back->prev;

					current_back->prev = temp;
					current_back->prev->next = temp;
					return;
				}

				// Iterate
				current_front = current_front->next;
				current_back = current_back->prev;

				// Just incase it gets out of order
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);

			// Key isn't in linked list
			return;
		}

#ifdef KRAKEN_DEBUG
#include <iostream>
		void display_debug() {
			if (this->head == nullptr) {
				std::cout << "Linked List is Empty" << std::endl;
				return;
			}

			Node<T>* current = this->head;
			while (current != this->tail)
			{
				std::cout << current->data << " -> ";
				current = current->next;
			}
			std::cout << this->tail->data << std::endl;
		}
#endif
	};

}