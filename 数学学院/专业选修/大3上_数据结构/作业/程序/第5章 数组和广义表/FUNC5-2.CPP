 // func5-2.cpp ϡ��������������main5-2.cpp��main5-3.cpp����
 void main()
 {
   TSMatrix A,B,C;
   printf("��������A��");
   CreateSMatrix(A); // ��������A
   PrintSMatrix(A); // �������A
   CopySMatrix(A,B); // �ɾ���A���ƾ���B
   printf("�ɾ���A���ƾ���B��\n");
   PrintSMatrix(B); // �������B
   DestroySMatrix(B); // ���پ���B
   printf("���پ���B��\n");
   PrintSMatrix(B); // �������B
   printf("��������B2��(�����A���С�������ͬ���С��зֱ�Ϊ%d,%d)\n",A.mu,A.nu);
   CreateSMatrix(B); // ��������B
   PrintSMatrix(B); // �������B
   AddSMatrix(A,B,C); // ������ӣ�C=A+B
   printf("����C1(A+B)��\n");
   PrintSMatrix(C); // �������C
   SubtSMatrix(A,B,C); // ���������C=A-B
   printf("����C2(A-B)��\n");
   PrintSMatrix(C); // �������C
   TransposeSMatrix(A,C); // ����C�Ǿ���A��ת�Ⱦ���
   printf("����C3(A��ת��)��\n");
   PrintSMatrix(C); // �������C
   printf("��������A2��");
   CreateSMatrix(A); // ��������A
   PrintSMatrix(A); // �������A
   printf("��������B3��(����Ӧ�����A2��������ͬ=%d)\n",A.nu);
   CreateSMatrix(B); // ��������B
   PrintSMatrix(B); // �������B
 #ifndef FLAG // δ����FLAG
   MultSMatrix(A,B,C); // ������ˣ�C=A��B
 #else // ������FLAG
   MultSMatrix1(A,B,C); // ��һ��������˺���C=A��B����bo5-3.cpp��
 #endif
   printf("����C5(A��B)��\n");
   PrintSMatrix(C); // �������C
 }
