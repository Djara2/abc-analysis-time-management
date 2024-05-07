/* David Jara 2024
 * This is a tool for implementing ABC analysis
 * Tasks are serialized (stored in binary format) so as to permit commas in their description field.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define TITLE_SIZE 32

struct simple_date {
	unsigned char month;
	unsigned char day; 
	unsigned short year;
};

struct task {
	// Stuff that is used for determining priority
	unsigned char priority;   // (1) presuming you won't need more than 255 active tasks. Default value 0 (unknown)
	unsigned char difficulty; // (2) Used to break ties in dues dates (two assignments at the
	                          //     same time, but one is significantly more difficult than the other).
	struct simple_date creation_date; 
	struct simple_date due_date;

	char title[TITLE_SIZE];  // it is safe to assume that this should not be too long --- please be concise.

	unsigned short description_length;    // There is no way to determine an appropriate length by using a fixed buffer. Theoretically,
                                              // some space may be saved using dynamic allocation. If only 60 characters are used for a 
	char *description;                    // description, then 64 bytes of memory are used, versus fixed 256 bytes with a static array.	
};

struct task* task_create(char title[], char *description, struct simple_date due_date, unsigned char difficulty)
{
	struct task *new_task = malloc(sizeof(struct task));
	if(new_task == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for task \"%s\".\n", title);
		return NULL;
	}

	// COPY OVER THE TITLE
	unsigned char title_length = (unsigned char) strlen(title);
	if(title_length < TITLE_SIZE)                  // IF the parameter is appropriate length, just copy
		strcpy(new_task->title, title);        // using strcpy function
	else                                           // ELSE copy character by character up to the 32nd character 
	{                                              // and insert a null terminator at the end
		for(int i = 0; i < TITLE_SIZE - 1; i++)
			new_task->title[i] = title[i];

		new_task->title[TITLE_SIZE - 1] = '\0';
	}
	
	// COPY OVER THE DESCRIPTION	
	new_task->description_length = (unsigned short) strlen(description);
	new_task->description = malloc(sizeof(char) * new_task->description_length);
	strcpy(new_task->description, description);
	
	// SET PRIORITY 
	new_task->priority = 0;

	// SET DATE TIME INFORMATION
	time_t t = time(NULL);
	struct tm current_time = *localtime(&t);
	new_task->creation_date.month = current_time.tm_mon;
	new_task->creation_date.day = current_time.tm_mday;
	new_task->creation_date.year = current_time.tm_year + 1900;
	
	new_task->due_date.month = due_date.month;
	new_task->due_date.day = due_date.day;
	new_task->due_date.year = due_date.year;

	// SET DIFFICULTY
	new_task->difficulty = difficulty;

	return new_task;
}

bool write_tasks(char *file_name, struct task **tasks, unsigned short tasks_length, unsigned short tasks_capacity)
{
	// ATTEMPT TO OPEN FILE FOR WRITING IN BINARY MODE
	FILE *fh = fopen(file_name, "wb");
	if(fh == NULL)
	{
		fprintf(stderr, "Failed to open file \"%s\" for reading.\n", file_name);
		return false;
	}

	// WRITE EACH INDIVIDUAL TASK
	for(int tasks_index = 0; tasks_index < tasks_length; tasks_index++)
	{
		struct task *current = tasks[tasks_index];

		fwrite(&current->priority, 1, 1, fh);
		fwrite(&current->difficulty, 1, 1, fh);

		fwrite(&current->creation_date, sizeof(struct simple_date), 1, fh);
		fwrite(&current->due_date,      sizeof(struct simple_date), 1, fh);

		fwrite(&current->title, TITLE_SIZE, 1, fh);

		fwrite(&current->description_length, sizeof(unsigned short), 1, fh);
		fwrite(current->description, 1, current->description_length, fh);
	}

	fclose(fh);

	return true;
}



int main(void)
{
	// test code
	//
	struct task **tasks = malloc(sizeof(struct task*) * 10);
	char titles[4][32] = {"Work on code", "Make tofu", "Work on ENGR589A", "Work on ENGR510"};
	char descriptions[4][50] = {"ABC analysis tool", "with beyond beef", "presentation of time management method", "read materials"};
	struct simple_date due_dates[4] = { {5, 6, 2024}, {5, 6, 2024}, {5, 8, 2024}, {5, 12, 2024} };
	unsigned char difficulties[4] = {3, 1, 2, 2};

	for(int i = 0; i < 4; i++)
	{
		tasks[i] = malloc(sizeof(struct task));
		tasks[i] = task_create(titles[i], descriptions[i], due_dates[i], difficulties[i]);
	}
	
	write_tasks("tasks.bin", tasks, 4, 10);
	return 0;
}
