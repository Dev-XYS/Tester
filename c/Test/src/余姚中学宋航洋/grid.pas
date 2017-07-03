procedure sw(var a,b:longint);
var c:longint; begin c:=a; a:=b; b:=c end;

var
 T,n,m,c,d,p,phip,i,x,y,p_n:longint;
 u,v:array[0..40]of longint;
 f:array[0..200005]of int64;

function gcd(a,b:longint):longint;
begin if b=0 then exit(a); exit(gcd(b,a mod b)) end;

function pw(const x,y:int64):int64;
begin
 if y=0 then exit(1);
 if y=1 then exit(x);
 exit(sqr(pw(x,y>>1))mod p*pw(x,y and 1)mod p)
end;

procedure initp;
begin
 phip:=p;
 x:=p;
 p_n:=0;
 i:=2;
 while x>=i*i do
 begin
  if x mod i=0 then
  begin
   phip:=phip div i*(i-1);
   inc(p_n);
   u[p_n]:=i;
   v[p_n]:=0;
   repeat x:=x div i; inc(v[p_n]) until x mod i<>0
  end;
  inc(i)
 end;
 if x>1 then begin phip:=phip div x*(x-1); inc(p_n); u[p_n]:=x; v[p_n]:=1 end;
 f[0]:=1;
 for i:=1 to n+m do
 begin
  x:=i;
  y:=gcd(x,p);
  while y>1 do
  begin
   x:=x div y;
   y:=gcd(x,p)
  end;
  f[i]:=f[i-1]*int64(x)mod p
 end
end;

function sk(n,p:longint):longint;
begin if n<p then exit(0); sk:=n div p; inc(sk,sk(sk,p)) end;

function ct(n,m:longint):int64;
var i,j:longint;
begin
 dec(n); dec(m); if n<m then sw(n,m); inc(n,m-1);
 ct:=f[n]*f[n-1]mod p*pw(f[m]*f[m-1]mod p*f[n-m]mod p*f[n-m+1]mod p,phip-1)mod p;
 for i:=1 to p_n do
 begin
  j:=sk(n,u[i])+sk(n-1,u[i])-sk(m,u[i])-sk(m-1,u[i])-sk(n-m,u[i])-sk(n-m+1,u[i]);
  ct:=ct*pw(u[i],j)mod p
 end
end;

begin
 assign(input,'grid.in'); reset(input);
 assign(output,'grid.out'); rewrite(output);
 read(T);
 for T:=1 to T do
 begin
  read(n,m,c,d,p);
  initP;
  writeln(ct(n,m))
 end;
 close(input); close(output)
end.