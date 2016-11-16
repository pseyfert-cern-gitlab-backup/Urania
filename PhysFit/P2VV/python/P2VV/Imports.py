###########################################################################################################################################
## P2VVImports                                                                                                                           ##
##                                                                                                                                       ##
## authors':                                                                                                                             ##
##   JvL, Jeroen van Leerdam, Nikhef, j.van.leerdam@nikhef.nl                                                                            ##
##                                                                                                                                       ##
###########################################################################################################################################


# parameter names dictionary:  'P2VV internal name' : ( 'text name', 'LaTeX name' )
parNames = {  'phiCP'                     : ( 'phi_s',                       '$\\phi_\\text{s}$'                          )
            , '__phiCP__'                 : ( 'phi_s (b)',                   '$\\phi_\\text{s}$ (b)'                      )
            , 'phiCPAv'                   : ( 'phi_s^av',                    '$\\phi_\\text{s}^\\text{av}$'               )
            , '__phiCPAv__'               : ( 'phi_s^av (b)',                '$\\phi_\\text{s}^\\text{av}$ (b)'           )
            , 'phiCP_A0'                  : ( 'phi_s^0',                     '$\\phi_\\text{s}^0$'                        )
            , '__phiCP_A0__'              : ( 'phi_s^0 (b)',                 '$\\phi_\\text{s}^0$ (b)'                    )
            , 'phiCP_Apar'                : ( 'phi_s^para',                  '$\\phi_\\text{s}^\\parallel$'               )
            , '__phiCP_Apar__'            : ( 'phi_s^para (b)',              '$\\phi_\\text{s}^\\parallel$ (b)'           )
            , 'phiCP_Aperp'               : ( 'phi_s^perp',                  '$\\phi_\\text{s}^\\perp$'                   )
            , '__phiCP_Aperp__'           : ( 'phi_s^perp (b)',              '$\\phi_\\text{s}^\\perp$ (b)'               )
            , 'phiCP_AS'                  : ( 'phi_s^S',                     '$\\phi_\\text{s}^\\text{S}$'                )
            , '__phiCP_AS__'              : ( 'phi_s^S (b)',                 '$\\phi_\\text{s}^\\text{S}$ (b)'            )
            , 'phiCP_m'                   : ( 'phi_s^0',                     '$\\phi_\\text{s}^0$'                        )
            , '__phiCP_m__'               : ( 'phi_s^0 (b)',                 '$\\phi_\\text{s}^0$ (b)'                    )
            , 'phiCPRel_Apar'             : ( 'Delta phi_s^para',            '$\\Delta \\phi_\\text{s}^\\parallel$'       )
            , '__phiCPRel_Apar__'         : ( 'Delta phi_s^para (b)',        '$\\Delta \\phi_\\text{s}^\\parallel$ (b)'   )
            , 'phiCPRel_Aperp'            : ( 'Delta phi_s^perp',            '$\\Delta \\phi_\\text{s}^\\perp$'           )
            , '__phiCPRel_Aperp__'        : ( 'Delta phi_s^perp (b)',        '$\\Delta \\phi_\\text{s}^\\perp$ (b)'       )
            , 'phiCPRel_AperpApar'        : ( 'Delta phi_s^perp\'',          '$\\Delta \\phi_\\text{s}^\\perp\'$'         )
            , '__phiCPRel_AperpApar__'    : ( 'Delta phi_s^perp\' (b)',      '$\\Delta \\phi_\\text{s}^\\perp\'$ (b)'     )
            , 'phiCPRel_AS'               : ( 'Delta phi_s^S',               '$\\Delta \\phi_\\text{s}^\\text{S}$'        )
            , '__phiCPRel_AS__'           : ( 'Delta phi_s^S (b)',           '$\\Delta \\phi_\\text{s}^\\text{S}$ (b)'    )
            , 'lambdaCP'                  : ( '|lambda_s|',                  '$|\\lambda_\\text{s}|$'                     )
            , '__lambdaCP__'              : ( '|lambda_s| (b)',              '$|\\lambda_\\text{s}|$ (b)'                 )
            , 'rhoCP_A0'                  : ( '|lambda_s^0|',                '$|\\lambda_\\text{s}^0|$'                   )
            , 'rhoCP_Apar'                : ( '|lambda_s^para|',             '$|\\lambda_\\text{s}^\\parallel|$'          )
            , 'rhoCP_Aperp'               : ( '|lambda_s^perp|',             '$|\\lambda_\\text{s}^\\perp|$'              )
            , 'rhoCP_AS'                  : ( '|lambda_s^S|',                '$|\\lambda_\\text{s}^\\text{S}|$'           )
            , 'lambdaCP_A0'               : ( '|lambda_s^0|',                '$|\\lambda_\\text{s}^0|$'                   )
            , 'lambdaCP_Apar'             : ( '|lambda_s^para|',             '$|\\lambda_\\text{s}^\\parallel|$'          )
            , 'lambdaCP_Aperp'            : ( '|lambda_s^perp|',             '$|\\lambda_\\text{s}^\\perp|$'              )
            , 'lambdaCP_AS'               : ( '|lambda_s^S|',                '$|\\lambda_\\text{s}^\\text{S}|$'           )
            , 'CCP'                       : ( 'C_s',                         '$C_\\text{s}$'                              )
            , 'CCPAv'                     : ( 'C_s^av',                      '$C_\\text{s}^\\text{av}$'                   )
            , 'CCPAv_AS'                  : ( 'C_s^avS',                     '$C_\\text{s}^\\text{avS}$'                  )
            , 'CCPRel_Apar'               : ( 'Delta C_s^para',              '$\\Delta C_\\text{s}^\\parallel$'           )
            , 'CCPRel_Aperp'              : ( 'Delta C_s^perp',              '$\\Delta C_\\text{s}^\\perp$'               )
            , 'Gamma'                     : ( 'Gamma_s',                     '$\\Gamma_\\text{s}$'                        )
            , 'Gamma_p2011'               : ( 'Gamma_s - beta_2011',         '$\\Gamma_\\text{s} - \\beta_\\{2011}$'      )
            , 'Gamma_p2012'               : ( 'Gamma_s - beta_2012',         '$\\Gamma_\\text{s} - \\beta_\\{2012}$'      )
            , 'dGamma'                    : ( 'Delta Gamma_s',               '$\\Delta\\Gamma_\\text{s}$'                 )
            , '__dGamma__'                : ( 'Delta Gamma_s (b)',           '$\\Delta\\Gamma_\\text{s}$ (b)'             )
            , 'dM'                        : ( 'Delta m_s',                   '$\\Delta m_\\text{s}$'                      )
            , 'A0Mag2'                    : ( '|A_0|^2',                     '$|A_0|^2$'                                  )
            , 'AperpMag2'                 : ( '|A_perp|^2',                  '$|A_\\perp|^2$'                             )
            , 'avA02'                     : ( 'A^av_0^2',                    '${A^\\text{av}_0}^2$'                       )
            , 'avAperp2'                  : ( 'A^av_perp^2',                 '${A^\\text{av}_\\perp}^2$'                  )
            , 'delA02'                    : ( 'Delta A_0^2',                 '$\\Delta A_0^2$'                            )
            , 'delApar2'                  : ( 'Delta A_para^2',              '$\\Delta A_\\parallel^2$'                   )
            , 'delAperp2'                 : ( 'Delta A_perp^2',              '$\\Delta A_\\perp^2$'                       )
            , 'f_S'                       : ( 'F_S',                         '$F_\\text{S}$'                              )
            , 'f_S_bin0'                  : ( 'F_S_0',                       '${F_\\text{S}}_0$'                          )
            , 'f_S_bin1'                  : ( 'F_S_1',                       '${F_\\text{S}}_1$'                          )
            , 'f_S_bin2'                  : ( 'F_S_2',                       '${F_\\text{S}}_2$'                          )
            , 'f_S_bin3'                  : ( 'F_S_3',                       '${F_\\text{S}}_3$'                          )
            , 'f_S_bin4'                  : ( 'F_S_4',                       '${F_\\text{S}}_4$'                          )
            , 'f_S_bin5'                  : ( 'F_S_5',                       '${F_\\text{S}}_5$'                          )
            , 'avf_S'                     : ( 'F_S^av',                      '$F_\\text{S}$'                              )
            , 'avf_S_bin0'                : ( 'F_S^av_0',                    '${F_\\text{S}}_0$'                          )
            , 'avf_S_bin1'                : ( 'F_S^av_1',                    '${F_\\text{S}}_1$'                          )
            , 'avf_S_bin2'                : ( 'F_S^av_2',                    '${F_\\text{S}}_2$'                          )
            , 'avf_S_bin3'                : ( 'F_S^av_3',                    '${F_\\text{S}}_3$'                          )
            , 'avf_S_bin4'                : ( 'F_S^av_4',                    '${F_\\text{S}}_4$'                          )
            , 'avf_S_bin5'                : ( 'F_S^av_5',                    '${F_\\text{S}}_5$'                          )
            , 'AparPhase'                 : ( 'delta_para - delta_0',        '$\\delta_\\parallel-\\delta_0$'             )
            , 'AperpPhase'                : ( 'delta_perp - delta_0',        '$\\delta_\\perp-\\delta_0$'                 )
            , 'ASOddPhase'                : ( 'delta_S - delta_perp',        '$\\delta_\\text{S}-\\delta_\\perp$'         )
            , 'ASOddPhase_bin0'           : ( 'delta_S_0 - delta_perp',      '${\\delta_\\text{S}}_0-\\delta_\\perp$'     )
            , 'ASOddPhase_bin1'           : ( 'delta_S_1 - delta_perp',      '${\\delta_\\text{S}}_1-\\delta_\\perp$'     )
            , 'ASOddPhase_bin2'           : ( 'delta_S_2 - delta_perp',      '${\\delta_\\text{S}}_2-\\delta_\\perp$'     )
            , 'ASOddPhase_bin3'           : ( 'delta_S_3 - delta_perp',      '${\\delta_\\text{S}}_3-\\delta_\\perp$'     )
            , 'ASOddPhase_bin4'           : ( 'delta_S_4 - delta_perp',      '${\\delta_\\text{S}}_4-\\delta_\\perp$'     )
            , 'ASOddPhase_bin5'           : ( 'delta_S_5 - delta_perp',      '${\\delta_\\text{S}}_5-\\delta_\\perp$'     )
            , 'ASPhase_bin1'              : ( 'delta_S_1',                   '${\\delta_\\text{S}}_1$'                    )
            , 'ASPhase_bin2'              : ( 'delta_S_2',                   '${\\delta_\\text{S}}_2$'                    )
            , 'ASPhase_bin3'              : ( 'delta_S_3',                   '${\\delta_\\text{S}}_3$'                    )
            , 'ASPhase_bin4'              : ( 'delta_S_4',                   '${\\delta_\\text{S}}_4$'                    )
            , 'ACP0'                      : ( 'Acp_0',                       '$A_0^{CP}$'                                )
            , 'ACPpar'                    : ( 'Acp_||',                      '$A_{\\parallel}^{CP}$'                     )
            , 'ACPperp'                   : ( 'Acp_perp',                    '$A_{\\perp}^{CP}$'                         )
            , 'ACPS'                      : ( 'Acp_S',                       '$A_S^{CP}$'                                )
            , '__ACP0__'                  : ( 'Acp_0 (b)',                   '$A_0^{CP}$ (b)'                            )
            , '__ACPpar__'                : ( 'Acp_|| (b)',                  '$A_{\\parallel}^{CP}$ (b)'                 )
            , '__ACPperp__'               : ( 'Acp_perp (b)',                '$A_{\\perp}^{CP}$ (b)'                     )
            , '__ACPS__'                  : ( 'Acp_S (b)',                   '$A_S^{CP}$ (b)'                            )    
            , 'timeResSigmaSF'            : ( 'S_sigma_t',                   '$S_{\\sigma_{t}}$'                          )
            , 'betaTimeEff'               : ( 'beta',                        '$\\beta$'                                   )
            , 'betaTimeEff_p2011'         : ( 'beta_2011',                   '$\\beta_{2011}$'                            )
            , 'betaTimeEff_p2012'         : ( 'beta_2012',                   '$\\beta_{2012}$'                            )
            , 'wTagP0OS'                  : ( 'p_0 OS',                      '$p_0$ OS'                                   )
            , 'wTagP1OS'                  : ( 'p_1 OS',                      '$p_1$ OS'                                   )
            , 'wTagDelP0OS'               : ( 'Delta p_0 OS',                '$\\Delta p_0$ OS'                           )
            , 'wTagDelP1OS'               : ( 'Delta p_1 OS',                '$\\Delta p_1$ OS'                           )
            , 'wTagP0SS'                  : ( 'p_0 SS',                      '$p_0$ SS'                                   )
            , 'wTagP1SS'                  : ( 'p_1 SS',                      '$p_1$ SS'                                   )
            , 'wTagDelP0SS'               : ( 'Delta p_0 SS',                '$\\Delta p_0$ SS'                           )
            , 'wTagDelP1SS'               : ( 'Delta p_1 SS',                '$\\Delta p_1$ SS'                           )
            , 'N_sigMass'                 : ( 'N_sig',                       '$N_\\text{sig}$'                            )
            , 'N_sigMass_bin0'            : ( 'N_sig_0',                     '${N_\\text{sig}}_0$'                        )
            , 'N_sigMass_bin1'            : ( 'N_sig_1',                     '${N_\\text{sig}}_1$'                        )
            , 'N_sigMass_bin2'            : ( 'N_sig_2',                     '${N_\\text{sig}}_2$'                        )
            , 'N_sigMass_bin3'            : ( 'N_sig_3',                     '${N_\\text{sig}}_3$'                        )
            , 'N_sigMass_bin4'            : ( 'N_sig_4',                     '${N_\\text{sig}}_4$'                        )
            , 'N_sigMass_bin5'            : ( 'N_sig_5',                     '${N_\\text{sig}}_5$'                        )
            , 'N_sigMass_{notExclB;bin0}' : ( 'N_sig_U0',                    '${N_\\text{sig}}_{U0}$'                     )
            , 'N_sigMass_{notExclB;bin1}' : ( 'N_sig_U1',                    '${N_\\text{sig}}_{U1}$'                     )
            , 'N_sigMass_{notExclB;bin2}' : ( 'N_sig_U2',                    '${N_\\text{sig}}_{U2}$'                     )
            , 'N_sigMass_{notExclB;bin3}' : ( 'N_sig_U3',                    '${N_\\text{sig}}_{U3}$'                     )
            , 'N_sigMass_{notExclB;bin4}' : ( 'N_sig_U4',                    '${N_\\text{sig}}_{U4}$'                     )
            , 'N_sigMass_{notExclB;bin5}' : ( 'N_sig_U5',                    '${N_\\text{sig}}_{U5}$'                     )
            , 'N_sigMass_{exclB;bin0}'    : ( 'N_sig_B0',                    '${N_\\text{sig}}_{B0}$'                     )
            , 'N_sigMass_{exclB;bin1}'    : ( 'N_sig_B1',                    '${N_\\text{sig}}_{B1}$'                     )
            , 'N_sigMass_{exclB;bin2}'    : ( 'N_sig_B2',                    '${N_\\text{sig}}_{B2}$'                     )
            , 'N_sigMass_{exclB;bin3}'    : ( 'N_sig_B3',                    '${N_\\text{sig}}_{B3}$'                     )
            , 'N_sigMass_{exclB;bin4}'    : ( 'N_sig_B4',                    '${N_\\text{sig}}_{B4}$'                     )
            , 'N_sigMass_{exclB;bin5}'    : ( 'N_sig_B5',                    '${N_\\text{sig}}_{B5}$'                     )
            , 'N_bkgMass'                 : ( 'N_bkg',                       '$N_\\text{bkg}$'                            )
            , 'N_bkgMass_bin0'            : ( 'N_bkg_0',                     '${N_\\text{bkg}}_0$'                        )
            , 'N_bkgMass_bin1'            : ( 'N_bkg_1',                     '${N_\\text{bkg}}_1$'                        )
            , 'N_bkgMass_bin2'            : ( 'N_bkg_2',                     '${N_\\text{bkg}}_2$'                        )
            , 'N_bkgMass_bin3'            : ( 'N_bkg_3',                     '${N_\\text{bkg}}_3$'                        )
            , 'N_bkgMass_bin4'            : ( 'N_bkg_4',                     '${N_\\text{bkg}}_4$'                        )
            , 'N_bkgMass_bin5'            : ( 'N_bkg_5',                     '${N_\\text{bkg}}_5$'                        )
            , 'N_bkgMass_{notExclB;bin0}' : ( 'N_bkg_U0',                    '${N_\\text{bkg}}_{U0}$'                     )
            , 'N_bkgMass_{notExclB;bin1}' : ( 'N_bkg_U1',                    '${N_\\text{bkg}}_{U1}$'                     )
            , 'N_bkgMass_{notExclB;bin2}' : ( 'N_bkg_U2',                    '${N_\\text{bkg}}_{U2}$'                     )
            , 'N_bkgMass_{notExclB;bin3}' : ( 'N_bkg_U3',                    '${N_\\text{bkg}}_{U3}$'                     )
            , 'N_bkgMass_{notExclB;bin4}' : ( 'N_bkg_U4',                    '${N_\\text{bkg}}_{U4}$'                     )
            , 'N_bkgMass_{notExclB;bin5}' : ( 'N_bkg_U5',                    '${N_\\text{bkg}}_{U5}$'                     )
            , 'N_bkgMass_{exclB;bin0}'    : ( 'N_bkg_B0',                    '${N_\\text{bkg}}_{B0}$'                     )
            , 'N_bkgMass_{exclB;bin1}'    : ( 'N_bkg_B1',                    '${N_\\text{bkg}}_{B1}$'                     )
            , 'N_bkgMass_{exclB;bin2}'    : ( 'N_bkg_B2',                    '${N_\\text{bkg}}_{B2}$'                     )
            , 'N_bkgMass_{exclB;bin3}'    : ( 'N_bkg_B3',                    '${N_\\text{bkg}}_{B3}$'                     )
            , 'N_bkgMass_{exclB;bin4}'    : ( 'N_bkg_B4',                    '${N_\\text{bkg}}_{B4}$'                     )
            , 'N_bkgMass_{exclB;bin5}'    : ( 'N_bkg_B5',                    '${N_\\text{bkg}}_{B5}$'                     )
            , 'm_sig_frac'                : ( 'f_mass_1',                    '${f_1}_\\text{mass}$'                       )
            , 'm_sig_mean'                : ( 'mu_mass',                     '$\\mu_\\text{mass}$'                        )
            , 'm_sig_sigma_sf'            : ( 'sigma_mass 2:1 SF',           '$\\text{SF}_{2:1}\\ \\sigma_\\text{mass}$'  )
            , 'm_sig_sigma_1'             : ( 'sigma_mass_1',                '${\\sigma_1}_\\text{mass}$'                 )
            , 'm_sig_sigma_2'             : ( 'sigma_mass_2',                '${\\sigma_2}_\\text{mass}$'                 )
            , 'm_sig_widthPar0'           : ( 'width_par_mass_0',            '${\\text{width}_0}_\\text{mass}$'           )
            , 'm_sig_widthPar1'           : ( 'width_par_mass_1',            '${\\text{width}_1}_\\text{mass}$'           )
            , 'm_sig_widthPar2'           : ( 'width_par_mass_2',            '${\\text{width}_2}_\\text{mass}$'           )
            , 'm_bkg_exp'                 : ( 'alpha_mass',                  '$\\alpha_\\text{mass}$'                     )
            , 'm_bkg_exp_bin0'            : ( 'alpha_mass_0',                '${\\alpha_\\text{mass}}_0$'                 )
            , 'm_bkg_exp_bin1'            : ( 'alpha_mass_1',                '${\\alpha_\\text{mass}}_1$'                 )
            , 'm_bkg_exp_bin2'            : ( 'alpha_mass_2',                '${\\alpha_\\text{mass}}_2$'                 )
            , 'm_bkg_exp_bin3'            : ( 'alpha_mass_3',                '${\\alpha_\\text{mass}}_3$'                 )
            , 'm_bkg_exp_bin4'            : ( 'alpha_mass_4',                '${\\alpha_\\text{mass}}_4$'                 )
            , 'm_bkg_exp_bin5'            : ( 'alpha_mass_5',                '${\\alpha_\\text{mass}}_5$'                 )
            , 'm_bkg_arg'                 : ( 'alpha_mass',                  '$\\alpha_\\text{mass}$'                     )
            , 'm_bkg_arg_bin0'            : ( 'alpha_mass_0',                '${\\alpha_\\text{mass}}_0$'                 )
            , 'm_bkg_arg_bin1'            : ( 'alpha_mass_1',                '${\\alpha_\\text{mass}}_1$'                 )
            , 'm_bkg_arg_bin2'            : ( 'alpha_mass_2',                '${\\alpha_\\text{mass}}_2$'                 )
            , 'm_bkg_arg_bin3'            : ( 'alpha_mass_3',                '${\\alpha_\\text{mass}}_3$'                 )
            , 'm_bkg_arg_bin4'            : ( 'alpha_mass_4',                '${\\alpha_\\text{mass}}_4$'                 )
            , 'm_bkg_arg_bin5'            : ( 'alpha_mass_5',                '${\\alpha_\\text{mass}}_5$'                 )
            , 'CPTConstant'               : ( 'CPTConstant' ,                '$CPTConstant$'                              )
            , 'Re_Z'                      : ( 'Re_Z'        ,                '$Re(Z)$'                                    )
            , 'Im_Z'                      : ( 'Im_Z'        ,                '$Im(Z)$'                                    )
            , 'DaX'                       : ( 'DaX'         ,                '$\Delta\alpha_{X}$'                         )
            , 'DaY'                       : ( 'DaY'         ,                '$\Delta\alpha_{Y}$'                         )
            , 'Da0-0.38DaZ'               : ( 'Da0-0.38DaZ' ,                '$\Delta\alpha_{0}-0.38\Delta_{Z}$'          ) 
            , 'Yield_2011_bin1'         : ( 'Yield_2011_bin1',             '$y_{\\text{bin}1}^{2011}$'                    )
            , 'Yield_2011_bin2'         : ( 'Yield_2011_bin2',             '$y_{\\text{bin}2}^{2011}$'                    )
            , 'Yield_2011_bin3'         : ( 'Yield_2011_bin3',             '$y_{\\text{bin}3}^{2011}$'                    )
            , 'Yield_2011_bin4'         : ( 'Yield_2011_bin4',             '$y_{\\text{bin}4}^{2011}$'                    )
            , 'Yield_2012_bin1'         : ( 'Yield_2012_bin1',             '$y_{\\text{bin}1}^{2012}$'                    )
            , 'Yield_2012_bin2'         : ( 'Yield_2012_bin2',             '$y_{\\text{bin}2}^{2012}$'                    )
            , 'Yield_2012_bin3'         : ( 'Yield_2012_bin3',             '$y_{\\text{bin}3}^{2012}$'                    )
            , 'Yield_2012_bin4'         : ( 'Yield_2012_bin4',             '$y_{\\text{bin}4}^{2012}$'                    )
          }

# common parameter names dictionary:  'P2VV internal name' : 'common name'
commonParNames = {  'phiCP'                  : 'phis'
                  , '__phiCP__'              : 'phis'
                  , 'phiCPAv'                : 'avphis'
                  , '__phiCPAv__'            : 'avphis'
                  , 'phiCP_A0'               : 'phiszero'
                  , '__phiCP_A0__'           : 'phiszero'
                  , 'phiCP_Apar'             : 'phispara'
                  , '__phiCP_Apar__'         : 'phispara'
                  , 'phiCP_Aperp'            : 'phisperp'
                  , '__phiCP_Aperp__'        : 'phisperp'
                  , 'phiCP_AS'               : 'phisS'
                  , '__phiCP_AS__'           : 'phisS'
                  , 'phiCP_m'                : 'phiszero'
                  , '__phiCP_m__'            : 'phiszero'
                  , 'phiCPRel_Apar'          : 'delphispara'
                  , '__phiCPRel_Apar__'      : 'delphispara'
                  , 'phiCPRel_Aperp'         : 'delphisperp'
                  , '__phiCPRel_Aperp__'     : 'delphisperp'
                  , 'phiCPRel_AperpApar'     : 'delphisperpprime'
                  , '__phiCPRel_AperpApar__' : 'delphisperpprime'
                  , 'phiCPRel_AS'            : 'delphisS'
                  , '__phiCPRel_AS__'        : 'delphisS'
                  , 'lambdaCP'               : 'lambda'
                  , '__lambdaCP__'           : 'lambda'
                  , 'rhoCP_A0'               : 'lambdazero'
                  , 'rhoCP_Apar'             : 'lambdapara'
                  , 'rhoCP_Aperp'            : 'lambdaperp'
                  , 'rhoCP_AS'               : 'lambdaS'
                  , 'rhoCP_m'                : 'lambdazero'
                  , 'lambdaCP_A0'            : 'lambdazero'
                  , 'lambdaCP_Apar'          : 'lambdapara'
                  , 'lambdaCP_Aperp'         : 'lambdaperp'
                  , 'lambdaCP_AS'            : 'lambdaS'
                  , 'CCPAv'                  : 'avC'
                  , 'CCPAv_AS'               : 'avCS'
                  , 'CCPRel_Apar'            : 'delCpara'
                  , 'CCPRel_Aperp'           : 'delCperp'
                  , 'Gamma'                  : 'Gamma'
                  , 'Gamma_p2011'            : 'Gamma_2011'
                  , 'Gamma_p2012'            : 'Gamma_2012'
                  , 'dGamma'                 : 'DelGam'
                  , '__dGamma__'             : 'DelGam'
                  , 'dM'                     : 'Delm'
                  , 'A0Mag2'                 : 'AzeroSq'
                  , 'AperpMag2'              : 'AperpSq'
                  , 'avA02'                  : 'avAzeroSq'
                  , 'avAperp2'               : 'avAperpSq'
                  , 'f_S'                    : 'FS'
                  , 'f_S_bin0'               : 'FS1'
                  , 'f_S_bin1'               : 'FS2'
                  , 'f_S_bin2'               : 'FS3'
                  , 'f_S_bin3'               : 'FS4'
                  , 'f_S_bin4'               : 'FS5'
                  , 'f_S_bin5'               : 'FS6'
                  , 'avf_S'                  : 'avFS'
                  , 'avf_S_bin0'             : 'avFS1'
                  , 'avf_S_bin1'             : 'avFS2'
                  , 'avf_S_bin2'             : 'avFS3'
                  , 'avf_S_bin3'             : 'avFS4'
                  , 'avf_S_bin4'             : 'avFS5'
                  , 'avf_S_bin5'             : 'avFS6'
                  , 'AparPhase'              : 'delpara'
                  , 'AperpPhase'             : 'delperp'
                  , 'ASOddPhase'             : 'delS'
                  , 'ASOddPhase_bin0'        : 'delS1'
                  , 'ASOddPhase_bin1'        : 'delS2'
                  , 'ASOddPhase_bin2'        : 'delS3'
                  , 'ASOddPhase_bin3'        : 'delS4'
                  , 'ASOddPhase_bin4'        : 'delS5'
                  , 'ASOddPhase_bin5'        : 'delS6'
                  , 'betaTimeEff'            : 'beta'
                  , 'betaTimeEff_p2011'      : 'beta_2011'
                  , 'betaTimeEff_p2012'      : 'beta_2012'
                  , 'CPTConstant'            : 'CPtConstant'
                 }

# nominal values of physics parameters
parValues = {  'A0Mag2'            : ( +0.52368915  , 0.0034397573, -1 )
             , 'ASOddPhase_bin0'   : ( +0.84326935  , 0.19890552  , -1 )
             , 'ASOddPhase_bin1'   : ( +2.1473906   , 0.28117736  , -1 )
             , 'ASOddPhase_bin2'   : ( +0.48284398  , 0.22298742  , -1 )
             , 'ASOddPhase_bin3'   : ( -0.3643156   , 0.18215683  , -1 )
             , 'ASOddPhase_bin4'   : ( -0.59244037  , 0.15590409  , -1 )
             , 'ASOddPhase_bin5'   : ( -0.90820409  , 0.14032249  , -1 )
             , 'AparPhase'         : ( +3.256916    , 0.12404786  , -1 )
             , 'AperpMag2'         : ( +0.25119184  , 0.0049016867, -1 )
             , 'AperpPhase'        : ( +3.0987118   , 0.14395878  , -1 )
             , 'Gamma'             : ( +0.65915099  , 0.0031074257, -1 )
             , '__dGamma__'        : ( +0.088523588 , 0.0091361497, -1 )
             , 'dGamma'            : ( +0.078493173 , 0.0091561838, -1 )
             , '__phiCP__'         : ( +0.072963883 , 0.049715421 , -1 )
             , 'phiCP'             : ( -0.057116522 , 0.049720002 , -1 )
             , 'betaTimeEff_p2011' : ( -0.0086391488, 0.0020435249, -1 )
             , 'betaTimeEff_p2012' : ( -0.012668772 , 0.0017998729, -1 )
             , 'dM'                : ( +17.723073   , 0.056704079 , -1 )
             , 'f_S_bin0'          : ( +0.42625712  , 0.054009263 , -1 )
             , 'f_S_bin1'          : ( +0.058747712 , 0.017556732 , -1 )
             , 'f_S_bin2'          : ( +0.0095625685, 0.0065687377, -1 )
             , 'f_S_bin3'          : ( +0.0094058926, 0.0058412882, -1 )
             , 'f_S_bin4'          : ( +0.048150007 , 0.015470046 , -1 )
             , 'f_S_bin5'          : ( +0.19204043  , 0.025480091 , -1 )
             , 'lambdaCP'          : ( +0.96269671  , 0.018784368 , -1 )
             , 'wTagDelP0OS'       : ( +0.014023729 , 0.0011999079, -1 )
             , 'wTagDelP0SS'       : ( -0.015786075 , 0.0013998909, -1 )
             , 'wTagDelP1OS'       : ( +0.065743477 , 0.011999235 , -1 )
             , 'wTagDelP1SS'       : ( +0.0081990069, 0.021987952 , -1 )
             , 'wTagP0OS'          : ( +0.38152954  , 0.0042498074, -1 )
             , 'wTagP0SS'          : ( +0.44585583  , 0.0046407908, -1 )
             , 'wTagP1OS'          : ( +1.0118529   , 0.034418609 , -1 )
             , 'wTagP1SS'          : ( +0.95813578  , 0.082657183 , -1 )
            }

#nominal values of physics parameters for CPT violation, with Im(z)=0
#some tagging parms set to be constant; the CP model used is lamb_phi
parValues_PhenoImZ0 =    {  'A0Mag2'           : ( +0.523737    , 0.0034396 , -1 )
                         , 'ASOddPhase_bin0'   : ( +0.84726     , 0.199931  , -1 )
                         , 'ASOddPhase_bin1'   : ( +2.15499     , 0.275743  , -1 )
                         , 'ASOddPhase_bin2'   : ( +0.482642    , 0.223274  , -1 )
                         , 'ASOddPhase_bin3'   : ( -0.365286    , 0.182299  , -1 )
                         , 'ASOddPhase_bin4'   : ( -0.590716    , 0.154749  , -1 )
                         , 'ASOddPhase_bin5'   : ( -0.906429    , 0.139977  , -1 )
                         , 'AparPhase'         : ( +3.25717     , 0.123253  , -1 )
                         , 'AperpMag2'         : ( +0.251091    , 0.00490103, -1 )
                         , 'AperpPhase'        : ( +3.09112     , 0.142579  , -1 )
                         , 'Gamma'             : ( +0.659072    , 0.00311091, -1 )
                         , 'dGamma'            : ( +0.0787202   , 0.00913929, -1 )
                         , 'phiCP'             : ( -0.060228    , 0.0497014 , -1 )
                         , 'betaTimeEff_p2011' : ( -0.00863596  , 0.00204396, -1 )
                         , 'betaTimeEff_p2012' : ( -0.0126666   , 0.00180044, -1 )
                         , 'dM'                : ( +17.7199     , 0.0561276 , -1 )
                         , 'f_S_bin0'          : ( +0.426614    , 0.0540601 , -1 )
                         , 'f_S_bin1'          : ( +0.0591684   , 0.017542 ,  -1 )
                         , 'f_S_bin2'          : ( +0.00951391  , 0.00653881, -1 )
                         , 'f_S_bin3'          : ( +0.00939672  , 0.00581715, -1 )
                         , 'f_S_bin4'          : ( +0.0482976   , 0.0154137 , -1 )
                         , 'f_S_bin5'          : ( +0.191859    , 0.0254653 , -1 )
                         , 'lambdaCP'          : ( +0.95959     , 0.0194776 , -1 )
                         , 'Re_Z'              : ( -0.0215716   , 0.0331882 , -1 )
                         }
#nominal values of physics parameters for CPT violation, with Im(z) not zero
#some tagging parms set to be constant; the CP model used is lamb_phi
parValues_Pheno    = {  'A0Mag2'           : ( +0.523857    , 0.0034617, -1  )
                     , 'ASOddPhase_bin0'   : ( +0.848774    , 0.200628  , -1 )
                     , 'ASOddPhase_bin1'   : ( +2.15616     , 0.27146   , -1 )
                     , 'ASOddPhase_bin2'   : ( +0.48063     , 0.2182    , -1 )
                     , 'ASOddPhase_bin3'   : ( -0.365466    , 0.183443  , -1 )
                     , 'ASOddPhase_bin4'   : ( -0.588966    , 0.153543  , -1 )
                     , 'ASOddPhase_bin5'   : ( -0.910024    , 0.141227  , -1 )
                     , 'AparPhase'         : ( +3.25784     , 0.121088  , -1 )
                     , 'AperpMag2'         : ( +0.250892    , 0.00495553, -1 )
                     , 'AperpPhase'        : ( +3.11829     , 0.157115  , -1 )
                     , 'Gamma'             : ( +0.659049    , 0.00311215, -1 )
                     , 'dGamma'            : ( +0.079024    , 0.00918372, -1 )
                     , 'phiCP'             : ( -0.0695266   , 0.0561305 , -1 )
                     , 'betaTimeEff_p2011' : ( -0.00863939  , 0.00204348, -1 )
                     , 'betaTimeEff_p2012' : ( -0.012669    , 0.00180013, -1 )
                     , 'dM'                : ( +17.7298     , 0.0605143 , -1 )
                     , 'f_S_bin0'          : ( +0.425329    , 0.0540289 , -1 )
                     , 'f_S_bin1'          : ( +0.0590739   , 0.0174248 , -1 )
                     , 'f_S_bin2'          : ( +0.0096493   , 0.00651712, -1 )
                     , 'f_S_bin3'          : ( +0.00932046  , 0.00579826, -1 )
                     , 'f_S_bin4'          : ( +0.0483135   , 0.0153502 , -1 )
                     , 'f_S_bin5'          : ( 0.191662     , 0.0254703 , -1 )
                     , 'lambdaCP'          : ( +0.958228    , 0.0197197 , -1 )
                     , 'Re_Z'              : ( -0.022112    , 0.0331901 , -1 )
                     , 'Im_Z'              : (  0.00426309  , 0.0107968 , -1 )
                     }

#physics parameters for CPT violation with Sidereal Variations, with Im(z) not zero
#some tagging parms set to be constant; the CP model used is lamb_phi. Collimated analysis
parValues_SMEc    = {  'A0Mag2'           : ( +0.523638    ,0.00343984, -1  )
                    , 'ASOddPhase_bin0'   : ( +0.845481    , 0.199553  , -1 )
                    , 'ASOddPhase_bin1'   : ( +2.14342     , 0.284439  , -1 )
                    , 'ASOddPhase_bin2'   : ( +0.474048     ,0.214137  , -1 )
                    , 'ASOddPhase_bin3'   : ( -0.366048    , 0.180651  , -1 )
                    , 'ASOddPhase_bin4'   : ( -0.592309    , 0.155693  , -1 )
                    , 'ASOddPhase_bin5'   : ( -0.904448    , 0.139881  , -1 )
                    , 'AparPhase'         : ( +3.25664     , 0.122247  , -1 )
                    , 'AperpMag2'         : ( +0.251222    , 0.00489971, -1 )
                    , 'AperpPhase'        : ( +3.09796     , 0.141563  , -1 )
                    , 'Gamma'             : ( +0.659228    , 0.00310976, -1 )
                    , 'dGamma'            : ( +0.0784446   , 0.00914389, -1 )
                    , 'phiCP'             : ( -0.0651711   , 0.0497076 , -1 )
                    , 'betaTimeEff_p2011' : ( -0.00863321  , 0.00204351, -1 )
                    , 'betaTimeEff_p2012' : ( -0.012662    , 0.00180015, -1 )
                    , 'dM'                : ( +17.7201     , 0.056052  , -1 )
                    , 'f_S_bin0'          : ( +0.425663    , 0.054001  , -1 )
                    , 'f_S_bin1'          : ( +0.0582913   , 0.0175278 , -1 )
                    , 'f_S_bin2'          : ( +0.00985804  , 0.00654275, -1 )
                    , 'f_S_bin3'          : ( +0.00960446  , 0.00587973, -1 )
                    , 'f_S_bin4'          : ( +0.0480695   , 0.0154081 , -1 )
                    , 'f_S_bin5'          : ( +0.191101    , 0.0254492 , -1 )
                    , 'lambdaCP'          : ( +0.960582    , 0.0192007 , -1 )
                    , 'DaX'               : ( +0.0143344   , 0.0315905 , -1 )
                    , 'DaY'               : ( -0.0579395   , 0.0315536 , -1 )
                    , 'Da0-0.38DaZ'       : ( -0.0146119   , 0.0213707 , -1 )
                       }

#physics parameters for CPT violation in the context of SME using the full description for the Re(z)--> No collimated analysis.
parValues_SMEf =       {  'A0Mag2'           : ( +0.5237    ,0.00344024  , -1 )
                       , 'ASOddPhase_bin0'   : ( +0.846485     ,0.199747   , -1 )
                       , 'ASOddPhase_bin1'   : ( +2.15431     ,0.276031   , -1 )
                       , 'ASOddPhase_bin2'   : ( +0.471481    ,0.211368   , -1 )
                       , 'ASOddPhase_bin3'   : ( -0.36673    , 0.180428  , -1 )
                       , 'ASOddPhase_bin4'   : ( -0.592941    , 0.155725  , -1 )
                       , 'ASOddPhase_bin5'   : ( -0.904632    , 0.13974  , -1 )
                       , 'AparPhase'         : ( +3.25583      , 0.123031  , -1 )
                       , 'AperpMag2'         : ( +0.251175    , 0.00489891, -1 )
                       , 'AperpPhase'        : ( +3.10762     , 0.140656  , -1 )
                       , 'Gamma'             : ( +0.659224    , 0.00310917 , -1 )
                       , 'dGamma'            : ( +0.0785203   , 0.00914151, -1 )
                       , 'phiCP'             : ( -0.0638601   , 0.0496983 , -1 )
                       , 'betaTimeEff_p2011' : ( -0.0086337   , 0.00204352, -1 )
                       , 'betaTimeEff_p2012' : ( -0.0126625   , 0.00180016, -1 )
                       , 'dM'                : ( +17.7236     , 0.0552724 , -1 )
                       , 'f_S_bin0'          : ( +0.424773    , 0.0539647 , -1 )
                       , 'f_S_bin1'          : ( +0.0588503   , 0.0175042 , -1 )
                       , 'f_S_bin2'          : ( +0.00996876  , 0.00654604, -1 )
                       , 'f_S_bin3'          : ( +0.00961504  , 0.00586709, -1 )
                       , 'f_S_bin4'          : ( +0.0481711   , 0.0154206 , -1 )
                       , 'f_S_bin5'          : ( +0.191281    , 0.0254381 , -1 )
                       , 'lambdaCP'          : ( +0.960217    , 0.0191013 , -1 )
                       , 'DaX'               : ( +0.0153518   , 0.0316518 , -1 )
                       , 'DaY'               : ( -0.0582057   , 0.0316997 , -1 )
                       , 'Da1'               : ( -0.0135514   , 0.021458  , -1 )
                       , 'Da2'               : ( -0.714179    , 0.586627  , -1 )
                          }



parValuesCPVDecay = {  'ASOddPhase_bin0'        : ( +0.8651519   , 0.20263224  , -1 )
                     , 'ASOddPhase_bin1'        : ( +2.1240611   , 0.30882125  , -1 )
                     , 'ASOddPhase_bin2'        : ( +0.52693804  , 0.25023634  , -1 )
                     , 'ASOddPhase_bin3'        : ( -0.35428857  , 0.1832169   , -1 )
                     , 'ASOddPhase_bin4'        : ( -0.58524615  , 0.15810649  , -1 )
                     , 'ASOddPhase_bin5'        : ( -0.90506879  , 0.14719732  , -1 )
                     , 'AparPhase'              : ( +3.2458132   , 0.13251596  , -1 )
                     , 'AperpPhase'             : ( +3.0360228   , 0.16476505  , -1 )
                     , 'CCPAv'                  : ( -0.0063327691, 0.038654444 , -1 )
                     , 'CCPAv_AS'               : ( +0.059610789 , 0.0320887   , -1 )
                     , 'CCPRel_Apar'            : ( -0.024859583 , 0.12163897  , -1 )
                     , 'CCPRel_Aperp'           : ( +0.043579554 , 0.16234744  , -1 )
                     , 'Gamma'                  : ( +0.65909951  , 0.0031142114, -1 )
                     , '__dGamma__'             : ( +0.088369008 , 0.0091501675, -1 )
                     , 'dGamma'                 : ( +0.078378293 , 0.0091745564, -1 )
                     , '__phiCPAv__'            : ( +0.13343593  , 0.050939783 , -1 )
                     , 'phiCPAv'                : ( -0.04668364  , 0.050934831 , -1 )
                     , '__phiCPRel_AS__'        : ( -0.22055728  , 0.06213971  , -1 )
                     , 'phiCPRel_AS'            : ( +0.014473037 , 0.062250957 , -1 )
                     , '__phiCPRel_Apar__'      : ( -0.1275711   , 0.042614556 , -1 )
                     , 'phiCPRel_Apar'          : ( -0.018687815 , 0.0426021   , -1 )
                     , '__phiCPRel_AperpApar__' : ( +0.093448879 , 0.028663924 , -1 )
                     , 'phiCPRel_AperpApar'     : ( -0.0025701655, 0.028633872 , -1 )
                     , 'avA02'                  : ( +0.52364923  , 0.0034424813, -1 )
                     , 'avAperp2'               : ( +0.25125265  , 0.0049268499, -1 )
                     , 'avf_S_bin0'             : ( +0.42439043  , 0.054149108 , -1 )
                     , 'avf_S_bin1'             : ( +0.057203752 , 0.017675727 , -1 )
                     , 'avf_S_bin2'             : ( +0.0086430752, 0.0065560183, -1 )
                     , 'avf_S_bin3'             : ( +0.0092896863, 0.0056341201, -1 )
                     , 'avf_S_bin4'             : ( +0.047903675 , 0.015387565 , -1 )
                     , 'avf_S_bin5'             : ( +0.19105515  , 0.025533194 , -1 )
                     , 'betaTimeEff_p2011'      : ( -0.008639038 , 0.0020435314, -1 )
                     , 'betaTimeEff_p2012'      : ( -0.012668832 , 0.0018002709, -1 )
                     , 'dM'                     : ( +17.696216   , 0.062066661 , -1 )
                     , 'wTagDelP0OS'            : ( +0.01402569  , 0.001199917 , -1 )
                     , 'wTagDelP0SS'            : ( -0.015789661 , 0.0013998837, -1 )
                     , 'wTagDelP1OS'            : ( +0.065723732 , 0.011998289 , -1 )
                     , 'wTagDelP1SS'            : ( +0.0083176392, 0.021988225 , -1 )
                     , 'wTagP0OS'               : ( +0.38121293  , 0.0042535384, -1 )
                     , 'wTagP0SS'               : ( +0.44614061  , 0.0046639048, -1 )
                     , 'wTagP1OS'               : ( +1.011308    , 0.034448767 , -1 )
                     , 'wTagP1SS'               : ( +0.96582722  , 0.082988063 , -1 )
                    }

parValuesFixLamb = {  'A0Mag2'            : ( +0.52363959  , 0.0034381486, -1 )
                    , 'ASOddPhase_bin0'   : ( +0.83997549  , 0.1995812   , -1 )
                    , 'ASOddPhase_bin1'   : ( +2.1501308   , 0.28873084  , -1 )
                    , 'ASOddPhase_bin2'   : ( +0.48276779  , 0.23080037  , -1 )
                    , 'ASOddPhase_bin3'   : ( -0.40315359  , 0.21489334  , -1 )
                    , 'ASOddPhase_bin4'   : ( -0.62415686  , 0.17636958  , -1 )
                    , 'ASOddPhase_bin5'   : ( -0.90094744  , 0.13935781  , -1 )
                    , 'AparPhase'         : ( +3.264085    , 0.12326559  , -1 )
                    , 'AperpMag2'         : ( +0.25118246  , 0.0049154903, -1 )
                    , 'AperpPhase'        : ( +3.0433104   , 0.16086479  , -1 )
                    , 'Gamma'             : ( +0.65907776  , 0.0031102199, -1 )
                    , '__dGamma__'        : ( +0.088542763 , 0.0091191873, -1 )
                    , 'dGamma'            : ( +0.078501399 , 0.0091489262, -1 )
                    , '__phiCP__'         : ( +0.073734246 , 0.049030444 , -1 )
                    , 'phiCP'             : ( -0.056329102 , 0.049040849 , -1 )
                    , 'betaTimeEff_p2011' : ( -0.0086401312, 0.0020435952, -1 )
                    , 'betaTimeEff_p2012' : ( -0.012670147 , 0.0018001712, -1 )
                    , 'dM'                : ( +17.697058   , 0.060098527 , -1 )
                    , 'f_S_bin0'          : ( +0.42604376  , 0.054055705 , -1 )
                    , 'f_S_bin1'          : ( +0.058901554 , 0.017984302 , -1 )
                    , 'f_S_bin2'          : ( +0.0095127616, 0.0068338671, -1 )
                    , 'f_S_bin3'          : ( +0.0078898616, 0.0057128832, -1 )
                    , 'f_S_bin4'          : ( +0.045036858 , 0.016065246 , -1 )
                    , 'f_S_bin5'          : ( +0.19237822  , 0.02548142  , -1 )
                    , 'wTagDelP0OS'       : ( +0.014025337 , 0.001199902 , -1 )
                    , 'wTagDelP0SS'       : ( -0.015789236 , 0.0013998678, -1 )
                    , 'wTagDelP1OS'       : ( +0.065723095 , 0.011998154 , -1 )
                    , 'wTagDelP1SS'       : ( +0.008291887 , 0.021987834 , -1 )
                    , 'wTagP0OS'          : ( +0.38124699  , 0.0042517145, -1 )
                    , 'wTagP0SS'          : ( +0.4459204   , 0.0046459804, -1 )
                    , 'wTagP1OS'          : ( +1.0115834   , 0.034428275 , -1 )
                    , 'wTagP1SS'          : ( +0.96225279  , 0.082786818 , -1 )
                   }


parValues20131203 = {  'A0Mag2'            : (  5.2080e-01, 3.45e-03, -1 )
                     , 'ASOddPhase_bin0'   : (  8.2353e-01, 1.85e-01, -1 )
                     , 'ASOddPhase_bin1'   : (  2.2694e+00, 2.22e-01, -1 )
                     , 'ASOddPhase_bin2'   : (  4.2763e-01, 1.90e-01, -1 )
                     , 'ASOddPhase_bin3'   : ( -3.6125e-01, 1.86e-01, -1 )
                     , 'ASOddPhase_bin4'   : ( -6.2751e-01, 1.65e-01, -1 )
                     , 'ASOddPhase_bin5'   : ( -8.9047e-01, 1.38e-01, -1 )
                     , 'AparPhase'         : (  3.2492e+00, 1.29e-01, -1 )
                     , 'AperpMag2'         : (  2.5361e-01, 4.92e-03, -1 )
                     , 'AperpPhase'        : (  3.1662e+00, 1.17e-01, -1 )
                     , 'Gamma'             : (  6.6112e-01, 6.00e-03, -1 )
                     , '__dGamma__'        : (  8.6749e-02, 9.16e-03, -1 )
                     , '__phiCP__'         : (  7.0521e-02, 5.14e-02, -1 )
                     , 'betaTimeEff_p2011' : ( -8.2819e-03, 4.00e-03, -1 )
                     , 'betaTimeEff_p2012' : ( -1.3524e-02, 6.54e-03, -1 )
                     , 'dM'                : (  1.7762e+01, 2.21e-02, -1 )
                     , 'f_S_bin0'          : (  4.4391e-01, 5.47e-02, -1 )
                     , 'f_S_bin1'          : (  6.0500e-02, 1.79e-02, -1 )
                     , 'f_S_bin2'          : (  1.0335e-02, 6.74e-03, -1 )
                     , 'f_S_bin3'          : (  8.7773e-03, 5.82e-03, -1 )
                     , 'f_S_bin4'          : (  4.8669e-02, 1.61e-02, -1 )
                     , 'f_S_bin5'          : (  1.9547e-01, 2.58e-02, -1 )
                     , 'lambdaCP'          : (  9.6630e-01, 1.78e-02, -1 )
                     , 'wTagDelP0OS'       : (  1.3722e-02, 1.20e-03, -1 )
                     , 'wTagDelP0SS'       : ( -1.5989e-02, 2.00e-03, -1 )
                     , 'wTagDelP1OS'       : (  6.9705e-02, 1.20e-02, -1 )
                     , 'wTagDelP1SS'       : (  1.5208e-02, 1.90e-02, -1 )
                     , 'wTagP0OS'          : (  3.9250e-01, 9.06e-03, -1 )
                     , 'wTagP0SS'          : (  4.3908e-01, 6.69e-03, -1 )
                     , 'wTagP1OS'          : (  1.0296e+00, 5.69e-02, -1 )
                     , 'wTagP1SS'          : (  9.3231e-01, 1.03e-01, -1 )
                    }

parValues2011 = {  'phiCP'           : (  6.9616e-02, 9.09e-02, -1. )
                 , 'lambdaCP'        : (  9.4368e-01, 3.04e-02, -1. )
                 , 'Gamma'           : (  6.7132e-01, 4.80e-03, -1. )
                 , 'dGamma'          : (  1.0053e-01, 1.62e-02, -1. )
                 , 'dM'              : (  1.7667e+01, 7.68e-02, -1. )
                 , 'A0Mag2'          : (  5.2122e-01, 6.08e-03, -1. )
                 , 'AperpMag2'       : (  2.4848e-01, 8.69e-03, -1. )
                 , 'f_S_bin0'        : (  2.2751e-01, 7.74e-02, -1. )
                 , 'f_S_bin1'        : (  6.7228e-02, 2.86e-02, -1. )
                 , 'f_S_bin2'        : (  7.9881e-03, 1.16e-02, -1. )
                 , 'f_S_bin3'        : (  1.6367e-02, 1.08e-02, -1. )
                 , 'f_S_bin4'        : (  5.4997e-02, 2.64e-02, -1. )
                 , 'f_S_bin5'        : (  1.6757e-01, 4.24e-02, -1. )
                 , 'AparPhase'       : (  3.3097e+00, 1.54e-01, -1. )
                 , 'AperpPhase'      : (  3.0759e+00, 2.17e-01, -1. )
                 , 'ASOddPhase_bin0' : (  1.3140e+00, 6.81e-01, -1. )
                 , 'ASOddPhase_bin1' : (  7.6351e-01, 2.76e-01, -1. )
                 , 'ASOddPhase_bin2' : (  4.9424e-01, 4.60e-01, -1. )
                 , 'ASOddPhase_bin3' : ( -5.0928e-01, 2.55e-01, -1. )
                 , 'ASOddPhase_bin4' : ( -4.5728e-01, 2.08e-01, -1. )
                 , 'ASOddPhase_bin5' : ( -6.5000e-01, 1.98e-01, -1. )
                 , 'm_sig_frac'      : (  7.5966e-01, 3.49e-02, -1. )
                 , 'm_sig_mean'      : (  5.3682e+03, 4.84e-02, -1. )
                 , 'm_sig_sigma_1'   : (  6.0797e+00, 1.33e-01, -1. )
                 , 'm_sig_sigma_sf'  : (  2.0652e+00, 8.87e-02, -1. )
                 , 'm_bkg_exp_bin0'  : ( -1.7313e-03, 1.47e-04, -1. )
                 , 'm_bkg_exp_bin1'  : ( -1.7486e-03, 1.77e-04, -1. )
                 , 'm_bkg_exp_bin2'  : ( -1.7360e-03, 1.98e-04, -1. )
                 , 'm_bkg_exp_bin3'  : ( -1.2316e-03, 1.98e-04, -1. )
                 , 'm_bkg_exp_bin4'  : ( -1.5366e-03, 1.55e-04, -1. )
                 , 'm_bkg_exp_bin5'  : ( -1.5859e-03, 9.95e-05, -1. )
                }

# fit parameters values for Bs-->JpsiKst
jspiKstParValues_Bs_3fb_freeACP = { 'A0Mag2'          :  ( +0.5094,  0.0237, -1 ),
                                    'ACP0'            :  ( -0.0672,  0.0535, -1 ),
                                    'ACPS'            :  ( +0.0689,  0.0500, -1 ),
                                    'ACPpar'          :  ( +0.1615,  0.1494, -1 ),
                                    'ACPperp'         :  ( -0.0532,  0.0935, -1 ),
                                    'ASPhase_bin1'    :  ( +0.4960,  0.1577, -1 ),
                                    'ASPhase_bin2'    :  ( -0.5082,  0.2114, -1 ),
                                    'ASPhase_bin3'    :  ( -1.2804,  0.2027, -1 ),
                                    'ASPhase_bin4'    :  ( -1.6422,  0.1378, -1 ),
                                    'AparPhase'       :  ( -2.6803,  0.1512, -1 ),
                                    'AperpMag2'       :  ( +0.3167,  0.0279, -1 ),
                                    'AperpPhase'      :  ( +0.0045,  0.1075, -1 ),
                                    'Yield_2011_bin1' :  ( +33.484,  5.7211, -1 ),
                                    'Yield_2011_bin2' :  ( +147.64,  12.117, -1 ),
                                    'Yield_2011_bin3' :  ( +177.83,  13.299, -1 ),
                                    'Yield_2011_bin4' :  ( +47.740,  6.8431, -1 ),
                                    'Yield_2012_bin1' :  ( +60.226,  7.6992, -1 ),
                                    'Yield_2012_bin2' :  ( +297.04,  17.209, -1 ),
                                    'Yield_2012_bin3' :  ( +380.10,  19.465, -1 ),
                                    'Yield_2012_bin4' :  ( +128.22,  11.290, -1 ),
                                    'f_S_bin1'        :  ( +0.4099,  0.0568, -1 ),
                                    'f_S_bin2'        :  ( +0.0920,  0.0278, -1 ),
                                    'f_S_bin3'        :  ( +0.0440,  0.0336, -1 ),
                                    'f_S_bin4'        :  ( +0.5465,  0.0253, -1 ),
                                }

jspiKstParValues_Bs_3fb_zeroACP = { 'A0Mag2'          :  ( +0.5073, 0.0240, -1 ),
                                    'ASPhase_bin1'    :  ( +0.5268, 0.1525, -1 ),
                                    'ASPhase_bin2'    :  ( -0.5143, 0.2151, -1 ),
                                    'ASPhase_bin3'    :  ( -1.2788, 0.2028, -1 ),
                                    'ASPhase_bin4'    :  ( -1.6690, 0.1285, -1 ),
                                    'AparPhase'       :  ( -2.7001, 0.1525, -1 ),
                                    'AperpMag2'       :  ( +0.3182, 0.0283, -1 ),
                                    'AperpPhase'      :  ( -0.0006, 0.1097, -1 ),
                                    'Yield_2011_bin1' :  ( +33.492, 5.7224, -1 ),
                                    'Yield_2011_bin2' :  ( +147.63, 12.116, -1 ),
                                    'Yield_2011_bin3' :  ( +177.81, 13.298, -1 ),
                                    'Yield_2011_bin4' :  ( +47.763, 6.8464, -1 ),
                                    'Yield_2012_bin1' :  ( +60.239, 7.7009, -1 ),
                                    'Yield_2012_bin2' :  ( +297.02, 17.208, -1 ),
                                    'Yield_2012_bin3' :  ( +380.06, 19.462, -1 ),
                                    'Yield_2012_bin4' :  ( +128.28, 11.296, -1 ),
                                    'f_S_bin1'        :  ( +0.4335, 0.1011, -1 ),
                                    'f_S_bin2'        :  ( +0.0925, 0.0285, -1 ),
                                    'f_S_bin3'        :  ( +0.0453, 0.0344, -1 ),
                                    'f_S_bin4'        :  ( +0.5010, 0.1144, -1 ),
                                }

# fit parameters values for Bd-->JpsiKst
jspiKstParValues_Bd_3fb_freeACP = { 'A0Mag2'          :( +0.5542,  0.0017, -1 ),
                                    'ACP0'            :( -0.0123,  0.0041, -1 ),
                                    'ACPS'            :( +0.0344,  0.0293, -1 ),
                                    'ACPpar'          :( -0.0051,  0.0091, -1 ),
                                    'ACPperp'         :( -0.0293,  0.0093, -1 ),
                                    'ASPhase_bin1'    :( +3.1756,  0.0700, -1 ),
                                    'ASPhase_bin2'    :( +2.4624,  0.0450, -1 ),
                                    'ASPhase_bin3'    :( +1.5333,  0.0181, -1 ),
                                    'ASPhase_bin4'    :( +1.2544,  0.0198, -1 ),
                                    'AparPhase'       :( -2.9523,  0.0119, -1 ),
                                    'AperpMag2'       :( +0.2221,  0.0020, -1 ),
                                    'AperpPhase'      :( +2.9239,  0.0096, -1 ),
                                    'Yield_2011_bin1' :( +7207.3,  84.896, -1 ),
                                    'Yield_2011_bin2' :( +26548.,  162.95, -1 ),
                                    'Yield_2011_bin3' :( +23811.,  154.32, -1 ),
                                    'Yield_2011_bin4' :( +7606.8,  87.22 , -1 ),
                                    'Yield_2012_bin1' :( +15274.,  123.62, -1 ),
                                    'Yield_2012_bin2' :( +56418.,  237.51, -1 ),
                                    'Yield_2012_bin3' :( +50441.,  224.62, -1 ),
                                    'Yield_2012_bin4' :( +16089 ,  126.85, -1 ),
                                    'f_S_bin1'        :( +0.0836,  0.0039, -1 ),
                                    'f_S_bin2'        :( +0.0227,  0.0018, -1 ),
                                    'f_S_bin3'        :( +0.0318,  0.0027, -1 ),
                                    'f_S_bin4'        :( +0.1048,  0.0067, -1 )
                        }

jspiKstParValues_Bd_3fb_zeroACP = { 'A0Mag2'          :( +0.5542, 0.0017, -1 ),
                                    'ASPhase_bin1'    :( +3.1769, 0.0693, -1 ),
                                    'ASPhase_bin2'    :( +2.4640, 0.0451, -1 ),
                                    'ASPhase_bin3'    :( +1.5328, 0.0181, -1 ),
                                    'ASPhase_bin4'    :( +1.2541, 0.0198, -1 ),
                                    'AparPhase'       :( -2.952,  0.0119, -1 ),
                                    'AperpMag2'       :( +0.2220, 0.0020, -1 ),
                                    'AperpPhase'      :( +2.9239, 0.0096, -1 ),
                                    'Yield_2011_bin1' :( +7205.8, 84.879, -1 ),
                                    'Yield_2011_bin2' :( +26541., 162.92, -1 ),
                                    'Yield_2011_bin3' :( +23804., 154.26, -1 ),
                                    'Yield_2011_bin4' :( +7605.4, 87.200, -1 ),
                                    'Yield_2012_bin1' :( +15271., 123.55, -1 ),
                                    'Yield_2012_bin2' :( +56401., 237.47, -1 ),
                                    'Yield_2012_bin3' :( +50427., 224.56, -1 ),
                                    'Yield_2012_bin4' :( +16086 , 126.82, -1 ),
                                    'f_S_bin1'        :( +0.0834, 0.0039, -1 ),
                                    'f_S_bin2'        :( +0.0226, 0.0018, -1 ),
                                    'f_S_bin3'        :( +0.0319, 0.0027, -1 ),
                                    'f_S_bin4'        :( +0.1051, 0.0067, -1 )
                                }

#  experimental assymetries and expected yields for Bs2JpsiKst analysis
JpsiKstExperimentalAssymetries = dict(
    Bs = dict( Detection  = ( -0.01086, 0.00531 ),
               Production = ( -0.01640, 0.02280 )
           ),
    Bd = dict( Detection  = ( +0.01115, 0.00547 ),
               Production = ( -0.01040, 0.00480 )
           )
)

JpsiKstExpectedYields = dict(

    Bs = dict( Yield_2011_bin1 = ( 33,  5.  ),
               Yield_2011_bin2 = ( 147, 12. ),
               Yield_2011_bin3 = ( 177, 13. ),
               Yield_2011_bin4 = ( 47,  6.  ),
               Yield_2012_bin1 = ( 60,  7.  ),
               Yield_2012_bin2 = ( 296, 17. ),
               Yield_2012_bin3 = ( 380, 19. ),
               Yield_2012_bin4 = ( 128, 11. ),
           ),

    Bd = dict( Yield_2011_bin1 = ( 7207. , 84.  ),
               Yield_2011_bin2 = ( 26549., 162. ),
               Yield_2011_bin3 = ( 23811., 154. ),
               Yield_2011_bin4 = ( 7606. , 87.  ),
               Yield_2012_bin1 = ( 15274., 123. ),
               Yield_2012_bin2 = ( 56418., 237. ),
               Yield_2012_bin3 = ( 50441., 224. ),
               Yield_2012_bin4 = ( 16088., 126. ),
           )
)

 # trigger selection strings
triggerSelStrings = dict(  noSelection        = ''
                         , HLT1Unbiased       = 'hlt1_unbiased_dec==1 && hlt2_biased==1'
                         , HLT1Unbiased_tos   = 'hlt1_unbiased==1 && hlt2_biased==1'
                         , HLT1ExclBiased     = 'hlt1_excl_biased_dec==1 && hlt2_biased==1'
                         , HLT1ExclBiased_tos = 'hlt1_excl_biased==1 && hlt2_biased==1'
                         , paper2012          = '(hlt1_excl_biased_dec==1 || hlt1_unbiased_dec==1) && hlt2_biased==1'
                         , paper2012_tos      = '(hlt1_excl_biased==1 || hlt1_unbiased==1) && hlt2_biased==1'
                         , timeEffFit         = '(hlt1_excl_biased_dec==1 || hlt1_unbiased_dec==1) && (hlt2_biased==1 || hlt2_unbiased==1)'
                         , timeEffFit_tos     = '(hlt1_excl_biased==1 || hlt1_unbiased==1) && (hlt2_biased==1 || hlt2_unbiased==1)'
                         , unbiased           = 'hlt1_unbiased==1 && hlt2_unbiased==1'
                        )

# cut selection strings
cutSelStrings = dict(  noSelection = ''
                     , nominal2011 = 'sel == 1 && sel_cleantail == 1'\
                                     ' && time>0.3 && time<14. && sigmat<0.12'\
                                     ' && mass>5200. && mass<5550. && abs(mdau1-3090.)<60. && abs(mdau2-1020.)<30.'\
                                     ' && muplus_track_chi2ndof < 4. && muminus_track_chi2ndof < 4.'\
                                     ' && Kplus_track_chi2ndof < 4. && Kminus_track_chi2ndof < 4.'
                    )

# external constraint values dictionary
class ExtConstrValsDict( dict ) :
    def __init__( self, valsDict ) :
        for key, val in valsDict.iteritems() : self[key] = val

    def valsDict(self)           : return self.copy()
    def getVal( self, key )      : return self[key]
    def setVal( self, key, val ) : self[key] = val

    def getSetVal( self, key, val = None ) :
        if not key in self :
            assert val != None, 'ExtConstrValsDict.getSetVal(): no value provided'
            self[key] = val
        return self[key]

constrVals = dict(  DM      = (  17.768, 0.024  )
                  , beta    = ( -8.3e-3, 4.0e-3 )
                  , P0OS    = (  0.392,  0.008, 0.392 )
                  , P0SS    = (  0.350,  0.017, 0.350 )
                  , P1OS    = (  1.000,  0.023  )
                  , P1SS    = (  1.00,   0.16   )
                  , DelP0OS = (  0.0110, 0.0034 )
                  , DelP0SS = ( -0.019,  0.005  )
                  , DelP1OS = (  0.000,  0.001  )
                  , DelP1SS = (  0.00,   0.01   )
                 )
global extConstraintValues
extConstraintValues = ExtConstrValsDict( constrVals )
