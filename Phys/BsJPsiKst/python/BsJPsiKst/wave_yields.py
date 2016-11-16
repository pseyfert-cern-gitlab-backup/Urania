WY = {}
WY["Bd"] = {}
WY["Bd"][0] = {
"Pwave1": 9413.16108423877,
"Swave1": 1129.53420572145,
"Pwave2": 9002.11306250343,
"Swave2": 1090.36715840203 }


WY["Bd"][1] = {
"Pwave1": 38729.6349299814,
"Swave1": 1464.35709264738,
"Pwave2": 37815.4145604541,
"Swave2": 1442.82446180919}

WY["Bd"][2] = {
"Pwave1": 35651.4815471654,
"Swave1": 1700.44499343393,
"Pwave2": 35361.8586427641,
"Swave2": 1702.27698416084}

WY["Bd"][3] = {
"Pwave1": 11202.9194490281,
"Swave1": 1343.99173814958,
"Pwave2": 11289.5205249287,
"Swave2": 1367.32527260564}


WY["Bs"] = {}

WY["Bs"][0] = {
"Pwave1": 48.4752020415668,
"Swave1": 51.4275479258599,
"Pwave2": 51.4061014354264,
"Swave2": 54.5754161252139}

WY["Bs"][1] = {
"Pwave1": 307.898859855014,
"Swave1": 23.9632204997632,
"Pwave2": 315.161989977500,
"Swave2": 24.5435529900201}

WY["Bs"][2] = {
"Pwave1": 344.786915010443,
"Swave1": 34.6241444877820,
"Pwave2": 342.014969039976,
"Swave2": 34.3686220651184}

WY["Bs"][3] = {
"Pwave1": 54.0431573585999,
"Swave1": 86.2321808812128,
"Pwave2": 53.1074036613286,
"Swave2": 84.8030267499993}


for i in range(4):
    WY["Bs"][i]["Pwave"] = 0.5*(WY["Bs"][i]["Pwave1"] + WY["Bs"][i]["Pwave2"])
    WY["Bs"][i]["PwaveErr"] = abs(WY["Bs"][i]["Pwave1"] - WY["Bs"][i]["Pwave2"])
    WY["Bs"][i]["Swave"] = 0.5*(WY["Bs"][i]["Swave1"] + WY["Bs"][i]["Swave2"])
    WY["Bs"][i]["SwaveErr"] = abs(WY["Bs"][i]["Swave1"] - WY["Bs"][i]["Swave2"])
    
    WY["Bd"][i]["Pwave"] = 0.5*(WY["Bd"][i]["Pwave1"] + WY["Bd"][i]["Pwave2"])
    WY["Bd"][i]["PwaveErr"] = abs(WY["Bd"][i]["Pwave1"] - WY["Bd"][i]["Pwave2"])
    WY["Bd"][i]["Swave"] = 0.5*(WY["Bd"][i]["Swave1"] + WY["Bd"][i]["Swave2"])
    WY["Bd"][i]["SwaveErr"] = abs(WY["Bd"][i]["Swave1"] - WY["Bd"][i]["Swave2"])


print "Bd"
print "------------"
for i in range(4):
    print "Swave",i, WY["Bd"][i]["Swave"] , " \pm " ,  WY["Bd"][i]["SwaveErr"]
    print "Pwave",i, WY["Bd"][i]["Pwave"] , " \pm " ,  WY["Bd"][i]["PwaveErr"]

print "Bs"
print "-----------"
for i in range(4):
    print "Swave",i, WY["Bs"][i]["Swave"] , " \pm " ,  WY["Bs"][i]["SwaveErr"]
    print "Pwave",i, WY["Bs"][i]["Pwave"] , " \pm " ,  WY["Bs"][i]["PwaveErr"]
