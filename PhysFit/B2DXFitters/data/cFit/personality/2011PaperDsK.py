# personality for 2011 Paper - mode DsK
{
        'Modes': [
            'Bs2DsK',
            'Bs2DsKst',
            'Bs2DsPi', 'Bs2DsstPi', 'Bs2DsRho',
            'Bd2DK', 'Bd2DPi', 'Bd2DsK',
            'Lb2LcK', 'Lb2LcPi', 'Lb2Dsp', 'Lb2Dsstp',
            'CombBkg'
            ],
        'SampleCategories': [
            'nonres', 'phipi', 'kstk', 'kpipi', 'pipipi'
            ],
        'DeltaMs':                      17.768, # in ps^{-1}
        'GammaLb':			0.700, # in ps^{-1}
        'GammaCombBkg':			0.971, # in ps^{-1}
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
        'CombineModesForEffCPObs': [ ],
        'NEvents':			[ 3474. ],
        'MassTemplateFile':             os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/WS_Mass_DsK_5M_BDTGA.root',
        'MassTemplateWorkspace':	'FitMeToolWS',
        'MassInterpolation':		False,
        'NTaggers':                     3,
        'TagEff':                    {
            'Bs2DsK': [ 0.3870 * (1. - 0.4772), 0.4772 * (1. - 0.3870), 0.3870 * 0.4772 ],
            'Lb': [ 0.3870, 0.4772 ],
            'Bd': [ 0.3870, 0.4772 ],
            },
        'MistagTemplates': {
            'Bs2DsK': [
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
                'Bs2DsK': [
                    [ [ 0., 1., 0. ] ],
                    [ [ 0., 1., 0. ] ],
                    [ [ 0., 1., 0. ] ],
                    ],
                'Bd': [
                    [ [ 0., 1., 0. ] ],
                    [ [ 0.5, 0., 0. ] ],
                    [ [ 0., 1., 0. ] ],
                    ],
                },
        'Constraints': {
                'Bd2DPi_lambda': 0.3 * 0.0187,
                'Bd2DPi_avgSSbar': [ '0.5*(@0+@1)', ['Bd2DPi_S', 'Bd2DPi_Sbar'], +0.046, 0.023 ],
                'Bd2DPi_difSSbar': [ '0.5*(@0-@1)', ['Bd2DPi_S', 'Bd2DPi_Sbar'], -0.022, 0.021 ],
		'Bd_AsymProd': 0.01,
		'Bs_AsymProd': 0.01,
		'Lb_AsymProd': 0.03,
		'Bd2DK_AsymDet':	0.01,
		'Bd2DPi_AsymDet':	0.01,
		'Bd2DsK_AsymDet':	0.01,
		'Bs2DsPi_AsymDet':	0.01,
		'Lb2LcK_AsymDet':	0.03,
		'Lb2LcPi_AsymDet':	0.03,
		'CombBkg_AsymDet':	0.01,
		'Lb2Dsp_AsymDet':	0.03,
		'Lb2Dsstp_AsymDet':	0.03,
		'Bs2DsstPi_AsymDet':	0.01,
		'Bs2DsRho_AsymDet':	0.01,
                },
        'Asymmetries': {
                'Prod': {
		    'Bs': -0.014,
		    'Bd': 0.011,
		    'Lb': 0.03,
		    },
		'Det': {
		        'Bs2DsK':	0.01,
			'Bd2DK':	0.01,
			'Bd2DPi':	0.005,
			'Bd2DsK':	0.01,
			'Bs2DsPi':	0.005,
			'Lb2LcK':	0.01,
			'Lb2LcPi':	0.005,
			'CombBkg':	0.01,
			'Lb2Dsp':	0.02,
			'Lb2Dsstp':	0.02,
			'Bs2DsstPi':	0.005,
			'Bs2DsRho':	0.005,
		    },
		'TagEff': {}, 'TagEff_t': {}, 'TagEff_f': {},
                },
        'DecayTimeResolutionModel':	'GaussianWithPEDTE',
        'DecayTimeResolutionScaleFactor': 1.37,
        'DecayTimeErrorTemplates': {
                'Bs2DsK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsK',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bs2DsPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bs2DsRho': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsRho',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bs2DsstPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsstPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Lb2Dsp': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Lb2Dsp',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Lb2Dsstp': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Lb2Dsstp',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Lb2LcK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Lb2LcK',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Lb2LcPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Lb2LcPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bd2DK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bd2DK',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bd2DPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bd2DPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'CombBkg': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsK.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_CombBkg',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                },
        'KFactorTemplates': {
                'Bs2DsPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bs2DsPi_both',
                    'VarName': 'kfactorVar', },
                'Bs2DsstPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bs2DsstPi_both',
                    'VarName': 'kfactorVar', },
                'Bs2DsRho': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bs2DsRho_both',
                    'VarName': 'kfactorVar', },
                'Lb2LcK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Lb2LcK_both',
                    'VarName': 'kfactorVar', },
                'Lb2LcPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Lb2LcPi_both',
                    'VarName': 'kfactorVar', },
                'Lb2Dsp': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Lb2Dsp_both',
                    'VarName': 'kfactorVar', },
                'Lb2Dsstp': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Lb2Dsstp_both',
                    'VarName': 'kfactorVar', },
                'Bd2DK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bd2DK_both',
                    'VarName': 'kfactorVar', },
                'Bd2DPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5320_5420.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'kFactor_Bd2DPi_both',
                    'VarName': 'kfactorVar', },
                },
        'AcceptanceFunction': 'Spline',
        'constParams': [
            'Gammas', 'deltaGammas', 'deltaMs',
            'Gammad', 'deltaGammad', 'deltaMd',
            'mistag', 'timeerr_bias', 'timeerr_scalefactor',
            '.+_Mistag[0-9]+Calib(B|Bbar)_p[0-9]+',
            'Bs2DsKst_TagEff[0-9]', 'Bs2DsKst_delta', 'Bs2DsKst_lambda', 'Bs2DsKst_phi_w',
	    '.+Asym.+',
            ],
}