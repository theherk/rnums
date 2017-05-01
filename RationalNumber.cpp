#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>
#include "RationalNumber.h"

std::vector<std::string> parseDelimited(std::string s, char d)
{
  // Helper method to parse from string: "4/9".
  std::vector<std::string> tokens;
  std::istringstream ss(s);
  std::string token;
  while (getline(ss, token, d))
    {
      tokens.push_back(token);
    }
  if (tokens.size() != 2)
    // Require there be precisely 2 tokens when split.
    {
      throw std::invalid_argument("not a valid representation");
    }
  return tokens;
}

int absVal(int x)
{
  if (x < 0)
    {
      return -x;
    }
  return x;
}

std::vector<int> factors(int x)
{
  std::vector<int> factors;
  if (x != 1)
    {
      factors.push_back(x);
    }
  for (int i = 2; i <= sqrt(static_cast<double>(x)); i++) {
    if (x % i == 0) {
      factors.push_back(i);
      if (x/i != x)
        {
          factors.push_back(x/i);
        }
    }
  }
  return factors;
}

RationalNumber::RationalNumber() {
  setNumerator(0);
  setDenominator(1);
}

RationalNumber::RationalNumber(int pN)
{
  setNumerator(pN);
  setDenominator(1);
  simplify();
}

RationalNumber::RationalNumber(std::string pRepr)
{
  // valid inputs are: "x" (x/1), "x, y", and "x/y"
  int i;
  i = std::stoi(pRepr);
  if (std::to_string(i) == pRepr)
    {
      setNumerator(i);
      setDenominator(1);
      simplify();
      return;
    }
  std::vector<std::string> tokens;
  try
    {
      tokens = parseDelimited(pRepr, '/');
    }
  catch (std::invalid_argument)
    {
      tokens = parseDelimited(pRepr, ',');
    }
  setNumerator(std::stoi(tokens[0]));
  setDenominator(std::stoi(tokens[1]));
  simplify();
}

RationalNumber::RationalNumber(const RationalNumber& r)
{
  setNumerator(r.getNumerator());
  setDenominator(r.getDenominator());
  simplify();
}

RationalNumber::RationalNumber(int pN, int pD)
{
  setNumerator(pN);
  setDenominator(pD);
  simplify();
}

void RationalNumber::swap(const RationalNumber& r) throw()
{
  setNumerator(r.getNumerator());
  setDenominator(r.getDenominator());
}

int RationalNumber::getNumerator() const
{
  return mN;
}

int RationalNumber::getDenominator() const
{
  return mD;
}

void RationalNumber::setNumerator(int pN)
{
  mN = pN;
}

void RationalNumber::setDenominator(int pD)
{
  if (pD == 0)
    {
      throw std::invalid_argument("divide by zero");
    }
  mD = pD;
}

void RationalNumber::simplify()
{
  // reduce fraction and normalize sign to numerator
  int tempN = getNumerator();
  int tempD = getDenominator();
  int small, temp;
  std::vector<int> fs;

  if (tempN < 0 && tempD < 0)
    {
      tempN = absVal(tempN);
      tempD = absVal(tempD);
    }
  else if (tempD < 0)
    {
      tempN = -absVal(tempN);
      tempD = absVal(tempD);
    }

  if (tempN == tempD)
    {
      setNumerator(1);
      setDenominator(1);
      return;
    }
  else if (tempN == -tempD)
    {
      setNumerator(-1);
      setDenominator(1);
      return;
    }
  else if (tempN == 0)
    {
      setDenominator(1);
      return;
    }


  if (absVal(tempN) < absVal(tempD))
    {
      small = absVal(tempN);
    }
  else
    {
      small = absVal(tempD);
    }

  fs = factors(small);
  for (unsigned int i = 0; i < fs.size(); i++)
    {
      temp = fs[i];
      while (tempN % temp == 0 && tempD % temp == 0)
        {
          tempN /= temp;
          tempD /= temp;
        }
    }
  setNumerator(tempN);
  setDenominator(tempD);
}

RationalNumber& RationalNumber::operator=(const RationalNumber& r)
{
  swap(r);
  return *this;
}

RationalNumber RationalNumber::operator+(const RationalNumber& r) const
{
  return {mN*r.getDenominator() + r.getNumerator()*mD, mD*r.getDenominator()};
}

RationalNumber RationalNumber::operator-(const RationalNumber& r) const
{
  return {mN*r.getDenominator() - r.getNumerator()*mD, mD*r.getDenominator()};
}

RationalNumber RationalNumber::operator*(const RationalNumber& r) const
{
  return {mN*r.getNumerator(), mD*r.getDenominator()};
}

RationalNumber RationalNumber::operator/(const RationalNumber& r) const
{
  return {mN*r.getDenominator(), mD*r.getNumerator()};
}

bool RationalNumber::operator==(const RationalNumber& r) const
{
  return (mN == r.getNumerator() && mD == r.getDenominator());
}

bool RationalNumber::operator!=(const RationalNumber& r) const
{
  return !(mN == r.getNumerator() && mD == r.getDenominator());
}

bool RationalNumber::operator<=(const RationalNumber& r) const
{
  double left, right;
  left = mN / mD;
  right = r.getNumerator() / r.getDenominator();
  return left <= right;
}

bool RationalNumber::operator<(const RationalNumber& r) const
{
  return !(*this >= r);
}

bool RationalNumber::operator>=(const RationalNumber& r) const
{
  return (r <= *this);
}

bool RationalNumber::operator>(const RationalNumber& r) const
{
  return (r < *this);
}

std::string RationalNumber::repr()
{
  // Return a string representation: x/y.
  // Repr will be valid input to parse.
  if (getDenominator() == 1)
    {
      return std::to_string(getNumerator());
    }
  return std::to_string(getNumerator()) + "/" + std::to_string(getDenominator());
}
