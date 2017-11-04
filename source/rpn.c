#include <stdlib.h>
#include <string.h>
#define SYM_END 0
#define SYM_READ4 1
#define SYM_READN 3
#define SYM_JUMPN 4
#define SYM_ADD 5
#define SYM_ADDF 6
#define SYM_SUB 7
#define SYM_SUBF 8
#define SYM_MUL 9
#define SYM_MULF 10
#define SYM_DIV 11
#define SYM_DIVF 12
#define SYM_MOD 13
#define SYM_MODF 14
#define SYM_SHL 15
#define SYM_SHR 16
#define SYM_INT2FLOAT 17
#define SYM_FLOAT2INT 18
 
void * eval(unsigned char * stack, unsigned char * bytecode){
  uint32_t tempi = 0;
  float tempf = 0;
  int running = 1;
  char code;
  
  while (running){
    code = *(bytecode++);
    switch(code){
    case SYM_END:
      running = 0;
      break;
    case SYM_READ4:
      memcpy(stack, bytecode, 4);
      bytecode += 4;
      stack += 4;
      break;
    case SYM_READN:
      tempi = *((uint32_t *)bytecode);
      memcpy(stack, bytecode, tempi);
      bytecode += tempi;
      stack += tempi;
      break;
    case SYM_JUMPN:
      tempi = *((uint32_t *)bytecode);
      memcpy(stack, bytecode, tempi);
      bytecode += tempi;
      break;
      
    case SYM_ADD:
      stack -= 4;
      *(((int32_t *)stack) - 1) = *(((int32_t *)stack) - 1) + *(((int32_t *)stack) + 1);
      break;
    case SYM_ADDF:
      stack -= 4;
      *(((float *)stack) - 1) = *(((float *)stack) - 1) + *((float *)stack);
      break;
      
    case SYM_SUB:
      stack -= 4;
      *(((int32_t *)stack) - 1) = *(((int32_t *)stack) - 1) - *((int32_t *)stack);
      break;
    case SYM_SUBF:
      stack -= 4;
      *(((float *)stack) - 1) = *(((float *)stack) - 1) - *((float *)stack);
      break;
    case SYM_MUL:
      stack -= 4;
      *(((int32_t *)stack) - 1) = *(((int32_t *)stack) - 1) * *((int32_t *)stack);
      break;
    case SYM_MULF:
      stack -= 4;
      *(((float *)stack) - 1) = *(((float *)stack) - 1) * *((float *)stack);
      break;
    case SYM_DIV:
      stack -= 4;
      *(((int32_t *)stack) - 1) = *(((int32_t *)stack) - 1) / *((int32_t *)stack);
      break;
    case SYM_DIVF:
      stack -= 4;
      *(((float *)stack) - 1) = *(((float *)stack) - 1) / *((float *)stack);
      break;
    case SYM_MOD:
      stack -= 4;
      *(((int32_t *)stack) - 1) = *(((int32_t *)stack) - 1) % *((int32_t *)stack);
      break;
    case SYM_MODF:
      stack -= 4;
      *(((float *)stack) - 1) = *(((float *)stack) - 1) % *((float *)stack);
      break;
    case SYM_SHL:
      stack -= 4;
      *(((int32_t *)stack) - 1) = *(((int32_t *)stack) - 1) << *((int32_t *)stack);
      break;
    case SYM_SHR:
      stack -= 4;
      *(((int32_t *)stack) - 1) = *(((int32_t *)stack) - 1) >> *((int32_t *)stack);
      break;
      
    case SYM_INT2FLOAT:
      *(((float *)stack) - 1) = (float)*(((int32_t *)stack) - 1);
      break;
    case SYM_FLOAT2INT:
      *(((int32_t *)stack) - 1) = (int)*(((float *)stack) - 1);
      break;
    default:
      running = 0;
      break;
    }
  }
}

int main(){
  //1 2 +
}
