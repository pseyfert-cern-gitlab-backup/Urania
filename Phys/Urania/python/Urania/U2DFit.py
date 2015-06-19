from sympy import *
from ROOT import *
from scipy import random as rnd, array
from SomeUtils.GLBasic import UniFunc
#from SomeUtils.numericFunctionClass import NF
import scipy.special as special
#### Build dictionary

dict_scipy_special = {}
for key in dir(special): dict_scipy_special[key] = getattr(special,key)


def TGraphToList(g):
    from ROOT import Double
    l =[]
    from scipy import linspace
    xl = []#linspace(5., 8., g.GetN())
    yl = []#linspace(5., 8., g.GetN())
    for i in range(g.GetN()):
        x = Double()
        y = Double()
        g.GetPoint(i,x,y)
	xl.append(float(x))
	yl.append(float(y))
        #l.append([float(x),float(y)])
    return xl, yl

def lambdify_for_fit(symfunc,x,mods =("numpy", dict_scipy_special)):
        from sympy.utilities.lambdify import lambdify
        symbols = symfunc.free_symbols
        symbols.remove(x)
        p = Tuple.fromiter(symbols)  ## making something that the fit will digest
        fitfunc = lambdify((p,x),symfunc,mods)
        return fitfunc
                    

        
def fit2D(x, y , func, init_params, state =0):
    from scipy import array, optimize
    
    errfunc = lambda p, x, y: func(p, x) - y
    p1, success = optimize.leastsq(errfunc, init_params[:], args=(x, y))
    if success: return p1
    #from scipy import random as rnd
    print "Second try"
    init_params_2 = len(init_params)*[0.]
    for i in range(len(init_params)):
        init_params2[i] = 2*round( rnd.random() -0.5)*init_params[i]
    p1, success = optimize.leastsq(errfunc, init_params2[:], args=(x, y))  ### full_ouput = 1
    if success: return p1
    print "Third try"
    for i in range(len(init_params)):
        init_params2[i] = 100*init_params[i]
    p1, success = optimize.leastsq(errfunc, init_params2[:], args=(x, y))
    if success: return p1
    print "Fourth Try"
    if state == 0 :
        state += 1
        print "Fit state changed to 1. Rebooting"
        return fit2D(x,y,func,init_params,state)
    elif state == 1 :
        state == 2
        print "Fit state changed to 2. Rebooting in different way. I forsee this is not wonna work"
        return fit2D(x,y,func,init_params2,state)
    else :
        print "I surrender"
        return "FAILED"
    
    
    
class UGraphFitBasis:
    def __init__(self, thing, function_list= [], param_list = [[]], cosmetic = 0, pRanges = [], cos_quick = 1, cos_tolerance = 0.1):
        """
        thing can be a list of [x,y] points, a list of [ [x],[y]] , a TGraph or a TH1F
        function_list can be a <lambda> function , or a list of those. You can also leave it blank and
        add functions later
        param_list is a list with the initial values of the parameters (or a list containing a list of those,
        if you plan to fit more than one function)
        """
        if "SetPoint" in dir(thing):
            x, y = TGraphToList(thing)
        if "GetBinContent" in dir(thing):
            x, y = TH1FToList(thing)
        if isinstance(thing,list):
            if len(thing[0]) == 2:
                x, y =[], []
                for entry in thing:
                    x.append(entry[0])
                    y.append(entry[1])
            else:
                x, y = thing[0], thing[1]
	if isinstance(function_list,list): self.function_list = function_list
        else: self.function_list = [function_list]
        if isinstance(param_list[0],list): self.param_list = param_list
        else: self.param_list = [param_list]

	self.x = array(x)
        self.y = array(y)
	
	if len(x) < 30:
		print "For unknown reasons, the underlying fitter sometimes complains when the number of points is smaller than 30"
		print "even if afterwards it reacts with an identical input"
		print "I'll try to cheat it. Wish me good luck"
		factor = int(30./len(x))+1
		
		self.x = array(factor*list(x))
		self.y = array(factor*list(y))
		#print len(self.x)
		#print len(self.y)
			  
		#self.lambdify()
		#self.checkParams()
		#self.fitAll()
		#print "still here ... "
		
        
        self.Ysize =  max(self.y)-min(self.y)
        self.pRanges = pRanges
        
        self.cosmetic_fit = cosmetic
        self.Nfuncs = len(self.param_list)
        if cosmetic and not pRanges:
            print "If cosmetic is set to 1, a parameter scan will be run. For this, you need to specify ranges in pRanges [ [[mins], [max]]]"
            return "ERROR"
        self.cos_quick = cos_quick
        self.cos_tolerance = cos_tolerance
        self.lambdify()
        #if self.cosmetic_fit: self.runParameterScan()
        self.checkParams()
        self.fitAll()
        self.cosmetic_FOM = len(self.param_list)*[1.]
        self.checkCosmeticsAll()
        
        if not cosmetic:return
        xx = min(self.cosmetic_FOM)
        if xx > self.cos_tolerance: self.CosmeticFitAll()
        self.checkCosmeticsAll()
        
        
    def CosmeticFitAll(self):
        for i in range(self.Nfuncs):
            self.CosmeticFit(i, quick = self.cos_quick, tolerance = self.cos_tolerance)
            
    def CosmeticFit(self, i = 0, N = 1000, quick = 0, tolerance =0.1):
        print "Using the cosmetic FOM to assist Levenberg-Marquardt algortithm"
        mins = self.pRanges[i][0]
        maxs = self.pRanges[i][1]
        #print mins
        #print maxs
        p = []
        
        for j in range(N):
            pj = len(self.pRanges[i][0])*[0.]
            for k in range(len(self.pRanges[i][0])):
                xk = mins[k] + rnd.random()*(maxs[k]-mins[k])
                pj[k] = xk
            #dy = sum(abs(self.function_list[i](pj,self.x)-self.y))*1./len(self.y)
            self.fit(i, params = pj, printflag = 0)
            dy = sum(abs(self.function_list[i](self.fitRes[i],self.x)-self.y))*1./len(self.y)
            xx = dy/self.Ysize
            if not xx == xx: xx = 999999999999999
            p.append([xx,pj])
            if quick and xx < tolerance: break
        p.sort()
        print p[0]
        self.param_list[i] = p[0][1]
        self.fit(i)
        return p
        
                           
    
    def lambdify(self):
        from sympy.utilities.lambdify import lambdify
        test = lambda zz, x : zz[0]*x + zz[1]*x**2
        for i in range(len(self.function_list)):
            ifunc = self.function_list[i]
            if isinstance(ifunc,test.__class__):continue
            if "sympy" in str(ifunc.__class__):
                print ifunc , "is a symbolic object. Lambdifying it ...."
                self.function_list[i] = lambdify_for_fit(ifunc)
            if isinstance(ifunc, str):
                self.function_list[i] = lambdify("p,x",self.function_list[i],("numpy",dict_scipy_special))
        return 1
    def checkParams(self):
        #from scipy import random as rnd
        for i in range(len(self.param_list)):
            if not self.param_list[i]:
                self.param_list[i] = 30*[rnd.random()]
                
    def fit(self, i=0, params = [], printflag = 1):
        if not params: params =self.param_list[i]
        if printflag: print "Fitting with initial parameters: ", params
        self.fitRes[i] = fit2D(self.x, self.y , self.function_list[i],params)
        if isinstance(self.fitRes,str): return
        
    def checkCosmetics(self, i = 0):
        print "0-0-0-0-0 Function number ", i
        xx = self.CosmeticFOM(i)
        self.cosmetic_FOM[i] = xx
        if xx > 0.1 and not self.cosmetic_fit:
            print "LevenbergMarquardt alfortighm finish. But looking by eye at the plot I do not like it"
            print "You can give a new try by setting cosmetic_fit = 1, specify range for parameter scan, and redo fitAll()"
    def checkCosmeticsAll(self):
        for i in range(self.Nfuncs): self.checkCosmetics(i)
        
        
    def CosmeticFOM(self,i=0):
        sy = self.Ysize
        dy = sum(abs(self.function_list[i](self.fitRes[i],self.x)-self.y))*1./len(self.y)
        out = dy/sy
        if not out == out: return 999999999999999
        return out
        
        
    def fitAll(self):
        self.fitRes = {}
        for i in range(len(self.function_list)):self.fit(i)
        
    def rotate90(self):
        x0 = self.y
        y0 = self.x
        self.x = x0
        self.y = y0
    
    def plot(self, i=0, point_opt = "go", line_opt = "orange", _range = [], Min ="",Max = "",save = 0, labelx = "", labely = ""):
        from scipy import array
        from pylab import plot, show, savefig, xlabel, ylabel
        if _range: _range = array(_range)
        else:
            if isinstance(Min, str) or isinstance(Max, str):
                Min = min(self.x)
                Max = max(self.x)
            for j in range(101):
                _range.append(Min + j*0.01*(Max-Min))
            _range = array(_range)
                
        self.the_plots = plot(self.x, self.y, point_opt, _range, self.function_list[i](self.fitRes[i], _range), line_opt)
        xlabel(labelx)
        ylabel(labely)
        if save: savefig(save)
        else: print "The pylab saver from the GUI didn't use to work....If you want to save the plot, call this method with save = <whatevername>"
        
        return show()


class SingleFit(UGraphFitBasis):
    def __init__(self, thingie, function, mins, maxs):
        UGraphFitBasis.__init__(self, thingie, function,param_list = len(mins)*[1.],cosmetic = 1, pRanges = [[mins ,maxs]])
        

## from scipy import *
## def load_test():
##     num_points = 150
##     Tx = linspace(5., 8., num_points)
##     tX = 11.86*cos(2*pi/0.81*Tx-1.32) + 0.64*Tx+4*((0.5-rand(num_points))*exp(2*rand(num_points)**2))
##     fitfunc = lambda p, x: p[0]*cos(2*pi/p[1]*x+p[2]) + p[3]*x
##     p0 = [-15., 0.8, 0., -1.]

##     return tX, Tx, fitfunc, p0

## tX, Tx, fitfunc, p0 = load_test()


        
        
    
    
    
