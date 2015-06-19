__author__ = 'P. Koppenburg'
import sys
import matplotlib.pyplot as plt

thecut = 0.552

def doplot(cuts,y,ye,title,a,b,cuts2,cuts2e,y2, ye2):
#    print title, y2
#    print y
    for i in range(len(cuts)):
        if thecut==cuts[i]: break
    plt.figure()
    plt.axvline(x=thecut,color="g")
    plt.axhline(y=y[i],color="g")
    plt.errorbar(cuts,y,yerr=ye,linestyle='-',color='c',marker='o')
    plt.errorbar(cuts2,y2,yerr=ye2,xerr=cuts2e,linestyle='None',marker='s',color='r')
    plt.ylabel(title)
    plt.xlabel("NN Cut")
    plt.axis([-1.05,1,a,b])
    plt.savefig((title+".png").replace(" ","_"))

def scanLines(l, cut, all_r ,all_re ,all_rLbpi ,all_rLbpie ,all_rLbK ,all_rLbKe ,all_Delta ,all_Deltae ):
    import re
    re_Lbpiyield = re.compile('(.*)(% grepme1)')
    re_LbKyield = re.compile('(.*)(% grepme2)')
#re_ratio = re.compile('[(\)](frac{N)[(()][(\)](Lbpi)[(\)](.*)')
    re_ratio = re.compile('(.)(frac{N)[(()](.)(Lbpi)[())](.*)')
    re_rawLbpi = re.compile('(.*)(raw)(.*)(Lbpi)(.*)')
    re_rawLbK = re.compile('(.*)(raw)(.*)(LbK)(.*)')
    re_rawD = re.compile('(.)(Delta)(.*)(raw)(.*)')

    for line in l:
        if (re_Lbpiyield.match(line)):
#            print line.split()
            lbpiy = int(line.split()[4])
            lbpiye = int((line.split()[6]).replace("\\quad",""))
            lbpiyr = float((line.split()[7]).replace("(","").replace("\%)",""))
 #           print lbpiy, lbpiye, lbpiyr
        elif (re_LbKyield.match(line)):
#            print line.split()
            lbKy = int(line.split()[4])
            lbKye = int((line.split()[6]).replace("\\quad",""))
            lbKyr = float((line.split()[7]).replace("(","").replace("\%)",""))
#            print lbKy, lbKye, lbKyr
        elif (re_ratio.match(line)):
#            print line.split()
            r = 100.*float(line.split()[4])
            re = 100.*float((line.split()[6]).replace("\\quad",""))
            all_r.append(r)
            all_re.append(re)            
#            print r, re
        elif (re_rawLbpi.match(line)):
#            print line.split()
            rLbpi = float((line.split()[4]).replace("(",""))
            rLbpie = float((line.split()[6]).replace(")\%\quad",""))
            all_rLbpi.append(rLbpi)
            all_rLbpie.append(rLbpie)
#            print rLbpi, rLbpie
        elif (re_rawLbK.match(line)):
#            print line.split()
            rLbK = float((line.split()[4]).replace("(",""))
            rLbKe = float((line.split()[6]).replace(")\%\quad",""))
            all_rLbK.append(rLbK)
            all_rLbKe.append(rLbKe)
#            print rLbK, rLbKe
        elif (re_rawD.match(line)):
#            print line.split()
            Delta = float((line.split()[5]).replace("(",""))
            Deltae = float((line.split()[7]).replace(")\%\quad",""))
            all_Delta.append(Delta)
            all_Deltae.append(Deltae)
#            print Delta, Deltae
           
    print cut,"&",lbpiy,"!",lbpiye,"& (",lbpiyr,"\\%) &",lbKy,"!",lbKye,"& (",lbKyr,"\\%) &",r,"!",re,"&",rLbpi,"!",rLbpie,"&",rLbK,"!",rLbKe,"&",Delta,"!",Deltae,"\\\\"  
    if (thecut==cut): print "\\hline"

all_r = []
all_re = []
all_rLbpi = []
all_rLbpie = []
all_rLbK = []
all_rLbKe = []
all_Delta = []
all_Deltae = []
all_r2 = []
all_re2 = []
all_rLbpi2 = []
all_rLbpie2 = []
all_rLbK2 = []
all_rLbKe2 = []
all_Delta2 = []
all_Deltae2 = []

cuts = [ -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, thecut, 0.6, 0.65, 0.7, 0.75 ]  #, 0.8, 0.9
for cut in cuts:
    if (thecut==cut): print "\\hline"
    f = open("root/test-weighting-"+str(cut))
    l = f.readlines()
    scanLines(l, cut, all_r ,all_re ,all_rLbpi ,all_rLbpie ,all_rLbK ,all_rLbKe ,all_Delta ,all_Deltae )

# more
print "\\hline"
f = open("root/test-weighting-0-0.5")
l = f.readlines()
scanLines(l, "0,0.5", all_r2 ,all_re2 ,all_rLbpi2 ,all_rLbpie2 ,all_rLbK2 ,all_rLbKe2 ,all_Delta2 ,all_Deltae2 )
f = open("root/test-weighting-0.5-0.75")
l = f.readlines()
scanLines(l, "0.5,0.75", all_r2 ,all_re2 ,all_rLbpi2 ,all_rLbpie2 ,all_rLbK2 ,all_rLbKe2 ,all_Delta2 ,all_Deltae2 )
f = open("root/test-weighting-0.75")
l = f.readlines()
scanLines(l, "0.75,1", all_r2 ,all_re2 ,all_rLbpi2 ,all_rLbpie2 ,all_rLbK2 ,all_rLbKe2 ,all_Delta2 ,all_Deltae2 )
cuts2 = [0.25,0.625,0.875]
cuts2e = [0.25,0.125,0.125]

doplot(cuts,all_r, all_re,"Ratio",8,10.5,cuts2,cuts2e,all_r2, all_re2)
doplot(cuts,all_rLbpi,all_rLbpie,"Raw Lbpi asymmetry",0,17,cuts2,cuts2e,all_rLbpi2,all_rLbpie2)
doplot(cuts,all_Delta,all_Deltae,"Raw Delta asymmetry",-5,20,cuts2,cuts2e,all_Delta2,all_Deltae2)

#f = open("root/test-weighting--1-0.0")
#l = f.readlines()
#scanLines(l, "-1,0", all_r2 ,all_re2 ,all_rLbpi2 ,all_rLbpie2 ,all_rLbK2 ,all_rLbKe2 ,all_Delta2 ,all_Deltae2 )
#cuts2.append(-0.5)
#cuts2e.append(0.5)
doplot(cuts,all_rLbK,all_rLbKe,"Raw LbK asymmetry",-6,3,cuts2,cuts2e,all_rLbK2,all_rLbKe2)
