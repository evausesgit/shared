#include <math.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <utility>

float compute_b(float N, float T, float prev_N, float prev_T)
{
  return (log2(T) - log2(prev_T))/(log2(N) - log2(prev_N));
}

int main()
{
  std::vector<std::pair<int, float> > datas; //N,T

  std::string filename = "/home/oem/Work/algorithms/orderOfGrowthNew.txt";
  std::string line          = "";

  std::ifstream myfile (filename.c_str());
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::cout << line << '\n';

      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;

      std::vector<std::string> tokens(beg, end); // done!
      int N   = 0;
      float T = 0.0;
      int i   = 0;
      for(auto& s: tokens)
      {
        if(i==0)
          N = atoi(s.c_str());
        else
          T = atof(s.c_str());
        ++i;
      }
      //std::cout << N << " " << T << '\n';
      datas.push_back(std::pair<int, float>(N, T));
    }
    myfile.close();
  }

  std::vector<std::pair<int, float> >::iterator it = datas.begin();

  float sum_b = 0;
  int sum_N   = 0;
  float prev_N = 0;
  float prev_T = 0;
  while(it != datas.end())
  {
    std::pair<int, float> data = *it;
    float N = data.first;
    float T = data.second;
    if(prev_N > 0 && prev_T > 0)
    {
      float b = compute_b(N, T, prev_N, prev_T);
      sum_b += b;
      sum_N += 1;
      std::cout << "for N " << data.first << " T " << data.second << " b = " << b << std::endl;
    }
    prev_N = N;
    prev_T = T;
    ++it;
  }

  std::cout << "mean b " << sum_b/sum_N << std::endl;

}
