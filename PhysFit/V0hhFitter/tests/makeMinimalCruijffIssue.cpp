#include "V0hhFitter/RooCruijff.h"
#include "V0hhFitter/RooCruijffSimple.h"

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "TFile.h"

int main( int argc, char* argv[] )
{
	bool doCruijff(true);
	if ( argc > 1 ) {
		const std::string option( argv[1] );
		const int optionint = std::stoi( option );
		if ( optionint == 0 ) {
			doCruijff = false;
		} else {
			doCruijff = true;
		}
	}

	RooRealVar X("X","",0.,-1.,1.);
	RooRealVar mu("mu","",0.,-0.1,0.1);
	RooRealVar sig("sig","",1.,0.1,5.);
	RooRealVar alpha0("alpha0","",1.,0.1,5.);
	RooRealVar alpha1("alpha1","",1.,0.1,5.);

	RooCruijffSimple pdf1("pdf1","",X,mu,sig,alpha0,alpha1);
	RooGaussian pdf2("pdf2","",X,mu,sig);

	RooWorkspace *w = new RooWorkspace("w");
	if ( doCruijff ) {
		w->import(pdf1);
	} else {
		w->import(pdf2);
	}

	TFile *f = TFile::Open("dummy.root","RECREATE");
	w->Write();
	f->Close();
	delete w;

	f = TFile::Open("dummy.root","READ");
	w = (RooWorkspace*) f->Get("w");
	RooAbsPdf *readPdf(0);
	if ( doCruijff ) {
		readPdf = w->pdf("pdf1");
	} else {
		readPdf = w->pdf("pdf2");
	}

	if (readPdf == NULL) {
		std::cout <<"ERROR: The pdf has not been written..." << std::endl;
	} else {
		std::cout <<"INFO: We got it."<< std::endl;
	}

	return 0;
}
