//Copyright (C) 2014-2015  Corwin Hansen
#include <stdio.h>//input and output
#include <stdlib.h>//standard stuff
#include <string.h>//string handling
#include <time.h>//time related stuff



int main(int argc, char *argv[]){
	if (argc == 1){//no arguments given. show current time
		printf("Current time is:\n");
		time_t timec;//current time
		time_t timel;//last time
		time(&timec);
		time(&timel);
		char times[128];//time string
		strcpy(times, asctime(localtime(&timec)));//copy string
		times[strlen(times) - 1] = '\0';//set last character as nothing insted of newline
		printf("%s", times);//print current timr
		while (1){
			time(&timec);//update time
			if (timec != timel){//if 2 are not equal
				timel = timec;//update last time
				strcpy(times, asctime(localtime(&timec)));//copy string
				times[strlen(times) - 1] = '\0';//set last character as nothing insted of newline
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");//delete last time
				printf("%s", times);//print current timr
			}
		}
	}
	if (argc == 2 && strcmp(argv[1], "-t") == 0){//timer mode
		double timer;//end time for timer
		unsigned long int min;//minute and second 
		unsigned int sec;
		time_t start;//start time
		time_t current;//current time
		time_t last;//last time
		printf("Enter Minutes:");//ask to enter time
		scanf("%lu", &min);//get minutes
		printf("Enter Seconds to start:");//ask to enter time
		scanf("%u", &sec);//get seconds
		timer = (double)min * 60 + (double)sec;
		time(&start);//get start time
		time(&current);//set current time
		time(&last);//set last time
		printf("\n%u:%u", (unsigned int)timer / 60, (unsigned int)timer % 60);//print time
		while (1){
			time(&current);//update current time
			if (last != current){//if 2 are not equal
				last = current;//update last time
				unsigned int difference = (unsigned int)difftime(current, start);
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");//delete last time
				printf("%0u:%02u", ((unsigned int)timer - difference) / 60, ((unsigned int)timer - difference) % 60);//print time;
			}
			if (difftime(current, start) >= timer){//if at end
				printf("\a");//ring a bell
				while (1){//ring bell continuoucely
					time(&current);//update current time
					if (last != current){//if 2 are not equal
						last = current;//update last time
						printf("\a");//ring a bell
					}
				}
			}
		}
	}
	if (argc == 2 && strcmp(argv[1], "-s") == 0){//stopwatch mode
		char unused;//unused
		printf("Press ENTER to start:");//pronpt user to press enter
		scanf("%c", &unused);//wait for enter
		clock_t start = clock();//start stopwatch
		printf("Press ENTER to stop:");//pronpt user to press enter
		scanf("%c", &unused);//wait for enter
		clock_t diftime = clock() - start;//get time difference
		printf("%u:%02u.%02u\n", (unsigned int)(diftime/CLOCKS_PER_SEC/60), (unsigned int)((diftime/CLOCKS_PER_SEC)%60), (unsigned int)((diftime/(CLOCKS_PER_SEC/100)))%100);//display time
		exit(EXIT_SUCCESS);//end of program
	}
	printf("Simple command line timer. \n-t for timer, -s for stopwatch, and no argument gives current local time.\n");//print out usage of this program
	exit(EXIT_SUCCESS);//end of program
}
