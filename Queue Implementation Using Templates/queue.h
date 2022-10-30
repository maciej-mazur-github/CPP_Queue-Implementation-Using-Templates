#pragma once
#include "doubly_linked_list.h"


template <class t>
class Queue;

template <class T>
ostream& operator<<(ostream& out, typename const Queue<T>& arg);


template <class T>
class Queue : private List<T>    // private inheritance in order to hide all List<T> mechanisms from the Client, still allowing Queue to use them internally
{
public:
	Queue() {}

	void push(T& arg)
	{
		List<T>::setChosenAfterLast();
		List<T>::addElement(arg);
	}

	T pop()
	{
		if (!List<T>::firstNodePtr)
			return NULL;

		List<T>::setChosenAsFirst();
		T temp = *(List<T>::firstNodePtr->objPtr);
		List<T>::removeChosenElement();
		return temp;
	}

	friend ostream& operator<< <> (ostream& out, typename const Queue<T>& arg);
	void loadArrayOfObjects(T arr[], int arraySize);
};


template <class T>
ostream& operator<<(ostream& out, typename const Queue<T>& arg)
{
	if (!(arg.List<T>::firstNodePtr))
		return out;

	typename List<T>::Node* bishop = arg.firstNodePtr;

	out << "\n";

	for (; bishop; bishop = bishop->nextNodePtr)
	{
		out << *(bishop->objPtr) << "\t";
	}

	out << "\n\n";

	return out;
}


template <>
string Queue<string>::pop()
{
	if (!List<string>::firstNodePtr)
		return "";						// instead of NULL which would produce an error

	List<string>::setChosenAsFirst();
	string temp = *(List<string>::firstNodePtr->objPtr);
	List<string>::removeChosenElement();
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