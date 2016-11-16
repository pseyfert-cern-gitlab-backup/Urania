
include Makefile.arch

TMVA  = -lTMVA 

%.o : %.C
	$(CXX) $(CXXFLAGS) -c -g $<

addbdt12: addBDT12.o
	$(LD) $(LDFLAGS) $^ $(LIBS) $(TMVA) -lMinuit $(OutPutOpt)$@
	@echo "$@ done"

addbdt9: addBDT9.o
	$(LD) $(LDFLAGS) $^ $(LIBS) $(TMVA) -lMinuit $(OutPutOpt)$@
	@echo "$@ done"




# ==========================================
clean: 
	rm -f *.o moni
