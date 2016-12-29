#include <iostream>
#include <stdio.h>
#include <sstream>
class QuickFind
{
public:
  QuickFind(int N) : N_(N)
  {
    id_ = new int[N];
    std::cout << sizeof(id_)*N*sizeof(int) << " bytes" << std::endl;
    for(int i = 0; i < N; ++i)
    {
      id_[i] = i;
    } 
  }

  virtual ~QuickFind()
  {
    delete[] id_;
  }

  virtual bool connected(int p, int q)
  {
    return id_[p] == id_[q];
  }

  virtual void unionqf(int p, int q)
  {
    int pid = id_[p];
    int qid = id_[q];

    for(int i = 0; i < N_; i++)
    {
      if(id_[i] == pid)
        id_[i] = qid;
    }
  }

  virtual void print()
  {
    std::stringstream oss;
    for(int i = 0; i < N_; i++)
    {
      oss << id_[i] << " ";
    }
    std::cout << oss.str() << std::endl; 
  }

protected:
  int* id_;
  int  N_;
};

