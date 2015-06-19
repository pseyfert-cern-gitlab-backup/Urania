from BsMuMuPy.pyMyRoot.unifuncInterface_byLines import *
from BsMuMuPy.pyMyRoot.triggerclass import *
from ROOT import *
import sys
vars = ["B_ctau","lessIPS","B_DOCA","B_pt","B_IP"]


cuts = "B_IPS<5 "
cuts += "&& P21_richPID_k>0 && P11_richPID_k>0 &&P22_richPID_k<0 && P12_richPID_k<0 "
cuts += "&& SV_chi2<25"
cuts += "&& P11_TrChi2DoF<5 && P12_TrChi2DoF<5 && P21_TrChi2Dof<5 && P22_TrChi2Dof<5 "
cuts += "&& P1_pt>900 && P2_pt>900 "
cuts += "&& P11_pt>500 && P12_pt>500 && P21_pt>500 && P22_pt>500 "
cuts += "&& max(P1V_chi2,P2V_chi2)<9 "
cuts += "&& B_dissig>15"

infilename = sys.argv[1]
infile = open(infilename)


while true:
    line = infile.readline()
    if not line: break

    name = line[0:-6]

    print name+".root"
    fsmc0 = TFile(name+".root") 
    tsmc0 = fsmc0.Get("BsKst0Kst0/BsKst0Kst0")

    fsmc1 = TFile(name+"_cuts.root", "recreate") ### idem para la senhal
    tsmc1 = tsmc0.CopyTree(cuts)
    tsmc1.Write()
    fsmc1.Close()



    ##### La clase channeldata es una mierda que hice cuando trabajaba en el trigger (~2005). Convierte los TTrees en una lista de diccionarios con algunas propiedades.

    # Le pasas el nombre del archivo, el del TTree (default = "T"), y la lista de variables q t interesan (default : todas)

    s = channelData(name+"_cuts", name2 = "BsKst0Kst0")#, labels = ["evt","B_ctau","B_DOCA","B_pt","B_IP","P11_IPS","P12_IPS","P22_IPS","P21_IPS","B_dissig"])

    for entry in s:
        entry["lessIPS"] = min(entry["P11_IPS"],entry["P12_IPS"],entry["P22_IPS"],entry["P21_IPS"])


    glfile = open(os.environ["PWD"] + "/glk_mc10_Vchi2_5",'r')

    import cPickle
    gl=cPickle.load(glfile)
    gl(s,"GLK") ### La aplicas donde quieras. Luego puedes salvar los channeldata como root files ota vez con s.save('signal'), b.save('bkg'),d.save('los_datos') etc....


    s.save(name+"_cuts_GL")
    print "Saved"
