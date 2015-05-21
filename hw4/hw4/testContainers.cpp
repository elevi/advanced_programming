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
	FIND,
	COUNT,
	PRINT,
	APPENND,
	PREPENR,
	IS_EMPTY,
	GET_FIRST_ELEMENT,
	EXIT
} Options;
//
////-------------------------------------------------------------------
//
const string optionsName[] = { "Insert",
"Remove",
"Remove All",
"Find",
"Count",
"Print",
"Append",
"Prepend",
"is Empty?",
"Get first element",
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

				break;
			case REMOVE_ALL:

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
			{
				try{
					T firstElement = container.getFirstElement();
					cout << "container first element is " << firstElement << endl;
				}
				catch (tEmptyException& ex){
					cout << "[ERROR] details: " << ex.what() << endl;
					break;
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

