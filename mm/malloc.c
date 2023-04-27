// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	// if (mem_list_head.next == NULL){
	// 	mem_list_init();
	// }
	void *p = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (p != MAP_FAILED) {
		mem_list_add(p,size);
		return p;
	}
	return NULL;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
	if (mem_list_head.next == NULL){
		mem_list_init();
	}
	void *p, *first;
	for (size_t i = 0; i < nmemb; i++) {
		p = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (p == MAP_FAILED){
			return NULL;
		}
		mem_list_add(p,size);
		if (i == 0)
			first = p;
	}
	return first;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	struct mem_list *aux = mem_list_find(ptr);
	if (aux == NULL) {
		return;
	}
	munmap(ptr,aux->len);
	mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	if (ptr == NULL) {
		return malloc(size);
	}
	if (size == 0) {
		free(ptr);
		return NULL;
	}
	struct mem_list *aux = mem_list_find(ptr);
	size_t old_size = aux->len;
	size_t copy_size;

	if (old_size < size){
		copy_size = old_size;
	} else {
		copy_size = size;
	}

	void *new_ptr = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	memcpy(new_ptr,ptr,copy_size);

	free(ptr);

	mem_list_add(new_ptr,size);

	return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
	if (nmemb == 0 || size == 0) {
        if (ptr != NULL) {
            free(ptr);
        }
        return NULL;
    }


    void *new_ptr = mmap(NULL,size,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_ptr == NULL) {
        return NULL;
    }

    if (ptr != NULL) {
        struct mem_list *item = mem_list_find(ptr);
        if (item == NULL) {
            free(new_ptr);
            return NULL;
        }

        size_t copy_size = item->len < size ? item->len : size;
        memcpy(new_ptr, ptr, copy_size);

        mem_list_del(ptr);
        free(ptr);
    }

    if (mem_list_add(new_ptr, size) != 0) {
        free(new_ptr);
        return NULL;
    }

    return new_ptr;
}
