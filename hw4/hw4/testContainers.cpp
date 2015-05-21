#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "tContainer_t.h"
#include "t_Exceptions.h"

using namespace std;
typedef enum
{
	INSERT,
	REMOVE,
	REMOVE_ALL,
	DELETE,
	DELETE_ALL,
	FIND,
	COUNT,
	PRINT,
	APPENND,
	PREPENR,
	IS_EMPTY,
	GET_FIRST_ELEMENT,
	GET_LAST_ELEMENT,
	FIND_ELEMENT_BY_VALUE,
	EXIT
} Options;
//
////-------------------------------------------------------------------
//
const string optionsName[] = { "Insert",
"Remove",
"Remove All",
"Delete",
"Delete All",
"Find",
"Count",
"Print",
"Append",
"Prepend",
"is Empty?",
"Get first element",
"Get last element",
"Find By Value",
"exit" };

////-------------------------------------------------------------------
////																			  
////						HELP FUNCTIOMS IMPLEMENTATION						  	
////-------------------------------------------------------------------

void PrintOptions()
{
	cout << "please choose your options:" << endl;
	for (int i = 0; i <= EXIT; i++)
	{
		cout << i << ". " << optionsName[i] << endl;
	}
}


void PrintTypeOptions(){
	cout << "please choose container type : " << endl;
	cout << "(0) int (1) double " << endl;
}

template<typename T, template <typename, typename> class Container>
int runner(tContainer_t<T, Container>& container){
	unsigned int command;
	bool cont = true;
	while (cont) {
		PrintOptions();
		cin >> command;

		switch (command){
			case INSERT:
			{
				//TODO elevi verify no memory leak occurs
				T * elemetToInsert = new T[1];
				cout << "please enter new element value" << endl;
				cin >> *elemetToInsert;
				int currentSize = container.elementAmount();
				container.insert(elemetToInsert);
				if (currentSize + 1 != container.elementAmount()) {
					cout << "[ERROR] failed to insert new element" << endl;
				}
			}
			break;
			case REMOVE:
			{
				cout << "please insert elemnet value for removal" << endl;
				T elementForRemoval;
				cin >> elementForRemoval;
				try{
					T* removedElement = container.removeElementFromContainer(elementForRemoval);
				}
				catch (tElementDoesNotExistException& ex){
					cout << "[ERROR] failed to removed element value: " << elementForRemoval << " details: " << ex.what() << endl;
				}
			}
				break;
			case REMOVE_ALL:
			case DELETE_ALL:
			{
				cout << "current container size: " << container.elementAmount() << endl;
				string action = (command == REMOVE_ALL) ? "removing" : "deleting";
				cout << "start " << action << " elements from container..." << endl;
				int totoalRemoved = container.removeAllElementsFromContainer();
				action = (command == REMOVE_ALL) ? "removed" : "deleted";
				cout << "total elements " << action << " from container: " << totoalRemoved << endl;
				cout << "current container size: " << container.elementAmount() << endl;
			}
				break;
			case DELETE:
			{
				cout << "please insert a value for deletion" << endl;
				T elementForDeletion;
				cin >> elementForDeletion;
				try{
					T * deletedElement = container.deleteElementFromContainer(elementForDeletion);
				}
				catch (tElementDoesNotExistException& ex){
					cout << "[ERROR] failed to delete element value: " << elementForDeletion << " details: " << ex.what() << endl;
				}
			}
				break;
			case FIND:

				break;
			case COUNT:
				cout << "container elements count is: " << container.elementAmount() << endl;
				break;
			case PRINT:

				break;
			case APPENND:

				break;
			case PREPENR:

				break;
			case IS_EMPTY:
				cout << "check is empty result:" << container.isEmpty() << endl;
				break;
			case GET_FIRST_ELEMENT:
			case GET_LAST_ELEMENT:
			{
				try{
					T element = (command == GET_FIRST_ELEMENT) ? container.getFirstElement() : container.getLastElement();
					string position = (command == GET_FIRST_ELEMENT) ? "first" : "last";
					cout << "container " << position << " element is " << element << endl;
				}
				catch (tEmptyException& ex){
					cout << "[ERROR] details: " << ex.what() << endl;
					break;
				}
			}
				break;
			case FIND_ELEMENT_BY_VALUE:
			{
				cout << "please insert element value to find" << endl;
				T element;
				cin >> element;
				T * pointerToElementInContainer = container.findElementByValue(element);
				if (pointerToElementInContainer == 0){
					cout << "element not found" << endl;
				}
				else{
					cout << "element value is: " << *pointerToElementInContainer << endl;
				}
			}
				break;
			case EXIT:
				cont = false;
				break;
			default:
				cout << "Unknown command" << endl;

		}

	}
	return 0;
}

int main()
{
	unsigned int VectorOrList;


	cout << "please choose vector(0) or list(1)" << endl;
	cin >> VectorOrList;
	while (VectorOrList != 0 && VectorOrList != 1)
	{
		cout << "[ERROR] wrong input, please enter 0 for array and 1 for list" << endl;
		cin >> VectorOrList;
	}

	PrintTypeOptions();
	unsigned int type;
	cin >> type;
	while (type != 0 && type != 1)
	{
		cout << "[ERROR] wrong input" << endl;
		PrintTypeOptions();
		cin >> type;
	}


	if (VectorOrList == 0){
		if (type == 0){
			tContainer_t<int, vector> container;
			return runner(container);
		}
		else if (type == 1){
			tContainer_t<double, vector> container;
			return runner(container);
		}
	}
	else if (VectorOrList == 1){
		if (type == 0){
			tContainer_t<int, list> container;
			return runner(container);
		}
		else if (type == 1){
			tContainer_t<double, list> container;
			return runner(container);
		}
	}
	else {
		cout << "[ERROR] failed to initialize container" << endl;
		return -1;
	}


}

