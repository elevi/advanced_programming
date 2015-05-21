#ifndef T_EXCEPTIONS_H
#define T_EXCEPTIONS_H


class tEmptyException {
	public:
	tEmptyException(){ ; }
	virtual const char* what() const throw(){
		return "container is empty";
	}
};

class tElementDoesNotExistException {
	public:
	tElementDoesNotExistException(){ ; }
	virtual const char* what() const throw(){
		return "element does not exist";
	}
};
#endif //T_EXCEPTIONS_H