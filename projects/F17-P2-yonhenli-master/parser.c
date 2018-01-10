#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

struct student *head;

struct student* read_txt (char *filename, char *error_string) {
	if (head) delete_all();

	FILE *fp;
	char str[256]; /*store the first 256 char in every line, not including null terminator; tab is considered 2 chars*/
	memset(str, 0, sizeof(str));

	int line = 0; /*current line number*/
	char line_str[64];

	fp = fopen(filename, "r");
	if (fp == NULL) {
		sprintf(error_string, "File could not be opened: %s", filename);
		return NULL;
	}

	short int state = 0; /*tell the program where it is*/
	struct student *temp_s = (struct student *)malloc(sizeof(struct student));
	struct course *temp_c = (struct course *)malloc(sizeof(struct course));

	/*initialize the student checker and the course checker*/
	struct student_check *student_checker = (struct student_check *)malloc(sizeof(struct student_check));
	struct course_check *course_checker = (struct course_check *)malloc(sizeof(struct course_check));
	reset_student_check(student_checker);
	reset_course_check(course_checker);

	if (!temp_s || !temp_c || !student_checker ||!course_checker) {
		strcpy(error_string, "allocation error!");
		free(temp_c);
		free(temp_s);
		free(student_checker);
		free(course_checker);
		fclose(fp);
		return NULL;
	}

	while (fgets(str, 256, fp) != NULL) {
		line ++;
		trim(str);
		if (str[0] != '\0' && str[0] != '#') {
			if (! str_check(str, &state, student_checker, course_checker, temp_s)){
				delete_all();
				free(temp_c);
				free(temp_s);
				free(student_checker);
				free(course_checker);
				fclose(fp);
				
				/*report errors*/
				strcpy(error_string, filename);
				strcat(error_string, ":");
				sprintf(line_str, "%d", line);
				strcat(error_string, line_str);
				strcat(error_string, ": Parse error.");

				return NULL;
			}
			else {
				str_put(temp_s, temp_c, state, str, student_checker, course_checker);
			}
		}

		memset(str, 0, sizeof(str));
	}

	free(temp_c);
	free(temp_s);
	free(student_checker);
	free(course_checker);
	fclose(fp);
	return head;
}


ERROR_CODE write_txt (char *filename, char *error_string) {
	if (!head) return SUCCESS;

	FILE *fp = fopen(filename, "w");
	if (!fp) {
		strcpy(error_string, "allocation error!");
		return FAILURE;
	}

	char str[256] = "# Auto generated output file!\n\n";
	fwrite(str, 1, strlen(str), fp);

	struct student *curr_s = head;
	struct course *curr_c = curr_s -> courses;

	while(curr_s) {
		if (curr_s -> courses) {
			strcpy(str, "student {\n");
			fwrite(str, strlen(str), 1, fp);
			memset(str, 0, sizeof(str));

			strcpy(str, "\tname = ");
			strcat(str, curr_s -> name);
			fwrite(str, strlen(str), 1, fp);
			memset(str, 0, sizeof(str));

			strcpy(str, "\n\tage  = ");
			fwrite(str, strlen(str), 1, fp);
			sprintf(str, "%d", curr_s -> age);
			fwrite(str, strlen(str), 1, fp);
			memset(str, 0, sizeof(str));

			strcpy(str, "\n\tsex  = ");
			fwrite(str, strlen(str), 1, fp);
			memset(str, 0, sizeof(str));
			if (curr_s->sex == MALE) {
				strcat(str, "M");
			}
			else if(curr_s->sex == FEMALE) {
				strcat(str, "F");
			}
			else if (curr_s->sex == OTHER) {
				strcat(str, "O");
			}
			fwrite(str, 1, 1, fp);
			memset(str, 0, sizeof(str));

			strcpy(str, "\n\tgpa  = ");
			fwrite(str, strlen(str), 1, fp);
			sprintf(str, "%f", curr_s -> gpa);
			fwrite(str, strlen(str), 1, fp);
			memset(str, 0, sizeof(str));

			while (curr_c) {
				strcpy(str, "\n\tcourse {\n");
				fwrite(str, strlen(str), 1, fp);
				memset(str, 0, sizeof(str));

				strcpy(str, "\t\tnumber = ");
				fwrite(str, strlen(str), 1, fp);
				sprintf(str, "%d", curr_c -> number);
				fwrite(str, strlen(str), 1, fp);
				memset(str, 0, sizeof(str));

				strcpy(str, "\n\t\tgrade  = ");
				fwrite(str, strlen(str), 1, fp);
				fwrite(&(curr_c -> grade), 1, 1, fp);
				memset(str, 0, sizeof(str));

				strcpy(str, "\n\t}");
				fwrite(str, strlen(str), 1, fp);
				memset(str, 0, sizeof(str));

				curr_c = curr_c -> next;
			}
			
			strcpy(str, "\n}\n\n");
			fwrite(str, strlen(str), 1, fp);
			memset(str, 0, sizeof(str));	
		}

		curr_s = curr_s -> next;
		if (curr_s) {
			curr_c = curr_s -> courses;
		}
	}

	fclose(fp);
	return SUCCESS;
}

struct student *read_bin (char *filename, char *error_string) {
	if (head) delete_all();
	
	FILE *fp = fopen(filename, "rb");
	if (!fp){
		strcpy(error_string, "File could not be opened");
		return NULL;
	}
	struct student *temp_s = (struct student *) malloc(sizeof(struct student));
	struct course *temp_c = (struct course *) malloc(sizeof(struct course));
	if (!temp_s || !temp_c) {
		free(temp_s);
		free(temp_c);
		fclose(fp);

		strcpy(error_string, "allocation error!");
		return NULL;
	}

	char str[64];
	memset(str, 0, sizeof(str));

	int num = 0;
	float gpa = 0.0;
	int num_stud = 0;
	int num_crs = 0;
	short int ret,i, j = 0;

	fread(&num, 1, 2, fp);
	if (num != 0xdf0) {
		free(temp_s);
		free(temp_c);
		fclose(fp);

		strcpy(error_string, filename);
		strcat(error_string, ": Invalid binary file format.");
		return NULL;
	}
	
	ret = fread(&num_stud, sizeof(num_stud), 1, fp);
	if (!ret) {
		free(temp_s);
		free(temp_c);
		fclose(fp);

		strcpy(error_string, filename);
		strcat(error_string, ": Invalid binary file format.");
		return NULL;
	}

	if (num_stud < 0) {
		free(temp_s);
		free(temp_c);
		fclose(fp);

		strcpy(error_string, filename);
		strcat(error_string, ": Invalid binary file format.");
		return NULL;
	}

	for (i = 0; i < num_stud; i++) {
		/*check name*/
		memset(str, 0, sizeof(str));
		memset(temp_s->name, 0, sizeof(temp_s->name));
		ret = fread(&str, 32, 1, fp);
		if (!ret) {
			free(temp_s);
			free(temp_c);
			delete_all();

			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}
		/*set name*/
		for (j = 0; j < strlen(str); j++) {
			temp_s -> name[j] = str[j]; 
		}
		memset(str, 0, sizeof(str));

		/*check age*/
		ret = fread(&num, 4, 1, fp);
		if (!ret) {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}
		if (num < 0) {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}
		/*set age*/
		temp_s -> age = num;


		/*check sex*/
		ret = fread(&str, 4, 1, fp);
		if (!ret) {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}
		if (str[0] != 'M' && str[0] != 'F' && str[0] != 'O') {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}
		/*set sex*/
		if (str[0] == 'M') {
			temp_s -> sex = MALE;
		}

		else if (str[0] == 'F') {
			temp_s -> sex = FEMALE;
		}

		else if (str[0] == 'O') {
			temp_s -> sex = OTHER;
		}
		memset(str, 0, sizeof(str));

		/*check gpa*/
		ret = fread(&gpa, 4, 1, fp);
		if (!ret) {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}
		if (gpa < 0.0 || gpa > 4.0) {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}
		/*set gpa*/
		temp_s -> gpa = gpa;

		/*create a new student*/
		enroll_student(temp_s->name, temp_s->age, temp_s->sex, temp_s->gpa);
		
		/*check number of courses*/
		ret = fread(&num_crs, 4, 1, fp);
		if (!ret) {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}

		if (num_crs <= 0) {
			free(temp_s);
			free(temp_c);
			delete_all();
			fclose(fp);

			strcpy(error_string, filename);
			strcat(error_string, ": Invalid binary file format.");
			return NULL;
		}

		for (j = 0; j < num_crs; j++) {
			/*check number*/
			ret = fread(&num, 4, 1, fp);
			if (!ret) {
				free(temp_s);
				free(temp_c);
				delete_all();
				fclose(fp);

				strcpy(error_string, filename);
				strcat(error_string, ": Invalid binary file format.");
				return NULL;
			}
			if (num < 0) {
				free(temp_s);
				free(temp_c);
				delete_all();
				fclose(fp);

				strcpy(error_string, filename);
				strcat(error_string, ": Invalid binary file format.");
				return NULL;
			}
			/*set number*/
			temp_c -> number = num;


			/*check grade*/
			ret = fread(&str, 1, 1, fp);
			if (!ret) {
				free(temp_s);
				free(temp_c);
				delete_all();
				fclose(fp);

				strcpy(error_string, filename);
				strcat(error_string, ": Invalid binary file format.");
				return NULL;
			}
			if (str[0] < 'A' || str[0] > 'F') {
				free(temp_s);
				free(temp_c);
				delete_all();
				fclose(fp);

				strcpy(error_string, filename);
				strcat(error_string, ": Invalid binary file format.");
				return NULL;
			}

			/*set grade*/
			temp_c -> grade = str[0];
			memset(str, 0, sizeof(str));

			/*add a course*/
			add_course(temp_s->name, temp_c->number, temp_c->grade);
		}

		memset(temp_s->name, 0, sizeof(temp_s->name));
	}
	free(temp_s);
	free(temp_c);

	fclose(fp);
	return head;
}

ERROR_CODE write_bin (char *filename, char *error_string) {
	if (!head) return SUCCESS;

	FILE *fp = fopen(filename, "wb");
	if (!fp){
		strcpy(error_string, "allocation error!");
		return FAILURE;
	}

	short int identifiers = 0;
	int num_crs = 0;
	int num_stud = get_student_num();

	/*write beginning identifiers*/
	identifiers = 0x0df0;
	fwrite(&identifiers, sizeof(identifiers), 1, fp);

	struct student *curr_s = head;
	struct course *curr_c = curr_s -> courses;

	/*write number of students*/
	fwrite(&num_stud, sizeof(num_stud), 1, fp);

	/*still need get course num*/
	while (curr_s) {
		if (curr_s -> courses){
			/*write name of the first student*/
			fwrite(&(curr_s->name), sizeof(curr_s->name), 1, fp);

			/*write age of student*/
			fwrite(&(curr_s->age), sizeof(curr_s->age), 1, fp);

			/*write sex of student*/
			fwrite(&(curr_s->sex), sizeof(curr_s->sex), 1, fp);

			/*write gpa of student*/
			fwrite(&(curr_s->gpa), sizeof(curr_s->gpa), 1, fp);

			/*write the number of courses*/
			num_crs = get_course_num(curr_s->courses);
			fwrite(&num_crs, sizeof(num_crs), 1, fp);

			while (curr_c) {
				/*write number of course*/
				fwrite(&(curr_c->number), sizeof(curr_c->number), 1, fp);

				/*write grade of course*/
				fwrite(&(curr_c->grade), sizeof(curr_c->grade), 1, fp);

				curr_c = curr_c -> next;
			}
		}
		curr_s = curr_s -> next;
		if (curr_s) curr_c = curr_s -> courses;
	}

	fclose(fp);
	return SUCCESS;
}

struct student* enroll_student(char *name, unsigned int age, SEX sex, float gpa) {
	struct student *new_student = (struct student *)malloc(sizeof(struct student));
	/*this block sets name*/
	memset(new_student -> name, 0, sizeof(new_student -> name));
	short int i = 0;
	for (i = 0; i < strlen(name); i++) {
		new_student -> name[i] = name[i];
	}

	new_student -> age = age;
	new_student -> gpa = gpa;
	new_student -> sex = sex;
	new_student -> courses = NULL;

	if (head == NULL) {
		new_student -> next = NULL;
		head = new_student;
	}

	else {
		struct student *temp_next = head -> next;
		head -> next = new_student;
		new_student -> next = temp_next;
	}

	head = sort_student();

	return new_student;
}

/*WHAT DO WE RETURN IF THE STUDENT IS NOT FOUND*/
struct student* remove_student (char *name) {
	struct student* current = head;
	struct student* previous = head;
	while (current) {
		if (strcmp(current -> name, name) == 0) {
			if (current == head) {
				head = current -> next;
				return current;
			}
			previous -> next = current -> next;
			return current;
		}
		previous = current;
		current = current -> next;
	}
	/*WHAT DO WE RETURN IF THE STUDENT IS NOT FOUND*/
	return head;
}

/*WHAT DO WE RETURN IF THE STUDENT IS NOT FOUND*/
struct course* add_course (char *name, unsigned int number, char grade) {
	struct course *new_course = (struct course*)malloc(sizeof(struct course));

	new_course -> number = number;
	new_course -> grade = grade;

	struct student* current = head;
	while (current) {
		if (strcmp(current -> name, name) == 0) {
			if (current -> courses == NULL) {
				new_course -> next = NULL;
				current -> courses = new_course;
			}
			else {
				struct course *temp_next = (current -> courses) -> next;
				(current -> courses) -> next = new_course;
				new_course -> next = temp_next;
			}
			
			current -> courses = sort_course(current);

			return new_course;
		}
		current = current -> next;
	}

	free(new_course);
	/*WHAT DO WE RETURN IF THE STUDENT IS NOT FOUND*/
	return head -> courses;
}

/*WHAT DO WE RETURN IF THE STUDENT IS NOT FOUND*/
struct course* remove_course (char *name, unsigned int number) {
	if (!head) return NULL;
	struct student* current = head;
	struct student* previous = head;

	struct course* hc = head -> courses;

	while (current) {
		if (strcmp(current -> name, name) == 0) {
			struct course* cc = current -> courses;
			struct course* pc = previous -> courses;
			while (cc) {
				if (cc -> number == number) {
					if (cc == hc) {
						current -> courses = cc -> next;
						return cc;
					}
					pc -> next = cc -> next;
					return cc;
				}
				pc = cc;
				cc = cc -> next;
			}
		}
		previous = current;
		current = current -> next;
	}

	/*WHAT DO WE RETURN IF THE STUDENT IS NOT FOUND*/
	return hc;
}

void delete_all () {
	if (!head) return;
	struct student* current = head;
	struct course* cc = current -> courses;
	while (current) {
		while (cc) {
			struct course* temp;
			temp = remove_course(current -> name, cc -> number);
			free(temp);

			cc = current -> courses;
		}

		struct student* temp;
		temp = remove_student(current -> name);
		free(temp);

		current = head;
		if (current) cc = current -> courses;
	}
}

/*FORMAT?*/
void list_students () {
	struct student *temp_head = head;
	while(temp_head) {
		if (temp_head->courses) {
			printf("%s", temp_head -> name);
			printf("\n");
		}
			temp_head = temp_head -> next;
	}
}

void list_courses() {
	if (!head) {
		printf("\n");
		return;
	}

	struct course *new_list = (struct course*) malloc(sizeof(struct course));
	if (!new_list) {
		return;
	}
	new_list = head -> courses;
	if (new_list == NULL) {
		new_list = head -> next -> courses;
	}

	struct course *current_list;
	struct student *current_student = head;
	struct course *current_course = current_student -> courses;

	/*to see if class is already in list*/
	short int found = 0;

	while (current_student) {
		while (current_course) {
			current_list = new_list;
			while (current_list && !found) {
				if (current_course -> number == current_list -> number) {
					found = 1;
				}
				current_list = current_list -> next;
			}
			if (!found) {
				struct course *new_course = (struct course*) malloc(sizeof(struct course));
				if (!new_course) {
					return;
				}
				new_course -> number = current_course -> number;
				new_course -> next = new_list -> next;
				new_list -> next = new_course;
			}
			current_course = current_course -> next;
			found = 0;
		}
		current_student = current_student -> next;
		if (current_student) current_course = current_student -> courses;
	}

	/*this is used to sort the course list; new head: new_list*/
	struct course *cur;
	struct course *prv;
	cur = prv = new_list;

	while (cur -> next != NULL) {
		if (cur -> number > (cur -> next) -> number) {
			new_list = swap_c(new_list, prv, cur);
			prv = cur = new_list;
		}
		
		else {
			prv = cur;
			cur = cur -> next;
		}
	}

	while(new_list) {
		printf("%d", new_list -> number);
		printf("\n");
		new_list = new_list -> next;
	}
	free_list(new_list);
}

void free_list (struct course* new_list) {
	if (!new_list) return;
	struct course* current = new_list;

	struct course* next_course = current -> next;
	free(current);

	while(next_course) {
		current = next_course;
		if (next_course -> next) next_course = next_course -> next;
		free(current);
	}
}

int is_space(char c) {
	if ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n') || (c == '\v') || (c == '\f')) {
		return 1;
	}

	return 0;
}

void trim(char *str) {
	int i,j,c = 0;
	int begin = 0;
	int end = strlen(str) - 1;
	while (is_space(str[begin])) begin++;

	while((end >= begin) && is_space(str[end])) end--;

	for (i = begin; i <= end; i++) {
		str[i-begin] = str[i];
	}

	str[i-begin] = '\0';

	for (i = 0; i < strlen(str); i++) {
		if (is_space(str[i])) {
			for (j = i+1; j < strlen(str); j++) {
				str[j-1] = str[j];
			}
			c++;
			i--;
		}
	}
	str[strlen(str)-c] = '\0';
}

short int str_check(char *str, short int *state, struct student_check *student_checker, struct course_check *course_checker, struct student *cs) {
	int i = 0;

	/*state 0: nothing has been catched*/
	if (*state == 0) {
		if (strstr(str, "student{")) {
			if (strlen(str) == 8) {
				*state = 1;
				return 1;
			}
		}
	
		return 0;	
	}

	/*if 0 < state < 5, it has not received all the informaiton for a student*/
	else if (!student_found_all(student_checker)) {

		/*CASE 1: if str starts with 'name=', state will be set as 2*/
		if (strstr(str, "name=")) {
			char *name_cmp = "name=";

			/*make sure the given string is longer than specification*/
			if (strlen(str) == 5) {
				return 0;
			}

			/*up to here, the beginning should be matched
			then we check the string after the '=' sign*/
			for (i = strlen(name_cmp); i < strlen(str); i++) {
				/*make sure everything is letter*/
				if ((str[i] < 65) || str[i] > 90) {
					if (str[i] < 97 || str[i] > 122) {
						return 0;
					}
				}
			}

			/*update state to 2, so str_put knows this line contains a name*/
			*state = 2;
			/*flag that name was found*/
			student_checker -> name_found = 1;
			return 1;
		}

		/*CASE 2: if str starts with 'age=', state will be set as 3*/
		else if (strstr(str, "age=")) {
			/*make sure the given string is longer than specification*/
			if (strlen(str) == 4) {
				return 0;
			}

			/*up to here, the beginning should be matched
			then we check the string after the '=' sign*/
			char *temp_str = strstr(str, &str[4]);
			int age = atoi(temp_str);
			if (age <= 0) {
				return 0;
			}

			*state = 3;
			student_checker -> age_found = 1;
			return 1;
		}

		/*CASE 3: if str starts with 'sex=', state will be set as 4*/
		else if (strstr(str, "sex=")) {
			/*make sure the given string is longer than specification*/
			if (strlen(str) > 5) {
				return 0;
			}

			/*up to here, the beginning should be matched
			then we check the string after the '=' sign*/
			if (strlen(str) > 5) return 0;
			if (str[4] != 'M' && str[4] != 'F' && str[4] != 'O') {
				return 0;
			}

			*state = 4;
			student_checker -> sex_found = 1;
			return 1;
		}

		/*CASE 4: if str starts with 'gpa=', state will be set as 5*/
		else if (strstr(str, "gpa=")) {
			/*make sure the given string is longer than specification*/
			if (strlen(str) == 4) {
				return 0;
			}

			/*up to here, the beginning should be matched
			then we check the string after the '=' sign*/
			char *temp_str = strstr(str, &str[4]);
			double gpa = atof(temp_str);
			if (gpa <= 0.0 || gpa > 4.0) {
				return 0;
			}

			*state = 5;
			student_checker -> gpa_found = 1;
			return 1;
		}

		/*CASE 5: if nothing is matched, it means str is junk*/
		else {
			return 0;
		}
	}

	/*check whether the str is '}' or "course{"*/
	else if (*state <= 5 && student_found_all(student_checker)) {
		/*if it is a '}', it means that student doesn't have a class,
		  we reset the state to 0*/
		if (str[0] == '}') {
			if (strlen(str) > 1) return 0;
			*state = 0;
			/*we finished a student, reset the student checker*/
			memset(cs -> name, 0, sizeof(cs -> name));
			reset_student_check(student_checker);
			return 1;
		}

		/*if it starts with "course{"*/
		else if (strstr(str, "course{")){

			/*if there is any char follow "course{"*/
			if (strlen(str) > 7) {
				return 0;
			}

			*state = 6;
			return 1;
		}
		
		/*if str doesn't match either '}' or "course{"*/
		return 0;
	}

	/*we are expecting either a nubmer or a grade*/
	else if (!course_found_all(course_checker)) {
		/*CASE 1: if str starts with 'number=', state will be set as 7*/
		if (strstr(str, "number=")) {
			/*make sure the given string is longer than specification*/
			if (strlen(str) == 7) {
				return 0;
			}

			/*check whatever after equal sign is digit*/
			char *temp_str = strstr(str, &str[7]);
			int num = atoi(temp_str);
			if (num <= 0) {
				return 0;
			}

			if (num < 100 || num > 1000) return 0;

			*state = 7;
			course_checker -> number_found = 1;
			return 1;
		}

		/*CASE 2: if str starts with 'grade=', state will be set as 8*/
		else if (strstr(str, "grade=")) {
			/*make sure the given string is longer than we want*/
			if (strlen(str) > 7) {
				return 0;
			}

			/*check whatever afer the equal sign meet the specificaitons*/
			if (str[6] < 'A' || str[6] > 'F') {
				return 0;
			}

			*state = 8;
			course_checker -> grade_found = 1;
			return 1;
		}

		/*CASE 3: Junk*/
		else return 0;
	}
	
	else if (*state <= 8 && course_found_all(course_checker)) {
		if (str[0] == '}') {
			if (strlen(str) > 1) return 0;

			*state = 9;
			return 1;
		}

		return 0;
	}

	else if (*state == 9) {
		/*this ends a student*/
		if (str[0] == '}') {
			if (strlen(str) > 1) return 0;
			memset(cs -> name, 0, sizeof(cs -> name));
			reset_student_check(student_checker);
			reset_course_check(course_checker);
			*state = 0;
			return 1;
		}

		/*if there are some more courses*/
		else if (strstr(str, "course{")) {
			if (strlen(str) > 7) return 0;

			*state = 6;
			reset_course_check(course_checker);
			return 1;
		}

		/*Junk*/
		return 0;
	}
	
	return 0;
}

void str_put (struct student *cs, struct course *cc, short int state, char *str, struct student_check *student_checker, struct course_check *course_checker) {
	if (state == 1) {
		return;
	}

	else if (state == 2) {
		/*name=...*/
		char *temp_str = strstr(str, &str[5]);
		short int i = 0;
		for (i = 0; i < strlen(temp_str); i++) {
			cs -> name[i] = temp_str[i];
		}

		/*after found name, age, sex, gpa, we enroll a student*/
		if (student_found_all(student_checker)) {
			enroll_student(cs->name, cs->age, cs->sex, cs->gpa);
		}
	}

	else if (state == 3) {
		/*age=...*/
		char *temp_str = strstr(str, &str[4]);
		cs -> age = atoi(temp_str);

		if (student_found_all(student_checker)) {
			enroll_student(cs->name, cs->age, cs->sex, cs->gpa);
		}
	}

	else if (state == 4) {
		/*sex=*/
		char sex = str[4];
		if (sex == 'M') {
			cs -> sex = MALE;
		}

		else if (sex == 'F') {
			cs -> sex = FEMALE;
		}

		else if (sex == 'O') {
			cs -> sex = OTHER;
		}

		if (student_found_all(student_checker)) {
			enroll_student(cs->name, cs->age, cs->sex, cs->gpa);
		}
	}

	/*after we found GPA, we enroll a student*/
	else if (state == 5) {
		char *temp_str = strstr(str, &str[4]);
		cs -> gpa = atof(temp_str);

		if (student_found_all(student_checker)) {
			enroll_student(cs->name, cs->age, cs->sex, cs->gpa);
		}
	}

	/*if it is state 5, we do nothing, prepare to receive a number or a grade*/
	else if (state == 6) {

		return;
	}

	else if (state == 7) {
		char *temp_str = strstr(str, &str[7]);
		cc -> number = atoi(temp_str);

		if (course_found_all(course_checker)) {
			add_course(cs->name, cc->number, cc->grade);
		}

	}

	else if (state == 8) {
		cc -> grade = str[6];

		if (course_found_all(course_checker)) {
			add_course(cs->name, cc->number, cc->grade);
		}
	}

	else if (state == 9) {
	}
}

struct course *swap_c (struct course *head_c, struct course *prv, struct course *cur) {
	struct course *next_temp;
	struct course *new_head;

	/*cur isn't the head of courses*/
	if (cur != head_c) {
		prv -> next = cur -> next;
		next_temp = cur -> next;
		cur -> next = (cur -> next) -> next;
		next_temp -> next = cur;

		return head_c;
	}

	else {
		new_head = cur -> next;
		next_temp = cur -> next;
		cur -> next = (cur -> next) -> next;
		next_temp -> next = cur;

		return new_head;
	}
}

struct student *swap_s(struct student *prv, struct student *cur) {
	struct student *next_temp;
	struct student *new_head;

	if (cur != head) {
		prv -> next = cur -> next;
		next_temp = cur -> next;
		cur -> next = (cur -> next) -> next;
		next_temp -> next = cur;

		return head;
	}

	else {
		new_head = cur -> next;
		next_temp = cur -> next;
		cur -> next = (cur -> next) -> next;
		(next_temp) -> next = cur;

		return new_head;
	}
}

struct student *sort_student () {
	struct student *cur;
	struct student *prv;

	cur = prv = head;

	while (cur -> next != NULL) {

		if (strcmp((cur -> name), (cur -> next) -> name) > 0) {
			head = swap_s(prv, cur);

			prv = cur = head;
		}

		else {
			prv = cur;

			cur = cur -> next;
		}
	}

	return head;
}

struct course *sort_course (struct student* curr_s) {
	struct course *cur;
	struct course *prv;
	struct course *head_c;
	cur = prv = head_c = curr_s -> courses;

	while (cur -> next != NULL) {
		if (cur -> number > (cur -> next) -> number) {
			head_c = swap_c(head_c, prv, cur);

			prv = cur = head_c;
		}
		
		else {
			prv = cur;
			cur = cur -> next;
		}
	}

	return head_c;
}

int get_student_num() {
	int num = 0;
	struct student *current = head;
	while (current) {
		if (current -> courses) num++;
		current = current -> next;
	}

	return num;
}

int get_course_num(struct course* hc) {
	int num = 0;
	struct course *current = hc;
	while (current) {
		num++;
		current = current -> next;
	}

	return num;
}

int student_found_all(struct student_check *student_checker) {
	if (student_checker -> name_found && student_checker -> age_found &&
		student_checker -> sex_found && student_checker -> gpa_found) {
		return 1;
	}

	return 0;
}

void reset_student_check(struct student_check *student_checker) {
	student_checker -> name_found = 0;
	student_checker -> age_found = 0;
	student_checker -> sex_found = 0;
	student_checker -> gpa_found = 0;
}

int course_found_all(struct course_check *course_checker) {
	if (course_checker -> number_found && course_checker -> grade_found) {
		return 1;
	}

	return 0;
}

void reset_course_check(struct course_check *course_checker) {
	course_checker -> number_found = 0;
	course_checker -> grade_found = 0;
}

