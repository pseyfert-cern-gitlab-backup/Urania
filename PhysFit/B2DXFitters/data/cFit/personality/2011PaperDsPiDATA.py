# personality for 2011 Paper - mode DsPi
{
        'IsToy':                False,
        'DataFileName':         os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/WS_Mass_DsPi_5M_BDTGA.root',
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
        'GammaLb':			0.700, # in ps^{-1}
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
        'MassTemplateFile':             os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/WS_Mass_DsPi_5M_BDTGA.root',
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
                'Bs2DsPi_Mistag0CalibB_p0': 0.0014,
                'Bs2DsPi_Mistag0CalibB_p1': 0.0173,
                'Bs2DsPi_Mistag1CalibB_p0': 0.0086,
                'Bs2DsPi_Mistag1CalibB_p1': 0.1110,
                'Bs2DsPi_Mistag2CalibB_p0': 0.0026,
                'Bs2DsPi_Mistag2CalibB_p1': 0.0285,
                'Bd_Mistag0CalibB_p0': 0.0014,
                'Bd_Mistag0CalibB_p1': 0.0173,
                'Bd_Mistag2CalibB_p0': 0.0026,
                'Bd_Mistag2CalibB_p1': 0.0285,
                },
        'Asymmetries': {
                'Prod': {}, 'Det': { }, 'TagEff': {}, 'TagEff_t': {}, 'TagEff_f': {},
                },
        'DecayTimeResolutionModel':	'GaussianWithPEDTE',
        'DecayTimeResolutionScaleFactor': 1.37,
        'DecayTimeErrorTemplates': {
                'Bs2DsK': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsK',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bs2DsPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bs2DsstPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bs2DsstPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Lb2LcPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Lb2LcPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'Bd2DPi': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_Bd2DPi',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                'CombBkg': {
                    'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_Data_Terr_BsDsPi.root',
                    'Workspace': 'workspace',
                    'TemplateName': 'TimeErrorPdf_CombBkg',
                    'VarName': 'lab0_LifetimeFit_ctauErr', },
                },
        #'KFactorTemplates': {
        #        'Bs2DsPi': {
        #            'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5300_5800.root',
        #            'Workspace': 'workspace',
        #            'TemplateName': 'kFactor_Bs2DsPi_both',
        #            'VarName': 'kfactorVar', },
        #        'Bs2DsstPi': {
        #            'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5300_5800.root',
        #            'Workspace': 'workspace',
        #            'TemplateName': 'kFactor_Bs2DsstPi_both',
        #            'VarName': 'kfactorVar', },
        #        'Bs2DsRho': {
        #            'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5300_5800.root',
        #            'Workspace': 'workspace',
        #            'TemplateName': 'kFactor_Bs2DsRho_both',
        #            'VarName': 'kfactorVar', },
        #        'Lb2LcK': {
        #            'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5300_5800.root',
        #            'Workspace': 'workspace',
        #            'TemplateName': 'kFactor_Lb2LcK_both',
        #            'VarName': 'kfactorVar', },
        #        'Lb2Dsp': {
        #            'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5300_5800.root',
        #            'Workspace': 'workspace',
        #            'TemplateName': 'kFactor_Lb2Dsp_both',
        #            'VarName': 'kfactorVar', },
        #        'Lb2Dsstp': {
        #            'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5300_5800.root',
        #            'Workspace': 'workspace',
        #            'TemplateName': 'kFactor_Lb2Dsstp_both',
        #            'VarName': 'kfactorVar', },
        #        'Bd2DK': {
        #            'File': os.environ['B2DXFITTERSROOT']+'/data/workspace/MDFitter/template_MC_KFactor_BsDsK_5300_5800.root',
        #            'Workspace': 'workspace',
        #            'TemplateName': 'kFactor_Bd2DK_both',
        #            'VarName': 'kfactorVar', },
        #        },
        'AcceptanceFunction': 'Spline',
        'constParams': [
            'Gammas', 'deltaGammas',
            'Gammad', 'deltaGammad', 'deltaMd',
            'mistag', 'timeerr_bias', 'timeerr_scalefactor',
            '.+_Mistag[0-9]+Calib(B|Bbar)_p[0-9]+',
            'Bs2DsKst_TagEff[0-9]', 'Bs2DsKst_delta', 'Bs2DsKst_lambda', 'Bs2DsKst_phi_w',
            ],
}
