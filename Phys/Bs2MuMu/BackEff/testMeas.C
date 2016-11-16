/*

    
  Author: Francesco Dettori 
  Date:   December 2012
  

*/

#include <iostream>
#include <fstream>

#include "Measurement.h" 

void testMeasurement(Measurement a, Measurement b, bool debug=false){
  cout << "a = " << a << endl
       << "b = " << b << endl;
  Measurement c = a+b;
  cout << "a + b = " << c << endl;
  c = a - b;
  cout << "a - b = " << c << endl;
  c = a * b ;
  cout << "a * b = " << c << endl;
  c = a / b;
  cout << "a / b = " << c << endl;
  c = a.average(b);
  cout << "average of a and b = " << c << endl;
  
  c+=a;
  cout << "c+=a ,  c = " << c <<endl;
  
  double k = 3.0;
  cout << "k = " << k << endl;
  cout << " a*k = " << a * k << endl;
  cout << " a*k = " << k * a << endl;
  a += k;
  cout << " a+=k, a = " << a << endl;
  

  if(debug){
    cout << a.tex() << endl;
    a.debug();
    cout << b.tex() << endl;
    b.debug();
    cout << c.tex() << endl;
    c.debug();
  }

}



using namespace std;
//============================================================
// MAIN 
int main(int argc, char **argv)
{
  //  welcome();
  
  Measurement a(5,2);
  Measurement b(6,1);
  cout << endl <<" Test simple measurements " << endl;
  testMeasurement(a,b,1);


  cout << endl << " Test asymmetric measurements " << endl;
  // Test of asymmetric measurement 
  Measurement d1 = Measurement::AMeasurement(5,1,2);
  Measurement d2 = Measurement::AMeasurement(6,0.1,0.2);
  testMeasurement(d1,d2,1);

  cout << endl << " Test normal versus asymmetric measurements " << endl;
  Measurement e1(5,1);
  Measurement e2 = Measurement::AMeasurement(6,0.1,0.2);
  testMeasurement(e1,e2,1);

  cout << endl << " Test stat and syst errors " << endl;
  Measurement k = Measurement::SMeasurement(5,1,2);
  Measurement l = Measurement::SMeasurement(6,0.1,0.2);
  testMeasurement(k,l,1);

  cout << endl << " Test normal versus stat and syst errors " << endl;
  Measurement p(5,1);
  Measurement q = Measurement::SMeasurement(6,0.1,0.2);
  testMeasurement(p,q,1);



  cout << endl << " Test asymmetric stat and syst errors " << endl;
  Measurement m(5, 0.2, 0.1, 0.3,0.1);
  Measurement n(2, 0.2, 0.1, 0.3,0.1);
  testMeasurement(m,n,1);


  cout << endl << " Test efficiency variable " << endl;
  Measurement eff = Measurement::Efficiency(0.99, 2000);
  Measurement eff2 = Measurement::GetEfficiency(20, 4000);
  testMeasurement(eff, eff2);

  cout << "the end" << endl;


}


