eosdir = "/eos/lhcb/wg/PID/PIDGen/Data/Run1"
eosrootdir = "root://eoslhcb.cern.ch/" + eosdir

tmpdir = "/tmp/poluekt/"

samples = {
  "gammaKst" : {
    'reco' : None, 
    'datasets' : {
      '2012'   : "/eos/lhcb/wg/CaloObj/CalibSamples/S21/KstGamma_S21Data_2012_sWeights.root", 
      '2011'   : "/eos/lhcb/wg/CaloObj/CalibSamples/S21/KstGamma_S21Data_2011_sWeights.root", 
    }, 
    'tree'    : "DecayTree", 
    'pt'      : "gamma_PT", 
    'eta'     : "gamma_ETA", 
    'ntracks' : None, 
    'weight'  : "nkstgWeight", 
  }, 
  "p" : {
    'reco' : 'Reco14_DATA', 
    'datasets' : {
      'MagUp_2012'   : ("IncLc_P_MagUp_Strip20_%d.root", 2), 
      'MagDown_2012' : ("IncLc_P_MagDown_Strip20_%d.root", 3), 
      'MagUp_2011'   : ("IncLc_P_MagUp_Strip20r1_%d.root", 1), 
      'MagDown_2011' : ("IncLc_P_MagDown_Strip20r1_%d.root", 2),
    }, 
    'tree'    : "IncLcCalib", 
    'pt'      : "P_PT", 
    'eta'     : "P_Eta", 
    'ntracks' : "nTracks", 
  }, 
  "K" : {
    'reco' : 'Reco14_DATA', 
    'datasets' : {
      'MagUp_2012'   : ("DSt_K_MagUp_Strip20_%d.root", 72+1), 
      'MagDown_2012' : ("DSt_K_MagDown_Strip20_%d.root", 71+1), 
      'MagUp_2011'   : ("DSt_K_MagUp_Strip20r1_%d.root", 24+1), 
      'MagDown_2011' : ("DSt_K_MagDown_Strip20r1_%d.root", 35+1),
    }, 
    'tree'    : "RSDStCalib", 
    'pt'      : "K_PT", 
    'eta'     : "K_Eta", 
    'ntracks' : "nTracks", 
  }, 
  "pi" : {
    'reco' : 'Reco14_DATA', 
    'datasets' : {
      'MagUp_2012'   : ("DSt_Pi_MagUp_Strip20_%d.root", 72+1), 
      'MagDown_2012' : ("DSt_Pi_MagDown_Strip20_%d.root", 71+1), 
      'MagUp_2011'   : ("DSt_Pi_MagUp_Strip20r1_%d.root", 24+1), 
      'MagDown_2011' : ("DSt_Pi_MagDown_Strip20r1_%d.root", 35+1),
    }, 
    'tree'    : "RSDStCalib", 
    'pt'      : "Pi_PT", 
    'eta'     : "Pi_Eta", 
    'ntracks' : "nTracks", 
  }, 
  "mu" : {
    'reco' : 'Reco14_DATA', 
    'datasets' : {
      'MagUp_2012'   : ("Jpsi_Mu_MagUp_Strip20_%d.root", 81+1), 
      'MagDown_2012' : ("Jpsi_Mu_MagDown_Strip20_%d.root", 79+1), 
      'MagUp_2011'   : ("Jpsi_Mu_MagUp_Strip20r1_%d.root", 18+1), 
      'MagDown_2011' : ("Jpsi_Mu_MagDown_Strip20r1_%d.root", 26+1),
    }, 
    'tree'    : "JpsiCalib", 
    'pt'      : "Mu_PT", 
    'eta'     : "Mu_Eta", 
    'ntracks' : "nTracks", 
  }, 
  "e20" : {
    'reco' : 'Reco14_DATA', 
    'datasets' : {
      'MagUp_2012'   : ("Jpsi_e_MagUp_Strip20_%d.root", 1), 
      'MagDown_2012' : ("Jpsi_e_MagDown_Strip20_%d.root", 1), 
      'MagUp_2011'   : ("Jpsi_e_MagUp_Strip20r1_%d.root", 1), 
      'MagDown_2011' : ("Jpsi_e_MagDown_Strip20r1_%d.root", 1),
    }, 
    'tree'    : "JpsieeCalib", 
    'pt'      : "e_PT", 
    'eta'     : "e_Eta", 
    'ntracks' : "nTracks", 
  }, 
  "e21" : {
    'reco' : 'Reco14_DATA', 
    'datasets' : {
      'MagUp_2012'   : ("Jpsi_e_MagUp_Strip21_%d.root", 1), 
      'MagDown_2012' : ("Jpsi_e_MagDown_Strip21_%d.root", 1), 
      'MagUp_2011'   : ("Jpsi_e_MagUp_Strip21r1_%d.root", 1), 
      'MagDown_2011' : ("Jpsi_e_MagDown_Strip21r1_%d.root", 1),
    }, 
    'tree'    : "JpsieeCalib", 
    'pt'      : "e_PT", 
    'eta'     : "e_Eta", 
    'ntracks' : "nTracks", 
  }, 
}

configs = {
  "p_V3ProbNNp" : {
    "sample" : "p", 
    "var" : "P_V3ProbNNp", 
    "bins" : 50, 
    "transform_forward"  : "1.-sqrt(1.-x)", 
    "transform_backward" : "(1.-(1.-x)*(1.-x))", 
    'scale_default' : 1.0, 
    'scale_syst'    : 1.3, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 10
  }, 
  "p_V2ProbNNp" : {
    "sample" : "p", 
    "var" : "P_V2ProbNNp", 
    "bins" : 50, 
    "transform_forward"  : "1.-sqrt(1.-x)", 
    "transform_backward" : "(1.-(1.-x)*(1.-x))", 
    'scale_default' : 1.0, 
    'scale_syst'    : 1.3, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "K_V3ProbNNK" : {
    "sample" : "K", 
    "var" : "K_V3ProbNNK", 
    "bins" : 100, 
    "transform_forward"  : "1.-(1.-x)**0.15", 
    "transform_backward" : "(1.-(1.-x)**(1./0.15))", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "K_V3ProbNNpi" : {
    "sample" : "K", 
    "var" : "K_V3ProbNNpi", 
    "bins" : 100, 
    "transform_forward"  : "x**0.2", 
    "transform_backward" : "x**(1./0.2)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "pi_V3ProbNNpi" : {
    "sample" : "pi", 
    "var" : "Pi_V3ProbNNpi", 
    "bins" : 100, 
    "transform_forward"  : "1.-(1.-x)**0.3", 
    "transform_backward" : "(1.-(1.-x)**(1./0.3))", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "pi_V3ProbNNK" : {
    "sample" : "pi", 
    "var" : "Pi_V3ProbNNK", 
    "bins" : 100, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "mu_V3ProbNNmu" : {
    "sample" : "mu", 
    "var" : "Mu_V3ProbNNmu", 
    "bins" : 100, 
    "transform_forward"  : "1.-(1.-x)**0.25", 
    "transform_backward" : "(1.-(1.-x)**(1./0.25))", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "K_CombDLLK" : {
    "sample" : "K", 
    "var" : "K_CombDLLK", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'limits' : (-20., 100), 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "pi_CombDLLK" : {
    "sample" : "pi", 
    "var" : "Pi_CombDLLK", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'limits' : (-100., 20), 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "mu_CombDLLmu" : {
    "sample" : "mu", 
    "var" : "Mu_CombDLLmu", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 100, 
    "limits" : (-10., 20.), 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  },
  "K_CombDLLmu" : {
    "sample" : "K", 
    "var" : "K_CombDLLmu", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 100, 
    "limits" : (-15., 15.), 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 5
  },
  "pi_CombDLLmu" : {
    "sample" : "pi", 
    "var" : "Pi_CombDLLmu", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 100, 
    "limits" : (-15., 15.), 
    'scale_default' : 0.1, 
    'scale_syst' : 0.15, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 5
  },
  "K_V3ProbNNp" : {
    "sample" : "K", 
    "var" : "K_V3ProbNNp", 
    "bins" : 100, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "pi_V3ProbNNp" : {
    "sample" : "pi", 
    "var" : "Pi_V3ProbNNp", 
    "bins" : 100, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "K_V2ProbNNK" : {
    "sample" : "K", 
    "var" : "K_V2ProbNNK", 
    "bins" : 100, 
    "transform_forward"  : "1.-(1.-x)**0.15", 
    "transform_backward" : "(1.-(1.-x)**(1./0.15))", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "K_V2ProbNNpi" : {
    "sample" : "K", 
    "var" : "K_V2ProbNNpi", 
    "bins" : 100, 
    "transform_forward"  : "x**0.2", 
    "transform_backward" : "x**(1./0.2)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 10
  }, 
  "K_V2ProbNNp" : {
    "sample" : "K", 
    "var" : "K_V2ProbNNp", 
    "bins" : 100, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 0
  }, 

  "p_V3ProbNNpi" : {
    "sample" : "p", 
    "var" : "P_V3ProbNNpi", 
    "bins" : 30, 
    "transform_forward"  : "x**0.3", 
    "transform_backward" : "x**(1./0.3)", 
    'scale_default' : 1.0, 
    'scale_syst'    : None, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "p_V3ProbNNK" : {
    "sample" : "p", 
    "var" : "P_V3ProbNNK", 
    "bins" : 30, 
    "transform_forward"  : "x**0.3", 
    "transform_backward" : "x**(1./0.3)", 
    'scale_default' : 1.0, 
    'scale_syst'    : None, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "p_CombDLLK" : {
    "sample" : "p", 
    "var" : "P_CombDLLK", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'limits' : (-30., 60), 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "p_CombDLLp" : {
    "sample" : "p", 
    "var" : "P_CombDLLp", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'limits' : (-20., 100), 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "K_CombDLLp" : {
    "sample" : "K", 
    "var" : "K_CombDLLp", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'limits' : (-100., 70), 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 0
  }, 
  "pi_CombDLLp" : {
    "sample" : "pi", 
    "var" : "Pi_CombDLLp", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'limits' : (-120., 30), 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 0
  }, 
  "pi_V2ProbNNpi" : {
    "sample" : "pi", 
    "var" : "Pi_V2ProbNNpi", 
    "bins" : 100, 
    "transform_forward"  : "1.-(1.-x)**0.3", 
    "transform_backward" : "(1.-(1.-x)**(1./0.3))", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 0
  }, 
  "pi_V2ProbNNK" : {
    "sample" : "pi", 
    "var" : "Pi_V2ProbNNK", 
    "bins" : 100, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 0
  }, 
  "pi_V2ProbNNp" : {
    "sample" : "pi", 
    "var" : "Pi_V2ProbNNp", 
    "bins" : 100, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 0
  }, 
  "p_V2ProbNNpi" : {
    "sample" : "p", 
    "var" : "P_V2ProbNNpi", 
    "bins" : 30, 
    "transform_forward"  : "x**0.3", 
    "transform_backward" : "x**(1./0.3)", 
    'scale_default' : 1.0, 
    'scale_syst'    : None, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "p_V2ProbNNK" : {
    "sample" : "p", 
    "var" : "P_V2ProbNNK", 
    "bins" : 30, 
    "transform_forward"  : "x**0.3", 
    "transform_backward" : "x**(1./0.3)", 
    'scale_default' : 1.0, 
    'scale_syst'    : None, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "pi_V3ProbNNmu" : {
    "sample" : "pi", 
    "var" : "Pi_V3ProbNNmu", 
    "bins" : 100, 
#    "transform_forward"  : "math.tan((x-0.5)*2.9)", 
#    "transform_backward" : "math.atan(x)/2.9+0.5", 
    "transform_forward"  : "1.-(1.-x**0.15)**0.2", 
    "transform_backward" : "1.-(1.-x**(1./0.2))**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 5
  }, 
  "e_S20V3ProbNNe" : {
    "sample" : "e20", 
    "var" : "e_V3ProbNNe", 
    "bins" : 30, 
    "transform_forward"  : "1.-(1.-x)**0.25", 
    "transform_backward" : "(1.-(1.-x)**(1./0.25))", 
    'scale_default' : 1.5, 
    'scale_syst' : 2.0, 
    'scale_pid' : 2.0, 
    'toystat' : 300000, 
    'controlstat' : 300000, 
    'nbootstrap' : 0
  }, 
  "e_S20CombDLLe" : {
    "sample" : "e20", 
    "var" : "e_CombDLLe", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    "limits" : (-20., 20.), 
    'scale_default' : 2.0, 
    'scale_syst' : 2.5, 
    'scale_pid' : 2.0, 
    'toystat' : 300000, 
    'controlstat' : 300000, 
    'nbootstrap' : 10
  }, 
  "e_V3ProbNNe" : {
    "sample" : "e21", 
    "var" : "e_V3ProbNNe", 
    "bins" : 30, 
    "transform_forward"  : "1.-(1.-x)**0.25", 
    "transform_backward" : "(1.-(1.-x)**(1./0.25))", 
    'scale_default' : 1.5, 
    'scale_syst' : 2.0, 
    'scale_pid' : 1.5, 
    'toystat' : 300000, 
    'controlstat' : 300000, 
    'nbootstrap' : 5
  }, 
  "e_CombDLLe" : {
    "sample" : "e21", 
    "var" : "e_CombDLLe", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    "limits" : (-20., 20.), 
    'scale_default' : 2.0, 
    'scale_syst' : 2.5, 
    'scale_pid' : 1.5, 
    'toystat' : 300000, 
    'controlstat' : 300000, 
    'nbootstrap' : 5
  }, 
  "e_V3ProbNNpi" : {
    "sample" : "e21", 
    "var" : "e_V3ProbNNpi", 
    "bins" : 30, 
    "transform_forward"  : "math.tan((x-0.5)*2.9)", 
    "transform_backward" : "math.atan(x)/2.9+0.5", 
    "limits" : (-8.2381, 8.2381), 
    'scale_default' : 1.5, 
    'scale_syst' : 2.0, 
    'scale_pid' : 1.5, 
    'toystat' : 300000, 
    'controlstat' : 300000, 
    'nbootstrap' : 5
  }, 
  "e_V3ProbNNK" : {
    "sample" : "e21", 
    "var" : "e_V3ProbNNK", 
    "bins" : 30, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 1.5, 
    'scale_syst' : 2.0, 
    'scale_pid' : 1.5, 
    'toystat' : 300000, 
    'controlstat' : 300000, 
    'nbootstrap' : 5
  }, 
  "gamma_CL" : {
    "sample" : "gammaKst", 
    "var" : "gamma_CL", 
    "bins" : 30, 
    "transform_forward"  : "1.-(1.-x)**0.3", 
    "transform_backward" : "1.-(1.-x)**(1./0.3)", 
    'scale_default' : 1.0, 
    'scale_syst'    : None, 
    'scale_pid'     : 2.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "mu_V3ProbNNpi" : {
    "sample" : "mu", 
    "var" : "Mu_V3ProbNNpi", 
    "bins" : 100, 
    "transform_forward"  : "x**0.25", 
    "transform_backward" : "x**(1./0.25)", 
    'scale_default' : 0.1, 
    'scale_syst' : 0.15, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 5
  }, 
  "mu_V3ProbNNK" : {
    "sample" : "mu", 
    "var" : "Mu_V3ProbNNK", 
    "bins" : 100, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 0.1, 
    'scale_syst' : 0.15, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 5
  }, 
  "K_V3ProbNNmu" : {
    "sample" : "K", 
    "var" : "K_V3ProbNNmu", 
    "bins" : 100, 
#    "transform_forward"  : "x", 
#    "transform_backward" : "x", 
    "transform_forward"  : "1.-(1.-x**0.15)**0.2", 
    "transform_backward" : "1.-(1.-x**(1./0.2))**(1./0.15)", 
    'scale_default' : 0.6, 
    'scale_syst' : 0.9, 
    'scale_pid' : 1.0, 
    'toystat' : 10000000, 
    'controlstat' : 5000000, 
    'nbootstrap' : 5
  }, 
}
