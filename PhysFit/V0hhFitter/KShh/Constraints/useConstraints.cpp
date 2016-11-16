namespace KShhConstraints
{
	typedef std::vector<std::string>::iterator stringIter;
	
	std::string itoa(int i)
	{
		std::stringstream ss;
		ss << i;
		return ss.str();
	}
	
	//Tests if a constraint file exists.
	void testFile(std::string fileName)
	{
		std::ifstream f;
		std::string dir = getenv("V0HHFITTERROOT");
		f.open((dir+"/KShh/Constraints/"+fileName+".txt").c_str());
		if (!f.is_open())
			{
				std::cout << "File not found! (" << fileName << ")" << std::endl;
				assert(0);
			}
		f.close();
	}
	
	bool readBool(std::string fileName, const char* var)
	{
		std::ifstream f;
		std::string dir = getenv("V0HHFITTERROOT");
		f.open((dir+"/KShh/Constraints/"+fileName+".txt").c_str());
		if (f.is_open())
			{
				std::string line;
				while(getline(f,line)) {
					line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
					if(line[0] == '/' && line[1] == '/') continue;
					if(line[0] == '#') continue;
					std::string name, value;
					std::istringstream stream(line);
					stream >> name;
					if (name == std::string(var))
						{
							stream >> value;	      
							f.close();
							if (value == "true")
								{
									std::cout << "INFO: Enabling " << var <<"." << std::endl;
									return true;
								}
							else
								{
									std::cout << "INFO: Dismissing " << var <<"." << std::endl;										  
									return false;
								}
						}
				}
				std::cout << "ERROR: While decoding file, did not find the variable " << var 
						  << ". Setting it to false (default)." << std::endl;
				return false;
			}
		else
			std::cout << "ERROR: Could not open the file! (" << dir+"/KShh/Constraints/"+fileName+".txt" << ")" << std::endl;
		assert(0);
		return false;
	}  
	
	//Reads a pair of doubles which sets a central value and an error for a Gaussian constraint
	std::pair<double,double> readConstraint(std::string fileName, std::string key)
	{
		std::ifstream f;
		std::string dir(getenv("V0HHFITTERROOT"));
		f.open((dir+"/KShh/Constraints/"+fileName+".txt").c_str());
		if (f.is_open())
			{
				std::string line;
				while(getline(f,line)) {
					line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
					if(line[0] == '/' && line[1] == '/') continue;
					if(line[0] == '#') continue;
					std::string name, value1, value2;
					std::istringstream stream(line);
					stream >> name;
					if (name == key)
						{
							stream >> value1;
							stream >> value2;
							f.close();
							return (std::make_pair(std::atof(value1.c_str()),std::atof(value2.c_str())));
						}	      
				}
				std::cout << "ERROR: While decoding file, did not find the key " << key << "." << std::endl;
				assert(0);
				return (std::make_pair(0.,1.));
			}
		else
			std::cout << "ERROR: Could not open the file! (" << dir+"/KShh/Constraints/"+fileName+".txt" << ")" << std::endl;
		assert(0);
		return (std::make_pair(0.,1.));
	}
	
	//Reads a pair of keysK and the bool attached to it (it is for the crossfeeds & prb inclusion).
	bool readKey(std::string fileName,std::string firstKey, std::string secondKey)
	{
		std::ifstream f;
		std::string dir(getenv("V0HHFITTERROOT"));
		f.open((dir+"/KShh/Constraints/"+fileName+".txt").c_str());
		if (f.is_open())
			{
				std::string line;
				while(getline(f,line)) {
					line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
					if(line[0] == '/' && line[1] == '/') continue;
					if(line[0] == '#') continue;
					std::string name1, name2, value;
					std::istringstream stream(line);
					stream >> name1;
					if (name1 == firstKey)
						{
							stream >> name2;
							if (name2 == secondKey)
								{
									stream >> value;
									f.close();
									return (value == "true");
								}	      
						}
				}
				std::cout << "ERROR: While decoding file, did not find the key " << firstKey << " " << secondKey 
						  << ". Returning false (default)." << std::endl;
				return false;
			}
		else
			std::cout << "ERROR: Could not open the file! (" << dir+"/KShh/Constraints/"+fileName+".txt" << ")" << std::endl;
		assert(0);
		return false;    
	}

	double readValue(std::string fileName, const char* var)
	{
		std::ifstream f;
		std::string dir(getenv("V0HHFITTERROOT"));
		f.open((dir+"/KShh/Constraints/"+fileName+".txt").c_str());
		if (f.is_open())
			{
				std::string line;
				while(getline(f,line)) {
					line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
					if(line[0] == '/' && line[1] == '/') continue;
					if(line[0] == '#') continue;
					std::string name, value;
					std::istringstream stream(line);
					stream >> name;
					if (name == std::string(var))
						{
							stream >> value;	      
							f.close();
							return std::atof(value.c_str());
						}
				}
				std::cout << "ERROR: While decoding file, did not find the variable " << var << std::endl;
			}
		else
			std::cout << "ERROR: Could not open the file! (" << dir+"/KShh/Constraints/"+fileName+".txt" << ")" << std::endl;
		assert(0);
		return 0;
	}

	std::string readString(std::string fileName, std::string key)
	{
		std::ifstream f;
		std::string dir(getenv("V0HHFITTERROOT"));
		f.open((dir+"/KShh/Constraints/"+fileName+".txt").c_str());
		if (f.is_open())
			{
				std::string line;
				while(getline(f,line)) {
					line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
					if(line[0] == '/' && line[1] == '/') continue;
					if(line[0] == '#') continue;
					std::string name, value;
					std::istringstream stream(line);
					stream >> name;
					if (name == std::string(key))
						{
							stream >> value; 
							f.close();
							return value;
						}
				}
				std::cout << "ERROR: While decoding file, did not find the variable " << key << std::endl;
			}
		else
			std::cout << "ERROR: Could not open the file! (" << dir+"/KShh/Constraints/"+fileName+".txt" << ")" << std::endl;
		assert(0);
		return 0;
	}
  
	// Method to bind every piK parameter to Kpi ones.
	void bindPiK(V0hhFit::SimultaneousFitter &fitter, std::vector<std::string> years, std::vector<std::string> modes, std::vector<std::string> KS, std::vector<std::string> vars)
	{
		for (stringIter itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
			if ((*itModes).find("piK") != std::string::npos)
				for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
					for (stringIter itKS = KS.begin() ; itKS != KS.end() ; ++itKS)
						for (stringIter itVars = vars.begin() ; itVars != vars.end() ; ++itVars)
							{
								if ((*itModes).find("Bs") != std::string::npos)
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str(),
														 "@0",
														 ("Bs2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str());      
								else
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str(),
														 "@0",
														 ("Bd2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_"+(*itVars)).c_str());      
							}
	}
  
	//==============================================================================================================================
	//==============================================================================================================================

	void setDoubleCB(V0hhFit::Fitter &fitter,
					 std::vector<std::string> years,
					 std::vector<std::string> modes,
					 std::vector<std::string> KS,
					 std::string option)
	{     
		std::string fileName = "constraints-DataFit-"+option;
		std::cout << fileName << std::endl;
		//Mus
		bool deltaM = KShhConstraints::readBool(fileName,"deltaM");
		bool deltaMYears = KShhConstraints::readBool(fileName,"deltaMYears");
		if (deltaM && !deltaMYears)
			fitter.addParameter("(m(Bs)-m(Bd))",85.,70.,100.);
		for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years) {
			fitter.addParameter(("mu(Bd)("+(*it_years)+")").c_str(),5250.,5310.);
			if (deltaM && deltaMYears)
				fitter.addParameter(("(m(Bs)-m(Bd))("+*it_years+")").c_str(),85.,70.,100.);
			else if (!deltaM)
				fitter.addParameter(("mu(Bs)("+(*it_years)+")").c_str(),5340.,5380.);
			//      fitter.addParameter(("mu(Bd)(pipi)("+(*it_years)+")").c_str(),5250.,5310.);
			//      fitter.addParameter(("mu(Bs)(pipi)("+(*it_years)+")").c_str(),5340.,5380.);
			//      fitter.addParameter(("mu(Bd)(Kpi)("+(*it_years)+")").c_str(),5250.,5310.);
			//      fitter.addParameter(("mu(Bs)(Kpi)("+(*it_years)+")").c_str(),5340.,5380.);
			//      fitter.addParameter(("mu(Bd)(KK)("+(*it_years)+")").c_str(),5250.,5310.);
			//      fitter.addParameter(("mu(Bs)(KK)("+(*it_years)+")").c_str(),5370.,5370.);
			/*
			  for(std::vector<std::string>::iterator it_KS = KS.begin(); it_KS    != KS.end(); ++it_KS)
			  {
			  fitter.addConstraint(("Bd2KSpipi"+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bd)(pipi)("+(*it_years)+")").c_str());
			  fitter.addConstraint(("Bs2KSpipi"+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bs)(pipi)("+(*it_years)+")").c_str());
			  fitter.addConstraint(("Bd2KSKpi" +(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bd)(Kpi)(" +(*it_years)+")").c_str());
			  fitter.addConstraint(("Bs2KSKpi" +(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bs)(Kpi)(" +(*it_years)+")").c_str());
			  fitter.addConstraint(("Bd2KSKK"  +(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bd)(KK)("  +(*it_years)+")").c_str());
			  fitter.addConstraint(("Bs2KSKK"  +(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bs)(KK)(  "+(*it_years)+")").c_str());
			  }
			*/      
			for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes)
				for(std::vector<std::string>::iterator it_KS = KS.begin(); it_KS    != KS.end(); ++it_KS)
					if (((*it_modes).find("Bd") != std::string::npos))
						fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bd)("+(*it_years)+")").c_str());
					else if (((*it_modes).find("Bs") != std::string::npos))
						{
							if (deltaM && !deltaMYears)
								fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0+@1",("mu(Bd)("+(*it_years)+"),(m(Bs)-m(Bd))").c_str());
							else if (deltaM && deltaMYears)
								fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0+@1",("mu(Bd)("+(*it_years)+"),(m(Bs)-m(Bd))("+(*it_years)+")").c_str());
							else
								fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bs)("+(*it_years)+")").c_str());
						}
		}
		//Sigmas
		fitter.addParameter("Sigma(pipi)(DD)(2011)" ,         8.,        30.);
		fitter.addParameter("kSig(Kpi)(2011)"       ,         0.,         2.);
		fitter.addParameter("kSig(KK)(2011)"        ,         0.,         2.);
		fitter.addParameter("kSig(LL)(2011)"        ,         0.,         2.);
		bool facBs = KShhConstraints::readBool(fileName,"facBs");
		if (std::find(years.begin(),years.end(),"2012a") != years.end())
			{
				fitter.addParameter("Sigma(pipi)(DD)(2012a)",         8.,        30.);
				fitter.addParameter("kSig(Kpi)(2012a_o_2011)"       ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(KK)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(LL)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
			}
		if (std::find(years.begin(),years.end(),"2012b") != years.end())
			{
				fitter.addParameter("Sigma(pipi)(DD)(2012b)",         8.,        30.);
				fitter.addParameter("kSig(Kpi)(2012b_o_2011)"       ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(KK)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(LL)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
			}
		if (facBs)
			{
				fitter.addParameter("kSig(Bs)(2011)"        ,         0.,         5.);
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addParameter("kSig(Bs)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addParameter("kSig(Bs)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
			}
		//Setting piK and Kpi to be the same.
		for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
				{
					if (*itModes == "Bs2KSpiK")
						for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
							fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str(),"@0",("Bs2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str());
					else if (*itModes == "Bd2KSpiK")
						for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
							fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str(),"@0",("Bd2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str());
				}
		for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
				for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
					{	
						if (itModes->find("piK") != std::string::npos)
							continue;
						std::string dependents = "Sigma(pipi)(DD)("+*itYears+")";
						std::string formula    = "@0";
						int nDeps = 1;
						if (facBs)
							{
								if (itModes->find("Bs") != std::string::npos){
									dependents += ",kSig(Bs)(2011)";
									formula    += "*@"+KShhConstraints::itoa(nDeps);
									nDeps++;
									if (itYears->find("2012a") != std::string::npos){
										dependents += ",kSig(Bs)(2012a_o_2011)";
										formula    += "*@"+KShhConstraints::itoa(nDeps);
										nDeps++;
									}
									else if (itYears->find("2012b") != std::string::npos){
										dependents += ",kSig(Bs)(2012b_o_2011)";
										formula    += "*@"+KShhConstraints::itoa(nDeps);
										nDeps++;
									}
								}
							}
						if (itKS->find("LL") != std::string::npos){
							dependents += ",kSig(LL)(2011)";
							formula    += "*@"+KShhConstraints::itoa(nDeps);
							nDeps++;
							if (itYears->find("2012a") != std::string::npos){
								dependents += ",kSig(LL)(2012a_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
							else if (itYears->find("2012b") != std::string::npos){
								dependents += ",kSig(LL)(2012b_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
						}
						if (itModes->find("Kpi") != std::string::npos){
							dependents += ",kSig(Kpi)(2011)";
							formula    += "*@"+KShhConstraints::itoa(nDeps);
							nDeps++;
							if (itYears->find("2012a") != std::string::npos){
								dependents += ",kSig(Kpi)(2012a_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
							else if (itYears->find("2012b") != std::string::npos){
								dependents += ",kSig(Kpi)(2012b_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
						}
						else if (itModes->find("KK") != std::string::npos){
							dependents += ",kSig(KK)(2011)";
							formula    += "*@"+KShhConstraints::itoa(nDeps);
							nDeps++;
							if (itYears->find("2012a") != std::string::npos){
								dependents += ",kSig(KK)(2012a_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
							else if (itYears->find("2012b") != std::string::npos){
								dependents += ",kSig(KK)(2012b_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
						}
						fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str(),formula.c_str(),dependents.c_str());
					}
		//Gaussian now!
		double mean,width;
		mean  = KShhConstraints::readConstraint(fileName,"kSig(LL)(2012X/2011)").first;
		width = KShhConstraints::readConstraint(fileName,"kSig(LL)(2012X/2011)").second;
		if (width != 0)
			{
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addGaussianConstraint("kSig(LL)(2012a_o_2011)",mean,width);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addGaussianConstraint("kSig(LL)(2012b_o_2011)",mean,width);
			}
		else
			{
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.setParameterValue("kSig(LL)(2012a_o_2011)",mean,true);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.setParameterValue("kSig(LL)(2012b_o_2011)",mean,true);
			}
		if (facBs)
			{
				mean  = KShhConstraints::readConstraint(fileName,"kSig(Bs)").first;
				width = KShhConstraints::readConstraint(fileName,"kSig(Bs)").second;
				if (width != 0)	  
					fitter.addGaussianConstraint("kSig(Bs)(2011)",mean,width);
				mean = KShhConstraints::readConstraint(fileName,"kSig(Bs)(2012X/2011)").first;
				width = KShhConstraints::readConstraint(fileName,"kSig(Bs)(2012X/2011)").second;
				if (width != 0)
					{
						if (std::find(years.begin(),years.end(),"2012a") != years.end())
							fitter.addGaussianConstraint("kSig(Bs)(2012a_o_2011)",mean,width);
						if (std::find(years.begin(),years.end(),"2012b") != years.end())
							fitter.addGaussianConstraint("kSig(Bs)(2012b_o_2011)",mean,width);
					}
				else
					{
						if (std::find(years.begin(),years.end(),"2012a") != years.end())
							fitter.setParameterValue("kSig(Bs)(2012a_o_2011)",mean,true);
						if (std::find(years.begin(),years.end(),"2012b") != years.end())
							fitter.setParameterValue("kSig(Bs)(2012b_o_2011)",mean,true);
					}
			}
		std::pair<double,double> constraint;
		constraint = KShhConstraints::readConstraint(fileName,"kSig(Kpi)(2011)");
		if (constraint.second != 0.)
			fitter.addGaussianConstraint("kSig(Kpi)(2011)",constraint.first,constraint.second);
		constraint = KShhConstraints::readConstraint(fileName,"kSig(KK)(2011)");
		if (constraint.second != 0.)
			fitter.addGaussianConstraint("kSig(KK)(2011)",constraint.first,constraint.second);
	  
		mean  = KShhConstraints::readConstraint(fileName,"kSig(Mode)(2012X/2011)").first;
		width = KShhConstraints::readConstraint(fileName,"kSig(Mode)(2012X/2011)").second;
		if (width != 0)
			{
				//	fitter.addGaussianConstraint("kSig(Kpi)(2011)",1.,width);
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addGaussianConstraint("kSig(Kpi)(2012a_o_2011)",mean,width);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addGaussianConstraint("kSig(Kpi)(2012b_o_2011)",mean,width);	
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addGaussianConstraint("kSig(KK)(2012a_o_2011)",mean,width);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addGaussianConstraint("kSig(KK)(2012b_o_2011)",mean,width);
			}
		else
			{
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.setParameterValue("kSig(Kpi)(2012a_o_2011)",mean,true);
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.setParameterValue("kSig(KK)(2012a_o_2011)",mean,true);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.setParameterValue("kSig(Kpi)(2012b_o_2011)",mean,true);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.setParameterValue("kSig(KK)(2012b_o_2011)",mean,true);
			}
		std::cout << "done!" << std::endl;    
	}
	//==============================================================================================================================
	//==============================================================================================================================
	
	void setDoubleGauss(V0hhFit::Fitter &fitter,
						std::vector<std::string> years,
						std::vector<std::string> modes,
						std::vector<std::string> KS,
						std::string option)
	{     
		std::string fileName = "constraints-DataFit-"+option;
		std::cout << fileName << std::endl;
		//Mus
		for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years) {
			fitter.addParameter(("mu(Bd)("+(*it_years)+")").c_str(),5250.,5310.);
			fitter.addParameter(("mu(Bs)("+(*it_years)+")").c_str(),5340.,5380.);
			for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes)
				for(std::vector<std::string>::iterator it_KS = KS.begin(); it_KS    != KS.end(); ++it_KS)
					if (((*it_modes).find("Bd") != std::string::npos))
						fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bd)("+(*it_years)+")").c_str());
					else if (((*it_modes).find("Bs") != std::string::npos))
						fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),"@0",("mu(Bs)("+(*it_years)+")").c_str());
		}
		//Sigmas
		fitter.addParameter("Sigma(pipi)(DD)(2011)" ,         8.,        30.);
		fitter.addParameter("kSig(Kpi)(2011)"       ,         0.,         2.);
		fitter.addParameter("kSig(KK)(2011)"        ,         0.,         2.);
		fitter.addParameter("kSig(LL)(2011)"        ,         0.,         2.);
		bool facBs = KShhConstraints::readBool(fileName,"facBs");
		if (std::find(years.begin(),years.end(),"2012a") != years.end())
			{
				fitter.addParameter("Sigma(pipi)(DD)(2012a)",         8.,        30.);
				fitter.addParameter("kSig(Kpi)(2012a_o_2011)"       ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(KK)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(LL)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
			}
		if (std::find(years.begin(),years.end(),"2012b") != years.end())
			{
				fitter.addParameter("Sigma(pipi)(DD)(2012b)",         8.,        30.);
				fitter.addParameter("kSig(Kpi)(2012b_o_2011)"       ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(KK)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
				fitter.addParameter("kSig(LL)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
			}
		if (facBs)
			{
				fitter.addParameter("kSig(Bs)(2011)"        ,         0.,         2.);
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addParameter("kSig(Bs)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addParameter("kSig(Bs)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
			}
		//Setting piK and Kpi to be the same.
		for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
				{
					if (*itModes == "Bs2KSpiK")
						for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
							fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma0").c_str(),"@0",("Bs2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_sigma0").c_str());
					else if (*itModes == "Bd2KSpiK")
						for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
							fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma0").c_str(),"@0",("Bd2KSKpi"+(*itKS)+"_"+(*itYears)+"_pdf_sigma0").c_str());
				}
		for (stringIter itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (stringIter itModes = modes.begin() ; itModes != modes.end(); ++itModes)
				for (stringIter itKS = KS.begin() ; itKS != KS.end(); ++itKS)	
					{	
						if (itModes->find("piK") != std::string::npos)
							continue;
						std::string dependents = "Sigma(pipi)(DD)("+*itYears+")";
						std::string formula    = "@0";
						int nDeps = 1;
						if (facBs)
							{
								if (itModes->find("Bs") != std::string::npos){
									dependents += ",kSig(Bs)(2011)";
									formula    += "*@"+KShhConstraints::itoa(nDeps);
									nDeps++;
									if (itYears->find("2012a") != std::string::npos){
										dependents += ",kSig(Bs)(2012a_o_2011)";
										formula    += "*@"+KShhConstraints::itoa(nDeps);
										nDeps++;
									}
									else if (itYears->find("2012b") != std::string::npos){
										dependents += ",kSig(Bs)(2012b_o_2011)";
										formula    += "*@"+KShhConstraints::itoa(nDeps);
										nDeps++;
									}
								}
							}
						if (itKS->find("LL") != std::string::npos){
							dependents += ",kSig(LL)(2011)";
							formula    += "*@"+KShhConstraints::itoa(nDeps);
							nDeps++;
							if (itYears->find("2012a") != std::string::npos){
								dependents += ",kSig(LL)(2012a_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
							else if (itYears->find("2012b") != std::string::npos){
								dependents += ",kSig(LL)(2012b_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
						}
						if (itModes->find("Kpi") != std::string::npos){
							dependents += ",kSig(Kpi)(2011)";
							formula    += "*@"+KShhConstraints::itoa(nDeps);
							nDeps++;
							if (itYears->find("2012a") != std::string::npos){
								dependents += ",kSig(Kpi)(2012a_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
							else if (itYears->find("2012b") != std::string::npos){
								dependents += ",kSig(Kpi)(2012b_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
						}
						else if (itModes->find("KK") != std::string::npos){
							dependents += ",kSig(KK)(2011)";
							formula    += "*@"+KShhConstraints::itoa(nDeps);
							nDeps++;
							if (itYears->find("2012a") != std::string::npos){
								dependents += ",kSig(KK)(2012a_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
							else if (itYears->find("2012b") != std::string::npos){
								dependents += ",kSig(KK)(2012b_o_2011)";
								formula    += "*@"+KShhConstraints::itoa(nDeps);
								nDeps++;
							}
						}
						fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma0").c_str(),formula.c_str(),dependents.c_str());
					}
		//Gaussian now!
		double width;
		width = KShhConstraints::readValue(fileName,"kSig(LL)(2012X/2011)");
		if (width != 0)
			{
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addGaussianConstraint("kSig(LL)(2012a_o_2011)",1.,width);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addGaussianConstraint("kSig(LL)(2012b_o_2011)",1.,width);
			}
		else
			{
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.setParameterConstant("kSig(LL)(2012a_o_2011)");
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.setParameterConstant("kSig(LL)(2012b_o_2011)");
			}
		if (facBs)
			{
				width = KShhConstraints::readValue(fileName,"kSig(Bs)");
				if (width != 0)	  
					fitter.addGaussianConstraint("kSig(Bs)(2011)",1.,width);
				width = KShhConstraints::readValue(fileName,"kSig(Bs)(2012X/2011)");
				if (width != 0)
					{
						if (std::find(years.begin(),years.end(),"2012a") != years.end())
							fitter.addGaussianConstraint("kSig(Bs)(2012a_o_2011)",1.,width);
						if (std::find(years.begin(),years.end(),"2012b") != years.end())
							fitter.addGaussianConstraint("kSig(Bs)(2012b_o_2011)",1.,width);
					}
				else
					{
						if (std::find(years.begin(),years.end(),"2012a") != years.end())
							fitter.setParameterConstant("kSig(Bs)(2012a_o_2011)");
						if (std::find(years.begin(),years.end(),"2012b") != years.end())
							fitter.setParameterConstant("kSig(Bs)(2012b_o_2011)");
					}
			}

		width = KShhConstraints::readValue(fileName,"kSig(Mode)(2011)");
		if (width != 0.)
			{
				fitter.addGaussianConstraint("kSig(Kpi)(2011)",1.,width);
				fitter.addGaussianConstraint("kSig(KK)(2011)",1.,width);
			}
		width = KShhConstraints::readValue(fileName,"kSig(Mode)(2012X/2011)");
		if (width != 0)
			{
				//	fitter.addGaussianConstraint("kSig(Kpi)(2011)",1.,width);
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addGaussianConstraint("kSig(Kpi)(2012a_o_2011)",1.,width);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addGaussianConstraint("kSig(Kpi)(2012b_o_2011)",1.,width);	
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.addGaussianConstraint("kSig(KK)(2012a_o_2011)",1.,width);
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.addGaussianConstraint("kSig(KK)(2012b_o_2011)",1.,width);
			}
		else
			{
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.setParameterConstant("kSig(Kpi)(2012a_o_2011)");
				if (std::find(years.begin(),years.end(),"2012a") != years.end())
					fitter.setParameterConstant("kSig(KK)(2012a_o_2011)");
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.setParameterConstant("kSig(Kpi)(2012b_o_2011)");
				if (std::find(years.begin(),years.end(),"2012b") != years.end())
					fitter.setParameterConstant("kSig(KK)(2012b_o_2011)");
			}
		std::cout << "done!" << std::endl;    
	}

	//==============================================================================================================================
	//==============================================================================================================================

	//	void setBristolBall(V0hhFit::Fitter &fitter,
	//						std::vector<std::string> years,
	//						std::vector<std::string> modes,
	//						std::vector<std::string> KScat,
	//						std::string option)
	//	{
	//	}

	//==============================================================================================================================
	//==============================================================================================================================

	//	void setCruijff(V0hhFit::Fitter &fitter,
	//					std::vector<std::string> years,
	//					std::vector<std::string> modes,
	//					std::vector<std::string> KScat,
	//					std::string option)
	//	{
    
	//	}


	//==============================================================================================================================
	//==============================================================================================================================

	void setSignalModel(V0hhFit::Fitter &fitter,
						std::string sigModel,
						std::vector<std::string> years,
						std::vector<std::string> modes,
						std::vector<std::string> KScat,
						std::string option)
	{
		std::vector<std::string> vars;
    
		if (sigModel == "DoubleCB")
			{
				KShhConstraints::setDoubleCB(
											 fitter,
											 years,
											 modes,
											 KScat,
											 option
											 );
			}
		else if (sigModel == "DoubleGauss")
			{
				KShhConstraints::setDoubleGauss(
												fitter,
												years,
												modes,
												KScat,
												option);
	
			}
		else
			{
				std::cout << "FATAL: Following signal shape: " << sigModel <<"is NOT IMPLEMENTED." << std::endl;
				std::exit(1);
			}
		/*
		  else if (sigModel == "Cruijff")
		  {
		  KShhConstraints::setCruijff(
		  fitter,
		  years,
		  modes,
		  KScat,
		  option
		  );
		  }
		  else if (sigModel == "BristolBall")
		  {
		  KShhConstraints::setBristolBall(
		  fitter,
		  years,
		  modes,
		  KScat,
		  option
		  );
		  }
		*/
	}

	//==============================================================================================================================
	//==============================================================================================================================
	
	void setCombinatorialModel(V0hhFit::Fitter &fitter,
							   std::vector<std::string> years,
							   std::vector<std::string> invMass,
							   std::vector<std::string> KS_cat,
							   std::string option,
							   std::string combOption)
	{	  
		std::string fileName = "constraints-DataFit-"+option;
		bool sameSlopesYears = KShhConstraints::readBool(fileName,"sameSlopesYears");
		bool sameSlopesModes = KShhConstraints::readBool(fileName,"sameSlopesModes");
		bool facSlopesYears  = KShhConstraints::readBool(fileName,"facSlopesYears");
		bool facSlopesModes  = KShhConstraints::readBool(fileName,"facSlopesModes");
		bool sameRatiosYears = KShhConstraints::readBool(fileName,"sameRatiosYears");
		//		bool sameRatiosModes = KShhConstraints::readBool(fileName,"sameRatiosModes");
		bool allKKConstraint = KShhConstraints::readBool(fileName,"allKKConstraint");
		bool polSlopes = (combOption.find("PolSlopes") != std::string::npos);	  
		
		if (!polSlopes)
			{
				if (sameSlopesYears && sameSlopesModes)
					fitter.addParameter("Slope(Comb)",-1.,0.);
				else if (!sameSlopesYears && sameSlopesModes)
					for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years)
						{
							if (it_years->find("2012") == std::string::npos || !facSlopesYears)
								fitter.addParameter(("Slope(Comb)("+*it_years+")").c_str(),-0.01,0.);
						}
				else if (sameSlopesYears && !sameSlopesModes)
					{
						fitter.addParameter(("Slope(Comb)(pipi)"),-0.01,0.);
						if (!facSlopesModes)
							fitter.addParameter(("Slope(Comb)(Kpi)" ),-0.01,0.);
						if (!facSlopesModes)
							fitter.addParameter(("Slope(Comb)(KK)"  ),-0.01,0.);	
					}
				else if (!sameSlopesYears && !sameSlopesModes)
					for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years)
						{
							if (it_years->find("2012") == std::string::npos || !facSlopesYears)
								{
									fitter.addParameter(("Slope(Comb)(pipi)("+(*it_years)+")").c_str(),-0.01,0.);
									if (!facSlopesModes)
										fitter.addParameter(("Slope(Comb)(Kpi)(" +(*it_years)+")").c_str(),-0.01,0.);
									if (!facSlopesModes)
										fitter.addParameter(("Slope(Comb)(KK)("  +(*it_years)+")").c_str(),-0.01,0.);	
								}
						}
				else 
					{
						std::cout << "TEMP: Can't do that." << std::endl;
						std::exit(1);
					}
			  
				if (sameSlopesYears && !sameRatiosYears)
					std::cout << "WARNING: Inconsistent model. If comb slopes are the same through years, ratios should as well." << std::endl;
				if (sameRatiosYears || sameSlopesYears)
					fitter.addParameter( ("Slope(Comb)(LL_o_DD)"), 0. , 5.0 );
				else
					for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years)
						fitter.addParameter( ("Slope(Comb)(LL_o_DD)("+(*it_years)+")").c_str(), 0. , 5.0 );

				if (facSlopesModes)
					for(std::vector<std::string>::iterator it_invMass = invMass.begin(); it_invMass != invMass.end(); ++it_invMass)
						if (it_invMass->find("K") != std::string::npos && (*it_invMass) != "piK")
							fitter.addParameter( ("Slope(Comb)("+*it_invMass+"_o_pipi)").c_str(), 0. , 5.0 );
				if (facSlopesYears)
					for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years)
						if (it_years->find("2012") != std::string::npos)
							fitter.addParameter( ("Slope(Comb)("+*it_years+"_o_2011)").c_str(), 0. , 5.0 );

				for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
					for(std::vector<std::string>::iterator it_invMass = invMass.begin(); it_invMass != invMass.end(); ++it_invMass)
						for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; ++itKS)
							{
								std::string formula("@0"),dependents(""),name("");
								unsigned int nParams(1);
								dependents += "Slope(Comb)";
								if (!sameSlopesModes && !facSlopesModes)
									if (it_invMass->find("piK") != std::string::npos)
										dependents += "(Kpi)";
									else
										dependents += "("+*it_invMass+")";
								else if (facSlopesModes)
									dependents += "(pipi)";
								if (!sameSlopesYears && !facSlopesYears)
									dependents += "("+(*it_years)+")";
								else if (facSlopesYears)
									dependents += "(2011)";
								if (itKS->find("LL") != std::string::npos)
									{
										if (sameRatiosYears)
											dependents += ",Slope(Comb)(LL_o_DD)";
										else
											dependents += ",Slope(Comb)(LL_o_DD)("+(*it_years)+")";
										std::stringstream ss;
										ss << nParams;
										formula += "*@" + ss.str();
										nParams++;
									}
								if (it_invMass->find("pipi") == std::string::npos && facSlopesModes)								  
									{
										if (it_invMass->find("KK") != std::string::npos)
											dependents += ",Slope(Comb)(KK_o_pipi)";
										else
											dependents += ",Slope(Comb)(Kpi_o_pipi)";
										std::stringstream ss;
										ss << nParams;
										formula += "*@"+ss.str();		
										nParams++;
									}

								if (it_years->find("2011") == std::string::npos && facSlopesYears)
									{
										dependents += ",Slope(Comb)("+*it_years+"_o_2011)";
										std::stringstream ss;
										ss << nParams;
										formula += "*@"+ss.str();		
										nParams++;
									}
							  
								fitter.addConstraint(("combinatoric_KS"+(*it_invMass)+(*itKS)+"_"+(*it_years)+"_pdf_slope").c_str(),
													 formula.c_str(),
													 dependents.c_str()
													 );
								//							  std::cout << ("combinatoric_KS"+(*it_invMass)+(*itKS)+"_"+(*it_years)+"_pdf_slope").c_str() << std::endl << formula.c_str() << std::endl << dependents << std::endl<< std::endl;
							}
			  
			}
		else
			{
			    
				fitter.addParameter(("c1(Comb)(Kpi)(2011)" ),-0.01,-5.,0.);
				fitter.addParameter(("c1(Comb)(pipi)(2011)"),-0.01,-5.,0.);
				if (!facSlopesYears)
					{
						fitter.addParameter(("c1(Comb)(pipi)(2012a)"),-0.01,-5.,0.);
						fitter.addParameter(("c1(Comb)(pipi)(2012b)"),-0.01,-5.,0.);
						fitter.addParameter(("c1(Comb)(Kpi)(2012a)" ),-0.01,-5.,0.);
						fitter.addParameter(("c1(Comb)(Kpi)(2012b)" ),-0.01,-5.,0.);
					}
				if (allKKConstraint)
					fitter.addParameter(("c1(Comb)(KK)"  ),-0.01,-5.,0.);	
				else
					{
						fitter.addParameter(("c1(Comb)(KK)(2011)"  ),-0.01,-5.,0.);	
						if (!facSlopesYears)
							{
								fitter.addParameter(("c1(Comb)(KK)(2012a)"  ),-0.01,-5.,0.);	
								fitter.addParameter(("c1(Comb)(KK)(2012b)"  ),-0.01,-5.,0.);	
							}
					}
				fitter.addParameter(("c1(Comb)(LL_o_DD)"), 0. , 5.0 );			  
				if (facSlopesYears)
					{
						fitter.addParameter("c1(Comb)(2012a_o_2011)",1.,0.,2.);
						fitter.addParameter("c1(Comb)(2012b_o_2011)",1.,0.,2.);
					}
				std::vector<std::string> paramName;
				paramName.push_back("c1");
				//    paramName.push_back("c2");
			  
				for(std::vector<std::string>::iterator itPars       = paramName.begin();    itPars    != paramName.end();    ++itPars)
					for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
						for(std::vector<std::string>::iterator it_invMass = invMass.begin(); it_invMass != invMass.end(); ++it_invMass)
							for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; ++itKS)
								{
									std::string formula("@0"),dependents(""),name("");
									unsigned int nParams(1);
									dependents += *itPars+"(Comb)";
									if (it_invMass->find("piK") != std::string::npos)
										dependents += "(Kpi)";
									else
										dependents += "("+*it_invMass+")";
									if (!facSlopesYears)
										if (it_invMass->find("KK") == std::string::npos || !allKKConstraint)
											dependents += "("+(*it_years)+")";
										else{}
									else
										dependents += "(2011)";									  
										  
									if (itKS->find("LL") != std::string::npos)
										{
											dependents += ","+(*itPars)+"(Comb)(LL_o_DD)";
											std::stringstream ss;
											ss << nParams;
											formula += "*@" + ss.str();
											nParams++;
										}
									if (it_years->find("2012") != std::string::npos && facSlopesYears)
										{
											dependents += ","+(*itPars)+"(Comb)("+*it_years+"_o_2011)";
											std::stringstream ss;
											ss << nParams;
											formula += "*@" + ss.str();
											nParams++;
										}
									fitter.addConstraint(("combinatoric_KS"+(*it_invMass)+(*itKS)+"_"+(*it_years)+"_pdf_poly_"+*itPars).c_str(),
														 formula.c_str(),
														 dependents.c_str()
														 );
								}
			  
			}
	}
};
