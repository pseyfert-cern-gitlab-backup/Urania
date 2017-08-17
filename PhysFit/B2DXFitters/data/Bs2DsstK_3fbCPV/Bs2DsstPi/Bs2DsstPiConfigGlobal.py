def getconfig():
    configdict = {}
	# 1 No Weights
#    configdict["GlobalWeight"] = {"2011": {"NonRes": {"Down": 0.289209, "Up": 0.251107},
#                                               "PhiPi" : {"Down": 0.952755, "Up": 0.697112},
#                                               "KstK"  : {"Down": 0.855990, "Up": 0.629444},
#                                               "KPiPi" : {"Down": 0.322164, "Up": 0.236617},
#                                               "PiPiPi": {"Down": 0.281257, "Up": 0.203771}},
#                                    "2012": {"NonRes": {"Down": 0.504975, "Up": 0.597404},
#                                               "PhiPi" : {"Down": 0.844784, "Up": 1.000000},
#                                               "KstK"  : {"Down": 0.786025, "Up": 0.933315},
#                                               "KPiPi" : {"Down": 0.261030, "Up": 0.263619},
#                                               "PiPiPi": {"Down": 0.454144, "Up": 0.482168}}}
	# 2 DPi Weights
#    configdict["GlobalWeight"] = {"2011": {"NonRes": {"Down": 0.276518, "Up": 0.241515},
#                                               "PhiPi" : {"Down": 0.952154, "Up": 0.696388},
#                                               "KstK"  : {"Down": 0.861316, "Up": 0.633159},
#                                               "KPiPi" : {"Down": 0.325433, "Up": 0.238880},
#                                               "PiPiPi": {"Down": 0.283598, "Up": 0.207653}},
#                                    "2012": {"NonRes": {"Down": 0.502486, "Up": 0.598065},
#                                               "PhiPi" : {"Down": 0.839427, "Up": 1.000000},
#                                               "KstK"  : {"Down": 0.781442, "Up": 0.937611},
#                                               "KPiPi" : {"Down": 0.260006, "Up": 0.264109},
#                                               "PiPiPi": {"Down": 0.451160, "Up": 0.485865}}}
	# 3 DsstPi Weights
    configdict["GlobalWeight"] = {"2011": {"NonRes": {"Down": 0.283086, "Up": 0.245430},
                                               "PhiPi" : {"Down": 1.000000, "Up": 0.731054},
                                               "KstK"  : {"Down": 0.909715, "Up": 0.669551},
                                               "KPiPi" : {"Down": 0.346204, "Up": 0.251875},
                                               "PiPiPi": {"Down": 0.300899, "Up": 0.219959}},
                                    "2012": {"NonRes": {"Down": 0.335349, "Up": 0.396745},
                                               "PhiPi" : {"Down": 0.559205, "Up": 0.659702},
                                               "KstK"  : {"Down": 0.522821, "Up": 0.626752},
                                               "KPiPi" : {"Down": 0.174603, "Up": 0.176777},
                                               "PiPiPi": {"Down": 0.302242, "Up": 0.322775}}}
    return configdict
