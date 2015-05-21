
#include "t_Exceptions.h"
template<typename T, template <typename, typename> class Container>
class tContainer_t
{
	typedef enum {
		First,
		Last
	}Position;


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


	~tContainer_t(){
		;
	}

	private:
	
	
	T getElement(Position pos) const{
		if (isEmpty()){
			throw tEmptyException();
		}
		else{
			//typename Container<T*, std::allocator<T*>>::const_iterator itr = (pos == Position::First) ? container.begin() : container.end();
			T * element = (pos == Position::First) ? container.front() : container.back();
			if (element != 0){
				return *element;
			}
		}
	}
	
	tContainer_t(const tContainer_t& obj) { ; }
	
	Container<T*, std::allocator<T*>> container;
	int elementsCounter;


};

