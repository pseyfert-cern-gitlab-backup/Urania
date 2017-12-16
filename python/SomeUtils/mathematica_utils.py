def math_executable(filename):
    import os
    if os.path.exists("/afs/cern.ch/project/parc/math80/Executables/"):
        print "Using lxplus mathematica"
        math = "/afs/cern.ch/project/parc/math80/Executables/math"
    else:
        print "Not on lxplus. Trying simply 'math'"
        math = "math"
    os.system(math + "< " + filename)
