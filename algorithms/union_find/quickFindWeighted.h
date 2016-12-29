#include "quickFind.h"
#include "string.h"

class QuickFindWeighted : public QuickFind
{
 public:
 QuickFindWeighted(int N) : QuickFind(N)
  {
    size_ = new int[N];
    for(int i = 0; i < N; ++i)
      size_[i] = 1;
  }

  virtual ~QuickFindWeighted()
  {
    delete[] size_;
  }

  virtual void unionUF(int p, int q)
  {
    int i = id_[p];
    int j = id_[q];

    if(i == j) return;
    std::cout << "p="<<p << " q=" << q << std::endl;
    std::cout << "size(i)="<<size_[i] << " size(j)="<<size_[j] << std::endl;
    if(size_[i] < size_[j])
    {
      id_[i]    = j;
      size_[j] += size_[i];
    }
    else
    {
      id_[j]      = i;
      size_[i] += size_[j];
    }
        std::cout << "size(i)="<<size_[i] << " size(j)="<<size_[j] << std::endl;
  }

 protected:
  int* size_;
};
