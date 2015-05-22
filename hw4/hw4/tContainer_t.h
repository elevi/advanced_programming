
#include "t_Exceptions.h"
#include <algorithm>
#include <vector>

using namespace std;

#ifdef TEMPLATE_TEMPLATE
template<typename T, template <typename, typename> class Container>
#else
template<class T, class Container>
#endif

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

	~tContainer_t(){
		;
	}

	bool isEmpty() const {
		return container.empty();
	}

	int elementAmount() const {
		return container.size();
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
	//TODO elevi  check if need to be modified because of the template template change
#ifdef TEMPLATE_TEMPLATE
	typedef typename Container<T*, std::allocator<T*>>::const_iterator Iter;
#else 
	typedef typename Container::const_iterator Iter;
#endif
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


	T* operator[](const int& index) const {
		//vector
		if (typeid(container) == typeid(vector<T*>)){
			vector<T*> * vecPtr = (vector<T*> *)&container;
			if (elementAmount() - 1 < index){
				return 0;
			}
			else{
				return (*vecPtr)[index];
			}

		}
		//list
		else {
			Iter itr = container.begin();
			T * output = 0;
			int index_t = index;
			while (index_t > 0 && itr != container.end()){
				++itr;
				--index_t;
			}
			if (itr != container.end()){
				output = *itr;
			}
			return output;
		}
	}



	private:

	tContainer_t(const tContainer_t& obj) { ; }

	tContainer_t& operator=(tContainer_t& obj){
		*this = obj;
	}


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

#ifdef TEMPLATE_TEMPLATE
	Container<T*, std::allocator<T*>> container;
#else
	Container container;
#endif
	
};

