import os
import cPickle

def merge(file_list, output_file):
  f_out = file(output_file, 'w')
  dc_final = {}
  for f in file_list:
    f_in = file(f)
    dc_in = cPickle.load(f_in)
    key_dc_in = dc_in.keys()[0]
    dc_final[key_dc_in] = dc_in[key_dc_in]
    f_in.close()
  cPickle.dump(dc_final, f_out)
  f_out.flush()
  f_out.close()

def merge_special(file_list, output_file):
  f_out = file(output_file, 'w')
  dc_final = {}
  for m in file_list.keys(): 
    dc_final[m] = {}
    for f in file_list[m]:
      f_in = file(f)
      dc_in = cPickle.load(f_in)
      for key_dc_in in dc_in.keys(): dc_final[m][key_dc_in] = dc_in[key_dc_in]
      f_in.close()
  cPickle.dump(dc_final, f_out)
  f_out.flush()
  f_out.close()

AMasses    = range(8550,11000,150)
nJobs      = range(285,302) # High-pT: range(268,284)
nSubjobs   = 12

for index in range(len(nJobs)):
  nJob     = nJobs[index]
  AMass    = AMasses[index]
  file_list = []
  for nSubjob in range(nSubjobs): file_list.append(str(nJob)+'/'+str(nSubjob)+'/output/output.nsig')
  output_file = str(nJob)+'/output_'+str(AMass)+'.nsig'
  merge(file_list, output_file)

file_list = {}
for index in range(len(nJobs)):
  nJob     = nJobs[index]
  AMass    = AMasses[index]
  file_list[AMass] = []
  file_list[AMass].append(str(nJob)+'/output_'+str(AMass)+'.nsig')

output_file = 'output_CLs.nsig'
merge_special(file_list, output_file)
