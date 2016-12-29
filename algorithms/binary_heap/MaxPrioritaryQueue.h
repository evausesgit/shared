#include <sstream>
#include <iostream>
template<class T>
class MaxPQ
{
 public:
 MaxPQ(int capacity) : N(0)
  {
    pq = new T[capacity+1];
  }

  virtual ~MaxPQ() {}
  void print()
  {
    std::stringstream oss;
    for(int i =1; i < N+1; i++)
      oss << pq[i] << " ";

    std::cout << oss.str() << std::endl;
  }
  bool isEmpty() { return  N == 0; }

  void insert(T key)
  {
    pq[++N] = key; 
    swim(N);
  }

  void swim(T k)
  {
    while(k > 1 && less(k/2, k))
    {
      exchange(k, k/2);
      k = k/2;
    }
  }

  bool less(T i, T j) { return pq[i] < pq[j]; }

  void exchange(T i, T j)
  {
    T tmp = pq[i];
    pq[i] = pq[j];
    pq[j] = tmp; 
  }

  void sink(T k)
  {
    while(2*k < N)
    {
      T j = 2*k;

      if (j < N && less(j, j+1)) j++;

      if(!less(k, j))            break;

      exchange(k, j);
      k = j;
    }
  }

  T delMax()
  {
    T max = pq[1];
    exchange(1, N--);
    sink(1);
    pq[N+1] = 0;
    return max;
  }
  int N;
  T* pq;
    
 private:

};
