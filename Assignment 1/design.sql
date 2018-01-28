/*Need to verify the code once again, with some test cases*/


CREATE TABLE student(
	student_id TEXT PRIMARY KEY,
	name TEXT	
);

CREATE TABLE course(
	course_id TEXT PRIMARY KEY,
	name TEXT
);

CREATE TABLE registers(
	student_id TEXT references student(student_id) ON DELETE CASCADE ON UPDATE CASCADE,
	course_id TEXT references course(course_id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY(student_id, course_id)
);

CREATE TABLE teacher(
	teacher_id TEXT PRIMARY KEY,
	name TEXT
);

CREATE TABLE teaches(
	teacher_id TEXT references teacher(teacher_id) ON DELETE CASCADE ON UPDATE CASCADE,
	course_id TEXT references course(course_id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY(teacher_id, course_id)
);

CREATE DOMAIN sec_num TEXT 
check( 
	VALUE IN ('A', 'B', 'C', 'D')
);

CREATE TABLE section(
	section_number sec_num,
	course_id TEXT references course(course_id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY(section_number, course_id)
);
