#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <climits>
//Numeros, the Artist, had two lists and , such that was a permutation of . Numeros was very proud of these lists. Unfortunately, while transporting them from one exhibition to another, some numbers were left out of . Can you find the missing numbers?
//
//Notes
//
//    If a number occurs multiple times in the lists, you must ensure that the frequency of that number in both lists is the same. If that is not the case, then it is also a missing number.
//    You have to print all the missing numbers in ascending order.
//    Print each missing number once, even if it is missing multiple times.
//    The difference between maximum and minimum number in is less than or equal to .
//
//Input Format
//
//There will be four lines of input:
//
//- the size of the first list
//This is followed by space-separated integers that make up the first list.
//- the size of the second list
//This is followed by space-separated integers that make up the second list.
//
//Constraints
//
//Output Format
//
//Output the missing numbers in ascending order.
//Sample Input
//
//10
//203 204 205 206 207 208 203 204 205 206
//13
//203 204 204 205 206 207 205 208 203 206 205 206 204
//
//Sample Output
//
//204 205 206

#define FOR(a) for(int i=0; i<a; ++i)
int main()
{
  std::string inputFile = "/home/oem/Work/hackerrank/input.txt"; 
  std::ifstream file {inputFile};
  int n=0,m=0;
  int Xmin=INT_MAX, Xmax=0;

  std::map<int, int> N;

  std::cin >> n;
  //  file >> n;
  FOR(n)
  {
    int tmp;
    std::cin >> tmp;
    //    file >> tmp;
    if (tmp < 1 || tmp > 10000)
      return 0;

    std::map<int, int>::iterator it = N.find(tmp);
    if(it != N.end())
      N[tmp] = it->second+1;
    else
      N[tmp] = 1;
  }

  std::cin >> m;
  //  file >> m;
  FOR(m)
  {
    int tmp;
    std::cin >> tmp;
    //    file >> tmp;
    if (tmp < 1 || tmp > 10000)
      return 0;

    if(tmp>Xmax)
    {
      Xmax = tmp;
      //      std::cout << "new max " << Xmax << std::endl;
    }
    if(tmp<Xmin)
    {
      Xmin = tmp;
      //std::cout << "new min " << Xmin << std::endl;
    }

    std::map<int, int>::iterator it = N.find(tmp);
    if(it != N.end())
      N[tmp] = it->second-1;
    else
      N[tmp] = 1;
  }

  if((Xmax-Xmin) >100)
    return 0;

  std::map<int, int>::iterator it = N.begin();

  std::stringstream oss;

  while(it != N.end())
  {
    if(it->second != 0)
      oss << it->first << " ";
    ++it;
  }

  std::cout << oss.str() <<std::endl
;
  return 0;
}
