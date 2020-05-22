#include "runner.h"
#include "check_clist.h"
#include <stdlib.h>

int main()
{
	int failed_count = run_suite_forkless(clist_suite());
	return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
