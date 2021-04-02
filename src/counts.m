clear; clc;
contagem=input('Contagem: ');
count=zeros(1,1);
i=1;

while(1)
  if(contagem==(-1))
    break; 
  else 
   if(i~=1)
     count=[count 0];
   end
  end
  count(i)=log10(contagem);
  i=i+1;
  contagem=input('Contagem: ');
end

%algoritmos = {'BubbleSort','ShakerSort','InsertionSort','ShellSort','QuickSort','MergeSort','HeapSort','RankSort','SelectionSort'};
%contagem = [203992486693,136085538912,102079446092,419898387,231850740,260532948,384002962,204060215186,455947821779];
%count = log10(contagem);

bar(1:length(count), count)
print('switches','-dpng');