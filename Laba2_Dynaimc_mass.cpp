#include <iostream>
using namespace std;
struct Index
{
	int var;
	Index* next;
};
class Spisok {
private:
	Index* head;

	size_t length = 0;
public:
	Spisok() {
		head = NULL;
	}
	void add(int d) {

		Index* NewVariable = new Index;

		NewVariable->var = d;
		NewVariable->next = NULL;


		if (head == NULL) {
			head = NewVariable;

		}
		else
		{
			Index* Cur = head;
			while (Cur->next != NULL) {
				Cur = Cur->next;
			}
			Cur->next = NewVariable;
		}

		length++;
	}
	int GetFirstElement() {
		return head->var;
	}
	void DeleteHead() {
		Index* tmp = head;
		head = head->next;
		delete tmp;
		length--;
	}
	size_t  HowMuch() {
		return length;
	}
	int& GetElement(int INDEX) {
		Index* Cur = head;
		int counter = 0;
		while (Cur != nullptr) {
			if (counter == INDEX) {
				return Cur -> var;
			}
			Cur = Cur->next;
			counter++;
		}
		
	
	}
	int Length() {
		return length;
	}
	void Print() {
		Index* Cur = head;
		while (Cur != NULL) {
			cout << Cur->var << "\n";
			Cur = Cur->next;
		}
	}
	bool WasInSpisOK(int number) {
		Index* Cur = head;
		while (Cur != NULL) {
			if (Cur->var == number) {
				return true;
			}
			Cur = Cur->next;
		}
		return false;
	}
};
void Create_and_Pack(int rows, int col) {
	int** Matrix = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		Matrix[i] = new int[col];

	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << i + 1 << j + 1 << "\t";
			cin >> Matrix[i][j];
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}
	int m = 0;//количество ненулевых диагоналей и кол-во столбцов в упаковке
	Spisok Index; // список ненулевых диагоналей
	// главная диагональ

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < col; j++) {
			if (i == j && Matrix[i][j] != 0) {
				m++;
				Index.add(0);
				break;
			}
		}
		if (m == 1) {
			break;
		}
	}
	// проверка нижних диагоналей
	
	for (int i = 1; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{

			if (Matrix[i][j] != 0 && j == 0) {
				m++;
				Index.add(-i);
				continue;
			}

			if (j < i) {
				if (Matrix[i][j] != 0 && Matrix[i - j][i - j - 1] == 0) {
					m++;
					Index.add(-(i - j));
					if (Index.WasInSpisOK(-(i - j)) == false) {
						m++;
					}
				}
			}
		}
	}
	
	//проверка верхних диагоналей

	for (int i = 0; i < rows; i++)
	{
		for (int j = 1; j < col; j++)
		{
			if (i == 0 && Matrix[i][j] != 0) {
				m++;
				Index.add(j);
				continue;
			}
			if (i < j) {
				if (Matrix[i][j] != 0 && Matrix[j - i - 1][j - i] == 0) {
					m++;
					Index.add(j - i);
					if (Index.WasInSpisOK(j - i) == false)
					{
						m++;
					}


				}
			}
		}
	}
	cout << m;
	// Запаковываю
	// Новая матрица получается размером строк на m. Количество столбцов = m
	int col_new = m;
	int** Matrix_New = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		Matrix_New[i] = new int[col_new];
	}

	for (int i = 0; i < Index.Length(); i++)
	{
		Index.GetElement(i);
	}
	// Упаковка нижнего треугольника
	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col_new; j++)
		{
			if ()
		}
	}*/

}
int main() {
	setlocale(LC_ALL, "Rus");

	int rows; // кол-во строк 
	int col;// кол-во столбцов
	cin >> rows;
	cin >> col;
	Create_and_Pack(rows, col);
	
	return 0;
}

	