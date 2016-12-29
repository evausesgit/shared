#include <iostream>
#include <sstream>

template<class T, int N>
void exchange(T array[N], int i, int j)
{
  T tmp = array[j];
  array[j] = array[i];
  array[i] = tmp;
}

template<class T>
int compare(T a, T b)
{
  return (a<b ? -1 : (a>b ? 1 : 0));
}

template<class T, int N>
void sort(T array[N], int lo, int hi)
{
  if(hi<=lo) return;

  int lt = lo, gt = hi;

  T v = array[lo];

  int i = lo;

  while(i <= gt)
  {
    int comp = compare<T>(array[i], v);

    if      (comp < 0) exchange<T, N>(array, lt++, i++);
    else if (comp > 0) exchange<T, N>(array, i, gt--);
    else               i++;
  }
  std::stringstream oss;
  for(int i=0; i<N; ++i)
    oss << array[i] << " ";
  std::cout << "=============" << oss.str() << std::endl;
  sort<T, N>(array, lo, lt-1);
  sort<T, N>(array, gt+1, hi);

}

int  main()
{
  const int N = 10;
  int array[N] = {53,42,53,52,62,84,53,64,53,26};
 
  sort<int, N>(array, 0, N-1);

  std::stringstream oss;
  for(int i=0; i<N; ++i)
    oss << array[i] << " ";
  std::cout << "=============" << oss.str() << std::endl;
 return 0;
}
