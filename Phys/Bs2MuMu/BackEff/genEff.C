/*

    
  Author: Francesco Dettori 
  Date:   December 2012
  

*/

#include <iostream>
#include <fstream>

#include "Measurement.h" 

using namespace std;

Measurement average(double ed, double ederr,
             double edb, double edberr,
             double eu, double euerr, 
             double eub, double euberr){
  Measurement eff_down(ed, ederr);
  Measurement eff_down_b(edb, edberr);
  Measurement eff_up(eu, euerr);
  Measurement eff_up_b(eub, euberr);
  
  Measurement eff_down_av = eff_down.average(eff_down_b);
  Measurement eff_up_av = eff_up.average(eff_up_b);
  cout << "average down eff " << eff_down_av << endl;
  cout << "average up eff " << eff_up_av << endl;
  cout << "average  eff " << eff_down_av.average(eff_up_av) << endl;
  return eff_down_av.average(eff_up_av);
  
  }

Measurement  average(double ed, double ederr,
             double eu, double euerr){
  Measurement eff_down(ed, ederr);
  Measurement eff_up(eu, euerr);
  Measurement av = eff_down.average(eff_up);
  
  cout << "average  eff " << av <<  " " << av.tex() << endl;
  return av;
}
  
//============================================================
// MAIN 
int main(int argc, char **argv)
{
  //  welcome();
  cout << "Lambdab -> p k " << endl;
  average(0.1829,0.001340,
          0.1865, 0.001383,
          0.1819,  0.001340,
          0.1864 , 0.001388);
  
  cout << endl << "Lambda b-> p pi" << endl;
  
  average(0.1843 	, 0.001333, 	0.1820, 0.001366,
          0.1817 	,    0.001328,0.1830 ,0.001371);
  

  cout << endl << "Lambda b-> p mu nu" << endl;
  average(0.0287 ,	  0.000231,0.0293, 0.000240,
          0.0290 ,	 0.000231 	, 0.0294,0.000239);
  

  cout << endl << "Bd K pi MC10 " << endl;
  Measurement bdkpi10 =   average(0.1769, 0.001136,
                                  0.1780, 0.001548);
  Measurement bsmumu10( 0.1747 , 0.000426);
  cout << " Ratio bkpi bsmumu 10 =" <<bdkpi10/bsmumu10 <<endl;
  
  Measurement bdkpi12 = average(0.1821,  0.000912,
                                0.1794, 0.000938);
  Measurement bsmumu12(0.1775,0.000932);
  cout << " Ratio bkpi bsmumu 12 = " << bdkpi12/bsmumu12 << endl;
  
  Measurement bdpimunu = average(0.0082,  0.001040, 
                                 0.0065,  0.000926, 
                                 0.0064, 0.000052,
                                 0.0065,  0.000052);
  


  cout << "Bd pimunu eff = " << bdpimunu << endl;
  

  cout << "the end" << endl;


}


