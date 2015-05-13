#ifndef ASCIIIO_T_H_
#define ASCIIIO_T_H_
#include "virtIO_t.h"


class asciiIO_t : public virtIO_t
{ // supports IO for ASCII files
public:
	asciiIO_t();
	asciiIO_t(const string pathName, const string access);
	~asciiIO_t();

	// operators
	virtIO_t & operator<<(const char *s);
	virtIO_t & operator<<(const char& c);
	virtIO_t & operator<<(const unsigned char& uc);
	virtIO_t & operator<<(const short& s);
	virtIO_t & operator<<(const unsigned short& us);
	virtIO_t & operator<<(const int& i)	;
	virtIO_t & operator<<(const unsigned int& ui);
	virtIO_t & operator<<(const long& l);
	virtIO_t & operator<<(const unsigned long& ul);
	virtIO_t & operator<<(const double& d);
	virtIO_t & operator<<(const float& f);

	virtIO_t & operator>>(char *s);
	virtIO_t & operator>>(char& c);
	virtIO_t & operator>>(unsigned char& uc);
	virtIO_t & operator>>(short& s);
	virtIO_t & operator>>(unsigned short& us);
	virtIO_t & operator>>(int& i);
	virtIO_t & operator>>(unsigned int& ui);
	virtIO_t & operator>>(long& l);
	virtIO_t & operator>>(unsigned long& ul);
	virtIO_t & operator>>(double& d);
	virtIO_t & operator>>(float& f);

private:
	template <typename T> asciiIO_t writeAscii(const char * writeFormat, T& t){
		if (fprintf(m_file, writeFormat, t) <= 0){
			setStatus(writeErr_e);
			//m_status = writeErr_e;
			throw IOErr_t("Write error!");
		}
		return *this;
	}

	template <typename T> asciiIO_t readAscii(const char * readFormat, T* t){
		if (!feof(m_file) && (getPosition() < getFileLength())){
			if (fscanf(m_file, readFormat, t) <= 0){
				setStatus(readErr_e);
				//m_status = readErr_e;
				throw IOErr_t("Read error!");;
			}
		}
		else{
			setStatus(read_after_eof_e);
			//m_status = read_after_eof_e;
			throw IOErr_t("trying to Read after eof.");;
		}
		return *this;
	}
};

#endif