import casadi.*
arg = SX.sym('arg',4); 
  
[y_F,~,~] = foo_F(arg); % True case
[y_T,~,b_T] = foo_T(arg); % False case, b_T is 1 if conditional is True
y = if_else(b_T==1, y_T, y_F);

F = Function('F',{arg},{y});

cg = CodeGenerator('foo_jac');
cg.add(F);
cg.add(F.jacobian())
cg.generate();

in1 = [1,2,3,32];
in2 = [-1,2,3,32];

out1 = full(F(in1));
out2 = full(F(in2));  

assert(out1==67)
assert(out2==-3)
