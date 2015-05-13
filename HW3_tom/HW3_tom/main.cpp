#include "stdafx.h"
#include "virtIO_t.h"
#include "asciiIO_t.h"
#include "binIO_t.h"
#include "Test_t.h"

int main(){
	bool cont = true;
	virtIO_t* file = NULL;
	string pathpName, accessMode;
	char c;

	Test_t* test = new Test_t();

	while (cont) {

		cout << "Your options are:" << endl
			<< "1 - Open a text file" << endl
			<< "2 - Open a binary file" << endl
			<< "3 - write to file" << endl
			<< "4 - read from file" << endl
			<< "5 - print path" << endl
			<< "6 - print access mode" << endl
			<< "7 - print status" << endl
			<< "8 - print file length" << endl
			<< "9 - flush the file" << endl
			<< "10 - set the file to a certain point" << endl
			<< "0 - quit" << endl
			<< "So What would you like to do? ";
		cin >> c;

		switch (c) {
		case '1':
			test->openAsciiFile();
			break;
		case '2':
			test->openAsciiFile();
			break;
		case '3':
			test->write2File();
			break;
		case '4':
			test->readFromFile();
			break;
		case '5':
			test->printPath();
			
			break;
		case '6':
			test->printAccessMode();
			break;
		case '7':
			test->printStatus();
			break;
		case '8':
			test->printFileLength();
			break;
		case '9':
			test->flush();
			break;
		case '10':
			test->movePointer();
			break;
		default:
			cont = false;
			break;
		}
	}
	delete file;
}