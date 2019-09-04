#include "../header.c"
//
void error(char *fmt, ...){
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

bool consume(char op){
  if(token->kind != TK_RESERVED || token->str[0] != op){
    return false;
  }
  token = token->next;
  return true;
}

void expect(char op){
  if (token->kind != TK_RESERVED || token->str[0] != op){
    error_at(token->str, "expected '%c'", op);
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
Token *new_token(TokenKind kind, Token *cur, char *str){
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  cur->next = tok;
  return tok;
}

// 入力文字列pをトークナイズしてそれを返す
Token *tokenize(){
  char *p = user_input;
  Token head;
  head.next = NULL;
  Token *cur = &head;

  while(*p){
    //printf("%s\n", p);
    if(isspace(*p)){
      p++;
      continue;
    }

    if(strchr("+-*/()", *p)){
      cur = new_token(TK_RESERVED, cur, p++);
      continue;
    }

    if(isdigit(*p)){
      cur = new_token(TK_NUM, cur, p);
      cur->val = strtol(p, &p, 10);
      // /printf("%s\n", cur->str);
      continue;
    }
    error_at(p, "invalid token");
  }

  new_token(TK_EOF, cur, p);
  return head.next;
}

Node *new_node(NodeKind kind){
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;
  return node;
}

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs){
  Node *node = new_node(kind);
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node *new_num(int val){
  Node *node = new_node(ND_NUM);
  node->val = val;
  return node;
}

Node *new_node_num(int val){
  Node *node = calloc(1, sizeof(Node));
  node->kind = ND_NUM;
  node->val = val;
  return node;
}

Node *expr() {
  Node *node = mul();

  for(;;){
    if(consume('+')){
      node = new_binary(ND_ADD, node, mul());
    } else if(consume('-')) {
      node = new_binary(ND_SUB, node, mul());
    } else {
      return node;
    }
  }

}

Node *mul() {
  Node *node = unary();

  for(;;){
    if(consume('*')){
      node = new_binary(ND_MUL, node, unary());
    } else if(consume('/')) {
      node = new_binary(ND_DIV, node, unary());
    } else {
      return node;
    }
  }
}

Node *primary() {
  if(consume('(')){
    Node *node = expr();
    expect(')');
    return node;
  }

  return new_node_num(expect_number());
}

void gen(Node *node){
  if(node->kind == ND_NUM){
    printf("  push %d\n", node->val);
    return;
  }

  gen(node->lhs);
  gen(node->rhs);

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->kind) {
    case ND_ADD:
      printf("  add rax, rdi\n");
      break;
    case ND_SUB:
      printf("  sub rax, rdi\n");
      break;
    case ND_MUL:
      printf("  imul rax, rdi\n");
      break;
    case ND_DIV:
      printf("  cqo\n");
      printf("  idiv rdi\n");
      break;
  }

  printf("  push rax\n");
}

Node *unary(){
  if(consume('+')){
    return primary();
  }
  if(consume('-')){
    return new_binary(ND_SUB, new_node_num(0), primary());
  }
  return primary();
}
