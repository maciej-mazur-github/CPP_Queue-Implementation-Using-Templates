#pragma once
#include "Doubly_linked_list.h"


template <class t>
class Queue;

template <class T>
ostream& operator<<(ostream& out, typename const Queue<T>& arg);


template <class T>
class Queue : private List<T>    // private inheritance in order to hide all List<T> mechanisms from the Client, still allowing Queue to use them internally
{
public:
	Queue() {}
		//: Queue::list<T>() {}

	void push(T& arg)
	{
		List<T>::set_chosen_after_last();
		List<T>::add_element(arg);
	}

	T pop()
	{
		if (!List<T>::first_node_ptr)
			return NULL;

		List<T>::set_chosen_as_first();
		T temp = *(List<T>::first_node_ptr->obj_ptr);
		List<T>::remove_chosen_element();
		return temp;
	}

	friend ostream& operator<< <> (ostream& out, typename const Queue<T>& arg);
	void loadArrayOfObjects(T arr[], int arraySize);
};


template <class T>
ostream& operator<<(ostream& out, typename const Queue<T>& arg)
{
	if (!(arg.List<T>::first_node_ptr))
		return out;

	typename List<T>::node* bishop = arg.first_node_ptr;

	out << "\n";

	for (; bishop; bishop = bishop->next_node_ptr)
	{
		out << *(bishop->obj_ptr) << "\t";
	}

	out << "\n\n";

	return out;
}


template <>
string Queue<string>::pop()
{
	if (!List<string>::first_node_ptr)
		return "";

	List<string>::set_chosen_as_first();
	string temp = *(List<string>::first_node_ptr->obj_ptr);
	List<string>::remove_chosen_element();
	return temp;
}



template <class T>
void Queue<T>::loadArrayOfObjects(T arr[], int arraySize)
{
	cout << "Progress:\t";

	for (int i = 0; i < arraySize; i++) {
		this->push(arr[i]);
		cout << ".";
	}
}