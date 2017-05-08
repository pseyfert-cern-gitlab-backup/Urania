# PIDGen package

## Introduction

PIDGen is the package to correct the PID response for MC signal samples 
based on PID calibration data (the same data as used by PIDCalib package).
It implements two alternative approaches:

  * PID resampling, where the PID response is completely replaced 
    by the one randomly generated from calibration PDFs. 

  * Transformation of PID variables, where the PID variables from the 
    simulation are transformed in such a way that they are distributed 
    as in data. (This is only available for Run1 for the moment). 

Like in PIDCalib, the PID correction is a function of track kinematics 
(momentum and pseudorapidity) and event multiplicity (number of tracks).
Unlike PIDCalib, the correction is done with an unbinned approach, where 
the calibration PDFs in four dimensions (PID, Pt, eta, Ntracsk) are described 
by a kernel density estimation procedure using the Meerkat library. 

The corrected PID response from both the PID resampling and PID variable 
transformation can be used as an input to a multivariate classifier.

The PID resampling approach has an important limitation that the PID 
variables for the same track are generated independently, and thus no 
correlations between them are reproduced. Therefore, only one PID variable 
per track can be used in the selection (correlations between variables for 
different tracks are, naturally, preserved via correlations with kinematics
of tracks). 

The approach with PID variable transformation aims to remove this limitation. 
In that case, the corrected PID variables preserve correlations with 
the output of simulation, and through the correlations in simulation the 
correlations between PID variables for the same track are reproduced 
"in the first order". This is not perfect by probably acceptable in most 
cases. The drawback of this approach is that it also relies on the 
parametrisation of PID PDFs in simulation (which are extracted from samples
that are typically much smaller than calibration data). 

More details about the approach can be found here: 
  https://indico.cern.ch/event/572934/contributions/2318786/attachments/1357558/2052812/pidcorr.pdf

## Contents of the package

PIDGen.py        - Python script for PID resampling using the 
                          calibrated PDFs stored on EOS

PIDCorr.py       - Python script for PID variable transformation

pid_resample.sh  - Example PID resampling script

pid_transform.sh - Example script for PID variable transformation

xib2lchh.py      - Another example script (Python) for variable transformation

Note that the scripts use data stored in CERN EOS, and assume that it's 
accessible at root://eoslhcb.cern.ch/ server. The location can be modified
in expert/runN/Config.py and expert/runN/ConfigMC.py files to allow local 
installation ouside CERN. 

## Creating PID PDF from calibration samples

See separate README files in the PIDGenExpert directory

## Using PIDGen with the MC samples

Generation of PID response is performed by one of the two scripts, PIDGen.py or PIDCorr.py
The scripts require many parameters (MC data location, variable names, 
location of the calibrated PID response etc. ). The sample shell scripts 
are provided, user/pid_resample.sh and user/pid_transform.py, which 
the user can modify to actually run the PID generation. 

The complete list of PID configurations available in Run 1 and Run 2 can be 
obtained by running PIDGen.py without arguments: 
```bash
> python PIDGen.py
```
