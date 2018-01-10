#include <stdio.h>
#include <math.h>
#include "define.h"

int strrindex(char s[], char t[]) {
	int i = 0;
	int j = 0;
	int found = 0;
	int slen = 0;
	int tlen = 0;
	char *p;
	
	p = s;
	while (*p != '\0') {
		slen++;
		*p++;
	}

	p = t;
	while (*p != '\0') {
		tlen++;
		*p++;
	}

	if (tlen > slen) return -1;

	for (i = 0; i < slen; i++) {
		if (s[slen-i-1] == t[tlen-j-1]) {
			found = 0;
			for (j = 0; j < tlen; j++) {
				if (s[slen-i-1-j] != t[tlen-j-1]) {
					break;
				}
				found++;		
			}
			if (found == tlen) {
				return slen-i-j;
			}
		}
		j = 0;
	}

	return -1;
}

int is_int(char str[]) {
	char *p;
	int len = 0;
	int i = 0;
	
	p = str;
	while (*p != '\0') {
		len++;
		*p++;
	}
	
	/*check index 0*/
	if (len == 0) return 0;

	if (str[0] != 45 && (str[0] < 49 || str[0] > 57)) return 0;
	
	for (i = 1; i < len; i++) {
		if (str[i] < 49 || str[i] > 57) return 0;
	}

	return 1;
}

float distance (struct point p1, struct point p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x) + 
		   (p1.y-p2.y)*(p1.y-p2.y) +
		   (p1.z-p2.z)*(p1.z-p2.z));
}

int main() {
	/*	
	char s1[] = "1234567";
	char s2[] = "415";
	printf("%d\n", strrindex(s1, s2));
	*/
	/*
	char s[] = "--567";
	printf("%d\n", is_int(s));
	*/
	struct point p1;
	struct point p2;

	p1.x = 1;
	p1.y = 1;
	p1.z = 1;

	p2.x = 2;
	p2.y = 2;
	p2.z = 2;
	
	printf("%lf\n", distance(p1,p2));
	return 0;
}
