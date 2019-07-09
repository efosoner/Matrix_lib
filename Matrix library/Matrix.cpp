#include "Matrix.h"
using namespace std;

void Matrix::InitializeTable() {
	MatrixTable = new double*[height];
	for (int i = 0; i < height; i++) {
		MatrixTable[i] = new double[width];
	}
}

bool Matrix::CheckIfSquare() {
	if (height == width) return true;
	else return false;
}

Matrix::Matrix(int m, int n, double value) : height(m), width(n) {

	isSquare = CheckIfSquare();
	InitializeTable();
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			MatrixTable[i][j] = value;
		}
	}
}

Matrix::Matrix(int size) : Matrix(size, size) {
}

Matrix::Matrix(const Matrix& m) {

	height = m.height;
	width = m.width;
	isSquare = m.isSquare;
	InitializeTable();

	for (int i = 0; i < m.height; i++) {
		for (int j = 0; j < m.width; j++) {
			MatrixTable[i][j] = m.MatrixTable[i][j];
		}
	}
}

Matrix::~Matrix() {

	for (int i = 0; i < width; i++) {
		delete[] MatrixTable[i];
	}
	delete[] MatrixTable;
}

int Matrix::getHeight() const {
	return height;
}

int Matrix::getWidth() const {
	return width;
}

Matrix Matrix::Transposition() const {

	Matrix temp(width, height);

	for (int i = 0; i < temp.height; i++) {
		for (int j = 0; j < temp.width; j++) {
			temp.MatrixTable[i][j] = MatrixTable[j][i];
		}
	}
	return temp;
}

Matrix Matrix::Power(int b) const {

	if (!isSquare) {
		throw "Invalid_argument\n";
	}
	else {
		Matrix temp(height, width);

		if (b == 0) {
			temp = UnitMatrix(width);
			return temp;
		}
		else if (b == 1) return *this;
		else {
			temp = UnitMatrix(width);
			for (int i = 0; i < b; i++) {
				temp = temp * (*this);
			}
			return temp;
		}
	}
}

void Matrix::n2search(double variable) {

	int height = this->height;
	int width = this->width;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (this->MatrixTable[i][j] == variable) {
				cout << "Your variable can be found in " << j << " column of " << i << " verse." << endl;
			}
		}
	}
}

Matrix& Matrix::operator=(const Matrix& m) {

	if (this != &m) {
		for (int i = 0; i < width; i++) {
			delete[] MatrixTable[i];
		}
		delete[] MatrixTable;

		height = m.height;
		width = m.width;
		isSquare = m.isSquare;
		InitializeTable();

		for (int i = 0; i < m.height; i++) {
			for (int j = 0; j < m.width; j++) {
				MatrixTable[i][j] = m.MatrixTable[i][j];
			}
		}
	}
	return *this;
}

istream& operator>>(istream& in, const Matrix& m) {

	for (int i = 0; i < m.height; i++) {
		cout << "Set coefficients for " << i + 1 << " line." << endl;
		for (int j = 0; j < m.width; j++) {
			in >> m.MatrixTable[i][j];
		}
	}
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, const Matrix& m) {

	out << "Matrix: " << "\n\n";
	for (int i = 0; i < m.height; i++) {
		for (int j = 0; j < m.width; j++) {
			out.width(7);
			out << m.MatrixTable[i][j];
		}
		out << "\n\n";
	}
	return out;
}

int operator==(const Matrix& a, const Matrix& b) {
	if (a.height == b.height && a.width == b.width) {
		for (int i = 0; i < a.width; i++) {
			for (int j = 0; j < a.height; j++) {
				if (a.MatrixTable[i][j] != b.MatrixTable[i][j]) return 0;
			}
		}
	}
	else return 0;
	return 1;
}

int operator!=(const Matrix& a, const Matrix& b) {
	if (a == b) return 0;
	else return 1;
}

Matrix operator+(const Matrix& a, const Matrix& b) {

	if (CheckSizeSum(a, b) != true) {
		throw "Invalid_argument\n";
	}
	else {
		Matrix Sum(a.height, a.width);
		for (int i = 0; i < Sum.height; i++) {
			for (int j = 0; j < Sum.width; j++) {
				Sum.MatrixTable[i][j] = a.MatrixTable[i][j] + b.MatrixTable[i][j];
			}
		}
		return Sum;
	}
}

Matrix operator+(const Matrix& a, double b) {
	if (a.isSquare != true) cout << "\nInvalid_argument\n";

	Matrix f = Matrix::UnitMatrix(a.height) * b;

	Matrix Sum(a.height, a.width);
	for (int i = 0; i < Sum.height; i++) {
		for (int j = 0; j < Sum.width; j++) {
			Sum.MatrixTable[i][j] = a.MatrixTable[i][j] + f.MatrixTable[i][j];
		}
	}
	return Sum;
}

Matrix operator+(double b, const Matrix& a) {

	return a + b;
}

Matrix operator-(const Matrix& a) {

	Matrix result(a.height, a.width);
	for (int i = 0; i < result.height; i++) {
		for (int j = 0; j < result.width; j++) {
			result.MatrixTable[i][j] = -a.MatrixTable[i][j];
		}
	}
	return result;
}

Matrix operator-(const Matrix& a, const Matrix& b) {

	Matrix result = a + (-b);
	return result;
}

Matrix operator-(const Matrix& a, double b) {
	if (a.isSquare != true) throw "\nInvalid_argument\n";

	Matrix f = Matrix::UnitMatrix(a.height) * -b;

	Matrix Sum(a.height, a.width);
	for (int i = 0; i < Sum.height; i++) {
		for (int j = 0; j < Sum.width; j++) {
			Sum.MatrixTable[i][j] = a.MatrixTable[i][j] + f.MatrixTable[i][j];
		}
	}
	return Sum;
}

Matrix operator*(const Matrix& a, const Matrix& b) {

	if (CheckSizeProduct(a, b) != true) {
		throw "Invalid_argument\n";
	}
	else {
		Matrix Product(b.height, a.width);

		for (int i = 0; i < Product.height; i++) {
			for (int j = 0; j < Product.width; j++) {
				double sum = 0;
				for (int k = 0; k < a.width; k++) {
					sum += a.MatrixTable[i][k] * b.MatrixTable[k][j];
				}
				Product.MatrixTable[i][j] = sum;
			}
		}
		return Product;
	}
}

Matrix operator*(const Matrix& a, double b) {

	Matrix Product(a.height, a.width);

	for (int i = 0; i < Product.height; i++) {
		for (int j = 0; j < Product.width; j++) {
			Product.MatrixTable[i][j] = a.MatrixTable[i][j] * b;
		}
	}
	return Product;
}

Matrix operator*(double b, const Matrix& a) {
	return operator*(a, b);
}

Matrix& Matrix::operator+=(const Matrix& b) {
	*this = *this + b;
	return *this;
}

Matrix& Matrix::operator+=(double b) {
	*this = *this + b;
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& b) {
	*this = *this + b;
	return *this;
}

Matrix& Matrix::operator*=(double b) {
	*this = *this * b;
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& b) {
	*this = *this + (-b);
	return *this;
}

Matrix& Matrix::operator-=(double b) {
	*this = *this + (-b);
	return *this;
}

bool CheckSizeSum(const Matrix& a, const Matrix& b) {
	if ((a.height == b.height) && (a.width == b.width)) return true;
	else return false;
}

bool CheckSizeProduct(const Matrix& a, const Matrix& b) {
	if (a.width == b.height) return true;
	else return false;
}

double det(const Matrix& a, int n) {

	double D = 0;

	if (n == 1) return a.MatrixTable[0][0];
	if (n == 2) {
		D = a.MatrixTable[0][0] * a.MatrixTable[1][1] - a.MatrixTable[0][1] * a.MatrixTable[1][0];
		return D;
	}
	int sign = 1;

	for (int i = 0; i < n; i++) {
		Matrix b = getCofactor(a, 0, i, n);
		if (a.MatrixTable[0][i] != 0)
			D = D + sign * a.MatrixTable[0][i] * det(b, n - 1);
		sign = -sign;
	}
	return D;
}

Matrix getCofactor(const Matrix& a, int p, int q, int n) {

	int i = 0, j = 0;
	Matrix b(n - 1, n - 1);

	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (row != p && col != q) {
				b.MatrixTable[i][j++] = a.MatrixTable[row][col];
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
	return b;
}

Matrix reverse(const Matrix& a) {

	int size = a.getWidth();
	Matrix b(size);
	int m = 1;
	if (det(a, size) != 0) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				b.MatrixTable[i][j] = m * det(getCofactor(a, i, j, size), size - 1);
				m = -m;
			}
		}
		b = b.Transposition();
		return b;
	}
	else throw "\nInvalid parameters.\n";
}

Matrix Matrix::UnitMatrix(int size) {

	Matrix temp(size, size);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) temp.MatrixTable[i][j] = 1;
			else temp.MatrixTable[i][j] = 0;
		}
	}
	return temp;
}

Matrix Matrix::ZeroMatrix(int height, int width) {

	Matrix temp(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			temp.MatrixTable[i][j] = 0;
		}
	}
	return temp;
}