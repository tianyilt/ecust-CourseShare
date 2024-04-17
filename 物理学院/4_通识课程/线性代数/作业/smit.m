function g=smit(G)
%施密特正交化方法讲向量正交，输入的G是一个矩阵，每一列是一个向量
%自动选择第一个向量正交
[m,n]=size(G);
g=zeros(m,n);
g(:,1)=G(:,1);
g2=sqrt( sum(g(:,1).^2));
g(:,1)=g(:,1)/g2;
for i=2:n
    g(:,i)=G(:,i);
    for j=1:i-1
        g(:,i)=g(:,i)-G(:,i)'*g(:,j)./( g(:,j)'*g(:,j))*g(:,j);
    end
    g2=sqrt( sum(g(:,i).^2));
    g(:,i)=g(:,i)/g2;
end
