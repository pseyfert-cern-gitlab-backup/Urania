from GLBasic import *

class Generator:
    def __init__(self, ch, keys, separate_constants = 1):
        self.keys = []
        self.l = []
        self.ctes = {}
        for key in keys:
            thingie = ch.takeKey(key)
            if max(thingie) == min(thingie) and separate_constants:
                print "Treating ",key, " as constant"
                self.ctes[key] = thingie[0]
                continue
            self.keys.append(key)
            self.l.append(thingie)
        self.op = UnCorrGaussOperator(self.l)
        self.Nsource = len(ch)
        

    def generate_matrix(self,N): return self.op.generate(N)
    def generate(self, N):
        M = self.generate_matrix(N)
        M2 = M.transpose()
        l = []
        for i in range(N):
            dc = {}
            entry = M2[i].tolist()[0]
            for j in range(self.op.Nvars):
                dc[self.keys[j]] = entry[j]
            l.append(dict(dc,**self.ctes))
        return l

class Cat:
    def __init__(self, chlist, keys):#, catvars):
        self.gens = []
        self.catvals = []
        self.Nsource = 0
        self.Ncats = len(chlist)
        #def get_catvals(ch):
         #   out = {}
          #  for key in catvars: out[key] = ch[0][key]
           # return out
        
        for i in range(self.Ncats):
            self.gens.append(Generator(chlist[i],keys))
            self.Nsource += self.gens[i].Nsource
            #self.catvals.append(get_catvals(chlist[i]))
        def pval(gen): return gen.Nsource*1./self.Nsource
        self.pvals = map(pval,self.gens)

    def generate(self,N):
        Ngen = rnd.multinomial(N, self.pvals)
        l = []
        for k in range(self.Ncats):
            l+=self.gens[k].generate(Ngen[k])
        return l


    ## def generate(self,N):
##         Ngen = rnd.multinomial(N, self.pvals)
##         l = []
##         for k in range(self.Ncats):
##             Ni = Ngen[k]
##             op = self.gens[k]
##             M = op.generate_matrix(Ni)
##             M2 = M.transpose()
##             catvals = self.catvals[k]
##             for i in range(Ni):
##                 dc = {}
##                 entry = M2[i].tolist()[0]
##                 for j in range(op.op.Nvars):
##                     dc[self.keys[j]] = entry[j]
##                 l.append(dict(dc,**catvals))
            
##         return l
