/* David Jara 2024
 * This is a tool for implementing ABC analysis
 * Tasks are serialized (stored in binary format) so as to permit commas in their description field.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

struct simple_date {
	unsigned short year;
	unsigned char month;
	unsigned char day; 
};

struct task {
	// Stuff that is used for determining priority
	unsigned char priority;   // (1) presuming you won't need more than 255 active tasks. Default value 0 (unknown)
	unsigned char difficulty; // (2) Used to break ties in dues dates (two assignments at the
	                          //     same time, but one is significantly more difficult than the other).
	struct simple_date creation_date; 
	struct simple_date due_date;

	char title[32];  // it is safe to assume that this should not be too long --- please be concise.

	unsigned short description_length;    // There is no way to determine an appropriate length by using a fixed buffer. Theoretically,
                                              // some space may be saved using dynamic allocation. If only 60 characters are used for a 
	char *description;                    // description, then 64 bytes of memory are used, versus fixed 256 bytes with a static array.	
};

struct task* task_create(char title[], char *description, struct tm creation_time
{
	struct task *new_task = malloc(sizeof(struct task));
	if(new_task == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for task \"%s\".\n", title);
		return NULL;
	}

	// COPY OVER THE TITLE
	unsigned char title_length = strlen(title);
	if(title_length < 32)                          // IF the parameter is appropriate length, just copy
		strcpy(new_task->title, title);        // using strcpy function
	else                                           // ELSE copy character by character up to the 32nd character 
	{                                              // and insert a null terminator at the end
		for(int i = 0; i < 31; i++)
			new_task->title[i] = title[i];

		new_task->title[31] = '\0';
	}

	// COPY OVER THE DESCRIPTION	
	new_task->description_length = strlen(description);
	strcpy(new_task->description, description);
	
	// SET PRIORITY 
	new_task->priority = 0;

	// SET DATE TIME INFORMATION
	time_t t = time(NULL);
	struct tm current_time = *localtime(&t);
	new_task->creation_date = current_time;
}

bool write_tasks(char *file_name, struct task **tasks, unsigned short tasks_length, unsigned short tasks_capacity)
{
	FILE *fh = fopen(file_name, "w");
	for(int tasks_index = 0; tasks_index < tasks_length)
	{
		fwrite(
	}

	return true;
}



int main(void)
{
	return 0;
}
