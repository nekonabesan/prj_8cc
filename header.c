#ifndef _TARGET_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
  TK_RESERVED,
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct Token Token;

typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_NUM, // whole number
} NodeKind;

typedef struct Node Node;

struct Token{
  TokenKind kind;
  Token *next;
  int val;
  char *str;
};

struct Node{
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
};

Token *token;
char *user_input;

#define _TARGET_H_

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str);
Token *tokenize();
Node *new_node(NodeKind kind, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *expr();
Node *mul();
Node *primary();

#endif /* _TARGET_H_ */
