
#include "t_Exceptions.h"
#include <algorithm>

using namespace std;

template<typename T, template <typename, typename> class Container>
class tContainer_t
{
	typedef enum {
		First,
		Last
	}Position;

	typedef enum {
		Remove,
		Delete
	}EliminateElement;

	class is_Equal{
		public:
		is_Equal(T value) :val(value){}
		~is_Equal(){}
		bool operator()(T * value) const {
			return *value == val;
		}
		private:
		T val;
	};


	public:
	tContainer_t(){}

	
	bool isEmpty() const {
		return container.empty();
	}

	int elementAmount() const {
		return container.size();
		//const tContainer_t<int, vector>& t1;
		//const tContainer_t<double, vector>& t2;
		//const tContainer_t<int, list>& t3;
		//const tContainer_t<double, list>& t4;
		//
		////vector
		//if (typeid(*this) == typeid(t1) || typeid(*this) == typeid(t2)){
		//	return conditional_t.capa
		//}
		////list
		//else if (typeid(*this) == typeid(t3) || typeid(*this) == typeid(t4)){

		//}

	}

	void insert(T * t){
		container.push_back(t);
	}

	T getFirstElement() const {
		return getElement(Position::First);
	}

	T getLastElement() const {
		return getElement(Position::Last);
	}
	typedef typename Container<T*, std::allocator<T*>>::const_iterator Iter;
	T * findElementByValue(const T& value) const{
		Iter result = iteratorAtElement(value);
		if (result != container.end()){
			return *result;
		}
		return 0;
	}



	T* removeElementFromContainer(const T& value){
		return eliminateElementFromContainer(value, EliminateElement::Remove);
	}

	T* deleteElementFromContainer(const T& value){
		return eliminateElementFromContainer(value, EliminateElement::Delete);
	}
	

	int removeAllElementsFromContainer(){
		return eliminateAllElementsFromContainer(EliminateElement::Remove);
	}

	int deleteAllElementsFromContainer(){
		return eliminateAllElementsFromContainer(EliminateElement::Delete);
	}

	~tContainer_t(){
		;
	}

	private:
	
	
	T getElement(Position pos) const{
		if (isEmpty()){
			throw tEmptyException();
		}
		else{
			T * element = (pos == Position::First) ? container.front() : container.back();
			if (element != 0){
				return *element;
			}
		}
	}

	Iter iteratorAtElement(const T& value) const{
		Iter result = container.begin();
		Iter end = container.end();
		return result = find_if(result, end, is_Equal(value));
	}

	T* eliminateElementFromContainer(const T& value, EliminateElement type){
		Iter itr = iteratorAtElement(value);
		if (itr != container.end()){
			T* output = *itr;
			container.erase(itr);
			cout << "elemet with value: " << value << " was removed from container" << endl;
			if (type == EliminateElement::Delete){
				delete output;
				cout << "element with value: " << value << " was deleted" << endl;
			}
			return output;
		}
		throw tElementDoesNotExistException();
	}

	int eliminateAllElementsFromContainer(EliminateElement type){
		Iter itr = container.begin();
		int totalElementRemoved = 0;
		while (itr != container.end()){
			T* elementPtr = *itr;
			cout << "removing element with value: " << *elementPtr << endl;
			container.erase(itr);
			if (type == EliminateElement::Delete){
				delete elementPtr;
				cout << "element deleted" << endl;
			}
			++totalElementRemoved;
			itr = container.begin();
		}
		return totalElementRemoved;
	}
	
	tContainer_t(const tContainer_t& obj) { ; }
	
	Container<T*, std::allocator<T*>> container;
};

