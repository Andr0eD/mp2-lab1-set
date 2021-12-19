#pragma once
#include "BitField.h"

class TSet
{
private:
	int MaxPower; // максимальная мощность множества
	TBitField BitField; // битовое поле для хранения хар-го вектора
public:
	TSet(int mp);
	TSet(const TSet& s); // конструктор копирования
	TSet(const TBitField& bf); // конструктор преобразования типа
	operator TBitField(); // преобразование типа к битовому полю
	// доступ к битам
	int GetMaxPower(void) const; // максимальная мощность множества
	void InsElem(const int n); // включить элемент в множество
	void DelElem(const int n); // удалить элемент из множества
	int IsMember(const int n) const; // проверить наличие элемента в
	// множестве
	// теоретико-множественные операции
	int operator== (const TSet& s); // сравнение
	TSet& operator=(const TSet& s); // присваивание
	TSet operator+ (const int n); // включение элемента в множество
	TSet operator- (const int n); // удаление элемента из множества
	TSet operator+ (const TSet& s); // объединение
	TSet operator* (const TSet& s); // пересечение
	TSet operator~ (void); // дополнение
	friend istream& operator>>(istream& istr, TSet& bf);
	friend ostream& operator<<(ostream& ostr, const TSet& bf);
};