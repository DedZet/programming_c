#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool isvowel(char c) // Гласные звуки, Согласный искать отрицанием
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
	// Строки, Цифры, Символы, Пробелы, Буквы, Ниж.рег., Верх.рег., гласные, согласные, итого

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
    	
    	if (ch == "\n") { // Кол-во новых строк [НЕ РАБОТАЕТ]
    		lines++;
		}
    	
    	if (isdigit(ch)) { // Кол-во цифр
    		digits++;
		}
		
		if (ispunct(ch)) { // Кол-во символов
    		syms++;
		}
		
		if (isspace(ch)) { // Кол-во пробелов
    		spaces++;
		}
		
		if (isalpha(ch)) { // Кол-во букв
    		letters++;
		}
		
		if (islower(ch)) { // Кол-во букв нижнего регистра
    		lowletr++;
		}
		
		if (isupper(ch)) { // Кол-во букв верхнего регистра
    		upletr++;
		}
    	
    	if (isvowel(ch)) { // Кол-во гласных
    		vowel++;
		}
    }
    
    cons = letters - vowel; // Кол-во согласных
    
	printf("\n");
	printf("--------------------------------");
	
	printf("\nlines=%d digits=%d symbols=%d\n", lines, digits-1, syms); // digits-1 т.к в конце он всегда ставит единицу
	printf("letters=%d, low letters=%d, up letters=%d\n", letters, lowletr, upletr);
	printf("spaces=%d, vowels=%d, consonants=%d\n", spaces, vowel, cons);
	
	total = digits + syms + spaces + letters + lowletr + upletr + vowel + cons;
	printf("total=%d",total);
	
	fclose(file);
 	return 0;
}

