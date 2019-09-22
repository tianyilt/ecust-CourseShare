
public class Course {
	private String Id=null;  //课程号
	private String name=null;  //课程名
	private String department=null; //系别
    private String classname=null; //班级
    
	public Course() { 
	}

	public Course(String id, String name, String department, String classname) {
		//super();
		Id = id;
		this.name = name;
		this.department = department;
		this.classname = classname;
	}

	public String getId() {		return Id;	}
	public void setId(String id) {		Id = id;	}

	public String getName() {		return name;	}
	public void setName(String name) {		this.name = name;	}

	public String getDepartment() {		return department;	}
	public void setDepartment(String department) {		this.department = department;	}

	public String getClassname() {		return classname;	}
	public void setClassname(String classname) {		this.classname = classname;	}

}

