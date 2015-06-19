#include "data.h"
#include "cuts.h"
#include "plots.h"
#include "scan.h"

void info(char *args[]);
void banner();
void help(char *args[]);

int main(int argc, char *argv[]) 
{
	banner();
	if(argc != 4 ){	help(argv);	return EXIT_FAILURE;}
	info(argv);
	
	std::string weightListName = argv[1];
	std::string cutListName = argv[2];
	//const unsigned int maxIters = atoi(argv[3]);
	std::string outname = argv[3];

	std::cout<<"data:	" << std::endl;

	data* tuples=new data(weightListName);

	tuples->print();
	
	std::cout<<"cuts:	" << std::endl;
	
	cuts* mycuts=new cuts(cutListName);
	
	//mycuts->print(tuples);
	//mycuts->print();
	
	//std::cout<<"arranged:	" << std::endl;
	
	mycuts->arrangeList(tuples);
	
	//mycuts->print(tuples);
	mycuts->print();
	
	plots* outputPlots = new plots(outname);
  outputPlots->stacked(false);
  
	
	std::cout<<"Input:	" << std::endl;
	std::cout<<"------------------------------------------------" << std::endl;
	
	scan* myscan=new scan(tuples,mycuts,outputPlots);

	char ip='n';

	std::cout << "Q. Use custom S/B calculation? y/[n] " ;
	std::cin>>ip;
  
  
	if(ip=='y' or ip=='Y')
  {
    myscan->setCustom(true);
    ip='n';
  }
	
	myscan->stats();
	std::cout<<"------------------------------------------------" << std::endl;
	

	outputPlots->mkdir("Input");
	std::cout << "Plotting initial data." << std::endl;;
	//std::cin>>ip;
	//if(ip=='y' or ip=='Y')
	//  {    
	//    ip='n';
	myscan->PlotAllClever("Input");
	//  }
	
	std::cout << "To speed up later running, all cuts will now be cached. " << std::endl;;
	myscan->StatsScan("Input",true);
	myscan->stats();
	//std::cout << "Q. Run initial stats scan on these data? y/[n] " ;
	//std::cin>>ip;
	//if(ip=='y' or ip=='Y')
	//  {    
	//    ip='n';
	//    std::cout << "-q. Cache all cuts? (will hopefully speed up later running) y/[n] " ;
	//    std::cin>>ip;
	//    myscan->StatsScan("Input",(ip=='y' or ip=='Y'));
	//    ip='n';
	//  }
	
	std::cout << "Q. Find 100% cuts on these data? y/[n] " ;
	std::cin>>ip;
	if(ip=='y' or ip=='Y')
  {    
    ip='n';
    std::cout << "-q. Add stats scan with 100pc? y/[n] " ;
    std::cin>>ip;
    myscan->Select100pc();
    myscan->stats();
    if(ip=='y' or ip=='Y')
    {
      outputPlots->mkdir("100pcSelection");
      myscan->StatsScan("100pcSelection");
      myscan->PlotAllClever("100pcSelection");
      myscan->stats();
    }
	    
  }
	
	std::cout << "Q. Run rate scan on these data? y/[n] " ;
	std::cin>>ip;
	if(ip=='y' or ip=='Y')
  {
    ip='n';
    std::cout << "-q. Add stats scans/plots at key points? y/[n] " ;
    std::cin>>ip;
    myscan->RateScan(ip=='y'|| ip=='Y');
    myscan->stats();
    ip='n';
  }
  
	std::cout << "Q. goto specific location? y/[n] " ;
	std::cin>>ip;
	if(ip=='y' or ip=='Y')
  {
    ip='n';
    myscan->ChooseCuts();    
    std::cout << "Q. Run stats scan on these data? y/[n] " ;
    std::cin>>ip;
    if(ip=='y' or ip=='Y')
    {    
      outputPlots->mkdir("Chosen");
      ip='n';
      myscan->StatsScan("Chosen");
      myscan->PlotAllClever("Chosen");
    }
    
  }
	
	std::cout << "Q. Optimise cuts on these data? y/[n] " ;
	std::cin>>ip;
	if(ip=='y' or ip=='Y')
  {
    ip='n';
    while(ip=='n')
    {
      std::cout << "-q. Optimise by S/sqrt(S+B), S/B or B/S? r/s/b " ;
      std::cin>>ip;
      if(ip!='r'&& ip!='s' && ip!='b' && (ip!='c'||!myscan->custom())) ip='n';
    }
    int maxIters=0;
    std::cout << "-q. Maximum iterations? " ;
    std::cin>>maxIters;
    myscan->ScanForBest(maxIters, ip);
    ip='n';
  }
  
	std::cout << "Q. goto specific location? y/[n] " ;
	std::cin>>ip;
	if(ip=='y' or ip=='Y')
  {
    ip='n';
    myscan->ChooseCuts();    
  }
  
	std::cout << "Q. Run final stats scan on these data? y/[n] " ;
	std::cin>>ip;
	if(ip=='y' or ip=='Y')
  {    
    outputPlots->mkdir("Final");
    ip='n';
    myscan->StatsScan("Final");
    myscan->PlotAllClever("Final");
  }
	
	
	delete myscan; myscan=NULL;
	delete tuples; tuples=NULL;
	delete outputPlots; outputPlots=NULL;
	delete mycuts; mycuts=NULL;
	
	
	return 0;
	
	

}

void info(char *args[]){
	cout<<"Initialisation:	" << endl;
	cout<<"	optimising cuts:	" << args[2]	<< endl;
	cout<<"	using ntuples in file:	" << args[1]	<< endl;
	cout<<"	output file:	" << args[3]	<< endl;

	cout << ""  << endl;
}

void banner(){
	cout << "MoreSimpleTools cut interactive optimisation and rate-scan tool "<< endl;
	cout << ""  << endl;
}

void help(char *args[]){
	cout<<	" Syntax: 		" << args[0] <<" <weightfile.list> <cutfile.list> <output.root>"<< endl;
	cout<<	" Cutfile Syntax:	<cut> <lower bound> <upper bound> <resolution>" << endl;
	cout<<	" Weightfile Syntax:	<B/S> <name> <filename.root> <path/to/ntuple> <weight> " << endl;
	cout<< ""  << endl;

	cout<< "see ../examples/*.txt for examples"  << endl;
	cout<< "" <<endl;
}

