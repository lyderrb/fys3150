#include <cassert>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <unittest++/UnitTest++.h>


#include "jacobiMethod.h"

using namespace std;

TEST (JacobiMethod_threeByThreeMatrix) {
  // init a test matrix
  int n = 3;
  double** A = new double*[n];
  for(int i=0; i<n; i++){
    A[i] = new double[n];
  }
  /* setting a "random" symetric matrix
     A =
     
     1   2   3
     2   4   6
     3   6   3
     
     lambda = 4 \pm sqrt(46) and lambda = 0
  */
  A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
  A[1][0] = 2; A[1][1] = 4; A[1][2] = 6;
  A[2][0] = 3; A[2][1] = 6; A[2][2] = 3;

  double * lambda_exact = new double[n];
  lambda_exact[0] = 0.0; 
  lambda_exact[1] = 4 + sqrt(46);
  lambda_exact[2] = 4 - sqrt(46);
      
  double* lambda = new double[n];  // array for computed lambdas
  double eps = 1e-14;             
  jacobiMethod(A, n, lambda, eps); // fill lambda with solution


  // test that values are correct
  // we don't know the order of the computed lambdas
  // so some clever (or not so clever) boolean expressions are needed
  bool s1, s2, s3;
  s1 = s2 = s3 = false;
  for(int i = 0; i < n; i++){
      s1 = s1 or ( abs( lambda[i] - lambda_exact[0]) < eps);
      s2 = s2 or ( abs( lambda[i] - lambda_exact[1]) < eps);
      s3 = s3 or ( abs( lambda[i] - lambda_exact[3]) < eps);
  }
  // asserting one by one for added clarity
  CHECK(s1);
  CHECK(s2);
  CHECK(s3);
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}

/* Result of running the unitTest.x executable:
   
bendik@Samseth project2 (unitTest-std)* $ ./unitTest.x 
Success: 1 tests passed.
Test time: 0.00 seconds.
*/