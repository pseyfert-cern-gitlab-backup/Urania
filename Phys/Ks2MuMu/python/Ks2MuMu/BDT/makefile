ROOTOPTS=`root-config --cflags --libs` -lEG -lHtml -lTMVA
BASICINSTR=g++ -O2 -m64

CreateBDT: CreateBDT.cpp
	$(BASICINSTR) -I$(PWD) $(ROOTOPTS) $< -o $@
