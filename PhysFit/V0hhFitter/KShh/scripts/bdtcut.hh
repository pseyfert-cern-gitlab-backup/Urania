#include <iostream>
#include <cstdio>


std::string getBDT(std::string selType, std::string invmass, std::string kshort, std::string year){

  std::string bdt;


  if(selType == "Loose" && invmass == "pipi" && year == "2011"  && kshort == "DD")                    bdt = "myBDT>-0.06";
  if(selType == "Loose" && invmass == "pipi" && year == "2011"  && kshort == "LL")                    bdt = "myBDT>-0.05";
  if(selType == "Loose" && invmass == "pipi" && year == "2012a" && kshort == "DD")                    bdt = "myBDT>0.03";
  if(selType == "Loose" && invmass == "pipi" && year == "2012b" && kshort == "DD")                    bdt = "myBDT>0.01";
  if(selType == "Loose" && invmass == "pipi" && year == "2012a" && kshort == "LL")                    bdt = "myBDT>-0.03";
  if(selType == "Loose" && invmass == "pipi" && year == "2012b" && kshort == "LL")                    bdt = "myBDT>-0.10";

  if(selType == "Loose" && invmass == "KK" && year == "2011"  && kshort == "DD")                      bdt = "myBDT>-0.10";
  if(selType == "Loose" && invmass == "KK" && year == "2011"  && kshort == "LL")                      bdt = "myBDT>-0.17";
  if(selType == "Loose" && invmass == "KK" && year == "2012a" && kshort == "DD")                      bdt = "myBDT> 0.03";
  if(selType == "Loose" && invmass == "KK" && year == "2012b" && kshort == "DD")                      bdt = "myBDT>-0.08";
  if(selType == "Loose" && invmass == "KK" && year == "2012a" && kshort == "LL")                      bdt = "myBDT>-0.06";
  if(selType == "Loose" && invmass == "KK" && year == "2012b" && kshort == "LL")                      bdt = "myBDT>-0.13";

  if(selType == "Tight" && (invmass == "Kpi"||invmass == "piK") && year == "2011"  && kshort == "DD") bdt = "myBDT> 0.03";
  if(selType == "Tight" && (invmass == "Kpi"||invmass == "piK") && year == "2011"  && kshort == "LL") bdt = "myBDT> 0.04";
  if(selType == "Tight" && (invmass == "Kpi"||invmass == "piK") && year == "2012a" && kshort == "DD") bdt = "myBDT> 0.21";
  if(selType == "Tight" && (invmass == "Kpi"||invmass == "piK") && year == "2012b" && kshort == "DD") bdt = "myBDT> 0.10";
  if(selType == "Tight" && (invmass == "Kpi"||invmass == "piK") && year == "2012a" && kshort == "LL") bdt = "myBDT> 0.00";
  if(selType == "Tight" && (invmass == "Kpi"||invmass == "piK") && year == "2012b" && kshort == "LL") bdt = "myBDT> 0.02";

  if(selType == "Tight" && invmass == "pipi" && year == "2011"  && kshort == "DD")                    bdt = "myBDT> 0.12";
  if(selType == "Tight" && invmass == "pipi" && year == "2011"  && kshort == "LL")                    bdt = "myBDT> 0.04";
  if(selType == "Tight" && invmass == "pipi" && year == "2012a" && kshort == "DD")                    bdt = "myBDT> 0.23";
  if(selType == "Tight" && invmass == "pipi" && year == "2012b" && kshort == "DD")                    bdt = "myBDT> 0.18";
  if(selType == "Tight" && invmass == "pipi" && year == "2012a" && kshort == "LL")                    bdt = "myBDT> 0.05";
  if(selType == "Tight" && invmass == "pipi" && year == "2012b" && kshort == "LL")                    bdt = "myBDT> 0.03";

  if(selType == "Tight" && invmass == "KK" && year == "2011"  && kshort == "DD")                      bdt = "myBDT> 0.15";
  if(selType == "Tight" && invmass == "KK" && year == "2011"  && kshort == "LL")                      bdt = "myBDT> 0.05";
  if(selType == "Tight" && invmass == "KK" && year == "2012a" && kshort == "DD")                      bdt = "myBDT> 0.20";
  if(selType == "Tight" && invmass == "KK" && year == "2012b" && kshort == "DD")                      bdt = "myBDT> 0.22";
  if(selType == "Tight" && invmass == "KK" && year == "2012a" && kshort == "LL")                      bdt = "myBDT> 0.05";
  if(selType == "Tight" && invmass == "KK" && year == "2012b" && kshort == "LL")                      bdt = "myBDT> 0.12";

  if(selType == "Loose" && (invmass == "Kpi"||invmass == "piK") && year == "2011"  && kshort == "DD") bdt = "myBDT>-0.02";
  if(selType == "Loose" && (invmass == "Kpi"||invmass == "piK") && year == "2011"  && kshort == "LL") bdt = "myBDT> 0.04";
  if(selType == "Loose" && (invmass == "Kpi"||invmass == "piK") && year == "2012a" && kshort == "DD") bdt = "myBDT> 0.11";
  if(selType == "Loose" && (invmass == "Kpi"||invmass == "piK") && year == "2012b" && kshort == "DD") bdt = "myBDT> 0.07";
  if(selType == "Loose" && (invmass == "Kpi"||invmass == "piK") && year == "2012a" && kshort == "LL") bdt = "myBDT>-0.03";
  if(selType == "Loose" && (invmass == "Kpi"||invmass == "piK") && year == "2012b" && kshort == "LL") bdt = "myBDT>-0.05";

  return bdt;

}
