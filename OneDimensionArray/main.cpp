#include <string>
#include <iostream>
#include <exception>
#include <random>
#include <sstream>

/**
* \brief ���� �������.
* \param message ��������� ������������.
* \exception ��� ����� ������������� ��������.
* \return ������.
*/
size_t GetSize(const std::string& message = nullptr);

/**
* \brief ������� ����� � ��������� ��� ������.
* \param size ������ �������.
* \param message ��������� ������������.
* \return ��������� �� ������.
*/
int* CreateArrayManually(
	const size_t size,
	const std::string& message = nullptr);

/**
* \brief ������� ����� � ��������� ���������� �������.
* \param size ������ �������.
* \param message ��������� ������������.
* \return ��������� �� ������.
*/
int* CreateArrayRandomly(
	const size_t size,
	const int max = 100, 
	const int min = -100);

/**
* \brief �����, ������������ ������ � ������.
* \param size ������ �������.
* \param ��������� �� ������.
* \return ������ � ���� ������.
*/
std::string ToString(const size_t size, int* array);

/**
* \brief ������� ���������� ������������� ��������, ������� � k-��.
* \param array ��������� �� ������.
* \param size ������ �������.
* \return ������������ �������.
*/
int GetMax(int* array, const size_t size);

/**
* \brief ������� ���������� ������������� ��������, ������� � k-��.
* \param array ��������� �� ������.
* \param size ������ �������.
* \param k ����� ��������, � �������� �������� ���� ���������.
* \return ������������ �������.
*/
int GetMax(int* array, const size_t size, const size_t k);

/**
* \brief ������� ������ ������� �������������� ��������.
* \param array ��������� �� ������.
* \param size ������ �������.
* \return ������ ������� �������������� ��������.
* \return ���� ��� ������������� ���������, ���������� size.
*/
size_t GetNegativeElementIndex(int* array, const size_t size);

/**
* \brief ����� ����� ������� k-�� ��������
* \param array ��������� �� ������.
* \param size ������ �������.
* \k - ������� ������������.
* \return ����� ������� k-�� ��������.
*/
int GetSum(int* array, const size_t size, const size_t k = 1);

/**
* \brief �������� �������.
* \param array ��������� �� ������.
*/
void DeleteArray(int*& array);

/**
* \brief �������� ��������� �������.
*/
enum class UserChoice
{
	/**
	* \brief �������.
	*/
	manually,
	/**
	* \brief ��������.
	*/
	randomly
};

/**
* \brief ����� ����� � ���������.
* \return 0, � ������ ����������� ����������.
*/
int main()
{
	setlocale(LC_ALL, "RU");
	try
	{
		const size_t size = GetSize("������� ������ ������� ");
		std::cout << "������� ������ ������� �������\n" <<
			static_cast<int>(UserChoice::manually) <<
			" - �������\n" <<
			static_cast<int>(UserChoice::randomly) <<
			" - ��������\n";
		auto userChoice = -1;

		std::cin >> userChoice;
		auto choice = static_cast<UserChoice>(userChoice);
		int* array = nullptr;
		switch (choice)
		{
		case UserChoice::manually:
		{
			array = CreateArrayManually(size, "������� ������:\n");
			break;
		}
		case UserChoice::randomly:
		{
			array = CreateArrayRandomly(size);
			break;
		}
		default:
		{
			std::cerr << "������������ �����" << std::endl;
			return 1;
		}
		}
		
		std::cout << "��� ������\n";
		std::cout << ToString(size, array);
		std::cout << "������������ ������� �������: ";
		std::cout << GetMax(array, size) << "\n";

		std::cout << "������������ ������������� ������� �������: ";
		size_t index = GetNegativeElementIndex(array, size);

		if (index == size)
		{
			std::cout << "� ������� ��� ������������� ���������\n";
		}
		else
		{
			std::cout << GetMax(array, size, index) << "\n";
		}

		size_t k = GetSize("������� �������, ����� ����� ��������� ����� ���������� (1 - ��� ��������, 2 - ������ ������ � �.�.) = ");
		std::cout << "����� ��������� = " << GetSum(array, size, k);
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
		throw std::out_of_range("������������ ������!");
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

int GetMax(int* array, const size_t size, const size_t k)
{
	int max = array[k];
	for (size_t index = k + 1; index < size; index++)
	{
		if (max < array[index] && array[index] < 0)
		{
			max = array[index];
		}
	}
	return max;
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

size_t GetNegativeElementIndex(int* array, const size_t size)
{
	size_t index = 0;
	while (index < size && array[index] > 0)
	{
		index++;
	}

	return index;
}

int GetSum(int* array, const size_t size, const size_t k)
{
	int sum = 0;
	for (size_t index = 0; index < size; index += k)
	{
		sum += array[index];
	}

	return sum;
}

void DeleteArray(int*& array)
{
	if (array != nullptr)
	{
		delete[] array;
		array == nullptr;
	}
}
