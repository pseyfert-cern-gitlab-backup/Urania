from ROOT import *
from math import *
from python_utils import *
import array
from err_poisson import pois_err


def assymGraph(xs,ys,exl,eyl,exh=0,eyh=0,title="",markerColor=1,markerStyle=20,markerSize=1):
    [myxs,myys,myexl,myeyl]=map(arr_to_vect,[xs,ys,exl,eyl])
    if exh==0: myexh=myexl
    else: myexh=arr_to_vect(exh)
    if eyh==0: myeyh=myeyl
    else: myeyh=arr_to_vect(eyh)
    n=len(xs)
    #print myxs,"\n",myys,"\n",myexl,"\n",myexh,"\n",myeyl,"\n",myeyh
    myg=TGraphAsymmErrors(n, myxs, myys, myexl, myexh, myeyl, myeyh)
    myg.SetTitle(title)
    myg.SetMarkerColor(markerColor)
    myg.SetMarkerStyle(markerStyle)
    myg.SetMarkerSize(markerSize)
    return myg


def histo_to_graph(histo,exl,eyl,exh,eyh,title="",markerColor=1,markerStyle=20,markerSize=1):
    nbins=histo.GetXaxis().GetNbins()
    xs=[]
    ys=[]
    myexl = []
    myexh = []

    if isinstance(exl,list): myexl=exl
    else:
        for i in range(nbins): myexl.append(exl)
    if isinstance(exh,list): myexh=exh
    else:
        for i in range(nbins): myexh.append(exh)

    if exh==0: myexh=myexl

    for i in range(1,nbins+1):
        yval=histo.GetBinContent(i)
#        if not yval: continue # exclude bins with no entries
        xs.append(histo.GetBinCenter(i))
        ys.append(yval)

    myg=assymGraph(xs,ys,myexl,eyl,myexh,eyh,title,markerColor,markerStyle,markerSize)
    return myg


def histo_to_graph_talcual(histo,title="",markerColor=1,markerStyle=20,markerSize=1):
    nbins=histo.GetXaxis().GetNbins()
    binwidth = histo.GetBinWidth(1)
    xs=[]
    ys=[]
    myexl = [binwidth/2.]*nbins
    myexh = [binwidth/2.]*nbins
    myeyl = []
    myeyh = []

    for i in range(1,nbins+1):
        yval=histo.GetBinContent(i)
        xs.append(histo.GetBinCenter(i))
        ys.append(yval)

        yerr = histo.GetBinError(i)
        myeyl.append(yerr)
        myeyh.append(yerr)

    myg=assymGraph(xs,ys,myexl,myeyl,myexh,myeyh,title,markerColor,markerStyle,markerSize)
    return myg


def add_graphs(title,graph1,graph2,markerColor=1,markerStyle=20,markerSize=1):

    nbins = graph1.GetN()
    if graph2.GetN()!=nbins:
        print "Cannot add graphs with different numbers of bins"
        return 0

    
    xs = graph1.GetX()
    exs = graph1.GetEXhigh()
    y1s = graph1.GetY()
    eh1s = graph1.GetEYhigh()
    el1s = graph1.GetEYlow()

    y2s = graph2.GetY()
    eh2s = graph2.GetEYhigh()
    el2s = graph2.GetEYlow()

    myxs = []
    myexs = [] 
    ys = []
    ehs = []
    els = []

    for i in range(nbins):

        y = y1s[i] + y2s[i]
        eh = sqrt(eh1s[i]**2 + eh2s[i]**2)
        el = sqrt(el1s[i]**2 + el2s[i]**2)

        myxs.append(xs[i])
        myexs.append(exs[i])
        ys.append(y)
        ehs.append(eh)
        els.append(el)

    myg=assymGraph(myxs,ys,myexs,els,myexs,ehs,title,markerColor,markerStyle,markerSize)
    return myg


def av_graphs(title,graph1,graph2,markerColor=1,markerStyle=20,markerSize=1):

    nbins = graph1.GetN()
    if graph2.GetN()!=nbins:
        print "Cannot add graphs with different numbers of bins"
        return 0

    
    xs = graph1.GetX()
    exs = graph1.GetEXhigh()
    y1s = graph1.GetY()
    eh1s = graph1.GetEYhigh()
    el1s = graph1.GetEYlow()

    y2s = graph2.GetY()
    eh2s = graph2.GetEYhigh()
    el2s = graph2.GetEYlow()

    myxs = []
    myexs = [] 
    ys = []
    ehs = []
    els = []

    for i in range(nbins):

        y = (y1s[i] + y2s[i])/2.
        eh = sqrt(eh1s[i]**2 + eh2s[i]**2)/2.
        el = sqrt(el1s[i]**2 + el2s[i]**2)/2.

        myxs.append(xs[i])
        myexs.append(exs[i])
        ys.append(y)
        ehs.append(eh)
        els.append(el)

    myg=assymGraph(myxs,ys,myexs,els,myexs,ehs,title,markerColor,markerStyle,markerSize)
    return myg


def histo_to_graph_paula(title,histo,ex,eyl,eyh):
    nbins=histo.GetXaxis().GetNbins()
    xs=[]
    ys=[]
    exs=[]
    for i in range(1,nbins+1):
        # exclude bins with no entries
        yval=histo.GetBinContent(i)
        if not yval: continue
        xs.append(histo.GetBinCenter(i))
        ys.append(yval)
        exs.append(ex)
    myg=assymGraph(xs,ys,exs,eyl,0,eyh,title)
    return myg


def histo_to_graph_poisson(title,histo):
    nbins=histo.GetXaxis().GetNbins()
    xs=[]
    ys=[]
    exs=[]
    eyh=[]
    eyl=[]
    for i in range(1,nbins+1):
        yval=histo.GetBinContent(i)
        if not yval: continue
        xs.append(histo.GetBinCenter(i))
        ys.append(yval)
        exs.append((histo.GetBinLowEdge(i+1)-histo.GetBinLowEdge(i))/2)
        yerrs = pois_err(int(yval))
        eyl.append(yerrs[0])
        eyh.append(yerrs[1])
    myg=assymGraph(xs,ys,exs,eyl,0,eyh,title)
    return myg



def graph_curve_Chi2(graph, curve, nparams):

    nbins = graph.GetN()
    nodf = nbins - nparams

    xs = graph.GetX()
    ys = graph.GetY()
    eys = graph.GetEYhigh()
    chi2 = 0


    for j in range(nbins):

        theo = curve.Eval(xs[j])
        exp = ys[j]
        err = eys[j]
        dist = (theo-exp)**2/err**2
        chi2 += dist

    return chi2, nodf
