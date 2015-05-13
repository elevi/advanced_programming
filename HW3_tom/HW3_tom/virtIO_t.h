#ifndef VIRTIO_T
#define VIRTIO_T

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <cstdio>
#include <cerrno>
#include <string.h>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

enum statusCode {
	ok_e,
	cant_open_file_e,
	bad_access_e,
	read_after_eof_e,
	file_not_open_e,
	file_already_open_e,
	closeErr_e,
	writeErr_e,
	readErr_e,
	general_error_e
};

class virtIO_t {

public:
	// no Ctor/Dtor - pure abstract class 

	class IOErr_t{
	private:
		const char* errMsg;
	public:
		IOErr_t(const char* msg) :errMsg(msg){};
		const char* getErrMsg() const { return errMsg; };
	};

	//getters/setters
	const string getPath() const { return m_path; }
	const string getMode() const { return m_accessMode; }
	long int getFileLength(); // can change status
	const statusCode getStatus() const { return m_status; };
	void setStatus(statusCode status) { m_status = status; };
	long int getPosition(); // can change status

	void clearStatus() { setStatus(ok_e); };
	void initPosition();

	// more functionalities
	void open();
	void open(const string pathname, const string access);
	void close();
	void flush();
	
	virtual void  read(void* c, unsigned int size, unsigned int count);
	virtual void  write(const void* c, unsigned int size, unsigned int count);

	// overloading operators
	void operator,(int l);
	void operator[](int pos); //fseek
	virtIO_t & operator<<(const void* c);
	virtIO_t & operator>>(void* c);
	
	// pure abstarct operators
	virtual virtIO_t & operator<<(const char* c) = 0; 
	virtual virtIO_t & operator>>(char* c) = 0;

	virtual virtIO_t & operator<<(const char& c) = 0;
	virtual virtIO_t & operator>>(char& c) = 0;

	virtual virtIO_t & operator<<(const unsigned char& c) = 0;
	virtual virtIO_t & operator>>(unsigned char& c) = 0;

	virtual virtIO_t & operator<<(const short& c) = 0;
	virtual virtIO_t & operator>>(short& c) = 0;

	virtual virtIO_t & operator<<(const unsigned short& c) = 0;
	virtual virtIO_t & operator>>(unsigned short& c) = 0;

	virtual virtIO_t & operator<<(const int& c) = 0;
	virtual virtIO_t & operator>>(int& c) = 0;

	virtual virtIO_t & operator<<(const unsigned int& c) = 0;
	virtual virtIO_t & operator>>(unsigned int& c) = 0;

	virtual virtIO_t & operator<<(const long& c) = 0;
	virtual virtIO_t & operator>>(long& c) = 0;

	virtual virtIO_t & operator<<(const unsigned long& c) = 0;
	virtual virtIO_t & operator>>(unsigned long& c) = 0;

	virtual virtIO_t & operator<<(const float& c) = 0;
	virtual virtIO_t & operator>>(float& c) = 0;

	virtual virtIO_t & operator<<(const double& c) = 0;
	virtual virtIO_t & operator>>(double& c) = 0;

protected: 
	string m_path;
	string m_accessMode;
	FILE *m_file;
	char* m_buffer;
	int lastIOCommand; // 0 - read, 1 - write
	statusCode m_status;

	//virtual statusCode check_access(const string access) const = 0;

};
#endif