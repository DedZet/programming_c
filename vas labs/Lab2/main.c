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

char *getword(FILE *F)
	{
	char *s; int c;
 	// ñ÷èòûâàåì îäíî ñëîâî èç ôàéëà F
 	// return NULL åñëè ôàéë çàêîí÷èëñÿ
 	return s;
	}

int main(int ac, char *av[])
	{
		
  	FILE *OUT1, *OUT2, *IN;
  	char *pword;
  	// çäåñü îòêðûòü ôàéëû äëÿ âûâîäà,
  	// ïðîâåðêà íà óñïåõ,  èíèöèàëèçàöèÿ ïåðåìåííûõ è ò.ä.
  	
  	char dirname[128];
  	printf("Enter dir name ");
  	scanf("%s", &dirname);
  	IN = fopen(dirname, "r");
  	
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
