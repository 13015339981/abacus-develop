#ifndef HAMILT_H
#define HAMILT_H

#include "../module_base/global_function.h"
#include "../module_base/global_variable.h"
#include "../module_base/complexmatrix.h"

#if ((defined __CUDA) || (defined __ROCM))

#ifdef __CUDA
#include "hamilt_pw.cuh"
#else
#include "hamilt_pw_hip.h"
#endif
#endif

class Hamilt
{
	public:

    Hamilt();
    ~Hamilt();

	// be called by diagH_subspace
    void diagH_LAPACK(
		const int n,
		const int m,
		const ModuleBase::ComplexMatrix &hc, // Hamiltonian matrix
		const ModuleBase::ComplexMatrix &sc, // overlap matrix
		const int ldh,
		double *e, // output: eigenvalues
		ModuleBase::ComplexMatrix &hvec); // output: eigenvectors

#ifdef __CUDA
	cusolverDnHandle_t cusolver_handle; // cusolver handle

	// Use hpsi_cuda to do operations in diagH_subspace instead of hpsi.
	void diagH_subspace_cuda(
		const int ik,
		const int nstart,
		const int n_band,
		const double2* psi,
		double2* evc,
		double *en,
		double2 *d_ekb_c);

	// Use cusolver API to solve eigenvalue problems instead Lapack.
	void diagH_CUSOLVER(
		const int nstart,
		const int nbands,
		double2* hc,  // nstart * nstart
		double2* sc,  // nstart * nstart
		const int ldh, // nstart
		double *e,
		double2* hvec);
#endif

#ifdef __ROCM
	// rocsolver_handle rocsolver_handle;

	// Use hpsi_cuda to do operations in diagH_subspace instead of hpsi.
	void diagH_subspace_cuda(
		const int ik,
		const int nstart,
		const int n_band,
		const hipblasDoubleComplex* psi,
		hipblasDoubleComplex* evc,
		double *en,
		hipblasDoubleComplex *d_ekb_c);
#endif

private:

};
#endif
