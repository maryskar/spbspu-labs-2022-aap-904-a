#include "rowvalidation.h"
#include <cctype>

bool isSign(char c)
{
  return (c == '+' || c == '-');
}
bool isDigit(char c)
{
  return std::isdigit(c);
}
bool isEnd(char c)
{
  return (c == '\0');
}
bool isDot(char c)
{
  return (c == '.');
}
bool isE(char c)
{
  return (c == 'E');
}
bool finishedWithDigit(const char * data)
{
  return isDigit(*data) && isEnd(*(data + 1));
}
bool continueWithDigit(const char * data)
{
  return isDigit(*data) && (continueWithDigit(data + 1) || finishedWithDigit(data + 1));
}
bool continueWithSign(const char * data)
{
  return isSign(*data) && (continueWithSign(data + 1) || continueWithDigit(data + 1));
}
bool continueWithOrder(const char * data)
{
  return isE(*data) && (continueWithSign(data + 1) || continueWithDigit(data + 1));
}
bool continueWithMantisaPartOne(const char * data)
{
  return isDot(*data) && continueWithDigit(data + 1);
}
bool continueWithMantisaPartTwo(const char * data)
{
  return continueWithDigit(data) && isDot(*(data + 1)) && continueWithDigit(data + 2);
}
bool isMantisa(const char * data)
{
  return continueWithMantisaPartOne(data) || continueWithMantisaPartTwo(data) || continueWithDigit(data);
}
bool isFloat(const char * data)
{
  return ((isMantisa(data) && continueWithOrder(data + 1)) || (isSign(*data) && isMantisa(data + 1) && continueWithOrder(data + 2)));
}
