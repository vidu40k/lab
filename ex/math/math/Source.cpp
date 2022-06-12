#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
#include <iomanip>
using namespace std;


double F(double);
double df(double x,double eps);

double FindRootNewton(double, double, ...);
double FindRootSecant(double, double, ... );
double FindRootWerstein(double, double, ... );

void printMenu(string* arr, int size, int current);
int choose(string* arr, size_t size);
template<class T>
void getValue(T& num);
bool isValuesRight(double& a, double& b, double& h, double& eps);
void inputValues(double& a, double& b, double& h, double& eps);
void printRezults(double& a, double& b, double& h, double& eps);

typedef double (*fPointer)(double, double, ...);

int main()
{
	double a,b,h,eps;
	
	size_t optionCount = 3;
	string options[] = {
		"Использовать параметры по умолчанию",
		"Ввод собственных значений",
		"Выход"
	};

	enum 
	{
		DEFAULT_VALUES=1,INPUT_VALUES,EXIT
	};
	do
	{
		switch (choose(options,optionCount))
		{
		case DEFAULT_VALUES:
			 a = -1, b = 3, h = 0.01, eps = 0.001;
			break;
		case INPUT_VALUES:
			inputValues(a, b, h, eps);
			break;
		case EXIT:
			return 0;
		}
		printRezults(a, b, h, eps);

		cout << "Нажмите 1 чтобы продолжить" << endl;
	} while (_getch()=='1');

}

double F(double x)
{
	return pow(x, 2) - 10 * pow(sin(x), 2) + 2;
}
double df(double x,double eps)
{
	return  (F(x + eps) - F(x - eps)) / (2 * eps);
}
double FindRootSimpleIteration(double x0, double eps,...)
{
	int iter = 0;
	double rez, x1 = x0 + 0.1 * F(x0);
	while (fabs(x1 - x0) > eps) {
		iter++;
		x0 = x1;
		x1 = x0 + 0.0001 * F(x0);
	}
	cout << "Найден за " << iter << " итераций";
	return x0;
}
double FindRootNewton(double x0, double eps,...)
{
	int iter=0;
	double x1 = x0 - F(x0) / df(x0,eps);
	while (fabs(x1 - x0) > eps)
	{
		iter++;
		x0 = x1;
		x1 = x1 - F(x1) / df(x1,eps);
	}
	cout << "Найден за " << iter << " итераций";
	return x0;
}
double FindRootSecant(double x0, double eps, ...) {

	double* p = &eps;
	p++;
	double h = *p;
	int iter = 0;
	double x1 = x0 - F(x0) * h / (F(x0) - F(x0 - h));
	while (fabs(x1 - x0) > eps)
	{
		iter++;
		x0 = x1;
		x1 = x1 - F(x1) * h / (F(x1) - F(x1 - h));
	}
	cout << "Найден за " << iter << " итераций";
	return x0;
}
double FindRootWerstein(double x0, double eps, ...) {

	double* p = &eps;
	p++;
	double x1 = *p;

	int iter=0;
	double x2 = x1 - (F(x1) * (x1 - x0)) / (F(x1) - F(x0));
	while (fabs(x2 - x1) > eps)
	{
		iter++;
		x0 = x1;
		x1 = x2;
		x2 = x1 - F(x1) * (x1 - x0) / (F(x1) - F(x0));
	}
	cout << "Найден за " << iter << " итераций";
	return x0;
}
void printMenu(string* arr, int size, int current) {
	for (size_t i = 0; i < size; i++)
	{
		if (i == current)
		{
			cout << arr[i] << "<-- " << endl;
		}
		else
			cout << arr[i] << endl;
	}
}
int choose(string* arr, size_t size) {



	int current = 1;
	while (true)
	{

		printMenu(arr, size, current - 1);

		char msg = _getch();
		system("cls");

		if (msg == '\r')
		{
			break;
		}

		if (msg == -32)
		{
			msg = _getch();

			if (msg == 80)
			{
				if (current != size)
					current++;


			}

			if (msg == 72)
			{
				if (current != 1)
					current--;

			}
		}
		if (msg <= '9' and msg >= '0') {

			int num = msg - 48;
			if (num == 0)
			{
				current = 1;
				continue;
			}


			if (num <= size)
			{
				current = num;
			}
			else current = size;
		}

	}


	return current;
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
			cout << "Некоректный ввод данных. Введите число повторно!" << endl;;
		}

	}

}
bool isValuesRight(double& a, double& b, double& h, double& eps) {

	if (b <= a)
	{
		cout << "Некоректный ввод,b меньше чем a" << endl;
		return false;
	}

	if (h <= b - a)
	{
		cout << "Слишком малая погрешность" << endl;
		return false;
	}

}
void inputValues(double& a, double& b, double& h, double& eps) {


	do
	{

	cout << "Введите начало отрезка" << endl;
	getValue(a);

	cout << "Введите конец отрезка" << endl;
	getValue(b);

	cout << "Введите погрешность" << endl;
	getValue(eps);

	cout << "Введите шаг" << endl;
	getValue(h);

	} while (isValuesRight(a,b,h,eps));


}
void printRezults(double& a, double& b, double& h, double& eps) {

	string funcTextArray[] = { "Метод Ньютона","Метод Верстеина","Метод Секущих","Метод Простых Итераций" };
	double (*funcArray[4])(double, double, ...) = { FindRootNewton,FindRootWerstein,FindRootSecant,FindRootSimpleIteration };


	cout << "Параметры             |  a=" << a << "   |   b=" << b << "  |  h=" << h << " | eps=" << eps << endl;

	for (size_t i = 0; i < 4; i++)
	{
		fPointer fpointer = funcArray[i];
		cout << "---------------------------------------------------------------" << endl;
		cout << funcTextArray[i] << endl;
		int n = 0;
		for (double x = a; x <= b; x += h)
		{
			if (F(x) * F(x + h) <= 0)
			{
				n++;
				cout << "                      | " "x" << n << " = " << fpointer(x, eps, h) << "   f(x)" << F(x) << endl;
			}

		}
		if (n == 0) cout << "Корней нет\n";
	}
	
}
