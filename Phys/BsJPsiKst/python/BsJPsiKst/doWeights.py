from os import system
x = "Bs"
for i in range(23):
    system("python AddSweights.py 2011p " + str(i) + " " + x)
    system("python AddSweights.py 2011n " + str(i) + " " + x)
    system("python AddSweights.py 2012p " + str(i) + " " + x)
    system("python AddSweights.py 2012n " + str(i) + " " + x)

