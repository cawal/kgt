
/*
 * Automatically generated by lexi version 2.0
 * Copyright terms for the input source also apply to this generated code.
 */

#include <assert.h>
#include <string.h>

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L
#include <stdbool.h>
#include <stdint.h>
#endif



	#include <assert.h>
	#include <stdio.h>
	#include <stdlib.h>

	#include "../io.h"
	#include "../tokens.h"
	#include "../xalloc.h"

	#include "lexer.h"

	/*
	 * Interfaces for the generated lexer.
	 */

	typedef enum tok ZTTERMINAL;


	FILE *io_fin;
	unsigned int io_line;

	char io_buffer[1024];

	size_t bufferindex;


	/*
	 * Lexi's interface to get a character from our input stream.
	 */
	static int
	lexi_getchar(struct bnf_state *state)
	{
		int c;

		assert(state != NULL);

		(void) state;

		c = getc(io_fin);
		if (c == EOF) {
			return EOF;
		}

		if (c == '\n') {
			io_line++;
		}

		return c;
	}

int wsn_readchar(struct wsn_state *state) {
	if (state->buffer_index) {
		return wsn_pop(state);
	}

	return lexi_getchar(state);
}
void wsn_push(struct wsn_state *state, const int c) {
	assert(state);
	assert((size_t) state->buffer_index < sizeof state->buffer / sizeof *state->buffer);
	state->buffer[state->buffer_index++] = c;
}

int wsn_pop(struct wsn_state *state) {
	assert(state);
	assert(state->buffer_index > 0);
	return state->buffer[--state->buffer_index];
}

void wsn_flush(struct wsn_state *state) {
	state->buffer_index = 0;
}


/* LOOKUP TABLE */

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L
typedef uint8_t lookup_type;
#else
typedef unsigned char lookup_type;
#endif
static lookup_type lookup_tab[] = {
	   0,    0,    0,    0,    0,    0,    0,    0,    0,  0x1,  0x1,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,  0x1,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,  0x2,    0,    0, 
	 0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,    0,    0, 
	   0,    0,    0,    0,    0,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2, 
	 0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2, 
	 0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,    0,    0,    0,    0,  0x2, 
	   0,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2, 
	 0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2, 
	 0x2,  0x2,  0x2,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
	   0,    0,    0,    0
};

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L
bool wsn_group(enum wsn_groups group, int c) {
#else
int wsn_group(enum wsn_groups group, int c) {
#endif
	if (c == LEXI_EOF) {
		return 0;
	}
	return lookup_tab[c] & group;
}


/* PRE-PASS ANALYSERS */

void wsn_init(struct wsn_state *state) {
	state->zone = wsn_next;
	state->buffer_index = 0;
}
/* ZONES PASS ANALYSER PROTOTYPES */

static int wsn_next_identifier(struct wsn_state *state);
static int wsn_next_literal(struct wsn_state *state);
/* MAIN PASS ANALYSERS */


/* MAIN PASS ANALYSER for identifier */
static int
wsn_next_identifier(struct wsn_state *state)
{
	start: {
		int c0 = wsn_readchar(state);
		if (c0 == LEXI_EOF) {
			/* ACTION <err_unexpected_eof> */
			{

	xerror("unexpected EOF on line %d", io_line);
			}
			/* END ACTION <err_unexpected_eof> */
			goto start; /* leaf */
		}
		if (!wsn_group(wsn_group_character, c0)) {
			wsn_push(state, c0);
			return TOK_NAME;
		}

		/* DEFAULT */
		/* ACTION <io_push> */
		{

	io_push(c0);
		}
		/* END ACTION <io_push> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for literal */
static int
wsn_next_literal(struct wsn_state *state)
{
	start: {
		int c0 = wsn_readchar(state);
		switch (c0) {
		case LEXI_EOF: {
				/* ACTION <err_unexpected_eof> */
				{

	xerror("unexpected EOF on line %d", io_line);
				}
				/* END ACTION <err_unexpected_eof> */
				goto start; /* leaf */
			}

		case '"': {
				int c1 = wsn_readchar(state);
				if (c1 == '"') {
					/* ACTION <io_push> */
					{

	io_push(c0);
					}
					/* END ACTION <io_push> */
					goto start; /* leaf */
				}
				wsn_push(state, c1);
				/* ACTION <io_literal> */
				{
					ZTTERMINAL ZT1;

	ZT1 = io_literal();
					return ZT1;
				}
				/* END ACTION <io_literal> */
			}

		}

		/* DEFAULT */
		/* ACTION <io_push> */
		{

	io_push(c0);
		}
		/* END ACTION <io_push> */
		goto start; /* DEFAULT */
	}
}

/* MAIN PASS ANALYSER for global zone */
int
wsn_next(struct wsn_state *state)
{
	if (state->zone != wsn_next)
		return state->zone(state);
	start: {
		int c0 = wsn_readchar(state);
		if (wsn_group(wsn_group_white, c0)) goto start;
		switch (c0) {
		case ')': {
				return TOK_END_HGROUP;
			}

		case '(': {
				return TOK_START_HGROUP;
			}

		case ']': {
				return TOK_END_HOPT;
			}

		case '[': {
				return TOK_START_HOPT;
			}

		case '}': {
				return TOK_END_HSTAR;
			}

		case '{': {
				return TOK_START_HSTAR;
			}

		case '"': {
				return wsn_next_literal(state);
			}

		case '.': {
				return TOK_SEP;
			}

		case LEXI_EOF: {
				return TOK_SEP;
			}

		case '|': {
				return TOK_ALT;
			}

		case '=': {
				return TOK_EQUALS;
			}

		}
		if (wsn_group(wsn_group_character, c0)) {
			/* ACTION <io_push> */
			{

	io_push(c0);
			}
			/* END ACTION <io_push> */
			return wsn_next_identifier(state);
		}

		/* DEFAULT */
		/* ACTION <err_unexpected_character> */
		{

	xerror("unexpected character \"%c\" on line %d", c0, io_line);
		}
		/* END ACTION <err_unexpected_character> */
		goto start; /* DEFAULT */
	}
}



