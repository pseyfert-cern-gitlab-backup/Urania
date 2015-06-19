//--------------------------------------------------
#include <iostream>
#include "TString.h"
#include "TError.h"
#include "TPad.h"

using namespace std ;

TString goodName(TString name){
 // cout << "goodName : Name input " << name << endl ;
  name.ReplaceAll(" ","_");
  name.ReplaceAll("(","_");
  name.ReplaceAll(")","_");
  name.ReplaceAll("/","_");
  name.ReplaceAll(">","_g_");
  name.ReplaceAll("<","_l_");
  name.ReplaceAll("*","_times_");
  name.ReplaceAll(".","_");
  name.ReplaceAll("[","_");
  name.ReplaceAll("]","_");
  name.ReplaceAll("?","_");
  name.ReplaceAll("{","_");
  name.ReplaceAll("}","_");
  name.ReplaceAll("||","_or_");
  name.ReplaceAll("&&","_and_");
  name.ReplaceAll("&","_");
  name.ReplaceAll("|","_");
  name.ReplaceAll(":","_vs_");
//  cout << "Name output " << name << endl ;
  return name;
}

void makepic(TString name, TString extension="pdf"){
  TString sname = goodName(name);
  gErrorIgnoreLevel = 1001 ;
  if (!gPad){
    cout << "No gPad!" << endl ;
    return ;
  }
  gPad->SaveAs(sname+"."+extension);
}

void eps(TString name){ makepic(name,"eps"); }
void pdf(TString name){ makepic(name,"pdf"); }
void png(TString name){ makepic(name,"png"); }

