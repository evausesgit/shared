#include <stdio.h>
#include <sstream>
#include <iostream>

template<class T>
bool less(T a, T b)
{
  return a<b;
}

template<class T, int N>
void exchange(T array[N], int i, int j)
{
  T tmp = array[j];
  array[j] = array[i];
  array[i] = tmp;
}

template<class T, int N>
int partition(T array[N], int lo, int hi)
{
  int i = lo, j = hi+1;

  while(true)
  {
    //find item on the left to swap
    while(less<T>(array[++i], array[lo]))
      if(i == hi) break;

    //find item on the right to swap
    while(less<T>(array[lo], array[--j]))
      if(j == lo) break;
    
    //check if pointer cross
    if(i >= j) break;

    exchange<T, N>(array, i, j);
         
  }
  //swap with partitionning item
  exchange<T, N>(array, lo, j);
  //return index of item now known to be in place
  return j;
}

template<class T, int N>
void sort(T array[N], int lo, int hi)
{

  if (hi<=lo) return;

  int j = partition<T, N>(array, lo, hi);

  std::stringstream oss;
  for(int i=0; i<N; ++i)
    oss << array[i] << " ";
  std::cout << "=============" << oss.str() << std::endl;

  sort<T, N>(array, lo, j-1);
  sort<T, N>(array, j+1,hi);

}

template<class T, int N>
void sort(T array[N])
{
  //should shuffle
  sort<T, N>(array, 0, N-1);
}

int main()
{
  const int N = 12;
  int array[N] = {59,20,70,67,33,99,89,26,16,61,65,22};

  sort<int, N>(array);  
  std::stringstream oss;
  for(int i=0; i<N; ++i)
    oss << array[i] << " ";
  std::cout << "=============" << oss.str() << std::endl;

  return 0;

}
