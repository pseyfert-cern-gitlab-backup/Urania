# Tool to allow user-defined variables, binning, etc. for TrackEff evaluation

## minimal preparation script execution:
`python scripts/CreateTrackEffTables.py "2016_25ns"`

Will loop over both MC and Data, and all three methods, create a reduced tuple (with multiplicity weights), Fit in the default binning, and create plots of the results. The year_conditions define the dataset used.

### The three sub-scripts can be run separately by specifying:
* `--Prepare`: only runs the Prepare script, reducing the dataset to specified variables, weighting MC in multiplicity, and applying additional matching criteria
* `--Fit`: creates the efficiency fits in a given set of variables, mode, and method with an earlier created tuple
* `--Plot`: Plots the efficiencies from the fit, and creates data/MC correction tables in all 2D variables

### Additional options are:

* `-v`: verbose printout
* `-vROOT`: sets ROOT printout level to kInfo, default:kFatal
* `-mode "MC/Data"`: specify to only run over Data or MC; default: both
* `-simVer "SimXYZ"`: defines the Sim version of the MC; default: Sim09b
* `-method "<method1>,<method2>"`: specify method to use, separate by comma; default: Long, T, and Velo
* `-variables "<var1>,<var2>,<var3>"`: additional variables for which the efficiency dependency is evaluated; default: P, ETA, nPVs, nSPDHits
* `-variables2D "<var1>-<var2>,<var3>-<var4>"`: additional sets of 2D variables for which the efficiency dependency is evaluated. Minus connects the variables within a set, comma separates sets; default: P-ETA
* `-matchCrit "Probe:<criterion1,criterion2>;Global:<criterion3>"`: Define tighter matching criterion (when is an event considered efficient), e.g. 'Matched_GhostProb < 0.3', separation as above
* `-polarity "MagUp/MagDown"`: specify to run only over MagUp or MagDown. Does not affect the Prepare script

#### only affecting the 'Prepare' script
* `-noWeight`: set to disable reweighting MC to fit the Data multiplicity
* `-cuts "Probe:<cut1,cut2,cut3>;Tag:<cut4>;Global:<cut6,cut7>"`: Define additional cuts applied to the probe/tag muon as well as global cuts (e.g. Jpsi cuts, runNumber, etc.). Separate individual cuts by comma, categories by semicolon
* `-maxEntries 1234567`: Sets the maximum number of events used per method and charge. Needed to limit memory consumption of fit script; default: 4.e7

#### only affecting the 'Fit' script
* `-binning "<var1>:<binborder1>,<binborder2>,<binborder3>;<var2>:<binborder4>,..."`: binning scheme used for the customised variables defined as above. Bin borders separated by comma, variable+binning sets by semicolon.
* `-simFit "True/False"`: controls the use of a simultaneous fit to matched and failed events to evaluate efficiency. Should be set to False for binnings/datasets with low statistics; default: True
* `-binnedFit`: Sets the use of a binned fit to evaluate efficiency. Should be set to True for datasets with large statistics; default: False
* `-binsInFit 123`: Sets the number of bins in the fit; default: 100

#### only affecting the 'Plot' script
* `-vartitles "<var1>:<vartitle1>;<var2>:<vartitle2>"`: defines the axis title for the custom variables as defined above, standard TLatex synthax can be used
* `-maxError`: Sets the maximal acceptable error for the efficiencies; default: 0.03. If the error is >maxError, the efficiency is set to 1 +- 5%
* `-maxDeviation`: Sets the maximal deviation of the efficiency from 1; default: 0.3. If the deviation is >maxDeviation, the efficiency is set to 1 +- 5%
* `-ignoreBins "<var1>-<var2>:<bin1var1>-<bin1var2>,<bin2var1>-<bin2var2>,..."`: Sets which variable bins should be set to 1+-5%; default P-ETA:1-2,5-1". Given bins are set to 1 +- 5%




# Debugging

## Instalation of *Numpy* on lxplus

Numpy might not be installed on lxplus. So we need to install it in your own workspace:

```
cd your_favorite_directory
mkdir my_numpy
cd my_numpy
```
And then download the package. Don't forget to check for the latest version!

```
wget https://sourceforge.net/projects/numpy/files/NumPy/1.11.2/numpy-1.11.2.tar.gz
```
Unpack and install:
```
tar -xzf numpy-1.11.2.tar.gz
mkdir INSTALL
cd numpy-1.11.2
python setup.py install --prefix=your_favorite_directory/my_numpy/INSTALL
```

Now, we need to tell python where to look every time we connect to lxplus.
First, chech the correct python version by
```
which python
```
then write the path in your .bashrc:

```
echo 'export PYTHONPATH=your_favorite_directory/my_numpy/INSTALL/lib/python2.7/site-packages:$PYTHONPATH' >> ~/.bashrc
```

This installation might fail due to a missing tool called setuptools; we install it in the same way as numpy:

```
cd your_favorite_directory
mkdir my_setuptools
cd my_setuptools
wget https://pypi.python.org/packages/a9/23/720c7558ba6ad3e0f5ad01e0d6ea2288b486da32f053c73e259f7c392042/setuptools-36.0.1.zip
unzip setuptools-36.0.1.zip
mkdir INSTALL
cd setuptools-36.0.1.zip
python setup.py install  --prefix=your_favorite_directory/my_setuptools/INSTALL
echo 'export PYTHONPATH=your_favorite_directory/my_setuptools/INSTALL/lib/python2.7/site-packages:$PYTHONPATH' >> ~/.bashrc
```

## Adding global variables
 Note that adding *non-standard* ***global*** variables requires manual changes in Prepare.py Standard global variables are ```totCandidates, nTracks, nLongTracks, nTTTracks, nVeloTracks, nPVs, nSPDHits, nVeloClusters, nITClusters, nOTClusters, nTTClusters, nRich1Hits, nRich2Hits, nMuonTracks, matched``` and ```Polarity.```
 In case of doubt contact the authors.
