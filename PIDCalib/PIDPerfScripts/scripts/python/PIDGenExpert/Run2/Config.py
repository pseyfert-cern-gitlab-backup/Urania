eosdir = "/eos/lhcb/wg/PID/PIDGen/Data/Run2"
eosrootdir = "root://eoslhcb.cern.ch/" + eosdir

tmpdir = "/tmp/poluekt/"

datasets = {
  'MagDown_2016'   : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision16/PIDCALIB.ROOT/00056408/0000/00056408_%8.8d_1.pidcalib.root", 182), 
  'MagUp_2016'     : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision16/PIDCALIB.ROOT/00056409/0000/00056409_%8.8d_1.pidcalib.root", 185), 
  'MagDown_2015'   : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision15/PIDCALIB.ROOT/00057802/0000/00057802_%8.8d_1.pidcalib.root", 87), 
  'MagUp_2015'     : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision15/PIDCALIB.ROOT/00057800/0000/00057800_%8.8d_1.pidcalib.root", 48), 
}

samples = {
  "p_Lam0_Brunel" : {
    'trees'   : ("Lam0_PTuple/DecayTree", "Lam0_PbarTuple/DecayTree", "Lam0_HPT_PTuple/DecayTree", "Lam0_HPT_PbarTuple/DecayTree", "Lam0_VHPT_PTuple/DecayTree", "Lam0_VHPT_PbarTuple/DecayTree"), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 
  "p_Lam0_LPT_Brunel" : {
    'trees'   : ("Lam0_PTuple/DecayTree", "Lam0_PbarTuple/DecayTree"), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 
  "p_Lam0_HPT_Brunel" : {
    'trees'   : ("Lam0_HPT_PTuple/DecayTree", "Lam0_HPT_PbarTuple/DecayTree"), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 
  "p_Lam0_VHPT_Brunel" : {
    'trees'   : ("Lam0_VHPT_PTuple/DecayTree", "Lam0_VHPT_PbarTuple/DecayTree"), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 
  "K_DSt_Brunel" : {
    'trees'   : ("DSt_KPTuple/DecayTree", "DSt_KMTuple/DecayTree"), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 
  "pi_DSt_Brunel" : {
    'trees'   : ("DSt_PiPTuple/DecayTree", "DSt_PiMTuple/DecayTree"), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 
  'mu_Jpsi_Brunel' : {
    'trees'   : ('Jpsi_MuPTuple/DecayTree', 'Jpsi_MuMTuple/DecayTree'), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 
  'e_BJpsi_Brunel' : {
    'trees'   : ('B_Jpsi_EPTuple/DecayTree', 'B_Jpsi_EMTuple/DecayTree'), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks", 
    'weight'  : "probe_sWeight"
  }, 

  "p_LbLcMu_Brunel" : {
    'datasets' : {
      'MagDown_2016'   : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision16/PIDCALIB.ROOT/00064795/0000/00064795_%8.8d_1.pidcalib.root", 156), 
      'MagUp_2016'     : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision16/PIDCALIB.ROOT/00064793/0000/00064793_%8.8d_1.pidcalib.root", 147), 
      'MagDown_2015'   : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision15/PIDCALIB.ROOT/00064785/0000/00064785_%8.8d_1.pidcalib.root", 79), 
      'MagUp_2015'     : ("/eos/lhcb/grid/prod/lhcb/LHCb/Collision15/PIDCALIB.ROOT/00064787/0000/00064787_%8.8d_1.pidcalib.root", 45), 
    }, 
    'trees'   : ("LbLcMu_PTuple/DecayTree", "LbLcMu_PbarTuple/DecayTree"), 
    'pt'      : "probe_Brunel_PT", 
    'eta'     : "probe_Brunel_ETA", 
    'ntracks' : "nTracks_Brunel", 
    'weight'  : "probe_sWeight"
  }, 

  "p_LbLcPi_Brunel" : {
    'datasets': {
                  "MagDown_2016" : "/eos/lhcb/wg/PID/PIDGen/Calibration/Run2/Proton/lcpi_splot_exp16_md.root", 
                  "MagUp_2016"   : "/eos/lhcb/wg/PID/PIDGen/Calibration/Run2/Proton/lcpi_splot_exp16_mu.root", 
                  "MagDown_2015" : "/eos/lhcb/wg/PID/PIDGen/Calibration/Run2/Proton/lcpi_splot_exp15_md.root", 
                  "MagUp_2015"   : "/eos/lhcb/wg/PID/PIDGen/Calibration/Run2/Proton/lcpi_splot_exp15_mu.root", 
                }, 
    'trees'   : ( "wdata",  ), 
    'pt'      : "lp_pt", 
    'eta'     : "lp_eta", 
    'ntracks' : "nTracks", 
    'weight'  : "sum_lcpi_sig_norm_sw"
  }, 
}

configs = {
  "p_MC15TuneV1_ProbNNp_Brunel" : {
    "sample"        :  "p_Lam0_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNp", 
    "bins"          :  50, 
    "gamma"         : -0.3, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
#  "p_LPT_MC15TuneV1_ProbNNp_Brunel" : {
#    "sample"        :  "p_Lam0_LPT_Brunel", 
#    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNp", 
#    "bins"          :  50, 
#    "gamma"         : -0.3, 
#    'scale_default' :  0.1, 
#    'scale_syst'    :  0.15, 
#    'scale_pid'     :  1.0, 
#    'toystat'       : 20000000, 
#    'controlstat'   :  1000000, 
#    'nbootstrap'    :  5
#  }, 
#  "p_LPT_HLT_MC15TuneV1_ProbNNp_Brunel" : {
#    "sample"        :  "p_Lam0_LPT_Brunel", 
#    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNp", 
#    "bins"          :  50, 
#    "gamma"         : -0.3, 
#    'scale_default' :  0.1, 
#    'scale_syst'    :  0.15, 
#    'scale_pid'     :  1.0, 
#    'toystat'       : 20000000, 
#    'controlstat'   :  1000000, 
#    'nbootstrap'    :  5
#  }, 
#  "p_HPT_MC15TuneV1_ProbNNp_Brunel" : {
#    "sample"        :  "p_Lam0_HPT_Brunel", 
#    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNp", 
#    "bins"          :  50, 
#    "gamma"         : -0.3, 
#    'scale_default' :  0.1, 
#    'scale_syst'    :  0.15, 
#    'scale_pid'     :  1.0, 
#    'toystat'       : 20000000, 
#    'controlstat'   :  1000000, 
#    'nbootstrap'    :  5
#  }, 
  "p_LbLcMu_MC15TuneV1_ProbNNp_Brunel" : {
    "sample"        :  "p_LbLcMu_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNp", 
    "bins"          :  50, 
    "gamma"         : -0.3, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "p_LbLcPi_MC12TuneV2gt0.05_MC15TuneV1_ProbNNp_Brunel" : {
    "sample"        :  "p_LbLcPi_Brunel", 
    "var"           :  "lp_MC15TuneV1_ProbNNp", 
    "cut"           : "i.lp_MC12TuneV2_ProbNNp>0.05", 
    "bins"          :  50, 
    "gamma"         : -0.25, 
    'scale_default' :  0.75, 
    'scale_syst'    :  1., 
    'scale_pid'     :  1.2, 
    'toystat'       :  2000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "p_LbLcPi_MC15TuneV1_ProbNNp_Brunel" : {
    "sample"        :  "p_LbLcPi_Brunel", 
    "var"           :  "lp_MC15TuneV1_ProbNNp", 
    "bins"          :  50, 
    "gamma"         : -0.25, 
    'scale_default' :  0.75, 
    'scale_syst'    :  1., 
    'scale_pid'     :  1.2, 
    'toystat'       :  2000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "p_MC15TuneV1_ProbNNK_Brunel" : {
    "sample"        :  "p_Lam0_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNk", 
    "bins"          :  50, 
    "gamma"         :  0.3, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "p_MC15TuneV1_ProbNNpi_Brunel" : {
    "sample"        :  "p_Lam0_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNpi", 
    "bins"          :  50, 
    "gamma"         :  0.15, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "K_MC15TuneV1_ProbNNK_Brunel" : {
    "sample"        :  "K_DSt_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNk", 
    "bins"          :  100, 
    "gamma"         : -0.2, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "K_MC15TuneV1_ProbNNpi_Brunel" : {
    "sample"        :  "K_DSt_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNpi", 
    "bins"          :  100, 
    "gamma"         :  0.2, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "K_MC15TuneV1_ProbNNp_Brunel" : {
    "sample"        :  "K_DSt_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNp", 
    "bins"          :  100, 
    "gamma"         :  0.3, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "pi_MC15TuneV1_ProbNNpi_Brunel" : {
    "sample"        :  "pi_DSt_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNpi", 
    "bins"          :  100, 
    "gamma"         : -0.2, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "pi_MC15TuneV1_ProbNNK_Brunel" : {
    "sample"        :  "pi_DSt_Brunel",
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNk",
    "bins"          :  100,
    "gamma"         :  0.05,
    'scale_default' :  0.1,
    'scale_syst'    :  0.15,
    'scale_pid'     :  1.0,
    'toystat'       : 20000000,
    'controlstat'   :  1000000,
    'nbootstrap'    :  5
  },
  "pi_MC15TuneV1_ProbNNp_Brunel" : {
    "sample"        :  "pi_DSt_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNp", 
    "bins"          :  100, 
    "gamma"         :  0.15, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "pi_CombDLLK_Brunel" : {
    "sample"        : "pi_DSt_Brunel", 
    "var"           : "probe_Brunel_PIDK", 
    "bins"          : 100, 
    "gamma"         : 1., 
    'scale_default' : 0.1, 
    'scale_syst'    : 0.15, 
    'scale_pid'     : 1.0,
    'limits'        : (-150., 50.), 
    'toystat'       : 10000000, 
    'controlstat'   : 5000000, 
    'nbootstrap'    : 5
  },
  "pi_CombDLLp_Brunel" : {
    "sample"        :  "pi_DSt_Brunel", 
    "var"           :  "probe_Brunel_PIDp", 
    "bins"          :  100, 
    "gamma"         :  1., 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'limits'        : (-150., 70),
    'toystat'       : 10000000, 
    'controlstat'   : 5000000, 
    'nbootstrap'    : 5
  },
  "p_CombDLLp_Brunel" : {
    "sample"        : "p_Lam0_Brunel", 
    "var"           : "probe_Brunel_PIDp", 
    "bins"          : 100, 
    "gamma"         : 1., 
    'scale_default' : 0.1, 
    'scale_syst'    : 0.15, 
    'scale_pid'     : 1.0, 
    'limits'        : (-30., 120), 
    'toystat'       : 20000000, 
    'controlstat'   : 1000000, 
    'nbootstrap'    : 5
  }, 
#  "p_LPT_HLT_CombDLLp_Brunel" : {
#    "sample"        : "p_Lam0_LPT_Brunel", 
#    "cut"           : "i.probe_MINIPCHI2>400", 
#    "var"           : "probe_Brunel_PIDp", 
#    "bins"          : 100, 
#    "gamma"         : 1., 
#    'scale_default' : 0.1, 
#    'scale_syst'    : 0.15, 
#    'scale_pid'     : 1.0, 
#    'limits'        : (-30., 120), 
#    'toystat'       : 20000000, 
#    'controlstat'   : 1000000, 
#    'nbootstrap'    : 5
#  }, 
#  "p_LPT_LLT_CombDLLp_Brunel" : {
#    "sample"        : "p_Lam0_LPT_Brunel", 
#    "cut"           : "i.probe_MINIPCHI2<100", 
#    "var"           : "probe_Brunel_PIDp", 
#    "bins"          : 100, 
#    "gamma"         : 1., 
#    'scale_default' : 0.1, 
#    'scale_syst'    : 0.15, 
#    'scale_pid'     : 1.0, 
#    'limits'        : (-30., 120), 
#    'toystat'       : 20000000, 
#    'controlstat'   : 1000000, 
#    'nbootstrap'    : 5
#  }, 
  "p_CombDLLK_Brunel" : {
    "sample"        : "p_Lam0_Brunel", 
    "var"           : "probe_Brunel_PIDK", 
    "bins"          : 100, 
    "gamma"         : 1., 
    'scale_default' : 0.1, 
    'scale_syst'    : 0.15, 
    'scale_pid'     : 1.0, 
    'limits'        : (-50., 60), 
    'toystat'       : 20000000, 
    'controlstat'   : 1000000, 
    'nbootstrap'    : 5
  }, 
  "K_CombDLLK_Brunel" : {
    "sample"        :  "K_DSt_Brunel", 
    "var"           :  "probe_Brunel_PIDK", 
    "bins"          :  100, 
    "gamma"         :  1., 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'limits'        : (-50., 150), 
    'toystat'       : 10000000, 
    'controlstat'   : 5000000, 
    'nbootstrap'    : 5
  }, 
  "K_CombDLLp_Brunel" : {
    "sample"        :  "K_DSt_Brunel", 
    "var"           :  "probe_Brunel_PIDp", 
    "bins"          :  100, 
    "gamma"         :  1., 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'limits'        : (-150., 100), 
    'toystat'       : 10000000, 
    'controlstat'   : 5000000, 
    'nbootstrap'    : 5
  }, 
  "mu_MC15TuneV1_ProbNNmu_Brunel" : {
    "sample"        :  "mu_Jpsi_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNmu", 
    "bins"          :  100, 
    "gamma"         : -0.2, 
    'scale_default' :  0.1, 
    'scale_syst'    :  0.15, 
    'scale_pid'     :  1.0, 
    'toystat'       : 20000000, 
    'controlstat'   :  1000000, 
    'nbootstrap'    :  5
  }, 
  "e_MC15TuneV1_ProbNNe_Brunel" : {
    "sample"        :  "e_BJpsi_Brunel", 
    "var"           :  "probe_Brunel_MC15TuneV1_ProbNNe", 
    "bins"          :  30, 
    "gamma"         : -0.2, 
    'scale_default' :  1.5, 
    'scale_syst'    :  2.0, 
    'scale_pid'     :  1.5, 
    'toystat'       :  300000, 
    'controlstat'   :  300000, 
    'nbootstrap'    :  5
  }, 
  "e_CombDLLe_Brunel" : {
    "sample"        :  "e_BJpsi_Brunel", 
    "var"           :  "probe_Brunel_PIDe", 
    "bins"          :  30, 
    "gamma"         :  1., 
    'scale_default' :  1.5, 
    'scale_syst'    :  2.0, 
    'scale_pid'     :  1.5, 
    'limits'        : (-20., 20), 
    'toystat'       : 300000, 
    'controlstat'   : 300000, 
    'nbootstrap'    : 5
  }, 
#  "p_MC12TuneV2_ProbNNp_Brunel" : {
#    "sample"        :  "p_Lam0_Brunel", 
#    "var"           :  "probe_Brunel_MC12TuneV2_ProbNNp", 
#    "bins"          :  50, 
#    "gamma"         : -0.3, 
#    'scale_default' :  0.1, 
#    'scale_syst'    :  0.15, 
#    'scale_pid'     :  1.0, 
#    'toystat'       : 20000000, 
#    'controlstat'   :  1000000, 
#    'nbootstrap'    :  5
#  }, 
}
