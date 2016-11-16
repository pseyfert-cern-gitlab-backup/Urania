/////////////////////////////////////////////////////
//                                                 //
// Definition of the variables to generate the BDT //
// for the Ks0 -> mu+ mu- analysis                 //
//                                                 //
// Author: Miguel Ramos Pernas                     //
// e-mail: miguel.ramos.pernas@cern.ch             //
//                                                 //
/////////////////////////////////////////////////////

#include <string>
#include <vector>

// --------------------------------------------------------------------------------
// These are the main variables to be used. The VARSET variables are attached
// later.
const std::vector<std::string> MAIN_VARIABLES = { "KS0_LV0",
						  "KS0_IPCHI2_OWNPV",
						  "KS0_DOCA",
						  "KS0_ENDVERTEX_CHI2",
						  "KS0_SmallestDeltaChi2OneTrack",
						  "MinMu_IPCHI2_OWNPV"
};
const std::vector<std::string> VARSET_0 = { "KS0_PT", "KS0_TAU", "KS0_isInMatter" };
const std::vector<std::string> VARSET_1 = { "KS0_PT", "KS0_TAU", "KS0_isInMatter", "KS0_ENDVERTEX_Z" };
const std::vector<std::string> VARSET_2 = { "KS0_PT" , "KS0_ENDVERTEX_X", "KS0_ENDVERTEX_Y", "KS0_ENDVERTEX_Z" };
const std::vector<std::string> VARSET_3 = { "KS0_TAU", "KS0_ENDVERTEX_X", "KS0_ENDVERTEX_Y", "KS0_ENDVERTEX_Z" };

const std::vector<std::string> SPECTATORVARS = { "KS0_M" };

const std::map<std::string, std::string> VARTITLES = {
  {"KS0_LV0"                      , "(K_{S}^{0})_{LV0}"},
  {"KS0_IPCHI2_OWNPV"             , "(K_{S}^{0})_{IP#chi^{2}}"},
  {"KS0_DOCA"                     , "(K_{S}^{0})_{DOCA}"},
  {"KS0_ENDVERTEX_CHI2"           , "(K_{S}^{0})_{SV#chi^{2}}"},
  {"KS0_SmallestDeltaChi2OneTrack", "(K_{S}^{0})_{Small#Delta#chi^{2}}"},
  {"MinMu_IPCHI2_OWNPV"           , "(#mu)_{MinIP#chi^{2}}"},
  {"KS0_PT"                       , "(K_{S}^{0})_{PT}"},
  {"KS0_TAU"                      , "(K_{S}^{0})_{#tau}"},
  {"KS0_isInMatter"               , "(K_{S}^{0})_{isInMatter}"},
  {"KS0_ENDVERTEX_X"              , "(K_{S}^{0})_{SVX}"},
  {"KS0_ENDVERTEX_Y"              , "(K_{S}^{0})_{SVY}"},
  {"KS0_ENDVERTEX_Z"              , "(K_{S}^{0})_{SVZ}"},
  {"KS0_M"                        , "(K_{S}^{0})_{M}"}
};

void AddGLandVarSetFlags( std::string &name, const size_t &glstatus, const size_t &varset ) {
  
  // If the GL is enabled, the corresponding flag is added
  if ( glstatus ) {
    if ( glstatus == 2 )
      name += "_GLall";
    else
      name += "_GLhalf";
  }
  else
    name += "_NoGL";
  
  // Depending on the variable set used, the corresponding flag is set
  name += "_VarSet" + std::to_string( varset );
}
