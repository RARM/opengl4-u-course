#include <stdio.h>
#include <stdlib.h>

char* read_file(FILE* const fp) {
  unsigned total_chars = 0;
  char* content = NULL;

  while (fgetc(fp) != EOF) total_chars++;
  content = (char*)malloc((size_t)(total_chars + 1) * sizeof(char));

  rewind(fp);
  for (int i = 0; i < total_chars; i++) *(content + i) = fgetc(fp);
  *(content + total_chars) = '\0';

  return content;
}

char* get_file_content(const char* const filename) {
  char* file_content;
  FILE* fp = fopen(filename, "r");

  if (fp != NULL) {
    file_content = read_file(fp);
    fclose(fp);
  } else {
    file_content = NULL;
  }

  return file_content;
}

int main(int argc, char* argv[]) {
  char* content = NULL;

  if (argc != 2) {
    printf("Missing argument: filename.\n");
  } else {
    content = get_file_content(argv[1]);
    printf("Printing file content:\n\n%s\n", content);
    free(content);
  }

  return 0;
}