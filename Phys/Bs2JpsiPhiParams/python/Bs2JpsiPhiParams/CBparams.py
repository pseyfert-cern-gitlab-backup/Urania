#from Selections import *


class tailtable:
    def __init__(self, a,a2,n,n2, l,zeta):
        self.a = a
        self.a2 = a2
        self.n = n
        self.n2 = n2
        self.l = l
        self.zeta = zeta

BiasedBin0 = tailtable(3.29939e+00,2.24270e+00,1.60990e-01,1.78788e+00,-4.14520e+00 ,4.91180e-02 )
BiasedBin1 = tailtable(2.90,2.47,1.72,2.86,-2.89863e+00, 1.66073e-02)
BiasedBin2 = tailtable(3.15,2.17,1.77,2.42,-2.95347e+00,2.43734e-01 )
BiasedBin3 = tailtable(3.29,3.18,1.,0.7, -2.60276e+00,2.01611e-03)

UnBiasedBin0 = tailtable(3.66949e+00,2.65075e+00  ,5.29853e-02 ,1.37889e+00, -2.67962e+00, 1.25799e-02)
UnbiasedBin1 = tailtable(2.84152e+00,2.41278e+00, 1.70082e+00 , 2.93785e+00 ,-3.05731e+00, 4.08103e-05)
UnbiasedBin2 = tailtable( 2.93371e+00, 2.25545e+00, 2.05133e+00 , 2.28098e+00,-3.15260e+00,9.02817e-04)
UnbiasedBin3 = tailtable(3.31371e+00 , 3.35729e+00, 8.22345e-01, 5.90315e-01,-2.48238e+00, 2.72442e-04)

AllTrig12MeVBin = tailtable(2.90285e+00,2.34455e+00,1.81284e+00, 2.51768e+00, -3.05600)
