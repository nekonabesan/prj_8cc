#ifndef _TARGET_H_

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//
// Toakenizer
//

typedef enum {
  TK_RESERVED,
  TK_IDENT,
  TK_NUM,
  TK_EOF,
} TokenKind;

// Token type
typedef struct Token Token;
struct Token{
  TokenKind kind;
  Token *next;
  int val;
  char *str;
  int len;
};

// Input program
char *user_input;

// Current token
Token *token;

//
// Paser
//

typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT , // <
  ND_LE,  // <=
  ND_NUM, // Integer
} NodeKind;

//
// As node type
//
typedef struct Node Node;
struct Node{
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
};

#define _TARGET_H_

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
void expect(char *op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, Token *cur, char *str, int len);
bool startswith(char *p, char *q);
Token *tokenize();
Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *primary();
void gen(Node *node);
Node *unary();

//
// codegen.c
//

void codegen(Node *node);

#endif /* _TARGET_H_ */
