/* $Id$ */

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "ast.h"
#include "xalloc.h"

struct ast_term *
ast_make_empty_term(void)
{
	struct ast_term *new;

	new = xmalloc(sizeof *new);
	new->type = TYPE_EMPTY;
	new->next = NULL;

	return new;
}

struct ast_term *
ast_make_rule_term(const char *name)
{
	struct ast_term *new;

	assert(name != NULL);

	new = xmalloc(sizeof *new);
	new->type   = TYPE_RULE;
	new->next   = NULL;
	new->u.name = name;

	return new;
}

struct ast_term *
ast_make_literal_term(const char *literal)
{
	struct ast_term *new;

	assert(literal != NULL);

	new = xmalloc(sizeof *new);
	new->type      = TYPE_TERMINAL;	/* TODO: rename to literal or vice-versa, perhaps */
	new->next      = NULL;
	new->u.literal = literal;

	return new;
}

struct ast_term *
ast_make_group_term(struct ast_alt *group)
{
	struct ast_term *new;

	new = xmalloc(sizeof *new);
	new->type    = TYPE_GROUP;
	new->next    = NULL;
	new->u.group = group;

	return new;
}

struct ast_alt *
ast_make_alt(struct ast_term *terms)
{
	struct ast_alt *new;

	new = xmalloc(sizeof *new);
	new->terms = terms;
	new->next  = NULL;

	return new;
}

struct ast_rule *
ast_make_rule(const char *name, struct ast_alt *alts)
{
	struct ast_rule *new;

	assert(name != NULL);

	new = xmalloc(sizeof *new);
	new->name = name;
	new->alts = alts;
	new->next = NULL;

	return new;
}

struct ast_rule *
ast_find_rule(const struct ast_rule *grammar, const char *name)
{
	const struct ast_rule *p;

	assert(name != NULL);

	for (p = grammar; p != NULL; p = p->next) {
		if (0 == strcmp(p->name, name)) {
			return (struct ast_rule *) p;
		}
	}

	return NULL;
}
