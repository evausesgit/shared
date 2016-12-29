#include <iostream>
#include <sstream>
#include <assert.h>
#include <algorithm>
template<class T, int N>
bool isSorted(T array[N], T begin, T end)
{
  for(int i = begin; i < end; ++i)
  {
    if(array[i] > array[i+1])
      return false;
  }

  return true;
}

static int nb_call_merge = 0;

template<class T, int N>
void merge(T array[N], T aux[N], const int lo, const int mid, const int hi)
{
  ++nb_call_merge;
  //std::cout << "merge lo " << lo << " mid " << mid << " hi " << hi << std::endl;
  bool res1 = isSorted<int, N>(array, lo, mid);
  bool res2 = isSorted<int, N>(array, mid+1, hi);
  assert(res1);
  assert(res2);
  for(int k = lo; k <= hi; ++k)
    aux[k] = array[k];
  int i = lo;
  int j = mid+1;
  for(int k = lo; k <= hi; ++k)
  {
    if     (i>mid)           array[k] = aux[j++];
    else if(j>hi)            array[k] = aux[i++];
    else if(aux[j] < aux[i]) array[k] = aux[j++];
    else                     array[k] = aux[i++];
  }
  bool res3 = isSorted<int, N>(array, lo, hi); 
  assert(res3);
}

template<class T, int N>
void sort(T array[N], T aux[N], const int lo, const int hi)
{
  if(hi <= lo) return;
  int mid = lo + (hi - lo)/2;
  std::cout << "sort lo " << lo  << " mid " << mid << " hi " << hi  << std::endl;
  sort <int, N>(array, aux, lo,      mid);
  sort <int, N>(array, aux, mid+1,   hi);
  merge<int, N>(array, aux, lo, mid, hi);
  if(nb_call_merge <= 7)
  {
    std::stringstream oss;
    oss << "merge("<<lo << ", " << mid << ", " << hi << "): ";
    for(int i=0; i<N; ++i)
      oss << array[i] << " ";
    std::cout << oss.str() << std::endl;
  }
}

template<class T, int N>
void sort(T array[N])
{
  T aux[N];

  sort<int, N>(array, aux, 0, N-1);

}
template<class T, int N>
void sort_bottom_up(T array[N])
{
  T aux[N];

  for(int sz = 1; sz < N; sz = sz +sz )
    for(int lo = 0; lo < N-sz; lo += sz+sz)
    {
      merge<int, N>(array, aux, lo, lo+sz-1, std::min(lo+sz+sz-1, N-1));
      if(nb_call_merge == 7)
      {
        std::stringstream oss;
        for(int i=0; i<N; ++i)
          oss << array[i] << " ";
        std::cout << "=============" << oss.str() << std::endl;
      }
    }
}

int main()
{
  const int N = 12;
  int array[N] = {66,84,39,34,53,23,17,47,41,25,57,22};
  sort<int, N>(array);
 
  // const int N = 10;
  // int array[N] = {79,45,66,74,72,32,34,88,37,50};
  // sort_bottom_up<int, N>(array);

  return 0;
}
