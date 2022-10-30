#include <iostream>
#include "queue.h"
#include "person.h"


int main()
{
	int howManyElementsInArray;

	cout << "****************************\n";
	cout << "Initiating ex1 queue:\n";
	Queue<int> ex1;
	int intArray[] = { 1, 2, 3, 4 };
	howManyElementsInArray = sizeof(intArray) / sizeof(intArray[0]);
	ex1.loadArrayOfObjects(intArray, howManyElementsInArray);
	cout << "\n****************************\n";

	cout << "Current ex1 status:\n";
	cout << ex1;
	cout << "\nNow popping \"" << ex1.pop() << endl;
	cout << "Current ex1 status after using pop():\n";
	cout << ex1;
	cout << "\n****************************\n";
	


	cout << "\n\n****************************\n";
	cout << "Initiating ex2 queue:\n";
	Queue<Person> ex2;

	Person person1("Lois");
	Person person2("Damian");

	ex2.push(person1);
	ex2.push(person2);

	cout << "\nCurrent ex2 status:\n";
	cout << ex2;


	cout << "\n\n****************************\n";
	cout << "Initiating ex3 queue:\n";
	Queue<string> ex3;
	string stringArray[] = {"Gordon", "Ramsey", "And", "Others"};
	howManyElementsInArray = sizeof(stringArray) / sizeof(stringArray[0]);
	ex3.loadArrayOfObjects(stringArray, howManyElementsInArray);
	cout << "\nCurrent ex3 status:\n";
	cout << ex3;



}