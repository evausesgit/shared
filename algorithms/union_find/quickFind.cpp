#include "quickFind.h"
int main()
{
  QuickFind qf(10);
  qf.print();
  
  qf.unionqf(0,5);
  qf.unionqf(3,0);
  qf.unionqf(6,0);
  qf.unionqf(9,0);
  qf.unionqf(8,4);
  qf.unionqf(7,9);

  qf.print();

  return 0;
}
