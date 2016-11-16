#include <iostream>
using namespace std;

typedef Double_t (*IntFunctionWithOneParameter) (Double_t b);

Double_t function1(Double_t a){ return a; }
Double_t functionTimesTwo(Double_t a){ return a*2; }
Double_t functionDivideByTwo(Double_t a){ return a/2; }

int main()
{
    IntFunctionWithOneParameter functions[] = {function1,functionTimesTwo,functionDivideByTwo};

    for(int i = 0; i < 3; ++i){cout << functions[i](8) << endl;}

    return 1.;

}
