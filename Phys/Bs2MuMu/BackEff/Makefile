include Makefile.arch

ROOFIT = -lRooFit -lRooFitCore -lFoam


%.o : %.C
	$(CXX) $(CXXFLAGS) -c -g $<

backEff: backEff.o Measurement.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lTreePlayer -lMinuit $(ROOFIT) $(OutPutOpt)$@
	@echo "$@ done"

testMeas: testMeas.o Measurement.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(OutPutOpt)$@
	@echo "$@ done"

genEff: genEff.o Measurement.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(OutPutOpt)$@
	@echo "$@ done"

fsfdcomb: fsfdComb.o Measurement.o 
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(OutPutOpt)$@
	@echo "$@ done"

fitshape: fitShape.o Measurement.o  DrawUtils.o RooPhysBkg.o RooExpAndGauss.o RooExpAndGaussInv.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit $(ROOFIT) $(OutPutOpt)$@
	@echo "$@ done"

avmisid: averageMisID.o Measurement.o  
	$(LD) $(LDFLAGS) $^ $(LIBS) -lMinuit  $(OutPutOpt)$@
	@echo "$@ done"

testMass: testMassShape.o Measurement.o RooPhysBkg.o
	$(LD) $(LDFLAGS) $^ $(LIBS) -lTreePlayer -lMinuit $(ROOFIT) $(OutPutOpt)$@
	@echo "$@ done"

Measurement.o: Measurement.cpp Measurement.h

DrawUtils.o: DrawUtils.cpp DrawUtils.h

RooPhysBkg.o: RooPhysBkg.C RooPhysBkg.h

RooExpAndGauss.o: RooExpAndGauss.C RooExpAndGauss.h

RooExpAndGaussInv.o: RooExpAndGaussInv.C RooExpAndGaussInv.h

# ==========================================
clean: 
	rm -f *.o moni
