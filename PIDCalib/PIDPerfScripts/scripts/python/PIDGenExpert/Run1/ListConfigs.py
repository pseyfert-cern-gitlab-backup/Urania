import Config
import ConfigMC
import ConfigMCSim09

particles = []
variables = []

for n in Config.configs.keys() + ConfigMC.configs.keys() + ConfigMCSim09.configs.keys() : 
  ns = n.split("_")
  p = ns[0]
  v = ns[1]
  if p == 'gamma' : continue
  if not p in particles : particles += [ p ]
  if not v in variables : variables += [ v ]

particles = [ "pi", "K", "p", "e", "mu" ]

s = "| *%12.12s* " % "Variable"
for p in particles : 
  s += " | *%5.5s* " % p 
s += " |"
print s
for v in sorted(variables) : 
  s = "| %14.14s " % ("!" + v)
  for p in particles : 
    n = "%s_%s" % (p, v)
    f = ""
    if n in Config.configs.keys() : 
      f += "G"
      if n in ConfigMC.configs.keys() : f += "/C8"
      if n in ConfigMCSim09.configs.keys() : f += "/C9"
    s += " | %7.7s " % f
  s += ' |'
  print s
