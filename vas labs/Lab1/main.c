#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool isvowel(char c)
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
    
	int lines, digits, punct, spaces, letters, lowletr, upletr, vowel, cons, total = 0; 
	// Строки, Цифры, Символы, Пробелы, Буквы, Ниж.рег, Верх.рег, Гласные, Согласные, Итого

	printf("Enter file name ");
	if (scanf("%31s", filename) != 1) {
        printf("Reading error\n");
        return 1;
    }
	
	file = fopen(filename, "r");
    if (file == NULL) {
        perror("File opening error");
        return 1;
    }
    
    printf("\n");
    // Вывод содержимого
    while ((ch = fgetc(file)) != EOF) {
    	putchar(ch);
		}
		
	fclose(file);
	file = fopen(filename, "r");
	
	// Подсчёт данных
	while ((ch = fgetc(file)) != EOF) {
    	total++;
    	if (ch == '\n') lines++;
        if (isdigit(ch)) digits++;
        if (ispunct(ch)) punct++;
        if (isspace(ch)) spaces++;
        if (isalpha(ch)) {
            letters++;
            if (islower(ch)) lowletr++;
            if (isupper(ch)) upletr++;
   		}
        if (isvowel(ch)) {
            vowel++;
        } else { 
		cons++; 
		}
	}
    fclose(file);
    
	printf("\n");
	printf("--------------------------------");
	
	printf("\nlines = %d digits = %d puncts = %d\n", lines, digits-1, punct); // (digits-1) т.к последний байт выделяется для обозначения конца строки
	printf("letters = %d, low letters = %d, up letters = %d\n", letters, lowletr, upletr);
	printf("spaces = %d, vowels = %d, consonants = %d\n", spaces, vowel, cons);
	
	total = digits + punct + spaces + letters + lowletr + upletr + vowel + cons;
	printf("total=%d",total);

 	return 0;
}
