mean = {'TOS1_0': 498.04106845548836,
        'TOS1_1': 497.98905063860724,
        'TOS1_2': 497.76725841575416,
        'TOS1_3': 497.7881316858459,
        
        'TOS2_3': 497.1886537084609,
        'TOS2_2': 497.76871615096894,
        'TOS2_1': 497.55883895742426,
        'TOS2_0': 498.0175550018635,
        
        'TIS_3': 497.9128932448269,
        'TIS_2': 497.80844119299945,
        'TIS_0': 497.78169766544005,
        'TIS_1': 497.7307522231982}

sigma = {'TOS1_0': 4.426562709205831,
         'TOS1_1': 4.311390738237183,
         'TOS1_2': 3.961812954176075,
         'TOS1_3': 4.280380365124879,
         
         'TOS2_3': 3.4749661737020436,
         'TOS2_2': 3.9109698801911303,
         'TOS2_1': 3.662360924002011,
         'TOS2_0': 3.497087620970315,
         
         'TIS_3': 3.546883771804911,
         'TIS_2': 3.520678511286974,
         'TIS_0': 3.752402247510088,
         'TIS_1': 3.469677957039842}

zeta = {'TOS1_0': 0.6719765161945951,
        'TOS1_1': 0.004743766665449567,
        'TOS1_2': 1.7038462032536952,
        'TOS1_3': 2.0291569466629085,
        
        'TOS2_3': 0.7878025255371977,
        'TOS2_2': 2.6850262168572208,
        'TOS2_1': 1.1478794120425913,
        'TOS2_0': 4.999999999733145,
        
        'TIS_3': 0.13197359386010604,
        'TIS_2': 0.027761324923420982,
        'TIS_0': 1.0523704003398877,
        'TIS_1': 1.664063042211238}
#beta = {}
landa = {'TOS1_0': -1.0000115199019284,
         'TOS1_1': -2.0429205983297356,
         'TOS1_2': -1.0000140639613484,
         'TOS1_3': -1.3237311592254901,
         
         'TOS2_3': -4.873019258799719,
         'TOS2_2': -1.0065615033117599,
         'TOS2_1': -1.0000054878149278,
         'TOS2_0': -1.000120962399901,
         
         'TIS_3': -4.49626641306367,
         'TIS_2': -2.6773794107644333,
         'TIS_0': -2.025432934088295,
         'TIS_1': -1.0002845157132416}

a1 = {'TOS1_0': 3.718066866545949,
      'TOS1_1': 4.143449997868089,
      'TOS1_2': 3.696914891744067,
      'TOS1_3': 3.83645228597557,
      
      'TOS2_3': 5.497405334605182,
      'TOS2_2': 6.942135342935513,
      'TOS2_1': 8.150488298335958,
      'TOS2_0': 5.767560060085151,
      
      'TIS_3': 2.9988625729440437,
      'TIS_2': 4.175239364635054,
      'TIS_0': 4.499452473449249,
      'TIS_1': 2.798035904125543}

n1 = {'TOS1_0': 9.999788406660558,
      'TOS1_1': 0.5000046023756068,
      'TOS1_2': 0.7260264487738525,
      'TOS1_3': 0.500003518473389,
      
      'TOS2_3': 8.980519771678681,
      'TOS2_2': 7.86055089370783,
      'TOS2_1': 0.7693435715095184,
      'TOS2_0': 9.490723353718957,
      
      'TIS_3': 1.7575041536256486,
      'TIS_2': 0.5000000092865624,
      'TIS_0': 0.5000003811106636,
      'TIS_1': 1.6221983520091035}

beta = {}
for key in ["TIS_","TOS1_","TOS2_"]:
    for i in range(100):
        #mean[key + str(i)]= 499. 
        #sigma[key + str(i)] = 5.01
        beta[key + str(i)] = 0.
        #zeta[key + str(i)] =  7e-02
        #landa[key + str(i)] = -2 
