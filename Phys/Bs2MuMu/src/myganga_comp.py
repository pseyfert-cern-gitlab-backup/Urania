# Ntupler for stripped runs
#------------------------------------------------------------------------------
r = Root()
r.version = '5.34.00'
r.script = '/afs/cern.ch/user/f/fdettori/cmtuser/Erasmus_v6r1/Phys/Bs2MuMu/src/runMain.C'
r.args = ['-var','1','-bin','5','-points','2','-f','RootWorksp_FD_outp.root']
#r.args = ['Minbias', 10]

tem = JobTemplate( application = r )

tem.name = 'MyFCjob'
tem.merger = None
#tem.inputsandbox = ["confinte_cpp.so","testFC_macro_C.so","testFC_macro.C","RootWorksp_FD_outp.root"]
tem.inputsandbox = ["libFoo.so", "RootWorksp_FD_outp.root"]

#tem.backend    = Local()
tem.backend    = Dirac()

#tem.backend.diracOpts = 'tem.setBannedSites([''])'
#tem.backend    = LCG()
#tem.backend    = LSF()
#tem.backend.diracOpts = 'tem.setDestination("LCG.CERN.ch")'
#------------------------------------------------------------------------------

#points = [0,10,20,30,40,50,60,70,80,90,
#          100,110,120,130,140,150,160,170,180,190,
#          200,210,220,230,240,250,260,270,280,290,
#          300,310,320,330,340,350,360,370,380,390,
#          400,410,420,430,440,450,460,470,480,490]
points = [0,10, 20]

j_idx = 0
for apoi in points:
    print "Doing Point:: ",apoi
    j = Job( tem )
    myargs = ['-var','1','-bin','500','-P',str(apoi),'-points','10','-f','RootWorksp_FD_outp.root']
    if j.backend == Dirac() : 
        j.backend.diracOpts="j.setSystemConfig('x86_64-slc5-gcc43-opt')"
    j.application.args = myargs
    apoin = apoi+10
    output = "myConfIntervaln"+str(apoi)+"_"+str(apoin)+".root"
    
    j.outputsandbox = [output,"mycl.root"]
    j.submit()
    j_idx += 1
    print(j)



#------------------------------------------------------------------------------
