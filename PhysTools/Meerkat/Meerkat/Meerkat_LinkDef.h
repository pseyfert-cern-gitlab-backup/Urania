//! Definitions for Cint and PYTHON interface

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class AbsDensity;
#pragma link C++ class AbsPhaseSpace;
#pragma link C++ class AdaptiveKernelDensity;
#pragma link C++ class BinnedDensity;
#pragma link C++ class BinnedKernelDensity;
#pragma link C++ class DivideDensity;
#pragma link C++ class KernelDensity;
#pragma link C++ class HistogramDensity;
#pragma link C++ class PolynomialDensity;
#pragma link C++ class UniformDensity;
#pragma link C++ class FormulaDensity;
#pragma link C++ class FactorisedDensity;
#pragma link C++ class ProductDensity;
#pragma link C++ class SumDensity;

#pragma link C++ class CombinedPhaseSpace;
#pragma link C++ class DalitzPhaseSpace;
#pragma link C++ class ExtendedDalitzPhaseSpace;
#pragma link C++ class IntersectionPhaseSpace;
#pragma link C++ class OneDimPhaseSpace;
#pragma link C++ class ParametricPhaseSpace;

#pragma link C++ class RooMeerkatPdf; 

#endif
