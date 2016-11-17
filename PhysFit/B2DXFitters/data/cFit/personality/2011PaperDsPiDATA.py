# personality for 2011 Paper - mode DsPi
{
        'IsToy':                False,
        'DataFileName':         ('/afs/cern.ch/work/g/gligorov/public/Bs2DsKPlotsForPaper/NominalFit/WS_Mass_DsPi_5M_BDTGA.root' if haveAFS else
	    os.environ['B2DXFITTERSROOT']+'/scripts/paperv3a-dsk-DATA/NominalFit/WS_Mass_DsPi_5M_BDTGA.root'),
        'DataWorkSpaceName':    'FitMeToolWS',
        'DataSetNames':         'combData',
        'Modes': [
            'Bs2DsPi',
            'Bd2DPi', 'Bs2DsstPi',
            'Bd2DsPi',
            'Bs2DsK',
            'Lb2LcPi',
            'CombBkg'
            ],
        'SampleCategories': [
            'nonres', 'phipi', 'kstk', 'kpipi', 'pipipi'
            ],
        'DeltaMs':                      17.768, # in ps^{-1}
        'GammaLb':			0.676, # in ps^{-1}
        'WeakPhase': {
            'Bs2DsK':           70. / 180. * pi,
            'Bs2DsstK':         70. / 180. * pi,
            'Bs2DsKst':         70. / 180. * pi,
            'Bs2DsstKst':	70. / 180. * pi,
            'Bd2DPi':           70. / 180. * pi
            },
        'StrongPhase': {
            'Bs2DsK':           30. / 180. * pi,
            'Bs2DsstK':         -150. / 180. * pi,
            'Bs2DsKst':         -150. / 180. * pi,
            'Bs2DsstKst':       30. / 180. * pi,
            'Bd2DPi':           30. / 180. * pi
            },
        'AcceptanceCorrectionFile': None,
        'CombineModesForEffCPObs': [ ],
        'Bs2DsKCPObs':                  'LambdaPhases',
        'NEvents':			[ 33672. ],
	'DataSetVarNameMapping': {
	    'sample':   'sample',
	    'mass':     'lab0_MassFitConsD_M',
	    'pidk':     'lab1_PIDK',
            'dsmass':   'lab2_MM',
            'time':     'lab0_LifetimeFit_ctau',
            'timeerr':  'lab0_LifetimeFit_ctauErr',
            'mistag':   'tagOmegaComb',
            'qf':       'lab1_ID',
            'qt':       'tagDecComb',
            'weight':   'nSig_both_nonres_Evts_sw+nSig_both_phipi_Evts_sw+nSig_both_kstk_Evts_sw+nSig_both_kpipi_Evts_sw+nSig_both_pipipi_Evts_sw'
            },
	'GammaCombBkg': [0.9944595961930113, 1.1013800661491908, 1.1831661712064796, 1.587632962259566],
	'DGammaCombBkg': [1.0654394467936141, 0.9107177671397291, 1.421727928077652, 1.3131440797097205],
        'CombBkg_D': [-0.8702277122156367, -0.8331423856820918, -0.9734197117683249, -0.8883029928866554],
        'FitRanges': {
		'time':     [0.4, 15.],
		'timeerr':  [1e-6, 0.25],
		'mistag':   [0., 0.5],
		'mass':     [5320., 5420.],
		'dsmass':   [1930., 2015.],
		'pidk':     [0., 150.]
		},
        'MassTemplateFile':         ('/afs/cern.ch/work/g/gligorov/public/Bs2DsKPlotsForPaper/NominalFit/WS_Mass_DsPi_5M_BDTGA.root' if haveAFS else
	    os.environ['B2DXFITTERSROOT']+'/scripts/paperv3a-dsk-DATA/NominalFit/WS_Mass_DsPi_5M_BDTGA.root'),
        'MassTemplateWorkspace':	'FitMeToolWS',
        'MassInterpolation':		False,
        'NTaggers':                     3,
        'TagEff':                    {
            'Bs2DsPi': [ 0.3870 * (1. - 0.4772), 0.4772 * (1. - 0.3870), 0.3870 * 0.4772 ],
            'Lb': [ 0.3870, 0.4772 ],
            'Bd': [ 0.3870, 0.4772 ],
            },
        'MistagTemplates': {
            'Bs2DsPi': [
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_1',
                    'VarName': 'tagOmegaComb', },
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_2',
                    'VarName': 'tagOmegaComb', },
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_3',
                    'VarName': 'tagOmegaComb', },
                ],
            'Bd2DPi': [
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_BDPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_1',
                    'VarName': 'tagOmegaComb', },
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_BDPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_2',
                    'VarName': 'tagOmegaComb', },
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_BDPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_3',
                    'VarName': 'tagOmegaComb', },
                ],
            'CombBkg': [
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_CombBkg.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_1',
                    'VarName': 'tagOmegaComb', },
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_CombBkg.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_2',
                    'VarName': 'tagOmegaComb', },
                {   'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Mistag_CombBkg.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'sigMistagPdf_3',
                    'VarName': 'tagOmegaComb', },
                ],
            },
        'MistagCalibrationParams': {
                'Bs2DsPi': [
                    [ [ 0.376730, 1.048155, 0.371147 ], [ 0.365517, 0.950216, 0.371147 ] ],
                    [ [ 0.404896, 0.995879, 0.414892 ], [ 0.424801, 1.004340, 0.414892 ] ],
                    [ [ 0.338363, 1.027861, 0.338493 ], [ 0.338781, 0.971845, 0.338493 ] ],
                    ],
                'Bd': [
                    [ [ 0.376730, 1.048155, 0.371147 ], [ 0.365517, 0.950216, 0.371147 ] ],
                    [ [ 0.5, 0., 0. ], [ 0.5, 0., 0. ] ],
                    [ [ 0.338363, 1.027861, 0.338493 ], [ 0.338781, 0.971845, 0.338493 ] ],
                    ],
                },
        'Constraints': {
                'GammaLb': 0.006,
                'Bd2DPi_lambda': 0.3 * 0.0187,
                'Bd2DPi_avgSSbar': [ '0.5*(@0+@1)', ['Bd2DPi_S', 'Bd2DPi_Sbar'], +0.046, 0.023 ],
                'Bd2DPi_difSSbar': [ '0.5*(@0-@1)', ['Bd2DPi_S', 'Bd2DPi_Sbar'], -0.022, 0.021 ],
                'Bd_AsymProd': 0.01,
		'Bs_AsymProd': 0.01,
		'Lb_AsymProd': 0.03,
		'CombBkg_AsymProd': 0.03,
		'Bs2DsK_AsymDet':	0.005,
		'Bd2DPi_AsymDet':	0.01,
		'Bd2DsPi_AsymDet':	0.01,
		'Bs2DsPi_AsymDet':	0.01,
		'Lb2LcPi_AsymDet':	0.03,
		'CombBkg_AsymDet':	0.01,
		'Bs2DsstPi_AsymDet':	0.01,
                #'multivar_Bs2DsPiMistagCalib_p0p1': [
                #    [   'Bs2DsPi_Mistag0CalibB_p0', 'Bs2DsPi_Mistag0CalibB_p1',
                #        'Bs2DsPi_Mistag1CalibB_p0', 'Bs2DsPi_Mistag1CalibB_p1',
                #        'Bs2DsPi_Mistag2CalibB_p0', 'Bs2DsPi_Mistag2CalibB_p1',
                #        'Bs2DsPi_Mistag0CalibBbar_p0', 'Bs2DsPi_Mistag0CalibBbar_p1',
                #        'Bs2DsPi_Mistag1CalibBbar_p0', 'Bs2DsPi_Mistag1CalibBbar_p1',
                #        'Bs2DsPi_Mistag2CalibBbar_p0', 'Bs2DsPi_Mistag2CalibBbar_p1', ],
                #    [   0.004389, 0.039917, 0.007146, 0.148797, 0.005959, 0.038725,
                #        0.004395, 0.040072, 0.011414, 0.150355, 0.006030, 0.039962, ],
                #    [   [  1.000000000, -0.111790756,  0.000000000,  0.000000000,  0.495659195, -0.121263673,  0.883403568, -0.090341177,  0.000000000,  0.000000000,  0.436308995, -0.115934567 ],
                #        [ -0.111790756,  1.000000000,  0.000000000,  0.000000000, -0.170723691,  0.368653977, -0.090433543,  0.808300854,  0.000000000,  0.000000000, -0.138612127,  0.303210400 ],
                #        [  0.000000000,  0.000000000,  1.000000000, -0.122610568,  0.658158523, -0.541239353,  0.000000000,  0.000000000,  0.938782519, -0.120298908,  0.633382320, -0.525375965 ],
                #        [  0.000000000,  0.000000000, -0.122610568,  1.000000000, -0.631056425,  0.811985505,  0.000000000,  0.000000000, -0.122445304,  0.986409445, -0.608419498,  0.787887823 ],
                #        [  0.495659195, -0.170723691,  0.658158523, -0.631056425,  1.000000000, -0.874463407,  0.436823522, -0.137898963,  0.622128000, -0.622176239,  0.940276558, -0.841479510 ],
                #        [ -0.121263673,  0.368653977, -0.541239353,  0.811985505, -0.874463407,  1.000000000, -0.104272659,  0.297793832, -0.514032745,  0.800698231, -0.830102616,  0.950602614 ],
                #        [  0.883403568, -0.090433543,  0.000000000,  0.000000000,  0.436823522, -0.104272659,  1.000000000, -0.111883376,  0.000000000,  0.000000000,  0.494752953, -0.134191009 ],
                #        [ -0.090341177,  0.808300854,  0.000000000,  0.000000000, -0.137898963,  0.297793832, -0.111883376,  1.000000000,  0.000000000,  0.000000000, -0.170921923,  0.374807565 ],
                #        [  0.000000000,  0.000000000,  0.938782519, -0.122445304,  0.622128000, -0.514032745,  0.000000000,  0.000000000,  1.000000000, -0.123454584,  0.672735926, -0.556618676 ],
                #        [  0.000000000,  0.000000000, -0.120298908,  0.986409445, -0.622176239,  0.800698231,  0.000000000,  0.000000000, -0.123454584,  1.000000000, -0.616497607,  0.798523473 ],
                #        [  0.436308995, -0.138612127,  0.633382320, -0.608419498,  0.940276558, -0.830102616,  0.494752953, -0.170921923,  0.672735926, -0.616497607,  1.000000000, -0.878334170 ],
                #        [ -0.115934567,  0.303210400, -0.525375965,  0.787887823, -0.841479510,  0.950602614, -0.134191009,  0.374807565, -0.556618676,  0.798523473, -0.878334170,  1.000000000 ], ],
                #    ],
                'multivar_BdMistagCalib_p0p1': [
                    [   'Bd_Mistag0CalibB_p0', 'Bd_Mistag0CalibB_p1',
                        'Bd_Mistag2CalibB_p0', 'Bd_Mistag2CalibB_p1',
                        'Bd_Mistag0CalibBbar_p0', 'Bd_Mistag0CalibBbar_p1',
                        'Bd_Mistag2CalibBbar_p0', 'Bd_Mistag2CalibBbar_p1', ],
                    [   0.004389, 0.039917, 0.005959, 0.038725,
                        0.004395, 0.040072, 0.006030, 0.039962, ],
                    [   [  1.000000000, -0.111790756,  0.495659195, -0.121263673,  0.883403568, -0.090341177,  0.436308995, -0.115934567 ],
                        [ -0.111790756,  1.000000000, -0.170723691,  0.368653977, -0.090433543,  0.808300854, -0.138612127,  0.303210400 ],
                        [  0.495659195, -0.170723691,  1.000000000, -0.874463407,  0.436823522, -0.137898963,  0.940276558, -0.841479510 ],
                        [ -0.121263673,  0.368653977, -0.874463407,  1.000000000, -0.104272659,  0.297793832, -0.830102616,  0.950602614 ],
                        [  0.883403568, -0.090433543,  0.436823522, -0.104272659,  1.000000000, -0.111883376,  0.494752953, -0.134191009 ],
                        [ -0.090341177,  0.808300854, -0.137898963,  0.297793832, -0.111883376,  1.000000000, -0.170921923,  0.374807565 ],
                        [  0.436308995, -0.138612127,  0.940276558, -0.830102616,  0.494752953, -0.170921923,  1.000000000, -0.878334170 ],
                        [ -0.115934567,  0.303210400, -0.841479510,  0.950602614, -0.134191009,  0.374807565, -0.878334170,  1.000000000 ], ],
                    ],
                'multivar_Bs2DsKTagEffAsyms': [
                        [   'Bs2DsK_TagEff0', 'Bs2DsK_TagEff1', 'Bs2DsK_TagEff2',
                            'Bs2DsK_AsymTagEff0', 'Bs2DsK_AsymTagEff1', 'Bs2DsK_AsymTagEff2' ],
                        [   0.001952, 0.002330, 0.001843, 0.001628, 0.001029, 0.001629 ],
                        [   [   1.0000000000000000e+00,  -9.6310597862753633e-01,   2.4948159233783404e-01,   1.0144953478135443e-02,   7.0203224420703663e-03,   1.0233976427853671e-02 ],
                            [  -9.6310597862753633e-01,   1.0000000000000000e+00,   2.0335415458912924e-02,  -8.0556554583657968e-03,  -5.7778847902391142e-03,  -8.1729979402554217e-03 ],
                            [   2.4948159233783404e-01,   2.0335415458912924e-02,   1.0000000000000000e+00,   8.9803482925014111e-03,   5.0106145332872738e-03,   8.8849526862593686e-03 ],
                            [   1.0144953478135443e-02,  -8.0556554583657968e-03,   8.9803482925014111e-03,   1.0000000000000000e+00,  -9.9965299841531974e-01,   9.9878828433569355e-01 ],
                            [   7.0203224420703663e-03,  -5.7778847902391142e-03,   5.0106145332872738e-03,  -9.9965299841531974e-01,   1.0000000000000000e+00,  -9.9759036187377381e-01 ],
                            [   1.0233976427853671e-02,  -8.1729979402554217e-03,   8.8849526862593686e-03,   9.9878828433569355e-01,  -9.9759036187377381e-01,   1.0000000000000000e+00 ], ],
                    ],
                #'multivar_Bs2DsPiTagEffAsyms': [
                #        [   'Bs2DsPi_TagEff0', 'Bs2DsPi_TagEff1', 'Bs2DsPi_TagEff2',
                #            'Bs2DsPi_AsymTagEff0', 'Bs2DsPi_AsymTagEff1', 'Bs2DsPi_AsymTagEff2' ],
                #        [   0.001952, 0.002330, 0.001843, 0.001628, 0.001029, 0.001629 ],
                #        [   [   1.0000000000000000e+00,  -9.6310597862753633e-01,   2.4948159233783404e-01,   1.0144953478135443e-02,   7.0203224420703663e-03,   1.0233976427853671e-02 ],
                #            [  -9.6310597862753633e-01,   1.0000000000000000e+00,   2.0335415458912924e-02,  -8.0556554583657968e-03,  -5.7778847902391142e-03,  -8.1729979402554217e-03 ],
                #            [   2.4948159233783404e-01,   2.0335415458912924e-02,   1.0000000000000000e+00,   8.9803482925014111e-03,   5.0106145332872738e-03,   8.8849526862593686e-03 ],
                #            [   1.0144953478135443e-02,  -8.0556554583657968e-03,   8.9803482925014111e-03,   1.0000000000000000e+00,  -9.9965299841531974e-01,   9.9878828433569355e-01 ],
                #            [   7.0203224420703663e-03,  -5.7778847902391142e-03,   5.0106145332872738e-03,  -9.9965299841531974e-01,   1.0000000000000000e+00,  -9.9759036187377381e-01 ],
                #            [   1.0233976427853671e-02,  -8.1729979402554217e-03,   8.8849526862593686e-03,   9.9878828433569355e-01,  -9.9759036187377381e-01,   1.0000000000000000e+00 ], ],
                #    ],
                },
        'Asymmetries': {
                'Prod': {
		    'Bs': -0.014,
		    'Bd': 0.011,
		    'Lb': 0.03,
		    'CombBkg': -0.01,
		    },
		'Det': {
		        'Bs2DsK':	0.01,
			'Bd2DPi':	0.005,
			'Bd2DsPi':	0.01,
			'Bs2DsPi':	0.005,
			'Lb2LcPi':	0.005,
			'CombBkg':	0.01,
			'Bs2DsstPi':	0.005,
		    },
                'TagEff': {
                        'Bs2DsK':   [ -0.002756, 0.001837, -0.002315 ],
                        'Bs2DsPi':  [ -0.002756, 0.001837, -0.002315 ],
                    },
                'TagEff_t': {}, 'TagEff_f': {},
                },
        'DecayTimeResolutionModel':	'GaussianWithPEDTE',
        'DecayTimeResolutionScaleFactor': 1.37,
        'DecayTimeErrorTemplates': {
                'Bs2DsK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsK',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bs2DsPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bs2DsstPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsstPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Lb2LcPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Lb2LcPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bd2DPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bd2DPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'CombBkg': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_CombBkg',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                },
        'KFactorTemplates': {
                'Bs2DsK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsPi_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bs2DsK_both',
                    'VarName': 'kfactorVar', },
                'Bs2DsstPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsPi_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bs2DsstPi_both',
                    'VarName': 'kfactorVar', },
                'Lb2LcPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsPi_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Lb2LcPi_both',
                    'VarName': 'kfactorVar', },
                'Bd2DPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsPi_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bd2DPi_both',
                    'VarName': 'kfactorVar', },
                },
        'AcceptanceFunction': 'Spline',
        'constParams': [
            'Gammas', 'deltaGammas',
            'Gammad', 'deltaGammad', 'deltaMd',
            'mistag', 'timeerr_bias', 'timeerr_scalefactor',
            '.+_Mistag[0-9]+Calib(B|Bbar)_p[0-9]+',
            'Bs2DsKst_TagEff[0-9]', 'Bs2DsKst_delta', 'Bs2DsKst_lambda', 'Bs2DsKst_phi_w',
	    '.+Asym.+',
            ],
}