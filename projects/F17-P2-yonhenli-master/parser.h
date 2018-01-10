#ifndef _PARSER_H
#define _PARSER_H

#include <string.h>
#include <stdio.h>

/* Maximum length of name */
#define MAX_NAME_LEN	32

typedef enum _SEX {MALE = 'M', FEMALE = 'F', OTHER = 'O'} SEX;
typedef enum _ERROR_CODE { SUCCESS = 1, FAILURE = -1} ERROR_CODE;

/*
 * The course structure. 
 */
struct course {
	char grade;
	unsigned int number;
	struct course *next;
};

/*
 * The student structure. 
 */ 
struct student {
	char name[MAX_NAME_LEN];
	unsigned int age;
	SEX sex;
	float gpa;
	struct course *courses;
	struct student *next;
};

struct student_check {
	short int name_found;
	short int age_found;
	short int sex_found;
	short int gpa_found;
};

struct course_check {
	short int number_found;
	short int grade_found;
};

/* 
 * This function reads the input file in text format and stores it in memory. 
 * See sample input file for format. 
 * Lines starting with '#' are comments and must be ignored. 
 * If there is an error in input text format, the error string must contain the
 * line number where the error occurred. 
 * Also, upon error, all allocated memory must be freed. 
 */
struct student* read_txt (char *filename, char *error_string);

/* 
 * This function writes the student list and the courses to a file in text format. 
 * The first line should contain a string:
 * "# Auto generated output file!"
 * The students are written in alphabetical order (dictionary order), 
 * and the courses are written in numerically increasing order. 
 * That is, higher numbered courses follow lower numbered courses. 
 */
ERROR_CODE write_txt(char *filename, char *error_string);

/*
 * Bin format sample (also see sample file included using the hexdump program): 
 * 0xF0 0x0D
 * # students
 * student 1.name[32]
 * student 1.age
 * student 1.sex
 * student 1.gpa
 * number of courses for student 2
 * student1.course1.number
 * student1.course1.grade
 * student1.course2.number
 * student1.course2.grade
 * student 2.name[32]
 * ...
 * ...
 */
struct student* read_bin (char *filename, char *error_string);

/* 
 * This function writes the student list and the courses to a file in binary format. 
 * The first two bytes must be 0xF0 and 0x0D.
 * The students are written in alphabetical order (dictionary order), 
 * and the courses are written in numerically increasing order. 
 * That is, higher numbered courses follow lower numbered courses. 
 * SUCCESS or FAILURE is appropriately returned.
 * The error string must contain an informative error message. 
 */
ERROR_CODE write_bin(char *filename, char *error_string);

/*
 * This functions create a new student and store it in its appropriate position (following dictionary order)
 * in the list. A pointer to the newly added student structure is returned. 
 */
struct student* enroll_student(char *name, unsigned int age, SEX sex, float gpa);

/*
 * This function removes a student given the name (case sensitive).
 * A pointer to the removed student structure is returned. 
 */
struct student* remove_student(char *name);

/*
 * This function adds a course information for a student. 
 * A course structure is created and added at appropriate position in the courses list within student structure. 
 * A pointer to the newly added course is returned.  
 */ 
struct course* add_course(char *name, unsigned int number, char grade);

/*
 * This function removes a course structure from a student's course list given the student's name. 
 * A pointer to the removed structure is returned. 
 */
struct course* remove_course(char *name, unsigned int number);

/*
 * This function systematically frees all the memory. 
 * NOTE: All the memory must be freed (i.e., all students and all courses). There must be no memory leak. 
 */ 
void delete_all();

/*
 * This function lists the names of all students in the list (in alphabetical order). 
 */
void list_students();

/*
 * This function lists all the course numbers enrolled by all the students. 
 * For example, if student 1 is registered for 120, 220, 240 and 440, and 
 * student 2 is registered for 120, 340 and 580. This function prints out:
 * 120, 220, 240, 340, 440 and 580. 
 */
void list_courses();

void free_list (struct course* new_list);

int is_space(char c);

void trim(char *str);

short int str_check(char *str, short int *state, struct student_check *student_checker, struct course_check *course_checker, struct student *cs);

void str_put (struct student *cs, struct course *cc, short int state, char *str, struct student_check *student_checker, struct course_check *course_checker);

struct course *sort_course (struct student* curr_s);

struct student *sort_student ();

struct student *swap_s(struct student *prv, struct student *cur);

struct course *swap_c (struct course *head_c, struct course *prv, struct course *cur);

int get_student_num();

int get_course_num(struct course* head);

int student_found_all(struct student_check *student_checker);

int course_found_all(struct course_check *course_checker);

void reset_student_check(struct student_check *student_checker);

void reset_course_check(struct course_check *course_checker);
#endif
