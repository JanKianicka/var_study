#ifndef FOO_H
#define FOO_H
typedef struct {
  int (* const bar)(int, char *);
  void (* const baz)(void);
} namespace_struct;
extern namespace_struct const foo;
#endif // FOO_H
