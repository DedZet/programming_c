#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/time.h>

typedef struct word {
	int count;
  	char *Word;
	} WORD;

int cmpword_alpha(WORD *, WORD *);
int cmpword_quant(WORD *, WORD *);

WORD words[100000];

int totalw=0; // word count

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

char *getword(FILE *F) {
		
	int c, index;
	char *word = (char *)malloc(32 * sizeof(char));
 	
 	while ((c == fgetc(F)) != EOF && !isalpha(c)) {
        word[index++] = tolower(c);
    }
    
    word[index] = '\0';
 	
 	if (c == EOF) {
 		free(word);
        return NULL;
    }
 	
 	return word;
	}
	
void add_word(const char *token) {
	
    // Ïðèâîäèì ñëîâî ê íèæíåìó ðåãèñòðó
//    char *lower_token = strdup(token);
//    int i;
//    for (i = 0; lower_token[i]; i++) {
//        lower_token[i] = tolower(lower_token[i]);
//    }
//    
//    // Ïðîâåðÿåì, åñòü ëè ñëîâî óæå â ñëîâàðå
//    int i;
//    for (i = 0; i < word_count; i++) {
//        if (strcmp(words[i]->w, lower_token) == 0) {
//            words[i]->count++;
//            free(lower_token);
//            return;
//        }
//    }
    
//    if (word_count < MAX_WORDS) {
//        WORD *new_word = (WORD *)malloc(sizeof(WORD));
//        new_word->w = lower_token;
//        new_word->count = 1;
//        words[word_count++] = new_word;
//    } else {
//        free(lower_token);
//        fprintf(stderr, "Error max word limit\n");
    
}

int main(int ac, char *av[])
	{
		
  	FILE *OUT1, *OUT2, *IN;
  	char *pword;
  	
    int ch;
	char filename[] = "text.txt";

	IN = fopen(filename, "r");
	
	if (IN == NULL) {
        perror("File opening error");
        return 1;
    }
	  
	while (getword(IN) != EOF) {
		printf("%s",getword(IN));
	}
  	
  	if (ac<2)
  		{
  			
    	printf("You forgot to specify the file list!\n");
		exit (0);
    	
  		}
  		
  	while (--ac) // èäåì ïî ñïèñêó ôàéëîâ
  		{
  			
   		IN=fopen(av[ac],"r");
   		printf("Processing files %s\n",av[ac]);
   		// îòêðûâàåì î÷åðåäíîé ôàéë
   		
   		while ((pword=getword(IN))!=NULL)
    		{ 	
      			// ðàáîòàåì ñ ïðî÷èòàííûì ñëîâîì
      			// äîáàâëÿåì â ìàññèâ ñ óâåëè÷åíèåì totalw
      			// èëè óâåëè÷èâàåì ñ÷åò÷èê óæå
      			// çàíåñåííîãî â ñëîâàðü ñëîâà
      			// òîëüêî äëÿ ïðîâåðêè

      			break;  
    		}
	fclose(IN);
  		}
  		
 	qsort(words,totalw,sizeof(WORD *),
    (int (*)(const void *, const void *))cmpword_alpha ); // çäåñü âûâîä ìàññèâà
 	
 	qsort(words,totalw,sizeof(WORD *),
    (int (*)(const void *, const void *))cmpword_quant ); // çäåñü âûâîä ìàññèâà
 	
	return 0; 
	}
	
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
	
int cmpword_alpha(WORD *w1,  WORD *w2) // Ôóíêöèÿ ñðàâíåíèÿ ñëîâ äëÿ ñîðòèðîâêè ïî àëôàâèòó
	{
	const WORD *word1 = *(const WORD **) w1;
    const WORD *word2 = *(const WORD **) w2;
    
    return strcmp(word1->Word, word2->Word);
    
	printf("test_alpha");
	}
	
int cmpword_quant(WORD *w1,  WORD *w2) // Ôóíêöèÿ ñðàâíåíèÿ ÷àñòîò äëÿ ñîðòèðîâêè ïî ÷àñòîòå ïîÿâëåíèé
	{
	const WORD *word1 = *(const WORD **) w1;	
    const WORD *word2 = *(const WORD **) w2;
    
    if (word1->count > word2->count) return -1;
    if (word1->count < word2->count) return 1;
    
    return strcmp(word1->Word, word2->Word);
    
	printf("test_quant");
	}
