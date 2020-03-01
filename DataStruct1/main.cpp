#include"ForwardList.h" //	Class declaration
#include"ForwardList.cpp" //	Class definition

//#define BASE_CHECK
//#define OPERATORS_AND_CONSTRUCTORS_CHECK
#define RANGE_BASED_FOR
//#define PREFORMANCE_ARR
//#define PREFORMANCE_LIST	ForwardList fl;
	//for (int i = 0; i < n; i++)


void main()
{
	setlocale(LC_ALL, "");

	//int n;
	//std::cout << "Input list size: "; std::cin >> n;
#ifdef BASE_CHECK
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

#ifdef RANGE_BASED_FOR
	//ForwardList<int> list = { 3, 5, 8, 13, 21 };
	ForwardList<double> list = { 2.7, 3.14, 5.4, 8.3 };
	//list.print();
	for (ForwardList<double>::Iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "\t";
	}
	std::cout << std::endl;
	for (double i : list)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
#endif //RANGE_BASED_FOR

#ifdef PREFORMANCE_ARR
	//int n;
	std::cout << "Input size: "; std::cin >> n;
	int* arr = new int[n] {};
	std::cout << "Memory allocated." << std::endl;
	std::cout << "Loading data....." << std::endl;
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand();
	}
	std::cout << "Data loaded." << std::endl;
	std::cout << "-----------------------------" << std::endl;
	for (int i = 0; i < n; i++)
	{
		//std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
	std::cout << "\n\n\nData usage...\n\n\n" << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Releasing memory........." << std::endl;
	delete[] arr;
	std::cout << "Memory released." << std::endl;

#endif //PREFORMANCE_ARR

#ifdef PREFORMANCE_LIST
	std::cout << "Input size: "; std::cin >> n;
	ForwardList<int> list(n);
	std::cout << "Memory allocated." << std::endl;
	std::cout << "Loading data....." << std::endl;
	for (int i = 0; i < n; i++)
	{
		list[i] = rand();
	}
	std::cout << "Data loaded." << std::endl;
	std::cout << "-----------------------------" << std::endl;
	for (int i = 0; i < n; i++)
	{
		//std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
	std::cout << "\n\n\nData usage...\n\n\n" << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "Releasing memory........." << std::endl;
	list.~ForwardList();
	std::cout << "Memory released." << std::endl;
#endif //PREFORMANCE_LIST

}