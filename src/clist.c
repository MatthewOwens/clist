#include "clist.h"
#include <stdlib.h>

struct clist *clist_new(void *data)
{
	struct clist *head = malloc(sizeof(struct clist));
	head->next = NULL;
	head->prev = NULL;
	head->data = data;

	return head;
}

struct clist *clist_tail(struct clist *node)
{
	if(node == NULL) { return NULL; }

	return (node->next == NULL) ? node : clist_tail(node->next);
}

struct clist *clist_head(struct clist *node)
{
	if(node == NULL) { return NULL; }

	return (node->prev == NULL) ? node : clist_head(node->prev);
}

struct clist *clist_append(struct clist *node, void *data)
{
	if(node == NULL) { return NULL; }

	struct clist *tail = clist_tail(node);
	tail->next = malloc(sizeof(struct clist));
	tail->next->prev = tail;
	tail->next->next = NULL;
	tail->next->data = data;
	return tail->next;
}

struct clist *clist_prepend(struct clist *node, void *data)
{
	if(node == NULL) { return NULL; }

	struct clist *head = clist_head(node);
	head->prev = malloc(sizeof(struct clist));
	head->prev->prev = NULL;
	head->prev->next = head;
	head->next->data = data;
	return head->prev;
}

void rfree(struct clist* node)
{
	struct clist *next = node->next;

	free(node);
	node = NULL;

	if(next) { rfree(next); }
}

void clist_free(struct clist *node)
{
	// ensuring we start from the head of our list
	struct clist *head = clist_head(node);
	rfree(head);	// recursive free to the tail
}

void rdestroy(struct clist* node)
{
	struct clist *next = node->next;

	free(node->data);
	node->data = NULL;

	free(node);
	node = NULL;

	if(next) { rdestroy(next); }
}

void clist_destroy(struct clist *node)
{
	// ensuring we start from the head of our list
	struct clist *head = clist_head(node);
	rdestroy(head);	// recursive destroy to the tail
}
