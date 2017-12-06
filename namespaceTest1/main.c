#include <stdio.h>
#include "foo.h"
int main(void) {
  foo.baz();
  printf("%d", foo.bar(3, "hello"));
  return 0;
}
