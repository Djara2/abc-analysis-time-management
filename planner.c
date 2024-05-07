/* David Jara 2024
 * This is a tool for implementing ABC analysis
 * Tasks are serialized (stored in binary format) so as to permit commas in their description field.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct task {
	// Stuff that is used for determining priority
	unsigned char priority;   // (1) presuming you won't need more than 255 active tasks
	unsigned char difficulty; // (2) Used to break ties in dues dates (two assignments at the
	                          //     same time, but one is significantly more difficult than the other).
	struct tm creation_date; 
	struct tm due_date;

	char title[32];  // it is safe to assume that this should not be too long --- please be concise.

	unsigned short description_length;    // There is no way to determine an appropriate length by using a fixed buffer. Theoretically,
	unsigned short description_capacity;  // some space may be saved using dynamic allocation. If only 60 characters are used for a 
	char *description;                    // description, then 64 bytes of memory are used, versus fixed 256 bytes with a static array.	
};

int main(void)
{
	return 0;
}
