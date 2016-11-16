#############################
# Credits                   #
# Author: Siim Tolk         #
# Date: Autumn 2014         #
# Mail: siim.tolk@cern.ch   #
#############################

The code in this folder was used to combined the Bs->mumu 
analysis from LHCb (3fb) and CMS(25fb).

1. Run the fit
    Modify fitComb.py to configure the fit.

    python
    from fitComb import *


2. Plot the results

    The mass scales need to be united for the combined plots. The fit, however, cannot be
    performed ont the united mass scale as the ranges for CMS and LHCb are different. Therefore
    we have to use the fit results from the nominal fit (1.)

    a) run the fit as done in 1. and look for the Results folder
    b) Under Results/ make a copy of the Results/xxx -> Results/yyy (e.g. yyy = Combined_MeV)
        
    c) In Results/yyy, run: 
        for f in *_CMS_poly*; do mv "$f" "${f/xxx/yyy}"; done;
        to change the xxx->yyy in the filenames

    c) Edit massPlot.py to plot the thing you want 
    (NB! Make sure you set: fit = Combination(fitName) with fitName = yyy ) 
    
    d) Call massPlots.py
    python
    from massPlots import *

    The plots will be saved under the created Results folder.

3. Significances, yields, etc
    See getCombSigmas.py and combine.py for multiple helper functions.





