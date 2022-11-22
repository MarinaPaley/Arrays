#include <string>
#include <iostream>
#include <exception>
#include <random>
#include <sstream>

/**
* \brief Ввод размера.
* \param message Сообшение пользователю.
* \exception При вводе неправильного значения.
* \return Размер.
*/
size_t GetSize(const std::string& message = nullptr);

/**
* \brief Создаем массв и заполняем его руками.
* \param size Размер маасива.
* \param message Сообшение пользователю.
* \return Указатель на массив.
*/
int* CreateArrayManually(
	const size_t size,
	const std::string& message = nullptr);

/**
* \brief Создаем массв и заполняем случайными числами.
* \param size Размер маасива.
* \param message Сообшение пользователю.
* \return Указатель на массив.
*/
int* CreateArrayRandomly(
	const size_t size,
	const int max = 100, 
	const int min = -100);

/**
* \brief Метод, возвращающий массив в строку.
* \param size Размер маасива.
* \param Указатель на массив.
* \return Массив в виде строки.
*/
std::string ToString(const size_t size, int* array);

/**
* \brief Функция нахождения максимального элемента.
* \param array Указатель на массив.
* \param size Размер маасива.
* \return Максимальный элемент.
*/
int GetMax(int* array, const size_t size);

/**
* \brief Удаление массива.
* \param array Указатель на массив.
*/
void DeleteArray(int*& array);

/**
* \brief Варианты заполнеия массива.
*/
enum class UserChoice
{
	/**
	* \brief Вручную.
	*/
	manually,
	/**
	* \brief Случайно.
	*/
	randomly
};

/**
* \brief Точка входа в программу.
* \return 0, в случае правильного завершения.
*/
int main()
{
	setlocale(LC_ALL, "RU");
	try
	{
		const size_t size = GetSize("Введите размер массива ");
		std::cout << "Введите способ задания массива\n" <<
			static_cast<int>(UserChoice::manually) <<
			" - вручную\n" <<
			static_cast<int>(UserChoice::randomly) <<
			" - случайно\n";
		auto userChoice = -1;
		std::cin >> userChoice;
		auto choice = static_cast<UserChoice>(userChoice);
		int* array = nullptr;
		switch (choice)
		{
		case UserChoice::manually:
		{
			array = CreateArrayManually(size, "Введите маасив:\n");
			break;
		}
		case UserChoice::randomly:
		{
			array = CreateArrayRandomly(size);
			break;
		}
		default:
		{
			std::cerr << "Неправильный выбор" << std::endl;
			return 1;
		}
		}
		
		std::cout << "Наш массив\n";
		std::cout << ToString(size, array);
		std::cout << GetMax(array, size) << std::endl;

		DeleteArray(array);
		return 0;
	}
	catch (std::exception& error)
	{
		std::cerr << error.what();
		return 1;
	}
}

size_t GetSize(const std::string& message)
{
	int number = -1;
	std::cout << message;
	std::cin >> number;
	if (number <= 0)
	{
		throw std::out_of_range("Неправильный размер!");
	}

	return static_cast<size_t>(number);
}

int* CreateArrayManually(const size_t size, const std::string& message)
{
	std::cout << message;
	int* array = new int[size];
	for (size_t index = 0; index < size; index++)
	{
		std::cin >> array[index];
	}

	return array;
}

int* CreateArrayRandomly(const size_t size, const int max, const int min)
{
	//Will be used to obtain a seed for the random number engine
	std::random_device rd;

	//Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> uniformIntDistribution(min, max);

	auto* array = new int[size];
	for (size_t index = 0; index < size; index++)
	{
		array[index] = uniformIntDistribution(gen);
	}

	return array;
}

std::string ToString(const size_t size, int* array)
{
    std::stringstream buffer;
	for (size_t index = 0; index < size -1; index++)
	{
		buffer << array[index] << ", ";
	}
	buffer << array[size - 1] << "\n";

	return buffer.str();
}

int GetMax(int* array, const size_t size)
{
	int max = array[0];
	for (size_t index = 1; index < size; index++)
	{
		if (max < array[index])
		{
			max = array[index];
		}
	}
	return max;
}

void DeleteArray(int*& array)
{
	if (array != nullptr)
	{
		delete[] array;
		array == nullptr;
	}
}
