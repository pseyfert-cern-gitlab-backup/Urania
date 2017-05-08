eosdir = "/eos/lhcb/wg/PID/PIDGen/MC/Run1Sim08"
eosrootdir = "root://eoslhcb.cern.ch/" + eosdir

datadir = "../data/"

tmpdir = "/tmp/poluekt/"

samples = {
  "K" : {
    'datasets' : {
      'MagDown_2012' : "tuple_dstar_mc12_magdown.root", 
      'MagUp_2012' : "tuple_dstar_mc12_magup.root", 
      'MagDown_2011' : "tuple_dstar_mc11_magdown.root", 
      'MagUp_2011' : "tuple_dstar_mc11_magup.root", 
    }, 
    'dir'     : "dstar", 
    'tree'    : "dstar", 
    'pt'      : "dk_PT", 
    'eta'     : "dk_ETA", 
    'ntracks' : "nTracks", 
  }, 
  "pi" : {
    'datasets' : {
      'MagDown_2012' : "tuple_dstar_mc12_magdown.root", 
      'MagUp_2012' : "tuple_dstar_mc12_magup.root", 
      'MagDown_2011' : "tuple_dstar_mc11_magdown.root", 
      'MagUp_2011' : "tuple_dstar_mc11_magup.root", 
    }, 
    'dir'     : "dstar", 
    'tree'    : "dstar", 
    'pt'      : "dpi_PT", 
    'eta'     : "dpi_ETA", 
    'ntracks' : "nTracks", 
  }, 
  "p" : {
    'datasets' : {
      'MagDown_2012' : "tuple_lcmu_mc12_magdown.root", 
      'MagUp_2012' : "tuple_lcmu_mc12_magup.root", 
      'MagDown_2011' : "tuple_lcmu_mc11_magdown.root", 
      'MagUp_2011' : "tuple_lcmu_mc11_magup.root", 
    }, 
    'dir'     : "lc", 
    'tree'    : "nt", 
    'pt'      : "p_PT", 
    'eta'     : "p_ETA", 
    'ntracks' : "nTracks", 
  }, 
  "e" : {
    'datasets' : {
      'MagDown_2012' : "tuple_jpsi2ee_mc12_magdown.root", 
      'MagUp_2012' : "tuple_jpsi2ee_mc12_magup.root", 
      'MagDown_2011' : "tuple_jpsi2ee_mc11_magdown.root", 
      'MagUp_2011' : "tuple_jpsi2ee_mc11_magup.root", 
    }, 
    'dir'     : "", 
    'tree'    : "bu2kjpsi2ee", 
    'pt'      : "pt", 
    'eta'     : "eta", 
    'ntracks' : "ntr", 
  
  }
}

configs = {
  "K_CombDLLK" : {
    "sample" : "K", 
    "var" : "dk_PIDK", 
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
  "K_V2ProbNNK" : {
    "sample" : "K", 
    "var" : "dk_V2ProbNNK", 
    "bins" : 30, 
    "transform_forward"  : "1.-(1.-x)**0.15", 
    "transform_backward" : "(1.-(1.-x)**(1./0.15))", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "K_V2ProbNNpi" : {
    "sample" : "K", 
    "var" : "dk_V2ProbNNpi", 
    "bins" : 30, 
    "transform_forward"  : "x**0.2", 
    "transform_backward" : "x**(1./0.2)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "K_V3ProbNNK" : {
    "sample" : "K", 
    "var" : "dk_V3ProbNNK", 
    "bins" : 30, 
    "transform_forward"  : "1.-(1.-x)**0.15", 
    "transform_backward" : "(1.-(1.-x)**(1./0.15))", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "K_V3ProbNNpi" : {
    "sample" : "K", 
    "var" : "dk_V3ProbNNpi", 
    "bins" : 30, 
    "transform_forward"  : "x**0.2", 
    "transform_backward" : "x**(1./0.2)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "K_V3ProbNNp" : {
    "sample" : "K", 
    "var" : "dk_V3ProbNNp", 
    "bins" : 30, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 

  "pi_CombDLLK" : {
    "sample" : "pi", 
    "var" : "dpi_PIDK", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'limits' : (-100., 20), 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "pi_V2ProbNNpi" : {
    "sample" : "pi", 
    "var" : "dpi_V2ProbNNpi", 
    "bins" : 30, 
    "transform_forward"  : "1.-(1.-x)**0.3", 
    "transform_backward" : "(1.-(1.-x)**(1./0.3))", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "pi_V2ProbNNK" : {
    "sample" : "pi", 
    "var" : "dpi_V2ProbNNK", 
    "bins" : 30, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "pi_V3ProbNNpi" : {
    "sample" : "pi", 
    "var" : "dpi_V3ProbNNpi", 
    "bins" : 30, 
    "transform_forward"  : "1.-(1.-x)**0.3", 
    "transform_backward" : "(1.-(1.-x)**(1./0.3))", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "pi_V3ProbNNK" : {
    "sample" : "pi", 
    "var" : "dpi_V3ProbNNK", 
    "bins" : 30, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "pi_V3ProbNNp" : {
    "sample" : "pi", 
    "var" : "dpi_V3ProbNNp", 
    "bins" : 30, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 

  "p_V3ProbNNp" : {
    "sample" : "p", 
    "var" : "p_V3ProbNNp", 
    "bins" : 30, 
    "transform_forward"  : "1.-sqrt(1.-x)", 
    "transform_backward" : "(1.-(1.-x)*(1.-x))", 
    'scale_default' : 1.0, 
    'scale_syst'    : None, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "p_V2ProbNNp" : {
    "sample" : "p", 
    "var" : "p_V2ProbNNp", 
    "bins" : 30, 
    "transform_forward"  : "1.-sqrt(1.-x)", 
    "transform_backward" : "(1.-(1.-x)*(1.-x))", 
    'scale_default' : 1.0, 
    'scale_syst'    : None, 
    'scale_pid'     : 1.0, 
    'toystat'       : 1000000, 
    'controlstat'   : 500000, 
    'nbootstrap'    : 0
  }, 
  "p_V3ProbNNpi" : {
    "sample" : "p", 
    "var" : "p_V3ProbNNpi", 
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
    "var" : "p_V3ProbNNK", 
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
    "var" : "p_PIDK", 
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
    "var" : "p_PIDp", 
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
    "var" : "dk_PIDp", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'limits' : (-100., 70), 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "pi_CombDLLp" : {
    "sample" : "pi", 
    "var" : "dpi_PIDp", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'limits' : (-120., 30), 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 

  "p_V2ProbNNpi" : {
    "sample" : "p", 
    "var" : "p_V2ProbNNpi", 
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
    "var" : "p_V2ProbNNK", 
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
  "pi_V2ProbNNp" : {
    "sample" : "pi", 
    "var" : "dpi_V2ProbNNp", 
    "bins" : 30, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "K_V2ProbNNp" : {
    "sample" : "K", 
    "var" : "dk_V2ProbNNp", 
    "bins" : 30, 
    "transform_forward"  : "x**0.15", 
    "transform_backward" : "x**(1./0.15)", 
    'scale_default' : 1.0, 
    'scale_syst' : None, 
    'scale_pid' : 1.0, 
    'toystat' : 1000000, 
    'controlstat' : 500000, 
    'nbootstrap' : 0
  }, 
  "e_CombDLLe" : {
    "sample" : "e", 
    "var" : "CombDLLe", 
    "transform_forward"  : "x", 
    "transform_backward" : "x", 
    "bins" : 30, 
    "limits" : (-20., 20.), 
    'scale_default' : 2.0, 
    'scale_syst' : 2.5, 
    'scale_pid' : 2.0, 
    'toystat' : 300000, 
    'controlstat' : 300000, 
    'nbootstrap' : 0
  }, 
  "e_V3ProbNNe" : {
    "sample" : "e",
    "var" : "V3ProbNNe",
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
}
