
set terminal postscript eps color enhanced "Helvetica" 20
f(x) = l/sqrt(x)
g(x) = c/(x**k)
set yrange [0:0.2]
set xrange [0:6000]


set output "lumi_opt.eps"
fit f(x) "lumi" using 1:($2/$1) via l
fit g(x) "lumi" using 1:($2/$1) via c, k
plot "lumi" using 1:($2/$1), f(x), g(x)



set output "lumi_5.0.eps"
fit f(x) "lumi" using 1:($3/$1) via l
fit g(x) "lumi" using 1:($3/$1) via c, k
plot     "lumi" using 1:($3/$1), f(x), g(x)


set output "binningopt.eps"
plot     "lumi" using 1:($3/$1), "lumi" using 1:($2/$1)
