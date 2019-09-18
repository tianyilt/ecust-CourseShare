 
 #include <iostream>
 using namespace std; 
 
 class A{ 
    public: 
       virtual void show(){cout<<"基类的show()"<<endl;} 
       void get(){cout<<"基类的get()"<<endl;} 
};

class B:public A{ 
       public: 
      virtual void show(){cout<<"派生类的show()"<<endl; }
	  void get(){cout<<"派生类的get()"<<endl;}

}; 

int main(int argc, char *argv[])
{
   A a; 
   B b; 
   A *c=&b; 
   c->show();//show函数是虚函数，并且此时使用派生类的对象去初始化基类的引用，发生了动态绑定，调用的是实际类　　　　　　　　型B的show()----"派生类的show"
   c->get();//此时不满足动态绑定的条件，c是静态类型，结果是-------基类的get()
	
	return 0;
}
