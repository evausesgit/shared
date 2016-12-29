#include <iostream>
#include <sstream>
#include <cstdlib>
//You are given a 2D matrix, a, of dimension MxN and a positive integer R. You have to rotate the matrix R times and print the resultant matrix. Rotation should be in anti-clockwise direction.
//
//Rotation of a 4x5 matrix is represented by the following figure. Note that in one rotation, you have to shift elements by one step only (refer sample tests for more clarity).
//
//matrix-rotation
//
//It is guaranteed that the minimum of M and N will be even.
//
//Input Format
//First line contains three space separated integers, M, N and R, where M is the number of rows, N is number of columns in matrix, and R is the number of times the matrix has to be rotated.
//Then M lines follow, where each line contains N space separated positive integers. These M lines represent the matrix.
//
//Constraints
//2 <= M, N <= 300
//1 <= R <= 109
//min(M, N) % 2 == 0
//1 <= aij <= 108, where i ∈ [1..M] & j ∈ [1..N]
//
//Output Format
//Print the rotated matrix.
//
//=====> you can test with Sample Input #00
//
//4 4 1
//1 2 3 4
//5 6 7 8
//9 10 11 12
//13 14 15 16
//
//Sample Output #00
//
//2 3 4 8
//1 7 11 12
//5 6 10 16
//9 13 14 15


int M=0;//row     // i
int N=0;//column  // j

int** allocateMatrix(int M, int N)
{
  int** matrix = (int**)malloc(M*sizeof(int*));
  for(int j=0; j<N; ++j)
    matrix[j] = (int*)malloc(N*sizeof(int));
  return matrix;
}

void desallocateMatrix(int** matrix, int M)
{
  for(int j=0; j<M; ++j)
    free(matrix[j]);
  free(matrix);
}

int** rotation(int** matrix)
{
  int** r_matrix = allocateMatrix(M, N);

  for(int i=0; i<M; ++i)
  {
    for(int j=0; j<N; ++j)
    {
      if(i < j)
      {
        if(j+1 < N)
          r_matrix[i][j] = matrix[i][j+1];
        else if(i+1 < M)
          r_matrix[i][j] = matrix[i+1][j];
        else
          r_matrix[i][j] = matrix[i][j-1];
      }
      else if(i > j)
      {
        if(i-1 < M && i >=0)
          r_matrix[i][j] = matrix[i-1][j];
        else
          r_matrix[i][j] = matrix[i][j-1];
      }
      else // i==j
      {
        if((i+j) < std::min(M, N))
          r_matrix[i][j] = matrix[i][j+1];
        else
          r_matrix[i][j] = matrix[i][j-1];
      }
    }
  }

  return r_matrix;
}

void printMatrix(int** matrix)
{
  for(int i=0; i<M; ++i)
  {
    std::stringstream oss;
    for(int j=0; j<N; ++j)
    {
      oss << matrix[i][j] << " ";

    }
    std::cout << oss.str() << std::endl;
  }

}


int main()
{

  int R;

  std::cin >> M >> N >> R;

  int** matrix = allocateMatrix(M, N);

  for(int i=0; i<M; ++i)
  {
    for(int j=0; j<N; ++j)
    {
      int a;
      std::cin >> a;
      matrix[i][j] = a;
    }
  }

  int** r_matrix = rotation(matrix);

  printMatrix(r_matrix);    

  desallocateMatrix(matrix, M);
  desallocateMatrix(r_matrix, M);

}
