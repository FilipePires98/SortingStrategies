fid = fopen ('to_be_processed.txt', 'r');
x=zeros(1,1);
med=zeros(9, 1);
var=zeros(9, 1);
iteracao=1;
alg=1;
count=0;
while (~ feof (fid) )
  line = fgetl (fid);
  numeros=strsplit(line, ' ');
  med(alg, iteracao)=str2double(numeros{2});
  var(alg, iteracao)=str2double(numeros{3});
  if(alg==1)
    x(iteracao)=str2double(numeros{1});
    x=[x 0];
  end
  if(alg==9)
    alg=1;
    iteracao=iteracao+1;
    med=[med zeros(9,1)];
    var=[var zeros(9,1)];
  else
    alg=alg+1;
  end
  count=count+1;
end
i=count/9;
hold on
figure(1)
plot(log10(x(1:i)), log10(med(:,1:i)))
print('averages','-dpng');
figure(2)
plot(x(1:i), log10(var(:,1:i)))
print('deviations','-dpng');