// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Generate code for list of Observables
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################


// ####################################################################################################
// *** Load Useful Classes ***

#include <iostream>
#include <fstream>
#include <sstream>


// *** Main Function *** //
///////////////////////////


int main(int argc, char* argv[]){

  // Decode Arguments
	if(argc!=3){
	  std::cout << "     ERROR: incorrect arguments given. Should be: [init|slim|fill] filename" << std::endl;
		return -1;
  }
	std::string setting = argv[1];

  // Open file
  std::ifstream theFile(argv[2]);

  if( !theFile.good() ){
    std::cout << "     ERROR in opening file " << argv[2] << std::endl;
    return 1;
  }
	std::cout << "     Reading File: " << argv[2] << std::endl;

  // Initialize
  char theLine[100];
  theLine[0] = 0;
  char theWord[100];
  theWord[0] = 0;	

  // Read and print
  while(theFile){ // So far we did not encounter eof
    theFile.getline(theLine,100); // read another line
    // Did we just read End of file?
    if(theFile.eof()) break; // Stop at end of file
		
    // Reread buffer to get the first word
    std::istringstream theStream(theLine);
		theStream >> theWord;
    if(setting=="init"){
      if(theWord[2]==0){
				continue;
			}	
  		std::cout << "   fChain->SetBranchAddress(\"" << theWord << "\", &" << theWord << ", &b_" << theWord << ");" << std::endl;
		} else if(setting=="slim"){
		  if(theWord[2]==0){
			  std::cout << "  " << theLine << std::endl;
				continue;
			}
		  std::cout << "  Double_t my" << theWord << " = -999; outtree.Branch(\"" << theWord << "\", &my" << theWord << ",\"b_" << theWord << "/D\");" << std::endl;
		} else if(setting=="fill"){
		  if(theWord[2]==0){
			  std::cout << "    " << theLine << std::endl;
				continue;
			}	
  		std::cout << "    my" << theWord << " = ntuple->" << theWord << ";" << std::endl;					
    }
  } 

  return 0;
}

