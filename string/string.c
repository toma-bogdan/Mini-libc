// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	size_t len = strlen(source);
	for (size_t i = 0; i < len; i++) {
		*(destination + i) = *(source + i);
	}
	*(destination + len) = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	for (size_t i = 0; i < len; i++) {
		*(destination + i) = *(source + i);
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	size_t len = strlen(destination);
	size_t len_source = strlen(source);

	 // Start inserting all characters from source at the end of destination
	for (size_t i = len; i < len + len_source; i++) {
		*(destination + i) = *(source + i - len);
	}
	*(destination + len + len_source) = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	// Start inserting LEN characters from source at the end of destination
	size_t len_dest = strlen(destination);
	for (size_t i = len_dest; i < len_dest + len; i++) {
		*(destination + i) = *(source + i - len_dest);
	}
	*(destination + len + len_dest) = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	while (*str1 != '\0' && *str2 != '\0') { // compare characters until end of either string
        if (*str1 != *str2) {  // if 2 characters are different, returns the difference in ascii between them
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
	// If a string is shorter returns the difference between '\0' and last char
    return *str1 - *str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	for (size_t i = 0; i < len && str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) { // if 2 characters are different, returns the difference in ascii between them
            return (int)(unsigned char)str1[i] - (int)(unsigned char)str2[i];
        }
    }
	// If a string is shorter or LEN chars have been compares
    if (len > 0 && str1[len - 1] != '\0' && str2[len - 1] != '\0') {
        return (int)(unsigned char)str1[len - 1] - (int)(unsigned char)str2[len - 1];
    }
	// The strings are equal
    return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	// Itterate through str and verify if the current char is equal to c
	// then return the rest of the string
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++) {
		if (*(str + i) == c) {
			return (char*)(str + i);
		}
	}
	if (*(str + len) == c) {
		return (char*) (str + len);
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	// Itterate through str and verify if the current char is equal to c
	// if so, store the remaining string in "last", and continue with the itteration 
	const char* last = NULL;
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++) {
		if (*(str + i) == c) {
			last = (str + i);
		}
	}

    if (*str == c) {
        last = str + len;
    }
    return (char*)last;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	if (*needle == '\0') {
        return (char*)haystack;
    }
	size_t len_h = strlen(haystack);
	size_t len_n = strlen(needle);
	int ok = 1; // flag that checks if the needle has been found
	for (size_t i = 0; i < len_h; i++) {
		ok = 1;
		// Checks the needle
		for (size_t j = 0; j < len_n; j++) {
			if (*(haystack + i + j) != *(needle + j)){
				ok = 0;
				break;
			}
		}
		if (ok == 1) {
			return (char*)(haystack + i);
		}
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	if (*needle == '\0') {
        return (char*)haystack;
    }
	const char* last = NULL;
	size_t len_h = strlen(haystack);
	size_t len_n = strlen(needle);
	int ok = 1; // flag that checks if the needle has been found
	for (size_t i = 0; i < len_h; i++) {
		ok = 1;
		// Checks the needle
		for (size_t j = 0; j < len_n; j++) {
			if (*(haystack + i + j) != *(needle + j)){
				ok = 0;
				break;
			}
		}
		if (ok == 1) {
			last = (char*)(haystack + i);
		}
	}
	return (char*)last;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	char* aux_dest = destination;
    const char* aux_source = source;
	for (size_t i = 0; i < num; i++) {
		*(aux_dest + i) = *(aux_source + i);
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	char buffer[num];   // temporary buffer
    char* dest_ptr = (char*)destination;
    const char* src_ptr = (const char*)source;
    
	memcpy(buffer, src_ptr, num);
	for (size_t i = 0; i < num; i++) {
		dest_ptr[i] = buffer[i];
	}
    
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	unsigned char* p1 = (unsigned char*)ptr1;
    unsigned char* p2 = (unsigned char*)ptr2;
    for (size_t i = 0; i < num; i++) {
        if (p1[i] < p2[i]) {
            return -1;
        } else if (p1[i] > p2[i]) {
            return 1;
        }
    }
    return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	unsigned char* p = (unsigned char*)source;
    unsigned char v = (unsigned char)value;
    for (size_t i = 0; i < num; i++) {
        p[i] = v;
    }
	return source;
}
