###########################################################################################################################################
## Utilities.General: General P2VV utilities                                                                                             ##
##                                                                                                                                       ##
## authors:                                                                                                                              ##
##   GR,  Gerhard Raven,      Nikhef & VU, Gerhard.Raven@nikhef.nl                                                                       ##
##   JvL, Jeroen van Leerdam, Nikhef,      j.van.leerdam@nikhef.nl                                                                       ##
##                                                                                                                                       ##
###########################################################################################################################################

# clever switch construct from http://code.activestate.com/recipes/410692/
class switch(object):
    def __init__(self, value):
        self.value = value
        self.fall = False

    def __iter__(self):
        """Return the match method once, then stop"""
        yield self.match

    def match(self, *args):
        """Indicate whether or not to enter a case suite"""
        if self.fall or not args:
            return True
        elif self.value in args:
            self.fall = True
            return True
        else:
            return False


import sys
def numCPU( Max = sys.maxint ) :
    try : # needs >= 2.6
        import multiprocessing
        return min(Max,multiprocessing.cpu_count())
    except :
        import os
        ncpu = os.sysconf('SC_NPROCESSORS_ONLN')
        return min(Max,max( ncpu, 1 ))


def createProfile(name,data,pdf,npoints,param1,param1min,param1max,param2,param2min,param2max,NumCPU=8,Extend=True):
    print '**************************************************'
    print 'making profile for %s and %s'%(param1.GetName(),param2.GetName())
    print '**************************************************'

    nll = pdf.createNLL(data,RooFit.NumCPU(NumCPU),RooFit.Extended(Extend))
    profile = nll.createProfile(RooArgSet( param1,param2))
    return profile.createHistogram(name,         param1, RooFit.Binning(npoints,param1_min,param1_max)
                                  , RooFit.YVar( param2, RooFit.Binning(npoints,param2_min,param2_max))
                                  , RooFit.Scaling(False)
                                  )


# function for finding a splitted parameter in a simultaneous PDF
def getSplitPar( parName, stateName, parSet ) :
    from itertools import permutations
    stateName = stateName[ 1 : -1 ].split(';') if stateName.startswith('{') and stateName.endswith('}') else [ stateName ]
    if len(stateName) > 1 :
        fullNames = [ '%s_{%s}' % ( parName, ';'.join( comp for comp in perm ) )\
                     for perm in permutations( stateName, len(stateName) ) ]
    else :
        fullNames = [ ( '%s_%s' % ( parName, stateName[0] ) ) if stateName[0] else parName ]

    name = lambda par : par if type(par) == str else par.GetName()
    for par in parSet :
        if name(par) in fullNames : return par
    return None


# function for creating lists of split parameters and categories
def createSplitParsList( splitParsDict ) :
    # create lists of split categories and parameters
    splitParsDict = splitParsDict.copy()
    pars = splitParsDict.keys()
    splitPars = [ ]
    for par in pars :
        if par not in splitParsDict : continue
        splitPars.append( [ set( [par] ), splitParsDict.pop(par) ] )
        for par1 in pars :
            if par1 not in splitParsDict : continue
            if splitParsDict[par1] == splitPars[-1][1] :
                splitPars[-1][0].add(par1)
                splitParsDict.pop(par1)

    # sort lists of split categories and parameters
    compFunc = lambda a, b : cmp( a.GetName(), b.GetName() )
    for it in range( len(splitPars) ) :
        splitPars[it][0] = sorted( list( splitPars[it][0] ), compFunc )
        splitPars[it][1] = sorted( list( splitPars[it][1] ), compFunc )
    splitPars.sort( cmp = lambda a, b : cmp( a[0][0].GetName(), b[0][0].GetName() ) )

    return splitPars


def make_binning(data, var, n_bins):
    tmp = data.get().find(var.GetName())
    values = []
    for i in range(data.numEntries()):
        data.get(i)
        values.append((tmp.getVal(), data.weight()))

    s = sum(e[1] for e in values)
    d = s / float(n_bins)

    from operator import itemgetter
    values = sorted(values, key = itemgetter(0))

    bounds = [var.getMin()]
    total = 0

    for v, w in values:
        total += w
        if total >= d:
            total = 0
            bounds.append(v)

    def __ae(a, b, tol):
        return (abs(a-b) / max(abs(a), abs(b))) < tol

    if __ae(bounds[-1], var.getMax(), 0.05):
        bounds[-1] = var.getMax()
    else:
        bounds.append(var.getMax())

    bounds = [float('%4.3e' % e) for e in bounds]
    return bounds

def make_exp_binning(n_bins, t_min, t_max, tau = 1.5):
    # Make an exponential binning
    def next_bin(prev_bin, min_bin, max_bin):
        from math import e, log
        a = e ** (- min_bin / tau) - e ** (- max_bin / tau)
        return - tau * log(e ** (- prev_bin / tau) - a / n_bins)
    from array import array
    bins = array('d', [t_min])
    for i in range(n_bins - 1):
        bins.append(next_bin(bins[-1], t_min, t_max))
    bins.append(t_max)
    return bins

class input_paths_parser(dict):
    def __init__( self, **kwargs ):

        # identify site from hostname
        import subprocess, os
        host_name = subprocess.check_output(['hostname' ,'--fqdn'])
        self.atNikhef = 'nikhef.nl' in host_name.lower()
        self.atLxplus = 'cern.ch' in host_name.lower()

        if self.atNikhef:
            pass
        elif self.atLxplus:
            print 'P2VV - INFO: Running at a cern site, hostname: %s'%host_name

            # locate eos mount point
            eos_p2vv_inputs = kwargs.pop( 'EosInputsPath', '/lhcb/wg/B2CC/p2vv_fitting_package_inputs/Bs2JpsiPhi' )

            user_name = os.environ['USER']
            user_init = os.environ['USER'][0]
            eos_mount_point = '/afs/cern.ch/user/%s/%s/eos'%(user_init,user_name)

            if eos_mount_point and os.path.exists(eos_mount_point):
                self.other = eos_mount_point
            else:
                print 'P2VV - INFO: Cannot locate eos mount point at default locations.'
                self.other = raw_input('P2VV - INFO: Please provide mount point of eos. ( No quotes!! e.g. %s): '%eos_mount_point)

                if not os.path.exists(self.other):
                    self.other = raw_input('P2VV - INFO: Provided eos mount point does not exists or the input format is incorrect. Try again!!')
                    if not path.exists(self.other):
                        sys.exit( 'P2VV - INFO: Failed to access provided eos mount point. Extiting program.')

            # build inputs full path
            if self.other[-1] == '/':
                pass
            else:
                self.other += '/'
            self.other += eos_p2vv_inputs
        else:
            print """P2VV - ERROR: Unknown host site (%s). Do not know where to find inputs. \n
            Either Edit input_paths_parser() in P2VV/Utilities/General.py and accomodate a new host,
            or create your own script under scripts/. Do not edit files under /examples!!"""%host_name


