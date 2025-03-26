#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool isvowel(char c) // ������� �����, ��������� ������ ����������
{
	switch(tolower(c))
	{
		case 'a': 
		case 'e':
		case 'i': 
		case 'o': 
		case 'u':
		case 'y': return true;
	}
	return false;
}


int main(int argc, char **argv)
{	

	char filename[32];
    FILE *file;
    int ch;
    
	int lines, digits, syms, spaces, letters, lowletr, upletr, vowel, cons, total = 0; 
	// ������, �����, �������, �������, �����, ���.���., ����.���., �������, ���������, �����

	printf("Enter file name ");
	if (scanf("%32s", filename) != 1) {
        printf("Reading error\n");
        return 1;
    }
	
	file = fopen(filename, "r");
    if (file == NULL) {
        perror("File opening error");
        return 1;
    }
    
    printf("\n");
    while ((ch = fgetc(file)) != EOF) {
    	putchar(ch);
    	
    	if (ch == "\n") { // ���-�� ����� ����� [�� ��������]
    		lines++;
		}
    	
    	if (isdigit(ch)) { // ���-�� ����
    		digits++;
		}
		
		if (ispunct(ch)) { // ���-�� ��������
    		syms++;
		}
		
		if (isspace(ch)) { // ���-�� ��������
    		spaces++;
		}
		
		if (isalpha(ch)) { // ���-�� ����
    		letters++;
		}
		
		if (islower(ch)) { // ���-�� ���� ������� ��������
    		lowletr++;
		}
		
		if (isupper(ch)) { // ���-�� ���� �������� ��������
    		upletr++;
		}
    	
    	if (isvowel(ch)) { // ���-�� �������
    		vowel++;
		}
    }
    
    cons = letters - vowel; // ���-�� ���������
    
	printf("\n");
	printf("--------------------------------");
	
	printf("\nlines=%d digits=%d symbols=%d\n", lines, digits-1, syms); // digits-1 �.� � ����� �� ������ ������ �������
	printf("letters=%d, low letters=%d, up letters=%d\n", letters, lowletr, upletr);
	printf("spaces=%d, vowels=%d, consonants=%d\n", spaces, vowel, cons);
	
	total = digits + syms + spaces + letters + lowletr + upletr + vowel + cons;
	printf("total=%d",total);
	
	fclose(file);
 	return 0;
}

