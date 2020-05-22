#include "check_clist.h"
#include <stdlib.h>
#include "clist.h"

static int nums[] = { 1,2,3,4,5 };
static int nnums = 5;

static struct clist *head;

void teardown()
{
	head = NULL;
}

void free_forward_setup()
{
	head = clist_new(nums);
	for(int i = 1; i < nnums; ++i) {
		clist_append(head, &nums[i]);
	}
}

void free_rev_setup()
{
	head = clist_new(&nums[nnums-1]);
	for(int i = nnums-2; i >= 0; --i) {
		clist_append(head, &nums[i]);
	}
}

void destroy_forward_setup()
{
	int *tmp = malloc(sizeof(int));
	*tmp = nums[0];

	head = clist_new(tmp);
	for(int i = 1; i < nnums; ++i) {
		int *tmp = malloc(sizeof(int));
		*tmp = nums[i];
		clist_append(head, tmp);
	}
}

void destroy_rev_setup()
{
	int *tmp = malloc(sizeof(int));
	*tmp = nums[nnums-1];

	head = clist_new(tmp);
	for(int i = nnums-2; i >= 0; --i) {
		int *tmp = malloc(sizeof(int));
		*tmp = nums[i];
		clist_append(head, tmp);
	}
}

void forward_checks()
{
	int i = 0;
	struct clist *node = head;

	// checking our head is valid
	ck_assert_ptr_nonnull(head);
	ck_assert_ptr_null(head->prev);
	ck_assert_ptr_nonnull(head->next);

	do {
		ck_assert_int_eq(*(int*)node->data, nums[i]);
		node = node->next;
		++i;
	} while (node != NULL);

	ck_assert_int_eq(i, nnums);
}

void reverse_checks()
{
	int i = nnums-1;
	struct clist *node = head;

	// checking our head is valid
	ck_assert_ptr_nonnull(head);
	ck_assert_ptr_null(head->prev);
	ck_assert_ptr_nonnull(head->next);

	do {
		ck_assert_int_eq(*(int*)node->data, nums[i]);
		node = node->next;
		--i;
	} while (node != NULL);

	ck_assert_int_eq(i, -1);
}

START_TEST(clist_test_free_forward)
{
	free_forward_setup();
	forward_checks();
}
END_TEST

START_TEST(clist_test_free_reverse)
{
	free_rev_setup();
	reverse_checks();
}
END_TEST

START_TEST(clist_test_destroy_forward)
{
	destroy_forward_setup();
	forward_checks();
}
END_TEST

START_TEST(clist_test_destroy_reverse)
{
	destroy_rev_setup();
	reverse_checks();
}
END_TEST

Suite * clist_suite(void)
{
	Suite *s;
	TCase *free_case;
	TCase *destroy_case;

	s = suite_create("clist suite");
	free_case = tcase_create("clist (free)");
	destroy_case = tcase_create("clist (destroy)");

	tcase_add_test(free_case, clist_test_free_forward);
	tcase_add_test(free_case, clist_test_free_reverse);

	tcase_add_test(destroy_case, clist_test_destroy_forward);
	tcase_add_test(destroy_case, clist_test_destroy_reverse);

	suite_add_tcase(s, free_case);
	suite_add_tcase(s, destroy_case);
	return s;
}
