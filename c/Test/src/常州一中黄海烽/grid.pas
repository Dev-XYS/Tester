var
    n,m,t,i,j,k,i1,j1,pp,c,d,la,nn,tt,num,t2:longint;
    mo,moo,ans,ans1:int64;
    p,mark,q,ss:array[0..201000] of longint;
    f:array[0..1,0..51,0..51,0..51] of int64;
    a:array[0..51,0..51] of longint;

procedure setin;
begin
    assign(input,'grid.in');
    assign(output,'grid.out');
    reset(input);rewrite(output);
end;

procedure outit;
begin
    close(input);close(output);
end;

procedure prepare;
begin
    n:=200000;
    for i:=2 to n do
    begin
        if mark[i]=0 then
        begin
            inc(pp);p[pp]:=i;
        end;
        for j:=1 to pp do
        begin
            if i*p[j]>n then break;
            mark[i*p[j]]:=1;
            if i mod p[j]=0 then break;
        end;
    end;
    for i:=1 to pp do q[p[i]]:=i;
end;

function pow(a,b:int64):int64;
var c:int64;
begin
    c:=1;
    while b<>0 do
    begin
        if b and 1=1 then c:=(c*a) mod mo;
        a:=(a*a) mod mo;
        b:=b>>1;
    end;
    exit(c);
end;

function gcd(a,b:int64):int64;
var c:int64;
begin
    while b<>0 do
    begin
        c:=a mod b;a:=b;b:=c;
    end;
    exit(a);
end;

procedure ins(x,v:longint);
var i,j:longint;
begin
    j:=x;i:=1;
    while p[i]<=trunc(sqrt(x)) do
    begin
        if j=1 then break;
        while j mod p[i]=0 do begin ss[i]:=ss[i]+v;j:=j div p[i];end;
        i:=i+1;
    end;
    if j>1 then inc(ss[q[j]],v);
end;

begin
    setin;
    read(t);prepare;
    for t:=1 to t do
    begin
        read(n,m,c,d,mo);
        if (n=1)or(m=1) then begin writeln(0);continue;end;
        if c=0 then
        begin
            if (n=2)or(m=2) then begin writeln(1);continue;end;
            moo:=mo;j:=mo;
            for i:=1 to pp do
            if j mod p[i]=0 then
            begin
                while j mod p[i]=0 do j:=j div p[i];
                moo:=moo div p[i]*(p[i]-1);
            end;
            if j>1 then moo:=moo div j*(j-1);
            if moo=mo-1 then
            begin
            ans:=1;
            for i:=m-2+1 to m-2+n-1 do ans:=(ans*i) mod mo;
            for i:=m-2+2 to m-2+n-2 do ans:=(ans*i) mod mo;
            ans1:=1;
            for i:=2 to n-2 do ans1:=(ans1*i) mod mo;
            ans1:=((ans1*ans1) mod mo*(n-1)) mod mo;
            ans:=(ans*pow(ans1,moo-1)) mod mo;
            end
            else
            begin
                for i:=1 to pp do ss[i]:=0;
                for i:=m-2+1 to m-2+n-1 do ins(i,1);
                for i:=m-2+2 to m-2+n-2 do ins(i,1);
                for i:=2 to n-2 do ins(i,-2);
                ins(n-1,-1);
                ans:=1;
                for i:=1 to pp do ans:=(ans*pow(p[i],ss[i]))mod mo;
            end;
            writeln(ans);
        end
        else
        begin
            for i:=1 to n do for j:=1 to m do a[i,j]:=0;
            for i:=1 to c do begin read(i1,j1);a[i1,j1]:=1;end;
            fillchar(f,sizeof(f),0);
            if a[1,2]=1 then f[1,1,2,1]:=1 else f[1,1,2,0]:=1;
            la:=0;nn:=1;
            for k:=2 to n+1 do
            begin
                la:=la xor 1;nn:=nn xor 1;
                for i:=1 to m-1 do
                 for j:=i+1 to m do
                 begin
                     for num:=0 to d do f[nn,i,j,num]:=0;
                     tt:=a[k,i]+a[k,j];
                     for i1:=i downto 1 do
                     begin
                      t2:=tt;
                      for j1:=j downto i+1 do
                      begin
                       for num:=t2 to d do
                        f[nn,i,j,num]:=(f[nn,i,j,num]+f[la,i1,j1,num-t2]) mod mo;
                       t2:=t2+a[k-1,j1];
                      end;
                      tt:=tt+a[k-1,i1];
                     end;
                 end;
            end;
            ans:=0;
            for i:=0 to d do ans:=(ans+f[nn,m-1,m,i]) mod mo;
            writeln(ans);
        end;
    end;
    outit;
end.
