#include <iostream>
#include <cstdio>

TCut veto(std::string invmass){


  std::string E13Sq_pipiKS = "((sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_pipiKS = "((sqrt(139.57018*139.57018 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(139.57018*139.57018 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_pipiKS = "((sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(139.57018*139.57018 + h2_P*h2_P))*(sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(139.57018*139.57018 + h2_P*h2_P)))";

  std::string E13Sq_KpiKS  = "((sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_KpiKS  = "((sqrt(139.57018*139.57018 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(139.57018*139.57018 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_KpiKS  = "((sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(139.57018*139.57018 + h2_P*h2_P))*(sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(139.57018*139.57018 + h2_P*h2_P)))";

  std::string E13Sq_piKKS  = "((sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_piKKS  = "((sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_piKKS  = "((sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(139.57018*139.57018 + h1_P*h1_P))*(sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(139.57018*139.57018 + h1_P*h1_P)))";

  std::string E13Sq_KKKS   = "((sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_KKKS   = "((sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_KKKS   = "((sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(493.677*493.677 + h2_P*h2_P))*(sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(493.677*493.677 + h2_P*h2_P)))";

  std::string E13Sq_ppiKS  = "((sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_ppiKS  = "((sqrt(139.57018*139.57018 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(139.57018*139.57018 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_ppiKS  = "((sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(139.57018*139.57018 + h2_P*h2_P))*(sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(139.57018*139.57018 + h2_P*h2_P)))";

  std::string E13Sq_pipKS  = "((sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(139.57018*139.57018 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_pipKS  = "((sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_pipKS  = "((sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(139.57018*139.57018 + h1_P*h1_P))*(sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(139.57018*139.57018 + h1_P*h1_P)))";

  std::string E13Sq_pKKS  = "((sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_pKKS  = "((sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(493.677*493.677 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_pKKS  = "((sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(493.677*493.677 + h2_P*h2_P))*(sqrt(938.272046*938.272046 + h1_P*h1_P) + sqrt(493.677*493.677 + h2_P*h2_P)))";


  std::string E13Sq_KpKS  = "((sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(493.677*493.677 + h1_P*h1_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E23Sq_KpKS  = "((sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P))*(sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(KS_M*KS_M + KS_P*KS_P)))";
  std::string E12Sq_KpKS  = "((sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(493.677*493.677 + h1_P*h1_P))*(sqrt(938.272046*938.272046 + h2_P*h2_P) + sqrt(493.677*493.677 + h1_P*h1_P)))";

  std::string P13Sq = "((h1_PX+KS_PX)*(h1_PX+KS_PX)+(h1_PY+KS_PY)*(h1_PY+KS_PY)+(h1_PZ+KS_PZ)*(h1_PZ+KS_PZ))";
  std::string P23Sq = "((h2_PX+KS_PX)*(h2_PX+KS_PX)+(h2_PY+KS_PY)*(h2_PY+KS_PY)+(h2_PZ+KS_PZ)*(h2_PZ+KS_PZ))";
  std::string P12Sq = "((h1_PX+h2_PX)*(h1_PX+h2_PX)+(h1_PY+h2_PY)*(h1_PY+h2_PY)+(h1_PZ+h2_PZ)*(h1_PZ+h2_PZ))";


  std::string m13_pipiKS = "sqrt("+E13Sq_pipiKS+"-"+P13Sq+")";
  std::string m23_pipiKS = "sqrt("+E23Sq_pipiKS+"-"+P23Sq+")";
  std::string m12_pipiKS = "sqrt("+E12Sq_pipiKS+"-"+P12Sq+")";

  std::string m13_KpiKS = "sqrt("+E13Sq_KpiKS+"-"+P13Sq+")";
  std::string m23_KpiKS = "sqrt("+E23Sq_KpiKS+"-"+P23Sq+")";
  std::string m12_KpiKS = "sqrt("+E12Sq_KpiKS+"-"+P12Sq+")";

  std::string m13_piKKS = "sqrt("+E13Sq_piKKS+"-"+P13Sq+")";
  std::string m23_piKKS = "sqrt("+E23Sq_piKKS+"-"+P23Sq+")";
  std::string m12_piKKS = "sqrt("+E12Sq_piKKS+"-"+P12Sq+")";

  std::string m13_KKKS = "sqrt("+E13Sq_KKKS+"-"+P13Sq+")";
  std::string m23_KKKS = "sqrt("+E23Sq_KKKS+"-"+P23Sq+")";
  std::string m12_KKKS = "sqrt("+E12Sq_KKKS+"-"+P12Sq+")";

  std::string m13_ppiKS = "sqrt("+E13Sq_ppiKS+"-"+P13Sq+")";
  std::string m23_ppiKS = "sqrt("+E23Sq_ppiKS+"-"+P23Sq+")";
  std::string m12_ppiKS = "sqrt("+E12Sq_ppiKS+"-"+P12Sq+")";

  std::string m13_pipKS = "sqrt("+E13Sq_pipKS+"-"+P13Sq+")";
  std::string m23_pipKS = "sqrt("+E23Sq_pipKS+"-"+P23Sq+")";
  std::string m12_pipKS = "sqrt("+E12Sq_pipKS+"-"+P12Sq+")";

  std::string m13_pKKS = "sqrt("+E13Sq_pKKS+"-"+P13Sq+")";
  std::string m23_pKKS = "sqrt("+E23Sq_pKKS+"-"+P23Sq+")";
  std::string m12_pKKS = "sqrt("+E12Sq_pKKS+"-"+P12Sq+")";

  std::string m13_KpKS = "sqrt("+E13Sq_KpKS+"-"+P13Sq+")";
  std::string m23_KpKS = "sqrt("+E23Sq_KpKS+"-"+P23Sq+")";
  std::string m12_KpKS = "sqrt("+E12Sq_KpKS+"-"+P12Sq+")";

  TCut cut_pipiKS = "";
  TCut cut_KpiKS = "";
  TCut cut_piKKS = "";
  TCut cut_KKKS = "";
  TCut cut_ppiKS = "";
  TCut cut_pipKS = "";
  TCut cut_pKKS = "";
  TCut cut_KpKS = "";
  TCut Vetoes = "";

  std::string veto1 = "30";
  std::string veto2 = "48";

  TCut vetoDp_pipiKS = std::string("abs("+m13_pipiKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDp_KpiKS = std::string("abs("+m13_KpiKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDp_piKKS = std::string("abs("+m13_piKKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDp_KKKS = std::string("abs("+m13_KKKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDp_ppiKS = std::string("abs("+m13_ppiKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDp_pipKS = std::string("abs("+m13_pipKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDp_pKKS = std::string("abs("+m13_pKKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDp_KpKS = std::string("abs("+m13_KpKS+"-1869.61) >"+veto1).c_str();

  TCut vetoDm_pipiKS = std::string("abs("+m23_pipiKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDm_KpiKS = std::string("abs("+m23_KpiKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDm_piKKS = std::string("abs("+m23_piKKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDm_KKKS = std::string("abs("+m23_KKKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDm_ppiKS = std::string("abs("+m23_ppiKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDm_pipKS = std::string("abs("+m23_pipKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDm_pKKS = std::string("abs("+m23_pKKS+"-1869.61) >"+veto1).c_str();
  TCut vetoDm_KpKS = std::string("abs("+m23_KpKS+"-1869.61) >"+veto1).c_str();

  TCut vetoD0_pipiKS = std::string("abs("+m12_pipiKS+"-1864.86) >"+veto1).c_str();
  TCut vetoD0_KpiKS = std::string("abs("+m12_KpiKS+"-1864.86) >"+veto1).c_str();
  TCut vetoD0_piKKS = std::string("abs("+m12_piKKS+"-1864.86) >"+veto1).c_str();
  TCut vetoD0_KKKS = std::string("abs("+m12_KKKS+"-1864.86) >"+veto1).c_str();
  TCut vetoD0_ppiKS = std::string("abs("+m12_ppiKS+"-1864.86) >"+veto1).c_str();
  TCut vetoD0_pipKS = std::string("abs("+m12_pipKS+"-1864.86) >"+veto1).c_str();
  TCut vetoD0_pKKS = std::string("abs("+m12_pKKS+"-1864.86) >"+veto1).c_str();
  TCut vetoD0_KpKS = std::string("abs("+m12_KpKS+"-1864.86) >"+veto1).c_str();

  TCut vetoDsp_pipiKS = std::string("abs("+m13_pipiKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsp_KpiKS = std::string("abs("+m13_KpiKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsp_piKKS = std::string("abs("+m13_piKKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsp_KKKS = std::string("abs("+m13_KKKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsp_ppiKS = std::string("abs("+m13_ppiKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsp_pipKS = std::string("abs("+m13_pipKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsp_pKKS = std::string("abs("+m13_pKKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsp_KpKS = std::string("abs("+m13_KpKS+"-1968.49) >"+veto1).c_str();

  TCut vetoDsm_pipiKS = std::string("abs("+m23_pipiKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsm_KpiKS = std::string("abs("+m23_KpiKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsm_piKKS = std::string("abs("+m23_piKKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsm_KKKS = std::string("abs("+m23_KKKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsm_ppiKS = std::string("abs("+m23_ppiKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsm_pipKS = std::string("abs("+m23_pipKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsm_pKKS = std::string("abs("+m23_pKKS+"-1968.49) >"+veto1).c_str();
  TCut vetoDsm_KpKS = std::string("abs("+m23_KpKS+"-1968.49) >"+veto1).c_str();

  TCut vetoJpsi_pipiKS = std::string("abs("+m12_pipiKS+"-3096.92) >"+veto2).c_str();
  TCut vetoJpsi_KpiKS = std::string("abs("+m12_KpiKS+"-3096.92) >"+veto2).c_str();
  TCut vetoJpsi_piKKS = std::string("abs("+m12_piKKS+"-3096.92) >"+veto2).c_str();
  TCut vetoJpsi_KKKS = std::string("abs("+m12_KKKS+"-3096.92) >"+veto2).c_str();
  TCut vetoJpsi_ppiKS = std::string("abs("+m12_ppiKS+"-3096.92) >"+veto2).c_str();
  TCut vetoJpsi_pipKS = std::string("abs("+m12_pipKS+"-3096.92) >"+veto2).c_str();
  TCut vetoJpsi_pKKS = std::string("abs("+m12_pKKS+"-3096.92) >"+veto2).c_str();
  TCut vetoJpsi_KpKS = std::string("abs("+m12_KpKS+"-3096.92) >"+veto2).c_str();

  TCut vetoChic0_pipiKS = std::string("abs("+m12_pipiKS+"-3414.75) >"+veto2).c_str();
  TCut vetoChic0_KpiKS = std::string("abs("+m12_KpiKS+"-3414.75) >"+veto2).c_str();
  TCut vetoChic0_piKKS = std::string("abs("+m12_piKKS+"-3414.75) >"+veto2).c_str();
  TCut vetoChic0_KKKS = std::string("abs("+m12_KKKS+"-3414.75) >"+veto2).c_str();
  TCut vetoChic0_ppiKS = std::string("abs("+m12_ppiKS+"-3414.75) >"+veto2).c_str();
  TCut vetoChic0_pipKS = std::string("abs("+m12_pipKS+"-3414.75) >"+veto2).c_str();
  TCut vetoChic0_pKKS = std::string("abs("+m12_pKKS+"-3414.75) >"+veto2).c_str();
  TCut vetoChic0_KpKS = std::string("abs("+m12_KpKS+"-3414.75) >"+veto2).c_str();

  TCut vetoLcp_pipiKS = std::string("abs("+m13_pipiKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcp_KpiKS = std::string("abs("+m13_KpiKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcp_piKKS = std::string("abs("+m13_piKKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcp_KKKS = std::string("abs("+m13_KKKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcp_ppiKS = std::string("abs("+m13_ppiKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcp_pipKS = std::string("abs("+m13_pipKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcp_pKKS = std::string("abs("+m13_pKKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcp_KpKS = std::string("abs("+m13_KpKS+"-2286.46) >"+veto1).c_str();

  TCut vetoLcm_pipiKS = std::string("abs("+m23_pipiKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcm_KpiKS = std::string("abs("+m23_KpiKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcm_piKKS = std::string("abs("+m23_piKKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcm_KKKS = std::string("abs("+m23_KKKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcm_ppiKS = std::string("abs("+m23_ppiKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcm_pipKS = std::string("abs("+m23_pipKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcm_pKKS = std::string("abs("+m23_pKKS+"-2286.46) >"+veto1).c_str();
  TCut vetoLcm_KpKS = std::string("abs("+m23_KpKS+"-2286.46) >"+veto1).c_str();

  ////////////////////////////////                                                                                                                                                                                                           
  ///Applying vetoes//////////////                                                                                                                                                                                                           
  ////////////////////////////////                                                                                                                                                                                                           

  if(invmass == "pipi"){
    cut_KpiKS = vetoDp_pipiKS + vetoDm_pipiKS + vetoDsp_pipiKS + vetoDsm_pipiKS +vetoJpsi_pipiKS + vetoChic0_pipiKS;
    cut_piKKS = vetoDp_pipiKS + vetoDm_pipiKS + vetoDsp_pipiKS + vetoDsm_pipiKS +vetoJpsi_pipiKS + vetoChic0_pipiKS;
    cut_ppiKS = cut_KpiKS+vetoD0_KpiKS+vetoD0_piKKS+vetoDsp_KpiKS+vetoDsm_piKKS;
    cut_pipKS = cut_KpiKS+vetoD0_KpiKS+vetoD0_piKKS+vetoDsp_KpiKS+vetoDsm_piKKS;
    Vetoes   = cut_ppiKS+vetoLcp_ppiKS+vetoLcm_pipKS;
  }
  else if(invmass == "KK"){
    cut_KpiKS = vetoDp_KKKS + vetoDm_KKKS + vetoDsm_KKKS + vetoDsp_KKKS + vetoDsm_KKKS + vetoD0_KKKS + vetoJpsi_KKKS+vetoChic0_KKKS;
    cut_piKKS = vetoDp_KKKS + vetoDm_KKKS + vetoDsm_KKKS + vetoDsp_KKKS + vetoDsm_KKKS + vetoD0_KKKS + vetoJpsi_KKKS+vetoChic0_KKKS;
    cut_pKKS  = cut_piKKS+vetoDp_piKKS+vetoDm_KpiKS+vetoD0_piKKS+vetoD0_KpiKS;
    cut_KpKS  = cut_piKKS+vetoDp_piKKS+vetoDm_KpiKS+vetoD0_piKKS+vetoD0_KpiKS;
    Vetoes   = cut_pKKS+vetoLcp_pKKS+vetoLcm_KpKS;
  }
  else if(invmass == "Kpi" || invmass == "piK"){
    cut_ppiKS = vetoDp_piKKS+vetoDp_KpiKS+vetoDm_KpiKS+vetoDm_piKKS+vetoDsp_piKKS+vetoDsp_KpiKS+vetoDsm_KpiKS+vetoDsm_piKKS+vetoD0_piKKS+vetoD0_KpiKS;
    cut_pipKS = vetoDp_piKKS+vetoDp_KpiKS+vetoDm_KpiKS+vetoDm_piKKS+vetoDsp_piKKS+vetoDsp_KpiKS+vetoDsm_KpiKS+vetoDsm_piKKS+vetoD0_piKKS+vetoD0_KpiKS;
    cut_pKKS  = vetoDp_piKKS+vetoDp_KpiKS+vetoDm_KpiKS+vetoDm_piKKS+vetoDsp_piKKS+vetoDsp_KpiKS+vetoDsm_KpiKS+vetoDsm_piKKS+vetoD0_piKKS+vetoD0_KpiKS;
    cut_KpKS  = vetoDp_piKKS+vetoDp_KpiKS+vetoDm_KpiKS+vetoDm_piKKS+vetoDsp_piKKS+vetoDsp_KpiKS+vetoDsm_KpiKS+vetoDsm_piKKS+vetoD0_piKKS+vetoD0_KpiKS;
    Vetoes   = cut_pKKS+vetoLcp_pKKS+vetoLcm_KpKS;
  }


  return Vetoes;
}