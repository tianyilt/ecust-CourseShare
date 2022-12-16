    function matrix=OneStepGaoSi(SubZhengGuangMatrix)
        [row_ZhengGuang,col_ZhengGuang] = size(SubZhengGuangMatrix);
        FirstCol=SubZhengGuangMatrix(:,1);
        for i=2:row_ZhengGuang%°´ÁÐ
            for j=1:col_ZhengGuang
                SubZhengGuangMatrix(i,j)=SubZhengGuangMatrix(i,j)-SubZhengGuangMatrix(1,j)/SubZhengGuangMatrix(1,1)*FirstCol(i);
            end
        end
        matrix=SubZhengGuangMatrix;
    end