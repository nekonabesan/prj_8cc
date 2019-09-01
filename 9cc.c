#include "header.c"
#include "modules/9cc_error_module.c"
#include "modules/9cc_module.c"


int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "Arguments Error");
    return 1;
  }


  user_input = argv[1];
  token = tokenize();

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  printf("  mov rax, %d\n", expect_number());
  //
  while (!at_eof()){
    if(consume('+')){
      printf("  add rax, %d\n", expect_number());
      continue;
    }

    expect('-');
    printf("  sub rax, %d\n", expect_number());
  }

  printf("  ret\n");
  return 0;
}
