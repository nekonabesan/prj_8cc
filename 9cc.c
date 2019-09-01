#include "header.c"
#include "modules/9cc_error_module.c"
#include "modules/9cc_module.c"


int main(int argc, char **argv){
  if(argc != 2){
    error("%s: invalid number of argument", argv[0]);
    return 1;
  }


  user_input = argv[1];
  token = tokenize();
  Node *node = expr();

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  //
  gen(node);

  printf("  pop rax\n");
  printf("  ret\n");
  return 0;
}
