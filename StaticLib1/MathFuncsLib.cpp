#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include "stdafx.h"
#include "MathFuncsLib.h"

template <class T> const T& max(const T& a, const T& b) {
	return (a < b) ? b : a;
}

////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////
BigNumber::BigNumber()
{
}

BigNumber::BigNumber(short x) { initFromUnSigned(x); }

BigNumber::BigNumber(std::string    s)
{
	std::string x = s;
	//cas du moins
	if (x[0] == '-') {
		sign = Sign::MINUS;
		x = x.substr(1, x.length() - 1);
	}
	else
		sign = Sign::PLUS;

	char c;
	Lastone = x.length() - 1;
	for (int i = x.length() - 1; i >= 0; i--) {
		c = x[i] - '0';
		if ((c >= 0) && (c <= 9))
			Number1[Lastone - i] = c;
		else {
			printf("char error not a digit\n");
			Number1[Lastone - i] = 0; //TODO d¨¦clanchement d'erreur
		}
	}
	norma();
}
BigNumber::BigNumber(std::vector  <int> s)
{

	std::vector  <int> x = s;
	//cas du moins
	if (x[0] == '-') {
		sign = Sign::MINUS;
		for (int i = 1; i < x.size() - 1; i++) {
			x[i-1] = x[i];
		}
	}
	else
		sign = Sign::PLUS;

	char c;
	Lastone = x.size() - 1;
	for (int i = x.size() - 1; i >= 0; i--) {
		c = x[i] - 0;
		if ((c >= 0) && (c <= 9))
			Number1[Lastone - i] = c;
		else {
			printf("char error not a digit\n");
			Number1[Lastone - i] = 0; //TODO d¨¦clanchement d'erreur
		}
	}
	norma();
}

////////////////////////////////////////////////////////////////////////////////
// Copy constructor
////////////////////////////////////////////////////////////////////////////////
BigNumber::BigNumber(const BigNumber &n) {
	//cas n=n;
	if (this == &n)
		return;
	this->initia();
	this->sign = n.sign;
	this->Lastone = n.Lastone;
	for (unsigned int i = 0; i <= n.Lastone; i++)
		this->Number1[i] = n.Number1[i];
}

BigNumber::BigNumber(const BigNumber* n) {
	//cas n=n;
	if (this == n)
		return;
	this->initia();
	this->sign = n->sign;
	this->Lastone = n->Lastone;
	for (unsigned int i = 0; i <= n->Lastone; i++)
		this->Number1[i] = n->Number1[i];
}

////////////////////////////////////////////////////////////////////////////////
// templates
////////////////////////////////////////////////////////////////////////////////
template <class X> void BigNumber::initFromSigned(X x)
{
	//only Number1
	int tmpNumber1 = -1;
	X t = x;
	while (t != 0) {
		tmpNumber1++;
		Number1[tmpNumber1] = t % 10;
		t = t / 10;
	}
	Lastone = abs(tmpNumber1);
}

template <class X> void BigNumber::initFromUnSigned(X x)
{
	//signe
	if (x > 0) {
		sign = Sign::PLUS;
		initFromSigned(x);
	}
	else
		if (x < 0) {
			sign = Sign::MINUS;
			initFromSigned(-x);
		}
}

////////////////////////////////////////////////////////////////////////////////
// operator
////////////////////////////////////////////////////////////////////////////////
void BigNumber::operator=(const BigNumber &n) {
	this->initia();
	this->sign = n.sign;
	this->Lastone = n.Lastone;
	for (unsigned int i = 0; i <= n.Lastone; i++)
		this->Number1[i] = n.Number1[i];
}

void BigNumber::copy(const BigNumber &n) {
	this->sign = n.sign;
	this->Lastone = n.Lastone;
	for (unsigned int i = 0; i <= n.Lastone; i++)
		this->Number1[i] = n.Number1[i];
}
void BigNumber::absolute(const BigNumber &n) {
	this->copy(n);
	if (this->Number1[0] > 0)
		this->sign = Sign::PLUS;
}

std::ostream & operator << (std::ostream& sortie, const BigNumber & n)
{
	std::stringstream oss;
	if (n.sign == BigNumber::Sign::MINUS)
		oss << "-";
	char a;
	for (int tmp = n.Lastone; tmp >= 0; tmp--) {
		a = n.Number1[tmp] + '0';
		oss << a;
	}
	sortie << oss.str();
	return sortie;
}

BigNumber BigNumber::operator -() const
{
	BigNumber n(this);
	n.opp();
	return n;
}

bool BigNumber::operator !=(const BigNumber &n) const {
	return !operator ==(n);
}

bool BigNumber::operator ==(const BigNumber &n) const {
	if (this->sign != n.sign)
		return false;
	if (this->Lastone != n.Lastone)
		return false;
	for (unsigned int i = 0; i <= n.Lastone; i++) {
		if (this->Number1[i] != n.Number1[i])
			return false;
	}
	return true;
}


BigNumber BigNumber::operator +(const BigNumber &x) const {
	BigNumber ans;
	ans.add(*this, x);
	return ans;
}

BigNumber BigNumber::operator -(const BigNumber &x) const {
	BigNumber ans;
	ans.sub(*this, x);
	return ans;
}

BigNumber BigNumber::operator *(const BigNumber &x) const {
	BigNumber ans;
	ans.mul(*this, x);
	return ans;
}

BigNumber BigNumber::operator /(const BigNumber &x) const {
	if (x.sign == Sign::NUL) throw "BigNumber::operator /: division by zero";
	BigNumber q, r;
	q.div(*this, x, r);
	return q;
}

BigNumber BigNumber::operator %(const BigNumber &x) const {
	if (x.sign == Sign::NUL) throw "BigNumber::operator %: division by zero";
	BigNumber q, r;
	q.div(*this, x, r);
	return r;
}



////////////////////////////////////////////////////////////////////////////////
// fonctions
////////////////////////////////////////////////////////////////////////////////
BigNumber::CompRes BigNumber::compareTo(const BigNumber &n) const
{
	// Study of signs
	if (this->sign < n.sign)
		return CompRes::LESS;
	if (this->sign > n.sign)
		return CompRes::GREATER;
	// case 0=0
	if ((this->sign == Sign::NUL) && (n.sign == Sign::NUL))
		return CompRes::EQUAL;

	return absCompareTo(n);
}

BigNumber::CompRes BigNumber::absCompareTo(const BigNumber &n) const
{
	//study of Number1 (BigNumbers have the same sing)
	if (this->Lastone < n.Lastone)
		return CompRes::LESS;
	else if (this->Lastone > n.Lastone)
		return CompRes::GREATER;
	else {
		// Compare Number1 one by one
		int i = this->Lastone + 1;
		while (i > 0) {
			i--;
			if (this->Number1[i] == n.Number1[i])
				continue;
			else if (this->Number1[i] > n.Number1[i])
				return CompRes::GREATER;
			else
				return CompRes::LESS;
		}
		// If no blocks differed, the numbers are equal.
		return CompRes::EQUAL;
	}
}



void BigNumber::initia()
{
	sign = Sign::NUL;
	Lastone = 0;
	for (int i = 0; i < MAX_Number1; i++)
		Number1[i] = 0;
}


void BigNumber::norma()
{
	while ((this->Lastone > 0) && (this->Number1[this->Lastone] == 0))
		this->Lastone--;

	if ((this->Lastone == 0) && (this->Number1[0] == 0))
		this->sign = Sign::NUL;
}

// printf -- obsolete --
void BigNumber::print()
{
	
//	printf("Number1:  %i\n", this->Lastone);
	if (this->sign == Sign::MINUS)
		printf("-");
	if (this->sign == Sign::PLUS)
		printf("+");
	if (this->sign == Sign::NUL)
		printf("o");
	for (int tmp = Lastone; tmp >= 0; tmp--) {
		//std::string  number;
		//number = Number1;
		printf("%i", Number1[tmp]);
	
	}
	/*std::string  number;
    number = Number1;
	
	std::cout << number;*/
	printf("\n");
}

void BigNumber::opp()
{
	if (this->sign == Sign::NUL) return;
	if (this->sign == Sign::PLUS) { this->sign = Sign::MINUS; return; }
	if (this->sign == Sign::MINUS) { this->sign = Sign::PLUS; return; }
};

void BigNumber::add(const BigNumber &a, const BigNumber &b)
{
	if ((a.sign == Sign::PLUS) && (b.sign == Sign::PLUS)) {
		this->sign = Sign::PLUS;
		this->addpos(a, b);
		return;
	}
	if ((a.sign == Sign::MINUS) && (b.sign == Sign::MINUS)) {
		this->sign = Sign::MINUS;
		this->addpos(a, b);
		return;
	}
	if (a.sign == Sign::NUL) {
		this->copy(b);
		return;
	}
	if (b.sign == Sign::NUL) {
		this->copy(a);
		return;
	}

	//Sign are different
	if (a.absCompareTo(b) == CompRes::GREATER) {
		this->sign = a.sign;
		this->subpos(a, b);
	}
	else {
		this->sign = b.sign;
		this->subpos(b, a);
	}
}


void BigNumber::sub(const BigNumber &a, const BigNumber &b)
{
	add(a, -b);
}

void BigNumber::addpos(const BigNumber &a, const BigNumber &b)
{
	unsigned int max_Number1 = max(a.Lastone, b.Lastone);
	//~ printf("max Number1 %i\n", max_Number1);
	char tmp, carry = 0;

	//~ this->sign = Sign::PLUS;
	for (unsigned int i = 0; i <= max_Number1; i++) {
		tmp = a.Number1[i] + b.Number1[i] + carry;
		if (tmp > 9) {
			this->Number1[i] = tmp - 10;
			carry = 1;
		}
		else {
			this->Number1[i] = tmp;
			carry = 0;
		}
	}
	//~ printf("max Number1 %i\n", this->Number1[max_Number1]);
	if (carry != 0) {
		this->Number1[max_Number1 + 1] = carry;
		this->Lastone = max_Number1 + 1;
	}
	else
		this->Lastone = max_Number1;
}

void BigNumber::subpos(const BigNumber &a, const BigNumber &b)
{
	char borrow = 0;
	char v;
	unsigned int i;

	this->Lastone = a.Lastone;

	for (i = 0; i <= a.Lastone; i++) {
		v = a.Number1[i] - borrow - b.Number1[i];
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}
		else
			borrow = 0;

		this->Number1[i] = v;
	}
	this->norma();
}


void BigNumber::mul(const BigNumber &n, const BigNumber &b)
{
	this->initia();
	if (n.sign == Sign::NUL || b.sign == Sign::NUL)
		return;
	if ((n.sign == Sign::PLUS && b.sign == Sign::PLUS) ||
		(n.sign == Sign::MINUS && b.sign == Sign::MINUS))
		this->sign = Sign::PLUS;
	else
		this->sign = Sign::MINUS;

	BigNumber tmp;// = n;
	for (unsigned int i = 0; i <= b.Lastone; i++) {
		tmp.mulByChar(n, b.Number1[i]);
		tmp.Number1hift(i);
		this->addpos(this, tmp);
	}
}

void BigNumber::Number1hift(int d)
{
	int i;

	if ((this->Lastone == 0) && (this->Number1[0] == 0))
		return;

	for (i = this->Lastone; i >= 0; i--)
		this->Number1[i + d] = this->Number1[i];
	for (i = 0; i < d; i++)
		this->Number1[i] = 0;

	this->Lastone += d;
}

void BigNumber::mulByChar(const BigNumber &n, const char a)
{
	if (a == 0) {
		this->initia();
		//~ this->Lastone = 0;
		//~ this->Number1[0]=0;
		//~ this->sign=Sign::NUL;
		return;
	}

	this->sign = Sign::PLUS;
	if (a < 0) {
		if (this->sign == Sign::PLUS)
			this->sign = Sign::MINUS;
		if (this->sign == Sign::MINUS)
			this->sign = Sign::PLUS;

		if (this->sign == Sign::NUL)
			return;
	}

	char v;
	unsigned int i;
	char carry = 0;

	this->Lastone = n.Lastone;
	for (i = 0; i <= n.Lastone; i++) {
		v = n.Number1[i] * a + carry;
		if (v > 9) {
			carry = v / 10;
			this->Number1[i] = v % 10;
		}
		else {
			carry = 0;
			this->Number1[i] = v;
		}
	}
	if (carry != 0) { //TODO cas capacity
		this->Lastone++;
		this->Number1[this->Lastone] = carry;
	}
}


void BigNumber::div(const BigNumber &_a, const BigNumber &_b, BigNumber &r)
{
	BigNumber a, b;
	a.absolute(_a);
	b.absolute(_b);

	if (a < b) {
		r = a;
		this->initia();
		return;
	}

	BigNumber tmp;
	BigNumber result;
	BigNumber tmpA = a;
	r.initia();
	tmp.initia();
	result.initia();

	//~ printf("diff : %i\n",a.Lastone-b.Lastone);
	//~ printf(" "); tmpA.print();
	result.Lastone = a.Lastone - b.Lastone;
	result.sign = Sign::PLUS;
	for (int i = a.Lastone - b.Lastone; i >= 0; i--) {
		tmp = b;
		tmp.Number1hift(i);
		//~ printf("       "); std::cout << tmp << std::endl;
		while (tmpA > tmp) {
			result.Number1[i] = result.Number1[i] + 1;
			tmpA = tmpA - tmp;
		}
		//~ printf(" "); tmpA.print();
	}
	r = tmpA;
	result.norma();
	this->copy(result);

	if (_a.sign == _b.sign)
		return;

	if (_a.sign == Sign::MINUS && _b.sign == Sign::PLUS) {
		this->sign = Sign::MINUS;
		*this = *this - 1;
		r = b - r;
		return;
	}

	if (_a.sign == Sign::PLUS && _b.sign == Sign::MINUS) {
		this->sign = Sign::MINUS;
		return;
	}
}