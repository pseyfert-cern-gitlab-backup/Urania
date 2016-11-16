

# change the output file name 
from fitResBsmy_OutputTag_sets import *



parList= ['ACPLBs','ACPSBs','ACPpaBs','ACPpeBs','fLBs','fpaBs','dpaBs','dpeBs','As2Bs_826_861','dsBs_826_861','As2Bs_861_896', 'dsBs_861_896','As2Bs_896_931','dsBs_896_931', 'As2Bs_931_966','dsBs_931_966']


parName= ['\ACPL','\ACPS','\ACPpa','\ACPpe','$f_{0}$','$f_{\parallel}$','$\delta_{\parallel}$','$\delta_{\perp}$','\AsBinZero','\dsBinZero','\AsBinOne', '\dsBinOne','\AsBinTwo','\dsBinTwo', '\AsBinThree','\dsBinThree']


for i in range(0,16): 
   
    if "d" in parName[i]:

        if (abs(round(fitRes_Exp888_ErrorHigh[parList[i]],2))==abs(round(fitRes_Exp888_ErrorLow[parList[i]],2))):

            if (fitRes_Exp888[parList[i]]>0):

                print parName[i],"& $\phantom{-}%.2f \pm %.2f$ \\\\"%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]])

            else:

                print parName[i],"& $%.2f \pm %.2f$ \\\\"%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]])
        
        elif (abs(round(fitRes_Exp888_ErrorHigh[parList[i]],2))!=abs(round(fitRes_Exp888_ErrorLow[parList[i]],2))):

            if (fitRes_Exp888[parList[i]]>0):
                
                print parName[i],"& $\phantom{-}%.2f^{+%.2f}_{%.2f}$  \\\\"%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]],fitRes_Exp888_ErrorLow[parList[i]])

            else:

                print parName[i],"& $%.2f^{+%.2f}_{%.2f}$  \\\\"%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]],fitRes_Exp888_ErrorLow[parList[i]])
                


    else: 

        if (abs(round(fitRes_Exp888_ErrorHigh[parList[i]],3))==abs(round(fitRes_Exp888_ErrorLow[parList[i]],3))):
            if (fitRes_Exp888[parList[i]]>0):
                print parName[i],"& $\phantom{-}%.3f \pm %.3f$  \\\\ "%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]])
            else:
                print parName[i],"& $%.3f \pm %.3f$  \\\\ "%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]])
        

        elif (abs(round(fitRes_Exp888_ErrorHigh[parList[i]],3))!=abs(round(fitRes_Exp888_ErrorLow[parList[i]],3))):

            if (fitRes_Exp888[parList[i]]>0):

                print parName[i],"& $\phantom{-}%.3f^{+%.3f}_{%.3f}$  \\\\ "%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]],fitRes_Exp888_ErrorLow[parList[i]])
                
            else:
                
                print parName[i],"& $%.3f^{+%.3f}_{%.3f}$  \\\\ "%(fitRes_Exp888[parList[i]],fitRes_Exp888_ErrorHigh[parList[i]],fitRes_Exp888_ErrorLow[parList[i]])
                
        
    if (i==3 or i==7 or i==15):
          print "\hline"


