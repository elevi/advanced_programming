#include "stdafx.h"

#include "asciiIO_t.h"


asciiIO_t::asciiIO_t()
{
	m_buffer = NULL;
	m_file = NULL;
	m_status = ok_e;
}

asciiIO_t::asciiIO_t(const string pathname, const string access)
{
	m_buffer = NULL;
	m_file = NULL;
	open(pathname, access);
}

asciiIO_t::~asciiIO_t()
{
	if (m_file)
		fclose(m_file);
}

virtIO_t & asciiIO_t::operator<<(const char* s)				{ return writeAscii("%s ", s); }
virtIO_t & asciiIO_t::operator>>(char* s)					{ return readAscii("%s ", s); }

virtIO_t & asciiIO_t::operator<<(const char& c)				{ return writeAscii("%c ", c); }
virtIO_t & asciiIO_t::operator>>(char& c)					{ return readAscii("%c ", &c); }

virtIO_t & asciiIO_t::operator<<(const unsigned char& uc)	{ return writeAscii("%c ", uc); }
virtIO_t & asciiIO_t::operator>>(unsigned char& uc)			{ return readAscii("%c ", &uc); }

virtIO_t & asciiIO_t::operator<<(const short& s)			{ return writeAscii("%d ", s); }
virtIO_t & asciiIO_t::operator>>(short& s)					{ return readAscii("%d ", &s); }

virtIO_t & asciiIO_t::operator<<(const unsigned short& us)	{ return writeAscii("%d ", us); }
virtIO_t & asciiIO_t::operator>>(unsigned short& us)		{ return readAscii("%d ", &us); }

virtIO_t & asciiIO_t::operator<<(const int& i)				{ return writeAscii("%d ", i); }
virtIO_t & asciiIO_t::operator>>(int& i)					{ return readAscii("%d ", &i); }

virtIO_t & asciiIO_t::operator<<(const unsigned int& ui)	{ return writeAscii("%u ", ui); }
virtIO_t & asciiIO_t::operator>>(unsigned int& ui)			{ return readAscii("%u ", &ui); }

virtIO_t & asciiIO_t::operator<<(const long& l)				{ return writeAscii("%ld ", l); }
virtIO_t & asciiIO_t::operator>>(long& l)					{ return readAscii("%ld ", &l); }

virtIO_t & asciiIO_t::operator<<(const unsigned long& ul)	{ return writeAscii("%ld ", ul); }
virtIO_t & asciiIO_t::operator>>(unsigned long& ul)			{ return readAscii("%ld ", &ul); }

virtIO_t & asciiIO_t::operator<<(const double& d)			{ return writeAscii("%lf ", d); }
virtIO_t & asciiIO_t::operator>>(double& d)					{ return readAscii("%lf ", &d); }

virtIO_t & asciiIO_t::operator<<(const float& f)			{ return writeAscii("%f ", f); }
virtIO_t & asciiIO_t::operator>>(float& f)					{ return readAscii("%f ", &f); }
