
//@HEADER
// ***************************************************
//
// HPCG: High Performance Conjugate Gradient Benchmark
//
// Contact:
// Michael A. Heroux ( maherou@sandia.gov)
// Jack Dongarra     (dongarra@eecs.utk.edu)
// Piotr Luszczek    (luszczek@eecs.utk.edu)
//
// ***************************************************
//@HEADER

/*!
 @file ComputeSPMV.cpp

 HPCG routine
 */

#include "ComputeSPMV.hpp"
#include "ComputeSPMV_ref.hpp"
#include "common.h"
#include "ComputeSPMV_FPGA.hpp"
// #define MAXNONZEROELEMENTS 27
#include <iostream>

using namespace std;
/*!
  Routine to compute sparse matrix vector product y = Ax where:
  Precondition: First call exchange_externals to get off-processor values of x

  This routine calls the reference SpMV implementation by default, but
  can be replaced by a custom, optimized routine suited for
  the target system.

  @param[in]  A the known system matrix
  @param[in]  x the known vector
  @param[out] y the On exit contains the result: Ax.

  @return returns 0 upon success and non-zero otherwise

  @see ComputeSPMV_ref
*/


int ComputeSPMV( const SparseMatrix & A, Vector & x, Vector & y) {

  // This line and the next two lines should be removed and your version of ComputeSPMV should be used.
  
  // FlattenMatrix(A,  27);
#ifndef FPGA
  A.isSpmvOptimized = true;
  //ComputeSPMV_FPGA(A.nonzerosInRow,A.flat_mtxIndL,A.flat_matrixValues,x.values,y.values,A.localNumberOfRows);
  return ComputeSPMV_FPGA(A, x, y);
#else
  A.isSpmvOptimized = false;
  return ComputeSPMV_ref(A, x, y);
#endif

}
