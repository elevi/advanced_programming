#ifndef BINIO_T_H_
#define BINIO_T_H_

#include "virtIO_t.h"

class binIO_t : public virtIO_t
{// supports IO for ASCII files
public:
	binIO_t();
	binIO_t(string pathName, string access);
	~binIO_t();

	// operators
	virtIO_t & operator<<(const char *s)			throw(IOErr_t);
	virtIO_t & operator<<(const char& c)			throw(IOErr_t);
	virtIO_t & operator<<(const unsigned char& uc)	throw(IOErr_t);
	virtIO_t & operator<<(const short& s)			throw(IOErr_t);
	virtIO_t & operator<<(const unsigned short& us)	throw(IOErr_t);
	virtIO_t & operator<<(const int& i)				throw(IOErr_t);
	virtIO_t & operator<<(const unsigned int& ui)	throw(IOErr_t);
	virtIO_t & operator<<(const long& l)			throw(IOErr_t);
	virtIO_t & operator<<(const unsigned long& ul)	throw(IOErr_t);
	virtIO_t & operator<<(const double& d)			throw(IOErr_t);
	virtIO_t & operator<<(const float& f)			throw(IOErr_t);
	
	virtIO_t & operator>>(char *s)					throw(IOErr_t);
	virtIO_t & operator>>(char& c)					throw(IOErr_t);
	virtIO_t & operator>>(unsigned char& uc)		throw(IOErr_t);
	virtIO_t & operator>>(short& s)					throw(IOErr_t);
	virtIO_t & operator>>(unsigned short& us)		throw(IOErr_t);
	virtIO_t & operator>>(int& i)					throw(IOErr_t);
	virtIO_t & operator>>(unsigned int& ui)			throw(IOErr_t);
	virtIO_t & operator>>(long& l)					throw(IOErr_t);
	virtIO_t & operator>>(unsigned long& ul)		throw(IOErr_t);
	virtIO_t & operator>>(double& d)				throw(IOErr_t);
	virtIO_t & operator>>(float& f)					throw(IOErr_t);	

private:
	template <typename T> binIO_t & binaryWrite(const T  &t) throw(virtIO_t::IOErr_t) {
		if (fwrite(&t, sizeof(t), 1, m_file) != 1){
			setStatus(writeErr_e);
			//m_status = writeErr_e;
			throw IOErr_t("Write failed.");
		}
		return *this;
	}

	template <typename T> binIO_t & binaryRead(T &t) throw(virtIO_t::IOErr_t) {
		if (getPosition() >= getFileLength()){
			setStatus(read_after_eof_e);
			//m_status = read_after_eof_e;
			throw IOErr_t("trying to read after eof.");
		}
		else{
			if (fread(&t, sizeof(t), 1, m_file) != 1){
				setStatus(readErr_e);
				//m_status = readErr_e;
				throw IOErr_t("Read failed.");
			}
		}
		return *this;
	}
};

#endif