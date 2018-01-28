INSERT INTO student (student_id, name) VALUES 
	('2015ME10686', 'Utkarsh N. Singh'),
	('2015EE10691', 'Yash Garg'),
	('2015EE30898', 'Ishu Jain'),
	('2015CS10210', 'Aman Agrawal'),
	('2015ME10354', 'Paras Gupta'),
	('2015EE30649', 'Harsh Hemant Malara'),
	('2015MT10592', 'Avaneep Gupta'),
	('2015CS10262', 'Suyash Agrawal');

INSERT INTO teacher (teacher_id, name) VALUES 
	('sayan', 'Sayan Ranu'),
	('srsarangi', 'Smruti Sarangi'),
	('jkdutt', 'Jayanta Kumar Dutt'),
	('sudipto', 'Sudipto Mukherjee'),
	('varunr', 'Varun Ramamohan'),
	('suban', 'Subhashis Banerjee'),
	('aravindam', 'S. Aravindam');

INSERT INTO course (course_id, name) VALUES
	('COL362', 'Intro. to Database Management Systems'),
	('COL331', 'Operating Systems'),
	('MCL212', 'Control Theory and Applications'),
	('MCL131', 'Manufacturing Processes I'),
	('MCL361', 'Manufacturing System Design'),
	('MCP301', 'Mechanical Engineering Lab I'),
	('COP290', 'Design Practices'),
	('ELL405', 'Operating Systems');

/*Each transaction is now independent*/

INSERT INTO section (course_id, section_number) VALUES	('COL362', 'A'); 
INSERT INTO section (course_id, section_number) VALUES	('COL331', 'E');
INSERT INTO section (course_id, section_number) VALUES	('COL331', 'D');
INSERT INTO section (course_id, section_number) VALUES	('COP290', 'B');
INSERT INTO section (course_id, section_number) VALUES	('MCL212', 'B');
INSERT INTO section (course_id, section_number) VALUES	('COL362', 'C');
INSERT INTO section (course_id, section_number) VALUES	('MCP301', 'P');
INSERT INTO section (course_id, section_number) VALUES	('MCP301', 'A');
INSERT INTO section (course_id, section_number) VALUES	('MCL131', 'D');
INSERT INTO section (course_id, section_number) VALUES	('MCL361', 'C');
INSERT INTO section (course_id, section_number) VALUES	('MCP301', 'P');
INSERT INTO section (course_id, section_number) VALUES	('MCL212', 'B');
INSERT INTO section (course_id, section_number) VALUES	('ELL405', 'D');


INSERT INTO registers (course_id, student_id) VALUES
INSERT INTO registers (course_id, student_id) VALUES	('COL362', '2015EE3898');
INSERT INTO registers (course_id, student_id) VALUES	('COL362', '2015EE10691');
INSERT INTO registers (course_id, student_id) VALUES	('COL362', '2015EE30649');
INSERT INTO registers (course_id, student_id) VALUES	('COL362', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('COL331', '2015EE10691');
INSERT INTO registers (course_id, student_id) VALUES	('ELL405', '2015EE30898');
INSERT INTO registers (course_id, student_id) VALUES	('ELL405', '2015EE30649');
INSERT INTO registers (course_id, student_id) VALUES	('COL331', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('MCL131', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('MCL131', '2015ME10354');
INSERT INTO registers (course_id, student_id) VALUES	('COL331', '2015MT10592');
INSERT INTO registers (course_id, student_id) VALUES	('COL331', '2015CS10210');
INSERT INTO registers (course_id, student_id) VALUES	('COL331', '2015MT10263');
INSERT INTO registers (course_id, student_id) VALUES	('COL331', '2015MT10262'),
INSERT INTO registers (course_id, student_id) VALUES	('MCL311', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('MCL361', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('MCL361', '2015ME10354');
INSERT INTO registers (course_id, student_id) VALUES	('COP290', '2015ME10354');
INSERT INTO registers (course_id, student_id) VALUES	('MCL212', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('MCL212', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('MCL212', '2015ME10354');
INSERT INTO registers (course_id, student_id) VALUES	('MCP301', '2015ME10686');
INSERT INTO registers (course_id, student_id) VALUES	('MCP301', '2015ME10354');

INSERT INTO teaches (teacher_id, course_id) VALUES ('srsarangi', 'ELL405');
INSERT INTO teaches (teacher_id, course_id) VALUES ('srsarangi', 'COL331');
INSERT INTO teaches (teacher_id, course_id) VALUES ('suban', 'COP290');
INSERT INTO teaches (teacher_id, course_id) VALUES ('aravindam', 'MCL131');
INSERT INTO teaches (teacher_id, course_id) VALUES ('sayan', 'COL362');
INSERT INTO teaches (teacher_id, course_id) VALUES ('sudipto', 'MCP301');
INSERT INTO teaches (teacher_id, course_id) VALUES ('varunr', 'MCL361');
INSERT INTO teaches (teacher_id, course_id) VALUES ('jkdutt', 'MCL212');
