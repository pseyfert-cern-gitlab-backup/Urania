import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from triggerclass import *
files_path = "../" #os.environ["HOME"] + "/public/for_Mathieu/"
q = os.walk(files_path)
a = q.next()
name ="Bs2012_autum_2010_atlas_cms_cdf_SYST1job" #"KSMM_TISTOSSYST"
ch = []
for entry in a[2]:
    
    if name in entry:
        f = file(files_path + "/" + entry,"r")
        if not f.readlines():
            print entry
            continue
        
        ch += channelData(files_path + "/" + entry,typ="ASCII")
ch = channelData(ch)
l = []
for entry in ch:
    l.append([entry["BR"], entry])
l.sort()
ch = []
for entry in l:
    ch.append(entry[1])
ch = channelData(ch)
ch.save(name + "_all",typ = "X")

x = ch.takeKey("CLs")
x2 = ch.takeKey("CLs_exp_b_med")
clsb = ch.takeKey("CLsb")

y =  ch.takeKey("BR")
q = NF(x,y)
q2 = NF(x2,y)
clsb = NF(clsb,y)
p = NF(y, ch.takeKey("CLb"))
