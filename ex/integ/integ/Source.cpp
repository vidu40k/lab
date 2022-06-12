#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;


double	f(double x);
double integByTrap(double a, double b, size_t n);
double integByTrapWithAccuracy(double a, double b, double e);
double averageMethod(double a, double b, int n);
double averageMethodByAccuracy(double a, double b, double eps);
template<class T>
void getValue(T& num);
void printMenu(string* arr, int size, int current);
int choose(string* arr, size_t size);
void byTheNumberOfPartitions();
void byTheAccuracy();

int main() {

	double upperLim, lowerLim, sum, e;
	size_t n;

	size_t optionsCount=3;
	string options[] =
	{
	"По количеству разбиений",
	"По заданной точности",
	"Выход"
	};
	enum
	{
		BY_THE_NUMBER_OF_PARTITIONS = 1, BY_THE_SPECIFIED_ACCURACY, EXIT
	};
	do
	{
	switch (choose(options,optionsCount))
	{
	case BY_THE_NUMBER_OF_PARTITIONS:
		byTheNumberOfPartitions();
		break;
	case BY_THE_SPECIFIED_ACCURACY:
		byTheAccuracy();
		break;
	case EXIT:
		return 0;
	}
	cout << "Нажмите 1 чтобы продолжить" << endl;
	} while (_getch() == '1');
	
}

double	f(double x) {
	return x * x - 10 * sin(x) * sin(x);
}
double integByTrap(double a, double b, size_t n) {

	double sum = 0;
	double step;
	size_t i;
	if (0 == n) return sum;

	step = (b - a) / (1.0 * n);
	for (i = 1; i < n; ++i) {
		sum += f(a + i * step);
	}
	sum += (f(a) + f(b)) / 2;
	sum *= step;
	return sum;
}
double integByTrapWithAccuracy(double a, double b, double e) {

	double sum = 0;
	double step;
	size_t i;
	size_t n = 2;
	if (0 == n) return sum;

	step = (b - a) / n;
	for (i = 1; i < n; ++i) {
		sum += f(a + i * step);
	}

	sum += (f(a) + f(b)) / 2;
	sum *= step;
	double I1 = sum;
	double I2 = I1 + 1;

	int k = 1;

	while (fabs(I1 - I2) > e)
	{
		n *= 2;
		step = (b - a) / n;

		if (k != 1)
		{
			I1 = I2;
		}
		sum = 0;

		for (i = 1; i < n; ++i) {
			sum += f(a + i * step);
		}

		I2 = step * sum;

		k++;
	}

	cout << "n=" << n << endl;
	return I2;
}
double averageMethod(double a, double b, int n) {



	double s = (f(a) + f(b)) / 2.;
	double h = (b - a) / n;
	double x1, x2, x;
	double I;
	for (int i = 1; i <= n; i++)
	{
		x1 = a + (i - 1) * h;
		x2 = a + i * h;
		x = (x1 + x2) / 2.;
		s += f(x);
	}
	I = h * s;



	return I;

}
double averageMethodByAccuracy(double a, double b, double eps) {

	int n = 2;
	double s = (f(a) + f(b)) / 2.;
	double h = (b - a) / n;
	double x1, x2, x;
	double I1 = averageMethod(a, b, n), I2;

	I2 = I1 + 1;
	int k = 1;

	while (fabs(I1 - I2) >= eps) {
		n *= 2;
		h = (b - a) / n;
		if (k != 1) {
			I1 = I2;
		}
		s = 0;
		for (int i = 1; i <= n - 1; i++)
		{
			x1 = a + (i - 1) * h;
			x2 = a + i * h;
			x = (x1 + x2) / 2.;
			s += f(x);
		}

		I2 = h * s;
		k++;
	}
	return I2;
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
void byTheNumberOfPartitions() {

	double upperLim, lowerLim, sum;
	size_t n;
	cout << "Введите верхний предел" << endl;
	cin >> upperLim;

	cout << "Введите нижний предел" << endl;
	cin >> lowerLim;

	cout << "Введите количество разбиений" << endl;
	cin >> n;

	sum = integByTrap(lowerLim, upperLim, n);
	cout << "Результат методом трапеций:" << sum << endl;;

	sum = averageMethod(lowerLim, upperLim, n);
	cout << "Результат методом средних:" << sum << endl;
}
void byTheAccuracy() {
	double upperLim, lowerLim, sum, e;


	cout << "Введите верхний предел" << endl;
	cin >> upperLim;

	cout << "Введите нижний предел" << endl;
	cin >> lowerLim;

	cout << "Введите точность" << endl;
	cin >> e;

	sum = integByTrapWithAccuracy(lowerLim, upperLim, e);
	cout << "Результат методом трапеций:" << sum << endl;

	sum = averageMethodByAccuracy(lowerLim, upperLim, e);
	cout << "Результат методом средних:" << sum << endl;

}
