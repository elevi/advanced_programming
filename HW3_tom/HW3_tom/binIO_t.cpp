#include "stdafx.h"

#include "binIO_t.h"

binIO_t::binIO_t()
{
	m_buffer = NULL;
	m_file = NULL;
	m_status = ok_e;
}

binIO_t::binIO_t(const string pathname, const string access)
{
	m_buffer = NULL;
	m_file = NULL;
	open(pathname, access);
}

binIO_t::~binIO_t()
{
	if (m_file)
		fclose(m_file);
}

virtIO_t & binIO_t::operator<<(const char* s)			{ return binaryWrite(s); }
virtIO_t & binIO_t::operator>>(char* s)					{ return binaryRead(s); }

virtIO_t & binIO_t::operator<<(const char& c)			{ return binaryWrite(c); }
virtIO_t & binIO_t::operator>>(char& c)					{ return binaryRead(c); }

virtIO_t & binIO_t::operator<<(const unsigned char& uc)	{ return binaryWrite(uc); }
virtIO_t & binIO_t::operator>>(unsigned char& uc)		{ return binaryRead(uc); }

virtIO_t & binIO_t::operator<<(const short& s)			{ return binaryWrite(s); }
virtIO_t & binIO_t::operator>>(short& s)				{ return binaryRead(s); }

virtIO_t & binIO_t::operator<<(const unsigned short& us){ return binaryWrite(us); }
virtIO_t & binIO_t::operator>>(unsigned short& us)      { return binaryRead(us); }

virtIO_t & binIO_t::operator<<(const int& i)			{ return binaryWrite(i); }
virtIO_t & binIO_t::operator>>(int& i)					{ return binaryRead(i); }

virtIO_t & binIO_t::operator<<(const unsigned int& ui)	{ return binaryWrite(ui); }
virtIO_t & binIO_t::operator>>(unsigned int& ui)		{ return binaryRead(ui); }

virtIO_t & binIO_t::operator<<(const long& l)			{ return binaryWrite(l); }
virtIO_t & binIO_t::operator>>(long& l)					{ return binaryRead(l); }

virtIO_t & binIO_t::operator<<(const unsigned long& ul)	{ return binaryWrite(ul); }
virtIO_t & binIO_t::operator>>(unsigned long& ul)		{ return binaryRead(ul); }

virtIO_t & binIO_t::operator<<(const double& d)			{ return binaryWrite(d); }
virtIO_t & binIO_t::operator>>(double& d)				{ return binaryRead(d); }

virtIO_t & binIO_t::operator<<(const float& f)			{ return binaryWrite(f); }
virtIO_t & binIO_t::operator>>(float& f)				{ return binaryRead(f); }
