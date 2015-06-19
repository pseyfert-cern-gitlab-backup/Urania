from errors import *
lambdaBR = EVal(3.3e-4, 1.35e-4)
Vub_old = 3.5e-3
Vub = EVal(4.15e-3 , 0.49e-3)
LambdaTau = EVal(1.482, [0.018, 0.012])   # picoseconds from LHCb
LambdaTau2 = EVal(1.479, [0.009, 0.010 ] ) #New LHCb value http://arxiv.org/abs/1402.6242

LambdaTau = LambdaTau.compress_errors()
LambdaTau2 = LambdaTau2.compress_errors()
LambdaTau_PDG = EVal(1.425, 0.032)      # picoseconds
LambdaTau_old = EVal(1.391, 0.038)      # picoseconds

myBR = lambdaBR * (Vub * Vub)/(Vub_old*Vub_old) * LambdaTau/LambdaTau_old
myBR2 = lambdaBR * (Vub * Vub)/(Vub_old*Vub_old) * LambdaTau2/LambdaTau_old

print 'lambda BF for paper was ', lambdaBR * (Vub * Vub)/(Vub_old*Vub_old) * LambdaTau_PDG/LambdaTau_old
print "New lambda BR is ", myBR
print "Newest lambda BR is " , myBR2

gammaReticoli = EVal(15.3, sqrt(2.4**2 + 3.4**2))
brReticoli = gammaReticoli * LambdaTau * Vub * Vub
brReticoli2 = gammaReticoli * LambdaTau2 * Vub * Vub
print 'B reticoli with PDG tau', gammaReticoli * LambdaTau_PDG * Vub * Vub
print "B reticoli " , brReticoli
print "B reticoli2 " , brReticoli2

                     
