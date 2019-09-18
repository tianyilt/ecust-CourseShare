
public class TeacherCourse {
	private String TeacherId=null;  //教师工号
	private String CourseId=null;  //课程号

	public TeacherCourse() {
		// TODO Auto-generated constructor stub
	}

	public TeacherCourse(String teacherId, String courseId) {
		super();
		TeacherId = teacherId;
		CourseId = courseId;
	}

	public String getTeacherId() {
		return TeacherId;
	}

	public void setTeacherId(String teacherId) {
		TeacherId = teacherId;
	}

	public String getCourseId() {
		return CourseId;
	}

	public void setCourseId(String courseId) {
		CourseId = courseId;
	} 
  
}
