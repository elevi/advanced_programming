
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
	tContainer_t() :elementsCounter(0){
		;
	}

	
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
		Iter itr = iteratorAtElement(value);
		if (itr != container.end()){
			T* output = *itr;
			container.erase(itr);
			return output;
		}
		throw tElementDoesNotExistException();
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
	
	tContainer_t(const tContainer_t& obj) { ; }
	
	Container<T*, std::allocator<T*>> container;
	int elementsCounter;


};

