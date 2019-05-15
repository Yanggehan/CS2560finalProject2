#ifndef _BIG_NUM_HPP_
#define _BIG_NUM_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#define MAX_Number1 1000

class BigNumber
{
public:
	BigNumber();
	// Constructors from primitive integer types
	
	BigNumber(short x);

	BigNumber(std::vector<int>s);

	BigNumber(const BigNumber &n);
	BigNumber(const BigNumber* n);

	// Assignment operator
	void operator=(const BigNumber &x);
	BigNumber operator -() const;

	// Ordinary comparison operators
	bool operator ==(const BigNumber &n) const;
	bool operator !=(const BigNumber &n) const;
	bool operator < (const BigNumber &n) const { return compareTo(n) == CompRes::LESS; }
	bool operator <=(const BigNumber &n) const { return compareTo(n) != CompRes::GREATER; }
	bool operator >=(const BigNumber &n) const { return compareTo(n) != CompRes::LESS; }
	bool operator > (const BigNumber &n) const { return compareTo(n) == CompRes::GREATER; }

	// Normal operator
	BigNumber operator +(const BigNumber &x) const;
	BigNumber operator -(const BigNumber &x) const;
	BigNumber operator *(const BigNumber &x) const;
	BigNumber operator /(const BigNumber &x) const;
	BigNumber operator %(const BigNumber &x) const;

	


	//ostream
	friend std::ostream & operator << (std::ostream& sortie, const BigNumber & n);
	void print();

	// functions
	void opp();
	void add(const BigNumber &a, const BigNumber &b);
	void sub(const BigNumber &a, const BigNumber &b);
	void mul(const BigNumber &n, const BigNumber &b);
	void div(const BigNumber &_a, const BigNumber &_b, BigNumber &r);

	void mulByChar(const BigNumber &n, const char a);
	void Number1hift(int d);
private:
	//Enums Sign
	enum class Sign : char { NUL = 0, PLUS = 1, MINUS = -1 };

	// Enums Results of comparisons
	enum class CompRes : char { LESS = -1, EQUAL = 0, GREATER = 1 };

	void initia();
	void norma();
	void copy(const BigNumber &n);
	void absolute(const BigNumber &n);
	void addpos(const BigNumber &a, const BigNumber &b);
	void subpos(const BigNumber &a, const BigNumber &b);
	BigNumber::CompRes absCompareTo(const BigNumber &n) const;
	template <class X> void initFromSigned(X x);
	template <class X> void initFromUnSigned(X x);
	char Number1[MAX_Number1] = { 0 };
	
	Sign sign = Sign::NUL;
	unsigned int Lastone = 0;
	CompRes compareTo(const BigNumber &n) const;
};

#endif //_BIG_NUM_HPP_