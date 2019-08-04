#include <stdlib.h>
#include <ilcplex/ilocplex.h>
#include <windows.h>

const int N = 100;

ILOSTLBEGIN

int
	main(int, char**)
{
//求解背包问题
	double s[N]={3,5,6,7,4};//物品 size
	double w[N]={3,3,6,9,1};//物品价值
	double c=20;//背包容量限制
	
	int n=5;
	
	IloEnv env;
	try{
		IloModel model(env);
		IloNumVarArray x(env,n,0,1,ILOINT);//添加整数型数组x(n维),取值范围 0 到1， 为0，1变量
		IloNumVar W(env,0,IloInfinity, ILOFLOAT);//添加FLOAT型变量W, 取值范围 0,IloInfinity， 类型 ILOFLOAT，W为所装物品的总价值
		
		IloExpr availExpr(env);	
		for(int i=0;i<n;i++)
		{
			availExpr+=s[i]*x[i];
		}
		model.add(availExpr<=c);//添加 容量限制的约束条件
		availExpr.end();

		IloExpr availExpr1(env);	
		for(int i=0;i<n;i++)
		{
			availExpr1+=w[i]*x[i];
		}
		model.add(availExpr1>=W);
		availExpr1.end();// 建立目标函数W所满足的关系，因为不支持等式，所以用不等式代替
		
		//model.add(IloMinimize(env,W));
		model.add(IloMaximize(env,W));//添加目标函数
			
		IloCplex cplex(env);
		cplex.extract(model);
		cplex.solve();
		int status=cplex.getStatus();
		double opt=cplex.getObjValue();
		
		double w0;
		w0=cplex.getValue(W);//可以取得W的值，以供调试
		int xx[N];
		for(int i=0;i<n;i++)
		{
			xx[i]=cplex.getValue(x[i]);//可以取得x[i]的值，以供调试
		}
		cout<<"W="<<w0<<endl;
		for(int i=0;i<n;i++)
			cout<<"x["<<i<<"]="<<xx[i]<<endl;		
	}
	catch (IloException& ex) {
		cerr << "Error: " << ex << endl;
	}
	env.end();
	//	Sleep(4000);

   system ("pause");
   return 0 ;
} 