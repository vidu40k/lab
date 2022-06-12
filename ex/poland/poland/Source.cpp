#include <iostream>
#include <string>
#include "Stack.h"
#include <conio.h>
using namespace std;

struct LettersValues
{
	char letter;
	double value;
};

int getPriority(char ch);
string convertToPolandRecord(string currentStr);
double rezult(string polandRec);
template<class T>
void getValue(T& num);
string inputEquation();
bool isEquationRight(string equation);

int main() {
		
	do
	{
	cout << "Введите выражение" << endl;
	string normZap = inputEquation();
	
	string  polandRec = convertToPolandRecord(normZap);
	cout << "Выражение в польской нoтaции" << endl;
	cout << polandRec << endl;
	cout << "Результат вычислений равен " << rezult(polandRec) << endl;

	cout << "Если хотите повторить нажмите 1" << endl;
	} while (_getch()=='1');

}





int getPriority(char ch) {

	switch (ch)
	{
	case '*':case'/': return 3;

	case '+': case'-':return 2;

	case '(':case ')': return 1;

	default:
		return 0;
		break;
	}

}
string convertToPolandRecord(string currentStr) {

	List<char> stack;
	string newStr;
	for (size_t i = 0; currentStr[i] != '\0'; i++)
	{
		if (currentStr[i] >= 'a' and currentStr[i] <= 'z')
		{
			newStr += currentStr[i];
		}
		if (currentStr[i] == '(') {
			stack.push_front(currentStr[i]);
		}
		if (currentStr[i] == ')' and i!=0)
		{
			for (; stack.top() != '(';)
			{
				newStr += stack.get_front();
			}
			stack.pop_front();
		}
		if (currentStr[i] == '*' or currentStr[i] == '/' or currentStr[i] == '+' or currentStr[i] == '-')
		{
			for (; getPriority(currentStr[i]) <= getPriority(stack.top()) and stack.getSize() != 0; )
			{
				newStr += stack.get_front();
			}
			stack.push_front(currentStr[i]);
		}
	}
	while (stack.getSize() != 0)
	{
		newStr += stack.get_front();
	}

	return newStr;

}
LettersValues* getUniqueLetters(string polandRec,int& unique) {

	size_t size = polandRec.length();
	string uniqueLetters = "";

	for (size_t i = 0; i < size; i++)
	{
		if (polandRec[i] <= 'z' and polandRec[i] >= 'a')
		{
			bool unique = true;
			for (size_t j = 0; j < uniqueLetters.length(); j++)
			{
				if (polandRec[i] == uniqueLetters[j])
				{
					unique = false;
				}
			}
			if (unique)
			{
				uniqueLetters += polandRec[i];
			}
		}
	}

	unique = uniqueLetters.length();
	auto lettersValue = new LettersValues[unique];

	for (size_t i = 0; i < unique; i++)
		lettersValue[i].letter = uniqueLetters[i];
	

	return lettersValue;
}
void setValuesOfLetters(LettersValues*& uniqueLetters,int amount) {

	for (size_t i = 0; i < amount; i++)
	{
		cout << "Введите значение переменной " << uniqueLetters[i].letter<< ":" << endl;
		getValue(uniqueLetters[i].value);
	}

}
double rezult(string polandRec) {

	List<double> stack;
	double value;
	double sum = 0;
	LettersValues *lettersValue;

	int amountOfUniqueLetters=0;
	lettersValue = getUniqueLetters(polandRec, amountOfUniqueLetters);

	bool error = false;
	do
	{

	setValuesOfLetters(lettersValue, amountOfUniqueLetters);

	size_t size = polandRec.length();
	for (size_t i = 0; i < size; i++)
	{

		if (polandRec[i] >= 'a' and polandRec[i] <= 'z')
		{
			for (size_t j = 0; j < size; j++)
			{
				if (polandRec[i]==lettersValue[j].letter)
				{
					stack.push_front(lettersValue[j].value);
				}
			}
		}

		if (polandRec[i] == '*')
		{
			double value1 = stack.get_front();
			double value2 = stack.get_front();

			sum = value1 * value2;
			stack.push_front(sum);
			continue;
		}
		if (polandRec[i] == '/')
		{
			double value1 = stack.get_front();
			double value2 = stack.get_front();

			if (value1==0)
			{
				cout << "При вводе данных параметров расчет невозможен, так как присутсвует деление на 0" << endl;
				cout << "Введите другие параметры" << endl;
				error = true;
				break;
			}
			sum = value2 / value1;
			stack.push_front(sum);
			continue;
		}
		if (polandRec[i] == '+')
		{
			double value1 = stack.get_front();
			double value2 = stack.get_front();

			sum = value1 + value2;
			stack.push_front(sum);
			continue;
		}
		if (polandRec[i] == '-')
		{
			double value1 = stack.get_front();
			double value2 = stack.get_front();

			sum = value2 - value1;
			stack.push_front(sum);
			continue;
		}

	}
	} while (error);


	return stack.get_front();
}
template<class T>
void getValue(T& num) {

	while (true)
	{

		cin >> num;

		if (cin.get() == '\n')
		{
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Некоректный ввод данных. Введите число повторно!";
		}

	}

}
string inputEquation() {

	string equation = "";
	string errorType = "";
	int amountOfOpenBrances = 0;

	while (true)
	{
		system("cls");
		cout << "Ввод выражения" << "\t" << errorType << endl;
		cout << equation;

		char buf = _getch();

		errorType = "";

		if (buf == '\r')
		{
			if (!amountOfOpenBrances)
			{
				if (equation.length() >= 3)
				{
					if (equation.back() <= 'z' and equation.back() >= 'a' or equation.back() == ')')
					{
						break;
					}
				}

			}


		}

		if (buf == '\b')
		{
			if (equation.length())
			{
				if (equation.back() == ')')
				{
					amountOfOpenBrances++;
					equation.pop_back();
					continue;
				}
				if (equation.back() == '(')
				{
					amountOfOpenBrances--;
					equation.pop_back();
					continue;
				}
				else
				{
					equation.pop_back();
					continue;
				}
			}
			
		}

		if (!equation.length())
		{
			if (buf <= 'z' and buf >= 'a') {
				equation += buf;
				continue;
			}

			if (buf == '(') {
				amountOfOpenBrances++;
				equation += buf;
				continue;
			}
			else
				continue;


		}

		if (equation.back() <= 'z' and equation.back() >= 'a')
		{
			if (buf == '-' or buf == '+' or buf == '/' or buf == '*')
			{
				equation += buf;
				continue;
			}
			if (buf == ')')
			{
				if (amountOfOpenBrances)
				{
					amountOfOpenBrances--;
					equation += buf;
					continue;
				}
			}
			else
				if (amountOfOpenBrances)
				{
					errorType = "Ожидается знак или закрытие скобки";
					continue;
				}
				else
				{
					errorType = "Ожидается знак";
					continue;
				}

		}

		if (equation.back() == '-' or equation.back() == '+' or equation.back() == '*' or equation.back() == '/')
		{
			if (buf <= 'z' and buf >= 'a')
			{
				equation += buf;
				continue;
			}
			if (buf == '(')
			{
				equation += buf;
				amountOfOpenBrances++;
				continue;
			}
			else
			{
				errorType = "Ожидается буква или открытие скобки";
				continue;
			}
		}

		if (equation.back() == '(')
		{
			if (buf <= 'z' and buf >= 'a')
			{
				equation += buf;
				continue;
			}
			if (buf == '(')
			{
				equation += buf;
				amountOfOpenBrances++;
				continue;
			}
			else
			{
				errorType = "Ожидается буква или скобка";
				continue;
			}
		}

		if (equation.back() == ')')
		{
			if (buf == '-' or buf == '+' or buf == '/' or buf == '*')
			{
				equation += buf;
				continue;
			}
			if (buf == ')')
			{
				if (amountOfOpenBrances)
				{
					equation += buf;
					amountOfOpenBrances--;
					continue;
				}

			}
			else if (amountOfOpenBrances)
			{
				errorType = "Ожидается знак или закрытие скобки";
				continue;
			}
			else
			{
				errorType = "Ожидается знак ";
				continue;
			}
		}
	}
	cout << endl;
	return equation;
}
bool isEquationRight(string equation) {

	if (equation[0] < 'a' and equation[0]>'z' and equation[0] != '(')
		return false;

	int rightBrace = 0;
	int leftBrace = 0;
	auto size = equation.length();
	for (size_t i = 0; i < size; i++)
	{
		if (equation[i] == ')')
			rightBrace++;



		if (equation[i] == '(') {
			leftBrace++;
			if (equation[i + 1])
			{

			}


		}
	}
	if (rightBrace != leftBrace)
		return false;


}
