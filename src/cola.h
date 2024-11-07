
// MIT No Attribution

// Copyright 2024 Antônio Ivo da Silva Gomes

// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  COLA_LoadFile,
  COLA_LoadString
} COLA_LoadType;

typedef struct {
  unsigned char content_loaded;
  char *content;
} COLA_Content;

typedef struct {
  unsigned int content_count;
  COLA_Content *content;
} COLA_Context;

inline COLA_Context *COLA_CreateContext(unsigned int content_count) {
  COLA_Context *context;

  context = (COLA_Context *)malloc(sizeof(COLA_Context));

  if (context != NULL) {
    context->content = (COLA_Content *)malloc(sizeof(COLA_Context) * content_count);
  }

  if (context->content != NULL) {
    context->content_count = content_count;
  } else {
    free(context);
    context = NULL;
  }

  return context;
}

inline void COLA_DestroyContext(COLA_Context *context) {
  for (int i = 0; i < context->content_count; i++) {
    if (context->content[i].content_loaded) {
      free(context->content[i].content);
    }
    free(context->content + i);
  }

  free(context->content);
  free(context);
}

inline void COLA_SetContent(COLA_Context *context, char *content, COLA_LoadType type, unsigned int index) {
  char *content_buffer;

  if (type == COLA_LoadFile) {
    FILE *file_content = fopen(content, "r");

    fseek(file_content, 0, SEEK_END);
    int size = ftell(file_content);
    rewind(file_content);

    content_buffer = (char *)malloc(size);

    fread(content_buffer, 1, size, file_content);

    fclose(file_content);

    context->content[index].content = content_buffer;
  } else {
    context->content[index].content = content;
  }

  context->content[index].content_loaded = 1;
}

inline void COLA_WriteContentInFile(COLA_Context *context, FILE *file, unsigned int index) {
  fprintf(file, "%s", context->content[index].content);
}

inline void COLA_WriteFile(COLA_Context *context, char *filename) {
  FILE *file = fopen(filename, "w");

  for (int i = 0; i < context->content_count; i++) {
    if (!context->content[i].content_loaded) {
      continue;
    }
    COLA_WriteContentInFile(context, file, i);
  }

  fclose(file);
};
