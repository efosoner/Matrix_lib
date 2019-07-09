#pragma once
#pragma once

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <cmath>
#include <string>
#include <unordered_map>

using namespace std;

const double eps = 1e-12;

class Matrix {
	int height, width;
	bool isSquare;

	void InitializeTable();
	bool CheckIfSquare();
public:
	double** MatrixTable;

	Matrix(int m, int n, double value = 0);
	Matrix(int size);
	Matrix(const Matrix& m);
	~Matrix();

	int getHeight() const;
	int getWidth() const;
	Matrix Transposition() const;
	Matrix Power(int b) const;
	void n2search(double variable);

	Matrix& operator=(const Matrix& m);
	friend istream& operator>>(istream& in, const Matrix& m);
	friend ostream& operator<<(ostream& out, const Matrix& m);

	friend int operator==(const Matrix& a, const Matrix& b);
	friend int operator!=(const Matrix& a, const Matrix& b);

	friend Matrix operator+(const Matrix& a, const Matrix& b);
	friend Matrix operator+(const Matrix& a, double b);
	friend Matrix operator+(double b, const Matrix& a);
	friend Matrix operator-(const Matrix& a);
	friend Matrix operator-(const Matrix& a, const Matrix& b);
	friend Matrix operator-(const Matrix& a, double b);
	friend Matrix operator*(const Matrix& a, const Matrix& b);
	friend Matrix operator*(const Matrix& a, double b);
	friend Matrix operator*(double b, const Matrix& a);

	Matrix& operator+=(const Matrix& b);
	Matrix& operator+=(double b);
	Matrix& operator*=(const Matrix& b);
	Matrix& operator*=(double b);
	Matrix& operator-=(const Matrix& b);
	Matrix& operator-=(double b);

	friend bool CheckSizeSum(const Matrix& a, const Matrix& b);
	friend bool CheckSizeProduct(const Matrix& a, const Matrix& b);
	friend double det(const Matrix& a, int n);
	friend Matrix getCofactor(const Matrix& a, int p, int q, int n);
	friend Matrix reverse(const Matrix& a);

	static Matrix UnitMatrix(int size);
	static Matrix ZeroMatrix(int height, int width);
};