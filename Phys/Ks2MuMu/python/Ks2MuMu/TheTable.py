from ipa_params import *
Blinding = "GRAPPA"
alpha, s_alpha_corr, s_alpha_uncorr = {}, {}, {}
# alpha is normalization factor, s_alpha is its error
from math import *

#------ SIGNAL MASS SHAPE SYSTEMATIC -------
TrackingSyst  = 0.4/100
SelectionSyst = { 'TOS1_': 1.9/100, 'TOS2_': 1.8/100}
TriggerSyst   = { 'TOS1_': 8.0/100, 'TOS2_': 11./100}
MuIDSyst      = { 'TOS1_': 0.2/100, 'TOS2_': 0.3/100}
KspectrumSyst = 4.3/100
SigShapeSyst  = 0.8/100

#------ NORMALIZATION FACTOR WITHOUT MUONID -------
TOS1_N=[7.368078409770543e-10, 7.598363016500101e-10, 7.752715245584159e-10, 7.800820262188811e-10, 7.420562324051509e-10, 7.652433938178411e-10, 7.464889117358329e-10, 7.792816477068047e-10, 7.696239724215666e-10, 7.650884816179239e-10]
s_TOS1_N_corr=[1.5557365904797635e-11, 1.678620170285612e-11, 1.7728918757353194e-11, 1.8893640131159053e-11, 1.7838399747090352e-11, 1.8534998816524535e-11, 1.8580836206024027e-11, 1.837991293127285e-11, 1.7978458366151075e-11, 1.6502157963428064e-11]
s_TOS1_N_uncorr=[8.283412423497202e-11, 8.554675203718213e-11, 8.73588179681011e-11, 8.792878518266718e-11, 8.346919757608545e-11, 8.618626133323587e-11, 8.399200788359843e-11, 8.784058270363437e-11, 8.672858445427472e-11, 8.614248593661135e-11]

TOS2_N=  [5.16433413193391e-09, 4.600653113892022e-09, 4.772134473579286e-09, 4.546010578482746e-09, 4.5336714142031425e-09, 4.81054877076096e-09, 4.515087608278994e-09, 4.880322838377314e-09, 4.620545354825601e-09, 4.558575797670084e-09]
s_TOS2_N_corr= [1.1327786922261585e-10, 1.0108208245008334e-10, 1.0460675880783428e-10, 1.0000809974747509e-10, 9.766138100068554e-11, 1.0743286930908935e-10, 9.936314305036473e-11, 1.0831559568454132e-10, 1.0556223291521452e-10, 1.0522224982375912e-10]
s_TOS2_N_uncorr=[6.986788900145599e-10, 6.114464808323011e-10, 6.36342410496768e-10, 6.023716217888852e-10, 5.985912942198764e-10, 6.439584325371528e-10, 5.979367873787947e-10, 6.560485962354351e-10, 6.15446883766349e-10, 6.059749131038127e-10]


#TIS_N=   [2.3428658118705624e-08, 2.4549278973303556e-08, 2.6306119000932476e-08, 2.634534625196316e-08, 2.7864988890280793e-08, 2.807242191861938e-08, 3.128291783391773e-08, 3.221105089559449e-08, 3.609296385475157e-08, 4.297884923073403e-08]
#s_TIS_N_corr=    [1.0134415930230457e-09, 1.096717193647688e-09, 1.221719123397519e-09, 1.2663668423764527e-09, 1.3799414095224827e-09, 1.403473741441469e-09, 1.6139914185578034e-09, 1.6883361546798248e-09, 1.917800063316105e-09, 2.432623231505185e-09]
#s_TIS_N_uncorr=    [1.2186838590214575e-09, 1.278620557829052e-09, 1.372640670641778e-09, 1.3752413325761509e-09, 1.456688839279808e-09, 1.4679973753471953e-09, 1.6406606834320418e-09, 1.6909605725090855e-09, 1.9015349788253386e-09, 2.2795682653859954e-09]

#print [i*10**(8) for i in TIS_N]
#print [i*10**(8) for i in s_TIS_N_corr]
#print [i*10**(8) for i in s_TIS_N_uncorr]

#------ MUONID-------  

TOS1_muonID =   [0.985, 0.984, 0.987, 0.984, 0.985, 0.983, 0.988, 0.986, 0.985, 0.987]
s_TOS1_muonID = [0.005, 0.005, 0.005, 0.005, 0.005, 0.007, 0.004, 0.004, 0.005, 0.005]


TOS2_muonID =   [0.975, 0.976, 0.977, 0.975, 0.975, 0.971, 0.981, 0.977, 0.978, 0.978]
s_TOS2_muonID = [0.005, 0.005, 0.005, 0.005, 0.005, 0.007, 0.004, 0.004, 0.005, 0.005]

#TIS_muonID = [92.8e-02,92.8e-02,92.8e-02,93.4e-02,93.3e-02,93.1e-02,93.2e-02,93.6e-02,93.7e-02,93.9e-02]
#s_TIS_muonID = [0.9e-02,0.9e-02,0.9e-02,0.7e-02,0.7e-02,0.8e-02,0.7e-02,0.7e-02,0.6e-02,0.6e-02]


#------------GLOBAL NORMALIZATION FACTOR

TOS1 = [i/j for i,j in zip(TOS1_N,TOS1_muonID)]
s_TOS1_uncorr = [i*sqrt(((j**2)/(k**2))+((l**2)/(m**2))) for i,j,k,l,m in zip(TOS1,s_TOS1_muonID,TOS1_muonID,s_TOS1_N_uncorr,TOS1_N)]
s_TOS1_corr = [i*sqrt((j**2)/(k**2)) for i,j,k in zip(TOS1,s_TOS1_N_corr,TOS1_N)]

TOS2 = [i/j for i,j in zip(TOS2_N,TOS2_muonID)]
s_TOS2_uncorr = [i*sqrt(((j**2)/(k**2))+((l**2)/(m**2))) for i,j,k,l,m in zip(TOS2,s_TOS2_muonID,TOS2_muonID,s_TOS2_N_uncorr,TOS2_N)]
s_TOS2_corr =[i*sqrt((j**2)/(k**2)) for i,j,k in zip(TOS2,s_TOS2_N_corr,TOS2_N)]

#TIS = [i/j for i,j in zip(TIS_N,TIS_muonID)]
#s_TIS_uncorr = [i*sqrt(((j**2)/(k**2))+((l**2)/(m**2))) for i,j,k,l,m in zip(TIS,s_TIS_muonID,TIS_muonID,s_TIS_N_uncorr,TIS_N)]
#s_TIS_corr =[i*sqrt((j**2)/(k**2)) for i,j,k in zip(TIS,s_TIS_N_corr,TIS_N)]

#for i,j,k in zip(TIS,s_TIS_uncorr,s_TIS_corr):
#    print i, "$\pm$ ", j, "$\pm$ ", k  

#print TOS1, s_TOS1_uncorr,s_TOS1_corr

## Now dummy numbers
for i in range(10):
    ix = str(i)
    #alpha["TIS_" + ix ]= TIS[i]
    #s_alpha_corr["TIS_" + ix]=s_TIS_corr[i]
    #s_alpha_uncorr["TIS_" + ix]=s_TIS_uncorr[i]

    alpha["TOS1_" + ix ]= TOS1[i]
    s_alpha_corr["TOS1_" + ix ]=s_TOS1_corr[i]
    s_alpha_uncorr["TOS1_" + ix ]=s_TOS1_uncorr[i]

    alpha["TOS2_" + ix] = TOS2[i]
    s_alpha_corr["TOS2_" + ix] = s_TOS2_corr[i]
    s_alpha_uncorr["TOS2_" + ix] = s_TOS2_uncorr[i]   

