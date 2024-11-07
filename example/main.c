#include "../src/cola.h"

int main() {
  COLA_Context *context = COLA_CreateContext(3);
  COLA_SetContent(context, "fizz.txt",  COLA_LoadFile, 0);
  COLA_SetContent(context, "-", COLA_LoadString, 1);
  COLA_SetContent(context, "buzz.txt", COLA_LoadFile, 2);
  COLA_WriteFile(context, "fizzbuzz.txt");
  COLA_DestroyContext(context);
  return 0;
}
