from os import system as shell
shell("bsub -q 2nd lsf.csh 0.01")

for i in range(400):
    shell("bsub -q 2nd lsf.csh " + str(0.1 + 0.05*i))
    #shell("bsub -q 2nd lsf.csh " + str(0.1*50 + 0.2*i))
    #$shell("bsub -q 2nd lsf.csh " + str(0.1*100 + 0.2*i))

