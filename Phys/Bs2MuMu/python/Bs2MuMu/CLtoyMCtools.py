import sys

import scipy
from math import sqrt
from os import system as subshell
double = scipy.double

def generateSample(numberS, numberB, refS, refB, Name = "anything", opt = "multinomial", opt2 = "poisson"):
    """( signal entries, background entries, signalPDF, backgroundPDF )
    generates a toy MC sample acording with given PDF's and expecting
    entries
    opt = 'binomial': binomial fluctuations for each bin are done,
            (it changes then the total number of events, being in general
            diferent to numberS + numberB)
    opt = 'multinomial': multinomial fluctuation of the histogram
       is done, for a fixed total number (numberS + numberB)

    opt2 = 'poisson': fluctuates numberS & numberB.
       Only active if opt = 'multinomial'
    """
    wB = double(double(1.)/double(refB.GetSum()))
    wS = double(double(1.)/double(refS.GetSum()))
    out = refB.Clone()
    total = 0
    if opt == "binomial":
        for i in range(out.GetNbinsX()):
            for j in range(out.GetNbinsY()):
                for k in range(out.GetNbinsZ()):
                    PB = wB*refB.GetBinContent(i+1,j+1,k+1)
                    PS = wS*refS.GetBinContent(i+1,j+1,k+1)
                    newContent = 0.
                    if numberS: newContent += scipy.random.binomial(int(round(numberS)),PS)
                    if numberB: newContent += scipy.random.binomial(int(round(numberB)),PB)
                    total += newContent
                    out.SetBinContent(i+1,j+1,k+1,newContent)
    elif opt == "multinomial":
        PS, PB = [], []
        for i in range(out.GetNbinsX()):
            for j in range(out.GetNbinsY()):
                for k in range(out.GetNbinsZ()):
                    PB.append(double(wB*refB.GetBinContent(i+1,j+1,k+1)))
                    PS.append(double(wS*refS.GetBinContent(i+1,j+1,k+1)))
        PB = scipy.array(PB)
        PS = scipy.array(PS)
        PB = PB/sum(PB)
        PS = PS/sum(PB)
        #print PB,PS, sum(PB), sum(PS)
        if opt2 == "poisson":
            if numberB != 0: numberB = scipy.random.poisson(numberB)
            if numberS != 0: numberS = scipy.random.poisson(numberS)
            
        bkgContent = scipy.random.multinomial(numberB,PB)
        sigContent = scipy.random.multinomial(numberS,PS) 
   
        index = 0
        for i in range(out.GetNbinsX()):
            for j in range(out.GetNbinsY()):
                for k in range(out.GetNbinsZ()):
                    total += bkgContent[index] + sigContent[index]
                    out.SetBinContent(i+1,j+1,k+1,bkgContent[index]+sigContent[index])
                    index += 1
        out.SetEntries(total)
        print "Sample Histogram was Set to have ",out.GetEntries(), " entries"
    return out


def backgroundShifted(hbmu, BMU, hbc, BC, setB = False):
    """ ( bmubmuSAMPLE_HISTOGRAM, bmubmu Events per fb -1,BC+ jpsi munu SAMPLE_HISTOGRAM, BC + Jpsi munu Events per fb -1 )

    makes a 3D histogram, shifting each bin to its 90 % CL (acording to STATISTICS given in SAMPLE
    HISTOGRAMS) divided by 1/2 of the number of bins
    """
    
    alpha1 = BMU/hbmu.GetSum() #1/Luminosity of hb1
    alpha2 = 0
    hbShifted = hbmu.Clone()
    for i in range(hbmu.GetNbinsX()):
        for j in range(hbmu.GetNbinsY()):
            for k in range(hbmu.GetNbinsZ()):
                number1 = hbmu.GetBinContent(i+1,j+1,k+1)
                number2 = 0
                if hbc:
                    number2 = hbc.GetBinContent(i+1,j+1,k+1)
                    alpha2 = BC/hbc.GetSum()#1./Luminosity of hb2
                number = number1*alpha1 + number2*alpha2
                
                #Shifting bmubmu
                Etr = hbmu.GetSum()
                
                f = file("computebinom.input","w")
                f.write("90 "+str(int(Etr))+" " + str(int(number1))+"\n")
                f.close()
                subshell("$BSMUMUPYROOT/fortran/computebinom.exe < computebinom.input")
                f = file("fort.11", "r")
                lines = f.readlines()
                nums = lines[1].split()
                if nums[7]!= "+": errorP = float(nums[7])
                else: errorP = float(nums[8])
                f.close()
               
                error= errorP * Etr
                shift1 = 2*error/(hbmu.GetNbinsX()*hbmu.GetNbinsY()*hbmu.GetNbinsZ())
                    
                shift2 = 0
                #Shifting JpsiMunu
                if hbc:
                    Etr = hbc.GetEntries()

               
                    #if not Etr: Etr = 100
               
                    f = file("computebinom.input","w")
                    f.write("90 "+str(int(Etr))+" " + str(int(number2))+"\n")
                    f.close()
                    subshell("$BSMUMUPYROOT/fortran/computebinom.exe < computebinom.input")
                    f = file("fort.11", "r")
                    lines = f.readlines()
                    nums = lines[1].split()
                    if nums[7]!= "+": errorP = float(nums[7])
                    else: errorP = float(nums[8])
                    f.close()
               
                    error= errorP * Etr
                    shift2 = 2*error/(hbc.GetNbinsX()*hbc.GetNbinsY()*hbc.GetNbinsZ())

                #propagating error

                shift = sqrt(shift1*shift1*alpha1*alpha1 + shift2*shift2*alpha2*alpha2)
                newV = number + shift
                hbShifted.SetBinContent(i+1,j+1,k+1,newV)
    if setB:
        sum = setB
        sum = alpha1*sum
        hx = hbShifted.Project3D("x")
        sum2 = hx.GetBinContent(3) + hx.GetBinContent(4)
        if abs((sum2 - sum)/(sum2 - sum)) > 0.1:
            cte = sum*1./sum2
            for i in [3,4]:
                for j in range(1,hbmu.GetNbinsY()+1):
                    for k in range(1,hbmu.GetNbinsZ()+1):
                        hbShifted.SetBinContent(i,j,k,hbShifted.GetBinContent(i,j,k)*cte)
    
    return hbShifted
                
def backgroundShifted3(hbmu, BMU, hbc, BC, setB = False):
    """ ( bmubmuSAMPLE_HISTOGRAM, bmubmu Events per fb -1,BC+ jpsi munu SAMPLE_HISTOGRAM, BC + Jpsi munu Events per fb -1 )

    makes a 3D histogram, shifting each bin to its 90 % CL (acording to STATISTICS given in SAMPLE
    HISTOGRAMS) divided by 1/2 of the number of bins
    """
    
    alpha1 = BMU/hbmu.GetSum() #1/Luminosity of hb1
    alpha2 = 0
    hbShifted = hbmu.Clone()
    for i in range(hbmu.GetNbinsX()):
        for j in range(hbmu.GetNbinsY()):
            for k in range(hbmu.GetNbinsZ()):
                number1 = hbmu.GetBinContent(i+1,j+1,k+1)
                number2 = 0
                if hbc:
                    number2 = hbc.GetBinContent(i+1,j+1,k+1)
                    alpha2 = BC/hbc.GetSum()#1./Luminosity of hb2
                number = number1*alpha1 + number2*alpha2
                
                #Shifting bmubmu
                Etr = hbmu.GetSum()
                
                f = file("computebinom.input","w")
                f.write("90 "+str(int(Etr))+" " + str(int(number1))+"\n")
                f.close()
                subshell("$BSMUMUPYPATH/fortran/computebinom.exe < computebinom.input")
                f = file("fort.11", "r")
                lines = f.readlines()
                nums = lines[1].split()
                if nums[7]!= "+": errorP = float(nums[7])
                else: errorP = float(nums[8])
                f.close()
               
                error= errorP * Etr
                shift1 = 2*error/(hbmu.GetNbinsX()*hbmu.GetNbinsY()*hbmu.GetNbinsZ())
                    
                shift2 = 0
                #Shifting JpsiMunu
                if hbc:
                    Etr = hbc.GetEntries()

               
                    #if not Etr: Etr = 100
               
                    f = file("computebinom.input","w")
                    f.write("90 "+str(int(Etr))+" " + str(int(number2))+"\n")
                    f.close()
                    subshell("$BSMUMUPYROOT/fortran/computebinom.exe < computebinom.input")
                    f = file("fort.11", "r")
                    lines = f.readlines()
                    nums = lines[1].split()
                    if nums[7]!= "+": errorP = float(nums[7])
                    else: errorP = float(nums[8])
                    f.close()
               
                    error= errorP * Etr
                    shift2 = 2*error/(hbc.GetNbinsX()*hbc.GetNbinsY()*hbc.GetNbinsZ())

                #propagating error

                shift = sqrt(shift1*shift1*alpha1*alpha1 + shift2*shift2*alpha2*alpha2)
                newV = number + shift
                hbShifted.SetBinContent(i+1,j+1,k+1,newV)
    if setB:
        sum = setB
        sum = alpha1*sum
        hx = hbShifted.Project3D("x")
        sum2 = hx.GetBinContent(3) #+ hx.GetBinContent(4)
        if abs((sum2 - sum)/(sum2 - sum)) > 0.1:
            cte = sum*1./sum2
            for i in [3]:
                for j in range(1,hbmu.GetNbinsY()+1):
                    for k in range(1,hbmu.GetNbinsZ()+1):
                        hbShifted.SetBinContent(i,j,k,hbShifted.GetBinContent(i,j,k)*cte)
    
    return hbShifted
                
