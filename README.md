# Database-Queries using C++
## HKUST Fall2020 - COMP2012 : Object-Oriented Programming and Data Structure
## Assignment1
Resource: [COMP2012 Assignment 1 Page] (https://course.cse.ust.hk/comp2012/assignments/assignment1/)

### Introduction

Suppose we are given a table of courses that are offered in Spring Semester of 2020. You can find eight courses, each of them are represented as an entry in the table. There are four attributes in the table, Department, Course Code, Course Name and Credits. An attribute characterizes information about entries.

Department	Course Code	Course Name	Credits
CSE	COMP2012	Object-Oriented Programming and Data Structures	4
CSE	COMP3021	Java Programming	3
CSE	COMP3711	Design and Analysis of Algorithms	3
CSE	COMP4511	System and Kernel Programming in Linux	3
CSE	COMP4641	Social Information Network Analysis and Engineering	3
MATH	MATH2343	Discrete Structures	4
MATH	MATH3033	Real Analysis	4
MATH	MATH4023	Complex Analysis	3
Table 1 - courses
Now we are asked to get the top 3 courses that are offered by CSE, ranked in descending order with their credits, then in ascending order with their name. This can be done by a SQL query:

SELECT * FROM courses
WHERE Department = 'CSE'
ORDER BY Credits DESC, `Course Name` ASC
LIMIT 3;
But we are taking a C++ course, aren't we? How about writing the query using the syntaxes of C++? Imagine we can translate the above SQL query into a C++ statement:

courses.query()
.where("Department", EQ, "CSE")
.orderBy("Course Name", ASCENDING)
.orderBy("Credits", DESCENDING)
.limit(3)
.select();
Looks very readable, isn't it? Your tasks in this programming assignment is to implement classes to support database queries in C++.

For those who are unfamiliar with SQL, here is a brief introduction to the SQL statements and clauses which are mimicked in this programming assignment. Click here for a full introduction to SQL.

SELECT statement retrieves information from a table in a database. Columns need to be specified explicity by a list of their names, or use * to denote all columns. In this programming assignment, the result of SELECT is printed out in a formatted way.
UPDATE statement modifies rows of a table in a database.
WHERE clause provides a condition such that SELECT and UPDATE statements return or update rows that satisfy the condition.
ORDER BY clause orders the result of SELECT statements according to the values of columns, in ascending or descending order.
LIMIT clause limits the result of SELECT and UPDATE statements. (MySQL only)
