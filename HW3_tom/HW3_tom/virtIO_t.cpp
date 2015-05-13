#pragma once
#include "stdafx.h"
#include "virtIO_t.h"
#include <string>

long int virtIO_t::getPosition() {
	long int  currentPos;

	currentPos = ftell(m_file);
	if (currentPos == -1)
		setStatus(general_error_e);
		//m_status = general_error_e;

	return currentPos;
}

long int virtIO_t::getFileLength() {
	long int endSeek, setSeek, endTell, currentPos;

	currentPos = getPosition();
	endSeek = fseek(m_file, 0, SEEK_END); // move pointer to eof
	endTell = getPosition();
	setSeek = fseek(m_file, currentPos, SEEK_SET); // return pointer to it's location

	if ((endSeek != 0) || (setSeek != 0) || (currentPos == -1) || (endTell == -1))
		setStatus(general_error_e);
		//m_status = general_error_e;

	return endTell;
}

void virtIO_t::open(){
	return open(m_path, m_accessMode);
}

void virtIO_t::open(const string pathname, const string access){
	if (m_file){
		close();
		m_file = fopen(pathname.c_str(), access.c_str());
	}
	else{
		m_file = fopen(pathname.c_str(), access.c_str());
	}

	if (!m_file){
		//m_status = cant_open_file_e;
		setStatus(cant_open_file_e);
		throw virtIO_t::IOErr_t("Can't open file.");
	}

	m_path = pathname;
	m_accessMode = access;
	//m_status = ok_e;
	setStatus(ok_e);
}

void virtIO_t::close(){ 
	if (m_file)
	{
		if (fclose(m_file) != 0)
		{
			//m_status = general_error_e;
			setStatus(closeErr_e);
			throw virtIO_t::IOErr_t("Can't close file");
		}
	}
}

void virtIO_t::flush(){
	if (m_file)
	{
		if (fflush(m_file) != 0)
		{
			//m_status = general_error_e;
			setStatus(general_error_e);
		}
		else
		{
			//m_status = ok_e;
			setStatus(ok_e);
		}
	}	
}

//operators
void virtIO_t::operator[](int pos){
	if (!m_file)
	{
		//m_status = file_not_open_e;
		setStatus(file_not_open_e);
	}
	else if ((pos < 0) || (pos > getFileLength())) 
	{
		//m_status = read_after_eof_e;
		setStatus(read_after_eof_e);
	}
	else if (fseek(m_file, pos, SEEK_SET) != 0) 
	{
		//m_status = general_error_e;
		setStatus(general_error_e);
	}
	else
	{
		//m_status = ok_e;
		setStatus(ok_e);
	}
}

virtIO_t & virtIO_t::operator<<(const void* c){
	m_buffer = (char*)c;
	lastIOCommand = 1;
	return *this;
}

virtIO_t & virtIO_t::operator>>(void* c){
	m_buffer = (char*)c;
	lastIOCommand = 0;
	return *this;
}


void virtIO_t::operator,(int len){
	int res = 0;

	if (m_buffer){
		if (lastIOCommand == 1) //write
		{

			canDoAction(actionType::write_action);
			res = fwrite(m_buffer, 1, len, m_file);
		}
		else{ //read
			canDoAction(actionType::read_action);
			if (getPosition() + len  > getFileLength()){
				//m_status = read_after_eof_e;
				setStatus(read_after_eof_e);
				throw IOErr_t("Comma operator failed. trying to Read after eof.");
			}
			else
				res = fread(m_buffer, 1, len, m_file);
		}
	}
	if (res != len){ // didn't read/write as much as we should have
		//m_status = general_error_e;
		setStatus(general_error_e);
		throw IOErr_t("Comma operator failed.");
	}
}

void virtIO_t::read(void* buf, unsigned int size, unsigned int count)
{
	canDoAction(actionType::read_action);
	if (getPosition() >= getFileLength())
	{
		//m_status = read_after_eof_e;
		setStatus(read_after_eof_e);
		throw IOErr_t("Reading after eof");
	}
	else
	{
		if (!(fread(buf, size, count, m_file) > 0))
		{
			//m_status = readErr_e;
			setStatus(readErr_e);
			throw IOErr_t("Failed to read");
		}
	}
}

void virtIO_t::write(const void* buf, unsigned int size, unsigned int count)
{
	canDoAction(actionType::write_action);
	if (!(fwrite(buf, size, count, m_file) > 0))
	{
		setStatus(writeErr_e);
		throw IOErr_t("Failed to write");
	}
}

void virtIO_t::initPosition()
{
	int pos = fseek(m_file, 0, SEEK_SET);

	if (pos == -1)
		setStatus(general_error_e);
}

bool virtIO_t::canDoRead() const{
	if (!m_accessMode.compare("w") || !m_accessMode.compare("a")){
		return false;
	}
	return true;
}

bool virtIO_t::canDoWrite() const{
	return (m_accessMode.compare("r") == 0) ? false : true;
}

void virtIO_t::canDoAction(actionType actionType) const{
	switch (actionType){
		case actionType::read_action:
			if (!canDoRead()){
				throw IOErr_t("bad_access_e - file doesn't has read permission");
			}
			break;
		case actionType::write_action:
			if (!canDoWrite()){
				throw IOErr_t("bad_access_e - file doesn't has write permission");
			}
			break;
		default:
			throw IOErr_t("Unknown actionType");
			break;
	}
}