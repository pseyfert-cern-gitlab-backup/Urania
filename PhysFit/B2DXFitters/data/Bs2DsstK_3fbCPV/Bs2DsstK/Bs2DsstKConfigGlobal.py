def getconfig():
    configdict = {}
	# 1 No Weights
#    configdict["GlobalWeight"] = {"2011": {"NonRes": {"Down": 0.497300, "Up": 0.385106},
#                                               "PhiPi" : {"Down": 0.848852, "Up": 0.670211},
#                                               "KstK"  : {"Down": 0.766982, "Up": 0.595876},
#                                               "KPiPi" : {"Down": 0.440421, "Up": 0.300269},
#                                               "PiPiPi": {"Down": 0.483716, "Up": 0.718091}},
#                                    "2012": {"NonRes": {"Down": 0.584562, "Up": 0.592608},
#                                               "PhiPi" : {"Down": 0.974114, "Up": 1.000000},
#                                               "KstK"  : {"Down": 0.923757, "Up": 0.940439},
#                                               "KPiPi" : {"Down": 0.499114, "Up": 0.476361},
#                                               "PiPiPi": {"Down": 0.885884, "Up": 0.956811}}}
	# 2 DPi Weights
#    configdict["GlobalWeight"] = {"2011": {"NonRes": {"Down": 0.498773, "Up": 0.381535},
#                                               "PhiPi" : {"Down": 0.850307, "Up": 0.665898},
#                                               "KstK"  : {"Down": 0.775542, "Up": 0.599347},
#                                               "KPiPi" : {"Down": 0.444178, "Up": 0.303590},
#                                               "PiPiPi": {"Down": 0.487857, "Up": 0.724080}},
#                                    "2012": {"NonRes": {"Down": 0.583234, "Up": 0.593709},
#                                               "PhiPi" : {"Down": 0.966443, "Up": 1.000000},
#                                               "KstK"  : {"Down": 0.920000, "Up": 0.946439},
#                                               "KPiPi" : {"Down": 0.496693, "Up": 0.480096},
#                                               "PiPiPi": {"Down": 0.883657, "Up": 0.967927}}}
	# 3 DsstPi Weights
    configdict["GlobalWeight"] = {"2011": {"NonRes": {"Down": 0.587016, "Up": 0.447754},
                                               "PhiPi" : {"Down": 1.000000, "Up": 0.778637},
                                               "KstK"  : {"Down": 0.913067, "Up": 0.705025},
                                               "KPiPi" : {"Down": 0.528173, "Up": 0.360441},
                                               "PiPiPi": {"Down": 0.575868, "Up": 0.847571}},
                                    "2012": {"NonRes": {"Down": 0.421325, "Up": 0.426633},
                                               "PhiPi" : {"Down": 0.698227, "Up": 0.716946},
                                               "KstK"  : {"Down": 0.666981, "Up": 0.682600},
                                               "KPiPi" : {"Down": 0.359885, "Up": 0.347029},
                                               "PiPiPi": {"Down": 0.636312, "Up": 0.700813}}}
    return configdict
