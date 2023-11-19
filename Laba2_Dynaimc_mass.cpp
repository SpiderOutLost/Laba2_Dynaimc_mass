 #include <iostream>
#include <fstream>
using namespace std;

void ReadMatrix(ifstream& file, int** matrix, int n) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			file >> matrix[i][j];
		}
	}
}
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
	void DeleteHead() {
		Index* tmp = head;
		head = head->next;
		delete tmp;
		length--;
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
	//Пузырьковая сортировка
	void Sort(void) {
		Index* t, * m, * a, * b;
		if (head == NULL)
			return;

		for (bool go = true; go; ) {
			go = false;
			a = t = head;
			b = head->next;

			while (b != NULL) {
				if (a->var > b->var) {
					if (t == a)
						head = b;
					else
						t->next = b;

					a->next = b->next;
					b->next = a;

					m = a, a = b, b = m;
					go = true;
				}
				t = a;
				a = a->next;
				b = b->next;
			}
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
class DiagonalMatrix {
private:
	size_t cols = 0;
	size_t rowses = 0;

public:

	int** Pack(int** Matrix, size_t rows, size_t col) {

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
						Index.add(j - i);

						if (Index.WasInSpisOK(j - i) == false) {
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

		Index.Sort();
		// Запаковываю
		// Новая матрица получается размером строк на m. Количество столбцов = m

		size_t col_new = m;
		int** Packmatrix = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			Packmatrix[i] = new int[col_new];
		}
		// Упаковка матрицы
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < col_new; j++)
			{
				Packmatrix[i][j] = 0; // заполнение нулями
			}
		}
		// сам процесс упаковки
		for (int i = 0; i < Index.Length(); i++)
		{
			int index = Index.GetElement(i);
			if (index < 0) {
				for (int j = -index; j < rows; j++)
				{
					Packmatrix[i][j] = Matrix[j][index + j];
				}
			}
			else
			{
				for (int j = index; j < rows; j++)
				{
					Packmatrix[i][j - index] = Matrix[j - index][j];

				}
			}
		}
		cols = m;
		rowses = rows;
		for (int i = 0; i < rows; i++)
		{
			delete[] Matrix[i];
		}
		delete[] Matrix;
		return Packmatrix;
	}
	int Rows() {
		return rowses;
	}
	int Col() {
		return cols;
	}
	
};
int Getdata(int** Matrix, int i, int j) {
	return Matrix[i][j];
}
int** SumOfMatrix(int** Matrix1, int** Matrix2, int row1, int col1, int row2, int col2) {
	if (row1 == row2 && col1 == col2) {
		int** m3 = new int* [row1];
		for (int i = 0; i < row1; i++)
		{
			m3[i] = new int[col1];
		}
		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < col1; j++)
			{
				m3[i][j] = Getdata(Matrix1, i, j) + Getdata(Matrix2, i, j);

			}
		}
		return m3;
	}
	else
	{
		cout << "Матрицы разного размера";
	}
}
#include <iostream>
using namespace std;

class CCSMatrix {
public:
	int* A;
	int* LI;
	int* LJ;
	int a; //кол-во ненулевых элементов
	size_t rows, col; // размеры матрицы
	CCSMatrix(int** Matrix, size_t rows, size_t col) {
		this->rows = rows;
		this->col = col;
		Init(Matrix);
	}
	void Init(int** Matrix) {
		a = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < col; j++) {
				if (Matrix[i][j] != 0) {
					a++;
				}
			}
		}
		A = new int[a];
		LI = new int[a];
		LJ = new int[col + 1];
		LJ[0] = 0;
		int k = 0;
		for (int j = 0; j < col; j++) {
			for (int i = 0; i < rows; i++) {
				if (Matrix[i][j] != 0) {
					A[k] = Matrix[i][j];
					LI[k] = i;
					k++;
				}
			}
			LJ[j + 1] = k;
		}
	}
	int GetElement(int i, int j) const {
		for (int k = LJ[j]; k < LJ[j + 1]; k++) {
			if (LI[k] == i) {
				return A[k];
			}
		}
		return 0;
	}
	void Print() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < col; j++) {
				cout << GetElement(i, j) << "\t";
			}
			cout << endl;
		}
	}
	void PrintCCS() {
		cout << "Values: ";
		for (int i = 0; i < a; i++) {
			cout << A[i] << " ";
		}
		cout << endl;
		cout << "Row Indices: ";
		for (int i = 0; i < a; i++) {
			cout << LI[i] << " ";
		}
		cout << endl;
		cout << "Column Pointers: ";
		for (int j = 0; j <= col; j++) {
			cout << LJ[j] << " ";
		}
		cout << endl;
	}
};


int main() {
	setlocale(LC_ALL, "Rus");
	ifstream file("matrixes.txt");
	if (!file) {
		cout << "Не удалось открыть файл" << std::endl;
		return 1;
	}
	int n1;
	file >> n1;
	int** matrix1 = new	int*[n1];
	for (int i = 0; i < n1; i++)
	{
		matrix1[i] = new int[n1];
	}
	ReadMatrix(file, matrix1, n1);

	int n2;
	file >> n2;
	int** matrix2 = new int* [n2];
	for (int i = 0; i < n2; i++)
	{
		matrix2[i] = new int[n2];
		
	}
	ReadMatrix(file, matrix2, n2);
	
	file.close();
	DiagonalMatrix m1;
	DiagonalMatrix m2;
	int**m1Pack = m1.Pack(matrix1, n1, n1);
	int** m2Pack = m2.Pack(matrix2, n2, n2);
	
	int** m3 = SumOfMatrix(m1Pack, m2Pack, m1.Rows(), m1.Col(), m2.Rows(), m2.Col());
	for (int i = 0; i < m1.Rows(); i++)
	{
		for (int j = 0; j < m1.Col(); j++)
		{
			cout << Getdata(m3, i, j);
		}
		cout << "\n";
	}
	cout << "\n";
	size_t Rows_CCS = m1.Rows();
	size_t Cols_CCS = m1.Col();

	CCSMatrix m_ccs { m3, Rows_CCS, Cols_CCS};
	m_ccs.Init(m3);
	m_ccs.PrintCCS();
	return 0;
}

	