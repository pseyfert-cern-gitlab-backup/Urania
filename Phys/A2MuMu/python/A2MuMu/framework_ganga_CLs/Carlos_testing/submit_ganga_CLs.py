from Ganga.GPI import *
from random import randint

# When submitted, can check the arguments doing 'jobs(XXX).subjobs(Y).application.args'.

def send_job(argList, tDataName, jTag, jYear, backendDest):
  jname = 'CLs_computation_'+tDataName[:-5]+'_'+jTag+'_Year-'+jYear
  project_           = 'Urania'
  version_           = 'v4r0'
  app = GaudiPython()
  app.project = project_
  app.version = version_
  app.script   = 'toy.py' # Main script, this may be changed.
  job = Job(name        = jname,
            application = app,
            backend     = Dirac(),
            outputfiles = [LocalFile('output.nsig')])
  job.inputfiles=[LocalFile(tDataName)] # Note that the toydata name is passed as an argument here.
  job.splitter = ArgSplitter(args = argList)
  #CustomMerger().module = 'mergeOutputNsig_postProcessor.py'
  #job.postprocessors.append(CustomMerger(files = ['output.nsig'])) # This is not working for some reason.
  #job.postprocessors.append(TextMerger(files = ['output.nsig'])) # The output is not cPickeable in this case.
  job.parallel_submit = True
  job.prepare()
  job.backend.settings['Destination'] = [backendDest] # Do not ask...
  job.submit()

backendList = ['LCG.Bari.it', 'LCG.Pisa.it', 'LCG.LAPP.fr']#, 'LCG.RRCKI.ru'] # Do not modify this.
A_masses    = range(8550,11000,150)
N_sigs      = range(50,110,5)
tDataName   = 'data_test.root' #'data_HPT.root'
nToys       = 10000
jYear       = 2011 # Just a label.

# Send one job per mass in A_masses, with n subjobs corresponding to each Nsig in N_sigs: 
for A_mass in A_masses:
  argList, jTag = [], 'nToys-'+str(nToys)+'_tData-'+tDataName[:-5]+'_Amass-'+str(A_mass)+'_Nsigs-'
  for N_sig in N_sigs:
    argList.append([A_mass, N_sig, tDataName, nToys])
    jTag += str(N_sig)+'_'
  jTag = jTag[:-1]
  print 'Sending job:', jTag, '|', tDataName, '|', str(jYear)
  backendDest = backendList[randint(0, len(backendList)-1)]
  send_job(argList, tDataName, jTag, str(jYear), backendDest)

