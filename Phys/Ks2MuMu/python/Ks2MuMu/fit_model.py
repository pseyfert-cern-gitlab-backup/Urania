from ROOT import *
gStyle.SetFillColor(0)
import os
vol5="~/vol5/"
import misidfits as myf
import err_poisson as ep
from HltPython.desktop import *
from fiducial import *
f1=TFile(vol5+"/ks/ks2pipimc10.root")
t1=f1.Get("T")

## get number of bkg in signal region from fit and counting from ntuple with errors
def get_res_ents(tnew,myfit,MS1,MS2):
    ents=int(tnew.GetEntries("Mkmumu>"+str(MS1)+"&&Mkmumu<"+str(MS2)))
    eents=ep.pois_err(ents)
    print myfit.get_res(),(ents,eents[0],eents[1])
    return myfit.get_res(),(ents,eents[0],eents[1])

## create a range to evaluate the integral
def create_range(myfit,m1,m2):
    nam=str(m1)+"_"+str(m2)
    myfit.mass.setRange(nam,m1,m2)
    return nam

## obtain the integral function of the pdf between m1 and m2
def get_integ_pdf(myfit,m1,m2):
    nam=create_range(myfit,m1,m2)
    return myfit.bkgmodel.createIntegral(RooArgSet(myfit.mass),RooFit.Range(nam)).getVal()

## number of entries given by the pdf between m1 and m2: uses integral, and normalizes to total number of entries in the fit range
def eval_pdf(tnew,myfit,m1,m2,norm,nents):
    return nents*get_integ_pdf(myfit,m1,m2)/float(norm)

## get chi2 of the fitted region and of the signal region
def get_chi2s(tnew,myfit,nparams,nents,M1,M2,MS1,MS2,nbins=[75,50,25],debug=True):
    chi2b,h1,g1={},{},{}
    ## obtain normalization 
    norm = get_integ_pdf(myfit,M1,M2)
    for nb in nbins:
        h1[nb]=[0,0,0]
        g1[nb]=[0,0,0,0]
        binsize=((M2-MS2)+(MS1-M1))/float(nb) ## define the binsize to have nbins in the left+right sideb
        nb0=int((MS2-MS1)/binsize) ## number of bins in signal region
        nb1=int((MS1-M1)/binsize) ## number of bins in left sb
        nb2=int((M2-MS2)/binsize)  ## number of bins in right sb
        ## initialize histos with defined mass regions and ~same bin size
        h1[nb][0]=TH1F(str(nb)+"_0","",nb0,MS1,MS2)
        h1[nb][1]=TH1F(str(nb)+"_1","",nb1,M1,MS1)
        h1[nb][2]=TH1F(str(nb)+"_2","",nb2,MS2,M2)
        ## fill from ntuples
        tnew.Project(str(nb)+"_0","Mkmumu","Mkmumu>"+str(MS1)+"&&Mkmumu<"+str(MS2))
        tnew.Project(str(nb)+"_1","Mkmumu","Mkmumu>"+str(M1)+"&&Mkmumu<"+str(MS1))
        tnew.Project(str(nb)+"_2","Mkmumu","Mkmumu>"+str(MS2)+"&&Mkmumu<"+str(M2))
        if debug:
            print "*"*20
            print "binsize=",binsize
            print "nb0=",nb0,",nb1=",nb1,",nb2=",nb2

        chi2b[nb]=[[0,0,0],[0,0,0]]
        vals1,vals2,vals3,vals4=[],[],[],[]
        for hi in h1[nb]:
            if debug: print "_"*10
            ## loop in every histogram
            for i in range(1,hi.GetXaxis().GetNbins()+1):
                m1=hi.GetBinLowEdge(i)
                m2=hi.GetBinLowEdge(i+1)
                x=(m1+m2)/2.
                ex=(m2-m1)/2.
                ## get pdf prediction per bin, and compare to measurement
                vmeas=hi.GetBinContent(i)
                e1,e2=ep.pois_err(int(vmeas))
                vfit=eval_pdf(tnew,myfit,m1,m2,norm,nents)
                ## add to control graphs
                vals1.append([x,vmeas,ex,e1,ex,e2])
                error = sqrt(e1**2 + e2**2)/sqrt(2)
                ## chi2 per bin
                cont=(vfit-vmeas)**2/error**2
                ## add chi2 to corresponding output
                if h1[nb].index(hi):
                    chi2b[nb][1][0]+=cont
                    if h1[nb].index(hi)==1: vals2.append([x,vfit])
                    else: vals3.append([x,vfit])
                else:
                    vals4.append([x,vfit])
                    chi2b[nb][0][0]+=cont
                if debug:
                    print "="*10
                    print "m1=",m1,",m2=",m2
                    print "vfit=",vfit,",vmeas=",vmeas
                    print "e1=",e1,"e2=",e2
                    print "cont=",cont

        ## create control graphs
        vals1.sort();vals2.sort();vals3.sort()
        xs1,ys1,exs1,eys1,exs2,eys2=map(lambda i: map(lambda x: x[i],vals1),range(6))
        xs2,ys2=map(lambda i: map(lambda x: x[i],vals2),range(2))
        xs3,ys3=map(lambda i: map(lambda x: x[i],vals3),range(2))
        xs4,ys4=map(lambda i: map(lambda x: x[i],vals4),range(2))
        xs4.insert(0,xs2[-1]);ys4.insert(0,ys2[-1])
        xs4.insert(-1,xs3[0]);ys4.insert(-1,ys3[0])
        g1[nb][0]=ep.assymGraph(xs1,ys1,exs1,eys1,exs2,eys2)
        g1[nb][1]=ep.assymGraph(xs2,ys2,len(xs2)*[0.],len(xs2)*[0.])
        g1[nb][2]=ep.assymGraph(xs3,ys3,len(xs3)*[0.],len(xs3)*[0.])
        g1[nb][3]=ep.assymGraph(xs4,ys4,len(xs4)*[0.],len(xs4)*[0.])
        g1[nb][0].GetHistogram().GetXaxis().SetTitle("K_{s}^{0} mass (MeV/c^{2})");g1[nb][0].GetHistogram().GetYaxis().SetTitle("Events")
        g1[nb][1].SetLineColor(4);g1[nb][1].SetLineWidth(2)
        g1[nb][2].SetLineColor(4);g1[nb][2].SetLineWidth(2)
        g1[nb][3].SetLineColor(4);g1[nb][3].SetLineWidth(2);g1[nb][3].SetLineStyle(2)
        ## signal region ndf and chi2/ndf
        chi2b[nb][0][1]=nb0
        chi2b[nb][0][2]=chi2b[nb][0][0]/float(chi2b[nb][0][1])
        ## fit region ndf and chi2/ndf
        chi2b[nb][1][1]=nb1+nb2-nparams #### == NDOF
        chi2b[nb][1][2]=chi2b[nb][1][0]/float(chi2b[nb][1][1])
    for nb in nbins: print nb,chi2b[nb]
    return chi2b,g1

## loops to be done to check fit models and stability
## beginning of the fit region
M1s=[465,470,475]
M2=550
MS1=485
MS2=510

## fitting models
models=["expo","npoly","breit","landau"]# + ["lorentz"]
## number of free pars per model (to later compute the ndf)
nparamsm={"expo":1,"npoly":2,"landau":2,"breit":2,"lorentz":4}
## different types of dcf: any decay, any decay with BDT bins, pion decaying after Tstations, pion decaying in the magnet, pion decaying very soon, both pions decaying
conds=["nocond","BDTbins","2_1","4_1","3_1","dcf_dcf"]
conddict={"2_1":"((mu1mcdecc==2&&mu2mcdecc==1)||(mu1mcdecc==1&&mu2mcdecc==2))","4_1":"((mu1mcdecc==4&&mu2mcdecc==1)||(mu1mcdecc==1&&mu2mcdecc==4))","3_1":"((mu1mcdecc==3&&mu2mcdecc==1)||(mu1mcdecc==1&&mu2mcdecc==3))","dcf_dcf":"(mu1mcdecc!=1&&mu2mcdecc!=1)"}

##nbins for chi2 computation
nbins=[75,50,25]

## definition of BDT bins, with 25% efficiency each
#bdtbins=[0.2,0.208, 0.216, 0.225, 0.235, 0.244, 0.257, 0.270, 0.288, 0.314,1]
bdtbins=[0.2,0.221,0.244,0.278,1]
lenb=len(bdtbins)

## get properties in a particular type of dcf and/or BDT bin
def get_props(tnew):
    out,g1s,myfitsd={},{},{}
    ## loop in the fit starting point
    for M1 in M1s:
        out[M1],g1s[M1],myfitsd[M1]={},{},{}
        ## total number of entries
        nents=tnew.GetEntries("Mkmumu>"+str(M1)+"&&Mkmumu<"+str(M2))
        ## loop in the different fitting models
        for model in models:
            print "="*10
            print str(M1)+"_"+str(model)
            print "="*10
            ## proceed to fit
            myfit=myf.fit_bkg(tnew,cuts="",mvar="Mkmumu",eopt=model,m1=M1,m2=MS1,m3=MS2,m4=M2)
            ## chi2 of the fitting regions and signal
            print "m_o_o_m"*10
            chi2s,g1=get_chi2s(tnew,myfit,nparamsm[model],nents,M1,M2,MS1,MS2)
            print "m_o_o_m"*10
            ## get predicted bkg and measured
            res_ents=get_res_ents(tnew,myfit,MS1,MS2)
            ## store everyting
            out[M1][model]=[chi2s,res_ents,myfit.get_params()]
            g1s[M1][model]=g1
            myfitsd[M1][model]=myfit
            
    return out,g1s,myfitsd


def myeval():
    ## create a tmp root file to store new ntuples
    fnew=TFile("/tmp/jcidvida/erasme2.root","RECREATE")
    ## output dicts
    out,g1s,myfitsd={},{},{}
    ## loop in types of dcf
    for cond in conds:
        ## if 1, loop also in bdt bins
        if cond=="BDTbins":
            out[cond],g1s[cond],myfitsd[cond]={},{},{}
            for i in range(1,lenb): 
                print "#"*10
                print str(cond)+"_"+str(i)
                print "#"*10
                ## create tuple, including simply bdt bins
                tnew=t1.CopyTree("Mkmumu>465&&BDTDA>"+str(bdtbins[i-1])+"&&BDTDA<"+str(bdtbins[i]))
                out[cond][i],g1s[cond][i],myfitsd[cond][i]=get_props(tnew)
        else:
            ## create tuple, including dcf type or simply wright mass region
            if cond=="nocond": tnew=t1.CopyTree("Mkmumu>465")
            else: tnew=t1.CopyTree("Mkmumu>465&&"+conddict[cond])
            
            print "#"*10
            print str(cond)
            print "#"*10
            out[cond],g1s[cond],myfitsd[cond]=get_props(tnew)

    ## first store fit quality values
    pickleSave(out,"fit_res.out")
    ## now loop and save plots in fitplots.root
    fplots=TFile("fitplots.root","RECREATE")
    for cond in conds:
        ## if 1, loop also in bdt bins
        if cond=="BDTbins":
            ## loop also in fit starting point and model
            for i in range(1,lenb): 
                for M1 in M1s:
                    for model in models:
                        name=str(cond)+"_"+str(i)+"_"+str(M1)+"_"+str(model)
                        c1=myfitsd[cond][i][M1][model].plot()
                        c1.SetName("f_"+name)
                        c1.Write()
                        for nb in nbins:
                            for j in range(4):
                                g1s[cond][i][M1][model][nb][j].SetName("g_"+name+"_"+str(nb)+"_"+str(j))
                                g1s[cond][i][M1][model][nb][j].Write()
                                
        else:
            ## loop in fit starting point and model
            for M1 in M1s:
                for model in models:
                    name=str(cond)+"_"+str(M1)+"_"+str(model)
                    c1=myfitsd[cond][M1][model].plot()
                    c1.SetName("f_"+name)
                    c1.Write()
                    for nb in nbins:
                        for j in range(4):
                            g1s[cond][M1][model][nb][j].SetName("g_"+name+"_"+str(nb)+"_"+str(j))
                            g1s[cond][M1][model][nb][j].Write()


    ## close fplots and return
    fplots.Close()
    return out,myfitsd,g1s


out,myfitsd,g1s=myeval()
print out
