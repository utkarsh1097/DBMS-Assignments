# README FILE.

1. Files ***part1.csv***, ***part2.sql*** and ***part3.txt*** are the test files which were use for the **Bulk Load**, **Multiple Inserts** and **JDBC method**.

2. ***jdbc.java*** is the file that connects to the database at the PostgreSQL server. Replace the asterisks with the actual password.

3. ***generator.cpp*** generates all the three test files that have been mentioned above. Function named **generatorx()** generates the relevant file for case "x".

4. ***postgresql-42.2.1.jar*** is the class package that will be used to connect to PostgreSQL server.

5. For part 1, command is ***COPY registers FROM '\<path to csv file> 'WITH DELIMITER ',';***. Command called when we are already connected to the database which has the table **registers** ready.

6. For part 2, command is ***\i '\<path to sql file>'***. Command called when we are already connected to the database which has the table **registers** ready.

7. For part 3, the command to run is ***java -cp .:postgresql-42.2.1.jar jdbc***. Command can be called when the terminal is open in the directory **code**.
