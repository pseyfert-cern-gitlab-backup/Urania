from ROOT import TDatabasePDG, TParticlePDG

rootpdg = TDatabasePDG()

print "Class ParticleDataPDG is based in TParticlePDG. But Masses and Widths will be given in MeV and not in GeV"
class ParticleData:
    def __init__(self, something):
        
        if isinstance(something, float): something = int(something)  
        self.Tpar = rootpdg.GetParticle(something)
        self.mass = self.Mass()
        self.width = self.Width()
        
    def Mass(self):
        return self.Tpar.Mass()*1000.
    
    def Width(self):
        return self.Tpar.Width()*1000.
    
    def Name(self):
        return self.Tpar.GetName()


## Do some BKK

phi = ParticleData(333)
Kst0 = ParticleData(313)
electron = ParticleData(11)
proton = ParticleData(2212)
neutron = ParticleData(2112)
muon = ParticleData(13)
Muon = muon
Kplus = ParticleData(321)
piplus = ParticleData(211)
K0  = ParticleData(311)
Jpsi = ParticleData(443)
Bd = ParticleData(511)
Bs = ParticleData(531)
Bu = ParticleData(521)
Lambda_b0 = ParticleData(5122)
        
