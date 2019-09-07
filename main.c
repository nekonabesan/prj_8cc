#include "9cc.h"

int main(int argc, char **argv){
  if(argc != 2){
    error("%s: invalid number of argument", argv[0]);
  }

  // Tonkenize and parse
  user_input = argv[1];
  token = tokenize();
  Node *node = expr();

  // Print out the first half of assembly
  codegen(node);

  return 0;
}
