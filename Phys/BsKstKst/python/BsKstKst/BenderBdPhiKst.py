#! /usr/bin/env python
from BsMuMuPy.pyUtils.alyabar import *   
from LinkerInstances.eventassoc import * 
from BsMuMuPy.pyDaVinci import climbing , dv22Tools
from BsMuMuPy.algorithms import extrafunctions

from Bender.MainMC import *                
from math import sqrt as s_q_r_t
import GaudiPython 
import GaudiKernel

selectVertexMin = LoKi.SelectVertex.selectMin

###Defining some variables
GBL = GaudiPython.gbl.LHCb
MBs = 5369.600
B_daughter_Ids = [313,-313,333,22]
B_Mother_ID = 511

def safeMCID(mcpart):
        if not mcpart :return 0.0
        return MCID(mcpart)
    
def safeparents(part):
        if not part: return 0
        if part.parents().size(): return part.parents()[0]
        return 0
    
def safekey(mcparticle):
        if not mcparticle: return 0
        else: return mcparticle.key()

def safemomentum(mcparticle,str="E"):
        if not mcparticle: return 0.0
        return getattr(mcparticle.momentum(),str)()

class BdPhiKst0(AlgoMC):            
    def analyse(self):
        self.COUNTER["EVT"] += 1
        TES = appMgr().evtsvc()
        pflag=0 
        bparts = TES["/Event/Phys/"+self.LookIn+"/Particles"]
        
        if not(bparts): return SUCCESS 
        bparts=bparts.containedObjects() 
        
        if bparts.size()==0 : return SUCCESS
       
        if self.MC_INFO:   
            link = linkedTo(GBL.MCParticle,GBL.Track,"Rec/Track/Best")
            mcpars = TES["MC/Particles"].containedObjects()
            bdMC = 0
            for par in mcpars:
                mcKs, mcPhi = 0,0
                if MCABSID(par) != B_Mother_ID: continue
                ev = par.endVertices().at(0).products()
                for j in range(ev.size()):
                    d = ev.at(j)
                    if MCID(d) not in B_daughter_Ids: continue
                    if MCABSID(d)==313:mcKs=d
                    if MCID(d)==333:mcPhi=d
                    
                if mcKs and mcPhi: 
                    bdMC = par
                    break
            mcpi_,mcK_,mcKp_,mcKm_ = 0,0,0,0
            
            if not bdMC and self.ONLY_MC:
                print "Something is wrong"
                return SUCCESS
            
            if bdMC:
                ev1 = mcKs.endVertices().at(0).products()
                for i in range(ev1.size()):
                    ep = ev1.at(i)
                   
                    if MCABSID(ep) == 211: mcpi_ = ep
                    if MCABSID(ep) == 321: mcK_ = ep
                   
                ev2 = mcPhi.endVertices().at(0).products()
                for i in range(ev2.size()):
                    ep = ev2.at(i)
                    if MCID(ep) == 321: mcKp_ = ep
                    if MCID(ep) == -321: mcKm_ = ep
            
            
        if self.TRIGGER: 
            l0T = TES["Trig/L0/L0DUReport"]
            HighT = TES["/Event/Hlt/DecReports"]
            hl1gd= HighT.decReport("Hlt1Global")
            hl2gd= HighT.decReport("Hlt2Global")
            tistostool = self.tistostool
            
        self.COUNTER["reco"] += 1
        
        pvs = self.vselect("pvs", ISPRIMARY)
        if pvs.empty(): return SUCCESS
        
        for b in bparts :
			
            phi, kstar =b.daughters().at(0), b.daughters().at(1)
	    if ABSID(kstar) != 313: print "You are calling a Kstar to something that is not a kstar"
	    
            k, pi = kstar.daughters().at(0), kstar.daughters().at(1)
            kp, km = phi.daughters().at(0), phi.daughters().at(1)
	    if ABSID(k) != 321: print "You are calling a k to something that is not a k"
	    if ABSID(pi) != 211: print "You are calling a pi to something that is not a pi"
	    if ID(kp) != 321: print "You are calling a k+ to something that is not a k+"
	    if ID(km) != -321: print "You are calling a k- to something that is not a k-"
	    
            PVips=VIPCHI2(b, self.geo())
            PVip=VIP(b,self.geo())
            PVcut = (PVips >= 0. )
            PV = selectVertexMin(pvs, PVips, PVcut)
            Bdis = VDCHI2( PV )
            Bd=VD(PV)
            if Bdis(b)< 0: continue
	    CandidateInfo, Done = {}, {}
	    Done["TES"], Done["Candidate"] = TES, b
            
            if self.MC_INFO:
                mck=link.first(k.proto().track())
                mcpi=link.first(pi.proto().track())
                mckplus=link.first(kp.proto().track())
                mckm=link.first(km.proto().track())
               
                mcPV, mcSV = 0, 0
                isSig = 1
                 
                if not (mck and mcpi and mckplus and mckm): isSig = 0
                elif mck.key() != mcK_.key(): isSig = 0
                elif mcpi.key() != mcpi_.key(): isSig = 0
                elif mckplus.key() != mcKp_.key(): isSig = 0
                elif mckm.key() != mcKm_.key(): isSig = 0
                
                if self.ONLY_MC and not isSig: continue
                if isSig:
                    mcSV = mck.mother().mother().endVertices()[0].data()
                    mcPV = mck.primaryVertex()
                
                mckp=safeparents(mck)
                mcpip=safeparents(mcpi) 
                mckplusp=safeparents(mckplus) 
                mckmp=safeparents(mckm)
		
                mckpp=safeparents(mckp)
                mcpipp=safeparents(mcpip)
                mckpluspp=safeparents(mckplusp)
                mckmpp=safeparents(mckmp)
                
                CandidateInfo["MCIDk"]=  safeMCID(mck)
                CandidateInfo["MCIDpi"]=  safeMCID(mcpi)
                CandidateInfo["MCIDkplus"]=  safeMCID(mckplus)
                CandidateInfo["MCIDkm"]=  safeMCID(mckm)
                
                CandidateInfo["MCIDkp"]=  safeMCID(mckp)
                CandidateInfo["MCIDpip"]=  safeMCID(mcpip)
                CandidateInfo["kpisp"]=  safekey(mckp)==safekey(mcpip)
		
                CandidateInfo["MCIDkplusp"]=  safeMCID(mckplusp)
                CandidateInfo["MCIDkmp"]=  safeMCID(mckmp)
                CandidateInfo["kpluskmsp"]=  safekey(mckpp)==safekey(mckmp)
                
                CandidateInfo["MCIDkpp"]=  safeMCID(mckpp)
                CandidateInfo["MCIDpipp"]=  safeMCID(mcpipp)
                CandidateInfo["MCIDkpluspp"]=  safeMCID(mckpluspp)
                CandidateInfo["MCIDkmpp"]=  safeMCID(mckmpp)
                
                CandidateInfo["mckp1"]=  safemomentum(mck,"Px")
                CandidateInfo["mckp2"]=  safemomentum(mck,"Py")
                CandidateInfo["mckp3"]=  safemomentum(mck,"Pz")
                CandidateInfo["mckE"]=  safemomentum(mck,"E")
                CandidateInfo["mckM"]=  safemomentum(mck,"M")
                
                CandidateInfo["mcpip1"]=  safemomentum(mcpi,"Px")
                CandidateInfo["mcpip2"]=  safemomentum(mcpi,"Py")
                CandidateInfo["mcpip3"]=  safemomentum(mcpi,"Pz")
                CandidateInfo["mcpiE"]=  safemomentum(mcpi,"E")
                CandidateInfo["mcpiM"]=  safemomentum(mcpi,"M")
                
                CandidateInfo["mckplusp1"]=  safemomentum(mckplus,"Px")
                CandidateInfo["mckplusp2"]=  safemomentum(mckplus,"Py")
                CandidateInfo["mckplusp3"]=  safemomentum(mckplus,"Pz")
                CandidateInfo["mckplusE"]=  safemomentum(mckplus,"E")
                CandidateInfo["mckplusM"]=  safemomentum(mckplus,"M")
                
                CandidateInfo["mckmp1"]=  safemomentum(mckm,"Px")
                CandidateInfo["mckmp2"]=  safemomentum(mckm,"Py")
                CandidateInfo["mckmp3"]=  safemomentum(mckm,"Pz")
                CandidateInfo["mckmE"]=  safemomentum(mckm,"E")
                CandidateInfo["mckmM"]=  safemomentum(mckm,"M")
                
                CandidateInfo["mcpkp1"]=  safemomentum(mckp,"Px")
                CandidateInfo["mcpkp2"]=  safemomentum(mckp,"Py")
                CandidateInfo["mcpkp3"]=  safemomentum(mckp,"Pz")
                CandidateInfo["mcpkE"]=  safemomentum(mckp,"E")
                CandidateInfo["mcpkM"]= safemomentum(mckp,"M")
                
                
                CandidateInfo["mcPVX"]=  0.0
                CandidateInfo["mcPVY"]=  0.0
                CandidateInfo["mcPVZ"]=  0.0
                CandidateInfo["mcSVX"]=  0.0
                CandidateInfo["mcSVY"]=  0.0
                CandidateInfo["mcSVZ"]=  0.0
                CandidateInfo["mcSVt"]=  -1.0
                CandidateInfo["mcBctau"]= -1.0
                
                if mcPV:
                    CandidateInfo["mcPVX"]=  mcPV.position().X()
                    CandidateInfo["mcPVY"]=  mcPV.position().Y()
                    CandidateInfo["mcPVZ"]=  mcPV.position().Z()
                        
                if mcSV:
                    CandidateInfo["mcSVX"]=  mcSV.position().X()
                    CandidateInfo["mcSVY"]=  mcSV.position().Y()
                    CandidateInfo["mcSVZ"]=  mcSV.position().Z()
                    CandidateInfo["mcSVt"]=  mcSV.time()
                    CandidateInfo["mcBctau"]=MCCTAU(safeparents(safeparents(mck)))
                   
           
            vt = vector(VX(PV),VY(PV),VZ(PV))

            SV = vector(VX(b.endVertex()),VY(b.endVertex()),VZ(b.endVertex()))
            rSV = SV-vt
           
            Ips = MIPCHI2(pvs, self.geo())
	    Ip = MIP(pvs,self.geo()) 	
            lifet=TIMEDIST(PV)

           
            CandidateInfo["evt"]=   self.COUNTER["EVT"]
            CandidateInfo["KstarChi2"]=   kstar.endVertex().chi2()
            CandidateInfo["PhiChi2"]=   phi.endVertex().chi2()
            CandidateInfo["Vchi2"]=   VCHI2(b.endVertex())
            CandidateInfo["SVnodf"]=  VDOF(b.endVertex())
            CandidateInfo["PVnodf"]=  VDOF(PV)
            CandidateInfo["KstarMass"]=   M(kstar)
            CandidateInfo["PhiMass"]=   M(phi)
            CandidateInfo["Bmass"]=   M(b)
            CandidateInfo["Bctau"]= lifet(b)  

            CandidateInfo["kp1"]=   PX(k)
            CandidateInfo["kp2"]=   PY(k)
            CandidateInfo["kp3"]=   PZ(k)

            CandidateInfo["kE"]=  E(k)
            CandidateInfo["piE"]=  E(pi)
            CandidateInfo["kpE"]=  E(kp)
            CandidateInfo["kmE"]=  E(km)

            CandidateInfo["kM"]= M(k)
            CandidateInfo["piM"]= M(pi)
            CandidateInfo["kpM"]= M(kp)
            CandidateInfo["kmM"]= M(km)

            CandidateInfo["pip1"]=   PX(pi)
            CandidateInfo["pip2"]=   PY(pi)
            CandidateInfo["pip3"]=   PZ(pi)
            CandidateInfo["kpp1"]=   PX(kp)
            CandidateInfo["kpp2"]=   PY(kp)
            CandidateInfo["kpp3"]=   PZ(kp)
            CandidateInfo["kmp1"]=   PX(km)
            CandidateInfo["kmp2"]=   PY(km)
            CandidateInfo["kmp3"]=   PZ(km)
            

            CandidateInfo["kPIDK"]=  PIDK(k)
            CandidateInfo["piPIDK"]=  PIDK(pi)
            CandidateInfo["kpPIDK"]=  PIDK(kp)
            CandidateInfo["kmPIDK"]=  PIDK(km)

            CandidateInfo["kTrChi2DoF"]=  TRCHI2DOF(k)
            CandidateInfo["piTrChi2DoF"]=  TRCHI2DOF(pi)
            CandidateInfo["kpTrChi2Dof"]=  TRCHI2DOF(kp)
            CandidateInfo["kmTrChi2Dof"]=  TRCHI2DOF(km)
           
            CandidateInfo["SV1"]=   VX(b.endVertex())
            CandidateInfo["SV2"]=   VY(b.endVertex())
            CandidateInfo["SV3"]=   VZ(b.endVertex())
            CandidateInfo["SVN"]=   b.endVertex().outgoingParticles().size()

            CandidateInfo["flightSigned"]=   vmod(rSV)*rSV[2]/abs(rSV[2])
            CandidateInfo["PV1"]=   VX(PV)
            CandidateInfo["PV2"]=   VY(PV)
            CandidateInfo["PV3"]=   VZ(PV)
            CandidateInfo["Bips"]= PVips(PV)
            CandidateInfo["Bip"]=  PVip(PV)
            CandidateInfo["Bdissig"]=   s_q_r_t(Bdis(b))
            CandidateInfo["Bd"]=  Bd(b)
            CandidateInfo["minIPS"]=   min(Ips(k), Ips(pi), Ips(kp), Ips(km))
            CandidateInfo["mKsIPS"]= min (Ips(kstar),Ips(phi))
            CandidateInfo["KsIP"]= Ip(kstar)
            CandidateInfo["KbIP"]= Ip(phi)
            CandidateInfo["KsIPS"]= Ips(kstar)
            CandidateInfo["KbIPS"]= Ips(phi)
            CandidateInfo["kIP"]= Ip(k)
            CandidateInfo["piIP"]= Ip(pi)
            CandidateInfo["kpIP"]= Ip(kp)
            CandidateInfo["kmIP"]= Ip(km)
            CandidateInfo["kIPS"]= Ips(k)
            CandidateInfo["piIPS"]= Ips(pi)
            CandidateInfo["kpIPS"]= Ips(kp)
            CandidateInfo["kmIPS"]= Ips(km)            
            CandidateInfo["minIP"]=   min(Ip(k), Ip(pi), Ip(kp), Ip(km))
            CandidateInfo["mKsIP"]= min (Ip(kstar),Ip(phi))
	    CandidateInfo["minPt"]=   min(PT(k), PT(pi), PT(kp), PT(km))
            CandidateInfo["minPtot"]=  min(P(k),P(pi),P(kp),P(km))
            CandidateInfo["minKstarPt"]=  min(PT(kstar),PT(phi))
            CandidateInfo["minKstarChi2"]=   min(kstar.endVertex().chi2(),kstar.endVertex().chi2())
            CandidateInfo["maxTrChi2DoF"]= max(TRCHI2DOF(k),TRCHI2DOF(pi),TRCHI2DOF(kp),TRCHI2DOF(km))
           
            if self.TRIGGER :extrafunctions.addTrigRedux(self, CandidateInfo,Done)
            if self.EXTTRIG:    
                CandidateTriggerInf={}
                CandidateTriggerInf["evt"]=   self.COUNTER["EVT"]
                extrafunctions.addTrigInfo(self,CandidateTriggerInf,Done)
				    
               
            if self.TUP:
                tup = self.nTuple(self.name() )
                for key in CandidateInfo.keys():
                    tup.column(key,CandidateInfo[key])
                tup.write()
              
            if self.EXTTRIG:
                
                tup2 = self.nTuple(self.name()+"trig")
                for key in CandidateTriggerInf.keys():    
                    tup2.column(key,CandidateTriggerInf[key])
                tup2.write()
               
            if self.DST:
                self.addedKeys = CandidateInfo.keys()
                self.addedKeys.sort()
                for i in range(len(self.addedKeys)):
                    j = 500 + i
                    b.addInfo(j,CandidateInfo[self.addedKeys[i]])
                    
        self.setFilterPassed( True )
        print "Bender has found a Bd --> phi K*0 candidate"
        self.COUNTER["Sel"] += 1
        return SUCCESS
    
    def finalize(self):
        print "Bd --> phi K*0 counter. \n -----------"
        print self.COUNTER
        if self.DST:
            print "[||] Keys for added Info", self.name()
            for i in range(len(self.addedKeys)):
                print 500+i, self.addedKeys[i]
        print "../../../../../"
        return SUCCESS
