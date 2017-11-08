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

