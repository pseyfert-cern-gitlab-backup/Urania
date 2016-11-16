#include <iostream>
#include <cstdio>


std::string getPID(std::string moth, std::string invmass, std::string kshort, std::string year){

  std::string  pidcut = "";
  if(year == "2012a" || year == "2012b") year = "2012";
    
  if(moth == "Loose" && invmass == "pipi" && year == "2011" && kshort == "DD")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.20)&&(h2_PROBNNpi>h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "pipi" && year == "2011" && kshort == "LL")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.25)&&(h2_PROBNNpi>h2_PROBNNK+0.25)";
  if(moth == "Loose" && invmass == "pipi" && year == "2012" && kshort == "DD")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.20)&&(h2_PROBNNpi>h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "pipi" && year == "2012" && kshort == "LL")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.25)&&(h2_PROBNNpi>h2_PROBNNK+0.25)";
  
  if(moth == "Tight" && invmass == "pipi" && year == "2011" && kshort == "DD")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.25)&&(h2_PROBNNpi>h2_PROBNNK+0.25)";
  if(moth == "Tight" && invmass == "pipi" && year == "2011" && kshort == "LL")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.35)&&(h2_PROBNNpi>h2_PROBNNK+0.35)";
  if(moth == "Tight" && invmass == "pipi" && year == "2012" && kshort == "DD")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.22)&&(h2_PROBNNpi>h2_PROBNNK+0.22)";
  if(moth == "Tight" && invmass == "pipi" && year == "2012" && kshort == "LL")  pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.35)&&(h2_PROBNNpi>h2_PROBNNK+0.35)";


  if(moth == "Loose" && invmass == "KK" && year == "2011" && kshort == "DD")    pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.20)&&(h2_PROBNNpi<h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "KK" && year == "2011" && kshort == "LL")    pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.25)&&(h2_PROBNNpi<h2_PROBNNK+0.25)";
  if(moth == "Loose" && invmass == "KK" && year == "2012" && kshort == "DD")    pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.20)&&(h2_PROBNNpi<h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "KK" && year == "2012" && kshort == "LL")    pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.25)&&(h2_PROBNNpi<h2_PROBNNK+0.25)";

  if(moth == "Tight" && invmass == "KK" && year == "2011" && kshort == "DD")    pidcut = "(h1_PROBNNpi<h1_PROBNNK-0.03)&&(h2_PROBNNpi<h2_PROBNNK-0.03)";
  if(moth == "Tight" && invmass == "KK" && year == "2011" && kshort == "LL")    pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.00)&&(h2_PROBNNpi<h2_PROBNNK+0.00)";
  if(moth == "Tight" && invmass == "KK" && year == "2012" && kshort == "DD")    pidcut = "(h1_PROBNNpi<h1_PROBNNK-0.02)&&(h2_PROBNNpi<h2_PROBNNK-0.02)";
  if(moth == "Tight" && invmass == "KK" && year == "2012" && kshort == "LL")    pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.00)&&(h2_PROBNNpi<h2_PROBNNK+0.00)";
  
  if(moth == "Tight" && invmass == "Kpi" && year == "2011" && kshort == "DD")   pidcut = "(h1_PROBNNpi<h1_PROBNNK-0.03)&&(h2_PROBNNpi>h2_PROBNNK+0.25)";
  if(moth == "Tight" && invmass == "Kpi" && year == "2011" && kshort == "LL")   pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.00)&&(h2_PROBNNpi>h2_PROBNNK+0.35)";
  if(moth == "Tight" && invmass == "Kpi" && year == "2012" && kshort == "DD")   pidcut = "(h1_PROBNNpi<h1_PROBNNK-0.02)&&(h2_PROBNNpi>h2_PROBNNK+0.22)";
  if(moth == "Tight" && invmass == "Kpi" && year == "2012" && kshort == "LL")   pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.00)&&(h2_PROBNNpi>h2_PROBNNK+0.35)";

  if(moth == "Tight" && invmass == "piK" && year == "2011" && kshort == "DD")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.25)&&(h2_PROBNNpi<h2_PROBNNK-0.03)";
  if(moth == "Tight" && invmass == "piK" && year == "2011" && kshort == "LL")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.35)&&(h2_PROBNNpi<h2_PROBNNK+0.00)";
  if(moth == "Tight" && invmass == "piK" && year == "2012" && kshort == "DD")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.22)&&(h2_PROBNNpi<h2_PROBNNK-0.02)";
  if(moth == "Tight" && invmass == "piK" && year == "2012" && kshort == "LL")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.35)&&(h2_PROBNNpi<h2_PROBNNK+0.00)";
  
  if(moth == "Loose" && invmass == "Kpi" && year == "2011" && kshort == "DD")   pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.20)&&(h2_PROBNNpi>h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "Kpi" && year == "2011" && kshort == "LL")   pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.25)&&(h2_PROBNNpi>h2_PROBNNK+0.25)";
  if(moth == "Loose" && invmass == "Kpi" && year == "2012" && kshort == "DD")   pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.20)&&(h2_PROBNNpi>h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "Kpi" && year == "2012" && kshort == "LL")   pidcut = "(h1_PROBNNpi<h1_PROBNNK+0.25)&&(h2_PROBNNpi>h2_PROBNNK+0.25)";

  if(moth == "Loose" && invmass == "piK" && year == "2011" && kshort == "DD")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.20)&&(h2_PROBNNpi<h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "piK" && year == "2011" && kshort == "LL")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.25)&&(h2_PROBNNpi<h2_PROBNNK+0.25)";
  if(moth == "Loose" && invmass == "piK" && year == "2012" && kshort == "DD")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.20)&&(h2_PROBNNpi<h2_PROBNNK+0.20)";
  if(moth == "Loose" && invmass == "piK" && year == "2012" && kshort == "LL")   pidcut = "(h1_PROBNNpi>h1_PROBNNK+0.25)&&(h2_PROBNNpi<h2_PROBNNK+0.25)";

  
  return pidcut;
  
}
