#pragma once

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
		therefore there is no order. 
	*/
	template <class T>
	class LinkedList
	{
	private:
		Node<T>* head_node; // The Starting element of the linked list
		Node<T>* tail_node; // The Ending element of the linked list

	public:
		// Initialising an empty linked list
		LinkedList() : head_node(nullptr), tail_node(nullptr) {}

		/*
			Inserts a element with the passed in data to the front
			of the linked list.
		*/
		void prepend(T data)
		{
			// Create the new element
			Node<T>* temp = new Node<T>(data);

			// Check if the linked list is empty
			if (this->head_node == nullptr) {
				this->head_node = temp;
				this->tail_node = temp;
			}
			else {
				// Set the new element as reference as the new head_node
				this->head_node->prev = temp;

				// Set the links of the new element
				temp->next = this->head_node;

				// Set the head_node as the new element
				this->head_node = temp;
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
			if (this->head_node == nullptr) {
				this->head_node = temp;
				this->tail_node = temp;
			}
			else {
				// Set the new element as reference as the new tail_node
				this->tail_node->next = temp;

				// Set the links of the new element
				temp->prev = this->tail_node;

				// Set the tail_node as the new element
				this->tail_node = temp;
			}
		}

		/*
			Removes a given element from the linked list and repairs
			the broken links.
		*/
		void remove(T data)
		{
			// If the list is empty do nothing
			if (this->head_node == nullptr || this->tail_node == nullptr) return;

			// If there is only one element in the list, empty the list
			if (this->head_node->data == data && this->head_node == this->tail_node) {
				this->head_node = nullptr;
				this->tail_node = nullptr;
				return;
			}

			// If the element to remove is the head_node, set the head_node's next
			// element to the new head_node and repair links.
			if (this->head_node->data == data) {
				// Repair links
				this->head_node->next->prev = nullptr;

				// Set new head_node
				this->head_node = this->head_node->next;
				return;
			}

			// If the element to remove is the tail_node, set the tail_node's previous
			// element to the new tail_node and repair links.
			if (this->tail_node->data == data) {
				// Repair links
				this->tail_node->prev->next = nullptr;

				// Set new head_node
				this->tail_node = this->tail_node->prev;
				return;
			}

			// Search the linked list from each end and narrow the search
			// Searching: head_node -> data <- tail_node
			Node<T>* current_front = this->head_node->next;
			Node<T>* current_back = this->tail_node->prev;
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
				if (current_front == nullptr || current_back == nullptr) break;
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);
		}

		bool contains(T data) {
			// If the list is empty then it's not in the list
			if (this->head_node == nullptr || this->tail_node == nullptr) return false;

			// Check head_node and tail_node
			if (this->head_node->data == data) return true;
			if (this->tail_node->data == data) return true;

			// Search the linked list from each end and narrow the search
			// Searching: head_node -> data <- tail_node
			Node<T>* current_front = this->head_node->next;
			Node<T>* current_back = this->tail_node->prev;
			do
			{
				// Check if data is in the list
				if (current_front->data == data) return true;
				if (current_back->data == data) return true;

				// Iterate
				current_front = current_front->next;
				current_back = current_back->prev;

				// Just incase it gets out of order
				if (current_front == nullptr || current_back == nullptr) break;
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);
			// Doens't contain data
			return false;
		}

		void insert_after(T key, T data) {
			// If the list is empty then it's not in the list
			if (this->head_node == nullptr || this->tail_node == nullptr)
			{
				this->append(data);
				return;
			}

			// Create the new element
			Node<T>* temp = new Node<T>(data);

			// If key is head_node
			if (this->head_node->data == key) {
				temp->next = this->head_node->next;
				temp->prev = this->head_node;

				this->head_node->next->prev = temp;
				this->head_node->next = temp;
				return;
			}

			// If key is tail_node
			if (this->head_node->data == key) {
				this->append(data);
				return;
			}

			// Searching: head_node -> data <- tail_node
			Node<T>* current_front = this->head_node->next;
			Node<T>* current_back = this->tail_node->prev;
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
				if (current_front == nullptr || current_back == nullptr) break;
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);

			// Key isn't in linked list
			return;
		}

		void insert_before(T key, T data) {
			// If the list is empty then it's not in the list
			if (this->head_node == nullptr || this->tail_node == nullptr)
			{
				this->prepend(data);
				return;
			}

			// Create the new element
			Node<T>* temp = new Node<T>(data);

			// If key is head_node
			if (this->head_node->data == key) {
				this->prepend(data);
				return;
			}

			// If key is tail_node
			if (this->head_node->data == key) {
				temp->next = this->head_node;

				this->head_node->prev = temp;
				return;
			}

			// Searching: head_node -> data <- tail_node
			Node<T>* current_front = this->head_node->next;
			Node<T>* current_back = this->tail_node->prev;
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
				if (current_front == nullptr || current_back == nullptr) break;
				if (current_front->prev == current_back || current_back->next == current_front) break;
			} while (current_front != current_back);

			// Key isn't in linked list
			return;
		}

#ifdef KRAKEN_DEBUG
#include <iostream>
		void display_debug() {
			if (this->head_node == nullptr) {
				std::cout << "Linked List is Empty" << std::endl;
				return;
			}

			Node<T>* current = this->head_node;
			while (current != this->tail_node)
			{
				std::cout << current->data << " -> ";
				current = current->next;
			}
			std::cout << this->tail_node->data << std::endl;
		}
#endif
		/*
			The iterator will allow forward and reverse iteration
			through a linked list.
		*/
		class iterator
		{
		public:
			iterator() : current(nullptr) { }
			iterator(Node<T>* ptr) : current(ptr) { }

			// Set iterator
			iterator operator=(const iterator& other) 
			{ 
				this->current = other.current;
				return *this; 
			}

			// Increment post and pre
			iterator operator++() 
			{ 
				this->current = this->current->next;
				return *this; 
			}
			iterator operator++(int x) 
			{
				iterator i = *this;
				this->current = this->current->next;
				return i;
			}

			// Decrement post and pre
			iterator operator--() 
			{ 
				this->current = this->current->prev;
				return *this; 
			}
			iterator operator--(int x) 
			{ 
				iterator i = *this; 
				this->current = this->current->prev;
				return i;
			}

			// Getting data from iterator
			const T& operator*() { return this->current->data; }
			const Node<T>* operator->() { return this->current; }

			// Comparisons
			const bool operator==(const iterator& rhs) { return this->current == rhs.current; }
			const bool operator!=(const iterator& rhs) { return this->current != rhs.current; }

			// Decement and Increment by a given step size
			const iterator operator-(const int& step) 
			{ 
				for (int i = 0; i < step; i++) {
					this->current = this->current->prev;
				}
				return this->current; 
			}
			const iterator operator+(const int& step)
			{
				for (int i = 0; i < step; i++) {
					this->current = this->current->next;
				}
				return this->current;
			}

			void remove()
			{
				if (this->current == nullptr) return;
				if (this->current->next == nullptr && this->current->prev == nullptr) return;
				
				if (this->current->next == nullptr) {
					this->current->prev->next = nullptr;
					return;
				}
				if (this->current->prev == nullptr) {
					this->current->next->prev = nullptr;
					return;
				}

				this->current->next->prev = this->current->prev;
				this->current->prev->next = this->current->next;
			}

		private:
			Node<T>* current;
		};

		// Begin and end of list for iterating
		iterator begin() { return iterator(this->head_node); }
		iterator end() { return iterator(this->tail_node->next); }
		iterator tail() { return iterator(this->tail_node); }
	};	
}