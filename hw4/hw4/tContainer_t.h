
template<typename T, template <typename, typename> class Container>
class tContainer_t
{
	public:
	tContainer_t() :elementsCounter(0){
		;
	}

	
	bool isEmpty() const {
		return container.empty();
	}

	~tContainer_t(){
		;
	}

	private:
	tContainer_t(const tContainer_t& obj) { ; }
	
	Container<T*, std::allocator<T*>> container;
	int elementsCounter;
};

