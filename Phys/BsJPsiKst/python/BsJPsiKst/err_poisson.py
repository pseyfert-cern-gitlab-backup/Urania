import math
from ROOT import *
#from easygraphs import *
OPT="-"
import array

DEBUG=False

CONF_LEVELS={
0 : [0.000 , 1.290 ],
1 : [0.370 , 2.755 ],
2 : [0.740 , 4.255 ],
3 : [1.105 , 5.305 ],
4 : [2.340 , 6.780 ],
5 : [2.755 , 7.810 ],
6 : [3.825 , 9.280 ],
7 : [4.255 , 10.305 ],
8 : [5.305 , 11.320 ],
9 : [6.335 , 12.795 ],
10 : [6.780 , 13.810 ],
11 : [7.810 , 14.820 ],
12 : [8.830 , 16.295 ],
13 : [9.280 , 17.305 ],
14 : [10.305 , 18.320 ],
15 : [11.320 , 19.325 ],
16 : [12.335 , 20.800 ],
17 : [12.795 , 21.810 ],
18 : [13.810 , 22.820 ],
19 : [14.820 , 23.825 ],
20 : [15.835 , 25.305 ],
21 : [16.295 , 26.310 ],
22 : [17.305 , 27.320 ],
23 : [18.320 , 28.325 ],
24 : [19.325 , 29.330 ],
25 : [20.335 , 30.805 ],
26 : [20.800 , 31.815 ],
27 : [21.810 , 32.820 ],
28 : [22.820 , 33.825 ],
29 : [23.825 , 34.830 ],
30 : [24.835 , 36.310 ]}

# CONF_LEVELS={
#     0: [0.0, 1.29],
#     1: [0.37, 2.75],
#     2: [0.74, 4.25],
#     3: [1.10, 5.30],
#     4: [2.34, 6.78],
#     5: [2.75, 7.81],
#     6: [3.82, 9.28],
#     7: [4.25,10.30],
#     8: [5.30,11.32],
#     9: [6.33,12.79],
#     10:[6.78,13.81],
#     11:[7.81,14.82],
#     12:[8.83,16.29],
#     13:[9.28,17.30],
#     14:[10.30,18.32], 
#     15:[11.32,19.32],
#     16:[12.33,20.80],
#     17:[12.79,21.81],
#     18:[13.81,22.82],
#     19:[14.82,23.82],
#     20:[15.83,25.30]}

#GAUS_CL = 0.3413*2
#FC=TFeldmanCousins(GAUS_CL)

def conf_level(n):
    if not isinstance(n,int) or n<0: raise ValueError

    if n<=30: return [CONF_LEVELS[n][0],CONF_LEVELS[n][1]]
    else: return [round(n-math.sqrt(n),2),round(n+math.sqrt(n),2)]

def pois_err(n):
    if not isinstance(n,int) or n<0: raise ValueError

    #if n<=30: return [n-FC.CalculateLowerLimit(n,0),FC.CalculateUpperLimit(n,0)-n]
    if n<=30: return [n-CONF_LEVELS[n][0],CONF_LEVELS[n][1]-n]
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

