WeightsBd = {}
WeightsBd['2012p_896_931'] =  {'0S': -0.6842, '0pa': -0.0018, 'paS': -0.0015, '0pe': -0.0006, 'SS': 1.0557, 'pepe': 1.2258, 'papa': 1.2252, '00': 0.8491, 'peS':  0.0005, 'pape': -0.0004}
WeightsBd['2012n_931_966'] =  {'0S': -0.6185, '0pa':  0.0010, 'paS': -0.0017, '0pe': -0.0009, 'SS': 1.0620, 'pepe': 1.2382, 'papa': 1.2373, '00': 0.8422, 'peS':  0.0012, 'pape':  0.0001}
WeightsBd['2012n_861_896'] =  {'0S': -0.7138, '0pa': -0.0007, 'paS': -0.0006, '0pe':  0.0006, 'SS': 1.0579, 'pepe': 1.2137, 'papa': 1.2147, '00': 0.8572, 'peS':  0.0003, 'pape':  0.0009}
WeightsBd['2011n_861_896'] =  {'0S': -0.7138, '0pa': -0.0007, 'paS': -0.0006, '0pe':  0.0006, 'SS': 1.0579, 'pepe': 1.2137, 'papa': 1.2147, '00': 0.8572, 'peS':  0.0003, 'pape':  0.0009}
WeightsBd['2011p_861_896'] =  {'0S': -0.7465, '0pa':  0.0001, 'paS': -0.0021, '0pe':  0.0002, 'SS': 1.0456, 'pepe': 1.2109, 'papa': 1.2095, '00': 0.8601, 'peS':  0.0009, 'pape':  0.0006}
WeightsBd['2011p_896_931'] =  {'0S': -0.6842, '0pa': -0.0018, 'paS': -0.0015, '0pe': -0.0006, 'SS': 1.0557, 'pepe': 1.2258, 'papa': 1.2252, '00': 0.8491, 'peS':  0.0005, 'pape': -0.0004}
WeightsBd['2011p_826_861'] =  {'0S': -0.7693, '0pa':  0.0006, 'paS':  0.0016, '0pe':  0.0002, 'SS': 1.0319, 'pepe': 1.1893, 'papa': 1.1878, '00': 0.8749, 'peS':  0.0021, 'pape': -0.0001}
WeightsBd['2012p_826_861'] =  {'0S': -0.7693, '0pa':  0.0006, 'paS':  0.0016, '0pe':  0.0002, 'SS': 1.0319, 'pepe': 1.1893, 'papa': 1.1878, '00': 0.8749, 'peS':  0.0021, 'pape': -0.0001}
WeightsBd['2012p_931_966'] =  {'0S': -0.5917, '0pa': -0.0002, 'paS': -0.0017, '0pe':  0.0006, 'SS': 1.0629, 'pepe': 1.2447, 'papa': 1.2432, '00': 0.8381, 'peS':  0.0013, 'pape': -0.0035}
WeightsBd['2012n_826_861'] =  {'0S': -0.7834, '0pa':  0.0008, 'paS':  0.0005, '0pe': -0.0002, 'SS': 1.0548, 'pepe': 1.2090, 'papa': 1.2100, '00': 0.8610, 'peS': -0.0013, 'pape':  0.0007}
WeightsBd['2012n_896_931'] =  {'0S': -0.6821, '0pa':  0.0001, 'paS': -0.0009, '0pe':  0.0001, 'SS': 1.0661, 'pepe': 1.2274, 'papa': 1.2263, '00': 0.8492, 'peS':  0.0002, 'pape':  0.0009}
WeightsBd['2011n_931_966'] =  {'0S': -0.6185, '0pa':  0.0010, 'paS': -0.0017, '0pe': -0.0009, 'SS': 1.0620, 'pepe': 1.2382, 'papa': 1.2373, '00': 0.8422, 'peS':  0.0012, 'pape':  0.0001}
WeightsBd['2011p_931_966'] =  {'0S': -0.5917, '0pa': -0.0002, 'paS': -0.0017, '0pe':  0.0006, 'SS': 1.0629, 'pepe': 1.2447, 'papa': 1.2432, '00': 0.8381, 'peS':  0.0013, 'pape': -0.0035}
WeightsBd['2012p_861_896'] =  {'0S': -0.7465, '0pa':  0.0001, 'paS': -0.0021, '0pe':  0.0002, 'SS': 1.0456, 'pepe': 1.2109, 'papa': 1.2095, '00': 0.8601, 'peS':  0.0009, 'pape':  0.0006}
WeightsBd['2011n_896_931'] =  {'0S': -0.6821, '0pa':  0.0001, 'paS': -0.0009, '0pe':  0.0001, 'SS': 1.0661, 'pepe': 1.2274, 'papa': 1.2263, '00': 0.8492, 'peS':  0.0002, 'pape':  0.0009}
WeightsBd['2011n_826_861'] =  {'0S': -0.7834, '0pa':  0.0008, 'paS':  0.0005, '0pe': -0.0002, 'SS': 1.0548, 'pepe': 1.2090, 'papa': 1.2100, '00': 0.8610, 'peS': -0.0013, 'pape':  0.0007}


for key, val in WeightsBd.iteritems():
    WeightsBd[key].update({ '200'    : 1
                            ,'2pa0'   : 0
                            ,'2pe20'  : 0
                            ,'2peS'   : 0 
                            ,'2pa2pa' : 1 
                            ,'20S'    : 0 
                            ,'2pepa'  : 0 
                            ,'2pepe'  : 0  
                            ,'2pa20'  : 0  
                            ,'2pe2pa' : 0
                            ,'2pe2pe' : 1
                            ,'20pa'   : 0  
                            ,'20pe'   : 0  
                            ,'2paS'   : 0  
                            ,'2pe0'   : 0  
                            ,'2020'   : 1   
                            ,'2pape'  : 0 
                            ,'2papa'  : 0  }
                          )
