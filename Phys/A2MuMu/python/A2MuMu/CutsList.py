e = "&&"
TriggerDecisions='V0_l0phys_dec==1 && V0_l1phys_dec==1 && V0_l2phys_dec==1'
PreSelectionCut = 'PIDmu1>0. && PIDmu2>0. && PIDk1<10. && PIDk2<10. && log10(Blife_ps)<-1.'

PreSelection = PreSelectionCut+e+TriggerDecisions


truthMatching = {
              'Y' :  'mc1==-13 && mc2==13 && mo1==553 && mo2==553',
              'A' :  'mc1==-13 && mc2==13 && mo1==36 && mo2==36',
              }


