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
public:
	int** Matrix;
	int* Index;
	
	int** Pack(size_t rows, size_t col) {
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
		return Packmatrix;

	}
	~DiagonalMatrix(){
		delete[] Matrix;
	
	}
};
template <size_t rows, size_t col>
pair <size_t, size_t> getMatrixSize(int(&Packmatrix)[rows][col]) {
	return { rows, col };
}
int** AdditionMatrix(int** Packmatrix1, int** Packmatrix2, size_t rows1, size_t col1, size_t rows2, size_t col2) {

	if (rows1 == rows2 && col1 == col2) {
		int** Matrix3 = new int* [rows1];
		for (int i = 0; i < rows1; i++)
		{
			Matrix3[i] == new int[col1];
		}

		for (int i = 0; i < rows1; i++)
		{
			for (int j = 0; j < col1; j++)
			{
				Matrix3[i][j] = Packmatrix1[i][j] + Packmatrix2[i][j];
			}
		}
		return Matrix3;
	}
	else
	{
		cout << "Матрицы разного размера";
	}
}
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
	}
	void Inin(const int** const Matrix) {
		int a = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (Matrix[i][j] != 0) {
					a++;
				}
			}
		}
		int* A = new int[a];
		int* LI = new int[rows * a];
		int* LJ = new int[rows + 1];
		LJ[0] = 0;
		int k = 0;
		for (int j = 0; j < col; j++)
		{
			for (int i = 0; i < rows; i++)
			{
				if (Matrix[i][j] != 0) {
					A[k] = Matrix[i][j];
					LI[k] = i;
					k++;
				}
			}
			LJ[j + 1] = k;
		}
	}
	int GetElement(int i, int j) {
	
		int N1 = LI[i];
		int N2 = LI[i + 1];
		for (int k = N1; k < N2; k++)
		{
			if (LJ[k] == j)
			{
				return A[k];
				
			}
		}
	}
	void Print() {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << GetElement(i, j), "t";
			}
			cout << endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Rus");
	DiagonalMatrix Matrix1;
	DiagonalMatrix Matrix2;
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
	DiagonalMatrix m1{matrix1};
	m1.Pack(n1, n1);
	DiagonalMatrix m2{ matrix2 };
	m2.Pack(n2, n2);
	auto size = 
	/*Matrix1.Create_and_Pack(3, 3);
	Matrix2.Create_and_Pack(3, 3);
	int** Matrix = AdditionMatrix(Matrix1.Create_and_Pack(3, 3), Matrix2.Create_and_Pack(3, 3), 3,3,3,3);
	CCSMatrix(Matrix, 3,3);*/
	return 0;
}

	