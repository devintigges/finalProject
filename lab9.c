// Lab 09 DS4Talker Skeleton Code       

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>
#define WORDLENGTH 11
#define MAXWORDS 100
#include <string.h>
#define DEBUGM 1   // Set this to 0 to disable debug output

// Reads words from the file into WL and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int read_words(char* WL[MAXWORDS], char* file_name);

// modifies str to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* str);


void draw_character(int x, int y, char use);


int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS];
	int wordcount;
	int i;
	int col = 0;
	int playing = 0;
	int word= 0;
	int joyX, joyY, joyLeft, joyRight;
	int t,b1,b2,b3,b4,b5,b6,b7,b8;
	int x = 16;
	int y = 0;
	int currentWord = 0;
	char sentence[200];
	int last;
	int lasts[100];
	int numWords = 0;
	
	
	wordcount = read_words(wordlist, argv[1]);

	if (DEBUGM) {
		printf("Read %d words from %s \n", wordcount, argv[1]);
		for (i = 0; i < wordcount; i++) {
			printf("%s,", wordlist[i]);

		}
		printf("\n");
	}
	

	// most of your code goes here. Do not forget to include the ncurses library 
	
	initscr();
	
	for(int i = 0; i < 15; i++){
		for(int j = 0; j < 5; j++){
			mvprintw(i, col * 15,"%15s",wordlist[word]);
			col++;
			word++;
		}			
		col = 0;
	}
	mvprintw(15,0,"%15s", wordlist[word]);
	refresh();
	while(playing == 0){
		scanf("%d,%d,%d,%d,%d,%d, %d, %d, %d,%d, %d, %d, %d", &t, &b1,&b2,&b3,&b4,&b5,&b6,&b7,&b8,&joyX, &joyY, &joyLeft, &joyRight);
		
		refresh();
		if(t%100 == 0 || t%100 == 1 || t%100 == 2 || t%100 == 3){
			if(joyY > 50 &&  x < 74){
				draw_character(x,y,' ');
				x += 15;
				currentWord++;
				draw_character(x,y,'*');
			}
			if(joyY < -50 && x > 17){
				draw_character(x,y,' ');
				x -= 15;
				currentWord--;
				draw_character(x,y,'*');
			}
			if(joyLeft < -50 && y > 0){
				draw_character(x,y,' ');
				y--;
				currentWord -= 5;
				draw_character(x,y,'*');
			}
			if(joyLeft > 50 && y < 15 ){
				draw_character(x,y,' ');
				y++;
				currentWord += 5;
				draw_character(x,y,'*');
			}
		if(b1 == 1){
			strcat(sentence, " ");
			strcat(sentence, wordlist[currentWord]);
			last = currentWord;
			lasts[numWords] = currentWord;
			numWords++;
		}
		if(b2 == 1){
			strcat(sentence, wordlist[currentWord]);
			last = currentWord;
			lasts[numWords] = currentWord;
			numWords++;
		}
		if(b3 == 1){
			int length;
			int senLength;
			length = strlen(wordlist[lasts[numWords -1]]);
			senLength = strlen(sentence);
			if(sentence[(senLength - 1) - length] == ' '){
				for(int i = 0; i <= length; i++){
				sentence[(senLength - 1) - i] = '\0';
				}
			}
			else
			{
				for(int i = 0; i < length; i++){
				sentence[(senLength - 1) - i] = '\0';
				}
			}
			mvprintw(25,1,"%s",sentence);
			mvprintw(25,strlen(sentence) + 1,"%s","                                                    			");
			
			numWords--;
		}
		mvprintw(25,1,"%s",sentence);
		}
		
		
	}
	
	return 0;
}

// DO NOT MODIFY THIS FUNCTION!
void trimws(char* str) {
	int length = strlen(str);
	int x;
	if (length == 0) return;
	x = length - 1;
	while (isspace(str[x]) && (x >= 0)) {
		str[x] = '\0';
		x -= 1;
	}
}


// DO NOT MODIFY THIS FUNCTION!
int read_words(char* WL[MAXWORDS], char* file_name)
{
	int numread = 0;
	char line[WORDLENGTH];
	char *p;
	FILE* fp = fopen(file_name, "r");
	while (!feof(fp)) {
		p = fgets(line, WORDLENGTH, fp);
		if (p != NULL) 
		{
			trimws(line);
			WL[numread] = (char *)malloc(strlen(line) + 1);
			strcpy(WL[numread], line);
			numread++;
		}
	}
	fclose(fp);
	return numread;
}

void draw_character(int x, int y, char use)
{
    mvaddch(y,x,use);
    refresh();
}