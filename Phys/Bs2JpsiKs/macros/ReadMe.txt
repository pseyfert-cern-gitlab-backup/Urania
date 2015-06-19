/////////////////////////////////////
// ***** Bs2JpsiKs - Read Me ***** //
/////////////////////////////////////

- This folder contains a collection of macros written by Kristof De Bruyn for the analysis of the effective lifetime in Bs->JpsiKs.

- The main results are obtained by the code provided in the folder "root", but these macros are used to create most of the plots given in the analysis note LHCb-ANA-2012-049

- The macros are stand-alone (*) (hence a lot of code duplication, you are warned) and only require the data samples created by the main code.
  (And in some rare cases the original DecayTreeTuple datasets.)
  To run out of the box, the data samples should be provided in the same folder as the macro.
  Otherwise you need to edit the paths in "TFile* netFile = TFile::Open(<filename>)" and "chain->Add(<filename>)"

  (*) Exceptions are:
      - Surviving_Events.C which requires you to compile RooExpAndGauss.C first
      - All Toy Models for which the run order is provided
