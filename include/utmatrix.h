﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);                // конструктор копирования
	~TVector();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector& v) const;  // сравнение
	bool operator!=(const TVector& v) const;  // сравнение
	TVector& operator=(const TVector& v);     // присваивание

	// скалярные операции
	TVector  operator+(const ValType& val);   // прибавить скаляр
	TVector& operator+=(const ValType& val);   // прибавить скаляр
	TVector  operator-(const ValType& val);   // вычесть скаляр
	TVector& operator-=(const ValType& val);   // вычесть скаляр
	TVector  operator*(const ValType& val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector& v);     // сложение
	TVector& operator+=(const TVector& v);     // сложение
	TVector  operator-(const TVector& v);     // вычитание
	TVector& operator-=(const TVector& v);     // вычитание
	ValType  operator*(const TVector& v);     // скалярное произведение

	// ввод-вывод
	friend istream& operator>>(istream& in, TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TVector& v)
	{
		for (int i = 0; i < v.Size; i++)
			//out << v.pVector[i] << ' ';
			out << v.pVector[i] << '\t';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
	if ((s < 0) || (s > MAX_VECTOR_SIZE) || (si < 0) || ((si >= s) && (si != 0)))
		throw "Size is out of range";
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v) : Size(v.Size), StartIndex(v.StartIndex)
{
	if (this != &v)
	{
		pVector = new ValType[Size];
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < 0) || (pos >= Size))
		throw "Index is out of range";
	return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
		return false;
	if (StartIndex != v.StartIndex)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
	return !operator==(v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (this != &v)
	{
		delete[] this->pVector;
		Size = v.Size;
		StartIndex = v.StartIndex;
		pVector = new ValType[Size];
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] += val;
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType>& TVector<ValType>::operator+=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		this->pVector[i] += val;
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] -= val;
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType>& TVector<ValType>::operator-=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		this->pVector[i] -= val;
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector<ValType> result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] *= val;
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "Addition vectors of different size is impossible";
	TVector<ValType> result(Size, __min(StartIndex, v.StartIndex));
	for (int i = 0; i < Size; i++)
		result.pVector[i] = this->pVector[i] + v.pVector[i];
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType>& TVector<ValType>::operator+=(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "Addition vectors of different size is impossible";
	StartIndex = __min(StartIndex, v.StartIndex);
	for (int i = 0; i < Size; i++)
		this->pVector[i] += v.pVector[i];
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "Subtraction vectors of different size is impossible";
	TVector<ValType> result(Size, __min(StartIndex, v.StartIndex));
	for (int i = 0; i < Size; i++)
		result.pVector[i] = this->pVector[i] - v.pVector[i];
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType>& TVector<ValType>::operator-=(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "Subtraction vectors of different size is impossible";
	StartIndex = __min(StartIndex, v.StartIndex);
	for (int i = 0; i < Size; i++)
		this->pVector[i] -= v.pVector[i];
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw "Multiplication vectors of different size is impossible";
	ValType result = {};
	for (int i = 0; i < Size; i++)
		result += this->pVector[i] * v.pVector[i];
	return result;
} /*-------------------------------------------------------------------------*/


// Матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
	bool operator==(const TMatrix& mt) const;      // сравнение
	bool operator!=(const TMatrix& mt) const;      // сравнение
	TMatrix& operator= (const TMatrix& mt);        // присваивание
	TMatrix  operator+ (const TMatrix& mt);        // сложение
	TMatrix  operator- (const TMatrix& mt);        // вычитание

	// ввод / вывод
	friend istream& operator>>(istream& in, TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix& mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if ((s < 0) || (s > MAX_MATRIX_SIZE))
		throw "Size is out of range";
	for (int i = 0; i < s; i++)
		pVector[i] = TVector<ValType>(s);
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	return (TVector<TVector<ValType>>::operator==(mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return (!(*this == mt));
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	if (*this != mt)
	{
		if (Size != mt.Size)
		{
			Size = mt.Size;
			delete[] pVector;
			pVector = new TVector<ValType>[Size];
		}
		StartIndex = mt.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = mt.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	if (Size != mt.Size)
		throw "Addition matrixes of different size is impossible";
	TMatrix result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] += mt.pVector[i];
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	if (Size != mt.Size)
		throw "Subtruction matrixes of different size is impossible";
	TMatrix result(*this);
	for (int i = 0; i < Size; i++)
		result.pVector[i] -= mt.pVector[i];
	return result;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
