/* Solution to comp10002 Assignment 1, 2018 semester 2.

   Authorship Declaration:

   I certify that the program contained in this submission is completely my
   own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been
   developed by another student, or by me in collaboration with other
   students, or by non-students as a result of request, solicitation, or
   payment, may not be submitted for assessment in this subject.  I further
   understand that submitting for assessment work developed by or in
   collaboration with other students or non-students constitutes Academic
   Misconduct, and may be penalized by mark deductions, or by other
   penalties determined via the University of Melbourne Academic Honesty
   Policy, as described at https://academicintegrity.unimelb.edu.au.

   I further certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor
   will I do so until after the marks are released. I understand that
   providing my work to other students, regardless of my intention or any
   undertakings made to me by that other student, is also Academic
   Misconduct.

   Signed by: Divyam Garg - 976443
   Dated: 16/09/2018

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*****************************************************************************/
/*Constants*/

#define MAX_STRFRAG_LEN 20
#define MAXNOSTR 1000
#define MAXSUPSTRLEN 20000
#define TRUE 1
#define FALSE 0
#define FIRST_LETTER 1
#define FIRST_ELEMENT 0
#define FIRST_OP 0
#define ERROR -1
#define LAST_OUTPUT_STRFRAG_INDEX -1

/*****************************************************************************/
/*DEBUG statements*/

#define DEBUG 0
#if DEBUG
#define DUMP_DBL(x) printf("line %d: %s = %.5f\n", __LINE__, #x, x)
#else
#define DUMP_DBL(x)
#endif

#if DEBUG
#define DUMP_INT(x) printf("line %d: %s = %.5d\n", __LINE__, #x, x)
#else
#define DUMP_INT(x)
#endif

#if DEBUG
#define DUMP_STR(x) printf("line %d: %s = %s\n", __LINE__, #x, x)
#else
#define DUMP_STR(x)
#endif

/*****************************************************************************/
/*Typedefs*/

typedef char strarr_t[MAXNOSTR][MAX_STRFRAG_LEN+1]; //+1 for null byte at end

/*****************************************************************************/
/* Function prototypes */

int mygetchar();
int read_input(strarr_t input);
int min(int num1, int num2);
int overlap(char* supstr, char* strfrag, int ol_chars);
int calc_tot_overlap(char* supstr, char* strfrag);
void stage1_supstr(char* supstr, strarr_t input,
												 int input_size);
char* mystrcasestr(char *txt, char *pat);
void print_firstnchar(char* str, int n);
void print_lastnchar(char* str, int n);
int mystrlen(char* str);
int processed(char* str);
void mark_processed(char* str);
void stage2_supstr(char* supstr, strarr_t input, int input_size);
void overlap_append(char* supstr, char*strfrag, int overlap);
int first_unprocessed(strarr_t input, int input_size);
void print_output(int no_ops, int strfrag_index, char* supstr);


/*****************************************************************************/

int
main(int argc, char *argv[]) {
	/* primary main function*/
	strarr_t input;
	int no_str_read;
	char supstr[MAXSUPSTRLEN];

	/* Stage 0 */
	no_str_read = read_input(input);

	/* Stage 1 */
	stage1_supstr(supstr, input, no_str_read);

	/* Stage 2 */
	stage2_supstr(supstr, input, no_str_read);

	return 0;
}

/* Solution for stage 0. Reads input into an array of strings with no more than
1000 strings each no more than 20 char long. Returns the number of string 
fragments read */
int
read_input(strarr_t input) {
	char ch;
	int no_str_read=0, no_char_read=0,tot_char_read=0;

	/* Read input char by char */
	while ((ch = mygetchar()) != EOF) {
		if (isalpha(ch)) {
			/* Ensure string length or the number of strings won't be exceeded
			   */
			if (no_char_read < MAX_STRFRAG_LEN && no_str_read < MAXNOSTR) {
				/* Add next char of string to the string */
				input[no_str_read][no_char_read] = ch;
				no_char_read += 1;
				tot_char_read += 1;
			}
		}
		else if (ch == '\n') {
			/* To complete the existing string append null byte at the end and 
		    increment no_str_read */
			input[no_str_read][no_char_read] = '\0';
			no_str_read += 1;
			no_char_read = 0;
		}
	}
	/* Format the output of the function as required by the specs */
	printf("\n");
	printf("Stage 0 Output\n--------------\n%d fragments read, ", no_str_read);
	printf("%d characters in total\n\n", tot_char_read);
	return no_str_read;
}

/* Solution for Stage 1 of assignment. Initializes supstr as the first str
   frag and then appends the non-overlapping portions of the following str 
   fragments onto the supstr */
void
stage1_supstr(char* supstr, strarr_t input, int input_size) {
	int no_ops=0, no_ol_char;
	char* tocap;

	/* Stage 1 output */
	printf("Stage 1 Output\n--------------\n");
	
	/* initialize the super string as the capitalized first letter in the first
	 fragment of the input */
	supstr[0] = toupper(input[0][0]);
	supstr[1] = '\0';

	/* Append the rest of the first fragment to the supstr */
	strncat(supstr, &input[0][1], MAX_STRFRAG_LEN-1);

	/* Stage 1 output */
	printf("%2d: frg=%2d, slen=%3d  %s\n", no_ops, no_ops, mystrlen(supstr),
																	 supstr);
	
	/* Iterate over input and append the required str fragments */
	for (no_ops=1; no_ops<input_size; no_ops++) {

		/* Ignore if the fragment is already wholly contained in supstr. 
		   Capitalize the letter where the str fragment starts in supstr */
		if ((tocap = mystrcasestr(supstr, input[no_ops]))) {
			*tocap = toupper(input[no_ops][0]);
		}
		else {
			overlap_append()
			}
		/* Stage 1 output */
		/* Passing the argument strfrag_index as no_ops as in this fundtion
		   no of operations and the index of the str fragment being appended
		   are equal */
		print_output(no_ops, no_ops, supstr);
	}
	printf("---\n");

	/* Stage 1 output */
	print_output(no_ops-1, LAST_OUTPUT_STRFRAG_INDEX, supstr);
	printf("\n");
	return ;
}


/* Solution for stage 2 of assignment */
void
stage2_supstr(char* supstr, strarr_t input, int input_size) {
	int i=0, j, no_frag_prssd=0, max_olap, max_olap_index, olap;
	char* to_cap;

	/* Mark the first str fragment in input as processed, which capitalizes 
	it's first letter. Then initialize supstr as the first str fragment */
	mark_processed(input[0]);
	no_frag_prssd += 1;
	strncpy(supstr, input[0], MAX_STRFRAG_LEN);

	/* Stage 2 output */
	printf("Stage 2 Output\n--------------\n");
	printf("%2d: frg=%2d, slen=%3d  %s\n", no_frag_prssd-1, FIRST_ELEMENT, 
													mystrlen(supstr), supstr);

	for (i=0; i<input_size && no_frag_prssd < input_size; i++) {

		/* Check every unprocessed fragment, if it appears anywhere within
	       supstr, mark it as processed */
		for (j=0; j<input_size && no_frag_prssd < input_size; j++) {
			if (!processed(input[j])) {
				if ((to_cap = mystrcasestr(supstr, input[j]))) {

				   /* Capitalize the first letter of the portion of supstr
				    which contains the str fragment */ 
					*to_cap = toupper(*to_cap);
					mark_processed(input[j]);
					no_frag_prssd += 1;

					/* Stage 2 output */
					/* The argument no_ops being passed as no_frag_prssd-1 as
						 no_ops is counted from 0 but no_frag_prssd from 1 */
					print_output(no_frag_prssd-1, j, supstr);
				}
			}
		}
	
		/* Initialize max_olap_index to the index of the first unprocessed str
		   fragment in input and max_olap to its overlap with supstr. Make sure
		   there is at least 1 unprocessed fragment */
		if ((max_olap_index = first_unprocessed(input, input_size)) >= 0) {
			max_olap = calc_tot_overlap(supstr, input[max_olap_index]);
		
			/* calculate overlap with supstr for unprocessed fragments and pick
			   the str fragment with max overlap */
			for (j=max_olap_index+1; j<input_size; j++) {
				if (!processed(input[j])) {
					if ((olap = calc_tot_overlap(supstr, input[j])) > 
																	max_olap) {
						max_olap = olap;
						max_olap_index = j;
					}
				}
			}

			/* Append the str fragment with the max overlap with supstr. In 
			   case two fragments have the same max overlap, the one with the 
			   smaller index gets appended */
    		overlap_append(supstr, input[max_olap_index], max_olap);

    		/* Mark the appended str frag as processed */
    		mark_processed(input[max_olap_index]);
    		no_frag_prssd += 1;

    		/* Stage 2 output */
    		/* The argumernt no_ops being passed as no_frag_prssd-1 as no_ops
    		 is counted from 0 but no_frag_prssd from 1 */
    		print_output(no_frag_prssd-1, max_olap_index, supstr);
    	}
	}

	/* Stage 2 output */
	printf("---\n");
	/* The argumernt no_ops being passed as no_frag_prssd-1 as no_ops is 
	counted from 0 but no_frag_prssd from 1 */
	print_output(no_frag_prssd-1, LAST_OUTPUT_STRFRAG_INDEX, supstr);
	printf("\n");
}


/* Alistairs version of getchar. Code copied from FAQ page for assignment1 */
int
mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
	}
	return c;
}

/* this function isn't universally available, here is a local version,
   returns pointer in txt to first place where pat occurs, and returns
   NULL if pat does not occur in txt, doing case-insensitive tests.
   Alistair Moffat's version of strcasestr. Code sourced from FAQ page for
   assignment1 */

char *
mystrcasestr(char *txt, char *pat) {
	int tl=strlen(txt);
	int pl=strlen(pat);
	int i;
	for (i=0; i<=tl-pl; i++) {
	    if (strncasecmp(txt+i, pat, pl)==0) {
			return txt+i;
	    }
	}
	return NULL;
}

/*Returns the smaller of (num1, num2). Returns num1 if both are equal */
int 
min(int num1, int num2) {
	if (num2 < num1) {
		return num2;
	}
	return num1;
}


/* Returns TRUE if last ol_chars of supstr are the same as first ol_chars of 
   strfrag, FALSE otherwise. Also returns FALSE if ol_chars is 0 or is greater
    than length of any of supstr or strfrag */
int
overlap(char* supstr, char* strfrag, int ol_chars) {
	int len_supstr, len_strfrag, minlen, olap=TRUE, i;

	len_supstr = strlen(supstr);
	len_strfrag = strlen(strfrag);
	minlen = min(len_supstr, len_strfrag);

	/* olap is false if number of chars to inspect for overlap(ol_chars) is
	   greater than length of supstr or strfrag */ 
	if ((ol_chars > minlen) || (!ol_chars)) {
		olap=FALSE;
	}

	/* Loop only if overlap has been found in previous chars and number of char
	   being inspected is less than the length of the smaller of supstr and
	   strfrag */
	for (i=0; olap && i<ol_chars; i++) {

		/* if some char doesnt match, conclude overlap is false */
		if (tolower(supstr[len_supstr-ol_chars+i]) != strfrag[i]) {
			olap = FALSE;
		}
	}
	return olap;
}


/* Returns the number of characters that overlap at the tail of supstr and
head of strfrag */
int
calc_tot_overlap(char* supstr, char* strfrag) {
	int len_supstr, len_strfrag, minlen,olap=FALSE, no_olap_char;

	len_supstr = strlen(supstr);
	len_strfrag = strlen(strfrag);
	minlen = min(len_supstr, len_strfrag);

	/* Check if 1 char overlap, if yes increment no_olap_char and check if 2
	   overlap... and so on until some char doesnt overlap */

	for (no_olap_char=minlen; no_olap_char>=0 && !olap; no_olap_char--) {
		olap = overlap(supstr, strfrag, no_olap_char);
	}
	return no_olap_char+1; 
}


/* Prints the first n characters of str. Prints all of str if n > length of 
str */
void
print_firstnchar(char* str, int n) {
	int len_str=strlen(str), i;

	/* Go over the first n characters and print them one by one */
	for(i=0; i<n && i<len_str; i++) {
		printf("%c", (str)[i]);
	}
}


/* Prints the last n characters of str. Prints all of str if n > length of
   str */
void
print_lastnchar(char* str, int n) {
	int len_str=strlen(str), i;

	/* Go over the first n characters and print them one by one */
	for(i=min(n, len_str); i>=1; i--) {
		printf("%c", (str+len_str)[-i]);
	}
}


/* Returns TRUE if str is processed, i.e the first letter of str is capitalized
   */
int
processed(char* str) {
	if (isupper(str[0])) {
		return TRUE;
	}
	return FALSE;
}


/* Capitalizes the first letter in str so later it can be identified if the
string has been processed or not */
void
mark_processed(char* str) {
	str[0] = toupper(str[0]);
}


/* Returns index of the first unprocessed string in input. Returns -1
 otherwise. */
int
first_unprocessed(strarr_t input, int input_size) {
	int i;

	/* Go over each str fragment in input, return the index of the first one
	   not processed */
	for (i=0; i<input_size; i++) {
		if (!processed(input[i])) {
			return i;
		}
	}
	/* Return ERROR(-1) if no str frag in input is unprocessed */
	return ERROR;
}


/* Appends strfrag to supstr where the amount of overlap between the two is 
   overlap. Assumes given overlap is accurate and is non zero. */
void
overlap_append(char* supstr, char*strfrag, int overlap) {
	char to_cap;

	/* Append the non-overlapping portion of strfrag to supstr */
	strncat(supstr, (strfrag+overlap), MAX_STRFRAG_LEN);

	/* Capitalize the letter in supstr where appended str fragment starts */ 
	to_cap = supstr[strlen(supstr)-strlen(strfrag)];
	supstr[strlen(supstr)-strlen(strfrag)] = toupper(to_cap);
}


/* Returns the length of str excluding the null byte. Written because strlen
   from string.h returns type size_t which presented problems compiling on the
   server */
int mystrlen(char* str) {
	int i, len=0;

	for (i=0; str[i]; i++) {
		len += 1;
	}
	return len;
}


/* Prints out the results of stages 1-3 in the required format */ 
void
print_output(int no_ops, int strfrag_index, char* supstr) {

	/* Print only the first 10 operations and then every 5th operation.
	   Also print the last line of a stage's output, which will have the value 
	   of strfrag_index as -1 */
	if (no_ops < 10 || !(no_ops%5) || (strfrag_index == -1)) {

		/* Print whole of supstr if its not longer than 54 characters */
		if (mystrlen(supstr)<=54) {
			printf("%2d: frg=%2d, slen=%3d  %s\n", no_ops, strfrag_index,
													 mystrlen(supstr), supstr);
		}

		/* Print only the first and last 25 characters of supstr if its 
		   longer than 54 characters */
		else {
			printf("%2d: frg=%2d, slen=%3d  ", no_ops, strfrag_index,
															 mystrlen(supstr));
			print_firstnchar(supstr, 25);
			printf(" .. ");
			print_lastnchar(supstr, 25);
			printf("\n");
		}
    }
}

/*algorithms are fun*/

