#pragma once

#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;



template <class T>
class List;

template <class T>
ostream& operator<<(ostream& out, const List<T>& arg);

template <class T>
class List
{
protected:
	struct Node
	{
		T* objPtr;
		Node* nextNodePtr;
		Node* previousNodePtr;
		Node()
			: nextNodePtr(NULL), previousNodePtr(NULL), objPtr(NULL) {}
	};

	Node* firstNodePtr;
	Node* lastNodePtr;
	Node* chosenNodePtr;

	int elementCounter;

public:
	List()
	{
		firstNodePtr = lastNodePtr = chosenNodePtr = NULL;
		elementCounter = 0;
	}

	friend ostream& operator<< <T>(ostream& out, const List<T>& arg);

	void addElement(T& obj);

	void printChosenElement() const
	{
		if (!firstNodePtr)
			return;

		else
			cout << chosenNodePtr->objPtr;
	}

	void setChosenAsFirst()
	{
		if (firstNodePtr)
			chosenNodePtr = firstNodePtr;
	}

	void setChosenAsLast()
	{
		if (lastNodePtr)
			chosenNodePtr = lastNodePtr;
	}

	void setChosenAfterLast()
	{
		chosenNodePtr = NULL;
	}

	Node* goToNextNode()
	{
		chosenNodePtr = chosenNodePtr->nextNodePtr;
		return chosenNodePtr;
	}

	Node* goToPreviousNode()
	{
		chosenNodePtr = chosenNodePtr->previousNodePtr;
		return chosenNodePtr;
	}

	void moveToPosition(int position)
	{
		if (!firstNodePtr)
			return;

		if (position >= elementCounter)
			setChosenAfterLast();
		else
		{
			setChosenAsFirst();

			for (int i = 0; i < position; i++)
			{
				goToNextNode();
			}
		}
	}

	void removeChosenElement();

	~List();

private:
	void addElementAsFirst(Node* newlyAddedNodePtr);
	void addElementAsLast(Node* newlyAddedNodePtr);
	void addElementInMiddle(Node* newlyAddedNodePtr);
	

	void removeLastElement();
	void removeFirstElement();
	void removeMiddleElement();
};
//##################################################################################
//##################################################################################


template <class T>
List<T>::~List()
{
	if (!firstNodePtr)  // stop doing anything if the list is empty
		return;

	Node* bishop;
	int i;
	cout << "\n\n";

	for (chosenNodePtr = firstNodePtr, i = 0; chosenNodePtr; i++)
	{
		bishop = chosenNodePtr->nextNodePtr;
		delete chosenNodePtr;
		chosenNodePtr = bishop;

		//cout << "Destruction of the " << i << " element" << endl;
	}
}



template <class T>
void List<T>::removeMiddleElement()
{
	typename List<T>::Node* previous_node = chosenNodePtr->previousNodePtr;
	typename List<T>::Node* next_node = chosenNodePtr->nextNodePtr;

	delete chosenNodePtr;
	previous_node->nextNodePtr = next_node;
	next_node->previousNodePtr = previous_node;
}


template <class T>
void List<T>::removeFirstElement()
{
	// 1-element list scenario has been covered in removeLastElement()

	if (firstNodePtr->nextNodePtr == lastNodePtr) // 2-element list scenario
	{
		delete firstNodePtr;
		firstNodePtr = lastNodePtr;  // the list becomes a 1-element one
		chosenNodePtr = firstNodePtr;
		firstNodePtr->previousNodePtr = NULL;
	}

	else
	{
		Node* second_node = firstNodePtr->nextNodePtr;
		delete firstNodePtr;
		firstNodePtr = second_node;
		chosenNodePtr = firstNodePtr;
		firstNodePtr->previousNodePtr = NULL;
	}
}


template <class T>
void List<T>::removeLastElement()  // 3 scenarios possible here
{
	if (firstNodePtr == lastNodePtr)  // if this is 1-element list then after the operation the list becomes empty
	{
		delete chosenNodePtr;    // free the memory

		firstNodePtr = lastNodePtr = chosenNodePtr = NULL;
		return;
	}

	else if (firstNodePtr->nextNodePtr == lastNodePtr)   // if this is a 2-element list
	{
		delete chosenNodePtr;
		lastNodePtr = chosenNodePtr = firstNodePtr;
		firstNodePtr->nextNodePtr = NULL;
		return;
	}

	else														// if the list has 3 or more elements
	{
		typename List<T>::Node* penultimate = lastNodePtr->previousNodePtr;
		delete lastNodePtr;
		penultimate->nextNodePtr = NULL;
		lastNodePtr = penultimate;
	}

}

template <class T>
void List<T>::removeChosenElement()
{
	if (!chosenNodePtr)   // if the list is empty or chosenNodePtr points at after the last element (is NULL)
		return;

	if (chosenNodePtr == lastNodePtr)
	{
		removeLastElement();
	}

	else if (chosenNodePtr == firstNodePtr)
	{
		removeFirstElement();
	}

	else
		removeMiddleElement();


	elementCounter--;
}


template <class T>
ostream& operator<<(ostream& out, const List<T>& arg)
{
	if (!(arg.firstNodePtr))
		return out;

	typename List<T>::Node* bishop = arg.firstNodePtr;

	for (; bishop; bishop = bishop->nextNodePtr)
	{
		out << *(bishop->objPtr) << "\t";
	}

	return out;
}



template <class T>
void List<T>::addElementInMiddle(Node* newlyAddedNodePtr)
{
	Node* previous_node = chosenNodePtr->previousNodePtr;
	previous_node->nextNodePtr = newlyAddedNodePtr;
	newlyAddedNodePtr->previousNodePtr = previous_node;
	newlyAddedNodePtr->nextNodePtr = chosenNodePtr;
	chosenNodePtr->previousNodePtr = newlyAddedNodePtr;
	chosenNodePtr = newlyAddedNodePtr;
}


template <class T>
void List<T>::addElementAsLast(Node* newlyAddedNodePtr)
{
	lastNodePtr->nextNodePtr = newlyAddedNodePtr;
	newlyAddedNodePtr->previousNodePtr = lastNodePtr;
	lastNodePtr = newlyAddedNodePtr;
}



template <class T>
void List<T>::addElementAsFirst(Node* newlyAddedNodePtr)
{
	if (!firstNodePtr)   // in case the list is empty yet
	{
		firstNodePtr = newlyAddedNodePtr;
		lastNodePtr = newlyAddedNodePtr;
	}
	else
	{
		newlyAddedNodePtr->nextNodePtr = firstNodePtr;
		firstNodePtr->previousNodePtr = newlyAddedNodePtr;
		firstNodePtr = newlyAddedNodePtr;
		chosenNodePtr = firstNodePtr;
	}
}

template <class T>
void List<T>::addElement(T& obj)
{
	Node* newNodePtr = new Node;
	newNodePtr->objPtr = &obj;

	if (!firstNodePtr || chosenNodePtr == firstNodePtr)    // if the list is empty or chosenNodePtr points at firstNodePtr
		addElementAsFirst(newNodePtr);
	else
	{
		if (!chosenNodePtr)
		{
			addElementAsLast(newNodePtr);
		}
		else
		{
			addElementInMiddle(newNodePtr);
		}
	}

	elementCounter++;
}


