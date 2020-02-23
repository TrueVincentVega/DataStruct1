#include<iostream>

class ForwardList
{
	class Element
	{
		int Data;
		Element* pNext;
		static int count;
	public:
		const int getData()const;
			const Element* getNext()const;
			Element(int Data, Element* pNext = nullptr);
			~Element();
	
		friend class ForwardList;
	};

	Element* Head;
	int size;
public:

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp);
			~Iterator();

			const int& operator*() const;
			int& operator*();
			Iterator& operator++();
		
		//перегружаем postfix ++
			Iterator operator++(int);

			bool operator==(const Iterator& other) const;
			bool operator!=(const Iterator& other) const;
	};

	const Iterator begin()const;
		const Iterator end()const;
		int get_size()const;
		ForwardList();
		explicit ForwardList(int size);
		ForwardList(std::initializer_list<int> il);
		ForwardList(const ForwardList& that);
		ForwardList(ForwardList&& other);
		~ForwardList();

		//	Operators:
		ForwardList& operator=(const ForwardList& other);
		ForwardList& operator=(ForwardList&& other);
		int& operator[](int index);

		//	Methods:
		void push_front(int Data);
		void push_back(int Data);
		void insert(int Index, int Data);

		void pop_front();
		void pop_back();
		void erase(int index);

		//	methods:
		void print();

	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int ForwardList::Element::count = 0;
//	Methods (Методы за классом)

////////////////////////////////////////////Element methods////////////////////////////////////
const int ForwardList::Element::getData()const
{
	return this->Data;
}
const ForwardList::Element* ForwardList::Element::getNext()const
{
	return this->pNext;
}
ForwardList::Element::Element(int Data, Element* pNext)
{
	this->Data = Data;
	this->pNext = pNext;
	count++;
	std::cout << "EConstructor:\t" << this << std::endl;
}
ForwardList::Element::~Element()
{
	count--;
	std::cout << "EDestructor:\t" << this << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Iterator methods/////////////////////////////////////////////
ForwardList::Iterator::Iterator(Element* Temp)
{
	this->Temp = Temp;

#ifdef DEBUG_IT
	std::cout << "ItConstructor:\t" << this << std::endl; //Ctrl+K+S -> ifdef hot keys of visual studio
#endif // DEBUG_IT
}
ForwardList::Iterator::~Iterator()
{
#ifdef DEBUG_IT
	std::cout << "ItDestructor:\t" << this << std::endl;
#endif // DEBUG_IT

}

const int& ForwardList::Iterator::operator*() const
{
	return Temp->Data;
}
int& ForwardList::Iterator::operator*()
{
	return Temp->Data;
}

ForwardList::Iterator& ForwardList::Iterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

//перегружаем postfix ++
ForwardList::Iterator ForwardList::Iterator::operator++(int)
{
	Iterator old = *this;
	if (Temp)Temp = Temp->pNext;
	return old;
}

bool ForwardList::Iterator::operator==(const Iterator& other) const
{
	return this->Temp == other.Temp;
}
bool ForwardList::Iterator::operator!=(const Iterator& other) const
{
	return this->Temp != other.Temp;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////ForwardList methods/////////////////////////////////
const ForwardList::Iterator ForwardList::begin()const
{
	//Возвращает итератор на начало контейнера
	return Head;
}
const ForwardList::Iterator ForwardList::end()const
{
	//Возвращает итератор на конец контейнера
	return nullptr;
}

int ForwardList::get_size()const
{
	return size;
}
ForwardList::ForwardList()
{
	this->Head = nullptr;
	this->size = 0;
	std::cout << "LConstructor:\t" << this << std::endl;
}
ForwardList::ForwardList(int size) :ForwardList()
{
	while (size--)push_front(0);
	std::cout << "LConstructor:\t" << this << std::endl;
}
ForwardList::ForwardList(std::initializer_list<int> il) :ForwardList()
{
	std::cout << typeid(il.begin()).name() << std::endl;
	for (int const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
	std::cout << "ILconstructor:\t" << this << std::endl;
}
ForwardList::ForwardList(const ForwardList& that) :ForwardList()
{
	/*Element* Temp = that.Head;
	while (Temp)
	{
	push_back(Temp->Data);
	Temp = Temp->pNext;
	}*/
	for (Element* Temp = that.Head; Temp != nullptr; Temp = Temp->pNext)push_back(Temp->Data);
	std::cout << "CopyConstructor:\t" << this << std::endl;
}
ForwardList::ForwardList(ForwardList&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	std::cout << "MoveConstructor:\t" << this << std::endl;
}
ForwardList::~ForwardList()
{
	while (Head)pop_front();
	std::cout << "LDestructor:\t" << this << std::endl;
}

// Operators:

ForwardList& ForwardList::operator=(const ForwardList& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	std::cout << "CopyAssignment:\t" << this << std::endl;
	return *this;
}
ForwardList& ForwardList::operator=(ForwardList&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	other.Head = nullptr;
	std::cout << "MoveAssignment:\t" << this << std::endl;
	return *this;
}

int& ForwardList::operator[](int index)
{
	Element* Temp = Head;
	for (int i = 0; i < index; i++)Temp = Temp->pNext;
	return Temp->Data;
}

// Methods:
void ForwardList::push_front(int Data)
{
	Element* New = new Element(Data);
	New->pNext = Head;
	Head = New;
	size++;
}
void ForwardList::push_back(int Data)
{
	if (Head == nullptr)
	{
		push_front(Data);
		return;
	}
	Element* Temp = Head;
	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	Element* New = new Element(Data);
	Temp->pNext = New;
	size++;
}
void ForwardList::insert(int Index, int Data)
{
	if (Index == 0)
	{
		push_front(Data);
		return;
	}
	if (Index > size)
	{
		std::cout << "Error: Out of range" << std::endl;
		return;
	}
	//1) Создаем элемент:
	Element* New = new Element(Data);
	//2) Доходим до нужной позиции в списке:
	Element* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		Temp = Temp->pNext;
	}
	//3) Вставляем новый элемент в список:
	New->pNext = Temp->pNext;
	Temp->pNext = New;
	size++;
}

void ForwardList::pop_front()
{
	Element* Temp = Head;
	Head = Head->pNext;
	delete Temp;
	size--;
}

void ForwardList::pop_back()
{
	//Удаление элемента с конца списка.
	Element* Temp = Head;
	while (Temp->pNext->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}

void ForwardList::erase(int index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index >= size)
	{
		std::cout << "Error: Out of range" << std::endl;;
		return;
	}
	/*if (index == size - 1)
	{
	pop_back();
	return;
	}*/
	Element* Temp = Head;
	for (int i = 0; i < index - 1; i++)
	{
		Temp = Temp->pNext;
	}
	Element* buffer = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete buffer;
	size--;
}

// methods:
void ForwardList::print()
{
	std::cout << "\n-------------------------------------\n";
	std::cout << "Head:\t" << Head << std::endl;
	//Element* Temp = Head; //Temp - это итератор.
	// //Итератор - это указатель, при помощи которого
	// //можно получить доступ к элементам структуры данных.
	//while (Temp != nullptr)
	//{
	// std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	// Temp = Temp->pNext; //Переход на следующий элемент.
	//}

	/*for (Element* Temp = Head; Temp; Temp=Temp->pNext)
	{
	std::cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << std::endl;
	}*/
	for (Iterator it = Head;
		it != nullptr;
		++it)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;

	std::cout << "List size:\t" << size << std::endl;
	std::cout << "\n-------------------------------------\n";
}

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (const ForwardList::Element* Temp = right.Head; Temp; Temp = Temp->getNext())
	{
		cat.push_back(Temp->getData());
	}
	std::cout << "Global operator +" << std::endl;
	return cat;
}

//#define BASE_CHECK
//#define OPERATORS_AND_CONSTRUCTORS_CHECK

void print(int arr[])
{
	std::cout << sizeof(arr) << std::endl;
	std::cout << typeid(arr).name() << std::endl;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;

	/*for (int i : arr)
	{
	std::cout << i << "\t";
	}
	std::cout << std::endl;*/
}

void main()
{
	setlocale(LC_ALL, "");

	int n;
	//std::cout << "Input list size: "; std::cin >> n;
#ifdef BASE_CHECK
	ForwardList fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_back(rand() % 100);
	}
	//fl.push_back(123);
	fl.print();

	int index;
	int data;

	/*std::cout << "Input index: "; std::cin >> index;
	std::cout << "Input value: "; std::cin >> data;
	fl.insert(index, data);
	fl.print();*/

	/*fl.pop_front();
	fl.pop_back();
	fl.print();*/

	/*std::cout << "Input index: "; std::cin >> index;
	fl.erase(index);
	fl.print();*/
#endif // BASE_CHECK

	/*int a = 2;
	double b = 3;
	ForwardList list1(5);
	for (int i = 0; i < n; i++)
	{
	list1[i] = rand() % 100;
	}
	for (int i = 0; i < n; i++)
	{
	std::cout << list1[i] << "\t";
	}
	std::cout << std::endl;*/

#ifdef OPERATORS_AND_CONSTRUCTORS_CHECK
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	list1.print();

	ForwardList list2 = { 34, 55, 89 };
	list2.print();

	std::cout << "\n---------------------------------------------\n";
	ForwardList list3;
	list3 = list1 + list2;
	std::cout << "\n---------------------------------------------\n";
	for (int i = 0; i < list3.get_size(); i++)std::cout << list3[i] << "\t";
	std::cout << std::endl;

	/*ForwardList list2;
	list2 = list1;
	list2.print();*/
#endif // OPERATORS_AND_CONSTRUCTORS_CHECK

	/*int arr[] = { 3, 5, 8, 13, 21 };
	std::cout << sizeof(arr) << std::endl;
	std::cout << typeid(arr).name() << std::endl;
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
	std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;

	for (int i : arr)
	{
	std::cout << i << "\t";
	}
	std::cout << std::endl;

	print(arr);*/

	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (ForwardList::Iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	/*for (int i : list)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;*/
}