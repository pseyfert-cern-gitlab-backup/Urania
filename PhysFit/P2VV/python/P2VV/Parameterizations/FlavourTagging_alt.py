from P2VV.Parameterizations.GeneralUtils import _util_parse_mixin, _util_extConstraints_mixin, _util_conditionalObs_mixin
###########################################################################################################################################
## Tagging parameters classes ##
################################

# Class takes as input a dictionary of taggers with the format:
# [ { 'name' : "EX", 'tagName' : "EX", mistagName : "EX"
# , 'p0' : [CV,lowerError,upperError]
# , 'p1' : [CV,lowerError,upperError]
# , 'etaB'   : [CV,lowerError,upperError] 
# , 'Delta p0' : [CV,lowerError,upperError]
# , 'Delta p1' : [CV,lowerError,upperError]
# , 'DeltaEtaB'   : [CV,lowerError,upperError] 
#   }, ...
# ]
class TaggingGeneric ( _util_parse_mixin, _util_extConstraints_mixin, _util_conditionalObs_mixin ):
    def __init__( self, **kwargs ) :
        
        self._taggers = kwargs.pop('Taggers')
        obsTag=kwargs.pop('TagObs')
        fix=kwargs.pop('Fix', False)
        cache=kwargs.pop('Cache', False)
        NamePF = kwargs.pop('Name')
        assert len(self._taggers)>0, "Please provide taggers"
        
        # Calibrated mistag
        from P2VV.RooFitWrappers import FormulaVar
        # 0: uncalibrated mistag, 1: p0, 2: Delta p0, 3: p1, 4: Delta p1
        # 5, etaB, 6: Delta eta B
        _calibMistagB = lambda name, mistag, calparams  :\
                FormulaVar( Name = NamePF + name+"_calibratedMistagB", Formula = "@1+(@2*0.5) + (@3+(@4*0.5))*( @0 - (@5+(@6*0.5)) )", Arguments = [mistag]+calparams )
        _calibMistagBbar = lambda name, mistag, calparams  :\
                FormulaVar( Name = NamePF + name+"_calibratedMistagBbar", Formula = "@1-(@2*0.5) + (@3-(@4*0.5))*( @0 - (@5-(@6*0.5)) )", Arguments = [mistag]+calparams )

        names=[]
        decisions=[]
        mistagsB=[]
        mistagsBbar=[]
        
        self.constraints = set()
        self.conditionals = set()
        from P2VV.RooFitWrappers import Pdf
        from ROOT import RooGaussian as Gaussian
        _constrainCalib = lambda param, mean, sigma :\
                Pdf(  Name = NamePF + param.GetName() + '_constraint', Type = Gaussian, Parameters = [  
                    param
                    , self._parseArg( NamePF + 'meanConstr_%s' % param.GetName(),  {}, Value = mean, ObjectType = 'ConstVar' )
                    , self._parseArg( NamePF + 'sigmaConstr_%s' % param.GetName(),  {}, Value = sigma, ObjectType = 'ConstVar' )
                    ] )

        for tagger in self._taggers:
            NameT = tagger['name']
            names.append(NameT)

            tagName = tagger['tagName']
            mistagName = tagger['mistagName']
            
            tag = obsTag[tagger['name']+"_"+tagger['tagName']]
            #self.conditionals|={tag}
            self.conditionals.add(tag)
            mistag = obsTag[tagger['name']+"_"+tagger['mistagName']]
            #self.conditionals|={mistag}
            self.conditionals.add(mistag)
            
            # Now we deal with calibration parameters *****************************************************************
            # p0
            if 'p0' not in tagger:
                # assume perfect calibration
                var_p0 = self._parseArg( 'p0_%s' % NameT , {}, Title = 'p0 %s' % NameT, Unit = '', Value = 0.0, Constant = fix)
            elif len(tagger['p0']==1):
                # fix value to CV
                p0 = tagger['p0'][0]
                var_p0 = self._parseArg( 'p0_%s' % NameT , {}, Title = 'p0 %s' % NameT, Unit = '', Value = p0, Constant = fix)
            else:
                # Constrain parameter to provided values
                assert len(tagger['p0'])==3, "Either give no tagger, a CV, or a CV with upper and lower errors"
                var_p0 = self._parseArg( 'p0_%s' % NameT , {}, Title = 'p0 %s' % NameT, Unit = '', Value = p0, Constant = fix )
                self.constraints.add( _constrainCalib( var_p0, tagger['p0'][1], tagger['p0'][2] ) )
            
            # Delta p0
            if 'Deltap0' not in tagger:
                # assume perfect calibration
                var_Dp0 = self._parseArg( 'Deltap0_%s' % NameT , {}, Title = 'Deltap0 %s' % NameT, Unit = '', Value = 0.0, Constant = fix)
            elif len(tagger['Deltap0']==1):
                # fix value to CV
                Deltap0 = tagger['Deltap0'][0]
                var_Dp0 = self._parseArg( 'Deltap0_%s' % NameT , {}, Title = 'Deltap0 %s' % NameT, Unit = '', Value = Deltap0, Constant = fix )
            else:
                # Constrain parameter to provided values
                assert len(tagger['Deltap0'])==3, "Either give no tagger, a CV, or a CV with upper and lower errors"
                var_Dp0 = self._parseArg( 'Deltap0_%s' % NameT , {}, Title = 'Deltap0 %s' % NameT, Unit = '', Value = Deltap0, Constant = False )
                self.constraints.add( _constrainCalib( var_Dp0, tagger['Deltap0'][1], tagger['Deltap0'][2] ) )
            
            # p1
            if 'p1' not in tagger:
                # assume perfect calibration
                var_p1 = self._parseArg( 'p1_%s' % NameT , {}, Title = 'p1 %s' % NameT, Unit = '', Value = 1.0, Constant = fix )
            elif len(tagger['p1']==1):
                # fix value to CV
                p1 = tagger['p1'][0]
                var_p1 = self._parseArg( 'p1_%s' % NameT , {}, Title = 'p1 %s' % NameT, Unit = '', Value = p1, Constant = fix )
            else:
                # Constrain parameter to provided values
                assert len(tagger['p1'])==3, "Either give no tagger, a CV, or a CV with upper and lower errors"
                var_p1 = self._parseArg( 'p1_%s' % NameT , {}, Title = 'p1 %s' % NameT, Unit = '', Value = p1, Constant = False )
                self.constraints.add( _constrainCalib( var_p1, tagger['p1'][1], tagger['p1'][2] ) )
            
            # Delta p1
            if 'Deltap1' not in tagger:
                # assume perfect calibration
                var_Dp1 = self._parseArg( 'Deltap1_%s' % NameT , {}, Title = 'Deltap1 %s' % NameT, Unit = '', Value = 0.0, Constant = fix )
            elif len(tagger['Deltap1']==1):
                # fix value to CV
                Deltap0 = tagger['Deltap1'][0]
                var_Dp1 = self._parseArg( 'Deltap1_%s' % NameT , {}, Title = 'Deltap1 %s' % NameT, Unit = '', Value = Deltap1, Constant = fix )
            else:
                # Constrain parameter to provided values
                assert len(tagger['Deltap1'])==3, "Either give no tagger, a CV, or a CV with upper and lower errors"
                var_Dp1 = self._parseArg( 'Deltap1_%s' % NameT , {}, Title = 'Deltap1 %s' % NameT, Unit = '', Value = Deltap1, Constant = False )
                self.constraints.add( _constrainCalib( var_Dp1, tagger['Deltap1'][1], tagger['Deltap1'][2] ) )
            
            # eta bar
            if 'etaB' not in tagger:
                # assume perfect calibration
                var_etaB = self._parseArg( 'etaB_%s' % NameT , {}, Title = 'etaB %s' % NameT, Unit = '', Value = 0.0, Constant = fix )
            elif len(tagger['etaB']==1):
                # fix value to CV
                etaB = tagger['etaB'][0]
                var_etaB = self._parseArg( 'etaB_%s' % NameT , {}, Title = 'etaB %s' % NameT, Unit = '', Value = etaB, Constant = fix )
            else:
                # Constrain parameter to provided values
                assert len(tagger['etaB'])==3, "Either give no tagger, a CV, or a CV with upper and lower errors"
                var_etaB = self._parseArg( 'etaB_%s' % NameT , {}, Title = 'etaB %s' % NameT, Unit = '', Value = etaB, Constant = False )
                self.constraints.add( _constrainCalib( var_etaB, tagger['etaB'][1], tagger['etaB'][2] ) )
            
            # Delta eta bar
            if 'DeltaEtaB' not in tagger:
                # assume perfect calibration
                var_DeltaB = self._parseArg( 'DeltaEtaB_%s' % NameT , {}, Title = 'Delta etaB %s' % NameT, Unit = '', Value = 0.0, Constant = fix )
            elif len(tagger['DeltaEtaB']==1):
                # fix value to CV
                etaB = tagger['DeltaEtaB'][0]
                var_DeltaB = self._parseArg( 'DeltaEtaB_%s' % NameT , {}, Title = 'DeltaEtaB %s' % NameT, Unit = '', Value = DeltaEtaB, Constant = fix )
            else:
                # Constrain parameter to provided values
                assert len(tagger['DeltaEtaB'])==3, "Either give no tagger, a CV, or a CV with upper and lower errors"
                var_DeltaB = self._parseArg( 'DeltaEtaB_%s' % NameT , {}, Title = 'DeltaEtaB %s' % NameT, Unit = '', Value = DeltaEtaB, Constant = False )
                self.constraints.add( _constrainCalib( var_DeltaEtaB, tagger['DeltaEtaB'][1], tagger['DeltaEtaB'][2] ) )
            # ****************************************************************************************************************************

            # Add calibrated tagger information to lists
            decisions.append(tag)
            mistagsB.append(_calibMistagB(NameT,mistag,[var_p0,var_Dp0,var_p1,var_Dp1,var_etaB,var_DeltaB]))
            mistagsBbar.append(_calibMistagBbar(NameT,mistag,[var_p0,var_Dp0,var_p1,var_Dp1,var_etaB,var_DeltaB]))

        from P2VV.RooFitWrappers import Product, Addition
        _TagDilSegPlus = lambda name, tag, mistagB, mistagBbar  :\
                FormulaVar( Name = NamePF + name+"_TagDilutionPlus", Formula = "@0>0 ? 1.0+@0*(1.0-2.0*@1) : 1.0+@0*(1.0-2.0*@2)", Arguments = [tag,mistagB,mistagBbar])
        _TagDilSegMinus = lambda name, tag, mistagB, mistagBbar  :\
                FormulaVar( Name = NamePF + name+"_TagDilutionMinus", Formula = "@0>0 ? 1.0-@0*(1.0-2.0*@1) : 1.0-@0*(1.0-2.0*@2)", Arguments = [tag,mistagB,mistagBbar])
        _TagDilSegPlusO = lambda name, tag, mistagB, mistagBbar  :\
                FormulaVar( Name = NamePF + name+"_TagDilutionPlus_Other", Formula = "@0>0 ? 1.0+@0*(1.0-2.0*@2) : 1.0+@0*(1.0-2.0*@1)", Arguments = [tag,mistagB,mistagBbar])
        _TagDilSegMinusO = lambda name, tag, mistagB, mistagBbar  :\
                FormulaVar( Name = NamePF + name+"_TagDilutionMinus_Other", Formula = "@0>0 ? 1.0-@0*(1.0-2.0*@2) : 1.0-@0*(1.0-2.0*@1)", Arguments = [tag,mistagB,mistagBbar])
        
        from P2VV.RooFitWrappers import ConstVar
        minus = ConstVar( Name = 'minus', Value = -1. )
        argsBPlus=[]
        argsBMinus=[]
        argsOtherBPlus=[]
        argsOtherBMinus=[]
        for n in range(len(mistagsB)):
            argsBPlus.append(_TagDilSegPlus(names[n],decisions[n],mistagsB[n],mistagsBbar[n]))
            argsBMinus.append(_TagDilSegMinus(names[n],decisions[n],mistagsB[n],mistagsBbar[n]))
            argsOtherBPlus.append(_TagDilSegPlusO(names[n],decisions[n],mistagsB[n],mistagsBbar[n]))
            argsOtherBMinus.append(_TagDilSegMinusO(names[n],decisions[n],mistagsB[n],mistagsBbar[n]))
        self.ProdBPlusPDF = self._parseArg( "Prod_B_Plus", { }, Arguments = argsBPlus, ObjectType = 'Product' )
        self.ProdBMinusPDF = self._parseArg( "Prod_B_Minus", { }, Arguments = argsBMinus, ObjectType = 'Product' )
        self.ProdOtherBPlusPDF = self._parseArg( "Prod_OtherB_Plus", { }, Arguments = argsOtherBPlus, ObjectType = 'Product' )
        self.ProdOtherBMinusPDF = self._parseArg( "Prod_OtherB_Minus", { }, Arguments = [minus]+argsOtherBMinus, ObjectType = 'Product' )

        # make combined D1 and D2 factors
        self._D1 = self._parseArg( "D1", {}, Arguments = [self.ProdBPlusPDF,self.ProdBMinusPDF], ObjectType = 'Addition' ) 
        self._D2 = self._parseArg( "D2", {}, Arguments = [self.ProdOtherBPlusPDF,self.ProdOtherBMinusPDF], ObjectType = 'Addition' ) 

        from ROOT import RooArgSet, RooCategory, RooRealVar
        if cache:
            obs = RooArgSet( o._var for o in obsTag.values() if isinstance(o._var,RooRealVar))
            print obs
            print 'P2VV - INFO: invoking parameterizeIntegral for tagging mistag' 
            self._D1.setParameterizeIntegral( obs )
            self._D2.setParameterizeIntegral( obs )
            for o in obs:
                print 'P2VV::TimeResolution: adding cache binning wth 20 bins to %s' % o.GetName()
                o.setBins( 20 , 'cache' )
            
        
        # process constraints and conditional observables
        BaseClassArgs={}
        BaseClassArgs['Conditionals']=self.conditionals
        BaseClassArgs['Constraints']=self.constraints
        #
        _util_conditionalObs_mixin.__init__( self, BaseClassArgs )
        _util_extConstraints_mixin.__init__( self, BaseClassArgs )
        self._check_extraneous_kw( kwargs )

class MistagPdf( _util_parse_mixin, _util_extConstraints_mixin, _util_conditionalObs_mixin ):
    def __init__( self, **kwargs ) :
        
        #pdf = kwargs.pop('pdf')
        obs = kwargs.pop('Observables')
        data = kwargs.pop('Data')

        from P2VV.RooFitWrappers import HistPdf
        self.mistagPdf = HistPdf("mistag_PDF"
                , Observables=obs
                , Data=data)
        #self.prodPdf = self._parseArg( "ProdPDF_Total", { }, Arguments = [pdf,mistagPdf], ObjectType = 'Product' )
    def pdf(self):
        return self.mistagPdf
