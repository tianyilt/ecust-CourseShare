function []=gTh(G)
%本函数判断一个矩阵构成的集合能否构成群
%群乘法的定义是矩阵乘法
%G是元组，元素是矩阵，最长可有52位。
%如果构成群，就输出乘法表，否则输出0
i=complex(0,1);
n=length(G);
M=zeros(n);
%判断G是否含有虚数
is_j=isreal(cell2mat(G));
for i0=1:n
    for j=1:n
        for k=1:n
            if cell2mat(G(i0))*cell2mat(G(j))==cell2mat(G(k))
                M(i0,j)=char(k+64);
            elseif ~is_j
                if round(real(cell2mat(G(i0))*cell2mat(G(j))))==round(real(cell2mat(G(k))))
                    M(i0,j)=char(k+64);
                end
            end
        end
    end
end
if all(M)
    %如果全非零，构成群，输出乘法表
    fprintf('*| ')
    for i0=1:n
        fprintf('  %s   ',char(i0+64));
    end
    fprintf('\n');
    for i0=1:n
        fprintf('______');
    end
    fprintf('__');
    for i0=1:n
        fprintf('\n%s| ',char(i0+64));
        for j=1:n
            fprintf('%s*%s=%s ',char(i0+64),char(j+64),M(i0,j));
        end
    end
    fprintf('\n');    
else
    disp('不构成矩阵');
    disp(M);
end
end