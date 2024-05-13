#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
void print_arr(T arr[], const int length) {
	std::cout << "{ ";
	for (int i = 0; i < length; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\b\b }\n";
}

template<typename T>
void fill_arr(T arr[], const int lenght, int left, int right) {
	srand(time(NULL));
	for (int i = 0; i < lenght; i++)
		arr[i] = rand() % (right - left) + left;
}

template <typename T>
void arr_app(T*& arr, int& lenght, int num) {
	//Шаг 0. Проверка на количество элиментов для увеличения размера массива. (Невозможно увеличить массив на число меньше нуля)
	if (num <= 0)
		return;
	//Шаг 1. Создание нового динамического массива нужного размера.
	T* tmp = new T[lenght + num]{};
	//Шаг 2. Копирование значений старого массива в элементы нового массива.
	for (int i = 0; i < lenght; i++)
		tmp[i] = arr[i];
	//Шаг 3. Удаление старого массива
	delete[] arr;
	//Шаг 4. Перенапрвление указателя на новый массив
	arr = tmp;

	//Шаг 5. Увеличение переменной, отвечающей за размер массива
	lenght += num;
}

template <typename T>
void arr_pop(T*& arr, int& lenght, int num) {
	//Шаг 0. Проверка на количество элиментов для увеличения размера массива. (Невозможно увеличить массив на число меньше нуля)
	if (lenght <= 0)
		return;
	if (num >= lenght) {
		delete[] arr;
		arr = nullptr;
		return;
	}
		
	//Шаг 1. Создание нового динамического массива нужного размера.
	T* tmp = new T[lenght - num];
	//Шаг 2. Копирование значений старого массива в элементы нового массива.
	for (int i = 0; i < lenght-num; i++)
		tmp[i] = arr[i];
	//Шаг 3. Удаление старого массива
	delete[] arr;
	//Шаг 4. Перенапрвление указателя на новый массив
	arr = tmp;

	//Шаг 5. Уменьшение переменной, отвечающей за размер массива
	lenght -= num;
}



int main() {
	setlocale(LC_ALL, "Russian");
	int n{};
	
	//Выделение динамической памяти под переменные
	int* pointer = new int; //Выделение участка динамической памяти типа int и сохранение ее адреса в указатель.
	*pointer = 7; //Запись в выделенную ранее динамическую память числа 7.
	std::cout << "pointer = " << pointer << std::endl;
	std::cout << "*pointer = " << *pointer << std::endl;

	delete pointer; //Delete - операция по освобождению участка ОЗУ на которую направлен указатель.

	pointer = new int; //Перенаправление указателя на новую область динамической памяти.
	*pointer = 15;
	std::cout << "pointer = " << pointer << std::endl;
	std::cout << "*pointer = " << *pointer << std::endl;

	/*
	Утечка памяти - явление, когда в динамической памяти остаются элименты, у которых потерялась связь с указателям. 
	Влечет за собой засорение ОЗУ устройства
	*/

	/*
	Динамические массивы.
	*/
	
	std::cout << "Введите размер массива -> ";
	int dsize;
	std::cin >> dsize;
	int* darr = new int[dsize];
	std::cout << "Ввод данных в массив:\n";
	for (int i = 0; i < dsize; i++) {
		std::cout << "Введите " << i + 1 << "-e число -> ";
		std::cin >> darr[i];
	}
	std::cout << "Итоговый массив:\n";
	print_arr(darr, dsize);
	
	delete[] darr; //Специальный синтаксис для удаления значений массива, для предотвращения утечки памяти.

	/*
	Двумерные динамические массивы.
	*/
	int  rows{ 5 }, cols{ 6 };
	//int* mx = new int[rows][cols]; //Не работает.

	//Выделение памяти двумерного массива

	int** mx = new int* [rows];
	for (int i = 0; i < rows; i++) {
		mx[i] = new int[cols];
	}

	//Освобождение памяти двумерного массива
	for (int i = 0; i < rows; i++) {
		delete[] mx[i];
	}
	delete[] mx;

	/*
	Области применения динамической памяти:
	1. Создание массива, размер которого может быть определен на этапе выполнения программы;
	2. Создание массива, размер которого должен иметь возможность измениться;
	3. Создание связных динамических структур данных;
	4. Выделение памяти для объектов в случае их крайней необходимости.
	*/

	/*
	Задача 1. Увеличение размера массива
	*/

	std::cout << "Введите размер массива -> ";
	int size1;
	std::cin >> size1;
	int* arr1 = new int[size1];
	fill_arr(arr1, size1, 10, 21);
	std::cout << "Изначальный массив:\n";
	print_arr(arr1, size1);
	std::cout << "Введите количество новых элиментов массива -> ";
	std::cin >> n;
	arr_app(arr1, size1, n);
	std::cout << "Измененный массив:\n";
	print_arr(arr1, size1);

	/*
	Задача 2. Уменьшение размера массива 
	*/

	std::cout << "Введите размер массива -> ";
	int size2;
	std::cin >> size2;
	int* arr2 = new int[size2];
	fill_arr(arr2, size2, 10, 21);
	std::cout << "Изначальный массив:\n";
	print_arr(arr2, size2);
	std::cout << "Введите количество элиментов для удаления -> ";
	std::cin >> n;
	arr_pop(arr2, size2, n);
	print_arr(arr2, size2);

	return 0;
}