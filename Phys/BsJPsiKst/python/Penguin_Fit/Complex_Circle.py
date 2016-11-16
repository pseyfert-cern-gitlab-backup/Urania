################################
## ***** Complex Circle ***** ##
################################

### Macro written by Kristof De Bruyn for "Implications of Penguin Topologies" Paper ###
# - Calculate contours


################################
## ***** Import Classes ***** ##
################################
import math
import numpy


##################################
## ***** General Settings ***** ##
##################################

### Plot Settings ###
# Annihilation
#plotRad = math.sqrt(2.) * 2.5 # Visual range
#plotPoints = 361 # Number of points on curve
#plotSplit = -180 # Point where to split Re - Im to Abs - Ang (Default Range [-pi, pi])

# Penguins
plotRad = 1. # Visual range
plotPoints = 361 # Number of points on curve
#plotSplit = 0 # Point where to split Re - Im to Abs - Ang (Default Range [-pi, pi])
plotSplit = -180 # Point where to split Re - Im to Abs - Ang (Default Range [-pi, pi])


#############################
### Calculate Coordinates ###
#############################

### Transformations ###
def Morph_Invert(ReCon, ImCon):
    # In case of non "concentric" circles, invert one of the contours
    RePar = []
    ImPar = []
    for i in range(0, len(ReCon)):
      RePar.append(ReCon[len(ReCon)-1 -i])
      ImPar.append(ImCon[len(ReCon)-1 -i])
    return RePar, ImPar

def Morph_DeltaPhi(AbsCon, AngCon, eps, gam):
    # Convert Abs Contour to DeltaPhi Contour
    DelPar = []
    for i in range(0, len(AbsCon)):
      # ignoring normalisastion
      theta = AngCon[i] * math.pi/180
      sinDel = 2 * eps * AbsCon[i] * math.cos(theta) * math.sin(gam) + pow(eps * AbsCon[i],2) * math.sin(2 * gam)
      cosDel = 1 + 2 * eps * AbsCon[i] * math.cos(theta) * math.cos(gam) + pow(eps * AbsCon[i],2) * math.cos(2 * gam)
      delta = math.atan2(sinDel, cosDel) * 180/math.pi
      DelPar.append(delta)
      #print AbsCon[i], theta, "=>", sinDel, cosDel, delta
    return DelPar

def Morph_Fit(RePar, ImPar, flag = "Def"):
    # STEP 1: Convert Points
    AbsTemp = []
    AngTemp = []
    jumpI = -1
    jumpII = -1
    for i in range(0, len(RePar)):
      AbsTemp.append(math.sqrt(pow(RePar[i],2) + pow(ImPar[i],2)))
      angle = math.atan2(ImPar[i], RePar[i]) * 180/math.pi
      if (angle < plotSplit):
        angle = angle + 360
      AngTemp.append(angle)
      if (i>0 and jumpI<0 and (math.fabs(AngTemp[i] - AngTemp[i-1]) > 270)):
        jumpI = i
      if (i>jumpI and (math.fabs(AngTemp[i] - AngTemp[i-1]) > 270)):
        jumpII = i

    # STEP 2: Rotate Points
    AbsPar = []
    AngPar = []
    # No jump point
    if (jumpI<0):
      AbsPar = AbsTemp
      AngPar = AngTemp
    else:
      for i in range(jumpI, len(AbsTemp)):
        if (i==jumpII):
          if (flag=="Def"):
            AbsPar.append(AbsPar[-1])
            AngPar.append(plotSplit)
            AbsPar.append(0)
            AngPar.append(plotSplit)
            AbsPar.append(0)
            AngPar.append(plotSplit + 360)
            AbsPar.append(AbsTemp[i])
            AngPar.append(plotSplit + 360)
          else:
            # Inverse
            AbsPar.append(AbsPar[-1])
            AngPar.append(plotSplit + 360)
            AbsPar.append(1.1*plotRad)
            AngPar.append(plotSplit + 360)
            AbsPar.append(1.1*plotRad)
            AngPar.append(plotSplit)
            AbsPar.append(AbsTemp[i])
            AngPar.append(plotSplit)
        AbsPar.append(AbsTemp[i])
        AngPar.append(AngTemp[i])
      for i in range(0, jumpI):
        AbsPar.append(AbsTemp[i])
        AngPar.append(AngTemp[i])
      # Close contour
      if (flag=="Def"):
        AbsPar.extend([AbsTemp[jumpI-1], 0, 0, AbsTemp[jumpI]])
        AngPar.extend([plotSplit+361, plotSplit+361, plotSplit-1, plotSplit-1])
      else:
        # Inverse
        AbsPar.extend([AbsTemp[jumpI-1], 1.1*plotRad, 1.1*plotRad, AbsTemp[jumpI]])
        AngPar.extend([plotSplit-1, plotSplit-1, plotSplit+361, plotSplit+361])

    # STEP: Return
    return AbsPar, AngPar

### Patch ###
def Gen_Patch(AbsRef, AngRef, rmin, fmin, rmax, fmax):
    # Create small patch from reference
    AngPar = []
    AbsPar = []
    # Glue
    AngPar.append(fmin)
    AbsPar.append(rmin)
    # Visual Range
    for i in range(0, len(AngRef)):
      if (AngRef[i] >= fmin and AngRef[i] <= fmax):
        AngPar.append(AngRef[i])
        AbsPar.append(AbsRef[i])
    # Glue
    AngPar.append(fmax)
    AbsPar.append(rmax)
    return AbsPar, AngPar

### Generators ###
def Gen_Contour(input):
    # Generate the part of the circular contour that is inside the visual range
    # The circle is parametrised by its radius rad and centre (x0,y0)
    # Visual range is defined as the circle with radius plotRad
    
    x0 = input[0]
    y0 = input[1]
    rad = input[2]
    
    # STEP 0: Sanity Check & Special Cases
    if (rad==0 and x0==0 and y0==0):
      print "SPECIAL: Real Axis"
      return [-plotRad, 0, plotRad], [0, 0, 0], [plotRad, 0, 0, plotRad], [plotSplit, plotSplit, plotSplit + 180, plotSplit + 180]
    
    if (rad <= 0.):
      if (rad < 0.):
        print "ERROR: Radius should be positive definite!"
      else: 
        print "WARNING: No points, radius is zero"
      return [], [], [], []
    
    # STEP 1: Check if any part is inside the visual range
    dist = math.sqrt(pow(x0,2) + pow(y0,2))
    if ((rad < dist - plotRad) or (rad > dist + plotRad)):
      print "WARNING: No points inside visual range"
      return [], [], [], []
    
    # STEP 2: Calculate Angles
    # alpha = opening angle
    # alpha0 = starting angle
    # We generate between alpha0 and alpha0 + alpha
    if (dist>0):
      cosTheta = max(-1, (pow(dist,2) + pow(rad,2) - pow(plotRad,2))/(2 * dist * rad))
    else:
      cosTheta = -1
    theta = math.acos(cosTheta)
    alpha = 2 * theta
    if (alpha == 2 * math.pi):
      alpha0 = math.asin(-y0/rad)
    else:
      alpha0 = math.atan2(y0, x0) + math.pi - theta
    
    # STEP 3: Generate points in Re - Im and in Abs - Angle plane
    RePar = []
    ImPar = []
    AbsTemp = []
    AngTemp = []
    step = alpha/(plotPoints-1)
    for i in range(0, plotPoints):
      # STEP 3a: Re - Im plane
      xAdd = rad * math.cos(alpha0 + i * step) + x0
      yAdd = rad * math.sin(alpha0 + i * step) + y0
      # make sure that full circles run from 0 -> 360 (instead of 0 -> 0)
      if ((i==plotPoints-1) and (yAdd==ImPar[0])):
        yAdd = yAdd - pow(10,-17)
      # STEP 3b: Abs - Angle plane
      rAdd = math.sqrt(pow(xAdd,2) + pow(yAdd,2))
      fAdd = math.atan2(yAdd, xAdd) * 180/math.pi
      # Shift angles from [-pi, pi] to [plotSplit, plotSplit + 2pi]
      if (fAdd < plotSplit):
        fAdd = fAdd + 360
      # STEP 3c: Add
      RePar.append(xAdd)
      ImPar.append(yAdd)
      AbsTemp.append(rAdd)
      AngTemp.append(fAdd)
    
    # STEP 4: Massage Abs - Ang contours
    # Possible cases:
    # (a) Non-Circular contours, not split
    # (b) Non-Circular contours, split
    # (c) Circular contours, including the origin
    # (d) Circular contours, excluding the origin, not split
    # (e) Circular contours, excluding the origin, split

    # STEP 4a: Determine situation
    split = False
    splitPoint = 0
    angMin = plotSplit + 360
    angPoint = 0
    circ = (alpha == 2 * math.pi)
    lim = (circ and (rad > dist))
    limShift = -1
    for i in range(0, plotPoints):
      if ((i > 0) and (i < plotPoints - 1) and (AngTemp[i] < plotSplit + 90) and
          (((AngTemp[i+1] - AngTemp[i]) > 180) or ((AngTemp[i-1] - AngTemp[i]) > 180))):
        split = True
        splitPoint = i
      if (AngTemp[i] - plotSplit < angMin):
        angMin = AngTemp[i] - plotSplit
        angPoint = i
    # Summary
    if (split and not circ and not lim):
      if ((AngTemp[splitPoint+1] - AngTemp[splitPoint]) > 180):
        case = "Bdw"
      else:
        case = "Bup"
    elif (circ and lim):
      case = "C"
    elif (not split and circ and not lim):
      case = "D"
    elif (split and circ and not lim):
      case = "E"
    else:
      case = "A"
    print "  Contour of CASE: ", case#, "Cross-Check:", split, circ, lim

    if ((case=="C" or case=="Bup") and (plotSplit==0)):
      limShift = 1
    elif ((not plotSplit==0) and case=="Bdw"):
      limShift = 1


    # STEP 4b: Fill
    AbsPar = []
    AngPar = []
    # CASE B & C & E: Add point for angle = plotSplit
    if ('B' in case or case=="C" or case=="E"):
      AbsPar.append(math.fabs(limShift * math.sqrt(pow(rad,2) - pow(y0,2)) + x0))
      AngPar.append(plotSplit)
    # CASE B & E:
    if ('B' in case or case=="E"):
      # Run from Split to Start
      if (case=="Bdw" or case=="E"):
        for i in range(0, splitPoint+1):
          AbsPar.append(AbsTemp[splitPoint - i])
          AngPar.append(AngTemp[splitPoint - i])
      else:
        for i in range(0, plotPoints - splitPoint):
          AbsPar.append(AbsTemp[splitPoint + i])
          AngPar.append(AngTemp[splitPoint + i])
      # CASE E Only:
      if (case=="E"):
        # Add point for angle = plotSplit
        AbsPar.append(-limShift * math.sqrt(pow(rad,2) - pow(y0,2)) + x0)
        AngPar.append(plotSplit)
        # Move outside the range
        AbsPar.append(plotRad)
        AngPar.append(plotSplit)
        AbsPar.append(plotRad)
        AngPar.append(plotSplit + 360)
        # Add point for angle = plotSplit + 360
        AbsPar.append(-limShift * math.sqrt(pow(rad,2) - pow(y0,2)) + x0)
        AngPar.append(plotSplit + 360)
      # CASE Bup Only:
      if (case=="Bup"):
        stepAng = (AngTemp[0] - AngTemp[-1])/plotPoints
        for i in range(0, plotPoints):
          xAdd = (plotRad * math.cos((AngTemp[-1] + i * stepAng) * math.pi/180))
          yAdd = (plotRad * math.sin((AngTemp[-1] + i * stepAng) * math.pi/180))
          rAdd = math.sqrt(pow(xAdd,2) + pow(yAdd,2))
          fAdd = math.atan2(yAdd, xAdd) * 180/math.pi
          if (fAdd < plotSplit):
            fAdd = fAdd + 360
          AbsPar.append(rAdd)
          AngPar.append(fAdd)
      # Continue from End to Split
      if (case=="Bdw" or case=="E"):
        for i in range(0, plotPoints - splitPoint - 1):
          AbsPar.append(AbsTemp[plotPoints-1 - i])
          AngPar.append(AngTemp[plotPoints-1 - i])
      else:
        for i in range(0, splitPoint):
          AbsPar.append(AbsTemp[i])
          AngPar.append(AngTemp[i])
    # CASE C & D: Start with point closest to plotSplit
    elif (case=="C" or case=="D"):
      for i in range(angPoint, plotPoints):
        AbsPar.append(AbsTemp[i])
        AngPar.append(AngTemp[i])
      for i in range(0, angPoint):
        AbsPar.append(AbsTemp[i])
        AngPar.append(AngTemp[i])
    # CASE A: Go Left to Right
    else:
      if (AngTemp[0] < AngTemp[-1]):
        for i in range(0, plotPoints):
          AbsPar.append(AbsTemp[i])
          AngPar.append(AngTemp[i]) 
      else:
        for i in range(0, plotPoints):
          AbsPar.append(AbsTemp[plotPoints-1 - i])
          AngPar.append(AngTemp[plotPoints-1 - i])  
    # CASE B & C & E: Add point for angle = plotSplit + 360
    if ('B' in case or case=="C" or case=="E"):
      AbsPar.append(math.fabs(limShift * math.sqrt(pow(rad,2) - pow(y0,2)) + x0))
      AngPar.append(plotSplit + 360)
    # CASE D: Close contour
    elif (case=="D"):
      AbsPar.append(AbsPar[0])
      AngPar.append(AngPar[0])

    # STEP: Return
    return RePar, ImPar, AbsPar, AngPar


def Gen_Circle(ReConInn, ImConInn, ReConOut, ImConOut):
    # STEP 1: Identify Situation
    CurveInn = (len(ReConInn) > 1)
    CurveOut = (len(ReConOut) > 1)

    # STEP 2: Determine points on visible radius
    # Default
    if (CurveOut):
      alphaB = math.atan2(ImConOut[0],  ReConOut[0] )
      alphaC = math.atan2(ImConOut[-1], ReConOut[-1])
    if (CurveInn):
      alphaA = math.atan2(ImConInn[0],  ReConInn[0] )
      alphaD = math.atan2(ImConInn[-1], ReConInn[-1])
    if (not CurveOut and CurveInn):
      alphaB = alphaA + math.pi
      alphaC = alphaB
    elif (not CurveOut and not CurveInn):
      alphaA = math.pi
      alphaB = 0
      alphaC = 0
      alphaD = math.pi
    elif (CurveOut and not CurveInn):
      if (alphaB < 0):
        alphaA = (alphaB + 2 * math.pi + alphaC)/2
      else:
        alphaA = (alphaB + alphaC)/2
      alphaD = alphaA
    #print alphaA * 180/math.pi, alphaB * 180/math.pi, alphaC * 180/math.pi, alphaD * 180/math.pi

    if (alphaA - alphaB > pow(10,-3)):
      alphaB = alphaB + 2 * math.pi
    if (alphaC - alphaD > pow(10,-3)):
      alphaC = alphaC - 2 * math.pi
    alphaAB = alphaB - alphaA
    stepAB = alphaAB/(plotPoints-1)
    alphaCD = alphaD - alphaC
    stepCD = alphaCD/(plotPoints-1)
    #print alphaA * 180/math.pi, alphaB * 180/math.pi, alphaC * 180/math.pi, alphaD * 180/math.pi
    #print stepAB * 180/math.pi, stepCD * 180/math.pi
    
    # STEP 3: Create Boundary
    RePar = []
    ImPar = []
    # Boundary (A->B)
    if (math.fabs(alphaB-alphaC)>pow(10,-3)):
      for i in range(0, plotPoints):
        RePar.append(plotRad * math.cos(alphaA + i * stepAB))
        ImPar.append(plotRad * math.sin(alphaA + i * stepAB))
    # Outer Curve (B->C)
    if (CurveOut):
      for i in range(0, len(ReConOut)):
        RePar.append(ReConOut[i])
        ImPar.append(ImConOut[i])
    # Boundary (C->D)
    if (math.fabs(alphaB-alphaC)>pow(10,-4)):
      for i in range(0, plotPoints):
        RePar.append(plotRad * math.cos(alphaC + i * stepCD))
        ImPar.append(plotRad * math.sin(alphaC + i * stepCD))
    # Inner Curve (D->A)
    if (CurveInn):
      for i in range(0, len(ReConInn)):
        RePar.append(ReConInn[len(ReConInn)-1 - i])
        ImPar.append(ImConInn[len(ReConInn)-1 - i])

    # STEP: Return
    return RePar, ImPar

def Gen_BandI(AbsConUp, AngConUp, AbsConDw, AngConDw):
    # For fully split curves
    
    # STEP 1: Identify Situation
    CurveUp = (len(AbsConUp) > 1)
    CurveDw = (len(AbsConDw) > 1)

    # STEP 2: Create Band
    AbsPar = []
    AngPar = []

    if ((not CurveUp) or ((not AngConUp[0]==plotSplit) and (AngConDw[0]==plotSplit))):
      AbsPar.append(plotRad)
      AngPar.append(plotSplit)
    if (CurveUp):
      for i in range(0, len(AbsConUp)):
        AbsPar.append(AbsConUp[i])
        AngPar.append(AngConUp[i])
    if ((not CurveUp) or ((not AngConUp[-1]==plotSplit+360) and (AngConDw[-1]==plotSplit+360))):
      AbsPar.append(plotRad)
      AngPar.append(plotSplit + 360)
    if (CurveDw):
      for i in range(0, len(AbsConDw)):
        AbsPar.append(AbsConDw[len(AbsConDw)-1 - i])
        AngPar.append(AngConDw[len(AbsConDw)-1 - i])
    else:
      AbsPar.append(0)
      AngPar.append(plotSplit)
      AbsPar.append(0)
      AngPar.append(plotSplit + 360)

    # STEP: Return
    return AbsPar, AngPar

def Gen_BandII(AbsConUp, AngConUp, AbsConDw, AngConDw):
    # For partially split curves
    
    # STEP 1: Identify Situation
    CurveUp = (len(AbsConUp) > 1)
    CurveDw = (len(AbsConDw) > 1)

    # STEP 2: Find jump point
    SecA = 0
    for i in range(0, len(AbsConDw)):
      if (AbsConDw[i]>=0.99999*plotRad and SecA < 1):
        SecA = i
    #print SecA, AngConDw[SecA], AngConDw[SecA+1]

    # STEP 3: Create Band
    AbsPar = []
    AngPar = []

    # Left part of Lower Curve
    if (CurveDw):
      for i in range(0, SecA+1):
        AbsPar.append(AbsConDw[i])
        AngPar.append(AngConDw[i])
    # Upper Curve
    if (CurveUp):
      for i in range(0, len(AbsConUp)):
        AbsPar.append(AbsConUp[i])
        AngPar.append(AngConUp[i])
    # Right part of Lower Curve
    if (CurveDw):
      for i in range(SecA+1, len(AbsConDw)):
        AbsPar.append(AbsConDw[i])
        AngPar.append(AngConDw[i])
    # Close Contour
    AbsPar.append(0)
    AngPar.append(plotSplit + 360)
    AbsPar.append(0)
    AngPar.append(plotSplit)

    # STEP: Return
    return AbsPar, AngPar

def Gen_BandIII(AbsConUp, AngConUp, AbsConDw, AngConDw):
    # For circular curves
    
    # STEP 1: Identify Situation
    CurveUp = (len(AbsConUp) > 1)
    CurveDw = (len(AbsConDw) > 1)

    circ = (AngConUp[0]==AngConUp[-1])
    upcut = (not circ and AngConUp[0]==plotSplit)

    # STEP 2: Create Band
    AbsPar = []
    AngPar = []

    # Upper Curve
    if (CurveUp):
      for i in range(0, len(AbsConUp)):
        AbsPar.append(AbsConUp[i])
        AngPar.append(AngConUp[i])
    # Close Contour
    if upcut:
      AbsPar.append(0)
      AngPar.append(plotSplit + 360)
      if (CurveDw):
        AbsPar.append(0)
        AngPar.append(AngConDw[0])
    elif (not circ and CurveDw):
      AbsPar.append(plotRad)
      AngPar.append(AngConDw[0])
    # Lower Curve
    if (CurveDw):
      if (upcut or circ):
        for i in range(0, len(AbsConDw)):
          AbsPar.append(AbsConDw[len(AbsConDw)-1 - i])
          AngPar.append(AngConDw[len(AbsConDw)-1 - i])
      else:
        for i in range(0, len(AbsConDw)):
          AbsPar.append(AbsConDw[i])
          AngPar.append(AngConDw[i])        
    # Close Contour
    if upcut:
      if (CurveDw):
        AbsPar.append(0)
        AngPar.append(AngConDw[0])
      AbsPar.append(0)
      AngPar.append(plotSplit)
    elif (not circ and CurveDw):
      AbsPar.append(plotRad)
      AngPar.append(AngConDw[0])   

    # STEP: Return
    return AbsPar, AngPar

def Gen_BandIV(AbsConUp, AngConUp, AbsConDw, AngConDw, bord = plotRad):
    # For special cases: Glue Up and Down together
    
    # STEP 1: Identify Situation
    CurveUp = (len(AbsConUp) > 1)
    CurveDw = (len(AbsConDw) > 1)
    first = True
    if (CurveUp and CurveDw and (AngConUp[-1] > AngConDw[0])):
      print "WARNING: Will exchange order of contours"
      first = False
    lbord = True
    rbord = True
    # Contours do not reach boundary
    if ((CurveUp and (AngConUp[0] > plotSplit and AngConUp[-1] > plotSplit) or not CurveUp) and
        (CurveDw and (AngConDw[0] > plotSplit and AngConDw[-1] > plotSplit) or not CurveDw)):
      lbord = False
    if ((CurveUp and (AngConUp[0] < plotSplit + 360 and AngConUp[-1] < plotSplit + 360) or not CurveUp) and
        (CurveDw and (AngConDw[0] < plotSplit + 360 and AngConDw[-1] < plotSplit + 360) or not CurveDw)):
      rbord = False

    # STEP 2: Create Band
    AbsPar = []
    AngPar = []

    # Close Contour
    if (not lbord):
      AbsPar.append(bord)
      AngPar.append(plotSplit)
    # Upper Curve
    if (CurveUp and first):
      if (AngConUp[-1] < AngConUp[0]):
        for i in range(0, len(AbsConUp)):
          AbsPar.append(AbsConUp[len(AbsConUp)-1 - i])
          AngPar.append(AngConUp[len(AbsConUp)-1 - i])
      else:
        for i in range(0, len(AbsConUp)):
          AbsPar.append(AbsConUp[i])
          AngPar.append(AngConUp[i]) 
    # Lower Curve
    if (CurveDw):
      if (AngConDw[-1] < AngConDw[0]):
        for i in range(0, len(AbsConDw)):
          AbsPar.append(AbsConDw[len(AbsConDw)-1 - i])
          AngPar.append(AngConDw[len(AbsConDw)-1 - i])
      else:
        for i in range(0, len(AbsConDw)):
          AbsPar.append(AbsConDw[i])
          AngPar.append(AngConDw[i])
    # Upper Curve
    if (CurveUp and not first):
      if (AngConUp[-1] < AngConUp[0]):
        for i in range(0, len(AbsConUp)):
          AbsPar.append(AbsConUp[len(AbsConUp)-1 - i])
          AngPar.append(AngConUp[len(AbsConUp)-1 - i])
      else:
        for i in range(0, len(AbsConUp)):
          AbsPar.append(AbsConUp[i])
          AngPar.append(AngConUp[i]) 
    # Close Contour
    if (not rbord):
      AbsPar.append(bord)
      AngPar.append(plotSplit + 360)
    AbsPar.append(0)
    AngPar.append(plotSplit + 360)
    AbsPar.append(0)
    AngPar.append(plotSplit)  

    # STEP: Return
    return AbsPar, AngPar

def Gen_Band(AbsConUp, AngConUp, caseUp, AbsConDw, AngConDw, caseDw, bord = plotRad):
    # Method Assignment:
    #   | A | B | C | D | E (Up)
    # A | 1 | 2 | X | X | X
    # B | 2 | 1 | X | X | X
    # C | 1 | 1 | 1 | X | X
    # D | 3 | 3 | 3 | 3 | X
    # E | 2 | 1 | 2 | X | 1
    # (Dw)

    if (caseDw=="G" and caseUp=="G"):
      print "Method IV"
      return Gen_BandIV(AbsConUp, AngConUp, AbsConDw, AngConDw, bord)
    elif ((caseUp=="D" or caseUp=="E" and not caseDw==caseUp) or (caseUp=="C" and (caseDw=="A" or caseDw=="B"))):
      print "WARNING: Impossible combination"
      return [], []
    elif (caseDw=="D"):
      print "Method III"
      return Gen_BandIII(AbsConUp, AngConUp, AbsConDw, AngConDw)
    elif (caseDw=="C" or caseDw==caseUp or (caseUp=="B" and caseDw=="E")):
      print "Method I"
      return Gen_BandI(AbsConUp, AngConUp, AbsConDw, AngConDw)
    else:
      print "Method II"
      return Gen_BandII(AbsConUp, AngConUp, AbsConDw, AngConDw)
