#include "foo.h"
static int my_bar(int a, char * s) { /* ... */ }
static void my_baz(void) { /* ... */ }
namespace_struct const foo = { my_bar, my_baz };
