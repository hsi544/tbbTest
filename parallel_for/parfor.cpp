#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/tick_count.h"

using namespace tbb;

void Foo(float &a)
{

    //a += 2;
    a = cos(a*a);

}

class ApplyFoo {
   float *const my_a;
public:
   void operator()(const blocked_range<size_t>&r) const {
      float *a = my_a;
      for(size_t i = r.begin(); i!= r.end(); i++)
         Foo(a[i]);
   }

   ApplyFoo(float a[]):my_a(a){}

};




void SerialApplyFoo(float a[], size_t n)
{

   for( size_t i= 0; i < n ; ++i) {

     Foo(a[i]);

   }

}


void ParallelApplyFoo(float a[], size_t n, int grainSize) {

   //parallel_for(blocked_range<size_t>(0, n, grainSize), ApplyFoo(a));
   parallel_for(blocked_range<size_t>(0, n), ApplyFoo(a), auto_partitioner());

}

int main(int argc, char *argv[])
{

   if(argc < 2) {
      std::cout << "usage ./test_parfor <grainsize>" << std::endl;
      return 1;
   }

   size_t sz = 1024*1024*512;
   int grainSize = atoi(argv[1]);

   std::vector<float> a(sz, 0.0f);

   for(int i = 0 ; i < a.size() ; i++) {

      a[i] = rand()/INT_MAX;
   }

   tick_count t0 = tick_count::now();

   //SerialApplyFoo(a.data(), a.size());
   ParallelApplyFoo(a.data(), a.size(), grainSize);

   tick_count t1 = tick_count::now();

   std::cout << "elapsed time: " << (t1-t0).seconds() << " sec" << std::endl;

   return 0;
}
