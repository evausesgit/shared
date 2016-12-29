#include "DoubleUtil.hpp"

int main(void)
{
  float value;
  std::cout << " enter a float " << std::endl;
  std::cin >> value;

  std::cout << sizeof(float) << std::endl;
  std::cout <<  "floatPrecision " << floatPrecision(value) << std::endl;
  std::cout <<  "floatEpsilon "   << floatEpsilon(value) << std::endl;
  return 0;
};
