from errors import *
lambdaBR = EVal(3.3e-4, 1.35e-4)
Vub_old = 3.5e-3
Vub = EVal(4.15e-3 , 0.49e-3)
LambdaTau = EVal(1.482, 0.0216)      # picoseconds
LambdaTau_old = EVal(1.391, 0.038)  # picoseconds

myBR = lambdaBR * (Vub * Vub)/(Vub_old*Vub_old) * LambdaTau/LambdaTau_old

print "New lambda BR is ", myBR


gammaReticoli = EVal(15.3, sqrt(2.4**2 + 3.4**2))
brReticoli = gammaReticoli * LambdaTau * Vub * Vub
print "B reticoli " , brReticoli

                     
