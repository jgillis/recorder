function [y,a,b]=foo(x)
nom = nargin==0;
if nom
  a1 = -1.0000000000000000e+00;
else
  a1 = x(1);
end
if nom
  a2 = 2.0000000000000000e+00;
else
  a2 = x(2);
end
if nom
  a3 = 3.0000000000000000e+00;
else
  a3 = x(3);
end
if nom
  a4 = 3.2000000000000000e+01;
else
  a4 = x(4);
end
a5 = times(a1,3.0000000000000000e+00);
if nom, assert(a5==-3.0000000000000000e+00); end;
a6 = ge(a5,0.0000000000000000e+00);
if nom, assert(a6==0.0000000000000000e+00); end;
a{1} = a6-0.0000000000000000e+00;%0.0000000000000000e+00
b{1} = a6;%0.0000000000000000e+00
if ~nom
y{1} = a5;%-3.0000000000000000e+00
end
if ~nom, y = vertcat(y{:}); end;
a = vertcat(a{:});
b = vertcat(b{:});
