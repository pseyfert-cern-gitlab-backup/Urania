#! /usr/bin/env python

from ROOT import TH1F
from math import exp
import sys
from ROOT import *
from MCLimit import *
from XTuple import XTuple

parameters = {
    "split"  : 0.5,
    "lambda" : 5.,
    "nbkg"   : 500,
    "toys"   : 100000
    }

def prepare_hist(splitval) :
  lam = parameters['lambda']
  sigpdf = TH1F("sigpdf","sigpdf",1,0.,1.)
  bkgpdf = TH1F("bkgpdf","bkgpdf",1,0.,1.)

  sigpdf.SetBinContent(1,splitval)
#  sigpdf.SetBinContent(1,1.-splitval)

## exp
  bkgpdf.SetBinContent(1,(1.-exp(-lam*splitval))/(1.-exp(-lam)))

## 1/x^2
##  bkgpdf.SetBinContent(1,1./(1./0.1/0.1-1./1.1/1.1)*(1./0.1/0.1-1./splitval/splitval))


#  bkgpdf.SetBinContent(1,1.-bkgpdf.GetBinContent(1))
  return sigpdf, bkgpdf

if 1<len(sys.argv) :
  parameters["split"] = float(sys.argv[1])

if 2<len(sys.argv) :
  parameters["nbkg"] = float(sys.argv[2])

if 3<len(sys.argv) :
  parameters["lambda"] = float(sys.argv[3])

ISTYLE = 1

splitval = parameters["split"]
sigpdf, bkgpdf = prepare_hist(splitval)
bkg = csm_template(0)
tmpp = bkgpdf.Clone()
summm = tmpp.GetSum()
tmpp.Scale(1./summm)
bkg.make(tmpp,parameters["nbkg"]*summm,0,0,"test")

nul = csm_model()
bkg.add_to(nul)
nul.set_interpolation_style("test",ISTYLE)

sighyp = {}
test = {}

def datahist() :
  data = TH1F("datahist","datahist",1,0.,1.)
  data.SetBinContent(1,bkgpdf.GetBinContent(1)*parameters["nbkg"]);
  #data.SetBinContent(2,bkgpdf.GetBinContent(2)*parameters["nbkg"]);
  c3 = TCanvas()
  c3.cd()
  data.Draw()
  c3.Print("data.eps")
  return data

thedata = datahist()

def make_sighyp(br):
  sighyp[br] = csm_template(0)
  tmp = sigpdf.Clone()
  summ = tmp.GetSum()
  tmp.Scale(1./summ)
  sighyp[br].make(tmp,br*summ,0,1,"test")
  test[br] = csm_model()
  sighyp[br].add_to(test[br])
  bkg.add_to(test[br])
  test[br].set_interpolation_style("test",ISTYLE)

  CL = mclimit_csm()
  CL.set_null_hypothesis(nul)
  CL.set_test_hypothesis(test[br])
  CL.set_null_hypothesis_pe(nul)
  CL.set_test_hypothesis_pe(test[br])
  CL.set_datahist(thedata,"data")
  CL.set_npe(parameters["toys"])
  CL.run_pseudoexperiments()
  return CL

c1 = TCanvas()
c1.cd()
sigpdf.Draw()
c1.Print("sig.eps")

c2 = TCanvas()
c2.cd()
bkgpdf.Draw()
c2.Print("bkg.eps")



ff = TFile("output_"+str(parameters["split"])+".root","recreate")
tup = XTuple("output_"+str(parameters["split"]),labels = ["br/F","exp_cls/F","exp_cls_plus/F","exp_cls_minus/F"])
ntup = TNtuple("output","output","br:exp_cls:exp_cls_plus:exp_cls_minus")

steps = 0.8
low = 0.
foundc = False
foundp = False
foundm = False
target = 0.1
br = low
while not (foundc and foundp and foundm):
    CL = make_sighyp(br)
    tup.fillItem("br",br)
    tup.fillItem("exp_cls",CL.clsexpbmed())
    tup.fillItem("exp_cls_plus",CL.clsexpbp1())
    tup.fillItem("exp_cls_minus",CL.clsexpbm1())
    ntup.Fill(br,CL.clsexpbmed(),CL.clsexpbp1(),CL.clsexpbm1())
    tup.fill()
    thisvalc = CL.clsexpbmed()
    thisvalp = CL.clsexpbp1()
    thisvalm = CL.clsexpbm1()
    if (not foundm) and (thisvalm<0.1):
      foundm = True
      limitm = br-steps + steps * (lastvalm-target)/(lastvalm-thisvalm)
    if (not foundc) and (thisvalc<0.1):
      foundc = True
      limitc = br-steps + steps * (lastvalc-target)/(lastvalc-thisvalc)
    if (not foundp) and (thisvalp<0.1):
      foundp = True
      limitp = br-steps + steps * (lastvalp-target)/(lastvalp-thisvalp)

    lastvalc = thisvalc
    lastvalp = thisvalp
    lastvalm = thisvalm
    br = br + steps

f = open(str('output_DOWN_split'+str(parameters["split"])+"_nevt"+str(parameters["nbkg"])), 'w')
f.write(str(parameters["split"]))
f.write("    " )
f.write(str(limitp) )
f.write("    " )
f.write(str(limitc))
f.write("    ")
f.write(str(limitm))
f.write("\n")
f.close()

ff.WriteTObject(ntup)
ff.Close()



tup.close()



























