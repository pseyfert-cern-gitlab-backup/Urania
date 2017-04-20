bkg_TOSA = [2.0417486942769583, 0.96621259573219054, 0.22661552817230668, 0.23372795473266716, 0.32395166564186456, 0.17291788039439288, 0.14897716390374083, 0.47137062648403916, 0.0021655358911720768, 0.67740756921980116]
bkg_TOSB = [1.6505608878849158, 1.0663438928460929, 0.42138143544254436, 0.39714584217267146, 0.30581062264863768, 0.0094121611362196766, 0.019611035243595087, 0.83674484757307832, 0.009634675636172263, 0.023961312378066868]
bkg_TISA =[3.1539571162946696, 1.1693954263868309, 2.2078212486508626, 1.3205068425953814, 1.1370849978247177, 0.17910024727574303, 0.00066437472163433098, 0.17853951938967771, 2.6763411062891151e-05, 8.7197889676815521e-05]
bkg_TISB = [0.52913551421568572, 2.5662321283779308, 0.79399913527150701, 0.4633633584739475, 0.35641862533630997, 1.0710606735960353, 0.10503234791718125, 0.01149479704724754, 0.23062803867363491, 0.2171103218899102]



for i in range(10):
    vars()["ATISbin" + str(i+1)] = [bkg_TISA[i]]
    vars()["BTISbin" + str(i+1)] = [bkg_TISB[i]]
    vars()["ATOSbin" + str(i+1)] = [bkg_TOSA[i]]
    vars()["BTOSbin" + str(i+1)] = [bkg_TOSB[i]]
    