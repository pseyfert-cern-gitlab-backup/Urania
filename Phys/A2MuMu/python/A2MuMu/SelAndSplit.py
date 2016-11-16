#!/usr/bin/env python
from ROOT import *
from Urania import PDG
from random import *
import optparse
import sys
from CutsList import *

def split(filename, treename, mc):

    f = TFile(filename, "update")
    torig = f.Get(treename)
    print torig
    cut = PreSelection + '&&' + truthMatching['Y']
    t = torig.CopyTree(cut)

    f1_name = filename.replace('.root', '_PreSel_1.root')
    f2_name = filename.replace('.root', '_PreSel_2.root')

    f1 = TFile(f1_name, "recreate")
    t1 = t.CloneTree(0)

    f2 = TFile(f2_name, "recreate")
    t2 = t.CloneTree(0)

    for entry in t:
        rand = randint(0,1)
        if rand == 0:
            t1.Fill()
        else:
            t2.Fill()

    #t.Write("",TObject.kOverwrite)
    f1.Write()
    f2.Write()

    f1.Close()
    f2.Close()
    f.Close()

def main():
    parser = optparse.OptionParser()
    parser.add_option('-i', '--input', dest='input', help='input root file')
    parser.add_option('-t', '--tree', dest='tree', help='name of the ROOT tree inside the ROOT file', default='A1/A1')
    parser.add_option('-m', '--mc', dest='mc', help='mc = 0 for BG, mc = 1 for signal MC', default=1)

    (options, args) = parser.parse_args()

    split(options.input, options.tree, options.mc)


if __name__ == "__main__":
    main()

