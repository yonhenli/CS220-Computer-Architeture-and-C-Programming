#include "functions.h"
#include<stdio.h>
#include<string.h>

static unsigned long buffer;
static unsigned long setbit[65];

int isFib(unsigned long i) {
	/*check special case*/
	if (i < 0 || i > 1000000000) {
		return -1;
	}
	if (i == 0) return 1;
	if (i == 1) return 2;
	unsigned long fib1, fib2, fib3;
	int counter;

	fib1 = 0;
	fib2 = 1;
	fib3 = 1;
	for (counter = 1; fib3 <= i; counter++){
		fib3 = fib1 + fib2;
		if (fib3 == i) return counter + 2;
		if (fib3 > i) return -1;
		fib1 = fib2;
		fib2 = fib3;
	}

	return 0;	
}

unsigned int count_vowels_helper(char parts[]) {
	char *count0[] = {"hundred", "thousand", "million", "billion"};
	char *count1[] = {"one", "two", "three", "four", "five", "six",
	       	          "seven", "eight", "nine"};
	char *count2[] = {"eleven","twelve", "thirteen", "fourteen","fifteen",
	       	          "sixteen", "seventeen", "eighteen", "nineteen"};
	char *count3[] = {"ten", "twenty", "thirty", "forty", "fift",
	       		  "sixty", "seventy", "eighty","ninety"};
	char buffer[256];
	char *(*ptr)[10];
	
	int i;
	int vowels;
	i = 0;
	vowels = 0;
	
/*	printf("this is the received substr: %s\n", parts);*/
	/*case: "00x" && "..x"*/
	if (strlen(parts)==1||(parts[0]==(0+'0')&&parts[1]==(0+'0')&&
			       parts[2]!=(0+'0'))){

		/*match the last element*/
		for(i = 0; i <= 9; i++){
			if (parts[strlen(parts)-1] == (i+'0')){
				ptr = &count1;
				strcpy(buffer, ((*ptr)[i-1]));
				break;
			}
		}	
	}
		
	/*case: "000"*/
	else if (parts[0] == (0+'0') && parts[1] == (0+'0') &&
		 parts[2] == (0+'0')) return 0;
	
	/*case: "010", ".10", "01x", ".1x"*/
	else if (parts[strlen(parts)-2]==(1+'0')&&(strlen(parts)==2||parts[0]==0)){
		/*case: "010" && ".10"*/
		if (parts[strlen(parts)-1] == 0+'0') {
			ptr = &count3;
			strcpy(buffer, ((*ptr)[0]));
		}

		/*match the last digit*/
		else{
			for(i = 0; i <= 9; i++){
				if (parts[strlen(parts)-1] == (i+'0')){
					ptr = &count2;
					strcpy(buffer, ((*ptr)[i-1]));
					break;
				}
			}
		}
	}
	
	/*case: "020", "021", "20", "21"*/
	else if (strlen(parts)==2 || parts[0]==(0+'0')){
		for(i = 0; i <= 9; i++){
			/*match the first digit*/
			if (parts[strlen(parts)-2] == (i+'0')){
				ptr = &count3;
				strcpy(buffer, ((*ptr)[i-1]));
				
				/*match the second digit*/
				for(i = 1; i <= 9; i++){
					if (parts[strlen(parts)-1] == (i+'0')){
						ptr = &count1;
						strcat(buffer, ((*ptr)[i-1]));
						break;
					}
				}
				break;
			}
		}
	}
	
	/*case: "200", "211", ""222"*/
	else if (strlen(parts)==3){
		/*match the first digit ----- add x hundred*/
		for (i = 1; i <= 9; i++){
			if (parts[strlen(parts)-3] == (i+'0')){
				ptr = &count1;
				strcpy(buffer, ((*ptr)[i-1]));
				strcat(buffer, "hundred");
			}
		}
		
		/*case: "200" ----- do nothing*/
		if ((parts[strlen(parts)-2]==0+'0')&&
			(parts[strlen(parts)-1]==0+'0'));
		
		/*case: "210", "211"*/
		else if (parts[strlen(parts)-2]==(1+'0')){
			/*case: "210"*/
			if (parts[strlen(parts)-1] == 0+'0') {
				ptr = &count3;
				strcat(buffer, ((*ptr)[0]));
			}
			/*case: "211"*/
			else{
				for(i = 0; i <= 9; i++){
					if (parts[strlen(parts)-1] == (i+'0')){
						ptr = &count2;
						strcat(buffer, ((*ptr)[i-1]));
						break;
					}
				}
			}
		}

		/*case: "222"*/
		else{
			for(i = 0; i <= 9; i++){
				/*match the second digit*/
				if (parts[strlen(parts)-2] == (i+'0')){
					if (i>0){
						ptr = &count3;
						strcat(buffer, ((*ptr)[i-1]));
					}

					/*match the third digit*/
					for(i = 1; i <= 9; i++){
						if (parts[strlen(parts)-1] == (i+'0')){
							ptr = &count1;
							strcat(buffer, ((*ptr)[i-1]));
							break;
						}
					}
					break;
				}
			}
		}
		
		
	}
	
	/*calculate the vowels*/
	for (i = 0; buffer[i] != '\0'; i++){
		if (buffer[i]=='a'||buffer[i]=='e'||buffer[i]=='i'||
		    buffer[i]=='o'||buffer[i]=='u')vowels++;
	}

	return vowels;
}	

unsigned int count_vowels(unsigned long num) {
	/*check special cases*/
	if (num < 0 || num > 1000000000) return 0;
	if (num == 0) return 2;
	if (num == 1000000000) return 5;
	
	char subbuff[256];
	char buffer[256];
	int i;
	int rmd;
	int len;
	int v1;
	int v2;
	int vowels;

	i = 0;
	rmd = 0;
	len = 0;
	v1 = 0;
	v2 = 0;
	vowels = 0;

	sprintf(buffer, "%lu", num);	
	len = strlen(buffer);
		
	/*case: 10-100*/
	if(len <= 3){
		memset(subbuff, '\0', sizeof(subbuff));
		strncpy(subbuff, buffer, len);
		vowels += count_vowels_helper(subbuff);
			
	}
	/*case: 10,000,000; 100,000,000 ---- xxx billion xxx thousand xxx*/
	else if (len >= 7) {
		/*check the validality of 6-4, 3-1 digits*/
		for (i = 0; i<6; i++){
			if (i<3) {
				if (buffer[len-(6-i)]!=(0+'0'))	v1=1;
			}
			else {
				if (buffer[len-(6-i)]!=(0+'0'))	v2=1;
			}
		}


		rmd = len%3;
		/*if it has 2 rmd*/
		if (rmd == 2) {
			memset(subbuff, '\0', sizeof(subbuff));
			strncpy(subbuff, buffer, 2);
			vowels = vowels + 3;
			vowels += count_vowels_helper(subbuff);
			if (v1 == 1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+2, 3);
				vowels = vowels + 3;
				vowels += count_vowels_helper(subbuff);	
			}
			if (v2 == 1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+5, 3);
				vowels += count_vowels_helper(subbuff);	
			}
		}

		/*if it has 1 rmd*/
		else if (rmd == 1) {
			memset(subbuff, '\0', sizeof(subbuff));
			strncpy(subbuff, buffer, 1);
			vowels = vowels + 3;
			vowels += count_vowels_helper(subbuff);
			if (v1 == 1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+1, 3);
				vowels = vowels + 3;
				vowels += count_vowels_helper(subbuff);	
			}
			if (v2 == 1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+4, 3);
				vowels += count_vowels_helper(subbuff);	
			}
		}

		/*if it does not have a rmd*/
		else {
			memset(subbuff, '\0', sizeof(subbuff));
			strncpy(subbuff, buffer, 3);
			vowels = vowels + 3;
			vowels += count_vowels_helper(subbuff);
			if (v1 == 1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+3, 3);
				vowels = vowels + 3;
				vowels += count_vowels_helper(subbuff);	
			}
			if (v2 == 1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+6, 3);
				vowels += count_vowels_helper(subbuff);	
			}	
		}	
	}

	
	/*case: 100,000; 10,000 ---- xxx thousand xxx*/
	else if (len >= 4) {
		/*check the validality of 6-4, 3-1 digits*/
		for (i = 0; i<3; i++){
			if (i<3) {
				if (buffer[len-(6-i)]!=(0+'0'))	v1=1;
			}
		}

		rmd = len%3;
		/*if it has 2 rmd*/
		if (rmd == 2) {
			memset(subbuff, '\0', sizeof(subbuff));
			strncpy(subbuff, buffer, 2);
			vowels = vowels + 3;
			vowels += count_vowels_helper(subbuff);
			if (v1==1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+2, 3);
				vowels += count_vowels_helper(subbuff);	
			}
		}

		/*if it has 1 rmd*/
		else if (rmd==1) {
			memset(subbuff, '\0', sizeof(subbuff));
			strncpy(subbuff, buffer, 1);
			vowels = vowels + 3;
			vowels += count_vowels_helper(subbuff);
			if (v1==1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+1, 3);
				vowels += count_vowels_helper(subbuff);	
			}
		}

		/*if it x a rmd*/
		else {
			memset(subbuff, '\0', sizeof(subbuff));
			strncpy(subbuff, buffer, 3);
			vowels = vowels + 3;
			vowels += count_vowels_helper(subbuff);
			if (v1 == 1) {
				memset(subbuff, '\0', sizeof(subbuff));
				strncpy(subbuff, buffer+3, 6);
				vowels += count_vowels_helper(subbuff);	
			}
		}	
	}

	return vowels;
}

unsigned int count_ones(long n) {
  	char buffer[65], tsc[65], temp;
	long i, j, add, n1 = 0;
	int count = 0;
	n1 = n;

	memset(buffer, '\0', sizeof(buffer));	
	memset(tsc, '\0', sizeof(tsc));	

	/*find the binary expression*/
	while (n != 0) {
		if (n%2 == 1 || n%2 == -1){
			if (strlen(buffer) == 0) {
				strcpy(buffer, "1");
			}

			else {
				strcat(buffer, "1");
			}
			n = n/2;
		}

		else {
			if (strlen(buffer) == 0) {
				strcpy(buffer, "0");
			}
			
			else {
				strcat(buffer, "0");
			}
			n = n/2;
		}
	}
	
	
	/*add the missing bits*/
	for (i = strlen(buffer); i < (sizeof(buffer) - 1); i++) {
		buffer[i] = '0';
	}

	/*reverse the string to correct order*/
	i = 0;
	j = strlen(buffer) - 1;
	while(i < j) {
		temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
		i++;
		j--;
	}
	
	/*case: negative number*/
	if (n1 < 0){
		/*flip each digit*/
		for (i = 0; i < strlen(buffer); i++) {
			temp = buffer[i];
			if (temp == 0+'0'){
				buffer[i]=1+'0';
			}
			else {
				buffer[i]=0+'0';
			}
		}
		
		/* add "1"to the last bit*/
		add = 1;
		for (i = 0; i <= strlen(buffer); i++) {
			if (add == 1 && i < strlen(buffer)) {
				/*add 1 to most significant bit*/
				if ((buffer[strlen(buffer)-(i+1)]-'0') + 1 == 2) {
					buffer[strlen(buffer)-(i+1)] = 0+'0';
					add = 1;
				}
				else {
					buffer[strlen(buffer)-(i+1)] = 1+'0';
					add = 0;
				}
			}
		}
	}
		
	for(i=0; i<strlen(buffer); i++){
		if (buffer[i] == 1+'0'){
			count++;
		}
	}
	
	return count;
}

unsigned long Swapnumber(int num1, int num2){
    int k = 0;
    if(num1 > num2){
    	k = num1;
    	num1 = num2;
    	num2 = k;
    }				 

    unsigned long c = buffer & setbit[num1];
    unsigned long d = buffer & setbit[num2];
    c = c << (num2 - num1);
    d = d >> (num2 - num1);

    unsigned long n = ~(unsigned long)(1 << (num1-1));
    unsigned long m = ~(unsigned long)(1 << (num2-1));
	buffer = buffer & n;
    buffer = buffer & m;

    buffer = buffer | c;
    buffer = buffer | d;

    return buffer;
}


unsigned long swap_bytes(unsigned long n) {
    setbit[0] = 0;					
	setbit[1] = 1;
	unsigned long buff;
	for(int i = 2; i<=64; i++){		
		buff = 1;
		for(int j = 2; j<=i; j++){
			buff = buff << 1;
		}
		setbit[i] = buff;
	}

	buffer = n;

	int i, j;

	for (i = 1; i <= 8; i++) {
			Swapnumber(i, i+8);
		}

	for (i = 17; i <= 24; i++) {
			Swapnumber(i, i+8);
		}

	for (i = 33; i <= 40; i++) {
			Swapnumber(i, i+8);
		}

	for (i = 49; i <= 56; i++) {
			Swapnumber(i, i+8);
		}

	return buffer;
}


long a4_minus_b4(int a, int b) {
  	long m, n;

	m = a*a;
	m = m*m;
	n = b*b;
	n = b*b;

	return m - n;
}
