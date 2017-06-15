#include <math.h>
#include <stdio.h>
#include <pycuda-complex.hpp>
#include<curand.h>
#include<curand_kernel.h>

extern "C" {

// ##########################################
// Global variables

#define pi 3.14159265359
#define MPion 139.57018
#define MKaon 493.667
#define MKst_1_1410 1414.
#define GKst_1_1410 232.
#define MKst_1_1680 1717.
#define GKst_1_1680 322.
#define MBs 5366.77

__device__ double DCP_prod;

__device__ double MEta = 547.;
__device__ double sAdler_Stheo = 0.236;
__device__ double B0_Stheo = 0.411;
__device__ double B1_Stheo = 0.162;
__device__ double alpha_Stheo = 1.15;
__device__ double s0_Stheo = 1.21;
__device__ double phi0_Stheo = -0.19;
__device__ double phi1_Stheo = 5.03;
__device__ double a_Stheo = -5.2;
__device__ double b_Stheo = 7.6;
__device__ double c_Stheo = -1.73;
__device__ double sqrtsr1_Stheo = 1.401;
__device__ double sqrtsr2_Stheo = 1.817;
__device__ double e1_Stheo = 1.;
__device__ double e2_Stheo = 0.184;
__device__ double G1_Stheo = 0.497;
__device__ double G2_Stheo = 0.28;

__device__ double s_Kpi_palano = (139.57018*139.57018+493.667*493.667)/1000./1000.;
__device__ double s_A_palano = 0.87753*(139.57018*139.57018+493.667*493.667)/1000./1000.;
__device__ double s_a_palano = 1.7991;
__device__ double g_1_a_palano = 0.3139;
__device__ double g_2_a_palano = -0.00775;
__device__ double s_b_palano = 8.3627;
__device__ double g_1_b_palano = 1.1804;
__device__ double g_2_b_palano = -0.22335;
__device__ double C_11_0_palano = -0.1553;
__device__ double C_11_1_palano = 0.0909;
__device__ double C_11_2_palano = 0.8618;
__device__ double C_11_3_palano = 0.0629;
__device__ double C_12_0_palano = 0.0738;
__device__ double C_12_1_palano = 0.3866;
__device__ double C_12_2_palano = 1.2195;
__device__ double C_12_3_palano = 0.8390;
__device__ double C_22_0_palano = -0.0036;
__device__ double C_22_1_palano = 0.2590;
__device__ double C_22_2_palano = 1.6950;
__device__ double C_22_3_palano = 2.2300;
__device__ double A_1_0_palano = 1.;
__device__ double A_1_1_palano = 0.00491636810678;
__device__ double A_1_2_palano = 2.12489529189;
__device__ double A_1_3_palano = 0.56004179484;
__device__ double A_1_4_palano = 0.;
__device__ double A_2_0_palano = -4.20943829183;
__device__ double A_2_1_palano = -1.2110147687;
__device__ double A_2_2_palano = 2.28474898994;
__device__ double A_2_3_palano = 5.93332582489;
__device__ double A_2_4_palano = 0.;


// ##########################################
// Auxiliar elements

__device__ double fjjphhpindexdict[3][3][5][5];
__device__ double ghhpindexdict[5][5];
__device__ double reNj1j2hdict[3][3][5];
__device__ double imNj1j2hdict[3][3][5];
__device__ double spl_knot_vector[2][2][6];

__device__ pycuda::complex<double> Nj1j2hdict(int j1, int j2, int h) {

   return pycuda::complex<double>(reNj1j2hdict[j1][j2][h],imNj1j2hdict[j1][j2][h]);

 }


// ##########################################
// Initializer

__global__ void initialize() {

   fjjphhpindexdict[0][0][0][0] = 1;
   fjjphhpindexdict[0][1][0][0] = 2;
   fjjphhpindexdict[0][1][0][1] = 3;
   fjjphhpindexdict[0][1][0][2] = 3;
   fjjphhpindexdict[0][2][0][0] = 4;
   fjjphhpindexdict[0][2][0][1] = 5;
   fjjphhpindexdict[0][2][0][2] = 5;
   fjjphhpindexdict[1][0][0][0] = 2;
   fjjphhpindexdict[1][1][0][0] = 6;
   fjjphhpindexdict[1][1][0][1] = 5;
   fjjphhpindexdict[1][1][0][2] = 5;
   fjjphhpindexdict[1][2][0][0] = 7;
   fjjphhpindexdict[1][2][0][1] = 8;
   fjjphhpindexdict[1][2][0][2] = 8;
   fjjphhpindexdict[1][0][1][0] = 3;
   fjjphhpindexdict[1][0][2][0] = 3;
   fjjphhpindexdict[1][1][1][0] = 5;
   fjjphhpindexdict[1][1][2][0] = 5;
   fjjphhpindexdict[1][1][1][1] = 9;
   fjjphhpindexdict[1][1][1][2] = 9;
   fjjphhpindexdict[1][1][2][1] = 9;
   fjjphhpindexdict[1][1][2][2] = 9;
   fjjphhpindexdict[1][2][1][0] = 10;
   fjjphhpindexdict[1][2][2][0] = 10;
   fjjphhpindexdict[1][2][1][1] = 11;
   fjjphhpindexdict[1][2][1][2] = 11;
   fjjphhpindexdict[1][2][2][1] = 11;
   fjjphhpindexdict[1][2][2][2] = 11;
   fjjphhpindexdict[2][0][0][0] = 4;
   fjjphhpindexdict[2][1][0][0] = 7;
   fjjphhpindexdict[2][1][0][1] = 10;
   fjjphhpindexdict[2][1][0][2] = 10;
   fjjphhpindexdict[2][2][0][0] = 12;
   fjjphhpindexdict[2][2][0][1] = 13;
   fjjphhpindexdict[2][2][0][2] = 13;
   fjjphhpindexdict[2][0][1][0] = 5;
   fjjphhpindexdict[2][0][2][0] = 5;
   fjjphhpindexdict[2][1][1][0] = 8;
   fjjphhpindexdict[2][1][2][0] = 8;
   fjjphhpindexdict[2][1][1][1] = 11;
   fjjphhpindexdict[2][1][1][2] = 11;
   fjjphhpindexdict[2][1][2][1] = 11;
   fjjphhpindexdict[2][1][2][2] = 11;
   fjjphhpindexdict[2][2][1][0] = 13;
   fjjphhpindexdict[2][2][2][0] = 13;
   fjjphhpindexdict[2][2][1][1] = 14;
   fjjphhpindexdict[2][2][1][2] = 14;
   fjjphhpindexdict[2][2][2][1] = 14;
   fjjphhpindexdict[2][2][2][2] = 14;
   fjjphhpindexdict[0][2][0][3] = 9;
   fjjphhpindexdict[0][2][0][4] = 9;
   fjjphhpindexdict[1][2][0][3] = 11;
   fjjphhpindexdict[1][2][0][4] = 11;
   fjjphhpindexdict[1][2][1][3] = 15;
   fjjphhpindexdict[1][2][1][4] = 15;
   fjjphhpindexdict[1][2][2][3] = 15;
   fjjphhpindexdict[1][2][2][4] = 15;
   fjjphhpindexdict[2][2][0][3] = 16;
   fjjphhpindexdict[2][2][0][4] = 16;
   fjjphhpindexdict[2][2][1][3] = 17;
   fjjphhpindexdict[2][2][1][4] = 17;
   fjjphhpindexdict[2][2][2][3] = 17;
   fjjphhpindexdict[2][2][2][4] = 17;
   fjjphhpindexdict[2][0][3][0] = 9;
   fjjphhpindexdict[2][0][4][0] = 9;
   fjjphhpindexdict[2][1][3][0] = 11;
   fjjphhpindexdict[2][1][4][0] = 11;
   fjjphhpindexdict[2][1][3][1] = 15;
   fjjphhpindexdict[2][1][3][2] = 15;
   fjjphhpindexdict[2][1][4][1] = 15;
   fjjphhpindexdict[2][1][4][2] = 15;
   fjjphhpindexdict[2][2][3][0] = 16;
   fjjphhpindexdict[2][2][4][0] = 16;
   fjjphhpindexdict[2][2][3][1] = 17;
   fjjphhpindexdict[2][2][3][2] = 17;
   fjjphhpindexdict[2][2][4][1] = 17;
   fjjphhpindexdict[2][2][4][2] = 17;
   fjjphhpindexdict[2][2][3][3] = 18;
   fjjphhpindexdict[2][2][3][4] = 18;
   fjjphhpindexdict[2][2][4][3] = 18;
   fjjphhpindexdict[2][2][4][4] = 18;

   ghhpindexdict[0][0] = 1;
   ghhpindexdict[0][1] = 2;
   ghhpindexdict[0][2] = 3;
   ghhpindexdict[1][0] = 2;
   ghhpindexdict[1][1] = 4;
   ghhpindexdict[1][2] = 5;
   ghhpindexdict[2][0] = 3;
   ghhpindexdict[2][1] = 5;
   ghhpindexdict[2][2] = 6;
   ghhpindexdict[0][3] = 7;
   ghhpindexdict[0][4] = 8;
   ghhpindexdict[1][3] = 9;
   ghhpindexdict[1][4] = 10;
   ghhpindexdict[2][3] = 11;
   ghhpindexdict[2][4] = 12;
   ghhpindexdict[3][0] = 7;
   ghhpindexdict[3][1] = 9;
   ghhpindexdict[3][2] = 11;
   ghhpindexdict[3][3] = 13;
   ghhpindexdict[3][4] = 14;
   ghhpindexdict[4][0] = 8;
   ghhpindexdict[4][1] = 10;
   ghhpindexdict[4][2] = 12;
   ghhpindexdict[4][3] = 14;
   ghhpindexdict[4][4] = 15;

   reNj1j2hdict[0][0][0] = pycuda::real(pycuda::complex<double>(1./(2.*sqrt(2.*pi)),0.));
   reNj1j2hdict[0][1][0] = pycuda::real(pycuda::complex<double>(-sqrt(3.)/(2.*sqrt(2.*pi)),0.));
   reNj1j2hdict[0][2][0] = pycuda::real(pycuda::complex<double>(sqrt(5.)/(4.*sqrt(2.*pi)),0.));
   reNj1j2hdict[1][0][0] = pycuda::real(pycuda::complex<double>(sqrt(3.)/(2.*sqrt(2.*pi)),0.));
   reNj1j2hdict[1][1][0] = pycuda::real(pycuda::complex<double>(-3./(2.*sqrt(2.*pi)),0.));
   reNj1j2hdict[1][1][1] = pycuda::real(pycuda::complex<double>(-3./(4.*sqrt(pi)),0.));
   reNj1j2hdict[1][1][2] = pycuda::real(pycuda::complex<double>(0.,-3./(4.*sqrt(pi))));
   reNj1j2hdict[1][2][0] = pycuda::real(pycuda::complex<double>(sqrt(15.)/(4.*sqrt(2.*pi)),0.));
   reNj1j2hdict[1][2][1] = pycuda::real(pycuda::complex<double>(3.*sqrt(5.)/(4.*sqrt(pi)),0.));
   reNj1j2hdict[1][2][2] = pycuda::real(pycuda::complex<double>(0.,3.*sqrt(5.)/(4.*sqrt(pi))));
   reNj1j2hdict[2][0][0] = pycuda::real(pycuda::complex<double>(sqrt(5.)/(4.*sqrt(2.*pi)),0.));
   reNj1j2hdict[2][1][0] = pycuda::real(pycuda::complex<double>(-sqrt(15.)/(4.*sqrt(2.*pi)),0.));
   reNj1j2hdict[2][1][1] = pycuda::real(pycuda::complex<double>(-3.*sqrt(5.)/(4.*sqrt(pi)),0.));
   reNj1j2hdict[2][1][2] = pycuda::real(pycuda::complex<double>(0.,-3.*sqrt(5.)/(4.*sqrt(pi))));
   reNj1j2hdict[2][2][0] = pycuda::real(pycuda::complex<double>(5./(8.*sqrt(2.*pi)),0.));
   reNj1j2hdict[2][2][1] = pycuda::real(pycuda::complex<double>(15./(4.*sqrt(pi)),0.));
   reNj1j2hdict[2][2][2] = pycuda::real(pycuda::complex<double>(0.,15./(4.*sqrt(pi))));
   reNj1j2hdict[2][2][3] = pycuda::real(pycuda::complex<double>(15./(16.*sqrt(pi)),0.));
   reNj1j2hdict[2][2][4] = pycuda::real(pycuda::complex<double>(0.,15./(16.*sqrt(pi))));
   imNj1j2hdict[0][0][0] = pycuda::imag(pycuda::complex<double>(1./(2.*sqrt(2.*pi)),0.));
   imNj1j2hdict[0][1][0] = pycuda::imag(pycuda::complex<double>(-sqrt(3.)/(2.*sqrt(2.*pi)),0.));
   imNj1j2hdict[0][2][0] = pycuda::imag(pycuda::complex<double>(sqrt(5.)/(4.*sqrt(2.*pi)),0.));
   imNj1j2hdict[1][0][0] = pycuda::imag(pycuda::complex<double>(sqrt(3.)/(2.*sqrt(2.*pi)),0.));
   imNj1j2hdict[1][1][0] = pycuda::imag(pycuda::complex<double>(-3./(2.*sqrt(2.*pi)),0.));
   imNj1j2hdict[1][1][1] = pycuda::imag(pycuda::complex<double>(-3./(4.*sqrt(pi)),0.));
   imNj1j2hdict[1][1][2] = pycuda::imag(pycuda::complex<double>(0.,-3./(4.*sqrt(pi))));
   imNj1j2hdict[1][2][0] = pycuda::imag(pycuda::complex<double>(sqrt(15.)/(4.*sqrt(2.*pi)),0.));
   imNj1j2hdict[1][2][1] = pycuda::imag(pycuda::complex<double>(3.*sqrt(5.)/(4.*sqrt(pi)),0.));
   imNj1j2hdict[1][2][2] = pycuda::imag(pycuda::complex<double>(0.,3.*sqrt(5.)/(4.*sqrt(pi))));
   imNj1j2hdict[2][0][0] = pycuda::imag(pycuda::complex<double>(sqrt(5.)/(4.*sqrt(2.*pi)),0.));
   imNj1j2hdict[2][1][0] = pycuda::imag(pycuda::complex<double>(-sqrt(15.)/(4.*sqrt(2.*pi)),0.));
   imNj1j2hdict[2][1][1] = pycuda::imag(pycuda::complex<double>(-3.*sqrt(5.)/(4.*sqrt(pi)),0.));
   imNj1j2hdict[2][1][2] = pycuda::imag(pycuda::complex<double>(0.,-3.*sqrt(5.)/(4.*sqrt(pi))));
   imNj1j2hdict[2][2][0] = pycuda::imag(pycuda::complex<double>(5./(8.*sqrt(2.*pi)),0.));
   imNj1j2hdict[2][2][1] = pycuda::imag(pycuda::complex<double>(15./(4.*sqrt(pi)),0.));
   imNj1j2hdict[2][2][2] = pycuda::imag(pycuda::complex<double>(0.,15./(4.*sqrt(pi))));
   imNj1j2hdict[2][2][3] = pycuda::imag(pycuda::complex<double>(15./(16.*sqrt(pi)),0.));
   imNj1j2hdict[2][2][4] = pycuda::imag(pycuda::complex<double>(0.,15./(16.*sqrt(pi))));

 }


// ##########################################
// Normalisation weights
 
__device__ int indexdictcpp[4050] = {0,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,
3,-1,-1,-1,-1,-1,-1,-1,-1,4,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,8,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,
11,-1,-1,-1,-1,-1,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,14,15,-1,-1,-1,-1,-1,-1,-1,-1,16,17,-1,-1,-1,-1,-1,-1,-1,-1,18,19,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,-1,-1,-1,-1,-1,-1,-1,-1,22,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,
25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,26,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,
29,-1,-1,-1,-1,-1,-1,-1,-1,30,31,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,32,33,-1,-1,-1,-1,-1,-1,-1,-1,34,35,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,36,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,38,39,-1,-1,-1,-1,-1,-1,-1,-1,40,
41,-1,-1,-1,-1,-1,-1,-1,-1,42,43,-1,-1,-1,-1,-1,-1,-1,-1,44,45,-1,-1,-1,-1,-1,-1,-1,-1,46,47,48,49,-1,-1,-1,-1,-1,-1,50,51,-1,-1,-1,-1,-1,-1,-1,-1,52,
53,-1,-1,-1,-1,-1,-1,-1,-1,54,55,-1,-1,-1,-1,-1,-1,-1,-1,56,57,-1,-1,-1,-1,-1,-1,-1,-1,58,59,-1,-1,-1,-1,-1,-1,-1,-1,60,61,-1,-1,-1,-1,-1,-1,-1,-1,62,
63,-1,-1,-1,-1,-1,-1,-1,-1,64,65,-1,-1,-1,-1,-1,-1,-1,-1,66,67,68,69,70,71,-1,-1,-1,-1,72,73,74,75,-1,-1,-1,-1,-1,-1,76,77,-1,-1,-1,-1,-1,-1,-1,-1,78,
79,80,81,-1,-1,-1,-1,-1,-1,82,83,84,85,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,
87,-1,-1,-1,-1,-1,-1,-1,-1,88,89,-1,-1,-1,-1,-1,-1,-1,-1,90,91,-1,-1,-1,-1,-1,-1,-1,-1,92,93,-1,-1,-1,-1,-1,-1,-1,-1,94,95,-1,-1,-1,-1,-1,-1,-1,-1,96,
97,-1,-1,-1,-1,-1,-1,-1,-1,98,99,-1,-1,-1,-1,-1,-1,-1,-1,100,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,103,-1,-1,-1,-1,-1,-1,-1,-1,104,
105,-1,-1,-1,-1,-1,-1,-1,-1,106,107,-1,-1,-1,-1,-1,-1,-1,-1,108,109,-1,-1,-1,-1,-1,-1,-1,-1,110,111,112,113,-1,-1,-1,-1,-1,-1,114,115,116,117,-1,-1,-1,-1,-1,-1,118,
119,-1,-1,-1,-1,-1,-1,-1,-1,120,121,122,123,-1,-1,-1,-1,-1,-1,124,125,-1,-1,-1,-1,-1,-1,-1,-1,126,127,-1,-1,-1,-1,-1,-1,-1,-1,128,129,-1,-1,-1,-1,-1,-1,-1,-1,130,
131,-1,-1,-1,-1,-1,-1,-1,-1,132,133,-1,-1,-1,-1,-1,-1,-1,-1,134,135,136,137,138,139,-1,-1,-1,-1,140,141,142,143,144,145,-1,-1,-1,-1,146,147,-1,-1,-1,-1,-1,-1,-1,-1,148,
149,150,151,152,153,-1,-1,-1,-1,154,155,156,157,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,158,
159,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,160,161,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,162,163,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,164,
165,-1,-1,-1,-1,-1,-1,-1,-1,166,167,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,168,169,-1,-1,-1,-1,-1,-1,-1,-1,170,171,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,172,173,-1,-1,-1,-1,-1,-1,-1,-1,174,175,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,176,177,-1,-1,-1,-1,-1,-1,-1,-1,178,
179,-1,-1,-1,-1,-1,-1,-1,-1,180,181,-1,-1,-1,-1,-1,-1,-1,-1,182,183,-1,-1,-1,-1,-1,-1,-1,-1,184,185,186,187,-1,-1,-1,-1,-1,-1,188,189,-1,-1,-1,-1,-1,-1,-1,-1,190,
191,-1,-1,-1,-1,-1,-1,-1,-1,192,193,194,195,-1,-1,-1,-1,-1,-1,196,197,-1,-1,-1,-1,-1,-1,-1,-1,198,199,-1,-1,-1,-1,-1,-1,-1,-1,200,201,-1,-1,-1,-1,-1,-1,-1,-1,202,
203,-1,-1,-1,-1,-1,-1,-1,-1,204,205,-1,-1,-1,-1,-1,-1,-1,-1,206,207,208,209,210,211,-1,-1,-1,-1,212,213,214,215,-1,-1,-1,-1,-1,-1,216,217,-1,-1,-1,-1,-1,-1,-1,-1,218,
219,220,221,222,223,-1,-1,-1,-1,224,225,226,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,
229,-1,-1,-1,-1,-1,-1,-1,-1,230,231,-1,-1,-1,-1,-1,-1,-1,-1,232,233,-1,-1,-1,-1,-1,-1,-1,-1,234,235,-1,-1,-1,-1,-1,-1,-1,-1,236,237,-1,-1,-1,-1,-1,-1,-1,-1,238,
239,-1,-1,-1,-1,-1,-1,-1,-1,240,241,-1,-1,-1,-1,-1,-1,-1,-1,242,243,-1,-1,-1,-1,-1,-1,-1,-1,244,245,-1,-1,-1,-1,-1,-1,-1,-1,246,247,-1,-1,-1,-1,-1,-1,-1,-1,248,
249,-1,-1,-1,-1,-1,-1,-1,-1,250,251,-1,-1,-1,-1,-1,-1,-1,-1,252,253,-1,-1,-1,-1,-1,-1,-1,-1,254,255,256,257,-1,-1,-1,-1,-1,-1,258,259,260,261,-1,-1,-1,-1,-1,-1,262,
263,-1,-1,-1,-1,-1,-1,-1,-1,264,265,266,267,-1,-1,-1,-1,-1,-1,268,269,270,271,-1,-1,-1,-1,-1,-1,272,273,-1,-1,-1,-1,-1,-1,-1,-1,274,275,-1,-1,-1,-1,-1,-1,-1,-1,276,
277,-1,-1,-1,-1,-1,-1,-1,-1,278,279,-1,-1,-1,-1,-1,-1,-1,-1,280,281,282,283,284,285,-1,-1,-1,-1,286,287,288,289,290,291,-1,-1,-1,-1,292,293,-1,-1,-1,-1,-1,-1,-1,-1,294,
295,296,297,298,299,-1,-1,-1,-1,300,301,302,303,304,305,-1,-1,-1,-1,306,307,-1,-1,-1,-1,-1,-1,-1,-1,308,309,-1,-1,-1,-1,-1,-1,-1,-1,310,311,-1,-1,-1,-1,-1,-1,-1,-1,312,
313,-1,-1,-1,-1,-1,-1,-1,-1,314,315,316,317,318,319,-1,-1,-1,-1,320,321,322,323,324,325,-1,-1,-1,-1,326,327,-1,-1,-1,-1,-1,-1,-1,-1,328,329,330,331,332,333,-1,-1,-1,-1,334,
335,336,337,338,339,340,341,-1,-1,342,343,-1,-1,-1,-1,-1,-1,-1,-1,344,345,-1,-1,-1,-1,-1,-1,-1,-1,346,347,-1,-1,-1,-1,-1,-1,-1,-1,348,349,-1,-1,-1,-1,-1,-1,-1,-1,350,
351,352,353,354,355,-1,-1,-1,-1,356,357,358,359,360,361,-1,-1,-1,-1,362,363,-1,-1,-1,-1,-1,-1,-1,-1,364,365,366,367,368,369,-1,-1,-1,-1,370,371,372,373,374,375,376,377,378,379};
 
__device__ int redindexcpp(int j1, int j2, int h, int j1p, int j2p, int hp, int part) {
   return indexdictcpp[part+2*hp+10*j2p+30*j1p+90*h+450*j2+1350*j1];
 }
 
__device__ double nw_comp_matrix[2][2][380];

__device__ double nw_comp(int year_opt,int trig_opt,int j1,int j2,int h,int j1p,int j2p,int hp,int part) {
   return nw_comp_matrix[year_opt][trig_opt][redindexcpp(j1,j2,h,j1p,j2p,hp,part)];
 }


// ##########################################
// Splines
 
__device__ double knots_wide[6] = {0.0,0.9,1.4,2.1,3.1,12.0}; 
__device__ double knots_narrow[6] = {0.0,0.9,1.4,2.0,3.1,12.0};
 
__device__ double a_2011_L0TIS_wide[5][4] = {{0.0,-0.00112621527248,1.58569721831,-0.819679115309},
{-0.695240812888,2.31634316102,-0.989268755348,0.134011986046},
{-0.968319206849,2.90151114808,-1.40724588896,0.233530351192},
{1.49093519128,-0.611709420676,0.265716286636,-0.0320192004899},
{0.480295052314,0.366329423485,-0.0497801147062,0.00190514374049}}; 
__device__ double a_2012_L0TIS_wide[5][4] = {{0.0,-0.00108246180814,2.40916212056,-1.38444396395},
{-1.71192960187,5.70534954441,-3.93131788635,0.963881964535},
{1.5097616167,-1.19827449537,0.999842142073,-0.210203756517},
{-1.60039623414,3.24480814869,-1.11591149796,0.125630154599},
{2.3184526579,-0.547626262968,0.107454441287,-0.00591457005072}}; 
__device__ double a_2011_L0noTIS_wide[5][4] = {{0.0,-0.00098639638413,2.21305126523,-1.24975680956},
{-1.38905016398,4.62918081687,-2.93157897172,0.655661796718},
{0.301283465128,1.00703732593,-0.344333621046,0.0396509989394},
{0.280998193193,1.03601628584,-0.358133125764,0.0418413965137},
{1.65203424402,-0.290792795608,0.0698698037346,-0.00418042386257}}; 
__device__ double a_2012_L0noTIS_wide[5][4] = {{0.0,-0.00143959572436,4.23974268964,-2.51791074478},
{-3.18832348534,10.6263053554,-7.56886281162,1.85564684828},
{2.64645621312,-1.87679399844,1.36192244113,-0.270730592851},
{-1.04557535896,3.39753681882,-1.14966366233,0.127933868015},
{2.9370024549,-0.456570742976,0.0935968414771,-0.00575005712493}}; 
__device__ double a_2011_L0TIS_narrow[5][4] = {{0.0,-0.00105007049752,2.10287696037,-1.21206867385},
{-1.42394206761,4.74542348821,-3.17098254931,0.741212626035},
{0.646630522127,0.308482224484,-0.00173878950165,-0.0133692215384},
{0.350645013584,0.752460487299,-0.223727920909,0.0236289670295},
{1.06879626479,0.0574754054844,0.000460815159922,-0.000477348676871}}; 
__device__ double a_2012_L0TIS_narrow[5][4] = {{0.0,-0.0217677276861,1.92932115124,-1.02522029051},
{-0.924217061529,3.05895581074,-1.49370500257,0.242567173866},
{-1.04708252048,3.32223893706,-1.68176437851,0.287343215756},
{1.38760726219,-0.329795736933,0.144252958489,-0.0169930070766},
{0.873682232338,0.167551066145,-0.0161814941165,0.000258009332581}}; 
__device__ double a_2011_L0noTIS_narrow[5][4] = {{0.0,-0.00141362744144,7.02846926232,-4.03198237274},
{-4.36857014682,14.5604868619,-9.15142017033,1.96056926898},
{-0.84323191785,7.00619065702,-3.75549430966,0.67582501644},
{5.39200898979,-2.34667070444,0.920936371063,-0.103580097015},
{2.42800757735,0.521717759207,-0.00435023011253,-0.00408691409238}}; 
__device__ double a_2012_L0noTIS_narrow[5][4] = {{0.0,-0.0135116503737,3.32589922088,-2.04848218086},
{-2.87136660569,9.55771036858,-7.3087919113,1.89029231253},
{3.9544829436,-5.06911009418,3.13893699067,-0.597262187936},
{-1.99801374513,3.85963493892,-1.32543552587,0.146799898155},
{2.48668454014,-0.480395659729,0.0745743446588,-0.00373879760085}};

__device__ double spline_knot(int wide_window,int i) {
   if (wide_window == 0) {return knots_narrow[i];}
   else {return knots_wide[i];}
 }

__device__ double spline_coef(int year_opt,int trig_opt,int wide_window,int ibin,int deg) {
   if (year_opt == 0) {
      if (trig_opt == 0) {
         if (wide_window == 0) {return a_2011_L0TIS_narrow[ibin][deg];}
         else {return a_2011_L0TIS_wide[ibin][deg];}
      }
      else {
         if (wide_window == 0) {return a_2011_L0noTIS_narrow[ibin][deg];}
         else {return a_2011_L0noTIS_wide[ibin][deg];}
      }
   }
   else {
      if (trig_opt == 0) {
         if (wide_window == 0) {return a_2012_L0TIS_narrow[ibin][deg];}
         else {return a_2012_L0TIS_wide[ibin][deg];}
      }
      else {
         if (wide_window == 0) {return a_2012_L0noTIS_narrow[ibin][deg];}
         else {return a_2012_L0noTIS_wide[ibin][deg];}
      }
   }
 }


// ##########################################
// Buffer variables

__device__ const int max_N_events = 100000;

__device__ int wide_window;
__device__ int year_opt[4];
__device__ int trig_opt[4];
__device__ double alt_fit;
__device__ double option;
__device__ double inftres;
__device__ double acctype;
__device__ double A_j1;
__device__ double A_j2;
__device__ double A_h;
__device__ double A_j1p;
__device__ double A_j2p;
__device__ double A_hp;
__device__ double qcomp;
__device__ int decision_SSK[4][max_N_events];
__device__ int decision_OS[4][max_N_events];
__device__ double etamistag_SSK[4][max_N_events];
__device__ double etamistag_OS[4][max_N_events];
__device__ double m1[4][max_N_events];
__device__ double m2[4][max_N_events];
__device__ double cos1[4][max_N_events];
__device__ double cos2[4][max_N_events];
__device__ double phi[4][max_N_events];
__device__ double t[4][max_N_events];
__device__ double t_err[4][max_N_events];
__device__ double max_fun[max_N_events];
__device__ double fun_ran[max_N_events];
__device__ double dec_accepted[max_N_events];
__device__ double reA00;
__device__ double reA01;
__device__ double reA10;
__device__ double reA02;
__device__ double reA20;
__device__ double reA110;
__device__ double reA11par;
__device__ double reA11perp;
__device__ double reA120;
__device__ double reA12par;
__device__ double reA12perp;
__device__ double reA210;
__device__ double reA21par;
__device__ double reA21perp;
__device__ double reA220;
__device__ double reA22par;
__device__ double reA22perp;
__device__ double reA22par2;
__device__ double reA22perp2;
__device__ double DCP_SS;
__device__ double DCP_SV;
__device__ double DCP_VS;
__device__ double DCP_ST;
__device__ double DCP_TS;
__device__ double DCP;
__device__ double DCP_VT;
__device__ double DCP_TV;
__device__ double DCP_TT;
__device__ double imA00;
__device__ double imA01;
__device__ double imA10;
__device__ double imA02;
__device__ double imA20;
__device__ double imA110;
__device__ double imA11par;
__device__ double imA11perp;
__device__ double imA120;
__device__ double imA12par;
__device__ double imA12perp;
__device__ double imA210;
__device__ double imA21par;
__device__ double imA21perp;
__device__ double imA220;
__device__ double imA22par;
__device__ double imA22perp;
__device__ double imA22par2;
__device__ double imA22perp2;
__device__ double phis;
__device__ double dphi_SS;
__device__ double dphi_SV;
__device__ double dphi_VS;
__device__ double dphi_ST;
__device__ double dphi_TS;
__device__ double dphi_VT;
__device__ double dphi_TV;
__device__ double dphi_TT;
__device__ double delta_m_freq;
__device__ double gamma_Bs_freq;
__device__ double delta_gamma_freq;
__device__ double p0metac_tag_SSK;
__device__ double p0metac_tag_OS;
__device__ double Dp0half_tag_SSK;
__device__ double Dp0half_tag_OS;
__device__ double p1_tag_SSK;
__device__ double p1_tag_OS;
__device__ double Dp1half_tag_SSK;
__device__ double Dp1half_tag_OS;
__device__ double etac_tag_SSK;
__device__ double etac_tag_OS;
__device__ double deltatmean_tres_11;
__device__ double p0_tres_11;
__device__ double p1_tres_11;
__device__ double deltatmean_tres_12;
__device__ double p0_tres_12;
__device__ double p1_tres_12;
__device__ double mv;
__device__ double ms;
__device__ double mt;
__device__ double gv;
__device__ double gs;
__device__ double gt;
__device__ double c1_mass_swave;
__device__ double c2_mass_swave;
__device__ double c3_mass_swave;
__device__ double c4_mass_swave;
__device__ double c5_mass_swave;
__device__ double c6_mass_swave;
__device__ double c7_mass_swave;
__device__ double c8_mass_swave;
__device__ double c9_mass_swave;
__device__ double res_mass;
__device__ double tag_eff_SSK;
__device__ double mu1_SSK;
__device__ double sigma1_SSK;
__device__ double c_SSK;
__device__ double mu2_SSK;
__device__ double sigma2_SSK;
__device__ double tag_eff_OS;
__device__ double mu1_OS;
__device__ double sigma1_OS;
__device__ double c_OS;
__device__ double mu2_OS;
__device__ double sigma2_OS;
__device__ double gamma1_dt;
__device__ double beta1_dt;
__device__ double c_dt;
__device__ double gamma2_dt;
__device__ double beta2_dt;
__device__ double pw_mass_altmodel;
__device__ double f_1410_rel2_892;
__device__ double delta_1410_rel2_892;
__device__ double f_1680_rel2_892;
__device__ double delta_1680_rel2_892;
__device__ double Im00;
__device__ double Im01;
__device__ double Im10;
__device__ double Im02;
__device__ double Im20;
__device__ double Im11;
__device__ double Im12;
__device__ double Im21;
__device__ double Im22;
__device__ double Ih1Re;
__device__ double Ih2Re;
__device__ double Ih3Re;
__device__ double Ih4Re;
__device__ double Ih5Re;
__device__ double Ih6Re;
__device__ double Ih7Re;
__device__ double Ih8Re;
__device__ double Ih9Re;
__device__ double Ih10Re;
__device__ double Ih11Re;
__device__ double Ih12Re;
__device__ double Ih13Re;
__device__ double Ih14Re;
__device__ double Ih15Re;
__device__ double Ih16Re;
__device__ double Ih17Re;
__device__ double Ih18Re;
__device__ double Ih19Re;
__device__ double Ih20Re;
__device__ double Ih21Re;
__device__ double Ih22Re;
__device__ double Ih23Re;
__device__ double Ih24Re;
__device__ double Ih25Re;
__device__ double Ih26Re;
__device__ double Ih27Re;
__device__ double Ih28Re;
__device__ double Ih29Re;
__device__ double Ih30Re;
__device__ double Ih1Im;
__device__ double Ih2Im;
__device__ double Ih3Im;
__device__ double Ih4Im;
__device__ double Ih5Im;
__device__ double Ih6Im;
__device__ double Ih7Im;
__device__ double Ih8Im;
__device__ double Ih9Im;
__device__ double Ih10Im;
__device__ double Ih11Im;
__device__ double Ih12Im;
__device__ double Ih13Im;
__device__ double Ih14Im;
__device__ double Ih15Im;
__device__ double Ih16Im;
__device__ double Ih17Im;
__device__ double Ih18Im;
__device__ double Ih19Im;
__device__ double Ih20Im;
__device__ double Ih21Im;
__device__ double If1;
__device__ double If2;
__device__ double If3;
__device__ double If4;
__device__ double If5;
__device__ double If6;
__device__ double If7;
__device__ double If8;
__device__ double If9;
__device__ double If10;
__device__ double If11;
__device__ double If12;
__device__ double If13;
__device__ double If14;
__device__ double If15;
__device__ double If16;
__device__ double If17;
__device__ double If18;

__device__ double reAj1j2h_temp[3][3][5];
__device__ double imAj1j2h_temp[3][3][5];
__device__ double reAbarj1j2h_temp[3][3][5];
__device__ double imAbarj1j2h_temp[3][3][5];

__device__ pycuda::complex<double> Aj1j2h_temp(int j1, int j2, int h) {

   return pycuda::complex<double>(reAj1j2h_temp[j1][j2][h],imAj1j2h_temp[j1][j2][h]);

 }

__device__ pycuda::complex<double> Abarj1j2h_temp(int j1, int j2, int h) {

   return pycuda::complex<double>(reAbarj1j2h_temp[j1][j2][h],imAbarj1j2h_temp[j1][j2][h]);

 }

__device__ double T_cosh_temp[4][max_N_events];
__device__ double T_sinh_temp[4][max_N_events];
__device__ double T_cos_temp[4][max_N_events];
__device__ double T_sin_temp[4][max_N_events];
__device__ double IT_cosh_temp_deltat[4][max_N_events];
__device__ double IT_sinh_temp_deltat[4][max_N_events];
__device__ double IT_cos_temp_deltat[4][max_N_events];
__device__ double IT_sin_temp_deltat[4][max_N_events];
__device__ double zeta_temp[4][max_N_events];
__device__ double DCP_tzero_temp[4][max_N_events];
__device__ double fi_cos1_temp[18][4][max_N_events];
__device__ double fi_cos2_temp[18][4][max_N_events];
__device__ double gi_temp[15][4][max_N_events];
__device__ double reMj1j2_temp[3][3][4][max_N_events];
__device__ double imMj1j2_temp[3][3][4][max_N_events];
__device__ double phasespace_temp[4][max_N_events];
__device__ double reIhj1j2j1pj2pdict[3][3][3][3];
__device__ double imIhj1j2j1pj2pdict[3][3][3][3];

__device__ pycuda::complex<double> Mj1j2_temp(int j1, int j2, int icat, int iev) {

   return pycuda::complex<double>(reMj1j2_temp[j1][j2][icat][iev],imMj1j2_temp[j1][j2][icat][iev]);

 }

__device__ pycuda::complex<double> Ihj1j2j1pj2p(int j1, int j2, int j1p, int j2p) {

   return pycuda::complex<double>(reIhj1j2j1pj2pdict[j1][j2][j1p][j2p],imIhj1j2j1pj2pdict[j1][j2][j1p][j2p]);

 }

// ##########################################
// Toy MC generation variables

__device__ double knots_gen_wide[6] = {0.0,0.9,1.3,1.9,3.0,12.0};
__device__ double knots_gen_narrow[6] = {0.0,0.9,1.3,1.9,3.0,12.0};

__device__ double a_gen_wide[5][4] = {{0.0,-0.00138436998913,2.5481847953,-1.45909728079},
{-1.6653800648,5.54988251268,-3.61988951878,0.82537468739},
{-0.289336418837,2.37439717584,-1.17720849044,0.199046218586},
{0.993185871959,0.349361979846,-0.111400492548,0.0120623593064},
{1.32606052325,0.0164873285591,-0.000442275452223,-0.000266331481965}};

__device__ double a_gen_narrow[5][4] = {{0.0,0.00101382530285,4.89487359849,-2.83048035352},
{-3.54249846114,11.8093420291,-8.22549107238,2.02891396902},
{1.06333885612,1.18048668157,-0.0494484973637,-0.0675072040589},
{-0.421082535913,3.52430993215,-1.28303968188,0.148912301997},
{3.78015377185,-0.67692637561,0.117372420705,-0.006689042735}};

__device__ double k1_gen(int wide_window) {
   if (wide_window) {return -0.40631262195;}
   else {return -0.505556252411;}
 }

__device__ double k2_gen(int wide_window) {
   if (wide_window) {return -0.39861379722;}
   else {return -0.404368705592;}
 }

__device__ double k3_gen(int wide_window) {
   if (wide_window) {return -0.0363987194893;}
   else {return -0.0483750503137;}
 }

__device__ double k4_gen(int wide_window) {
   if (wide_window) {return -0.0644151228873;}
   else {return -0.0175772310185;}
 }

__device__ double k5_gen(int wide_window) {
   if (wide_window) {return 0.0270906873059;}
   else {return 0.0389936024545;}
 }

__device__ double p1_gen(int wide_window) {
   if (wide_window) {return -0.000100573256821;}
   else {return 4.35273527839e-05;}
 }

__device__ double knot_gen(int wide_window,int i) {
   if (wide_window == 0) {return knots_gen_narrow[i];}
   else {return knots_gen_wide[i];}
 }

__device__ double coef_gen(int wide_window,int ibin,int deg) {
   if (wide_window == 0) {return a_gen_narrow[ibin][deg];}
   else {return a_gen_wide[ibin][deg];}
 }

__device__ double accGenTime(double tau) { 

   int tau_bin;
   if (tau < knot_gen(wide_window,1)) {tau_bin = 0;}
   else if ((tau >= knot_gen(wide_window,1)) and (tau < knot_gen(wide_window,2))) {tau_bin = 1;}
   else if ((tau >= knot_gen(wide_window,2)) and (tau < knot_gen(wide_window,3))) {tau_bin = 2;}
   else if ((tau >= knot_gen(wide_window,3)) and (tau < knot_gen(wide_window,4))) {tau_bin = 3;}
   else {tau_bin = 4;}

   return coef_gen(wide_window,tau_bin,0)+tau*coef_gen(wide_window,tau_bin,1)+tau*tau*coef_gen(wide_window,tau_bin,2)+tau*tau*tau*coef_gen(wide_window,tau_bin,3);

 }

__device__ double accGenAng(double x) { 

   return 1.+k1_gen(wide_window)*x+k2_gen(wide_window)*(2.*x*x-1.)+k3_gen(wide_window)*(4.*x*x*x-3.*x)+k4_gen(wide_window)*(8.*x*x*x*x-8.*x*x+1.)+k5_gen(wide_window)*(16.*x*x*x*x*x-20.*x*x*x+5.*x);

 }

__device__ double accGenMass(double m) { 
   
   return 1. + p1_gen(wide_window)*m;

 }

__device__ double accGen(double tau, double ma, double mb, double cos1var, double cos2var, double phivar) {
   return accGenTime(tau)*accGenMass(ma)*accGenMass(mb)*accGenAng(cos1var)*accGenAng(cos2var);
 }


// ##########################################
// Physical terms

__device__ double reAj1j2h(int j1, int j2, int h) {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return reA00;
      case 1 : return reA01;
      case 2 : return reA02;
      }
   case 1 :
      switch(j2) {
      case 0 : return reA10;
      case 1 :
         switch(h) {
         case 0 : return reA110;
         case 1 : return reA11par;
         case 2 : return reA11perp;
         }
      case 2 :
         switch(h) {
         case 0 : return reA120;
         case 1 : return reA12par;
         case 2 : return reA12perp;      
         }
      }
   case 2 :
      switch(j2) {
      case 0 : return reA20;
      case 1 :
         switch(h) {
         case 0 : return reA210;
         case 1 : return reA21par;
         case 2 : return reA21perp;
         }
      case 2 :
         switch(h) {
         case 0 : return reA220;
         case 1 : return reA22par;
         case 2 : return reA22perp;
         case 3 : return reA22par2;
         case 4 : return reA22perp2;
         }
      }
   }
   return 0.;

 }

__device__ double imAj1j2h(int j1, int j2, int h) {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return imA00;
      case 1 : return imA01;
      case 2 : return imA02;
      }
   case 1 :
      switch(j2) {
      case 0 : return imA10;
      case 1 :
         switch(h) {
         case 0 : return imA110;
         case 1 : return imA11par;
         case 2 : return imA11perp;
         }
      case 2 :
         switch(h) {
         case 0 : return imA120;
         case 1 : return imA12par;
         case 2 : return imA12perp;      
         }
      }
   case 2 :
      switch(j2) {
      case 0 : return imA20;
      case 1 :
         switch(h) {
         case 0 : return imA210;
         case 1 : return imA21par;
         case 2 : return imA21perp;
         }
      case 2 :
         switch(h) {
         case 0 : return imA220;
         case 1 : return imA22par;
         case 2 : return imA22perp;
         case 3 : return imA22par2;
         case 4 : return imA22perp2;
         }
      }
   }
   return 0.;

 }

__device__ double DCPj1j2(int j1, int j2) {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return DCP;//+DCP_SS;
      case 1 : return DCP;//+DCP_SV;
      case 2 : return DCP;//+DCP_TT;//DCP_ST;
      }
   case 1 :
      switch(j2) {
      case 0 : return DCP;//+DCP_VS;
      case 1 : return DCP;
      case 2 : return DCP;//+DCP_TT;//DCP_VT;
      }
   case 2 :
      switch(j2) {
      case 0 : return DCP;//+DCP_TT;//DCP_TS;
      case 1 : return DCP;//+DCP_TT;//DCP_TV;
      case 2 : return DCP;//+DCP_TT;
      }
   }
   return 0;

 }

__device__ double dphij1j2(int j1, int j2) {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return dphi_SS;
      case 1 : return dphi_SV;
      case 2 : return dphi_ST;
      }
   case 1 :
      switch(j2) {
      case 0 : return dphi_VS;
      case 1 : return 0.;
      case 2 : return dphi_VT;
      }
   case 2 :
      switch(j2) {
      case 0 : return dphi_TS;
      case 1 : return dphi_TV;
      case 2 : return dphi_TT;
      }
   }
   return 0;

 }

__device__ double etah(int h) {

   if ((h == 2) or (h == 4)) {return -1.;}
   else {return 1.;}

 }

__device__ double etaj1j2h(int j1, int j2, int h) {

   return pow(-1.,j1+j2)*etah(h);

 }

__device__ pycuda::complex<double> Aj1j2h(int j1, int j2, int h) {

   pycuda::complex<double> I(0.,1.);
   return pycuda::complex<double>(reAj1j2h(j1,j2,h),imAj1j2h(j1,j2,h))*pycuda::complex<double>(sqrt(1.+DCPj1j2(j1,j2)))*exp(I*0.5*(phis+dphij1j2(j1,j2)));

 }

__device__ pycuda::complex<double> Abarj1j2h(int j1, int j2, int h) {

   pycuda::complex<double> I(0.,1.);
   return etaj1j2h(j2,j1,h)*pycuda::complex<double>(reAj1j2h(j2,j1,h),imAj1j2h(j2,j1,h))*pycuda::complex<double>(sqrt(1.-DCPj1j2(j2,j1)))*exp(-I*0.5*(phis+dphij1j2(j2,j1)));

 }

__device__ pycuda::complex<double> M_Average(int j1, int j2, int h, int j1p, int j2p, int hp) {

   return Aj1j2h_temp(j1,j2,h)*pycuda::conj(Aj1j2h_temp(j1p,j2p,hp))+Abarj1j2h_temp(j1,j2,h)*pycuda::conj(Abarj1j2h_temp(j1p,j2p,hp));

 }

__device__ pycuda::complex<double> M_DeltaGamma(int j1, int j2, int h, int j1p, int j2p, int hp) {

   return Aj1j2h_temp(j1,j2,h)*pycuda::conj(Abarj1j2h_temp(j1p,j2p,hp))+Abarj1j2h_temp(j1,j2,h)*pycuda::conj(Aj1j2h_temp(j1p,j2p,hp));

 }

__device__ pycuda::complex<double> M_DirCP(int j1, int j2, int h, int j1p, int j2p, int hp) {

   return Aj1j2h_temp(j1,j2,h)*pycuda::conj(Aj1j2h_temp(j1p,j2p,hp))-Abarj1j2h_temp(j1,j2,h)*pycuda::conj(Abarj1j2h_temp(j1p,j2p,hp));

 }

__device__ pycuda::complex<double> M_MixCP(int j1, int j2, int h, int j1p, int j2p, int hp) {

   return pycuda::complex<double>(0.,-1.)*(Aj1j2h_temp(j1,j2,h)*pycuda::conj(Abarj1j2h_temp(j1p,j2p,hp))-Abarj1j2h_temp(j1,j2,h)*pycuda::conj(Aj1j2h_temp(j1p,j2p,hp)));

 }


// ##########################################
// Flavour tagging terms

__device__ double omega_SSK(double eta) {

   return (p0metac_tag_SSK+etac_tag_SSK+Dp0half_tag_SSK)+(p1_tag_SSK+Dp1half_tag_SSK)*(eta-etac_tag_SSK);

 }

__device__ double omegabar_SSK(double eta) {

   return (p0metac_tag_SSK+etac_tag_SSK-Dp0half_tag_SSK)+(p1_tag_SSK-Dp1half_tag_SSK)*(eta-etac_tag_SSK);

 }

__device__ double omega_OS(double eta) {

   return (p0metac_tag_OS+etac_tag_OS+Dp0half_tag_OS)+(p1_tag_OS+Dp1half_tag_OS)*(eta-etac_tag_OS);

 }

__device__ double omegabar_OS(double eta) {

   return (p0metac_tag_OS+etac_tag_OS-Dp0half_tag_OS)+(p1_tag_OS-Dp1half_tag_OS)*(eta-etac_tag_OS);

 }

__device__ double P_Bs(int q1, int q2, double eta1, double eta2) {

   return (1.+0.5*q1*(1.-q1-2.*omega_SSK(eta1)))*(1.+0.5*q2*(1.-q2-2.*omega_OS(eta2)));

 }

__device__ double P_Bsbar(int q1, int q2, double eta1, double eta2) {

   return (1.-0.5*q1*(1.+q1-2.*omegabar_SSK(eta1)))*(1.-0.5*q2*(1.+q2-2.*omegabar_OS(eta2)));

 }

__device__ double zeta(int q1, int q2, double eta1, double eta2) {

   return 0.5*((1.+DCP_prod)*P_Bs(q1,q2,eta1,eta2)+(1.-DCP_prod)*P_Bsbar(q1,q2,eta1,eta2));

 }

__device__ double DCP_tzero(int q1, int q2, double eta1, double eta2) {

   return 0.5/zeta(q1,q2,eta1,eta2)*((1.+DCP_prod)*P_Bs(q1,q2,eta1,eta2)-(1.-DCP_prod)*P_Bsbar(q1,q2,eta1,eta2));

 }


// ##########################################
// Time dependent terms

#define errf_const 1.12837916709551
#define xLim 5.33
#define yLim 4.29

__device__ pycuda::complex<double> faddeeva(pycuda::complex<double> z) {

   double in_real = pycuda::real(z);
   double in_imag = pycuda::imag(z);
   int n, nc, nu;
   double h, q, Saux, Sx, Sy, Tn, Tx, Ty, Wx, Wy, xh, xl, x, yh, y;
   double Rx [33];
   double Ry [33];

   x = fabs(in_real);
   y = fabs(in_imag);

   if (y < yLim && x < xLim) {
      q = (1.0 - y / yLim) * sqrt(1.0 - (x / xLim) * (x / xLim));
      h  = 1.0 / (3.2 * q);
      nc = 7 + int(23.0 * q);
      xl = pow(h, double(1 - nc));
      xh = y + 0.5 / h;
      yh = x;
      nu = 10 + int(21.0 * q);
      Rx[nu] = 0.;
      Ry[nu] = 0.;
      for (n = nu; n > 0; n--){
         Tx = xh + n * Rx[n];
         Ty = yh - n * Ry[n];
         Tn = Tx*Tx + Ty*Ty;
         Rx[n-1] = 0.5 * Tx / Tn;
         Ry[n-1] = 0.5 * Ty / Tn;
         }
      Sx = 0.;
      Sy = 0.;
      for (n = nc; n>0; n--){
         Saux = Sx + xl;
         Sx = Rx[n-1] * Saux - Ry[n-1] * Sy;
         Sy = Rx[n-1] * Sy + Ry[n-1] * Saux;
         xl = h * xl;
      };
      Wx = errf_const * Sx;
      Wy = errf_const * Sy;
   }
   else {
      xh = y;
      yh = x;
      Rx[0] = 0.;
      Ry[0] = 0.;
      for (n = 9; n>0; n--){
         Tx = xh + n * Rx[0];
         Ty = yh - n * Ry[0];
         Tn = Tx * Tx + Ty * Ty;
         Rx[0] = 0.5 * Tx / Tn;
         Ry[0] = 0.5 * Ty / Tn;
      };
      Wx = errf_const * Rx[0];
      Wy = errf_const * Ry[0];
   }

   if (y == 0.) {
      Wx = exp(-x * x);
   }
   if (in_imag < 0.) {
      Wx =   2.0 * exp(y * y - x * x) * cos(2.0 * x * y) - Wx;
      Wy = - 2.0 * exp(y * y - x * x) * sin(2.0 * x * y) - Wy;
      if (in_real > 0.) {
         Wy = -Wy;
      }
   }
   else if (in_real < 0.) {
      Wy = -Wy;
   }

   return pycuda::complex<double>(Wx,Wy);

}

__device__ pycuda::complex<double> conv_exp(double x, pycuda::complex<double> z) {

   double re = pycuda::real(z)-x;

   if (re>-5.0) {return 0.5*faddeeva(pycuda::complex<double>(-pycuda::real(z),re))*exp(-x*x);}

   else {
      pycuda::complex<double> mi(0,-1);
      pycuda::complex<double> zp  = mi*(z-x);
      pycuda::complex<double> zsq = zp*zp;
      pycuda::complex<double> v = -zsq -x*x;
      pycuda::complex<double> iz(pycuda::real(z)+x,pycuda::real(z)-x);
      return 0.5*exp(v)*(exp(zsq)/(iz*sqrt(pi)) + 1.)*2. ;
   }

 }

__device__ pycuda::complex<double> Kn(pycuda::complex<double> z, int n) {

   if (n == 0) {return 1./(2.*z);}
   else if (n == 1) {return 1./(2.*z*z);}
   else if (n == 2) {return 1./z*(1.+1./(z*z));}
   else if (n == 3) {return 3./(z*z)*(1.+1./(z*z));}
   return pycuda::complex<double>(0.,0.);

 }

__device__ pycuda::complex<double> Mn_x(double x, pycuda::complex<double> z, int n) {

   if (n == 0) {return pycuda::complex<double>(erf(x),0.)-2.*conv_exp(x,z);}
   else if (n == 1) {return 2.*(-pycuda::complex<double>(sqrt(1./pi)*exp(-x*x),0.)-2.*x*conv_exp(x,z));}
   else if (n == 2) {return 2.*(-2.*x*exp(-x*x)*pycuda::complex<double>(sqrt(1./pi),0.)-(2.*x*x-1.)*2.*conv_exp(x,z));}
   else if (n == 3) {return 4.*(-(2.*x*x-1.)*exp(-x*x)*pycuda::complex<double>(sqrt(1./pi),0.)-x*(2.*x*x-3.)*2.*conv_exp(x,z));}
   return pycuda::complex<double>(0.,0.);

 }

__device__ pycuda::complex<double> Mn(double x_1, double x_2, pycuda::complex<double> z, int n) {

   return Mn_x(x_2,z,n)-Mn_x(x_1,z,n);

 }

__device__ pycuda::complex<double> Tj1j2hj1pj2php(int j1, int j2, int h, int j1p, int j2p, int hp, int icat, int iev) {

   return zeta_temp[icat][iev]*((T_cosh_temp[icat][iev]*M_Average(j1,j2,h,j1p,j2p,hp)-T_sinh_temp[icat][iev]*M_DeltaGamma(j1,j2,h,j1p,j2p,hp))+DCP_tzero_temp[icat][iev]*(T_cos_temp[icat][iev]*M_DirCP(j1,j2,h,j1p,j2p,hp)+T_sin_temp[icat][iev]*M_MixCP(j1,j2,h,j1p,j2p,hp)));

 }

__device__ pycuda::complex<double> ITj1j2hj1pj2php_deltat(int j1, int j2, int h, int j1p, int j2p, int hp, int icat, int iev) {

   return (IT_cosh_temp_deltat[icat][iev]*M_Average(j1,j2,h,j1p,j2p,hp)-IT_sinh_temp_deltat[icat][iev]*M_DeltaGamma(j1,j2,h,j1p,j2p,hp))+DCP_prod*(IT_cos_temp_deltat[icat][iev]*M_DirCP(j1,j2,h,j1p,j2p,hp)+IT_sin_temp_deltat[icat][iev]*M_MixCP(j1,j2,h,j1p,j2p,hp));

 }


// ##########################################
// Angular terms

__device__ double fi(double x, int i) { 

   switch(i) {
      case 1 : return 1.;
      case 2 : return x;
      case 3 : return sqrt(1.-x*x);
      case 4 : return 3.*x*x-1.;
      case 5 : return x*sqrt(1.-x*x);
      case 6 : return x*x;
      case 7 : return x*(3.*x*x-1.);
      case 8 : return x*x*sqrt(1.-x*x);
      case 9 : return 1.-x*x;
      case 10 : return (3.*x*x-1.)*sqrt(1.-x*x);
      case 11 : return x*(1.-x*x);
      case 12 : return (3.*x*x-1.)*(3.*x*x-1.);
      case 13 : return x*(3.*x*x-1.)*sqrt(1.-x*x);
      case 14 : return x*x*(1.-x*x);
      case 15 : return (1.-x*x)*sqrt(1.-x*x);
      case 16 : return (3.*x*x-1.)*(1.-x*x);
      case 17 : return x*(1.-x*x)*sqrt(1.-x*x);
      case 18 : return (1.-x*x)*(1.-x*x);
   }
   return 0.;

 }

__device__ double gi(double x, int i) { 

   switch(i) {
      case 1 : return 1.;
      case 2 : return cos(x);
      case 3 : return sin(x);
      case 4 : return cos(x)*cos(x);
      case 5 : return sin(x)*cos(x);
      case 6 : return sin(x)*sin(x);
      case 7 : return cos(2.*x);
      case 8 : return sin(2.*x);
      case 9 : return cos(x)*cos(2.*x);
      case 10 : return cos(x)*sin(2.*x);
      case 11 : return sin(x)*cos(2.*x);
      case 12 : return sin(x)*sin(2.*x);
      case 13 : return cos(2.*x)*cos(2.*x);
      case 14 : return sin(2.*x)*cos(2.*x);
      case 15 : return sin(2.*x)*sin(2.*x);
   }
   return 0.;

 }

__device__ double fjjphhp_cos1(int j, int jp, int h, int hp, int icat, int iev) { 

   return fi_cos1_temp[(int) fjjphhpindexdict[j][jp][h][hp]-1][icat][iev];

 }

__device__ double fjjphhp_cos2(int j, int jp, int h, int hp, int icat, int iev) { 

   return fi_cos2_temp[(int) fjjphhpindexdict[j][jp][h][hp]-1][icat][iev];

 }

__device__ double ghhp_phi(int h, int hp, int icat, int iev) { 

   return gi_temp[(int) ghhpindexdict[h][hp]-1][icat][iev];

 }

__device__ pycuda::complex<double> Nj1j2hj1pj2php(int j1, int j2, int h, int j1p, int j2p, int hp) {

   return Nj1j2hdict(j1,j2,h)*pycuda::conj(Nj1j2hdict(j1p,j2p,hp));
  
 }


// ##########################################
// Mass dependent terms

__device__ double get_q(double M, double ma, double mb) {

   double M2 = M*M;
   double m12 = ma*ma;
   double m22 = mb*mb;
   double q2 = .25*( M2*M2 - 2*M2*(m12+m22) +(m12*m12+m22*m22)-2*m12*m22) /M2;
   if (q2<0) {return 0.;}
   return sqrt(q2);

 }

__device__ double Blatt_Weisskopf2(double q, double q0, int L) {

   if (L<1.) {return 1.;}  
   double d = 1.6e-03;
   double z = q*d*q*d;
   double z0 = q0*d*q0*d;
   if (L==1) {return (1+z0)/(1+z);}
   else if (L==2) {return ((z0-3)*(z0-3) + 9*z0) / ((z-3)*(z-3) + 9*z);}
   else if (L==3) {return (z0*(z0-15)*(z0-15) + 9*(z0-5)) / (z*(z-15)*(z-15) + 9*(z-5));}
   return ( pow(z0*z0 -45*z0+105,2) +25*z0*(2*z0-21)*(2*z0-21)) /(pow(z*z -45*z+105,2) +25*z*(2*z-21)*(2*z-21));

 }

__device__ double FL_j1j2(int j1, int j2, double ma, double mb) {

   double p = get_q(MBs,ma,mb);
   double q_1 = get_q(ma,MPion,MKaon);
   double q_2 = get_q(mb,MPion,MKaon);

   double m0 = 895.81;
   double p0 = get_q(MBs,m0,m0);
   double q0 = get_q(m0,MPion,MKaon);

   //int L;
   //if (j1*j2>0) {L = abs(j1-j2)+1;}
   //else {L = abs(j1-j2);}
   int L = abs(j1-j2);
   double FL_Bs = pow(p/p0,L)*sqrt(Blatt_Weisskopf2(p,p0,L));

   double FL_Kpi1 = pow((q_1/q0),j1)*sqrt(Blatt_Weisskopf2(q_1,q0,j1));

   double FL_Kpi2 = pow((q_2/q0),j2)*sqrt(Blatt_Weisskopf2(q_2,q0,j2));

   return FL_Bs*FL_Kpi1*FL_Kpi2;

 }

__device__ pycuda::complex<double> Resonance(double m, double m0, double g0, int J) {

   double q = get_q(m,MPion,MKaon);
   double q0 = get_q(m0,MPion,MKaon);

   double gamma = g0*pow(q/q0,2*J+1)*(m0/m)*Blatt_Weisskopf2(q,q0,J);

   pycuda::complex<double> num(m0*g0,0.);
   pycuda::complex<double> denom(m0*m0-m*m,-m0*gamma);
   pycuda::complex<double> BW = num/denom;

   pycuda::complex<double> I(0.,1.);
   if (J == 1) {return BW*exp(-I*1.5707963267948966);}
   else if (J == 2) {return BW*exp(-I*0.006008360479292941);}
   return BW;

 }

__device__ double omega_Stheo(double m) {

   double m_GeV = m/1000.;
   double svar_GeV = m_GeV*m_GeV;
   double Delta_Kpi = MKaon/1000.*MKaon/1000.-MPion/1000.*MPion/1000.;
   double y_s = pow((svar_GeV-Delta_Kpi)/(svar_GeV+Delta_Kpi),2);
   double y_s0 = pow((s0_Stheo-Delta_Kpi)/(s0_Stheo+Delta_Kpi),2);
   return (sqrt(y_s)-alpha_Stheo*sqrt(y_s0-y_s))/(sqrt(y_s)+alpha_Stheo*sqrt(y_s0-y_s));

 }

__device__ double cotdelta_Stheo(double m) {

   double m_GeV = m/1000.;
   double svar_GeV = m_GeV*m_GeV;
   double q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   double omega_func = omega_Stheo(m);
   return m_GeV/(2.*q_Kpi_GeV*(svar_GeV-sAdler_Stheo))*(B0_Stheo+B1_Stheo*omega_func);

 }

__device__ double get_p1_Stheo(double q) {

   return 1.+a_Stheo*q/1000.*q/1000.+b_Stheo*q/1000.*q/1000.*q/1000.*q/1000.;

 }

__device__ double get_p2_Stheo(double q) {

   return 1.+c_Stheo*q/1000.*q/1000.;

 }

__device__ double Theta_Keta(double m) {

   if (m>=(MKaon+MEta)) {return 1.;}
   return 0.;

 }

__device__ pycuda::complex<double> Prop_Stheo(double m) { 

   pycuda::complex<double> I(0.,1.);
   double m_GeV = m/1000.;
   double svar_GeV = m_GeV*m_GeV;
   double q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   double q_Keta_GeV = get_q(m,MKaon,MEta)/1000.;

   pycuda::complex<double> T;

   if (m<(MKaon+MEta)) {
      T = 1./(cotdelta_Stheo(m)-I);
   }

   else {
      pycuda::complex<double> S0b = exp(I*2.*q_Keta_GeV*(phi0_Stheo+phi1_Stheo*q_Keta_GeV*q_Keta_GeV));
      double q_Kpi_r1_GeV = get_q(sqrtsr1_Stheo*1000.,MKaon,MPion)/1000.;
      double q_Keta_r1_GeV = get_q(sqrtsr1_Stheo*1000.,MKaon,MEta)/1000.;
      double q_Kpi_r2_GeV = get_q(sqrtsr2_Stheo*1000.,MKaon,MPion)/1000.;
      double q_Keta_r2_GeV = get_q(sqrtsr2_Stheo*1000.,MKaon,MEta)/1000.;
      double q_Kpi_hat_GeV = get_q(MKaon+MEta,MKaon,MPion)/1000.;
      double beta_Stheo = 1./cotdelta_Stheo(MKaon+MEta);
      double P1_s = (sqrtsr1_Stheo*sqrtsr1_Stheo-svar_GeV)*beta_Stheo+e1_Stheo*G1_Stheo*(get_p1_Stheo(q_Kpi_GeV*1000.)*(q_Kpi_GeV-q_Kpi_hat_GeV))/(get_p1_Stheo(q_Kpi_r1_GeV*1000.)*(q_Kpi_r1_GeV-q_Kpi_hat_GeV));
      double Q1_s = (1.-e1_Stheo)*G1_Stheo*get_p1_Stheo(q_Kpi_GeV*1000.)/get_p1_Stheo(q_Kpi_r1_GeV*1000.)*q_Keta_GeV/q_Keta_r1_GeV*Theta_Keta(m);
      double P2_s = e2_Stheo*G2_Stheo*(get_p2_Stheo(q_Kpi_GeV*1000.)*(q_Kpi_GeV-q_Kpi_hat_GeV))/(get_p2_Stheo(q_Kpi_r2_GeV*1000.)*(q_Kpi_r2_GeV-q_Kpi_hat_GeV));
      double Q2_s = (1.-e2_Stheo)*G2_Stheo*get_p2_Stheo(q_Kpi_GeV*1000.)/get_p2_Stheo(q_Kpi_r2_GeV*1000.)*q_Keta_GeV/q_Keta_r2_GeV*Theta_Keta(m);
      pycuda::complex<double> S1r = (sqrtsr1_Stheo*sqrtsr1_Stheo-svar_GeV+I*(P1_s-Q1_s))/(sqrtsr1_Stheo*sqrtsr1_Stheo-svar_GeV-I*(P1_s+Q1_s));
      pycuda::complex<double> S2r = (sqrtsr2_Stheo*sqrtsr2_Stheo-svar_GeV+I*(P2_s-Q2_s))/(sqrtsr2_Stheo*sqrtsr2_Stheo-svar_GeV-I*(P2_s+Q2_s));
      T = (S0b*S1r*S2r-1.)/(2.*I);
   }

   double xm = (m-1175.)/425.;
   double modulus = 1.+c1_mass_swave*xm+c2_mass_swave*(2.*xm*xm-1.)+c3_mass_swave*(4.*xm*xm*xm-3.*xm)+c4_mass_swave*(8.*xm*xm*xm*xm-8.*xm*xm+1.);

   return pycuda::complex<double>(modulus)*exp(I*(pycuda::arg(T)-0.7095863518296103));

 }

__device__ pycuda::complex<double> Prop_ModInd(double m) { 

   double xm = (m-1175.)/425.;
   double re_T = 1.+c1_mass_swave*xm+c2_mass_swave*(2.*xm*xm-1.)+c3_mass_swave*(4.*xm*xm*xm-3.*xm)+c4_mass_swave*(8.*xm*xm*xm*xm-8.*xm*xm+1.);
   double im_T = c5_mass_swave+c6_mass_swave*xm+c7_mass_swave*(2.*xm*xm-1.)+c8_mass_swave*(4.*xm*xm*xm-3.*xm)+c9_mass_swave*(8.*xm*xm*xm*xm-8.*xm*xm+1.);

   pycuda::complex<double> T(re_T,im_T);

   return T;

 }

__device__ pycuda::complex<double> Prop_S_Palano(double m) {

   pycuda::complex<double> i(0.,1.);
   double m_GeV = m/1000.;
   double svar_GeV = m_GeV*m_GeV;
   double q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   double q_Keta_GeV = get_q(m,MKaon,MEta)/1000.;

   double rho_1 = 2.*q_Kpi_GeV/m_GeV;
   double rho_2 = 2.*q_Keta_GeV/m_GeV;

   double sbot_GeV = 0.36;
   double stop_GeV = 5.832;
   double X = (2.*svar_GeV-(stop_GeV+sbot_GeV))/(stop_GeV-sbot_GeV);

   double K11 = (svar_GeV-s_A_palano)/s_Kpi_palano*(g_1_a_palano*g_1_a_palano/(svar_GeV-s_a_palano)+g_1_b_palano*g_1_b_palano/(svar_GeV-s_b_palano)+C_11_0_palano+C_11_1_palano*X+C_11_2_palano*X*X+C_11_3_palano*X*X*X);
   double K12 = (svar_GeV-s_A_palano)/s_Kpi_palano*(g_1_a_palano*g_2_a_palano/(svar_GeV-s_a_palano)+g_1_b_palano*g_2_b_palano/(svar_GeV-s_b_palano)+C_12_0_palano+C_12_1_palano*X+C_12_2_palano*X*X+C_12_3_palano*X*X*X);
   double K22 = (svar_GeV-s_A_palano)/s_Kpi_palano*(g_2_a_palano*g_2_a_palano/(svar_GeV-s_a_palano)+g_2_b_palano*g_2_b_palano/(svar_GeV-s_b_palano)+C_22_0_palano+C_22_1_palano*X+C_22_2_palano*X*X+C_22_3_palano*X*X*X);

   double detK = K11*K22-K12*K12;
   pycuda::complex<double> Delta(1.-rho_1*rho_2*detK,-rho_1*K11-rho_2*K22);

   pycuda::complex<double> T11_hat = s_Kpi_palano/(svar_GeV-s_A_palano)*(K11-rho_2*detK)/Delta;
   pycuda::complex<double> T12_hat = s_Kpi_palano/(svar_GeV-s_A_palano)*K12/Delta;

   double xm = X;//(m-1175.)/425.;
   double alpha_1_s = 1.+c1_mass_swave*xm+c2_mass_swave*(2.*xm*xm-1.)+c3_mass_swave*(4.*xm*xm*xm-3.*xm)+c4_mass_swave*(8.*xm*xm*xm*xm-8.*xm*xm+1.);
   double alpha_2_s = c5_mass_swave+c6_mass_swave*xm+c7_mass_swave*(2.*xm*xm-1.)+c8_mass_swave*(4.*xm*xm*xm-3.*xm)+c9_mass_swave*(8.*xm*xm*xm*xm-8.*xm*xm+1.);

   pycuda::complex<double> T = alpha_1_s*T11_hat+alpha_2_s*T12_hat;

   return T*exp(i*3.06573);

 }

__device__ pycuda::complex<double> Prop_Lass(double m) { 

   pycuda::complex<double> i(0,1);

   double a_lass_ = 1./c1_mass_swave;
   double r_lass_ = c2_mass_swave;
   double m0_ = c3_mass_swave;
   double g0_ = c4_mass_swave;

   double q = get_q(m,MPion,MKaon);
   double q0 = get_q(m0_,MPion,MKaon);

   double cotg_deltaB = 1./(a_lass_*q)+0.5*r_lass_*q;
   double deltaB = atan(1./cotg_deltaB);
   pycuda::complex<double> expo = exp(i*2.*deltaB);

   double gamma = g0_*(q/q0)*(m0_/m);
   double cotg_deltaR = (m0_*m0_-m*m)/(m0_*gamma);

   pycuda::complex<double> T = 1./(cotg_deltaB-i)+expo/(cotg_deltaR-i);

   return T;

 }

__device__ pycuda::complex<double> Mji(double m, int ji) {

   pycuda::complex<double> i(0,1);
   pycuda::complex<double> T;

   if (ji == 0)
	{
	T = Prop_Stheo(m)*exp(-i*pycuda::arg(Prop_Stheo(mv)));
	}

   else if (ji == 1)
	{
	//T = Resonance(m,mv,gv,1)*exp(-i*pycuda::arg(Resonance(mv,mv,gv,1)));
	T = (Resonance(m,mv,gv,1)+pycuda::complex<double>(c5_mass_swave,c6_mass_swave)*Resonance(m,MKst_1_1410,GKst_1_1410,1)+pycuda::complex<double>(c7_mass_swave,c8_mass_swave)*Resonance(m,MKst_1_1680,GKst_1_1680,1))*exp(-i*pycuda::arg(Resonance(mv,mv,gv,1)+pycuda::complex<double>(c5_mass_swave,c6_mass_swave)*Resonance(mv,MKst_1_1410,GKst_1_1410,1)+pycuda::complex<double>(c7_mass_swave,c8_mass_swave)*Resonance(mv,MKst_1_1680,GKst_1_1680,1)));
	}

   else if (ji == 2)
	{
	T = Resonance(m,mt,gt,2)*exp(-i*pycuda::arg(Resonance(mv,mt,gt,2)));
	}
   
   return T;

 }
 
__device__ pycuda::complex<double> Mj1j2(double ma, double mb, int j1, int j2) { 

   double scale_factor = 1.;

   if ((j1 == 0) and (j2 == 0)) {return Mji(ma,0)*Mji(mb,0)*FL_j1j2(0,0,ma,mb)*(scale_factor/sqrt(Im00));}
   else if ((j1 == 0) and (j2 == 1)) {return Mji(ma,0)*Mji(mb,1)*FL_j1j2(0,1,ma,mb)*(scale_factor/sqrt(Im01));}
   else if ((j1 == 1) and (j2 == 0)) {return Mji(ma,1)*Mji(mb,0)*FL_j1j2(1,0,ma,mb)*(scale_factor/sqrt(Im10));}
   else if ((j1 == 0) and (j2 == 2)) {return Mji(ma,0)*Mji(mb,2)*FL_j1j2(0,2,ma,mb)*(scale_factor/sqrt(Im02));}
   else if ((j1 == 2) and (j2 == 0)) {return Mji(ma,2)*Mji(mb,0)*FL_j1j2(2,0,ma,mb)*(scale_factor/sqrt(Im20));}
   else if ((j1 == 1) and (j2 == 1)) {return Mji(ma,1)*Mji(mb,1)*FL_j1j2(1,1,ma,mb)*(scale_factor/sqrt(Im11));}
   else if ((j1 == 1) and (j2 == 2)) {return Mji(ma,1)*Mji(mb,2)*FL_j1j2(1,2,ma,mb)*(scale_factor/sqrt(Im12));}
   else if ((j1 == 2) and (j2 == 1)) {return Mji(ma,2)*Mji(mb,1)*FL_j1j2(2,1,ma,mb)*(scale_factor/sqrt(Im21));}
   else if ((j1 == 2) and (j2 == 2)) {return Mji(ma,2)*Mji(mb,2)*FL_j1j2(2,2,ma,mb)*(scale_factor/sqrt(Im22));}
   return pycuda::complex<double>(0.,0.);

 }

__device__ pycuda::complex<double> Mj1j2_unnorm(double ma, double mb, int j1, int j2) { 

   if ((j1 == 0) and (j2 == 0)) {return Mji(ma,0)*Mji(mb,0)*FL_j1j2(0,0,ma,mb);}
   else if ((j1 == 0) and (j2 == 1)) {return Mji(ma,0)*Mji(mb,1)*FL_j1j2(0,1,ma,mb);}
   else if ((j1 == 1) and (j2 == 0)) {return Mji(ma,1)*Mji(mb,0)*FL_j1j2(1,0,ma,mb);}
   else if ((j1 == 0) and (j2 == 2)) {return Mji(ma,0)*Mji(mb,2)*FL_j1j2(0,2,ma,mb);}
   else if ((j1 == 2) and (j2 == 0)) {return Mji(ma,2)*Mji(mb,0)*FL_j1j2(2,0,ma,mb);}
   else if ((j1 == 1) and (j2 == 1)) {return Mji(ma,1)*Mji(mb,1)*FL_j1j2(1,1,ma,mb);}
   else if ((j1 == 1) and (j2 == 2)) {return Mji(ma,1)*Mji(mb,2)*FL_j1j2(1,2,ma,mb);}
   else if ((j1 == 2) and (j2 == 1)) {return Mji(ma,2)*Mji(mb,1)*FL_j1j2(2,1,ma,mb);}
   else if ((j1 == 2) and (j2 == 2)) {return Mji(ma,2)*Mji(mb,2)*FL_j1j2(2,2,ma,mb);}
   return pycuda::complex<double>(0.,0.);

 }

__device__ double phasespace(double ma, double mb) {
 
   double Q1 = get_q(ma,MKaon,MPion);
   double Q2 = get_q(mb,MKaon,MPion);
   double QB = get_q(MBs,ma,mb);
   double phsp = Q1*Q2*QB;

   return phsp;

 }

__device__ pycuda::complex<double> hj1j2j1pj2p(int j1, int j2, int j1p, int j2p, int icat, int iev) { 

   return Mj1j2_temp(j1,j2,icat,iev)*pycuda::conj(Mj1j2_temp(j1p,j2p,icat,iev))*phasespace_temp[icat][iev];

 }


// ##########################################
// PDF elements

__device__ double comp_num_fit(int j1, int j2, int h, int j1p, int j2p, int hp, int icat, int iev) {

   return pycuda::real(Tj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp,icat,iev)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(j1,j2,j1p,j2p,icat,iev))*ghhp_phi(h,hp,icat,iev)*fjjphhp_cos1(j1,j1p,h,hp,icat,iev)*fjjphhp_cos2(j2,j2p,h,hp,icat,iev);

 }

__device__ double comp_den_fit(int j1, int j2, int h, int j1p, int j2p, int hp, int icat, int iev) { 
   return pycuda::real(ITj1j2hj1pj2php_deltat(j1,j2,h,j1p,j2p,hp,icat,iev)*pycuda::complex<double>(nw_comp(year_opt[icat],trig_opt[icat],j1,j2,h,j1p,j2p,hp,0),nw_comp(year_opt[icat],trig_opt[icat],j1,j2,h,j1p,j2p,hp,1)));
 }

__device__ double num_fit(int icat, int iev) {

   return comp_num_fit(0,0,0,0,0,0,icat,iev)+comp_num_fit(0,1,0,0,1,0,icat,iev)+comp_num_fit(0,2,0,0,2,0,icat,iev)+comp_num_fit(1,0,0,1,0,0,icat,iev)+comp_num_fit(1,1,0,1,1,0,icat,iev)+comp_num_fit(1,1,1,1,1,1,icat,iev)
+comp_num_fit(1,1,2,1,1,2,icat,iev)+comp_num_fit(1,2,0,1,2,0,icat,iev)+comp_num_fit(1,2,1,1,2,1,icat,iev)+comp_num_fit(1,2,2,1,2,2,icat,iev)+comp_num_fit(2,0,0,2,0,0,icat,iev)+comp_num_fit(2,1,0,2,1,0,icat,iev)+comp_num_fit(2,1,1,2,1,1,icat,iev)
+comp_num_fit(2,1,2,2,1,2,icat,iev)+comp_num_fit(2,2,0,2,2,0,icat,iev)+comp_num_fit(2,2,1,2,2,1,icat,iev)+comp_num_fit(2,2,2,2,2,2,icat,iev)+comp_num_fit(2,2,3,2,2,3,icat,iev)+comp_num_fit(2,2,4,2,2,4,icat,iev)+2.*comp_num_fit(0,1,0,0,0,0,icat,iev)
+2.*comp_num_fit(0,1,0,1,0,0,icat,iev)+2.*comp_num_fit(0,1,0,2,0,0,icat,iev)+2.*comp_num_fit(0,2,0,0,0,0,icat,iev)+2.*comp_num_fit(0,2,0,0,1,0,icat,iev)+2.*comp_num_fit(0,2,0,1,0,0,icat,iev)+2.*comp_num_fit(0,2,0,1,1,0,icat,iev)
+2.*comp_num_fit(0,2,0,2,0,0,icat,iev)+2.*comp_num_fit(0,2,0,2,1,0,icat,iev)+2.*comp_num_fit(1,0,0,0,0,0,icat,iev)+2.*comp_num_fit(1,1,0,0,0,0,icat,iev)+2.*comp_num_fit(1,1,0,0,1,0,icat,iev)+2.*comp_num_fit(1,1,0,1,0,0,icat,iev)
+2.*comp_num_fit(1,1,0,2,0,0,icat,iev)+2.*comp_num_fit(1,1,1,0,0,0,icat,iev)+2.*comp_num_fit(1,1,1,0,1,0,icat,iev)+2.*comp_num_fit(1,1,1,0,2,0,icat,iev)+2.*comp_num_fit(1,1,1,1,0,0,icat,iev)+2.*comp_num_fit(1,1,1,1,1,0,icat,iev)
+2.*comp_num_fit(1,1,1,1,2,0,icat,iev)+2.*comp_num_fit(1,1,1,2,0,0,icat,iev)+2.*comp_num_fit(1,1,1,2,1,0,icat,iev)+2.*comp_num_fit(1,1,1,2,2,0,icat,iev)+2.*comp_num_fit(1,1,2,0,0,0,icat,iev)+2.*comp_num_fit(1,1,2,0,1,0,icat,iev)
+2.*comp_num_fit(1,1,2,0,2,0,icat,iev)+2.*comp_num_fit(1,1,2,1,0,0,icat,iev)+2.*comp_num_fit(1,1,2,1,1,0,icat,iev)+2.*comp_num_fit(1,1,2,1,1,1,icat,iev)+2.*comp_num_fit(1,1,2,1,2,0,icat,iev)+2.*comp_num_fit(1,1,2,1,2,1,icat,iev)
+2.*comp_num_fit(1,1,2,2,0,0,icat,iev)+2.*comp_num_fit(1,1,2,2,1,0,icat,iev)+2.*comp_num_fit(1,1,2,2,1,1,icat,iev)+2.*comp_num_fit(1,1,2,2,2,0,icat,iev)+2.*comp_num_fit(1,1,2,2,2,1,icat,iev)+2.*comp_num_fit(1,2,0,0,0,0,icat,iev)
+2.*comp_num_fit(1,2,0,0,1,0,icat,iev)+2.*comp_num_fit(1,2,0,0,2,0,icat,iev)+2.*comp_num_fit(1,2,0,1,0,0,icat,iev)+2.*comp_num_fit(1,2,0,1,1,0,icat,iev)+2.*comp_num_fit(1,2,0,2,0,0,icat,iev)+2.*comp_num_fit(1,2,0,2,1,0,icat,iev)
+2.*comp_num_fit(1,2,1,0,0,0,icat,iev)+2.*comp_num_fit(1,2,1,0,1,0,icat,iev)+2.*comp_num_fit(1,2,1,0,2,0,icat,iev)+2.*comp_num_fit(1,2,1,1,0,0,icat,iev)+2.*comp_num_fit(1,2,1,1,1,0,icat,iev)+2.*comp_num_fit(1,2,1,1,1,1,icat,iev)
+2.*comp_num_fit(1,2,1,1,2,0,icat,iev)+2.*comp_num_fit(1,2,1,2,0,0,icat,iev)+2.*comp_num_fit(1,2,1,2,1,0,icat,iev)+2.*comp_num_fit(1,2,1,2,1,1,icat,iev)+2.*comp_num_fit(1,2,1,2,2,0,icat,iev)+2.*comp_num_fit(1,2,2,0,0,0,icat,iev)
+2.*comp_num_fit(1,2,2,0,1,0,icat,iev)+2.*comp_num_fit(1,2,2,0,2,0,icat,iev)+2.*comp_num_fit(1,2,2,1,0,0,icat,iev)+2.*comp_num_fit(1,2,2,1,1,0,icat,iev)+2.*comp_num_fit(1,2,2,1,1,1,icat,iev)+2.*comp_num_fit(1,2,2,1,1,2,icat,iev)
+2.*comp_num_fit(1,2,2,1,2,0,icat,iev)+2.*comp_num_fit(1,2,2,1,2,1,icat,iev)+2.*comp_num_fit(1,2,2,2,0,0,icat,iev)+2.*comp_num_fit(1,2,2,2,1,0,icat,iev)+2.*comp_num_fit(1,2,2,2,1,1,icat,iev)+2.*comp_num_fit(1,2,2,2,1,2,icat,iev)
+2.*comp_num_fit(1,2,2,2,2,0,icat,iev)+2.*comp_num_fit(1,2,2,2,2,1,icat,iev)+2.*comp_num_fit(2,0,0,0,0,0,icat,iev)+2.*comp_num_fit(2,0,0,1,0,0,icat,iev)+2.*comp_num_fit(2,1,0,0,0,0,icat,iev)+2.*comp_num_fit(2,1,0,0,1,0,icat,iev)
+2.*comp_num_fit(2,1,0,1,0,0,icat,iev)+2.*comp_num_fit(2,1,0,1,1,0,icat,iev)+2.*comp_num_fit(2,1,0,2,0,0,icat,iev)+2.*comp_num_fit(2,1,1,0,0,0,icat,iev)+2.*comp_num_fit(2,1,1,0,1,0,icat,iev)+2.*comp_num_fit(2,1,1,0,2,0,icat,iev)
+2.*comp_num_fit(2,1,1,1,0,0,icat,iev)+2.*comp_num_fit(2,1,1,1,1,0,icat,iev)+2.*comp_num_fit(2,1,1,1,1,1,icat,iev)+2.*comp_num_fit(2,1,1,1,2,0,icat,iev)+2.*comp_num_fit(2,1,1,2,0,0,icat,iev)+2.*comp_num_fit(2,1,1,2,1,0,icat,iev)
+2.*comp_num_fit(2,1,1,2,2,0,icat,iev)+2.*comp_num_fit(2,1,2,0,0,0,icat,iev)+2.*comp_num_fit(2,1,2,0,1,0,icat,iev)+2.*comp_num_fit(2,1,2,0,2,0,icat,iev)+2.*comp_num_fit(2,1,2,1,0,0,icat,iev)+2.*comp_num_fit(2,1,2,1,1,0,icat,iev)
+2.*comp_num_fit(2,1,2,1,1,1,icat,iev)+2.*comp_num_fit(2,1,2,1,1,2,icat,iev)+2.*comp_num_fit(2,1,2,1,2,0,icat,iev)+2.*comp_num_fit(2,1,2,1,2,1,icat,iev)+2.*comp_num_fit(2,1,2,2,0,0,icat,iev)+2.*comp_num_fit(2,1,2,2,1,0,icat,iev)
+2.*comp_num_fit(2,1,2,2,1,1,icat,iev)+2.*comp_num_fit(2,1,2,2,2,0,icat,iev)+2.*comp_num_fit(2,1,2,2,2,1,icat,iev)+2.*comp_num_fit(2,2,0,0,0,0,icat,iev)+2.*comp_num_fit(2,2,0,0,1,0,icat,iev)+2.*comp_num_fit(2,2,0,0,2,0,icat,iev)
+2.*comp_num_fit(2,2,0,1,0,0,icat,iev)+2.*comp_num_fit(2,2,0,1,1,0,icat,iev)+2.*comp_num_fit(2,2,0,1,2,0,icat,iev)+2.*comp_num_fit(2,2,0,2,0,0,icat,iev)+2.*comp_num_fit(2,2,0,2,1,0,icat,iev)+2.*comp_num_fit(2,2,1,0,0,0,icat,iev)
+2.*comp_num_fit(2,2,1,0,1,0,icat,iev)+2.*comp_num_fit(2,2,1,0,2,0,icat,iev)+2.*comp_num_fit(2,2,1,1,0,0,icat,iev)+2.*comp_num_fit(2,2,1,1,1,0,icat,iev)+2.*comp_num_fit(2,2,1,1,1,1,icat,iev)+2.*comp_num_fit(2,2,1,1,2,0,icat,iev)
+2.*comp_num_fit(2,2,1,1,2,1,icat,iev)+2.*comp_num_fit(2,2,1,2,0,0,icat,iev)+2.*comp_num_fit(2,2,1,2,1,0,icat,iev)+2.*comp_num_fit(2,2,1,2,1,1,icat,iev)+2.*comp_num_fit(2,2,1,2,2,0,icat,iev)+2.*comp_num_fit(2,2,2,0,0,0,icat,iev)
+2.*comp_num_fit(2,2,2,0,1,0,icat,iev)+2.*comp_num_fit(2,2,2,0,2,0,icat,iev)+2.*comp_num_fit(2,2,2,1,0,0,icat,iev)+2.*comp_num_fit(2,2,2,1,1,0,icat,iev)+2.*comp_num_fit(2,2,2,1,1,1,icat,iev)+2.*comp_num_fit(2,2,2,1,1,2,icat,iev)
+2.*comp_num_fit(2,2,2,1,2,0,icat,iev)+2.*comp_num_fit(2,2,2,1,2,1,icat,iev)+2.*comp_num_fit(2,2,2,1,2,2,icat,iev)+2.*comp_num_fit(2,2,2,2,0,0,icat,iev)+2.*comp_num_fit(2,2,2,2,1,0,icat,iev)+2.*comp_num_fit(2,2,2,2,1,1,icat,iev)
+2.*comp_num_fit(2,2,2,2,1,2,icat,iev)+2.*comp_num_fit(2,2,2,2,2,0,icat,iev)+2.*comp_num_fit(2,2,2,2,2,1,icat,iev)+2.*comp_num_fit(2,2,3,0,0,0,icat,iev)+2.*comp_num_fit(2,2,3,0,1,0,icat,iev)+2.*comp_num_fit(2,2,3,0,2,0,icat,iev)
+2.*comp_num_fit(2,2,3,1,0,0,icat,iev)+2.*comp_num_fit(2,2,3,1,1,0,icat,iev)+2.*comp_num_fit(2,2,3,1,1,1,icat,iev)+2.*comp_num_fit(2,2,3,1,1,2,icat,iev)+2.*comp_num_fit(2,2,3,1,2,0,icat,iev)+2.*comp_num_fit(2,2,3,1,2,1,icat,iev)
+2.*comp_num_fit(2,2,3,1,2,2,icat,iev)+2.*comp_num_fit(2,2,3,2,0,0,icat,iev)+2.*comp_num_fit(2,2,3,2,1,0,icat,iev)+2.*comp_num_fit(2,2,3,2,1,1,icat,iev)+2.*comp_num_fit(2,2,3,2,1,2,icat,iev)+2.*comp_num_fit(2,2,3,2,2,0,icat,iev)
+2.*comp_num_fit(2,2,3,2,2,1,icat,iev)+2.*comp_num_fit(2,2,3,2,2,2,icat,iev)+2.*comp_num_fit(2,2,4,0,0,0,icat,iev)+2.*comp_num_fit(2,2,4,0,1,0,icat,iev)+2.*comp_num_fit(2,2,4,0,2,0,icat,iev)+2.*comp_num_fit(2,2,4,1,0,0,icat,iev)
+2.*comp_num_fit(2,2,4,1,1,0,icat,iev)+2.*comp_num_fit(2,2,4,1,1,1,icat,iev)+2.*comp_num_fit(2,2,4,1,1,2,icat,iev)+2.*comp_num_fit(2,2,4,1,2,0,icat,iev)+2.*comp_num_fit(2,2,4,1,2,1,icat,iev)+2.*comp_num_fit(2,2,4,1,2,2,icat,iev)
+2.*comp_num_fit(2,2,4,2,0,0,icat,iev)+2.*comp_num_fit(2,2,4,2,1,0,icat,iev)+2.*comp_num_fit(2,2,4,2,1,1,icat,iev)+2.*comp_num_fit(2,2,4,2,1,2,icat,iev)+2.*comp_num_fit(2,2,4,2,2,0,icat,iev)+2.*comp_num_fit(2,2,4,2,2,1,icat,iev)
+2.*comp_num_fit(2,2,4,2,2,2,icat,iev)+2.*comp_num_fit(2,2,4,2,2,3,icat,iev);

 }

__device__ double den_fit(int icat, int iev) {

   return comp_den_fit(0,0,0,0,0,0,icat,iev)+comp_den_fit(0,1,0,0,1,0,icat,iev)+comp_den_fit(0,2,0,0,2,0,icat,iev)+comp_den_fit(1,0,0,1,0,0,icat,iev)+comp_den_fit(1,1,0,1,1,0,icat,iev)+comp_den_fit(1,1,1,1,1,1,icat,iev)
+comp_den_fit(1,1,2,1,1,2,icat,iev)+comp_den_fit(1,2,0,1,2,0,icat,iev)+comp_den_fit(1,2,1,1,2,1,icat,iev)+comp_den_fit(1,2,2,1,2,2,icat,iev)+comp_den_fit(2,0,0,2,0,0,icat,iev)+comp_den_fit(2,1,0,2,1,0,icat,iev)+comp_den_fit(2,1,1,2,1,1,icat,iev)
+comp_den_fit(2,1,2,2,1,2,icat,iev)+comp_den_fit(2,2,0,2,2,0,icat,iev)+comp_den_fit(2,2,1,2,2,1,icat,iev)+comp_den_fit(2,2,2,2,2,2,icat,iev)+comp_den_fit(2,2,3,2,2,3,icat,iev)+comp_den_fit(2,2,4,2,2,4,icat,iev)+2.*comp_den_fit(0,1,0,0,0,0,icat,iev)
+2.*comp_den_fit(0,1,0,1,0,0,icat,iev)+2.*comp_den_fit(0,1,0,2,0,0,icat,iev)+2.*comp_den_fit(0,2,0,0,0,0,icat,iev)+2.*comp_den_fit(0,2,0,0,1,0,icat,iev)+2.*comp_den_fit(0,2,0,1,0,0,icat,iev)+2.*comp_den_fit(0,2,0,1,1,0,icat,iev)
+2.*comp_den_fit(0,2,0,2,0,0,icat,iev)+2.*comp_den_fit(0,2,0,2,1,0,icat,iev)+2.*comp_den_fit(1,0,0,0,0,0,icat,iev)+2.*comp_den_fit(1,1,0,0,0,0,icat,iev)+2.*comp_den_fit(1,1,0,0,1,0,icat,iev)+2.*comp_den_fit(1,1,0,1,0,0,icat,iev)
+2.*comp_den_fit(1,1,0,2,0,0,icat,iev)+2.*comp_den_fit(1,1,1,0,0,0,icat,iev)+2.*comp_den_fit(1,1,1,0,1,0,icat,iev)+2.*comp_den_fit(1,1,1,0,2,0,icat,iev)+2.*comp_den_fit(1,1,1,1,0,0,icat,iev)+2.*comp_den_fit(1,1,1,1,1,0,icat,iev)
+2.*comp_den_fit(1,1,1,1,2,0,icat,iev)+2.*comp_den_fit(1,1,1,2,0,0,icat,iev)+2.*comp_den_fit(1,1,1,2,1,0,icat,iev)+2.*comp_den_fit(1,1,1,2,2,0,icat,iev)+2.*comp_den_fit(1,1,2,0,0,0,icat,iev)+2.*comp_den_fit(1,1,2,0,1,0,icat,iev)
+2.*comp_den_fit(1,1,2,0,2,0,icat,iev)+2.*comp_den_fit(1,1,2,1,0,0,icat,iev)+2.*comp_den_fit(1,1,2,1,1,0,icat,iev)+2.*comp_den_fit(1,1,2,1,1,1,icat,iev)+2.*comp_den_fit(1,1,2,1,2,0,icat,iev)+2.*comp_den_fit(1,1,2,1,2,1,icat,iev)
+2.*comp_den_fit(1,1,2,2,0,0,icat,iev)+2.*comp_den_fit(1,1,2,2,1,0,icat,iev)+2.*comp_den_fit(1,1,2,2,1,1,icat,iev)+2.*comp_den_fit(1,1,2,2,2,0,icat,iev)+2.*comp_den_fit(1,1,2,2,2,1,icat,iev)+2.*comp_den_fit(1,2,0,0,0,0,icat,iev)
+2.*comp_den_fit(1,2,0,0,1,0,icat,iev)+2.*comp_den_fit(1,2,0,0,2,0,icat,iev)+2.*comp_den_fit(1,2,0,1,0,0,icat,iev)+2.*comp_den_fit(1,2,0,1,1,0,icat,iev)+2.*comp_den_fit(1,2,0,2,0,0,icat,iev)+2.*comp_den_fit(1,2,0,2,1,0,icat,iev)
+2.*comp_den_fit(1,2,1,0,0,0,icat,iev)+2.*comp_den_fit(1,2,1,0,1,0,icat,iev)+2.*comp_den_fit(1,2,1,0,2,0,icat,iev)+2.*comp_den_fit(1,2,1,1,0,0,icat,iev)+2.*comp_den_fit(1,2,1,1,1,0,icat,iev)+2.*comp_den_fit(1,2,1,1,1,1,icat,iev)
+2.*comp_den_fit(1,2,1,1,2,0,icat,iev)+2.*comp_den_fit(1,2,1,2,0,0,icat,iev)+2.*comp_den_fit(1,2,1,2,1,0,icat,iev)+2.*comp_den_fit(1,2,1,2,1,1,icat,iev)+2.*comp_den_fit(1,2,1,2,2,0,icat,iev)+2.*comp_den_fit(1,2,2,0,0,0,icat,iev)
+2.*comp_den_fit(1,2,2,0,1,0,icat,iev)+2.*comp_den_fit(1,2,2,0,2,0,icat,iev)+2.*comp_den_fit(1,2,2,1,0,0,icat,iev)+2.*comp_den_fit(1,2,2,1,1,0,icat,iev)+2.*comp_den_fit(1,2,2,1,1,1,icat,iev)+2.*comp_den_fit(1,2,2,1,1,2,icat,iev)
+2.*comp_den_fit(1,2,2,1,2,0,icat,iev)+2.*comp_den_fit(1,2,2,1,2,1,icat,iev)+2.*comp_den_fit(1,2,2,2,0,0,icat,iev)+2.*comp_den_fit(1,2,2,2,1,0,icat,iev)+2.*comp_den_fit(1,2,2,2,1,1,icat,iev)+2.*comp_den_fit(1,2,2,2,1,2,icat,iev)
+2.*comp_den_fit(1,2,2,2,2,0,icat,iev)+2.*comp_den_fit(1,2,2,2,2,1,icat,iev)+2.*comp_den_fit(2,0,0,0,0,0,icat,iev)+2.*comp_den_fit(2,0,0,1,0,0,icat,iev)+2.*comp_den_fit(2,1,0,0,0,0,icat,iev)+2.*comp_den_fit(2,1,0,0,1,0,icat,iev)
+2.*comp_den_fit(2,1,0,1,0,0,icat,iev)+2.*comp_den_fit(2,1,0,1,1,0,icat,iev)+2.*comp_den_fit(2,1,0,2,0,0,icat,iev)+2.*comp_den_fit(2,1,1,0,0,0,icat,iev)+2.*comp_den_fit(2,1,1,0,1,0,icat,iev)+2.*comp_den_fit(2,1,1,0,2,0,icat,iev)
+2.*comp_den_fit(2,1,1,1,0,0,icat,iev)+2.*comp_den_fit(2,1,1,1,1,0,icat,iev)+2.*comp_den_fit(2,1,1,1,1,1,icat,iev)+2.*comp_den_fit(2,1,1,1,2,0,icat,iev)+2.*comp_den_fit(2,1,1,2,0,0,icat,iev)+2.*comp_den_fit(2,1,1,2,1,0,icat,iev)
+2.*comp_den_fit(2,1,1,2,2,0,icat,iev)+2.*comp_den_fit(2,1,2,0,0,0,icat,iev)+2.*comp_den_fit(2,1,2,0,1,0,icat,iev)+2.*comp_den_fit(2,1,2,0,2,0,icat,iev)+2.*comp_den_fit(2,1,2,1,0,0,icat,iev)+2.*comp_den_fit(2,1,2,1,1,0,icat,iev)
+2.*comp_den_fit(2,1,2,1,1,1,icat,iev)+2.*comp_den_fit(2,1,2,1,1,2,icat,iev)+2.*comp_den_fit(2,1,2,1,2,0,icat,iev)+2.*comp_den_fit(2,1,2,1,2,1,icat,iev)+2.*comp_den_fit(2,1,2,2,0,0,icat,iev)+2.*comp_den_fit(2,1,2,2,1,0,icat,iev)
+2.*comp_den_fit(2,1,2,2,1,1,icat,iev)+2.*comp_den_fit(2,1,2,2,2,0,icat,iev)+2.*comp_den_fit(2,1,2,2,2,1,icat,iev)+2.*comp_den_fit(2,2,0,0,0,0,icat,iev)+2.*comp_den_fit(2,2,0,0,1,0,icat,iev)+2.*comp_den_fit(2,2,0,0,2,0,icat,iev)
+2.*comp_den_fit(2,2,0,1,0,0,icat,iev)+2.*comp_den_fit(2,2,0,1,1,0,icat,iev)+2.*comp_den_fit(2,2,0,1,2,0,icat,iev)+2.*comp_den_fit(2,2,0,2,0,0,icat,iev)+2.*comp_den_fit(2,2,0,2,1,0,icat,iev)+2.*comp_den_fit(2,2,1,0,0,0,icat,iev)
+2.*comp_den_fit(2,2,1,0,1,0,icat,iev)+2.*comp_den_fit(2,2,1,0,2,0,icat,iev)+2.*comp_den_fit(2,2,1,1,0,0,icat,iev)+2.*comp_den_fit(2,2,1,1,1,0,icat,iev)+2.*comp_den_fit(2,2,1,1,1,1,icat,iev)+2.*comp_den_fit(2,2,1,1,2,0,icat,iev)
+2.*comp_den_fit(2,2,1,1,2,1,icat,iev)+2.*comp_den_fit(2,2,1,2,0,0,icat,iev)+2.*comp_den_fit(2,2,1,2,1,0,icat,iev)+2.*comp_den_fit(2,2,1,2,1,1,icat,iev)+2.*comp_den_fit(2,2,1,2,2,0,icat,iev)+2.*comp_den_fit(2,2,2,0,0,0,icat,iev)
+2.*comp_den_fit(2,2,2,0,1,0,icat,iev)+2.*comp_den_fit(2,2,2,0,2,0,icat,iev)+2.*comp_den_fit(2,2,2,1,0,0,icat,iev)+2.*comp_den_fit(2,2,2,1,1,0,icat,iev)+2.*comp_den_fit(2,2,2,1,1,1,icat,iev)+2.*comp_den_fit(2,2,2,1,1,2,icat,iev)
+2.*comp_den_fit(2,2,2,1,2,0,icat,iev)+2.*comp_den_fit(2,2,2,1,2,1,icat,iev)+2.*comp_den_fit(2,2,2,1,2,2,icat,iev)+2.*comp_den_fit(2,2,2,2,0,0,icat,iev)+2.*comp_den_fit(2,2,2,2,1,0,icat,iev)+2.*comp_den_fit(2,2,2,2,1,1,icat,iev)
+2.*comp_den_fit(2,2,2,2,1,2,icat,iev)+2.*comp_den_fit(2,2,2,2,2,0,icat,iev)+2.*comp_den_fit(2,2,2,2,2,1,icat,iev)+2.*comp_den_fit(2,2,3,0,0,0,icat,iev)+2.*comp_den_fit(2,2,3,0,1,0,icat,iev)+2.*comp_den_fit(2,2,3,0,2,0,icat,iev)
+2.*comp_den_fit(2,2,3,1,0,0,icat,iev)+2.*comp_den_fit(2,2,3,1,1,0,icat,iev)+2.*comp_den_fit(2,2,3,1,1,1,icat,iev)+2.*comp_den_fit(2,2,3,1,1,2,icat,iev)+2.*comp_den_fit(2,2,3,1,2,0,icat,iev)+2.*comp_den_fit(2,2,3,1,2,1,icat,iev)
+2.*comp_den_fit(2,2,3,1,2,2,icat,iev)+2.*comp_den_fit(2,2,3,2,0,0,icat,iev)+2.*comp_den_fit(2,2,3,2,1,0,icat,iev)+2.*comp_den_fit(2,2,3,2,1,1,icat,iev)+2.*comp_den_fit(2,2,3,2,1,2,icat,iev)+2.*comp_den_fit(2,2,3,2,2,0,icat,iev)
+2.*comp_den_fit(2,2,3,2,2,1,icat,iev)+2.*comp_den_fit(2,2,3,2,2,2,icat,iev)+2.*comp_den_fit(2,2,4,0,0,0,icat,iev)+2.*comp_den_fit(2,2,4,0,1,0,icat,iev)+2.*comp_den_fit(2,2,4,0,2,0,icat,iev)+2.*comp_den_fit(2,2,4,1,0,0,icat,iev)
+2.*comp_den_fit(2,2,4,1,1,0,icat,iev)+2.*comp_den_fit(2,2,4,1,1,1,icat,iev)+2.*comp_den_fit(2,2,4,1,1,2,icat,iev)+2.*comp_den_fit(2,2,4,1,2,0,icat,iev)+2.*comp_den_fit(2,2,4,1,2,1,icat,iev)+2.*comp_den_fit(2,2,4,1,2,2,icat,iev)
+2.*comp_den_fit(2,2,4,2,0,0,icat,iev)+2.*comp_den_fit(2,2,4,2,1,0,icat,iev)+2.*comp_den_fit(2,2,4,2,1,1,icat,iev)+2.*comp_den_fit(2,2,4,2,1,2,icat,iev)+2.*comp_den_fit(2,2,4,2,2,0,icat,iev)+2.*comp_den_fit(2,2,4,2,2,1,icat,iev)
+2.*comp_den_fit(2,2,4,2,2,2,icat,iev)+2.*comp_den_fit(2,2,4,2,2,3,icat,iev);

 }


// ##########################################
// PDF evaluator

__device__ void set_buffer_options(double *options, int icat) {

   wide_window = (int) options[0];
   year_opt[icat] = (int) options[1];
   trig_opt[icat] = (int) options[2];
   alt_fit = options[3];
   option = options[4];
   inftres = options[5];
   acctype = options[6];
   A_j1 = options[7];
   A_j2 = options[8];
   A_h = options[9];
   A_j1p = options[10];
   A_j2p = options[11];
   A_hp = options[12];
   qcomp = options[13];

 }

__device__ void set_buffer_amplitudes(double *re_amps, double *dirCP_asyms, double *im_amps, double *weak_phases, double *mixing_params, double *calib_params) {

   reA00 = re_amps[0];
   reA01 = re_amps[1];
   reA10 = re_amps[2];
   reA02 = re_amps[3];
   reA20 = re_amps[4];
   reA110 = re_amps[5];
   reA11par = re_amps[6];
   reA11perp = re_amps[7];
   reA120 = re_amps[8];
   reA12par = re_amps[9];
   reA12perp = re_amps[10];
   reA210 = re_amps[11];
   reA21par = re_amps[12];
   reA21perp = re_amps[13];
   reA220 = re_amps[14];
   reA22par = re_amps[15];
   reA22perp = re_amps[16];
   reA22par2 = re_amps[17];
   reA22perp2 = re_amps[18];

   DCP_SS = dirCP_asyms[0];
   DCP_SV = dirCP_asyms[1];
   DCP_VS = dirCP_asyms[2];
   DCP_ST = dirCP_asyms[3];
   DCP_TS = dirCP_asyms[4];
   DCP = dirCP_asyms[5];
   DCP_VT = dirCP_asyms[6];
   DCP_TV = dirCP_asyms[7];
   DCP_TT = dirCP_asyms[8];

   imA00 = im_amps[0];
   imA01 = im_amps[1];
   imA10 = im_amps[2];
   imA02 = im_amps[3];
   imA20 = im_amps[4];
   imA110 = im_amps[5];
   imA11par = im_amps[6];
   imA11perp = im_amps[7];
   imA120 = im_amps[8];
   imA12par = im_amps[9];
   imA12perp = im_amps[10];
   imA210 = im_amps[11];
   imA21par = im_amps[12];
   imA21perp = im_amps[13];
   imA220 = im_amps[14];
   imA22par = im_amps[15];
   imA22perp = im_amps[16];
   imA22par2 = im_amps[17];
   imA22perp2 = im_amps[18];

   phis = weak_phases[0];
   dphi_SS = weak_phases[1];
   dphi_SV = weak_phases[2];
   dphi_VS = weak_phases[3];
   dphi_ST = weak_phases[4];
   dphi_TS = weak_phases[5];
   dphi_VT = weak_phases[6];
   dphi_TV = weak_phases[7];
   dphi_TT = weak_phases[8];

   delta_m_freq = mixing_params[0];
   gamma_Bs_freq = mixing_params[1];
   delta_gamma_freq = mixing_params[2];

   p0metac_tag_SSK = calib_params[0];
   p0metac_tag_OS = calib_params[1];
   Dp0half_tag_SSK = calib_params[2];
   Dp0half_tag_OS = calib_params[3];
   p1_tag_SSK = calib_params[4];
   p1_tag_OS = calib_params[5];
   Dp1half_tag_SSK = calib_params[6];
   Dp1half_tag_OS = calib_params[7];
   etac_tag_SSK = calib_params[8];
   etac_tag_OS = calib_params[9];
   deltatmean_tres_11 = calib_params[10];
   p0_tres_11 = calib_params[11];
   p1_tres_11 = calib_params[12];
   deltatmean_tres_12 = calib_params[13];
   p0_tres_12 = calib_params[14];
   p1_tres_12 = calib_params[15];
   mv = calib_params[16];
   ms = calib_params[17];
   mt = calib_params[18];
   gv = calib_params[19];
   gs = calib_params[20];
   gt = calib_params[21];
   c1_mass_swave = calib_params[22];
   c2_mass_swave = calib_params[23];
   c3_mass_swave = calib_params[24];
   c4_mass_swave = calib_params[25];
   c5_mass_swave = calib_params[26];
   c6_mass_swave = calib_params[27];
   c7_mass_swave = calib_params[28];
   c8_mass_swave = calib_params[29];
   c9_mass_swave = calib_params[30];
   res_mass = calib_params[31];

   if (wide_window == 0) {DCP_prod = -0.0101;}
   else {DCP_prod = -0.0072;}

   reAj1j2h_temp[0][0][0] = pycuda::real(Aj1j2h(0,0,0));
   reAj1j2h_temp[0][1][0] = pycuda::real(Aj1j2h(0,1,0));
   reAj1j2h_temp[1][0][0] = pycuda::real(Aj1j2h(1,0,0));
   reAj1j2h_temp[0][2][0] = pycuda::real(Aj1j2h(0,2,0));
   reAj1j2h_temp[2][0][0] = pycuda::real(Aj1j2h(2,0,0));
   reAj1j2h_temp[1][1][0] = pycuda::real(Aj1j2h(1,1,0));
   reAj1j2h_temp[1][1][1] = pycuda::real(Aj1j2h(1,1,1));
   reAj1j2h_temp[1][1][2] = pycuda::real(Aj1j2h(1,1,2));
   reAj1j2h_temp[1][2][0] = pycuda::real(Aj1j2h(1,2,0));
   reAj1j2h_temp[1][2][1] = pycuda::real(Aj1j2h(1,2,1));
   reAj1j2h_temp[1][2][2] = pycuda::real(Aj1j2h(1,2,2));
   reAj1j2h_temp[2][1][0] = pycuda::real(Aj1j2h(2,1,0));
   reAj1j2h_temp[2][1][1] = pycuda::real(Aj1j2h(2,1,1));
   reAj1j2h_temp[2][1][2] = pycuda::real(Aj1j2h(2,1,2));
   reAj1j2h_temp[2][2][0] = pycuda::real(Aj1j2h(2,2,0));
   reAj1j2h_temp[2][2][1] = pycuda::real(Aj1j2h(2,2,1));
   reAj1j2h_temp[2][2][2] = pycuda::real(Aj1j2h(2,2,2));
   reAj1j2h_temp[2][2][3] = pycuda::real(Aj1j2h(2,2,3));
   reAj1j2h_temp[2][2][4] = pycuda::real(Aj1j2h(2,2,4));
   imAj1j2h_temp[0][0][0] = pycuda::imag(Aj1j2h(0,0,0));
   imAj1j2h_temp[0][1][0] = pycuda::imag(Aj1j2h(0,1,0));
   imAj1j2h_temp[1][0][0] = pycuda::imag(Aj1j2h(1,0,0));
   imAj1j2h_temp[0][2][0] = pycuda::imag(Aj1j2h(0,2,0));
   imAj1j2h_temp[2][0][0] = pycuda::imag(Aj1j2h(2,0,0));
   imAj1j2h_temp[1][1][0] = pycuda::imag(Aj1j2h(1,1,0));
   imAj1j2h_temp[1][1][1] = pycuda::imag(Aj1j2h(1,1,1));
   imAj1j2h_temp[1][1][2] = pycuda::imag(Aj1j2h(1,1,2));
   imAj1j2h_temp[1][2][0] = pycuda::imag(Aj1j2h(1,2,0));
   imAj1j2h_temp[1][2][1] = pycuda::imag(Aj1j2h(1,2,1));
   imAj1j2h_temp[1][2][2] = pycuda::imag(Aj1j2h(1,2,2));
   imAj1j2h_temp[2][1][0] = pycuda::imag(Aj1j2h(2,1,0));
   imAj1j2h_temp[2][1][1] = pycuda::imag(Aj1j2h(2,1,1));
   imAj1j2h_temp[2][1][2] = pycuda::imag(Aj1j2h(2,1,2));
   imAj1j2h_temp[2][2][0] = pycuda::imag(Aj1j2h(2,2,0));
   imAj1j2h_temp[2][2][1] = pycuda::imag(Aj1j2h(2,2,1));
   imAj1j2h_temp[2][2][2] = pycuda::imag(Aj1j2h(2,2,2));
   imAj1j2h_temp[2][2][3] = pycuda::imag(Aj1j2h(2,2,3));
   imAj1j2h_temp[2][2][4] = pycuda::imag(Aj1j2h(2,2,4));
   reAbarj1j2h_temp[0][0][0] = pycuda::real(Abarj1j2h(0,0,0));
   reAbarj1j2h_temp[0][1][0] = pycuda::real(Abarj1j2h(0,1,0));
   reAbarj1j2h_temp[1][0][0] = pycuda::real(Abarj1j2h(1,0,0));
   reAbarj1j2h_temp[0][2][0] = pycuda::real(Abarj1j2h(0,2,0));
   reAbarj1j2h_temp[2][0][0] = pycuda::real(Abarj1j2h(2,0,0));
   reAbarj1j2h_temp[1][1][0] = pycuda::real(Abarj1j2h(1,1,0));
   reAbarj1j2h_temp[1][1][1] = pycuda::real(Abarj1j2h(1,1,1));
   reAbarj1j2h_temp[1][1][2] = pycuda::real(Abarj1j2h(1,1,2));
   reAbarj1j2h_temp[1][2][0] = pycuda::real(Abarj1j2h(1,2,0));
   reAbarj1j2h_temp[1][2][1] = pycuda::real(Abarj1j2h(1,2,1));
   reAbarj1j2h_temp[1][2][2] = pycuda::real(Abarj1j2h(1,2,2));
   reAbarj1j2h_temp[2][1][0] = pycuda::real(Abarj1j2h(2,1,0));
   reAbarj1j2h_temp[2][1][1] = pycuda::real(Abarj1j2h(2,1,1));
   reAbarj1j2h_temp[2][1][2] = pycuda::real(Abarj1j2h(2,1,2));
   reAbarj1j2h_temp[2][2][0] = pycuda::real(Abarj1j2h(2,2,0));
   reAbarj1j2h_temp[2][2][1] = pycuda::real(Abarj1j2h(2,2,1));
   reAbarj1j2h_temp[2][2][2] = pycuda::real(Abarj1j2h(2,2,2));
   reAbarj1j2h_temp[2][2][3] = pycuda::real(Abarj1j2h(2,2,3));
   reAbarj1j2h_temp[2][2][4] = pycuda::real(Abarj1j2h(2,2,4));
   imAbarj1j2h_temp[0][0][0] = pycuda::imag(Abarj1j2h(0,0,0));
   imAbarj1j2h_temp[0][1][0] = pycuda::imag(Abarj1j2h(0,1,0));
   imAbarj1j2h_temp[1][0][0] = pycuda::imag(Abarj1j2h(1,0,0));
   imAbarj1j2h_temp[0][2][0] = pycuda::imag(Abarj1j2h(0,2,0));
   imAbarj1j2h_temp[2][0][0] = pycuda::imag(Abarj1j2h(2,0,0));
   imAbarj1j2h_temp[1][1][0] = pycuda::imag(Abarj1j2h(1,1,0));
   imAbarj1j2h_temp[1][1][1] = pycuda::imag(Abarj1j2h(1,1,1));
   imAbarj1j2h_temp[1][1][2] = pycuda::imag(Abarj1j2h(1,1,2));
   imAbarj1j2h_temp[1][2][0] = pycuda::imag(Abarj1j2h(1,2,0));
   imAbarj1j2h_temp[1][2][1] = pycuda::imag(Abarj1j2h(1,2,1));
   imAbarj1j2h_temp[1][2][2] = pycuda::imag(Abarj1j2h(1,2,2));
   imAbarj1j2h_temp[2][1][0] = pycuda::imag(Abarj1j2h(2,1,0));
   imAbarj1j2h_temp[2][1][1] = pycuda::imag(Abarj1j2h(2,1,1));
   imAbarj1j2h_temp[2][1][2] = pycuda::imag(Abarj1j2h(2,1,2));
   imAbarj1j2h_temp[2][2][0] = pycuda::imag(Abarj1j2h(2,2,0));
   imAbarj1j2h_temp[2][2][1] = pycuda::imag(Abarj1j2h(2,2,1));
   imAbarj1j2h_temp[2][2][2] = pycuda::imag(Abarj1j2h(2,2,2));
   imAbarj1j2h_temp[2][2][3] = pycuda::imag(Abarj1j2h(2,2,3));
   imAbarj1j2h_temp[2][2][4] = pycuda::imag(Abarj1j2h(2,2,4));

 }

__device__ void set_buffer_differential_terms(double *mass_integrals, int icat, int iev) {

   Im00 = mass_integrals[0];
   Im01 = mass_integrals[1];
   Im10 = mass_integrals[2];
   Im02 = mass_integrals[3];
   Im20 = mass_integrals[4];
   Im11 = mass_integrals[5];
   Im12 = mass_integrals[6];
   Im21 = mass_integrals[7];
   Im22 = mass_integrals[8];

   double f1,f2,s1,s2,x1,x2;

   if (acctype == 3) {
      f1 = 1.;
      f2 = 0.;
      s1 = p0_tres_12+p1_tres_12*(t_err[icat][iev]-deltatmean_tres_12);
      s2 = 1.;
      x1 = t[icat][iev]/(sqrt(2.)*s1);
      x2 = t[icat][iev]/(sqrt(2.)*s2);
   }
   else {
      f1 = 1.;
      f2 = 0.;
      if (year_opt == 0) {s1 = p0_tres_11+p1_tres_11*(t_err[icat][iev]-deltatmean_tres_11);}
      else {s1 = p0_tres_12+p1_tres_12*(t_err[icat][iev]-deltatmean_tres_12);}
      s2 = 1.;
      x1 = t[icat][iev]/(sqrt(2.)*s1);
      x2 = t[icat][iev]/(sqrt(2.)*s2);
   }

   pycuda::complex<double> z1_hyper_plus = s1/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z2_hyper_plus = s2/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z1_hyper_minus = s1/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z2_hyper_minus = s2/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z1_trigo = s1/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq,-delta_m_freq);
   pycuda::complex<double> z2_trigo = s2/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq,-delta_m_freq);

   double conv_exp_hyper_plus = pycuda::real(f1*conv_exp(x1,z1_hyper_plus)+f2*conv_exp(x2,z2_hyper_plus));
   double conv_exp_hyper_minus = pycuda::real(f1*conv_exp(x1,z1_hyper_minus)+f2*conv_exp(x2,z2_hyper_minus));
   pycuda::complex<double> conv_exp_trigo = f1*conv_exp(x1,z1_trigo)+f2*conv_exp(x2,z2_trigo);

   T_cosh_temp[icat][iev] = 0.5*(conv_exp_hyper_plus + conv_exp_hyper_minus);
   T_sinh_temp[icat][iev] = 0.5*(conv_exp_hyper_plus - conv_exp_hyper_minus);
   T_cos_temp[icat][iev] = pycuda::real(conv_exp_trigo);
   T_sin_temp[icat][iev] = pycuda::imag(conv_exp_trigo);

   zeta_temp[icat][iev] = zeta(decision_SSK[icat][iev],decision_OS[icat][iev],etamistag_SSK[icat][iev],etamistag_OS[icat][iev]);
   DCP_tzero_temp[icat][iev] = DCP_tzero(decision_SSK[icat][iev],decision_OS[icat][iev],etamistag_SSK[icat][iev],etamistag_OS[icat][iev]);

   for (int i=0; i<18; ++i) {fi_cos1_temp[i][icat][iev] = fi(cos1[icat][iev],i+1);}
   for (int i=0; i<18; ++i) {fi_cos2_temp[i][icat][iev] = fi(cos2[icat][iev],i+1);}
   for (int i=0; i<15; ++i) {gi_temp[i][icat][iev] = gi(phi[icat][iev],i+1);}

   for (int j1=0; j1<3; ++j1) {
      for (int j2=0; j2<3; ++j2) {
         pycuda::complex<double> M_temp = Mj1j2(m1[icat][iev],m2[icat][iev],j1,j2);
         reMj1j2_temp[j1][j2][icat][iev] = pycuda::real(M_temp);
         imMj1j2_temp[j1][j2][icat][iev] = pycuda::imag(M_temp);
      }
   }

   phasespace_temp[icat][iev] = phasespace(m1[icat][iev],m2[icat][iev]);

 }

__device__ double Factorial(int n) {

   if(n <= 0) return 1.;
   double x = 1;
   int b = 0;
   do {
      b++;
      x *= b;
   } while(b!=n);
   return x;

 }

__device__ void set_buffer_integral_terms(int icat, int iev) {

   double s1_deltat;

   if (acctype == 3) {
      s1_deltat = p0_tres_12+p1_tres_12*(t_err[icat][iev]-deltatmean_tres_12);
      for (int i=0; i<6; ++i) {spl_knot_vector[year_opt[icat]][trig_opt[icat]][i] = knot_gen(wide_window,i);}
   }

   else {
      if (year_opt == 0) {s1_deltat = p0_tres_11+p1_tres_11*(t_err[icat][iev]-deltatmean_tres_11);}
      else {s1_deltat = p0_tres_12+p1_tres_12*(t_err[icat][iev]-deltatmean_tres_12);}
      for (int i=0; i<6; ++i) {spl_knot_vector[year_opt[icat]][trig_opt[icat]][i] = spline_knot(wide_window,i);}
   }

   pycuda::complex<double> z1_hyper_plus_deltat = s1_deltat/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z1_hyper_minus_deltat = s1_deltat/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z1_trigo_deltat = s1_deltat/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq,-delta_m_freq);

   double spl_knot_x1_vector_deltat[6];
   double spl_coef_array_deltat[5][4][4][4];

   if (acctype == 1 or acctype == 2) {
      spl_knot_x1_vector_deltat[0] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][0]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[1] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][1]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[2] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][2]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[3] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][3]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[4] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][4]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[5] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][5]/(sqrt(2.)*s1_deltat);
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  spl_coef_array_deltat[ibin][k][i][j] = spline_coef(year_opt[icat],trig_opt[icat],wide_window,ibin,k)*Factorial(k)/Factorial(k-i)/Factorial(i-j)/Factorial(j)*pow(s1_deltat/sqrt(2.),i+1)*pow(0.,k-i);
               }
            }
         }
      }
   }
   else if (acctype == 3) {
      spl_knot_x1_vector_deltat[0] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][0]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[1] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][1]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[2] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][2]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[3] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][3]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[4] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][4]/(sqrt(2.)*s1_deltat);
      spl_knot_x1_vector_deltat[5] = spl_knot_vector[year_opt[icat]][trig_opt[icat]][5]/(sqrt(2.)*s1_deltat);
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  spl_coef_array_deltat[ibin][k][i][j] = coef_gen(wide_window,ibin,k)*Factorial(k)/Factorial(k-i)/Factorial(i-j)/Factorial(j)*pow(s1_deltat/sqrt(2.),i+1)*pow(0.,k-i);
               }
            }
         }
      }
   }

   double integral_conv_exp_hyper_plus_deltat = 0;
   double integral_conv_exp_hyper_minus_deltat = 0;
   pycuda::complex<double> integral_conv_exp_trigo_deltat = pycuda::complex<double>(0.,0.);

   if (acctype == 0) {
      integral_conv_exp_hyper_plus_deltat += pycuda::real(s1_deltat/sqrt(2.)*Mn(0.,12./(sqrt(2.)*s1_deltat),z1_hyper_plus_deltat,0)*Kn(z1_hyper_plus_deltat,0));
      integral_conv_exp_hyper_minus_deltat += pycuda::real(s1_deltat/sqrt(2.)*Mn(0.,12./(sqrt(2.)*s1_deltat),z1_hyper_minus_deltat,0)*Kn(z1_hyper_minus_deltat,0));
      integral_conv_exp_trigo_deltat += s1_deltat/sqrt(2.)*Mn(0.,12./(sqrt(2.)*s1_deltat),z1_trigo_deltat,0)*Kn(z1_trigo_deltat,0);
   }
   else {
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  integral_conv_exp_hyper_plus_deltat += pycuda::real(spl_coef_array_deltat[ibin][k][i][j]*Mn(spl_knot_x1_vector_deltat[ibin],spl_knot_x1_vector_deltat[ibin+1],z1_hyper_plus_deltat,i-j)*Kn(z1_hyper_plus_deltat,j));
                  integral_conv_exp_hyper_minus_deltat += pycuda::real(spl_coef_array_deltat[ibin][k][i][j]*Mn(spl_knot_x1_vector_deltat[ibin],spl_knot_x1_vector_deltat[ibin+1],z1_hyper_minus_deltat,i-j)*Kn(z1_hyper_minus_deltat,j));
                  integral_conv_exp_trigo_deltat += spl_coef_array_deltat[ibin][k][i][j]*Mn(spl_knot_x1_vector_deltat[ibin],spl_knot_x1_vector_deltat[ibin+1],z1_trigo_deltat,i-j)*Kn(z1_trigo_deltat,j);
               }
            }
         }
      }
   }

   IT_cosh_temp_deltat[icat][iev] = 0.5*(integral_conv_exp_hyper_plus_deltat + integral_conv_exp_hyper_minus_deltat);
   IT_sinh_temp_deltat[icat][iev] = 0.5*(integral_conv_exp_hyper_plus_deltat - integral_conv_exp_hyper_minus_deltat);
   IT_cos_temp_deltat[icat][iev] = pycuda::real(integral_conv_exp_trigo_deltat);
   IT_sin_temp_deltat[icat][iev] = pycuda::imag(integral_conv_exp_trigo_deltat);

 }

__global__ void evaluate(double *data, double *out, double *check, double *options, double *re_amps, double *dirCP_asyms, double *im_amps, double *weak_phases, double *mixing_params, double *calib_params, double *mass_integrals, int Nevt) {

   int row = threadIdx.x + blockDim.x * blockIdx.x;
   if (row >= Nevt) { return;}

   int cat_index;
   if (options[1]==0) {
      if (options[2]==0) {cat_index = 0;}
      else {cat_index = 1;}
   }
   else {
      if (options[2]==0) {cat_index = 2;}
      else {cat_index = 3;}
   }

   set_buffer_options(options,cat_index);
   set_buffer_amplitudes(re_amps,dirCP_asyms,im_amps,weak_phases,mixing_params,calib_params);

   int i0 = row*12;
   decision_SSK[cat_index][row] = (int) data[0 + i0];
   decision_OS[cat_index][row] = (int) data[1 + i0];
   etamistag_SSK[cat_index][row] = data[2 + i0];
   etamistag_OS[cat_index][row] = data[3 + i0];
   m1[cat_index][row] = data[4 + i0];
   m2[cat_index][row] = data[5 + i0];
   cos1[cat_index][row] = data[6 + i0];
   cos2[cat_index][row] = data[7 + i0];
   phi[cat_index][row] = data[8 + i0];
   t[cat_index][row] = data[9 + i0];
   t_err[cat_index][row] = data[10 + i0];
   double ev_weight = data[11 + i0];

   double xm1 = (m1[cat_index][row]-1175.)/425.;
   double modulus1 = 1.+c1_mass_swave*xm1+c2_mass_swave*(2.*xm1*xm1-1.)+c3_mass_swave*(4.*xm1*xm1*xm1-3.*xm1)+c4_mass_swave*(8.*xm1*xm1*xm1*xm1-8.*xm1*xm1+1.);
   double xm2 = (m2[cat_index][row]-1175.)/425.;
   double modulus2 = 1.+c1_mass_swave*xm2+c2_mass_swave*(2.*xm2*xm2-1.)+c3_mass_swave*(4.*xm2*xm2*xm2-3.*xm2)+c4_mass_swave*(8.*xm2*xm2*xm2*xm2-8.*xm2*xm2+1.);

   if (modulus1<0 or modulus2<0) {out[row] = -10000000000;}

   else {

      set_buffer_differential_terms(mass_integrals,cat_index,row);
      set_buffer_integral_terms(cat_index,row);

      double num_fit_temp = num_fit(cat_index,row);
      double den_fit_temp = den_fit(cat_index,row);

      if (num_fit_temp/den_fit_temp<=0) {out[row] = -10000000000;}
      else {out[row] = ev_weight*(log(num_fit_temp/den_fit_temp));}

   }

   /*set_buffer_differential_terms(mass_integrals,cat_index,row);
   set_buffer_integral_terms(cat_index,row);

   double num_fit_temp = num_fit(cat_index,row);
   double den_fit_temp = den_fit(cat_index,row);

   if (num_fit_temp/den_fit_temp<=0) {out[row] = -10000000000;}
   else {out[row] = ev_weight*(log(num_fit_temp/den_fit_temp));}*/

 }


// ##########################################
// Event generator

__device__ double Ifi(int i) {

   if (i == 1) {return If1;}
   else if (i == 2) {return If2;}
   else if (i == 3) {return If3;}
   else if (i == 4) {return If4;}
   else if (i == 5) {return If5;}
   else if (i == 6) {return If6;}
   else if (i == 7) {return If7;}
   else if (i == 8) {return If8;}
   else if (i == 9) {return If9;}
   else if (i == 10) {return If10;}
   else if (i == 11) {return If11;}
   else if (i == 12) {return If12;}
   else if (i == 13) {return If13;}
   else if (i == 14) {return If14;}
   else if (i == 15) {return If15;}
   else if (i == 16) {return If16;}
   else if (i == 17) {return If17;}
   else if (i == 18) {return If18;}

   return 0.;

 }

__device__ double Igi(int i) {

   if (i == 1) {return 2.*pi;}
   else if (i == 2) {return 0.;}
   else if (i == 3) {return 0.;}
   else if (i == 4) {return pi;}
   else if (i == 5) {return 0;}
   else if (i == 6) {return pi;}
   else if (i == 7) {return 0.;}
   else if (i == 8) {return 0.;}
   else if (i == 9) {return 0.;}
   else if (i == 10) {return 0.;}
   else if (i == 11) {return 0.;}
   else if (i == 12) {return 0.;}
   else if (i == 13) {return pi;}
   else if (i == 14) {return 0.;}
   else if (i == 15) {return pi;}

   return 0.;

 }

__device__ double Ifjjphhp(int j, int jp, int h, int hp) {

   return Ifi(fjjphhpindexdict[j][jp][h][hp]);

 }

__device__ double Ighhp(int h, int hp) {

   return Igi(ghhpindexdict[h][hp]);

 }

__device__ double Gaus(double x, double mean, double sigma, bool norm = 0) {
   if (sigma == 0) return 1.e30;
   double arg = (x-mean)/sigma;
   double res = exp(-0.5*arg*arg);
   if (!norm) return res;
   return res/(2.50662827463100024*sigma);
 }

__device__ double ran_gamma(curandState localState, double a, double b) {

   if (a < 1){
      double u = curand_uniform_double(&localState);
      return ran_gamma (localState, 1.0 + a, b) * pow (u, 1.0 / a);
   }

   {
      double x, v, u;
      double d = a - 1.0 / 3.0;
      double c = (1.0 / 3.0) / sqrt (d);

      while (1){
         do{
            x = curand_normal_double(&localState);
            v = 1.0 + c * x;
         }
         while (v <= 0);
         v = v * v * v;
         u = curand_uniform_double(&localState);
         if (u < 1 - 0.0331 * x * x * x * x)
            break;
         if (log (u) < 0.5 * x * x + d * (1 - v + log (v)))
            break;
      }
      return b * d * v;
   }

 }

__device__ double ran_P_deltat(curandState localState) {

   double result;
   while (1) {
      result = ran_gamma(localState,gamma1_dt,beta1_dt);
      if (result>=0. and result<=0.1) {break;}
   }
   return result;

 }

__device__ double P_eta_SSK(double eta) {
   if (eta < 0.5) {return c_SSK*Gaus(eta,mu1_SSK,sigma1_SSK)+(1.-c_SSK)*Gaus(eta,mu2_SSK,sigma2_SSK);}
   else {return 0.;}
 }

__device__ double P_eta_OS(double eta) {
   if (eta < 0.5) {return c_OS*Gaus(eta,mu1_OS,sigma1_OS)+(1.-c_OS)*Gaus(eta,mu2_OS,sigma2_OS);}
   else {return 0.;}
 }

__global__ void get_max_P_eta_SSK(double *out) {

   double funmax = 0;
   double etavar;
   double funvar;
   for (int i=0; i<10000; i++) {
      etavar = i/20000.;
      funvar = P_eta_SSK(etavar);
      if (funvar > funmax) {funmax = funvar;}
   }
   out[0] = 1.1*funmax;
   return;

 }

__global__ void get_max_P_eta_OS(double *out) {

   double funmax = 0;
   double etavar;
   double funvar;
   for (int i=0; i<10000; i++) {
      etavar = i/20000.;
      funvar = P_eta_OS(etavar);
      if (funvar > funmax) {funmax = funvar;}
   }
   out[0] = 1.1*funmax;
   return;

 }

__global__ void set_generator(double *options, double *re_amps, double *dirCP_asyms, double *im_amps, double *weak_phases, double *mixing_params, double *calib_params, double *cond_distr_params, double *mass_integrals, double *ang_integrals) {

   set_buffer_options(options,0);
   year_opt[0] = 0;
   trig_opt[0] = 0;
   set_buffer_amplitudes(re_amps,dirCP_asyms,im_amps,weak_phases,mixing_params,calib_params);

   tag_eff_SSK = cond_distr_params[0];
   mu1_SSK = cond_distr_params[1];
   sigma1_SSK = cond_distr_params[2];
   c_SSK = cond_distr_params[3];
   mu2_SSK = cond_distr_params[4];
   sigma2_SSK = cond_distr_params[5];
   tag_eff_OS = cond_distr_params[6];
   mu1_OS = cond_distr_params[7];
   sigma1_OS = cond_distr_params[8];
   c_OS = cond_distr_params[9];
   mu2_OS = cond_distr_params[10];
   sigma2_OS = cond_distr_params[11];
   gamma1_dt = cond_distr_params[12];
   beta1_dt = cond_distr_params[13];
   c_dt = cond_distr_params[14];
   gamma2_dt = cond_distr_params[15];
   beta2_dt = cond_distr_params[16];

   Im00 = mass_integrals[0];
   Im01 = mass_integrals[1];
   Im10 = mass_integrals[2];
   Im02 = mass_integrals[3];
   Im20 = mass_integrals[4];
   Im11 = mass_integrals[5];
   Im12 = mass_integrals[6];
   Im21 = mass_integrals[7];
   Im22 = mass_integrals[8];

   Ih1Re = mass_integrals[9];
   Ih2Re = mass_integrals[10];
   Ih3Re = mass_integrals[11];
   Ih4Re = mass_integrals[12];
   Ih5Re = mass_integrals[13];
   Ih6Re = mass_integrals[14];
   Ih7Re = mass_integrals[15];
   Ih8Re = mass_integrals[16];
   Ih9Re = mass_integrals[17];
   Ih10Re = mass_integrals[18];
   Ih11Re = mass_integrals[19];
   Ih12Re = mass_integrals[20];
   Ih13Re = mass_integrals[21];
   Ih14Re = mass_integrals[22];
   Ih15Re = mass_integrals[23];
   Ih16Re = mass_integrals[24];
   Ih17Re = mass_integrals[25];
   Ih18Re = mass_integrals[26];
   Ih19Re = mass_integrals[27];
   Ih20Re = mass_integrals[28];
   Ih21Re = mass_integrals[29];
   Ih22Re = mass_integrals[30];
   Ih23Re = mass_integrals[31];
   Ih24Re = mass_integrals[32];
   Ih25Re = mass_integrals[33];
   Ih26Re = mass_integrals[34];
   Ih27Re = mass_integrals[35];
   Ih28Re = mass_integrals[36];
   Ih29Re = mass_integrals[37];
   Ih30Re = mass_integrals[38];

   Ih1Im = mass_integrals[39];
   Ih2Im = mass_integrals[40];
   Ih3Im = mass_integrals[41];
   Ih4Im = mass_integrals[42];
   Ih5Im = mass_integrals[43];
   Ih6Im = mass_integrals[44];
   Ih7Im = mass_integrals[45];
   Ih8Im = mass_integrals[46];
   Ih9Im = mass_integrals[47];
   Ih10Im = mass_integrals[48];
   Ih11Im = mass_integrals[49];
   Ih12Im = mass_integrals[50];
   Ih13Im = mass_integrals[51];
   Ih14Im = mass_integrals[52];
   Ih15Im = mass_integrals[53];
   Ih16Im = mass_integrals[54];
   Ih17Im = mass_integrals[55];
   Ih18Im = mass_integrals[56];
   Ih19Im = mass_integrals[57];
   Ih20Im = mass_integrals[58];
   Ih21Im = mass_integrals[59];

   If1 = ang_integrals[0];
   If2 = ang_integrals[1];
   If3 = ang_integrals[2];
   If4 = ang_integrals[3];
   If5 = ang_integrals[4];
   If6 = ang_integrals[5];
   If7 = ang_integrals[6];
   If8 = ang_integrals[7];
   If9 = ang_integrals[8];
   If10 = ang_integrals[9];
   If11 = ang_integrals[10];
   If12 = ang_integrals[11];
   If13 = ang_integrals[12];
   If14 = ang_integrals[13];
   If15 = ang_integrals[14];
   If16 = ang_integrals[15];
   If17 = ang_integrals[16];
   If18 = ang_integrals[17];

   reIhj1j2j1pj2pdict[0][0][0][0] = pycuda::real(pycuda::complex<double>(Ih22Re,0.));
   reIhj1j2j1pj2pdict[0][0][0][1] = pycuda::real(pycuda::complex<double>(Ih1Re,Ih1Im));
   reIhj1j2j1pj2pdict[0][0][0][2] = pycuda::real(pycuda::complex<double>(Ih2Re,Ih2Im));
   reIhj1j2j1pj2pdict[0][0][1][0] = pycuda::real(pycuda::complex<double>(Ih1Re,Ih1Im));
   reIhj1j2j1pj2pdict[0][0][1][1] = pycuda::real(pycuda::complex<double>(Ih3Re,Ih3Im));
   reIhj1j2j1pj2pdict[0][0][1][2] = pycuda::real(pycuda::complex<double>(Ih4Re,Ih4Im));
   reIhj1j2j1pj2pdict[0][0][2][0] = pycuda::real(pycuda::complex<double>(Ih2Re,Ih2Im));
   reIhj1j2j1pj2pdict[0][0][2][1] = pycuda::real(pycuda::complex<double>(Ih4Re,Ih4Im));
   reIhj1j2j1pj2pdict[0][0][2][2] = pycuda::real(pycuda::complex<double>(Ih5Re,Ih5Im));
   reIhj1j2j1pj2pdict[0][1][0][0] = pycuda::real(pycuda::complex<double>(Ih1Re,-Ih1Im));
   reIhj1j2j1pj2pdict[0][1][0][1] = pycuda::real(pycuda::complex<double>(Ih23Re,0.));
   reIhj1j2j1pj2pdict[0][1][0][2] = pycuda::real(pycuda::complex<double>(Ih6Re,Ih6Im));
   reIhj1j2j1pj2pdict[0][1][1][0] = pycuda::real(pycuda::complex<double>(Ih7Re,Ih7Im));
   reIhj1j2j1pj2pdict[0][1][1][1] = pycuda::real(pycuda::complex<double>(Ih8Re,Ih8Im));
   reIhj1j2j1pj2pdict[0][1][1][2] = pycuda::real(pycuda::complex<double>(Ih9Re,Ih9Im));
   reIhj1j2j1pj2pdict[0][1][2][0] = pycuda::real(pycuda::complex<double>(Ih10Re,Ih10Im));
   reIhj1j2j1pj2pdict[0][1][2][1] = pycuda::real(pycuda::complex<double>(Ih11Re,Ih11Im));
   reIhj1j2j1pj2pdict[0][1][2][2] = pycuda::real(pycuda::complex<double>(Ih12Re,Ih12Im));
   reIhj1j2j1pj2pdict[0][2][0][0] = pycuda::real(pycuda::complex<double>(Ih2Re,-Ih2Im));
   reIhj1j2j1pj2pdict[0][2][0][1] = pycuda::real(pycuda::complex<double>(Ih6Re,-Ih6Im));
   reIhj1j2j1pj2pdict[0][2][0][2] = pycuda::real(pycuda::complex<double>(Ih25Re,0.));
   reIhj1j2j1pj2pdict[0][2][1][0] = pycuda::real(pycuda::complex<double>(Ih10Re,-Ih10Im));
   reIhj1j2j1pj2pdict[0][2][1][1] = pycuda::real(pycuda::complex<double>(Ih13Re,Ih13Im));
   reIhj1j2j1pj2pdict[0][2][1][2] = pycuda::real(pycuda::complex<double>(Ih14Re,Ih14Im));
   reIhj1j2j1pj2pdict[0][2][2][0] = pycuda::real(pycuda::complex<double>(Ih15Re,Ih15Im));
   reIhj1j2j1pj2pdict[0][2][2][1] = pycuda::real(pycuda::complex<double>(Ih16Re,Ih16Im));
   reIhj1j2j1pj2pdict[0][2][2][2] = pycuda::real(pycuda::complex<double>(Ih17Re,Ih17Im));
   reIhj1j2j1pj2pdict[1][0][0][0] = pycuda::real(pycuda::complex<double>(Ih1Re,-Ih1Im));
   reIhj1j2j1pj2pdict[1][0][0][1] = pycuda::real(pycuda::complex<double>(Ih7Re,Ih7Im));
   reIhj1j2j1pj2pdict[1][0][0][2] = pycuda::real(pycuda::complex<double>(Ih10Re,Ih10Im));
   reIhj1j2j1pj2pdict[1][0][1][0] = pycuda::real(pycuda::complex<double>(Ih24Re,0.));
   reIhj1j2j1pj2pdict[1][0][1][1] = pycuda::real(pycuda::complex<double>(Ih8Re,Ih8Im));
   reIhj1j2j1pj2pdict[1][0][1][2] = pycuda::real(pycuda::complex<double>(Ih11Re,Ih11Im));
   reIhj1j2j1pj2pdict[1][0][2][0] = pycuda::real(pycuda::complex<double>(Ih6Re,Ih6Im));
   reIhj1j2j1pj2pdict[1][0][2][1] = pycuda::real(pycuda::complex<double>(Ih9Re,Ih9Im));
   reIhj1j2j1pj2pdict[1][0][2][2] = pycuda::real(pycuda::complex<double>(Ih12Re,Ih12Im));
   reIhj1j2j1pj2pdict[1][1][0][0] = pycuda::real(pycuda::complex<double>(Ih3Re,-Ih3Im));
   reIhj1j2j1pj2pdict[1][1][0][1] = pycuda::real(pycuda::complex<double>(Ih8Re,-Ih8Im));
   reIhj1j2j1pj2pdict[1][1][0][2] = pycuda::real(pycuda::complex<double>(Ih13Re,-Ih13Im));
   reIhj1j2j1pj2pdict[1][1][1][0] = pycuda::real(pycuda::complex<double>(Ih8Re,-Ih8Im));
   reIhj1j2j1pj2pdict[1][1][1][1] = pycuda::real(pycuda::complex<double>(Ih27Re,0.));
   reIhj1j2j1pj2pdict[1][1][1][2] = pycuda::real(pycuda::complex<double>(Ih18Re,Ih18Im));
   reIhj1j2j1pj2pdict[1][1][2][0] = pycuda::real(pycuda::complex<double>(Ih13Re,-Ih13Im));
   reIhj1j2j1pj2pdict[1][1][2][1] = pycuda::real(pycuda::complex<double>(Ih18Re,Ih18Im));
   reIhj1j2j1pj2pdict[1][1][2][2] = pycuda::real(pycuda::complex<double>(Ih19Re,Ih19Im));
   reIhj1j2j1pj2pdict[1][2][0][0] = pycuda::real(pycuda::complex<double>(Ih4Re,-Ih4Im));
   reIhj1j2j1pj2pdict[1][2][0][1] = pycuda::real(pycuda::complex<double>(Ih9Re,-Ih9Im));
   reIhj1j2j1pj2pdict[1][2][0][2] = pycuda::real(pycuda::complex<double>(Ih14Re,-Ih14Im));
   reIhj1j2j1pj2pdict[1][2][1][0] = pycuda::real(pycuda::complex<double>(Ih11Re,-Ih11Im));
   reIhj1j2j1pj2pdict[1][2][1][1] = pycuda::real(pycuda::complex<double>(Ih18Re,-Ih18Im));
   reIhj1j2j1pj2pdict[1][2][1][2] = pycuda::real(pycuda::complex<double>(Ih28Re,0.));
   reIhj1j2j1pj2pdict[1][2][2][0] = pycuda::real(pycuda::complex<double>(Ih16Re,-Ih16Im));
   reIhj1j2j1pj2pdict[1][2][2][1] = pycuda::real(pycuda::complex<double>(Ih20Re,Ih20Im));
   reIhj1j2j1pj2pdict[1][2][2][2] = pycuda::real(pycuda::complex<double>(Ih21Re,Ih21Im));
   reIhj1j2j1pj2pdict[2][0][0][0] = pycuda::real(pycuda::complex<double>(Ih2Re,-Ih2Im));
   reIhj1j2j1pj2pdict[2][0][0][1] = pycuda::real(pycuda::complex<double>(Ih10Re,-Ih10Im));
   reIhj1j2j1pj2pdict[2][0][0][2] = pycuda::real(pycuda::complex<double>(Ih15Re,Ih15Im));
   reIhj1j2j1pj2pdict[2][0][1][0] = pycuda::real(pycuda::complex<double>(Ih6Re,-Ih6Im));
   reIhj1j2j1pj2pdict[2][0][1][1] = pycuda::real(pycuda::complex<double>(Ih13Re,Ih13Im));
   reIhj1j2j1pj2pdict[2][0][1][2] = pycuda::real(pycuda::complex<double>(Ih16Re,Ih16Im));
   reIhj1j2j1pj2pdict[2][0][2][0] = pycuda::real(pycuda::complex<double>(Ih26Re,0.));
   reIhj1j2j1pj2pdict[2][0][2][1] = pycuda::real(pycuda::complex<double>(Ih14Re,Ih14Im));
   reIhj1j2j1pj2pdict[2][0][2][2] = pycuda::real(pycuda::complex<double>(Ih17Re,Ih17Im));
   reIhj1j2j1pj2pdict[2][1][0][0] = pycuda::real(pycuda::complex<double>(Ih4Re,-Ih4Im));
   reIhj1j2j1pj2pdict[2][1][0][1] = pycuda::real(pycuda::complex<double>(Ih11Re,-Ih11Im));
   reIhj1j2j1pj2pdict[2][1][0][2] = pycuda::real(pycuda::complex<double>(Ih16Re,-Ih16Im));
   reIhj1j2j1pj2pdict[2][1][1][0] = pycuda::real(pycuda::complex<double>(Ih9Re,-Ih9Im));
   reIhj1j2j1pj2pdict[2][1][1][1] = pycuda::real(pycuda::complex<double>(Ih18Re,-Ih18Im));
   reIhj1j2j1pj2pdict[2][1][1][2] = pycuda::real(pycuda::complex<double>(Ih20Re,Ih20Im));
   reIhj1j2j1pj2pdict[2][1][2][0] = pycuda::real(pycuda::complex<double>(Ih14Re,-Ih14Im));
   reIhj1j2j1pj2pdict[2][1][2][1] = pycuda::real(pycuda::complex<double>(Ih29Re,0.));
   reIhj1j2j1pj2pdict[2][1][2][2] = pycuda::real(pycuda::complex<double>(Ih21Re,Ih21Im));
   reIhj1j2j1pj2pdict[2][2][0][0] = pycuda::real(pycuda::complex<double>(Ih5Re,-Ih5Im));
   reIhj1j2j1pj2pdict[2][2][0][1] = pycuda::real(pycuda::complex<double>(Ih12Re,-Ih12Im));
   reIhj1j2j1pj2pdict[2][2][0][2] = pycuda::real(pycuda::complex<double>(Ih17Re,-Ih17Im));
   reIhj1j2j1pj2pdict[2][2][1][0] = pycuda::real(pycuda::complex<double>(Ih12Re,-Ih12Im));
   reIhj1j2j1pj2pdict[2][2][1][1] = pycuda::real(pycuda::complex<double>(Ih19Re,-Ih19Im));
   reIhj1j2j1pj2pdict[2][2][1][2] = pycuda::real(pycuda::complex<double>(Ih21Re,-Ih21Im));
   reIhj1j2j1pj2pdict[2][2][2][0] = pycuda::real(pycuda::complex<double>(Ih17Re,-Ih17Im));
   reIhj1j2j1pj2pdict[2][2][2][1] = pycuda::real(pycuda::complex<double>(Ih21Re,-Ih21Im));
   reIhj1j2j1pj2pdict[2][2][2][2] = pycuda::real(pycuda::complex<double>(Ih30Re,0.));
   imIhj1j2j1pj2pdict[0][0][0][0] = pycuda::imag(pycuda::complex<double>(Ih22Re,0.));
   imIhj1j2j1pj2pdict[0][0][0][1] = pycuda::imag(pycuda::complex<double>(Ih1Re,Ih1Im));
   imIhj1j2j1pj2pdict[0][0][0][2] = pycuda::imag(pycuda::complex<double>(Ih2Re,Ih2Im));
   imIhj1j2j1pj2pdict[0][0][1][0] = pycuda::imag(pycuda::complex<double>(Ih1Re,Ih1Im));
   imIhj1j2j1pj2pdict[0][0][1][1] = pycuda::imag(pycuda::complex<double>(Ih3Re,Ih3Im));
   imIhj1j2j1pj2pdict[0][0][1][2] = pycuda::imag(pycuda::complex<double>(Ih4Re,Ih4Im));
   imIhj1j2j1pj2pdict[0][0][2][0] = pycuda::imag(pycuda::complex<double>(Ih2Re,Ih2Im));
   imIhj1j2j1pj2pdict[0][0][2][1] = pycuda::imag(pycuda::complex<double>(Ih4Re,Ih4Im));
   imIhj1j2j1pj2pdict[0][0][2][2] = pycuda::imag(pycuda::complex<double>(Ih5Re,Ih5Im));
   imIhj1j2j1pj2pdict[0][1][0][0] = pycuda::imag(pycuda::complex<double>(Ih1Re,-Ih1Im));
   imIhj1j2j1pj2pdict[0][1][0][1] = pycuda::imag(pycuda::complex<double>(Ih23Re,0.));
   imIhj1j2j1pj2pdict[0][1][0][2] = pycuda::imag(pycuda::complex<double>(Ih6Re,Ih6Im));
   imIhj1j2j1pj2pdict[0][1][1][0] = pycuda::imag(pycuda::complex<double>(Ih7Re,Ih7Im));
   imIhj1j2j1pj2pdict[0][1][1][1] = pycuda::imag(pycuda::complex<double>(Ih8Re,Ih8Im));
   imIhj1j2j1pj2pdict[0][1][1][2] = pycuda::imag(pycuda::complex<double>(Ih9Re,Ih9Im));
   imIhj1j2j1pj2pdict[0][1][2][0] = pycuda::imag(pycuda::complex<double>(Ih10Re,Ih10Im));
   imIhj1j2j1pj2pdict[0][1][2][1] = pycuda::imag(pycuda::complex<double>(Ih11Re,Ih11Im));
   imIhj1j2j1pj2pdict[0][1][2][2] = pycuda::imag(pycuda::complex<double>(Ih12Re,Ih12Im));
   imIhj1j2j1pj2pdict[0][2][0][0] = pycuda::imag(pycuda::complex<double>(Ih2Re,-Ih2Im));
   imIhj1j2j1pj2pdict[0][2][0][1] = pycuda::imag(pycuda::complex<double>(Ih6Re,-Ih6Im));
   imIhj1j2j1pj2pdict[0][2][0][2] = pycuda::imag(pycuda::complex<double>(Ih25Re,0.));
   imIhj1j2j1pj2pdict[0][2][1][0] = pycuda::imag(pycuda::complex<double>(Ih10Re,-Ih10Im));
   imIhj1j2j1pj2pdict[0][2][1][1] = pycuda::imag(pycuda::complex<double>(Ih13Re,Ih13Im));
   imIhj1j2j1pj2pdict[0][2][1][2] = pycuda::imag(pycuda::complex<double>(Ih14Re,Ih14Im));
   imIhj1j2j1pj2pdict[0][2][2][0] = pycuda::imag(pycuda::complex<double>(Ih15Re,Ih15Im));
   imIhj1j2j1pj2pdict[0][2][2][1] = pycuda::imag(pycuda::complex<double>(Ih16Re,Ih16Im));
   imIhj1j2j1pj2pdict[0][2][2][2] = pycuda::imag(pycuda::complex<double>(Ih17Re,Ih17Im));
   imIhj1j2j1pj2pdict[1][0][0][0] = pycuda::imag(pycuda::complex<double>(Ih1Re,-Ih1Im));
   imIhj1j2j1pj2pdict[1][0][0][1] = pycuda::imag(pycuda::complex<double>(Ih7Re,Ih7Im));
   imIhj1j2j1pj2pdict[1][0][0][2] = pycuda::imag(pycuda::complex<double>(Ih10Re,Ih10Im));
   imIhj1j2j1pj2pdict[1][0][1][0] = pycuda::imag(pycuda::complex<double>(Ih24Re,0.));
   imIhj1j2j1pj2pdict[1][0][1][1] = pycuda::imag(pycuda::complex<double>(Ih8Re,Ih8Im));
   imIhj1j2j1pj2pdict[1][0][1][2] = pycuda::imag(pycuda::complex<double>(Ih11Re,Ih11Im));
   imIhj1j2j1pj2pdict[1][0][2][0] = pycuda::imag(pycuda::complex<double>(Ih6Re,Ih6Im));
   imIhj1j2j1pj2pdict[1][0][2][1] = pycuda::imag(pycuda::complex<double>(Ih9Re,Ih9Im));
   imIhj1j2j1pj2pdict[1][0][2][2] = pycuda::imag(pycuda::complex<double>(Ih12Re,Ih12Im));
   imIhj1j2j1pj2pdict[1][1][0][0] = pycuda::imag(pycuda::complex<double>(Ih3Re,-Ih3Im));
   imIhj1j2j1pj2pdict[1][1][0][1] = pycuda::imag(pycuda::complex<double>(Ih8Re,-Ih8Im));
   imIhj1j2j1pj2pdict[1][1][0][2] = pycuda::imag(pycuda::complex<double>(Ih13Re,-Ih13Im));
   imIhj1j2j1pj2pdict[1][1][1][0] = pycuda::imag(pycuda::complex<double>(Ih8Re,-Ih8Im));
   imIhj1j2j1pj2pdict[1][1][1][1] = pycuda::imag(pycuda::complex<double>(Ih27Re,0.));
   imIhj1j2j1pj2pdict[1][1][1][2] = pycuda::imag(pycuda::complex<double>(Ih18Re,Ih18Im));
   imIhj1j2j1pj2pdict[1][1][2][0] = pycuda::imag(pycuda::complex<double>(Ih13Re,-Ih13Im));
   imIhj1j2j1pj2pdict[1][1][2][1] = pycuda::imag(pycuda::complex<double>(Ih18Re,Ih18Im));
   imIhj1j2j1pj2pdict[1][1][2][2] = pycuda::imag(pycuda::complex<double>(Ih19Re,Ih19Im));
   imIhj1j2j1pj2pdict[1][2][0][0] = pycuda::imag(pycuda::complex<double>(Ih4Re,-Ih4Im));
   imIhj1j2j1pj2pdict[1][2][0][1] = pycuda::imag(pycuda::complex<double>(Ih9Re,-Ih9Im));
   imIhj1j2j1pj2pdict[1][2][0][2] = pycuda::imag(pycuda::complex<double>(Ih14Re,-Ih14Im));
   imIhj1j2j1pj2pdict[1][2][1][0] = pycuda::imag(pycuda::complex<double>(Ih11Re,-Ih11Im));
   imIhj1j2j1pj2pdict[1][2][1][1] = pycuda::imag(pycuda::complex<double>(Ih18Re,-Ih18Im));
   imIhj1j2j1pj2pdict[1][2][1][2] = pycuda::imag(pycuda::complex<double>(Ih28Re,0.));
   imIhj1j2j1pj2pdict[1][2][2][0] = pycuda::imag(pycuda::complex<double>(Ih16Re,-Ih16Im));
   imIhj1j2j1pj2pdict[1][2][2][1] = pycuda::imag(pycuda::complex<double>(Ih20Re,Ih20Im));
   imIhj1j2j1pj2pdict[1][2][2][2] = pycuda::imag(pycuda::complex<double>(Ih21Re,Ih21Im));
   imIhj1j2j1pj2pdict[2][0][0][0] = pycuda::imag(pycuda::complex<double>(Ih2Re,-Ih2Im));
   imIhj1j2j1pj2pdict[2][0][0][1] = pycuda::imag(pycuda::complex<double>(Ih10Re,-Ih10Im));
   imIhj1j2j1pj2pdict[2][0][0][2] = pycuda::imag(pycuda::complex<double>(Ih15Re,Ih15Im));
   imIhj1j2j1pj2pdict[2][0][1][0] = pycuda::imag(pycuda::complex<double>(Ih6Re,-Ih6Im));
   imIhj1j2j1pj2pdict[2][0][1][1] = pycuda::imag(pycuda::complex<double>(Ih13Re,Ih13Im));
   imIhj1j2j1pj2pdict[2][0][1][2] = pycuda::imag(pycuda::complex<double>(Ih16Re,Ih16Im));
   imIhj1j2j1pj2pdict[2][0][2][0] = pycuda::imag(pycuda::complex<double>(Ih26Re,0.));
   imIhj1j2j1pj2pdict[2][0][2][1] = pycuda::imag(pycuda::complex<double>(Ih14Re,Ih14Im));
   imIhj1j2j1pj2pdict[2][0][2][2] = pycuda::imag(pycuda::complex<double>(Ih17Re,Ih17Im));
   imIhj1j2j1pj2pdict[2][1][0][0] = pycuda::imag(pycuda::complex<double>(Ih4Re,-Ih4Im));
   imIhj1j2j1pj2pdict[2][1][0][1] = pycuda::imag(pycuda::complex<double>(Ih11Re,-Ih11Im));
   imIhj1j2j1pj2pdict[2][1][0][2] = pycuda::imag(pycuda::complex<double>(Ih16Re,-Ih16Im));
   imIhj1j2j1pj2pdict[2][1][1][0] = pycuda::imag(pycuda::complex<double>(Ih9Re,-Ih9Im));
   imIhj1j2j1pj2pdict[2][1][1][1] = pycuda::imag(pycuda::complex<double>(Ih18Re,-Ih18Im));
   imIhj1j2j1pj2pdict[2][1][1][2] = pycuda::imag(pycuda::complex<double>(Ih20Re,Ih20Im));
   imIhj1j2j1pj2pdict[2][1][2][0] = pycuda::imag(pycuda::complex<double>(Ih14Re,-Ih14Im));
   imIhj1j2j1pj2pdict[2][1][2][1] = pycuda::imag(pycuda::complex<double>(Ih29Re,0.));
   imIhj1j2j1pj2pdict[2][1][2][2] = pycuda::imag(pycuda::complex<double>(Ih21Re,Ih21Im));
   imIhj1j2j1pj2pdict[2][2][0][0] = pycuda::imag(pycuda::complex<double>(Ih5Re,-Ih5Im));
   imIhj1j2j1pj2pdict[2][2][0][1] = pycuda::imag(pycuda::complex<double>(Ih12Re,-Ih12Im));
   imIhj1j2j1pj2pdict[2][2][0][2] = pycuda::imag(pycuda::complex<double>(Ih17Re,-Ih17Im));
   imIhj1j2j1pj2pdict[2][2][1][0] = pycuda::imag(pycuda::complex<double>(Ih12Re,-Ih12Im));
   imIhj1j2j1pj2pdict[2][2][1][1] = pycuda::imag(pycuda::complex<double>(Ih19Re,-Ih19Im));
   imIhj1j2j1pj2pdict[2][2][1][2] = pycuda::imag(pycuda::complex<double>(Ih21Re,-Ih21Im));
   imIhj1j2j1pj2pdict[2][2][2][0] = pycuda::imag(pycuda::complex<double>(Ih17Re,-Ih17Im));
   imIhj1j2j1pj2pdict[2][2][2][1] = pycuda::imag(pycuda::complex<double>(Ih21Re,-Ih21Im));
   imIhj1j2j1pj2pdict[2][2][2][2] = pycuda::imag(pycuda::complex<double>(Ih30Re,0.));

 }

__device__ void set_buffer_differential_terms_gen(int iev) {

   double f1,f2,s1,s2,x1,x2;

   if (acctype == 3) {
      f1 = 1.;
      f2 = 0.;
      s1 = p0_tres_12+p1_tres_12*(t_err[0][iev]-deltatmean_tres_12);
      s2 = 1.;
      x1 = t[0][iev]/(sqrt(2.)*s1);
      x2 = t[0][iev]/(sqrt(2.)*s2);
   }
   else {
      f1 = 1.;
      f2 = 0.;
      if (year_opt == 0) {s1 = p0_tres_11+p1_tres_11*(t_err[0][iev]-deltatmean_tres_11);}
      else {s1 = p0_tres_12+p1_tres_12*(t_err[0][iev]-deltatmean_tres_12);}
      s2 = 1.;
      x1 = t[0][iev]/(sqrt(2.)*s1);
      x2 = t[0][iev]/(sqrt(2.)*s2);
   }

   pycuda::complex<double> z1_hyper_plus = s1/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z2_hyper_plus = s2/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z1_hyper_minus = s1/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z2_hyper_minus = s2/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   pycuda::complex<double> z1_trigo = s1/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq,-delta_m_freq);
   pycuda::complex<double> z2_trigo = s2/sqrt(2.)*pycuda::complex<double>(gamma_Bs_freq,-delta_m_freq);

   double conv_exp_hyper_plus = pycuda::real(f1*conv_exp(x1,z1_hyper_plus)+f2*conv_exp(x2,z2_hyper_plus));
   double conv_exp_hyper_minus = pycuda::real(f1*conv_exp(x1,z1_hyper_minus)+f2*conv_exp(x2,z2_hyper_minus));
   pycuda::complex<double> conv_exp_trigo = f1*conv_exp(x1,z1_trigo)+f2*conv_exp(x2,z2_trigo);

   T_cosh_temp[0][iev] = 0.5*(conv_exp_hyper_plus + conv_exp_hyper_minus);
   T_sinh_temp[0][iev] = 0.5*(conv_exp_hyper_plus - conv_exp_hyper_minus);
   T_cos_temp[0][iev] = pycuda::real(conv_exp_trigo);
   T_sin_temp[0][iev] = pycuda::imag(conv_exp_trigo);

   zeta_temp[0][iev] = zeta(decision_SSK[0][iev],decision_OS[0][iev],etamistag_SSK[0][iev],etamistag_OS[0][iev]);
   DCP_tzero_temp[0][iev] = DCP_tzero(decision_SSK[0][iev],decision_OS[0][iev],etamistag_SSK[0][iev],etamistag_OS[0][iev]);

   for (int i=0; i<18; ++i) {fi_cos1_temp[i][0][iev] = fi(cos1[0][iev],i+1);}
   for (int i=0; i<18; ++i) {fi_cos2_temp[i][0][iev] = fi(cos2[0][iev],i+1);}
   for (int i=0; i<15; ++i) {gi_temp[i][0][iev] = gi(phi[0][iev],i+1);}

   for (int j1=0; j1<3; ++j1) {
      for (int j2=0; j2<3; ++j2) {
         pycuda::complex<double> M_temp = Mj1j2(m1[0][iev],m2[0][iev],j1,j2);
         reMj1j2_temp[j1][j2][0][iev] = pycuda::real(M_temp);
         imMj1j2_temp[j1][j2][0][iev] = pycuda::imag(M_temp);
      }
   }

   phasespace_temp[0][iev] = phasespace(m1[0][iev],m2[0][iev]);

 }

__device__ double comp_den_toy(int j1, int j2, int h, int j1p, int j2p, int hp, int iev) { 
   return pycuda::real(ITj1j2hj1pj2php_deltat(j1,j2,h,j1p,j2p,hp,0,iev)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p))*Ighhp(h,hp)*Ifjjphhp(j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp);
 }

__device__ double den_toy(int iev) {

   return comp_den_toy(0,0,0,0,0,0,iev)+comp_den_toy(0,1,0,0,1,0,iev)+comp_den_toy(0,2,0,0,2,0,iev)+comp_den_toy(1,0,0,1,0,0,iev)+comp_den_toy(1,1,0,1,1,0,iev)
+comp_den_toy(1,1,1,1,1,1,iev)+comp_den_toy(1,1,2,1,1,2,iev)+comp_den_toy(1,2,0,1,2,0,iev)+comp_den_toy(1,2,1,1,2,1,iev)+comp_den_toy(1,2,2,1,2,2,iev)
+comp_den_toy(2,0,0,2,0,0,iev)+comp_den_toy(2,1,0,2,1,0,iev)+comp_den_toy(2,1,1,2,1,1,iev)+comp_den_toy(2,1,2,2,1,2,iev)+comp_den_toy(2,2,0,2,2,0,iev)
+comp_den_toy(2,2,1,2,2,1,iev)+comp_den_toy(2,2,2,2,2,2,iev)+comp_den_toy(2,2,3,2,2,3,iev)+comp_den_toy(2,2,4,2,2,4,iev)+2.*comp_den_toy(0,1,0,0,0,0,iev)
+2.*comp_den_toy(0,1,0,1,0,0,iev)+2.*comp_den_toy(0,1,0,2,0,0,iev)+2.*comp_den_toy(0,2,0,0,0,0,iev)+2.*comp_den_toy(0,2,0,0,1,0,iev)+2.*comp_den_toy(0,2,0,1,0,0,iev)
+2.*comp_den_toy(0,2,0,1,1,0,iev)+2.*comp_den_toy(0,2,0,2,0,0,iev)+2.*comp_den_toy(0,2,0,2,1,0,iev)+2.*comp_den_toy(1,0,0,0,0,0,iev)+2.*comp_den_toy(1,1,0,0,0,0,iev)
+2.*comp_den_toy(1,1,0,0,1,0,iev)+2.*comp_den_toy(1,1,0,1,0,0,iev)+2.*comp_den_toy(1,1,0,2,0,0,iev)+2.*comp_den_toy(1,2,0,0,0,0,iev)+2.*comp_den_toy(1,2,0,0,1,0,iev)
+2.*comp_den_toy(1,2,0,0,2,0,iev)+2.*comp_den_toy(1,2,0,1,0,0,iev)+2.*comp_den_toy(1,2,0,1,1,0,iev)+2.*comp_den_toy(1,2,0,2,0,0,iev)+2.*comp_den_toy(1,2,0,2,1,0,iev)
+2.*comp_den_toy(1,2,1,1,1,1,iev)+2.*comp_den_toy(1,2,1,2,1,1,iev)+2.*comp_den_toy(1,2,2,1,1,2,iev)+2.*comp_den_toy(1,2,2,2,1,2,iev)+2.*comp_den_toy(2,0,0,0,0,0,iev)
+2.*comp_den_toy(2,0,0,1,0,0,iev)+2.*comp_den_toy(2,1,0,0,0,0,iev)+2.*comp_den_toy(2,1,0,0,1,0,iev)+2.*comp_den_toy(2,1,0,1,0,0,iev)+2.*comp_den_toy(2,1,0,1,1,0,iev)
+2.*comp_den_toy(2,1,0,2,0,0,iev)+2.*comp_den_toy(2,1,1,1,1,1,iev)+2.*comp_den_toy(2,1,2,1,1,2,iev)+2.*comp_den_toy(2,2,0,0,0,0,iev)+2.*comp_den_toy(2,2,0,0,1,0,iev)
+2.*comp_den_toy(2,2,0,0,2,0,iev)+2.*comp_den_toy(2,2,0,1,0,0,iev)+2.*comp_den_toy(2,2,0,1,1,0,iev)+2.*comp_den_toy(2,2,0,1,2,0,iev)+2.*comp_den_toy(2,2,0,2,0,0,iev)
+2.*comp_den_toy(2,2,0,2,1,0,iev)+2.*comp_den_toy(2,2,1,1,1,1,iev)+2.*comp_den_toy(2,2,1,1,2,1,iev)+2.*comp_den_toy(2,2,1,2,1,1,iev)+2.*comp_den_toy(2,2,2,1,1,2,iev)
+2.*comp_den_toy(2,2,2,1,2,2,iev)+2.*comp_den_toy(2,2,2,2,1,2,iev);

 }

__global__ void evaluate_CondPDF(double m1_ran, double m2_ran, double cos1_ran, double cos2_ran, double phi_ran, double t_ran, double t_err_ran, int q_SSK_ran, int q_OS_ran, double eta_SSK_ran, double eta_OS_ran, double *mixing_params, double *calib_params, double *out) {

   m1[0][0] = m1_ran;
   m2[0][0] = m2_ran;
   cos1[0][0] = cos1_ran;
   cos2[0][0] = cos2_ran;
   phi[0][0] = phi_ran;
   t[0][0] = t_ran;
   t_err[0][0] = t_err_ran;
   decision_SSK[0][0] = q_SSK_ran;
   decision_OS[0][0] = q_OS_ran;
   etamistag_SSK[0][0] = eta_SSK_ran;
   etamistag_OS[0][0] = eta_OS_ran;

   gamma_Bs_freq = mixing_params[1];
   delta_gamma_freq = mixing_params[2];
   p0metac_tag_SSK = calib_params[0];
   p0metac_tag_OS = calib_params[1];
   Dp0half_tag_SSK = calib_params[2];
   Dp0half_tag_OS = calib_params[3];
   p1_tag_SSK = calib_params[4];
   p1_tag_OS = calib_params[5];
   Dp1half_tag_SSK = calib_params[6];
   Dp1half_tag_OS = calib_params[7];
   p0_tres_12 = calib_params[14];
   p1_tres_12 = calib_params[15];

   set_buffer_differential_terms_gen(0);
   set_buffer_integral_terms(0,0);

   double num_temp = num_fit(0,0)*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
   double den_temp = den_toy(0);

   if (num_temp/den_temp<=0) {out[0] = -1.e20;}
   else {out[0] = log(num_temp/den_temp);}

 }

__global__ void generateEvent(double *gendata, double max_fun_eta_SSK, double max_fun_eta_OS, double max_fun_cond, int Nevt) {

   int row = threadIdx.x + blockDim.x * blockIdx.x;
   if (row >= Nevt) { return;}

   curandState state;
   curand_init((unsigned long long)clock(), row, 0, &state);

   // Determination of the per event decay time error.
   t_err[0][row] = ran_P_deltat(state);

   // Determination of the SSK mistag probability.
   double dec_SSK_tagged = curand_uniform(&state);
   if (dec_SSK_tagged < tag_eff_SSK) {
      double etamistag_SSK_ran;
      max_fun[row] = max_fun_eta_SSK;
      while (1) {
         etamistag_SSK_ran = 0.5*curand_uniform(&state);
         fun_ran[row] = P_eta_SSK(etamistag_SSK_ran);
         dec_accepted[row] = max_fun[row]*curand_uniform(&state);
         if (fun_ran[row] > dec_accepted[row]) {break;}
         }
      etamistag_SSK[0][row] = etamistag_SSK_ran;
      }
   else {
      etamistag_SSK[0][row] = 0.5;
      }

   // Determination of the OS mistag probability.
   double dec_OS_tagged = curand_uniform(&state);
   if (dec_OS_tagged < tag_eff_OS) {
      double etamistag_OS_ran;
      max_fun[row] = max_fun_eta_OS;
      while (1) {
         etamistag_OS_ran = 0.5*curand_uniform(&state);
         fun_ran[row] = P_eta_OS(etamistag_OS_ran);
         dec_accepted[row] = max_fun[row]*curand_uniform(&state);
         if (fun_ran[row] > dec_accepted[row]) {break;}
         }
      etamistag_OS[0][row] = etamistag_OS_ran;
      }
   else {
      etamistag_OS[0][row] = 0.5;
      }

   // Determination of the decay observables.
   max_fun[row] = max_fun_cond;
   while (1) {
      if (wide_window == 1) {
         m1[0][row] = 750.+curand_uniform(&state)*(1600.-750.);
         m2[0][row] = 750.+curand_uniform(&state)*(1600.-750.);
      }
      else {
         m1[0][row] = 750.+curand_uniform(&state)*(1050.-750.);
         m2[0][row] = 750.+curand_uniform(&state)*(1050.-750.);
      }
      cos1[0][row] = -1.+curand_uniform(&state)*2.;
      cos2[0][row] = -1.+curand_uniform(&state)*2.;
      phi[0][row] = curand_uniform(&state)*2.*pi;
      t[0][row] = curand_uniform(&state)*12.;
      if (etamistag_SSK[0][row] == 0.5) {decision_SSK[0][row] = 0;}
      else {
         double d_SSK = curand_uniform(&state);
         if (d_SSK <= 0.5) {decision_SSK[0][row] = -1;}
         else {decision_SSK[0][row] = 1;}
      }
      if (etamistag_OS[0][row] == 0.5) {decision_OS[0][row] = 0;}
      else {
         double d_OS = curand_uniform(&state);
         if (d_OS <= 0.5) {decision_OS[0][row] = -1;}
         else {decision_OS[0][row] = 1;}
      }
      set_buffer_differential_terms_gen(row);
      set_buffer_integral_terms(0,row);
      dec_accepted[row] = curand_uniform(&state);
      fun_ran[row] = num_fit(0,row)/den_toy(row)*accGen(t[0][row],m1[0][row],m2[0][row],cos1[0][row],cos2[0][row],phi[0][row])/max_fun[row];
      if (fun_ran[row] > dec_accepted[row]) {break;}

   }

   int i0 = row*12;
   gendata[0 + i0] = (double) decision_SSK[0][row];
   gendata[1 + i0] = (double) decision_OS[0][row];
   gendata[2 + i0] = etamistag_SSK[0][row];
   gendata[3 + i0] = etamistag_OS[0][row];
   gendata[4 + i0] = m1[0][row];
   gendata[5 + i0] = m2[0][row];
   gendata[6 + i0] = cos1[0][row];
   gendata[7 + i0] = cos2[0][row];
   gendata[8 + i0] = phi[0][row];
   gendata[9 + i0] = t[0][row];
   gendata[10 + i0] = t_err[0][row];
   gendata[11 + i0] = 1.;

   return;

 }

__global__ void evaluate_toy(double *data, double *out, double *re_amps, double *dirCP_asyms, double *im_amps, double *weak_phases, double *mixing_params, double *calib_params, int Nevt) {

   int row = threadIdx.x + blockDim.x * blockIdx.x;
   if (row >= Nevt) { return;}

   set_buffer_amplitudes(re_amps,dirCP_asyms,im_amps,weak_phases,mixing_params,calib_params);

   int i0 = row*12;
   decision_SSK[0][row] = (int) data[0 + i0];
   decision_OS[0][row] = (int) data[1 + i0];
   etamistag_SSK[0][row] = data[2 + i0];
   etamistag_OS[0][row] = data[3 + i0];
   m1[0][row] = data[4 + i0];
   m2[0][row] = data[5 + i0];
   cos1[0][row] = data[6 + i0];
   cos2[0][row] = data[7 + i0];
   phi[0][row] = data[8 + i0];
   t[0][row] = data[9 + i0];
   t_err[0][row] = data[10 + i0];

   set_buffer_differential_terms_gen(row);
   set_buffer_integral_terms(0,row);

   double num_fit_temp = num_fit(0,row);
   double den_fit_temp = den_toy(row);

   if (num_fit_temp/den_fit_temp<=0) {out[row] = -10000000000;}
   else {out[row] = log(num_fit_temp/den_fit_temp);}

 }

__global__ void set_mass_params(double *calib_params) {

   mv = calib_params[16];
   ms = calib_params[17];
   mt = calib_params[18];
   gv = calib_params[19];
   gs = calib_params[20];
   gt = calib_params[21];
   c1_mass_swave = calib_params[22];
   c2_mass_swave = calib_params[23];
   c3_mass_swave = calib_params[24];
   c4_mass_swave = calib_params[25];
   c5_mass_swave = calib_params[26];
   c6_mass_swave = calib_params[27];
   c7_mass_swave = calib_params[28];
   c8_mass_swave = calib_params[29];
   c9_mass_swave = calib_params[30];

 }

__global__ void find_max_mass_pdf(int mpdfid, int mintnpoints, double minthlimit, double *mpdfarray) {

   int mintindex = threadIdx.x + blockDim.x * blockIdx.x;
   if (mintindex >= mintnpoints*mintnpoints) { return;}

   int im1 = mintindex / mintnpoints;
   int im2 = mintindex % mintnpoints;

   double mintstep = (minthlimit-750.)/mintnpoints;
   double m1_ = 750.+im1*mintstep;
   double m2_ = 750.+im2*mintstep;

   if (mpdfid == 0) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 1) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 2) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 3) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,2))*phasespace(m1_,m2_);}
   else if (mpdfid == 4) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 5) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 6) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,2))*phasespace(m1_,m2_);}
   else if (mpdfid == 7) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 8) {mpdfarray[mintindex] =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,2))*phasespace(m1_,m2_);}

 }

__global__ void compute_mass_integral(int mpdfid, int npoints, double minthlimit, double maxmpdf, int *mintarray) {

   int row = threadIdx.x + blockDim.x * blockIdx.x;
   if (row >= npoints) { return;}

   curandState state;
   curand_init((unsigned long long)clock(), row, 0, &state);

   double m1_ = 750.+curand_uniform(&state)*(minthlimit-750.);
   double m2_ = 750.+curand_uniform(&state)*(minthlimit-750.);
   double vertical_ = curand_uniform(&state)*maxmpdf;

   double mpdf_temp = 0;
   if (mpdfid == 0) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 1) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 2) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 3) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,2))*phasespace(m1_,m2_);}
   else if (mpdfid == 4) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 5) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 6) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,2))*phasespace(m1_,m2_);}
   else if (mpdfid == 7) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 8) {mpdf_temp =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,2))*phasespace(m1_,m2_);}

   if (vertical_ <= mpdf_temp) {mintarray[row] = 1;}
   else {mintarray[row] = 0;}

 }

__global__ void compute_mint_array(int mpdfid, int mintnpoints, double minthlimit, double *mpdfarray) {

   int mintindex = threadIdx.x + blockDim.x * blockIdx.x;
   if (mintindex >= mintnpoints*mintnpoints) { return;}

   int im1 = mintindex / mintnpoints;
   int im2 = mintindex % mintnpoints;

   double mintstep = (minthlimit-750.)/mintnpoints;
   double m1_ = 750.+im1*mintstep;
   double m2_ = 750.+im2*mintstep;
   double m1next_ = 750.+(im1+1)*mintstep;
   double m2next_ = 750.+(im2+1)*mintstep;

   double point1 = 0.;
   double point2 = 0.;
   double point3 = 0.;
   double point4 = 0.;

   if (mpdfid == 0) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 1) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 2) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 3) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,0,2))*phasespace(m1_,m2_);}
   else if (mpdfid == 4) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,0))*phasespace(m1_,m2_);}
   else if (mpdfid == 5) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 6) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,1,2))*phasespace(m1_,m2_);}
   else if (mpdfid == 7) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,1))*phasespace(m1_,m2_);}
   else if (mpdfid == 8) {point1 =  pycuda::norm(Mj1j2_unnorm(m1_,m2_,2,2))*phasespace(m1_,m2_);}

   if (mpdfid == 0) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,0,0))*phasespace(m1next_,m2_);}
   else if (mpdfid == 1) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,0,1))*phasespace(m1next_,m2_);}
   else if (mpdfid == 2) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,1,0))*phasespace(m1next_,m2_);}
   else if (mpdfid == 3) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,0,2))*phasespace(m1next_,m2_);}
   else if (mpdfid == 4) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,2,0))*phasespace(m1next_,m2_);}
   else if (mpdfid == 5) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,1,1))*phasespace(m1next_,m2_);}
   else if (mpdfid == 6) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,1,2))*phasespace(m1next_,m2_);}
   else if (mpdfid == 7) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,2,1))*phasespace(m1next_,m2_);}
   else if (mpdfid == 8) {point2 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2_,2,2))*phasespace(m1next_,m2_);}

   if (mpdfid == 0) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,0,0))*phasespace(m1_,m2next_);}
   else if (mpdfid == 1) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,0,1))*phasespace(m1_,m2next_);}
   else if (mpdfid == 2) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,1,0))*phasespace(m1_,m2next_);}
   else if (mpdfid == 3) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,0,2))*phasespace(m1_,m2next_);}
   else if (mpdfid == 4) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,2,0))*phasespace(m1_,m2next_);}
   else if (mpdfid == 5) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,1,1))*phasespace(m1_,m2next_);}
   else if (mpdfid == 6) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,1,2))*phasespace(m1_,m2next_);}
   else if (mpdfid == 7) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,2,1))*phasespace(m1_,m2next_);}
   else if (mpdfid == 8) {point3 =  pycuda::norm(Mj1j2_unnorm(m1_,m2next_,2,2))*phasespace(m1_,m2next_);}

   if (mpdfid == 0) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,0,0))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 1) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,0,1))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 2) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,1,0))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 3) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,0,2))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 4) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,2,0))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 5) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,1,1))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 6) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,1,2))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 7) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,2,1))*phasespace(m1next_,m2next_);}
   else if (mpdfid == 8) {point4 =  pycuda::norm(Mj1j2_unnorm(m1next_,m2next_,2,2))*phasespace(m1next_,m2next_);}

   mpdfarray[mintindex] = 0.25*(point1+point2+point3+point4)*mintstep*mintstep;

 }

__global__ void set_mass_integrals(double *mass_integrals) {

   Im00 = mass_integrals[0];
   Im01 = mass_integrals[1];
   Im10 = mass_integrals[2];
   Im02 = mass_integrals[3];
   Im20 = mass_integrals[4];
   Im11 = mass_integrals[5];
   Im12 = mass_integrals[6];
   Im21 = mass_integrals[7];
   Im22 = mass_integrals[8];

 }

__global__ void compute_nw(double *MCdata, int j1, int j2, int h, int j1p, int j2p, int hp, int part, int NMCevts, double *evout) {

   int row = threadIdx.x + blockDim.x * blockIdx.x;
   if (row >= NMCevts) { return;}

   int i0 = row*6;
   double m1_ = MCdata[0 + i0];
   double m2_ = MCdata[1 + i0];
   double cos1_ = MCdata[2 + i0];
   double cos2_ = MCdata[3 + i0];
   double phi_ = MCdata[4 + i0];
   double weight_ = MCdata[5 + i0];

   pycuda::complex<double> ev_nw_temp = Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Mj1j2(m1_,m2_,j1,j2)*pycuda::conj(Mj1j2(m1_,m2_,j1p,j2p))*phasespace(m1_,m2_)*fi(cos1_,(int) fjjphhpindexdict[j1][j1p][h][hp])*fi(cos2_,(int) fjjphhpindexdict[j2][j2p][h][hp])*gi(phi_,(int) ghhpindexdict[h][hp]);

   if (part == 0) {evout[row] = 100.*weight_*pycuda::real(ev_nw_temp);}
   else {evout[row] = 100.*weight_*pycuda::imag(ev_nw_temp);}

 }

__global__ void set_nw_val(double nwval, int year_opt, int trig_opt, int inw) {

   nw_comp_matrix[year_opt][trig_opt][inw] = nwval;

 }

__global__ void compute_nwcov(double *masterevarray, int numofevts, double nwcovout[][336]) {

   int nwcovlinindex = threadIdx.x + blockDim.x * blockIdx.x;
   if (nwcovlinindex >= 336*336) { return;}

   int inw = nwcovlinindex / 336;
   int jnw = nwcovlinindex % 336;

   double sumi = 0;
   double sumj = 0;
   double sumij = 0;

   for( int kev = 0; kev < numofevts; kev++ ) {
      sumi += masterevarray[inw*numofevts+kev];
      sumj += masterevarray[jnw*numofevts+kev];
      sumij += masterevarray[inw*numofevts+kev]*masterevarray[jnw*numofevts+kev];
   }

   nwcovout[inw][jnw] = sumij-sumi*sumj/numofevts;

 }

__device__ double real_acc_mint(int imint, double ma, double mb) { 

   if (imint == 0) {return pycuda::real(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,0,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 1) {return pycuda::real(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,0,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 2) {return pycuda::real(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,1,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 3) {return pycuda::real(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 4) {return pycuda::real(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 5) {return pycuda::real(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,0,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 6) {return pycuda::real(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,1,0)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 7) {return pycuda::real(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,1,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 8) {return pycuda::real(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 9) {return pycuda::real(Mj1j2(ma,mb,1,0)*pycuda::conj(Mj1j2(ma,mb,0,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 10) {return pycuda::real(Mj1j2(ma,mb,1,0)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 11) {return pycuda::real(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 12) {return pycuda::real(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,1,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 13) {return pycuda::real(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 14) {return pycuda::real(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,2,0)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 15) {return pycuda::real(Mj1j2(ma,mb,2,0)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 16) {return pycuda::real(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 17) {return pycuda::real(Mj1j2(ma,mb,1,1)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 18) {return pycuda::real(Mj1j2(ma,mb,1,1)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 19) {return pycuda::real(Mj1j2(ma,mb,1,2)*pycuda::conj(Mj1j2(ma,mb,2,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 20) {return pycuda::real(Mj1j2(ma,mb,1,2)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 21) {return pycuda::real(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,0,0)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 22) {return pycuda::real(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,0,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 23) {return pycuda::real(Mj1j2(ma,mb,1,0)*pycuda::conj(Mj1j2(ma,mb,1,0)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 24) {return pycuda::real(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,0,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 25) {return pycuda::real(Mj1j2(ma,mb,2,0)*pycuda::conj(Mj1j2(ma,mb,2,0)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 26) {return pycuda::real(Mj1j2(ma,mb,1,1)*pycuda::conj(Mj1j2(ma,mb,1,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 27) {return pycuda::real(Mj1j2(ma,mb,1,2)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 28) {return pycuda::real(Mj1j2(ma,mb,2,1)*pycuda::conj(Mj1j2(ma,mb,2,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 29) {return pycuda::real(Mj1j2(ma,mb,2,2)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   return 0.;

 }

__device__ double imag_acc_mint(int imint, double ma, double mb) { 

   if (imint == 0) {return pycuda::imag(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,0,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 1) {return pycuda::imag(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,0,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 2) {return pycuda::imag(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,1,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 3) {return pycuda::imag(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 4) {return pycuda::imag(Mj1j2(ma,mb,0,0)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 5) {return pycuda::imag(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,0,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 6) {return pycuda::imag(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,1,0)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 7) {return pycuda::imag(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,1,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 8) {return pycuda::imag(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 9) {return pycuda::imag(Mj1j2(ma,mb,1,0)*pycuda::conj(Mj1j2(ma,mb,0,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 10) {return pycuda::imag(Mj1j2(ma,mb,1,0)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 11) {return pycuda::imag(Mj1j2(ma,mb,0,1)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 12) {return pycuda::imag(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,1,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 13) {return pycuda::imag(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 14) {return pycuda::imag(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,2,0)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 15) {return pycuda::imag(Mj1j2(ma,mb,2,0)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 16) {return pycuda::imag(Mj1j2(ma,mb,0,2)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 17) {return pycuda::imag(Mj1j2(ma,mb,1,1)*pycuda::conj(Mj1j2(ma,mb,1,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 18) {return pycuda::imag(Mj1j2(ma,mb,1,1)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 19) {return pycuda::imag(Mj1j2(ma,mb,1,2)*pycuda::conj(Mj1j2(ma,mb,2,1)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   else if (imint == 20) {return pycuda::imag(Mj1j2(ma,mb,1,2)*pycuda::conj(Mj1j2(ma,mb,2,2)))*phasespace(ma,mb)*accGenMass(ma)*accGenMass(mb);}
   return 0.;

 }

__global__ void compute_acc_mint_array(int imint, int part, int mintnpoints, double minthlimit, double *mpdfarray) {

   int mintindex = threadIdx.x + blockDim.x * blockIdx.x;
   if (mintindex >= mintnpoints*mintnpoints) { return;}

   int im1 = mintindex / mintnpoints;
   int im2 = mintindex % mintnpoints;

   double mintstep = (minthlimit-750.)/mintnpoints;
   double m1_ = 750.+im1*mintstep;
   double m2_ = 750.+im2*mintstep;
   double m1next_ = 750.+(im1+1)*mintstep;
   double m2next_ = 750.+(im2+1)*mintstep;

   double point1 = 0.;
   double point2 = 0.;
   double point3 = 0.;
   double point4 = 0.;

   if (part == 0) {
      point1 = real_acc_mint(imint,m1_,m2_);
      point2 = real_acc_mint(imint,m1next_,m2_);
      point3 = real_acc_mint(imint,m1_,m2next_);
      point4 = real_acc_mint(imint,m1next_,m2next_);
   }
   else {
      point1 = imag_acc_mint(imint,m1_,m2_);
      point2 = imag_acc_mint(imint,m1next_,m2_);
      point3 = imag_acc_mint(imint,m1_,m2next_);
      point4 = imag_acc_mint(imint,m1next_,m2next_);
   }

   mpdfarray[mintindex] = 0.25*(point1+point2+point3+point4)*mintstep*mintstep;

 }

__global__ void set_all_mass_integrals(double *mass_integrals) {

   Im00 = mass_integrals[0];
   Im01 = mass_integrals[1];
   Im10 = mass_integrals[2];
   Im02 = mass_integrals[3];
   Im20 = mass_integrals[4];
   Im11 = mass_integrals[5];
   Im12 = mass_integrals[6];
   Im21 = mass_integrals[7];
   Im22 = mass_integrals[8];

   Ih1Re = mass_integrals[9];
   Ih2Re = mass_integrals[10];
   Ih3Re = mass_integrals[11];
   Ih4Re = mass_integrals[12];
   Ih5Re = mass_integrals[13];
   Ih6Re = mass_integrals[14];
   Ih7Re = mass_integrals[15];
   Ih8Re = mass_integrals[16];
   Ih9Re = mass_integrals[17];
   Ih10Re = mass_integrals[18];
   Ih11Re = mass_integrals[19];
   Ih12Re = mass_integrals[20];
   Ih13Re = mass_integrals[21];
   Ih14Re = mass_integrals[22];
   Ih15Re = mass_integrals[23];
   Ih16Re = mass_integrals[24];
   Ih17Re = mass_integrals[25];
   Ih18Re = mass_integrals[26];
   Ih19Re = mass_integrals[27];
   Ih20Re = mass_integrals[28];
   Ih21Re = mass_integrals[29];
   Ih22Re = mass_integrals[30];
   Ih23Re = mass_integrals[31];
   Ih24Re = mass_integrals[32];
   Ih25Re = mass_integrals[33];
   Ih26Re = mass_integrals[34];
   Ih27Re = mass_integrals[35];
   Ih28Re = mass_integrals[36];
   Ih29Re = mass_integrals[37];
   Ih30Re = mass_integrals[38];

   Ih1Im = mass_integrals[39];
   Ih2Im = mass_integrals[40];
   Ih3Im = mass_integrals[41];
   Ih4Im = mass_integrals[42];
   Ih5Im = mass_integrals[43];
   Ih6Im = mass_integrals[44];
   Ih7Im = mass_integrals[45];
   Ih8Im = mass_integrals[46];
   Ih9Im = mass_integrals[47];
   Ih10Im = mass_integrals[48];
   Ih11Im = mass_integrals[49];
   Ih12Im = mass_integrals[50];
   Ih13Im = mass_integrals[51];
   Ih14Im = mass_integrals[52];
   Ih15Im = mass_integrals[53];
   Ih16Im = mass_integrals[54];
   Ih17Im = mass_integrals[55];
   Ih18Im = mass_integrals[56];
   Ih19Im = mass_integrals[57];
   Ih20Im = mass_integrals[58];
   Ih21Im = mass_integrals[59];

   reIhj1j2j1pj2pdict[0][0][0][0] = pycuda::real(pycuda::complex<double>(Ih22Re,0.));
   reIhj1j2j1pj2pdict[0][0][0][1] = pycuda::real(pycuda::complex<double>(Ih1Re,Ih1Im));
   reIhj1j2j1pj2pdict[0][0][0][2] = pycuda::real(pycuda::complex<double>(Ih2Re,Ih2Im));
   reIhj1j2j1pj2pdict[0][0][1][0] = pycuda::real(pycuda::complex<double>(Ih1Re,Ih1Im));
   reIhj1j2j1pj2pdict[0][0][1][1] = pycuda::real(pycuda::complex<double>(Ih3Re,Ih3Im));
   reIhj1j2j1pj2pdict[0][0][1][2] = pycuda::real(pycuda::complex<double>(Ih4Re,Ih4Im));
   reIhj1j2j1pj2pdict[0][0][2][0] = pycuda::real(pycuda::complex<double>(Ih2Re,Ih2Im));
   reIhj1j2j1pj2pdict[0][0][2][1] = pycuda::real(pycuda::complex<double>(Ih4Re,Ih4Im));
   reIhj1j2j1pj2pdict[0][0][2][2] = pycuda::real(pycuda::complex<double>(Ih5Re,Ih5Im));
   reIhj1j2j1pj2pdict[0][1][0][0] = pycuda::real(pycuda::complex<double>(Ih1Re,-Ih1Im));
   reIhj1j2j1pj2pdict[0][1][0][1] = pycuda::real(pycuda::complex<double>(Ih23Re,0.));
   reIhj1j2j1pj2pdict[0][1][0][2] = pycuda::real(pycuda::complex<double>(Ih6Re,Ih6Im));
   reIhj1j2j1pj2pdict[0][1][1][0] = pycuda::real(pycuda::complex<double>(Ih7Re,Ih7Im));
   reIhj1j2j1pj2pdict[0][1][1][1] = pycuda::real(pycuda::complex<double>(Ih8Re,Ih8Im));
   reIhj1j2j1pj2pdict[0][1][1][2] = pycuda::real(pycuda::complex<double>(Ih9Re,Ih9Im));
   reIhj1j2j1pj2pdict[0][1][2][0] = pycuda::real(pycuda::complex<double>(Ih10Re,Ih10Im));
   reIhj1j2j1pj2pdict[0][1][2][1] = pycuda::real(pycuda::complex<double>(Ih11Re,Ih11Im));
   reIhj1j2j1pj2pdict[0][1][2][2] = pycuda::real(pycuda::complex<double>(Ih12Re,Ih12Im));
   reIhj1j2j1pj2pdict[0][2][0][0] = pycuda::real(pycuda::complex<double>(Ih2Re,-Ih2Im));
   reIhj1j2j1pj2pdict[0][2][0][1] = pycuda::real(pycuda::complex<double>(Ih6Re,-Ih6Im));
   reIhj1j2j1pj2pdict[0][2][0][2] = pycuda::real(pycuda::complex<double>(Ih25Re,0.));
   reIhj1j2j1pj2pdict[0][2][1][0] = pycuda::real(pycuda::complex<double>(Ih10Re,-Ih10Im));
   reIhj1j2j1pj2pdict[0][2][1][1] = pycuda::real(pycuda::complex<double>(Ih13Re,Ih13Im));
   reIhj1j2j1pj2pdict[0][2][1][2] = pycuda::real(pycuda::complex<double>(Ih14Re,Ih14Im));
   reIhj1j2j1pj2pdict[0][2][2][0] = pycuda::real(pycuda::complex<double>(Ih15Re,Ih15Im));
   reIhj1j2j1pj2pdict[0][2][2][1] = pycuda::real(pycuda::complex<double>(Ih16Re,Ih16Im));
   reIhj1j2j1pj2pdict[0][2][2][2] = pycuda::real(pycuda::complex<double>(Ih17Re,Ih17Im));
   reIhj1j2j1pj2pdict[1][0][0][0] = pycuda::real(pycuda::complex<double>(Ih1Re,-Ih1Im));
   reIhj1j2j1pj2pdict[1][0][0][1] = pycuda::real(pycuda::complex<double>(Ih7Re,Ih7Im));
   reIhj1j2j1pj2pdict[1][0][0][2] = pycuda::real(pycuda::complex<double>(Ih10Re,Ih10Im));
   reIhj1j2j1pj2pdict[1][0][1][0] = pycuda::real(pycuda::complex<double>(Ih24Re,0.));
   reIhj1j2j1pj2pdict[1][0][1][1] = pycuda::real(pycuda::complex<double>(Ih8Re,Ih8Im));
   reIhj1j2j1pj2pdict[1][0][1][2] = pycuda::real(pycuda::complex<double>(Ih11Re,Ih11Im));
   reIhj1j2j1pj2pdict[1][0][2][0] = pycuda::real(pycuda::complex<double>(Ih6Re,Ih6Im));
   reIhj1j2j1pj2pdict[1][0][2][1] = pycuda::real(pycuda::complex<double>(Ih9Re,Ih9Im));
   reIhj1j2j1pj2pdict[1][0][2][2] = pycuda::real(pycuda::complex<double>(Ih12Re,Ih12Im));
   reIhj1j2j1pj2pdict[1][1][0][0] = pycuda::real(pycuda::complex<double>(Ih3Re,-Ih3Im));
   reIhj1j2j1pj2pdict[1][1][0][1] = pycuda::real(pycuda::complex<double>(Ih8Re,-Ih8Im));
   reIhj1j2j1pj2pdict[1][1][0][2] = pycuda::real(pycuda::complex<double>(Ih13Re,-Ih13Im));
   reIhj1j2j1pj2pdict[1][1][1][0] = pycuda::real(pycuda::complex<double>(Ih8Re,-Ih8Im));
   reIhj1j2j1pj2pdict[1][1][1][1] = pycuda::real(pycuda::complex<double>(Ih27Re,0.));
   reIhj1j2j1pj2pdict[1][1][1][2] = pycuda::real(pycuda::complex<double>(Ih18Re,Ih18Im));
   reIhj1j2j1pj2pdict[1][1][2][0] = pycuda::real(pycuda::complex<double>(Ih13Re,-Ih13Im));
   reIhj1j2j1pj2pdict[1][1][2][1] = pycuda::real(pycuda::complex<double>(Ih18Re,Ih18Im));
   reIhj1j2j1pj2pdict[1][1][2][2] = pycuda::real(pycuda::complex<double>(Ih19Re,Ih19Im));
   reIhj1j2j1pj2pdict[1][2][0][0] = pycuda::real(pycuda::complex<double>(Ih4Re,-Ih4Im));
   reIhj1j2j1pj2pdict[1][2][0][1] = pycuda::real(pycuda::complex<double>(Ih9Re,-Ih9Im));
   reIhj1j2j1pj2pdict[1][2][0][2] = pycuda::real(pycuda::complex<double>(Ih14Re,-Ih14Im));
   reIhj1j2j1pj2pdict[1][2][1][0] = pycuda::real(pycuda::complex<double>(Ih11Re,-Ih11Im));
   reIhj1j2j1pj2pdict[1][2][1][1] = pycuda::real(pycuda::complex<double>(Ih18Re,-Ih18Im));
   reIhj1j2j1pj2pdict[1][2][1][2] = pycuda::real(pycuda::complex<double>(Ih28Re,0.));
   reIhj1j2j1pj2pdict[1][2][2][0] = pycuda::real(pycuda::complex<double>(Ih16Re,-Ih16Im));
   reIhj1j2j1pj2pdict[1][2][2][1] = pycuda::real(pycuda::complex<double>(Ih20Re,Ih20Im));
   reIhj1j2j1pj2pdict[1][2][2][2] = pycuda::real(pycuda::complex<double>(Ih21Re,Ih21Im));
   reIhj1j2j1pj2pdict[2][0][0][0] = pycuda::real(pycuda::complex<double>(Ih2Re,-Ih2Im));
   reIhj1j2j1pj2pdict[2][0][0][1] = pycuda::real(pycuda::complex<double>(Ih10Re,-Ih10Im));
   reIhj1j2j1pj2pdict[2][0][0][2] = pycuda::real(pycuda::complex<double>(Ih15Re,Ih15Im));
   reIhj1j2j1pj2pdict[2][0][1][0] = pycuda::real(pycuda::complex<double>(Ih6Re,-Ih6Im));
   reIhj1j2j1pj2pdict[2][0][1][1] = pycuda::real(pycuda::complex<double>(Ih13Re,Ih13Im));
   reIhj1j2j1pj2pdict[2][0][1][2] = pycuda::real(pycuda::complex<double>(Ih16Re,Ih16Im));
   reIhj1j2j1pj2pdict[2][0][2][0] = pycuda::real(pycuda::complex<double>(Ih26Re,0.));
   reIhj1j2j1pj2pdict[2][0][2][1] = pycuda::real(pycuda::complex<double>(Ih14Re,Ih14Im));
   reIhj1j2j1pj2pdict[2][0][2][2] = pycuda::real(pycuda::complex<double>(Ih17Re,Ih17Im));
   reIhj1j2j1pj2pdict[2][1][0][0] = pycuda::real(pycuda::complex<double>(Ih4Re,-Ih4Im));
   reIhj1j2j1pj2pdict[2][1][0][1] = pycuda::real(pycuda::complex<double>(Ih11Re,-Ih11Im));
   reIhj1j2j1pj2pdict[2][1][0][2] = pycuda::real(pycuda::complex<double>(Ih16Re,-Ih16Im));
   reIhj1j2j1pj2pdict[2][1][1][0] = pycuda::real(pycuda::complex<double>(Ih9Re,-Ih9Im));
   reIhj1j2j1pj2pdict[2][1][1][1] = pycuda::real(pycuda::complex<double>(Ih18Re,-Ih18Im));
   reIhj1j2j1pj2pdict[2][1][1][2] = pycuda::real(pycuda::complex<double>(Ih20Re,Ih20Im));
   reIhj1j2j1pj2pdict[2][1][2][0] = pycuda::real(pycuda::complex<double>(Ih14Re,-Ih14Im));
   reIhj1j2j1pj2pdict[2][1][2][1] = pycuda::real(pycuda::complex<double>(Ih29Re,0.));
   reIhj1j2j1pj2pdict[2][1][2][2] = pycuda::real(pycuda::complex<double>(Ih21Re,Ih21Im));
   reIhj1j2j1pj2pdict[2][2][0][0] = pycuda::real(pycuda::complex<double>(Ih5Re,-Ih5Im));
   reIhj1j2j1pj2pdict[2][2][0][1] = pycuda::real(pycuda::complex<double>(Ih12Re,-Ih12Im));
   reIhj1j2j1pj2pdict[2][2][0][2] = pycuda::real(pycuda::complex<double>(Ih17Re,-Ih17Im));
   reIhj1j2j1pj2pdict[2][2][1][0] = pycuda::real(pycuda::complex<double>(Ih12Re,-Ih12Im));
   reIhj1j2j1pj2pdict[2][2][1][1] = pycuda::real(pycuda::complex<double>(Ih19Re,-Ih19Im));
   reIhj1j2j1pj2pdict[2][2][1][2] = pycuda::real(pycuda::complex<double>(Ih21Re,-Ih21Im));
   reIhj1j2j1pj2pdict[2][2][2][0] = pycuda::real(pycuda::complex<double>(Ih17Re,-Ih17Im));
   reIhj1j2j1pj2pdict[2][2][2][1] = pycuda::real(pycuda::complex<double>(Ih21Re,-Ih21Im));
   reIhj1j2j1pj2pdict[2][2][2][2] = pycuda::real(pycuda::complex<double>(Ih30Re,0.));
   imIhj1j2j1pj2pdict[0][0][0][0] = pycuda::imag(pycuda::complex<double>(Ih22Re,0.));
   imIhj1j2j1pj2pdict[0][0][0][1] = pycuda::imag(pycuda::complex<double>(Ih1Re,Ih1Im));
   imIhj1j2j1pj2pdict[0][0][0][2] = pycuda::imag(pycuda::complex<double>(Ih2Re,Ih2Im));
   imIhj1j2j1pj2pdict[0][0][1][0] = pycuda::imag(pycuda::complex<double>(Ih1Re,Ih1Im));
   imIhj1j2j1pj2pdict[0][0][1][1] = pycuda::imag(pycuda::complex<double>(Ih3Re,Ih3Im));
   imIhj1j2j1pj2pdict[0][0][1][2] = pycuda::imag(pycuda::complex<double>(Ih4Re,Ih4Im));
   imIhj1j2j1pj2pdict[0][0][2][0] = pycuda::imag(pycuda::complex<double>(Ih2Re,Ih2Im));
   imIhj1j2j1pj2pdict[0][0][2][1] = pycuda::imag(pycuda::complex<double>(Ih4Re,Ih4Im));
   imIhj1j2j1pj2pdict[0][0][2][2] = pycuda::imag(pycuda::complex<double>(Ih5Re,Ih5Im));
   imIhj1j2j1pj2pdict[0][1][0][0] = pycuda::imag(pycuda::complex<double>(Ih1Re,-Ih1Im));
   imIhj1j2j1pj2pdict[0][1][0][1] = pycuda::imag(pycuda::complex<double>(Ih23Re,0.));
   imIhj1j2j1pj2pdict[0][1][0][2] = pycuda::imag(pycuda::complex<double>(Ih6Re,Ih6Im));
   imIhj1j2j1pj2pdict[0][1][1][0] = pycuda::imag(pycuda::complex<double>(Ih7Re,Ih7Im));
   imIhj1j2j1pj2pdict[0][1][1][1] = pycuda::imag(pycuda::complex<double>(Ih8Re,Ih8Im));
   imIhj1j2j1pj2pdict[0][1][1][2] = pycuda::imag(pycuda::complex<double>(Ih9Re,Ih9Im));
   imIhj1j2j1pj2pdict[0][1][2][0] = pycuda::imag(pycuda::complex<double>(Ih10Re,Ih10Im));
   imIhj1j2j1pj2pdict[0][1][2][1] = pycuda::imag(pycuda::complex<double>(Ih11Re,Ih11Im));
   imIhj1j2j1pj2pdict[0][1][2][2] = pycuda::imag(pycuda::complex<double>(Ih12Re,Ih12Im));
   imIhj1j2j1pj2pdict[0][2][0][0] = pycuda::imag(pycuda::complex<double>(Ih2Re,-Ih2Im));
   imIhj1j2j1pj2pdict[0][2][0][1] = pycuda::imag(pycuda::complex<double>(Ih6Re,-Ih6Im));
   imIhj1j2j1pj2pdict[0][2][0][2] = pycuda::imag(pycuda::complex<double>(Ih25Re,0.));
   imIhj1j2j1pj2pdict[0][2][1][0] = pycuda::imag(pycuda::complex<double>(Ih10Re,-Ih10Im));
   imIhj1j2j1pj2pdict[0][2][1][1] = pycuda::imag(pycuda::complex<double>(Ih13Re,Ih13Im));
   imIhj1j2j1pj2pdict[0][2][1][2] = pycuda::imag(pycuda::complex<double>(Ih14Re,Ih14Im));
   imIhj1j2j1pj2pdict[0][2][2][0] = pycuda::imag(pycuda::complex<double>(Ih15Re,Ih15Im));
   imIhj1j2j1pj2pdict[0][2][2][1] = pycuda::imag(pycuda::complex<double>(Ih16Re,Ih16Im));
   imIhj1j2j1pj2pdict[0][2][2][2] = pycuda::imag(pycuda::complex<double>(Ih17Re,Ih17Im));
   imIhj1j2j1pj2pdict[1][0][0][0] = pycuda::imag(pycuda::complex<double>(Ih1Re,-Ih1Im));
   imIhj1j2j1pj2pdict[1][0][0][1] = pycuda::imag(pycuda::complex<double>(Ih7Re,Ih7Im));
   imIhj1j2j1pj2pdict[1][0][0][2] = pycuda::imag(pycuda::complex<double>(Ih10Re,Ih10Im));
   imIhj1j2j1pj2pdict[1][0][1][0] = pycuda::imag(pycuda::complex<double>(Ih24Re,0.));
   imIhj1j2j1pj2pdict[1][0][1][1] = pycuda::imag(pycuda::complex<double>(Ih8Re,Ih8Im));
   imIhj1j2j1pj2pdict[1][0][1][2] = pycuda::imag(pycuda::complex<double>(Ih11Re,Ih11Im));
   imIhj1j2j1pj2pdict[1][0][2][0] = pycuda::imag(pycuda::complex<double>(Ih6Re,Ih6Im));
   imIhj1j2j1pj2pdict[1][0][2][1] = pycuda::imag(pycuda::complex<double>(Ih9Re,Ih9Im));
   imIhj1j2j1pj2pdict[1][0][2][2] = pycuda::imag(pycuda::complex<double>(Ih12Re,Ih12Im));
   imIhj1j2j1pj2pdict[1][1][0][0] = pycuda::imag(pycuda::complex<double>(Ih3Re,-Ih3Im));
   imIhj1j2j1pj2pdict[1][1][0][1] = pycuda::imag(pycuda::complex<double>(Ih8Re,-Ih8Im));
   imIhj1j2j1pj2pdict[1][1][0][2] = pycuda::imag(pycuda::complex<double>(Ih13Re,-Ih13Im));
   imIhj1j2j1pj2pdict[1][1][1][0] = pycuda::imag(pycuda::complex<double>(Ih8Re,-Ih8Im));
   imIhj1j2j1pj2pdict[1][1][1][1] = pycuda::imag(pycuda::complex<double>(Ih27Re,0.));
   imIhj1j2j1pj2pdict[1][1][1][2] = pycuda::imag(pycuda::complex<double>(Ih18Re,Ih18Im));
   imIhj1j2j1pj2pdict[1][1][2][0] = pycuda::imag(pycuda::complex<double>(Ih13Re,-Ih13Im));
   imIhj1j2j1pj2pdict[1][1][2][1] = pycuda::imag(pycuda::complex<double>(Ih18Re,Ih18Im));
   imIhj1j2j1pj2pdict[1][1][2][2] = pycuda::imag(pycuda::complex<double>(Ih19Re,Ih19Im));
   imIhj1j2j1pj2pdict[1][2][0][0] = pycuda::imag(pycuda::complex<double>(Ih4Re,-Ih4Im));
   imIhj1j2j1pj2pdict[1][2][0][1] = pycuda::imag(pycuda::complex<double>(Ih9Re,-Ih9Im));
   imIhj1j2j1pj2pdict[1][2][0][2] = pycuda::imag(pycuda::complex<double>(Ih14Re,-Ih14Im));
   imIhj1j2j1pj2pdict[1][2][1][0] = pycuda::imag(pycuda::complex<double>(Ih11Re,-Ih11Im));
   imIhj1j2j1pj2pdict[1][2][1][1] = pycuda::imag(pycuda::complex<double>(Ih18Re,-Ih18Im));
   imIhj1j2j1pj2pdict[1][2][1][2] = pycuda::imag(pycuda::complex<double>(Ih28Re,0.));
   imIhj1j2j1pj2pdict[1][2][2][0] = pycuda::imag(pycuda::complex<double>(Ih16Re,-Ih16Im));
   imIhj1j2j1pj2pdict[1][2][2][1] = pycuda::imag(pycuda::complex<double>(Ih20Re,Ih20Im));
   imIhj1j2j1pj2pdict[1][2][2][2] = pycuda::imag(pycuda::complex<double>(Ih21Re,Ih21Im));
   imIhj1j2j1pj2pdict[2][0][0][0] = pycuda::imag(pycuda::complex<double>(Ih2Re,-Ih2Im));
   imIhj1j2j1pj2pdict[2][0][0][1] = pycuda::imag(pycuda::complex<double>(Ih10Re,-Ih10Im));
   imIhj1j2j1pj2pdict[2][0][0][2] = pycuda::imag(pycuda::complex<double>(Ih15Re,Ih15Im));
   imIhj1j2j1pj2pdict[2][0][1][0] = pycuda::imag(pycuda::complex<double>(Ih6Re,-Ih6Im));
   imIhj1j2j1pj2pdict[2][0][1][1] = pycuda::imag(pycuda::complex<double>(Ih13Re,Ih13Im));
   imIhj1j2j1pj2pdict[2][0][1][2] = pycuda::imag(pycuda::complex<double>(Ih16Re,Ih16Im));
   imIhj1j2j1pj2pdict[2][0][2][0] = pycuda::imag(pycuda::complex<double>(Ih26Re,0.));
   imIhj1j2j1pj2pdict[2][0][2][1] = pycuda::imag(pycuda::complex<double>(Ih14Re,Ih14Im));
   imIhj1j2j1pj2pdict[2][0][2][2] = pycuda::imag(pycuda::complex<double>(Ih17Re,Ih17Im));
   imIhj1j2j1pj2pdict[2][1][0][0] = pycuda::imag(pycuda::complex<double>(Ih4Re,-Ih4Im));
   imIhj1j2j1pj2pdict[2][1][0][1] = pycuda::imag(pycuda::complex<double>(Ih11Re,-Ih11Im));
   imIhj1j2j1pj2pdict[2][1][0][2] = pycuda::imag(pycuda::complex<double>(Ih16Re,-Ih16Im));
   imIhj1j2j1pj2pdict[2][1][1][0] = pycuda::imag(pycuda::complex<double>(Ih9Re,-Ih9Im));
   imIhj1j2j1pj2pdict[2][1][1][1] = pycuda::imag(pycuda::complex<double>(Ih18Re,-Ih18Im));
   imIhj1j2j1pj2pdict[2][1][1][2] = pycuda::imag(pycuda::complex<double>(Ih20Re,Ih20Im));
   imIhj1j2j1pj2pdict[2][1][2][0] = pycuda::imag(pycuda::complex<double>(Ih14Re,-Ih14Im));
   imIhj1j2j1pj2pdict[2][1][2][1] = pycuda::imag(pycuda::complex<double>(Ih29Re,0.));
   imIhj1j2j1pj2pdict[2][1][2][2] = pycuda::imag(pycuda::complex<double>(Ih21Re,Ih21Im));
   imIhj1j2j1pj2pdict[2][2][0][0] = pycuda::imag(pycuda::complex<double>(Ih5Re,-Ih5Im));
   imIhj1j2j1pj2pdict[2][2][0][1] = pycuda::imag(pycuda::complex<double>(Ih12Re,-Ih12Im));
   imIhj1j2j1pj2pdict[2][2][0][2] = pycuda::imag(pycuda::complex<double>(Ih17Re,-Ih17Im));
   imIhj1j2j1pj2pdict[2][2][1][0] = pycuda::imag(pycuda::complex<double>(Ih12Re,-Ih12Im));
   imIhj1j2j1pj2pdict[2][2][1][1] = pycuda::imag(pycuda::complex<double>(Ih19Re,-Ih19Im));
   imIhj1j2j1pj2pdict[2][2][1][2] = pycuda::imag(pycuda::complex<double>(Ih21Re,-Ih21Im));
   imIhj1j2j1pj2pdict[2][2][2][0] = pycuda::imag(pycuda::complex<double>(Ih17Re,-Ih17Im));
   imIhj1j2j1pj2pdict[2][2][2][1] = pycuda::imag(pycuda::complex<double>(Ih21Re,-Ih21Im));
   imIhj1j2j1pj2pdict[2][2][2][2] = pycuda::imag(pycuda::complex<double>(Ih30Re,0.));

 }

}
