#include <stdio.h>
#include "MaxPrioritaryQueue.h"

int main()
{
  MaxPQ<int> pq(10);
  pq.insert(99);
  pq.insert(76);
  pq.insert(69);
  pq.insert(71);
  pq.insert(73);
  pq.insert(51);
  pq.insert(39);
  pq.insert(31);
  pq.insert(60);
  pq.insert(35);

  pq.delMax();
  pq.delMax();
  pq.delMax();
  // pq.insert(88); pq.insert(85); pq.insert(64); pq.insert(55); pq.insert(62); pq.insert(33); pq.insert(61); pq.insert(35); pq.insert(40); pq.insert(27);


  // pq.insert(39);
  // pq.insert(72);
  // pq.insert(46);

  pq.print();
  return 0;
}
