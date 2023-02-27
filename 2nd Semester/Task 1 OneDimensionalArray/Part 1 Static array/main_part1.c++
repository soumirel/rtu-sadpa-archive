#include <iostream>
#include <locale.h>
using namespace std;


const int constArrSize = 1000;
void printMenu(long* array, int size, bool isFilled);
void fillArray(long* array, int size);
void printArray(long* array, int size, bool isArrayFilled);
int findIndex(long* array, int size, long digit);
int findHighestDigit(int vaule);
int insertElement(long* array, int size, long element, int digit);
int deleteElements(long* array, int size, int digit);


int main() {
	setlocale(LC_ALL, "Russian");
	//Главные переменные.
	long mainArray[constArrSize];
	int actualSize = 0;
	//Служебные переменные.
	int numDeletedElems = 0;
	int foundIndex;
	bool isArrayFilled = false;
	//Переменные для пользовательского ввода.
	int userChoice = 1;
	int userDigit;
	long userElement;
	while (userChoice != 0) { // Главный меню-цикл.
		printMenu(mainArray, actualSize, isArrayFilled);
		cin >> userChoice;
		switch (userChoice) {
		case 1: // Кейс заполнения массива.
			cout << "Введите кол-во элементов в массиве: ";
			cin >> actualSize;
			if (actualSize <= 0 || actualSize > constArrSize) {
				cout << "Ошибка ввода размерности массива!\n";
			}
			else {
				cout << "Введите элементы массива: ";
				fillArray(mainArray, actualSize);
				isArrayFilled = true;
			}
			system("pause");
			break;
		case 2: // Кейс поиска индекса.
			if (!isArrayFilled) {
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			}
			else {
				cout << "Введите искомую цифру:";
				cin >> userDigit;
				foundIndex = findIndex(mainArray, actualSize, userDigit);
				if (foundIndex != -1) {
					cout << "Искомый индекс: " << foundIndex << "\n";
				}
				else{
					cout << "Ничего не найдено :(\n";
				}
			}
			system("pause");
			break;
		case 3: // Кейс вставки элемента.
			if (!isArrayFilled) {
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			}
			else {
				cout << "Введите цифру, по которой будет происходить поиск элемента: ";
				cin >> userDigit;
				cout << "Введите эллемент, который хотите вставить: ";
				cin >> userElement;
				if (insertElement(mainArray, actualSize, userElement, userDigit) != -1) {
					cout << "Массив обновлён.\n";
					actualSize += 1;
				}
				else {
					cout << "По введённому значению ничего не найдено, некуда добавлять элемент :(\n";
				}
			}
			system("pause");
			break;
		case 4: //Кейс удаления элемента(ов).
			if (!isArrayFilled) {
				cout << "Ошибка! Заполните массив и попробуйте снова\n";
			}
			else {
				cout << "Введите цифру, по которой будет происходить выбор элементов: ";
				cin >> userDigit;
				numDeletedElems = deleteElements(mainArray, actualSize, userDigit);
				if (numDeletedElems != 0) {
					if (numDeletedElems == actualSize) {
						cout << "Вследстсвие удаления массив оказался пуст.\n";
						actualSize -= numDeletedElems;
					}
					else {

						actualSize -= numDeletedElems;
						cout << "Массив обновлён.\n";
					}
				}
				else {
					cout << "По введённому значению ничего не найдено\n";
					"Нечего удалять.\n";
				}
			}
			system("pause");
			break;
		case 0: // Кейс выхода.
			userChoice = 0;
			cout << "До свидания!\n";
			system("pause");
			break;
		default:
			cout << "Я не понимаю вас, повторите ввод\n";
			system("pause");
			break;
		}
	}
	return 0;
}


/*
Процедура отображения меню и массива.
Аргументы - 1) Массив, вместе с которым выводится меню,
			2) Размерность массива,
			3) Булево значение "заполнен ли массив?"
*/
void printMenu(long* array, int size, bool isFilled) { 
	system("cls");
	cout << "Практическая работа #1 ИКБО-03-21 Мазанов А.Е. Вариант 17\n\n"
		"Задание 1 - Статический массив\n"
		"================Меню================\n";
	if (isFilled && size != 0) {
		cout << "\n";
		printArray(array, size, isFilled);
		cout << "\n";
	}
	else {
		cout << "\nТекущий массив: Пуст\n\n";
	}
	cout << "1) Заполнить массив\n"
		"2) Найти индекс элемента массива, старшая цифра значения которого равна заданной.\n"
		"3) Вставить новый элемент в массив перед элементом массива, старшая цифра значения которого равна заданной\n"
		"4) Удалить все элементы массива, старшая цифра значений которых равна заданной.\n"
		"0) Выход\n"
		"Ваш выбор: ";
}


/*
Процедура заполнения массива.
Аргументы - 1) Массив, который нужно заполнить,
			2) Размерность массива,
*/
void fillArray(long* array, int size) {
	for (int i = 0; i < size; i++) {
		cin >> array[i];
	}
}


/*
Процедура вывода массива в консоль.
Аргументы - 1) Массив, который нужно вывести,
			2) Размерность массива,
			3) Булево значение "заполнен ли массив?".
*/
void printArray(long* array, int size, bool isFilled) {
	if (!isFilled) {
		cout << "Ошибка! Массив пуст. Заполните массив и попробуйте снова.\n";
	}
	else {
		cout << "Текущий массив: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
		cout << "\n";
	}
}


/*
Функция поиска индекса.
Аргументы - 1) Массив, в котором происх. поиск,
			2) Размерность массива,
			3) Цифра для поиска.
Возр.знач - 1) Индекс, если найден,
			2) -1 если не найден.
*/
int findIndex(long* array, int size, long digit) {
	for (int i = 0; i < size; i++){
		if (findHighestDigit(array[i]) == digit) {
			return i;
		}
	}
	return -1;
}

/*
Функция поиска старшей цифры числа.
Аргументы - 1) Число, в котором необходим поиск.
Возвр.знач - 1) Старшая цифра числа.
*/
int findHighestDigit(int vaule) {
	while (vaule > 9) {
		vaule /= 10;
	}
	return vaule;
}

/*
Функция вставки элемента в массив.
Аргументы - 1) Массив для вставки,
			2) Ращзмерность массива,
			3) Элемент для вставки,
			4) Цифра для поиска.
Возвр.знач - 1) 0, если вставка успешна,
			 2) -1, если вставка не успешна.
*/
int insertElement(long* array, int size, long element, int digit) {
	int index = findIndex(array, size, digit);
	if (index != -1) {
		for (int i = size - 1; i >= index; i--) {
			array[i + 1] = array[i];
		}
		array[index] = element;
		return 0;
	}
	else {
		return -1;
	}
}

/*
Функция удаления элемента(ов) в массиве.
Аргументы - 1) Массив для вставки,
			2) Ращзмерность массива,
			3) Цифра для поиска.
Возвр.знач - 1) Кол-во удалённых элементов.
*/
int deleteElements(long* array, int size, int digit) {
	int deletedCounter = 0;
	for (int i = 0; i < size; i++){
		if (findHighestDigit(array[i]) == digit) {
			deletedCounter += 1;
			for (int k = i; k < size; k++) {
				array[k] = array[k + 1];
			}
			i -= 1;
		}
	}
	return deletedCounter;
}