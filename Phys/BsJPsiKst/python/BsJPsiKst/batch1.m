(* Mathematica macro, called from penguins.py python script *)
(* Find the four theta solutions, given H and A *)
(* Keep only real solutions  *)
(* Olivier Leroy, Jan 2013 *)

(* H and A are computed in a python script: read them from file *)
myinput = ReadList["HandA.txt", Number]
H = myinput[[1]]
A = myinput[[2]]

myin = ReadList["penguin_inputs.py", Word, WordSeparators -> {"=", "#"}];

g = ToExpression[myin[[5]]]  (* Convert Word into number *)
eps = ToExpression[myin[[9]]]


U = (1 + eps*H)/(1 - (eps^2)*H)*Cos[theta]*Cos[g];
V = (1 - H)/(1 - (eps^2)*H);


Uprime = Cos[theta]*Cos[g] + Sin[theta]*Sin[g]/A;
Vprime = 1;

(* 4 equations, according to choice of signs *)
roots1 = theta /.NSolve[U + Sqrt[U^2 - V] - Uprime + Sqrt[Uprime^2 - Vprime] == 0, theta];
theta1 = Select[roots1, Im@# == 0 &];

roots2 = theta /.NSolve[U + Sqrt[U^2 - V] - Uprime - Sqrt[Uprime^2 - Vprime] == 0, theta];
theta2 = Select[roots2, Im@# == 0 &];

roots3 = theta /.NSolve[U - Sqrt[U^2 - V] - Uprime + Sqrt[Uprime^2 - Vprime] == 0, theta];
theta3 = Select[roots3, Im@# == 0 &];

roots4 = theta /.NSolve[U - Sqrt[U^2 - V] - Uprime - Sqrt[Uprime^2 - Vprime] == 0, theta];
theta4 = Select[roots4, Im@# == 0 &];


(* Save the 4 values of theta, for future use in python *)
Export["myOutput.txt", { theta1, theta2, theta3, theta4}, "Table"]; 


Print["fin"];
