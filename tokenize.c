#include "9cc.h"

// Reports an error and exit
void error(char *fmt, ...){
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

//  Reports an error exit
void error_at(char *loc, char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);

    int pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "*%*s", pos, " ");
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// Consumes the current token if it matches 'op'
bool consume(char *op){
  if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)){
    return false;
  }
  token = token->next;
  return true;
}

// Ensure that the current token is 'op'
void expect(char *op){
  if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)){
    error_at(token->str, "expected \"%s\"", op);
  }
  token = token->next;
}

int expect_number(){
  if(token->kind != TK_NUM){
    error_at(token->str, "expected a number");
  }
  int val = token->val;
  token = token->next;
  return val;
}

bool at_eof(){
  return token->kind == TK_EOF;
}

// 新しいTokenを作成してcurへ繋げる処理
Token *new_token(TokenKind kind, Token *cur, char *str, int len){
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  tok->len = len;
  cur->next = tok;
  return tok;
}

bool startswith(char *p, char *q){
  return memcmp(p, q, strlen(q)) == 0;
}

// 入力文字列pをトークナイズしてそれを返す
Token *tokenize(){
  char *p = user_input;
  Token head;
  head.next = NULL;
  Token *cur = &head;

  while(*p){
    if(isspace(*p)){
      p++;
      continue;
    }

    if(startswith(p, "==") || startswith(p, "!=") || startswith(p, "<=") || startswith(p, ">=")){
      cur = new_token(TK_RESERVED, cur, p, 2);
      p += 2;
      continue;
    }

    if(strchr("+-*/()<>", *p)){
      cur = new_token(TK_RESERVED, cur, p++, 1);
      continue;
    }

    // Integer literal
    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p, 0);
      char *q = p;
      cur->val = strtol(p, &p, 10);
      cur->len = p - q;
      continue;
    }

    error_at(p, "invalid token");
  }

  new_token(TK_EOF, cur, p, 0);
  return head.next;
}
