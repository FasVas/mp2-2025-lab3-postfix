// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, +
// - извлечение элемента, +
// - просмотр верхнего элемента (без удаления) +
// - проверка на пустоту, +
// - получение количества элементов в стеке +
// - очистка стека +
// при вставке в полный стек должна перевыделяться память

#define FAST_SIZE // Если задефайнено, размер рассчитывается заранее

template<typename T>
class TStack 
{

public:
	TStack() : highest(nullptr) 
#ifdef FAST_SIZE
		, size(0)
#endif	
	{} 

	// Правило трёх ---------------------------------------------------
	
	~TStack()
	{
		trash();
	}

	TStack(const TStack& other) : highest(nullptr)
	{
		if (!other.cat())
		{
			TStack<T> vrem;
			plate* taken_plate = other.highest;
			while (taken_plate != nullptr)
			{
				vrem.add(taken_plate->data);
				taken_plate = taken_plate->lower;
			}
			while (!vrem.cat())
			{
				add(vrem.steal());
			}
		}
	}

	TStack& operator=(const TStack& other)
	{
		if (this != &other)
		{
			trash();
			if (!other.cat())
			{
				TStack<T> vrem;
				plate* taken_plate = other.highest;
				while (taken_plate != nullptr)
				{
					vrem.add(taken_plate->data);
					taken_plate = taken_plate->lower;
				}
				while (!vrem.cat())
				{
					add(vrem.steal());
				}
			}
		}
	}

	//-----------------------------------------------------------------


	void add(const T& x) // Добавить элемент
	{
		plate* newest = new plate;
		newest->data = x;
		newest->lower = highest;
		highest = newest;
#ifdef FAST_SIZE
		size++;
#endif
	};
	
	bool cat() const // Проверка на пустоту
	{
		return highest == nullptr;
	};

	const T& nice() const// Поглядеть, что сверху
	{
		if (cat())
		{
			throw std::runtime_error("Ctek nyct");
		}
		return highest->data;
	};

	T steal() // Cпересть элемент из стека
	{
		if (cat())
		{
			throw std::runtime_error("Стек пустой");
		}
		plate* taken_plate = highest;
		T x = taken_plate->data;
		highest = taken_plate->lower;
		delete taken_plate;
#ifdef FAST_SIZE
		size--;
#endif
		return x;
	};

	unsigned int count() const // размер
	{
#ifndef FAST_SIZE
		unsigned int counter = 0;
		plate* taken_plate = highest;
		while (taken_plate != nullptr)
		{
			counter++;
			taken_plate = taken_plate->lower;
		}
		return counter;
#endif

#ifdef FAST_SIZE
		return size;
#endif
	};

	void trash() // Polnoye ochish'eniye steka
	{
		while (highest!= nullptr)
		{
			plate* taken_plate = highest;
			highest = highest->lower;
			delete taken_plate;
		}
#ifdef FAST_SIZE
		size = 0;
#endif
	};

protected:

	struct plate
	{
		T data;
		plate * lower;
	};

	plate * highest;
#ifdef FAST_SIZE
	unsigned int size;
#endif 


};
