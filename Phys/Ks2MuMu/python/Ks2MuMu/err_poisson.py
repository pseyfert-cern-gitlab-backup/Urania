import math
from ROOT import *
from HltPython.easygraphs import *
OPT="-"
import array

DEBUG=False


CONF_LEVELS={
    0: [0.0, 1.29],
    1: [0.37, 2.75],
    2: [0.74, 4.25],
    3: [1.10, 5.30],
    4: [2.34, 6.78],
    5: [2.75, 7.81],
    6: [3.82, 9.28],
    7: [4.25,10.30],
    8: [5.30,11.32],
    9: [6.33,12.79],
    10:[6.78,13.81],
    11:[7.81,14.82],
    12:[8.83,16.29],
    13:[9.28,17.30],
    14:[10.30,18.32], 
    15:[11.32,19.32],
    16:[12.33,20.80],
    17:[12.79,21.81],
    18:[13.81,22.82],
    19:[14.82,23.82],
    20:[15.83,25.30]}

def conf_level(n):
    if not isinstance(n,int) or n<0: raise ValueError

    if n<=20: return CONF_LEVELS[n]
    else: return [round(n-math.sqrt(n),2),round(n+math.sqrt(n),2)]

def pois_err(n):
    if not isinstance(n,int) or n<0: raise ValueError

    if n<=20: return [n-CONF_LEVELS[n][0],CONF_LEVELS[n][1]-n]
    else: return [round(math.sqrt(n),2),round(math.sqrt(n),2)]

#################################################################
def err_funct(myx,myy,sx,sy):
    return 1/((myx+myy)**2)*math.sqrt((myx**2)*(sy**2)+(myy**2)*(sx**2))

def err_rate(x,xtot,CROSS=True):
    y=xtot-x
    sx=pois_err(x)
    sy=pois_err(y)
    myx=float(x)
    myy=float(y) 
    if CROSS: return min(x/float(xtot),err_funct(myx,myy,sx[0],sy[1])),min(1-x/float(xtot),err_funct(myx,myy,sx[1],sy[0]))
    else: return min(x/float(xtot),err_funct(myx,myy,sx[0],sy[0])),min(1-x/float(xtot),err_funct(myx,myy,sx[1],sy[1]))

def arr_to_vect(myarray):
    if isinstance(myarray[0],int): return array.array("i",myarray)
    else: return array.array("f",myarray)

def example1(inp,opt="both"):
    myinp=float(inp)
    xs=map(lambda x: x/myinp*x,range(inp+1))
    ys1=[]
    ys2=[]
    for i in range(inp+1):
        errs=err_rate(i,inp)
        ys1.append(errs[0])
        ys2.append(errs[1])
    myg1=graph(xs,ys1)
    myg1.SetLineColor(1)
    myg2=graph(xs,ys2)
    myg2.SetLineColor(2)
    myg=TMultiGraph()
    if opt!="h": myg.Add(myg1)
    if opt!="l": myg.Add(myg2)
    return myg

def example2(inp):
    xs=[]
    ys=[]
    exl=[]
    exh=[]
    eyl=[]
    eyh=[]
    for i in range(1,11):
        xs.append(float(i))
        ys.append(1/float(11-i))
        ef=err_rate(int(round(inp/float(11-i),0)),inp)
        eyl.append(ef[0])
        eyh.append(ef[1])
        exl.append(1/math.sqrt(12))
        exh.append(1/math.sqrt(12))
    return assymGraph(xs,ys,exl,eyl,exh,eyh)
        
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

