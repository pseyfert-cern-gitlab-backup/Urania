#include <cstdlib>
#include <sstream>

namespace Constraints{
  typedef std::vector<std::string>::iterator stringIter;
  double alpha0_min =   0.;
  double alpha0_max =  10.;
  double alpha1_min = -10.;
  double alpha1_max =   0.;
  double alpha1oAlpha0_min = -10.;
  double alpha1oAlpha0_max =   0.;
  double n0_min     =   0.;
  double n0_max     =  10.;
  double n1_min     =   0.;
  double n1_max     =  10.;
  double n1oN0_min     =   0.;
  double n1oN0_max     =  10.;

  //Helpers functions
  bool isRecognized(std::string constraints)
  {
    if (constraints == "2011")
      return true;
    else if (constraints == "dummy")
      return true;
    return false;
  }
  bool finds(std::vector<std::string> vars, std::string var)
  {
    for (stringIter it = vars.begin() ; it != vars.end() ; ++it)
      if ((*it) == var)
	return true;
    return false;
  }
  std::string itoa(int i)
  {
    std::stringstream ss;
    ss << i;
    return ss.str();
  }

  //Binds the piK mode to Kpi. Used in apply functions
  void bindPiK(V0hhFit::SimultaneousFitter &fitter, std::vector<std::string> years, std::vector<std::string> modes, std::vector<std::string> KS, std::vector<std::string> vars)
  {
    for (stringIter itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
      if ((*itModes).find("piK") != std::string::npos)
	for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end() ; ++itKS)
	    for (stringIter itVars = vars.begin() ; itVars != vars.end() ; ++itVars)
	      {
		if ((*itModes).find("Bs") != std::string::npos)
		  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str(),"@0",("Bs2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str());      
		else
		  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str(),"@0",("Bd2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str());      
	      }
  }
  //===================================================================================================  
  //===================================================================================================  
  void apply2011(V0hhFit::SimultaneousFitter &fitter,
		 std::vector<std::string> years,
		 std::vector<std::string> modes,
		 std::vector<std::string> KS,
		 std::vector<std::string> vars
		 )
  {
    fitter.addParameter("mu(Bd)",5250.,5310.);
    fitter.addParameter("mu(Bs)",5340.,5380.);
    fitter.addParameter("Sigma(pipi)(DD)",         8.,        20.);
    fitter.addParameter("kSig(Kpi)"    ,         0.,         2.);
    fitter.addParameter("kSig(KK)"     ,         0.,         2.);
    fitter.addParameter("kSig(LL)"    ,         0.,         2.);
    fitter.addParameter("CoreFrac",0.,1.);
    fitter.addParameter("Alpha0(pipi)", alpha0_min, alpha0_max);
    fitter.addParameter("Alpha0(Kpi)" , alpha0_min, alpha0_max);
    fitter.addParameter("Alpha0(KK)"  , alpha0_min, alpha0_max);
    fitter.addParameter("N0(pipi)"    ,     n0_min,     n0_max);
    fitter.addParameter("N0(Kpi)"     ,     n0_min,     n0_max);
    fitter.addParameter("N0(KK)"      ,     n0_min,     n0_max);
    if (Constraints::finds(vars,"alpha1"))
      fitter.addParameter("Alpha1"        , alpha1_min, alpha1_max);
    else
      fitter.addParameter("Alpha1oAlpha0" , alpha1oAlpha0_min, alpha1oAlpha0_max);
    if (Constraints::finds(vars,"n1"))
      fitter.addParameter("N1"            , n1_min, n1_max);
    else
      fitter.addParameter("n1oN0"         , n1oN0_min, n1oN0_max);

    //Binding piK
    Constraints::bindPiK(fitter,years,modes,KS,vars);
    
    //Setting the mean
    std::cout << "Setting the means...";
    for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
      for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	  {	
	    if (itModes->find("piK") != std::string::npos)
	      continue;
	    if ((*itModes).find("Bd") != std::string::npos)
	      fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_mu").c_str(), "@0", "mu(Bd)");
	    else
	      fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_mu").c_str(), "@0", "mu(Bs)");
	  }
    std::cout << "done!"<< std::endl;
    //Sigma
    std::cout << "Setting the sigmas...";
    for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
      for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	  {	
	    if (itModes->find("piK") != std::string::npos)
	      continue;
	    std::string dependents = "Sigma(pipi)(DD)";
	    std::string formula    = "@0";
	    int nDeps = 1;
	    //	    if (itModes->find("Bs") != std::string::npos){
	    //	      dependents += ",kSig(Bs)";
	    //	      formula    += "*@"+Constraints::itoa(nDeps);
	    //	      nDeps++;
	    //	    }
	    if (itKS->find("LL") != std::string::npos){
	      dependents += ",kSig(LL)";
	      formula    += "*@"+Constraints::itoa(nDeps);
	      nDeps++;
	    }
	    if (itModes->find("Kpi") != std::string::npos){
	      dependents += ",kSig(Kpi)";
	      formula    += "*@"+Constraints::itoa(nDeps);
	      nDeps++;
	    }
	    else if (itModes->find("KK") != std::string::npos){
	      dependents += ",kSig(KK)";
	      formula    += "*@"+Constraints::itoa(nDeps);
	      nDeps++;
	    }
	    fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str(),formula.c_str(),dependents.c_str());
	  }
    std::cout << "done!" << std::endl;
    //CoreFrac
    std::cout << "Setting the core fractions...";
    for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
      for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	  {
	    if (itModes->find("piK") != std::string::npos)
	      continue;
	    fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(), "@0", ("CoreFrac"));
	  }
    std::cout << "done!" << std::endl;
    //Alpha1
    std::cout << "Setting the alpha1...";
      for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (!(Constraints::finds(vars,"alpha1")))
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0").c_str(), "@0", ("Alpha1oAlpha0"));
	      else
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha1"       ).c_str(), "@0", ("Alpha1"       ));
	    }
      std::cout << "done!" << std::endl;

	//N1
      std::cout << "Setting the n1...";
      for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (!(Constraints::finds(vars,"n1")))
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0").c_str(), "@0", ("n1oN0"));
	      else
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n1"   ).c_str(), "@0", ("N1"));
	    }
      std::cout << "done!" << std::endl;
      
      //Alpha0
      std::cout << "Setting alpha0...";
      for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (itModes->find("Kpi") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str(),"@0","Alpha0(Kpi)");
	      else if (itModes->find("KK") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str(),"@0","Alpha0(KK)");
	      else
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str(),"@0","Alpha0(pipi)");
	    }
      std::cout << "done!" << std::endl;
      //N0
      std::cout << "Setting n0...";
      for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (itModes->find("Kpi") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str(),"@0","N0(Kpi)");
	      else if (itModes->find("KK") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str(),"@0","N0(KK)");
	      else
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str(),"@0","N0(pipi)");
	    }
      std::cout << "done!" << std::endl;
  }

  //===================================================================================================  
  //===================================================================================================  

  void applyDummy(V0hhFit::SimultaneousFitter &fitter,
		  std::vector<std::string> years,
		  std::vector<std::string> modes,
		  std::vector<std::string> KS,
		  std::vector<std::string> vars
		  )
  {
    //Binding piK
    Constraints::bindPiK(fitter,years,modes,KS,vars);
    
    for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
      {
	//Adding parameters.
	fitter.addParameter(("mu(Bd)("+(*itYears)+")").c_str(),5250.,5310.);
	fitter.addParameter(("mu(Bs)("+(*itYears)+")").c_str(),5340.,5380.);
	fitter.addParameter(("Sigma(pipi)(DD)("+(*itYears)+")").c_str(),         8.,        20.);
	fitter.addParameter(("kSig(Kpi)("+(*itYears)+")").c_str()    ,         0.,         2.);
	fitter.addParameter(("kSig(KK)("+(*itYears)+")").c_str()     ,         0.,         2.);
	fitter.addParameter(("kSig(LL)("+(*itYears)+")").c_str()    ,         0.,         2.);
	fitter.addParameter(("CoreFrac("+(*itYears)+")").c_str(),0.,1.);
	fitter.addParameter(("Alpha0(pipi)("+(*itYears)+")").c_str(), alpha0_min, alpha0_max);
	fitter.addParameter(("Alpha0(Kpi)("+(*itYears)+")").c_str() , alpha0_min, alpha0_max);
	fitter.addParameter(("Alpha0(KK)("+(*itYears)+")").c_str()  , alpha0_min, alpha0_max);
	fitter.addParameter(("N0(pipi)("+(*itYears)+")").c_str()    ,     n0_min,     n0_max);
	fitter.addParameter(("N0(Kpi)("+(*itYears)+")").c_str()     ,     n0_min,     n0_max);
	fitter.addParameter(("N0(KK)("+(*itYears)+")").c_str()      ,     n0_min,     n0_max);
	if (Constraints::finds(vars,"alpha1"))
	  fitter.addParameter(("Alpha1("+(*itYears)+")").c_str()        , alpha1_min, alpha1_max);
	else
	  fitter.addParameter(("Alpha1oAlpha0("+(*itYears)+")").c_str() , alpha1oAlpha0_min, alpha1oAlpha0_max);
	if (Constraints::finds(vars,"n1"))
	  fitter.addParameter(("N1("+(*itYears)+")").c_str()            , n1_min, n1_max);
	else
	  fitter.addParameter(("N1oN0("+(*itYears)+")").c_str()         , n1oN0_min, n1oN0_max);
	//Naming them (for easier modifications)
	std::string mu_Bd         = "mu(Bd)("          +(*itYears)+")";
	std::string mu_Bs         = "mu(Bs)("          +(*itYears)+")";
	std::string sig_pipi      = "Sigma(pipi)(DD)(" +(*itYears)+")";
	std::string kSig_Kpi      = "kSig(Kpi)("       +(*itYears)+")";
	std::string kSig_KK       = "kSig(KK)("        +(*itYears)+")";
	std::string kSig_LL       = "kSig(LL)("        +(*itYears)+")";
	std::string CoreFrac      = "CoreFrac("        +(*itYears)+")";
	std::string Alpha0_pipi   = "Alpha0(pipi)("    +(*itYears)+")";
	std::string Alpha0_Kpi    = "Alpha0(Kpi)("     +(*itYears)+")";
	std::string Alpha0_KK     = "N0(KK)("          +(*itYears)+")";
	std::string N0_pipi       = "N0(pipi)("        +(*itYears)+")";
	std::string N0_Kpi        = "N0(Kpi)("         +(*itYears)+")";
	std::string N0_KK         = "N0(KK)("          +(*itYears)+")";
	std::string Alpha1        = "Alpha1("          +(*itYears)+")";
	std::string Alpha1oAlpha0 = "Alpha1oAlpha0("   +(*itYears)+")";
	std::string N1            = "N1("              +(*itYears)+")";
	std::string N1oN0         = "N1oN0("           +(*itYears)+")";
	
	//Setting the mean
	std::cout << "Setting the means...";
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {	
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if ((*itModes).find("Bd") != std::string::npos)
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_mu").c_str(), "@0", mu_Bd.c_str());
	      else
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_mu").c_str(), "@0", mu_Bs.c_str());
	    }
	std::cout << "done!"<< std::endl;
	//Sigma
	std::cout << "Setting the sigmas...";
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {	
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      std::string dependents = sig_pipi;
	      std::string formula    = "@0";
	      int nDeps = 1;
	      //	    if (itModes->find("Bs") != std::string::npos){
	      //	      dependents += ",kSig(Bs)";
	      //	      formula    += "*@"+Constraints::itoa(nDeps);
	      //	      nDeps++;
	      //	    }
	      if (itKS->find("LL") != std::string::npos){
		dependents += ","+kSig_LL;
		formula    += "*@"+Constraints::itoa(nDeps);
		nDeps++;
	      }
	      if (itModes->find("Kpi") != std::string::npos){
		dependents += ","+kSig_Kpi;
		formula    += "*@"+Constraints::itoa(nDeps);
		nDeps++;
	      }
	      else if (itModes->find("KK") != std::string::npos){
		dependents += ","+kSig_KK;
		formula    += "*@"+Constraints::itoa(nDeps);
		nDeps++;
	      }
	      fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str(),formula.c_str(),dependents.c_str());
	    }
	std::cout << "done!" << std::endl;
	//CoreFrac
	std::cout << "Setting the core fractions...";
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(), "@0", CoreFrac.c_str());
	    }
	std::cout << "done!" << std::endl;
	//Alpha1
	std::cout << "Setting the alpha1...";
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (!(Constraints::finds(vars,"alpha1")))
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0").c_str(), "@0", Alpha1oAlpha0.c_str());
	      else
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha1"       ).c_str(), "@0", Alpha1.c_str()       );
	    }
	std::cout << "done!" << std::endl;
	
	//N1
	std::cout << "Setting the n1...";
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (!(Constraints::finds(vars,"n1")))
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0").c_str(), "@0", N1oN0.c_str());
	      else
		fitter.addConstraint( ((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n1"   ).c_str(), "@0", N1   .c_str());
	    }
	std::cout << "done!" << std::endl;
	
	//Alpha0
	std::cout << "Setting alpha0...";
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (itModes->find("Kpi") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str(),"@0",Alpha0_Kpi .c_str());
	      else if (itModes->find("KK") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str(),"@0",Alpha0_KK  .c_str());
	      else
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str(),"@0",Alpha0_pipi.c_str());
	    }
	std::cout << "done!" << std::endl;
	//N0
	std::cout << "Setting n0...";
	for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
	  for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
	    {
	      if (itModes->find("piK") != std::string::npos)
		continue;
	      if (itModes->find("Kpi") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str(),"@0",N0_Kpi .c_str());
	      else if (itModes->find("KK") != std::string::npos)
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str(),"@0",N0_KK  .c_str());
	      else
		fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str(),"@0",N0_pipi.c_str());
	    }
	std::cout << "done!" << std::endl;
      }
  }
  
  //===================================================================================================  
  //===================================================================================================  
  //Stupid function to set everything constant (to a reasonable value) but the yields.
  //It is used in toying to make it faster for the moment
  void fixAllButYields(V0hhFit::SimultaneousFitter &fitter,
		       std::vector<std::string> years,
		       std::vector<std::string> modes,
		       std::vector<std::string> KS,
		       std::vector<std::string> vars
		       )
  {
    Constraints::apply2011(fitter,years,modes,KS,vars);

    fitter.setParameterValue("mu(Bd)",5281.0,true);
    fitter.setParameterValue("mu(Bs)",5367.9,true);
    fitter.setParameterValue("Sigma(pipi)(DD)", 16.55,true);
    fitter.setParameterValue("kSig(Kpi)"    ,    0.97,true);
    fitter.setParameterValue("kSig(KK)"     ,    0.91,true);
    fitter.setParameterValue("kSig(LL)"    ,     0.99,true);
    fitter.setParameterValue("CoreFrac",         0.54,true);
    fitter.setParameterValue("Alpha0(pipi)",     1.43,true);
    fitter.setParameterValue("Alpha0(Kpi)" ,     1.48,true);
    fitter.setParameterValue("Alpha0(KK)"  ,     1.51,true);
    fitter.setParameterValue("N0(pipi)"    ,     1.95,true);
    fitter.setParameterValue("N0(Kpi)"     ,     1.96,true);
    fitter.setParameterValue("N0(KK)"      ,     2.34,true);
    if (Constraints::finds(vars,"alpha1"))
      fitter.setParameterValue("Alpha1"    ,-4.,true);
    else
      fitter.setParameterValue("Alpha1oAlpha0" ,-1.14,true);
    if (Constraints::finds(vars,"n1"))
      fitter.setParameterValue("N1"        ,4.,true);
    else
      fitter.setParameterValue("n1oN0"     ,     2.62,true);
  }

  //===================================================================================================  
  //===================================================================================================  

  void applyConstraints(std::string constraints,
			V0hhFit::SimultaneousFitter &fitter,
			std::vector<std::string> years,
			std::vector<std::string> modes,
			std::vector<std::string> KS,
			std::vector<std::string> vars)
  {
    std::cout << "Applying constraints: " << constraints << std::endl;
    if (constraints=="2011")
      Constraints::apply2011(fitter,years,modes,KS,vars);
    else if (constraints=="dummy")
      Constraints::applyDummy(fitter,years,modes,KS,vars);
    else if (constraints=="FixAllButYields")
      Constraints::fixAllButYields(fitter,years,modes,KS,vars);
  }

};
