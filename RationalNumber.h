#ifndef RNUM_H
#define RNUM_H

#include <iostream>

class RationalNumber
{
  int mN, mD;

 public:
  RationalNumber();
  RationalNumber(int pN); // x/1
  RationalNumber(std::string pRepr); // "5/7"
  RationalNumber(int pN, int pD);
	RationalNumber(const RationalNumber &);

  void swap(const RationalNumber &) throw();

	int getNumerator() const;
	int getDenominator() const;

  void setNumerator(const int pN);
  void setDenominator(const int pD);

	void simplify();

  RationalNumber& operator=(const RationalNumber &);

	RationalNumber operator+(const RationalNumber &) const;
	RationalNumber operator-(const RationalNumber &) const;
	RationalNumber operator*(const RationalNumber &) const;
	RationalNumber operator/(const RationalNumber &) const;

	bool operator==(const RationalNumber &) const;
	bool operator!=(const RationalNumber &) const;
	bool operator<=(const RationalNumber &) const;
	bool operator<(const RationalNumber &) const;
	bool operator>=(const RationalNumber &) const;
	bool operator>(const RationalNumber &) const;

  // helpers
  std::string repr();
};

#endif
