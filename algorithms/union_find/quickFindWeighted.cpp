#include "quickFindWeighted.h"

int main()
{
  QuickFindWeighted qfw(10);

  qfw.unionUF(7,0); qfw.print();
  qfw.unionUF(2,9); qfw.print();
  qfw.unionUF(7,3); qfw.print();
  qfw.unionUF(3,6); qfw.print();
  qfw.unionUF(4,8); qfw.print();
  qfw.unionUF(2,8); qfw.print();
  qfw.unionUF(0,1); qfw.print();
  qfw.unionUF(7,2); qfw.print();
  qfw.unionUF(5,8); qfw.print();

  // qfw.unionUF(6,0);
  // qfw.print();
  // qfw.unionUF(2,1);
  // qfw.print();
  // qfw.unionUF(2,4);
  // qfw.print();
  // qfw.unionUF(4,5);
  // qfw.print();
  // qfw.unionUF(4,3);
  // qfw.print();
  // qfw.unionUF(8,9);
  // qfw.print();
  // qfw.unionUF(0,8);
  // qfw.print();
  // qfw.unionUF(7,2);
  // qfw.print();
  // qfw.unionUF(6,5); 


  // qfw.print();

  return 0;
}
