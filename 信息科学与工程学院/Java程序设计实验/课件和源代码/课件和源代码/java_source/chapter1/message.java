class Manager
{
    public void save(Account account,double balance){
          account.deposit(balance);
	}
}

class  Account
{
	public  double balance;
	public void deposit(double balance2){
          balance=balance+balance2;
	}

	public static void main(String[] args) 
	{
		Account tom=new Account();
		Manager rose=new Manager();
        rose.save(tom,100);
		 
	}
}
