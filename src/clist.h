#pragma once

struct clist {
	struct clist *next;
	struct clist *prev;
	void *data;
};

struct clist *clist_new(void *data);
struct clist *clist_append(struct clist *node, void *data);
struct clist *clist_prepend(struct clist *node, void *data);
void clist_free(struct clist *node);				// frees the list
void clist_destroy(struct clist *node);			// frees the list, and its data
struct clist* clist_tail(struct clist *node);
struct clist* clist_head(struct clist *node);
