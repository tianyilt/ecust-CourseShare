
public class Score {   
	private Student student=null;  //学生
	private Teacher teacher=null;  //教师
	private Course course=null;    //课程
	private int score=0;  //成绩
	
	public Score() {		
	}

	public Score(Student student, Teacher teacher, Course course, int score) {
		//super();
		this.student = student;
		this.teacher = teacher;
		this.course = course;
		this.score = score;
	}

	public Student getStudent() {		return student;	}
	public void setStudent(Student student) {		this.student = student;	}

	public Teacher getTeacher() {		return teacher;	}
	public void setTeacher(Teacher teacher) {		this.teacher = teacher;	}

	public Course getCourse() {		return course;	}
	public void setCourse(Course course) {		this.course = course;	}

	public int getScore() {		return score;	}

	public void setScore(int score) {		this.score = score;	} 
}
