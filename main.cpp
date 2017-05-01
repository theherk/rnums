#include <iostream>
#include <iomanip>
#include "RationalNumber.h"

#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

void output(RationalNumber& r)
{
  std::cout << r.repr() << std::endl;
}

void compare(RationalNumber& r1, RationalNumber& r2)
{
  RationalNumber sum;
  RationalNumber difference;
  RationalNumber product;
  RationalNumber quotient;

  sum = r1 + r2;
  difference = r1 - r2;
  product = r1 * r2;
  quotient = r1 / r2;

  std::cout << r1.repr() << " + " << r2.repr() << " = " << sum.repr() << std::endl;
  std::cout << r1.repr() << " - " << r2.repr() << " = " << difference.repr() << std::endl;
  std::cout << r1.repr() << " * " << r2.repr() << " = " << product.repr() << std::endl;
  std::cout << r1.repr() << " / " << r2.repr() << " = " << quotient.repr() << std::endl;

  std::cout << std::boolalpha << r1.repr() << " <= " << r2.repr() << ": " << (r1 <= r2) << std::endl;
  std::cout << std::boolalpha << r1.repr() << " < " << r2.repr() << ": " << (r1 < r2) << std::endl;
  std::cout << std::boolalpha << r1.repr() << " >= " << r2.repr() << ": " << (r1 >= r2) << std::endl;
  std::cout << std::boolalpha << r1.repr() << " > " << r2.repr() << ": " << (r1 > r2) << std::endl;

}

void test()
{
  RationalNumber r1("2/5");
  RationalNumber r2("3/-5");
  compare(r1, r2);
}

void getInput(std::string& s)
{
  std::cin >> s;
}

void interactive()
{
  std::string s1;
  std::string s2;

  RationalNumber *r1;
  RationalNumber *r2;

  std::cout << "Enter a fraction: ";
  getInput(s1);
  try
    {
      r1 = new RationalNumber(s1);
    }
  catch (std::invalid_argument e)
    {
      std::cout << "error: " << e.what() << std::endl;
    }

  std::cout << "Enter another fraction: ";
  getInput(s2);
  try
    {
      r2 = new RationalNumber(s2);
    }
  catch (std::invalid_argument e)
    {
      std::cout << "error: " << e.what() << std::endl;
    }

  compare(*r1, *r2);
}

int main()
{
  // test();
  interactive();

  return 0;
}
