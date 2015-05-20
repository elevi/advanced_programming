#ifndef T_EXCEPTIONS_H
#define T_EXCEPTIONS_H


class tEmptyException {
	public:
	tEmptyException(){ ; }
	virtual const char* what() const throw(){
		return "container is empty";
	}
};
#endif //T_EXCEPTIONS_H