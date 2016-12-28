#include <pthread.h>
#include <sys/time.h>
#include <iostream>
#include <cstring>
#include <assert.h>
#include <stdint.h>
#include <iomanip>

//sse include
#include <emmintrin.h>
#include <nmmintrin.h>

#include <boost/foreach.hpp>

#define N 8000

class sse
{
 public:
  sse() {}
  virtual ~sse() {}

  static void sum_array_char_slow(char* a, char* b, char* c);
  static void sum_array_char(char* a, char* b, char* c);

  static void sum_array_double_slow(double*a,double*b,double*c);
  static void sum_array_double(double*a,double*b,double*c);

  static void sum_float_and_array_float_slow(float*a,float*b,float);
  static void sum_float_and_array_float(float*a,float*b,float);

  static void big_sum_array_float_slow(float*a, float*b,float& x);
  static void big_sum_array_float(float*a, float*b,float& x);

 private:
};

//SSE2 intrinsics (unaligned load/store)
void sse::sum_array_char_slow(char* a, char* b, char* c)
{
  //Problem: vectorize the following code with MMX and SSE
  for (int i = 0; i < N; i++)
    a[i] = b[i] + c[i];
}
//SSE2 intrinsics (unaligned load/store)
void sse::sum_array_char(char* a, char* b, char* c)
{
  //Problem: vectorize the following code with MMX and SSE
  //  for (int i = 0; i < N; i++)
  //  a[i] = b[i] + c[i];

  __m128i *av, *bv, *cv;
  av = (__m128i*)a;
  bv = (__m128i*)b;
  cv = (__m128i*)c;
  for (int i = 0; i < N/16; i++)
  { 
    __m128i br = _mm_loadu_si128(&bv[i]);
    __m128i cr = _mm_loadu_si128(&cv[i]);
    __m128i ar = _mm_add_epi8(br, cr);
    _mm_storeu_si128(&av[i], ar);
  }
}

void sse::sum_array_double_slow(double*a,double*b,double*c)
{
  //Problem: vectorize the following code with SSE
  for (int i = 0; i < N; i++)
    a[i] = b[i] + c[i];

}

//SSE/SSE2 technology with 128-bit XMM registers (aligned load/store):
//SSE2 intrinsics (aligned load/store):

void sse::sum_array_double(double*a,double*b,double*c)
{
  __m128d *av, *bv, *cv;
  av = (__m128d*)a; // assume 16-byte aligned
  bv = (__m128d*)b; // assume 16-byte aligned
  cv = (__m128d*)c; // assume 16-byte aligned
  for (int i = 0; i < N/2; i++)
    av[i] = _mm_add_pd(bv[i], cv[i]);
}

void test_char()
{
  struct timeval t0, t1, t2;
  char a[N];
  char b[N];
  char c[N];
  memset(a, 'a', sizeof(a));
  memset(b, ' ', sizeof(b));
  memset(c, ' ', sizeof(c));
  gettimeofday(&t1, NULL);

  sse::sum_array_char_slow(a, b, c);
  
  gettimeofday(&t2, NULL);

  uint64_t d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "sum_array_char_slow d = " << d << " usec" << std::endl;

  gettimeofday(&t1, NULL);

  sse::sum_array_char(a, b, c);
  
  gettimeofday(&t2, NULL);

  d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "sum_array_char_fast d = " << d << " usec" << std::endl;

  for (int i = 0; i < N ; ++i) {
    assert(a[i] == '@');
    //    std::cout << "i=" << i <<" a[i]=" << a[i] << std::endl;
  }
}

void test_double()
{
  struct timeval t0, t1, t2;
  double a[N];
  double b[N];
  double c[N];
  memset(a, 0, sizeof(a));

  BOOST_FOREACH( double& f, b )
  {
    f = 1;//rand() % 100;
    //std::cout << f << std::endl;
  }
  BOOST_FOREACH( double& f, c )
  {
    f = 2;//rand() % 100;
    //std::cout << f << std::endl;
  }

  //  memset(b, 0, sizeof(b));
  //  memset(c, 0, sizeof(c));
  gettimeofday(&t1, NULL);

  sse::sum_array_double_slow(a, b, c);
  
  gettimeofday(&t2, NULL);

  uint64_t d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "sum_array_double_slow d = " << d << " usec" << std::endl;

  gettimeofday(&t1, NULL);

  sse::sum_array_double(a, b, c);
  
  gettimeofday(&t2, NULL);

  d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "sum_array_double_fast d = " << d << " usec" << std::endl;

  for (int i = 0; i < N ; ++i) {
    assert(a[i] == 3);
    //std::cout << "i=" << i <<" a[i]=" << a[i] << std::endl;
  }
}
void sse::sum_float_and_array_float_slow(float*a,float*b,float x)
{
  for(int i = 0; i < N; ++i)
  {
    a[i] = b[i] + x;
  }
}
//SSE2 intrinsics (aligned load/store):
void sse::sum_float_and_array_float(float*a,float*b,float x)
{

  __m128 *av, *bv, xr;
  av = (__m128*)a; // assume 16-byte aligned
  bv = (__m128*)b; // assume 16-byte aligned
  xr = _mm_set1_ps(x);
  for (int i = 0; i < N/4; i++)
    av[i] = _mm_add_ps(bv[i], xr);
}

void test_sum_float_arrayfloat()
{
  struct timeval t0, t1, t2;
  float a[N];
  float b[N];
  float c = 1.5;
  memset(a, 0, sizeof(a));

  BOOST_FOREACH( float& f, b )
  {
    f = 1;//rand() % 100;
    //std::cout << f << std::endl;
  }

  //  memset(b, 0, sizeof(b));
  //  memset(c, 0, sizeof(c));
  gettimeofday(&t1, NULL);

  sse::sum_float_and_array_float_slow(a, b, c);
  
  gettimeofday(&t2, NULL);

  uint64_t d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "sum_float_and_array_float_slow d = " << d << " usec" << std::endl;

  gettimeofday(&t1, NULL);

  memset(a, 0, sizeof(a));
  sse::sum_float_and_array_float(a, b, c);
  
  gettimeofday(&t2, NULL);

  d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "sum_float_and_array_float d = " << d << " usec" << std::endl;

  for (int i = 0; i < N ; ++i) {
    assert(a[i] == 2.5);
    //std::cout << "i=" << i <<" a[i]=" << a[i] << std::endl;
  }

}

void sse::big_sum_array_float_slow(float*a, float*b,float& x)
{
  for (int i = 0; i < N; i++)
    x = x + a[i]*b[i];
}
//SSE2 intrinsics (aligned load/store):
void sse::big_sum_array_float(float*a, float*b,float& x)
{
  float xx[4];
  __m128 *av = (__m128*)a; // assume 16-byte aligned
  __m128 *bv = (__m128*)b; // assume 16-byte aligned
  __m128 xv = _mm_setzero_ps();
  for (int i = 0; i < N/4; i++)
    xv = _mm_add_ps(xv, _mm_mul_ps(av[i], bv[i]));
  _mm_store_ps(xx, xv);
  x = xx[0] + xx[1] + xx[2] + xx[3];
  // or instead of the two lines above we can use a horizontal add:
  xv = _mm_hadd_ps(xv, xv);
  xv = _mm_hadd_ps(xv, xv);
  _mm_store_ps(xx, xv);
  x = xx[0];
}

void test_big_sum_float_array()
{
  struct timeval t0, t1, t2;
  float a[N];
  float b[N];
  float c = 0;

  BOOST_FOREACH( float& f, a )
  {
    f = 2;//rand() % 100;
    //std::cout << f << std::endl;
  }
  BOOST_FOREACH( float& f, b )
  {
    f = 1;//rand() % 100;
    //std::cout << f << std::endl;
  }

  gettimeofday(&t1, NULL);

  sse::big_sum_array_float_slow(a, b, c);
  
  assert(c == N*2);
  gettimeofday(&t2, NULL);

  uint64_t d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "big_sum_array_float_slow d = " << d << " usec" << std::endl;

  gettimeofday(&t1, NULL);

  c = 0;
  sse::big_sum_array_float(a, b, c);
  
  gettimeofday(&t2, NULL);

  d = (t2.tv_sec - t1.tv_sec) * 1000 * 1000 + t2.tv_usec - t1.tv_usec;
  std::cout << std::setw(30) << "big_sum_array_float d = " << d << " usec" << std::endl;

  std::cout << " c = " << c << std::endl;
  assert(c == N*2);
  
}

int main()
{
 
  //  test_char();
  // test_double();
  //test_sum_float_arrayfloat();
  test_big_sum_float_array();
  cpu_set_t m;

  CPU_ZERO(&m);

  CPU_SET(1, &m);

  sched_setaffinity(0, sizeof(cpu_set_t), &m); 

  struct sched_param param;

  bzero(&param, sizeof(param));
  int priority = 99;
  param.sched_priority = priority;

  int res = pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
  std::cout <<"set priority real time " << (!res ? "OK" : "NOK") << std::endl;

  //test_char();
  //test_double();
  //  test_sum_float_arrayfloat();
  test_big_sum_float_array();
  return 0;

}
