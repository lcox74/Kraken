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
		void insert(T data)
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

			// Loop through the list to find the element to remove. The fix
			// the broken links
			Node<T>* current = this->head;
			do
			{
				if (current->next->data == data) {
					// Fix links which removes the element from the list
					current->next = current->next->next;
					current->next->next->prev = current;
					return;
				}
				current = current->next;
			} while (current != this->tail->next);
		}
	};

}