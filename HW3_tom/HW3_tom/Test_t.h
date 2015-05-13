#pragma once
#include <string>
#include <ostream>
#include "virtIO_t.h"
#include "asciiIO_t.h"
#include "binIO_t.h"

class Test_t
{
private:
	virtIO_t* file;
public:
	Test_t(){
		file = NULL;
	}

	~Test_t()
	{
		delete file;
	}

	void openAsciiFile()
	{
		string pathpName, accessMode;

		if (file != NULL)
			delete file;
		cout << "\nEnter file path + name: ";
		cin >> pathpName;
		cout << "Choose access mode ['r','w','a','r+','w+','a+']: ";
		cin >> accessMode;
		while (!checkAsciiAccess(accessMode))
		{
			cout << "\nChoose a correct access mode ['r','w','a','r+','w+','a+']: ";
			cin >> accessMode;
		}
		file = new asciiIO_t(pathpName, accessMode);
	}

	void openBinFile()
	{
		string pathpName, accessMode;

		if (file != NULL)
			delete file;
		cout << "\nEnter file path + name: ";
		cin >> pathpName;
		cout << "Choose access mode ['rb','wb','ab','r+b','w+b','a+b']: ";
		cin >> accessMode;
		while (!checkBinAccess(accessMode))
		{
			cout << "\nChoose a correct access mode ['rb','wb','ab','r+b','w+b','a+b']: ";
			cin >> accessMode;
		}
		file = new binIO_t(pathpName, accessMode);
	}

	void write2File()
	{
		if (checkFile(file))
			writeToFile(*file);	
	}

	void readFromFile()
	{
		if (checkFile(file))
			readFromFile(*file);
	}

	void  printPath()
	{
		if (checkFile(file))
			cout << file->getPath() << endl;
	}

	void printAccessMode() 
	{ 
		if (checkFile(file))
			cout << file->getMode() << endl;
	}

	void printStatus()
	{
		if (checkFile(file))
			printFileStatus(file->getStatus());
	}

	void printFileLength()
	{
		if (checkFile(file))
			cout << file->getFileLength() << endl;
	}

	void flush()
	{
		if (checkFile(file))
			file->flush();
	}

	void movePointer()
	{
		if (checkFile(file)){
			int pos;
			cout << "\nWhere do you want to move the pointer: ";
			cin >> pos;
			file[pos];
		}
	}

	bool checkAsciiAccess(const string access)
	{
		regex reg("r|r\\+|w|w\\+|a|a\\+");
		if (regex_match(access, reg))
		{
			return true;
		}
		return false;
	}

	bool checkBinAccess(const string access) const
	{
		regex reg("rb|rb\\+|r\\+b|wb|wb\\+|w\\+b|ab|ab\\+|a\\+b");
		if (regex_match(access, reg))
		{
			return true;
		}
		return false;
	}

	void writeToFile(virtIO_t& file){
		int length;
		char ui;
		char c; short s; int i; long l; float f; double d;
		char buffer[1024];
		string buffStr;
		bool cont = true;
		while (cont)
		{
			printReadWriteOptions();
			cin >> ui;
			cout << "Enter value to write: ";
			try
			{
				switch (ui){
				case '1':
					cin >> c;
					file << c;
					break;
				case '2':
					cin >> s;
					file << s;
					break;
				case '3':
					cin >> i;
					file << i;
					break;
				case '4':
					cin >> l;
					file << l;
					break;
				case '5':
					cin >> f;
					file << f;
					break;
				case '6':
					cin >> d;
					file << d;
					break;
				case '7':
					cin.get();
					getline(cin, buffStr);
					strcpy(buffer, buffStr.c_str());
					file << buffer;
					break;
				case '8':
					cin.get();
					getline(cin, buffStr);
					strcpy(buffer, buffStr.c_str());
					cout << "Enter length: ";
					cin >> length;
					file.write(buffer, sizeof(char), length);
					break;
					
				default:
					cont = false;
					break;
				}
			}
			catch (virtIO_t::IOErr_t err)
			{
				cout << "" << err.getErrMsg() << endl;
				file.clearStatus();
			}
		}
	}

	void readFromFile(virtIO_t& file){
		int length;
		char ui;
		char c; short s; int i; long l; float f; double d;
		char buffer[1024];

		bool cont = true;
		while (cont)
		{
			printReadWriteOptions();
			cin >> ui;
			try
			{
				switch (ui){
				case '1':
					file >> c;
					cout << c;
					break;
				case '2':
					file >> s;
					cout << s;
					break;
				case '3':
					file >> i;
					cout << i;
					break;
				case '4':
					file >> l;
					cout << l;
					break;
				case '5':
					file >> f;
					cout << f;
					break;
				case '6':
					file >> d;
					cout << d;
					break;
				case '7':
					cout << "Enter length: ";
					cin >> length;
					file >> buffer;
					for (int k = 0; k < length; ++k)
						cout << buffer[k];
					break;
				case '8':
					cout << "Enter length: ";
					cin >> length;
					file.read(buffer, sizeof(char), length);
					for (int k = 0; k < length; ++k)
						cout << buffer[k];
					break;
				default:
					cont = false;
					break;
				}
			}
			catch (virtIO_t::IOErr_t err)
			{
				cout << "" << err.getErrMsg() << endl;
				file.clearStatus();
			}
		}
	}

	void printFileStatus(statusCode s){
		switch (s){
		case ok_e:
			cout << "ok_e" << endl;
			break;
		case cant_open_file_e:
			cout << "cant_open_file_e" << endl;
			break;
		case bad_access_e:
			cout << "bad_access_e" << endl;
			break;
		case writeErr_e:
			cout << "writeErr_e" << endl;
			break;
		case readErr_e:
			cout << "readErr_e" << endl;
			break;
		case closeErr_e:
			cout << "closeErr_e" << endl;
			break;
		case general_error_e:
			cout << "general_error_e" << endl;
			break;
		case read_after_eof_e:
			cout << "read_after_eof_e" << endl;
			break;
		case file_not_open_e:
			cout << "file_not_open_e" << endl;
			break;
		case file_already_open_e:
			cout << "file_already_open_e" << endl;
			break;
		default:
			cout << "Undefined status" << endl;
			break;
		}
	}

	bool checkFile(virtIO_t* file)
	{
		if (file == NULL)
		{
			cout << "No file - please open a file first" << endl;
			return false;
		}
		return true;
	}

	void printReadWriteOptions()
	{
		cout << "\nYour options are:" << endl
			<< "1 - char" << endl
			<< "2 - short" << endl
			<< "3 - int" << endl
			<< "4 - long" << endl
			<< "5 - float" << endl
			<< "6 - double" << endl
			<< "7 - char*" << endl
			<< "8 - using read/write functions" << endl
			<< "0 - back to main menu" << endl
			<< "choose: ";
	}
};

