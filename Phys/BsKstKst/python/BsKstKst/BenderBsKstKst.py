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
B_daughter_Ids = [313,-313,22]
B_Mother_ID = 531

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

class BsKst0Kst0(AlgoMC):            
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
            bsMC = 0
            for par in mcpars:
                mcKs, mcKsb = 0,0
                if MCABSID(par) != B_Mother_ID: continue
                ev = par.endVertices().at(0).products()
                for j in range(ev.size()):
                    d = ev.at(j)
                    if MCID(d) not in B_daughter_Ids: continue
                    if MCID(d)==313:mcKs=d
                    if MCID(d)==-313:mcKsb=d
                    
                if mcKs and mcKsb: 
                    bsMC = par
                    break
            mcpiM,mcKM,mcKm,mcpim = 0,0,0,0
            
            if not bsMC and self.ONLY_MC:
                print "Something is wrong in this event"
                return SUCCESS
            
            if bsMC:
                ev1 = mcKs.endVertices().at(0).products()
                for i in range(ev1.size()):
                    ep = ev1.at(i)
                    #if MCID(ep) == 211: mcpiM = ep
                    if MCID(ep) == -211: mcpim = ep
                    if MCID(ep) == 321: mcKM = ep
                    #if MCID(ep) == -321: mcKm = ep
                ev2 = mcKsb.endVertices().at(0).products()
                for i in range(ev2.size()):
                    ep = ev2.at(i)
                    if MCID(ep) == 211: mcpiM = ep
                    #if MCID(ep) == -211: mcpim = ep
                    #if MCID(ep) == 321: mcKM = ep
                    if MCID(ep) == -321: mcKm = ep
             
            if not ( mcpiM and mcKM and mcKm and mcpim) and self.ONLY_MC:
		    print "Something is VERY wrong in this event"
		    print TES["Gen/Header"]
		    return SUCCESS
            
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
			
            kstar, kstarb =b.daughters().at(0), b.daughters().at(1)
            d1, d2 = kstar.daughters().at(0), kstar.daughters().at(1)
            d3, d4 = kstarb.daughters().at(0), kstarb.daughters().at(1)
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
                mcd1=link.first(d1.proto().track())
                mcd2=link.first(d2.proto().track())
                mcd3=link.first(d3.proto().track())
                mcd4=link.first(d4.proto().track())
               
                mcPV, mcSV = 0, 0
                isSig = 1
                 
                if not (mcd1 and mcd2 and mcd3 and mcd4): isSig = 0
                elif mcd1.key() != mcKM.key(): isSig = 0
                elif mcd2.key() != mcpim.key(): isSig = 0
                elif mcd3.key() != mcKm.key(): isSig = 0
                elif mcd4.key() != mcpiM.key(): isSig = 0
                
                if self.ONLY_MC and not isSig: continue
                if isSig:
                    mcSV = mcd1.mother().mother().endVertices()[0].data()
                    mcPV = mcd1.primaryVertex()
                
                mcd1p=safeparents(mcd1)
                mcd2p=safeparents(mcd2) 
                mcd3p=safeparents(mcd3) 
                mcd4p=safeparents(mcd4)
                mcd1pp=safeparents(mcd1p)
                mcd2pp=safeparents(mcd2p)
                mcd3pp=safeparents(mcd3p)
                mcd4pp=safeparents(mcd4p)
                
                CandidateInfo["MCIDd1"]=  safeMCID(mcd1)
                CandidateInfo["MCIDd2"]=  safeMCID(mcd2)
                CandidateInfo["MCIDd3"]=  safeMCID(mcd3)
                CandidateInfo["MCIDd4"]=  safeMCID(mcd4)
                
                CandidateInfo["MCIDd1p"]=  safeMCID(mcd1p)
                CandidateInfo["MCIDd2p"]=  safeMCID(mcd2p)
                CandidateInfo["d1d2sp"]=  safekey(mcd1p)==safekey(mcd2p)
                CandidateInfo["MCIDd3p"]=  safeMCID(mcd3p)
                CandidateInfo["MCIDd4p"]=  safeMCID(mcd4p)
                CandidateInfo["d3d4sp"]=  safekey(mcd3p)==safekey(mcd4p)
                
                CandidateInfo["MCIDd1pp"]=  safeMCID(mcd1pp)
                CandidateInfo["MCIDd2pp"]=  safeMCID(mcd2pp)
                CandidateInfo["MCIDd3pp"]=  safeMCID(mcd3pp)
                CandidateInfo["MCIDd4pp"]=  safeMCID(mcd4pp)
                
                CandidateInfo["mcd1p1"]=  safemomentum(mcd1,"Px")
                CandidateInfo["mcd1p2"]=  safemomentum(mcd1,"Py")
                CandidateInfo["mcd1p3"]=  safemomentum(mcd1,"Pz")
                CandidateInfo["mcd1E"]=  safemomentum(mcd1,"E")
                CandidateInfo["mcd1M"]=  safemomentum(mcd1,"M")
                
                CandidateInfo["mcd2p1"]=  safemomentum(mcd2,"Px")
                CandidateInfo["mcd2p2"]=  safemomentum(mcd2,"Py")
                CandidateInfo["mcd2p3"]=  safemomentum(mcd2,"Pz")
                CandidateInfo["mcd2E"]=  safemomentum(mcd2,"E")
                CandidateInfo["mcd2M"]=  safemomentum(mcd2,"M")
                
                CandidateInfo["mcd3p1"]=  safemomentum(mcd3,"Px")
                CandidateInfo["mcd3p2"]=  safemomentum(mcd3,"Py")
                CandidateInfo["mcd3p3"]=  safemomentum(mcd3,"Pz")
                CandidateInfo["mcd3E"]=  safemomentum(mcd3,"E")
                CandidateInfo["mcd3M"]=  safemomentum(mcd3,"M")
                
                CandidateInfo["mcd4p1"]=  safemomentum(mcd4,"Px")
                CandidateInfo["mcd4p2"]=  safemomentum(mcd4,"Py")
                CandidateInfo["mcd4p3"]=  safemomentum(mcd4,"Pz")
                CandidateInfo["mcd4E"]=  safemomentum(mcd4,"E")
                CandidateInfo["mcd4M"]=  safemomentum(mcd4,"M")
                
                CandidateInfo["mcpd1p1"]=  safemomentum(mcd1p,"Px")
                CandidateInfo["mcpd1p2"]=  safemomentum(mcd1p,"Py")
                CandidateInfo["mcpd1p3"]=  safemomentum(mcd1p,"Pz")
                CandidateInfo["mcpd1E"]=  safemomentum(mcd1p,"E")
                CandidateInfo["mcpd1M"]= safemomentum(mcd1p,"M")
                
                CandidateInfo["mcpd3p1"]=  safemomentum(mcd3p,"Px")
                CandidateInfo["mcpd3p2"]=  safemomentum(mcd3p,"Py")
                CandidateInfo["mcpd3p3"]=  safemomentum(mcd3p,"Pz")
                CandidateInfo["mcpd3E"]=  safemomentum(mcd3p,"E")
                CandidateInfo["mcpd3M"]= safemomentum(mcd3p,"M")
                CandidateInfo["mcppd1p1"]=  safemomentum(mcd1pp,"Px")
                CandidateInfo["mcppd1p2"]=  safemomentum(mcd1pp,"Py")
                CandidateInfo["mcppd1p3"]=  safemomentum(mcd1pp,"Pz")
                CandidateInfo["mcppd1E"]=  safemomentum(mcd1pp,"E")
                CandidateInfo["mcppd1M"]= safemomentum(mcd1pp,"M")
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
                    CandidateInfo["mcBctau"]=MCCTAU(safeparents(safeparents(mcd1)))
                   
           
            vt = vector(VX(PV),VY(PV),VZ(PV))

            SV = vector(VX(b.endVertex()),VY(b.endVertex()),VZ(b.endVertex()))
            rSV = SV-vt
           
            Ips = MIPCHI2(pvs, self.geo())
	    Ip = MIP(pvs,self.geo()) 	
            lifet=TIMEDIST(PV)

           
            CandidateInfo["evt"]=   self.COUNTER["EVT"]
            CandidateInfo["KstarChi2"]=   kstar.endVertex().chi2()
            CandidateInfo["KstarbChi2"]=   kstarb.endVertex().chi2()
            CandidateInfo["Vchi2"]=   VCHI2(b.endVertex())
            CandidateInfo["SVnodf"]=  VDOF(b.endVertex())
            CandidateInfo["PVnodf"]=  VDOF(PV)
            CandidateInfo["KstarMass"]=   M(kstar)
            CandidateInfo["KstarbMass"]=   M(kstarb)
            CandidateInfo["Bmass"]=   M(b)
            CandidateInfo["Bctau"]= lifet(b)  

            CandidateInfo["d1p1"]=   PX(d1)
            CandidateInfo["d1p2"]=   PY(d1)
            CandidateInfo["d1p3"]=   PZ(d1)

            CandidateInfo["d1E"]=  E(d1)
            CandidateInfo["d2E"]=  E(d2)
            CandidateInfo["d3E"]=  E(d3)
            CandidateInfo["d4E"]=  E(d4)

            CandidateInfo["d1M"]= M(d1)
            CandidateInfo["d2M"]= M(d2)
            CandidateInfo["d3M"]= M(d3)
            CandidateInfo["d4M"]= M(d4)

            CandidateInfo["d2p1"]=   PX(d2)
            CandidateInfo["d2p2"]=   PY(d2)
            CandidateInfo["d2p3"]=   PZ(d2)
            CandidateInfo["d3p1"]=   PX(d3)
            CandidateInfo["d3p2"]=   PY(d3)
            CandidateInfo["d3p3"]=   PZ(d3)
            CandidateInfo["d4p1"]=   PX(d4)
            CandidateInfo["d4p2"]=   PY(d4)
            CandidateInfo["d4p3"]=   PZ(d4)
            

            CandidateInfo["d1PIDK"]=  PIDK(d1)
            CandidateInfo["d2PIDK"]=  PIDK(d2)
            CandidateInfo["d3PIDK"]=  PIDK(d3)
            CandidateInfo["d4PIDK"]=  PIDK(d4)

            CandidateInfo["d1TrChi2DoF"]=  TRCHI2DOF(d1)
            CandidateInfo["d2TrChi2DoF"]=  TRCHI2DOF(d2)
            CandidateInfo["d3TrChi2Dof"]=  TRCHI2DOF(d3)
            CandidateInfo["d4TrChi2Dof"]=  TRCHI2DOF(d4)
           
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
            CandidateInfo["minIPS"]=   min(Ips(d1), Ips(d2), Ips(d3), Ips(d4))
            CandidateInfo["mKsIPS"]= min (Ips(kstar),Ips(kstarb))
            CandidateInfo["KsIP"]= Ip(kstar)
            CandidateInfo["KbIP"]= Ip(kstarb)
            CandidateInfo["KsIPS"]= Ips(kstar)
            CandidateInfo["KbIPS"]= Ips(kstarb)
            CandidateInfo["d1IP"]= Ip(d1)
            CandidateInfo["d2IP"]= Ip(d2)
            CandidateInfo["d3IP"]= Ip(d3)
            CandidateInfo["d4IP"]= Ip(d4)
            CandidateInfo["d1IPS"]= Ips(d1)
            CandidateInfo["d2IPS"]= Ips(d2)
            CandidateInfo["d3IPS"]= Ips(d3)
            CandidateInfo["d4IPS"]= Ips(d4)            
            CandidateInfo["minIP"]=   min(Ip(d1), Ip(d2), Ip(d3), Ip(d4))
            CandidateInfo["mKsIP"]= min (Ip(kstar),Ip(kstarb))
	    CandidateInfo["minPt"]=   min(PT(d1), PT(d2), PT(d3), PT(d4))
            CandidateInfo["minPtot"]=  min(P(d1),P(d2),P(d3),P(d4))
            CandidateInfo["minKstarPt"]=  min(PT(kstar),PT(kstarb))
            CandidateInfo["minKstarChi2"]=   min(kstar.endVertex().chi2(),kstar.endVertex().chi2())
            CandidateInfo["maxTrChi2DoF"]= max(TRCHI2DOF(d1),TRCHI2DOF(d2),TRCHI2DOF(d3),TRCHI2DOF(d4))
           
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
        print "Bender has found a Bs --> K*0 K*0 candidate"
        self.COUNTER["Sel"] += 1
        return SUCCESS
    
    def finalize(self):
        print "Bs --> K*0 K*0 counter. \n -----------"
        print self.COUNTER
        if self.DST:
            print "[||] Keys for added Info", self.name()
            for i in range(len(self.addedKeys)):
                print 500+i, self.addedKeys[i]
        print "../../../../../"
        return SUCCESS
