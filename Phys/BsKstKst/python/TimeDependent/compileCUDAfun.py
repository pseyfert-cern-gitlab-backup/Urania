import pycuda.autoinit
import pycuda.cumath
import pycuda.driver as cudriver
import pycuda.gpuarray as gpuarray
from iminuit import Minuit
from ModelBricks import Parameter, Free, Cat, ParamBox, cuRead
from tools import plt
from timeit import default_timer as timer

print '\nCompiling CUDA PDF ...'
mod = cuRead("../../src/TimeDependent/Bs2KpiKpiTDPDF.cu", no_extern_c = True)
print 'OK.'
