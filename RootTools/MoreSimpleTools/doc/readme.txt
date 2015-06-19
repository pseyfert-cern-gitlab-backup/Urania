The extra optimiser in this package works in conjunction with the SimpleTools package to add extra interactivity

Function:

1) MoreSimpleToolsOptimiser.exe
   - the all-singing, all-dancing program of fantasticness
   - will read input files from a list (see weights_example.txt)
   - will examine cuts from a list (see cut_example.txt)
   - one stage plots you a rate-vs-efficiency curve, and a lot of
     output histograms/graphs. 
   - another stage would quickly find the tightest cuts with 100% efficiency
   - will also find the optimal rectangular cuts, based on one
     of many different criterion.
   - in situations with more than one candidate per event, it is prudent to
     recalculate the number of candidate per event at each stage and apply a
     weighting. The optimiser allows for this natively.

2) example/list_vars.txt
   - explains how to make a list of all entries in your tuple
   - you can use this list to make your personal cut file for the optimiser

Key Points:

1) Make sure the version of root you are using is the same that was used
   to generate the files in the first place. For DaVinci v19+ this is the 
   5.18 series of ROOT. If you don't do this, any new tuples you make can
   have errors, or be of infinite size :S
   the example files. Take a look at the output to understand the program.

Maintained:
	This package has been designed by Rob Lambert and Connor Fitzpatrick.
	Contact rob.lambert@cern.ch with suggestions/requests/bugs

Source:
	The source is provided in the ./src directory.
	This is open-source, have a look, hack/slash steal as you wish.
	I would suggest if you want new functionality you inherit from
	the classes which exist there.
	Root is annoyingly not correctly object-orientated.
	I try to get around this where possible, but you will see obvious
	memory leaks in my code due to Root's treatment of histos etc.


R. Lambert 11/05/10
