#include "String.h"
#include "new.h"
#include "new.r"

struct String {
	const void *class;			/* must be first */
	char *text;
};

static void * String_ctor (void * _self, va_list * app)
{
	struct String *self = _self;
	printf("I am in my ctor\n");
	self -> text = malloc(strlen(text) + 1);
	return self;
}

static void * String_dtor (void * _self)
{
	struct String *self = _self;
	printf("I am in my dtor\n");
	return self;
}

static void * String_clone (const void * _self)
{
	struct String * self = (void *) _self;
	printf("I am in my clone.\n");
	return self;
}

static int String_differ (const void * self, const void * b)
{
	printf("I am in my differ.\n");
	return self != b;
}

static const struct Class _String = {
	sizeof(struct String),
	String_ctor, String_dtor,
	String_clone, String_differ
};

const void * String = & _String;
