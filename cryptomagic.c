#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chartoint(char char1);
int encrypt(char name[]);
int decrypt(char name[]);

FILE *fp1, *fp2;
char outChar;
char outChar2;
int outint;
int outint2; 

int main(int argc, char *argv[]) {
    
  if (strcmp(argv[1],"decrypt") ==0){
    decrypt(argv[2]);
  }
  else if (strcmp(argv[1],"encrypt") ==0){
    encrypt(argv[2]);
    }
  else{
    encrypt(argv[1]);
  }
  printf("\n");

  return 0;   
}

int encrypt(char name[]){
  
  char directory[] = "C:/Users/ahmed/Desktop/";
  char directory2[] = "C:/Users/ahmed/Desktop/";
  strcat(directory,name);
  strcat(directory2,name);

  strcat(directory, ".txt");
  fp1 = fopen(directory,"r");

  if(fp1 == NULL){
    printf("File not found\n");
    exit(1);
  }
  strcat(directory2, ".crp");
  fp2 = fopen(directory2,"w");

  while(1){
    outChar = fgetc(fp1);
    if(outChar == EOF){
      printf("\nEnd of file\n");
      break;
    }
    else{
      if(outChar == 13){
        fprintf(fp2,"\r");
      }
      else if(outChar == 10){
        fprintf(fp2,"\n");
      }
      else if(outChar == 9){
        fprintf(fp2,"TT");
      }
      else{
        outChar -= 16;
        if(outChar < 32){
          outChar += 112;
        }
      fprintf(fp2,"%X", (unsigned char)outChar);
      }
    }
  }
  fclose(fp1);
  fclose(fp2);
  printf("\n");

  return 0;
}


int decrypt(char name[]){

  char directory[] = "C:/Users/ahmed/Desktop/";
  char directory2[] = "C:/Users/ahmed/Desktop/";
  strcat(directory,name);
  strcat(directory2,name);
  printf("\n");
  strcat(directory, ".crp");
  fp1 = fopen(directory,"r");

  if(fp1 == NULL){
    printf("File not found\n");
    exit(1);
  }
  strcat(directory2, ".txt");
  fp2 = fopen(directory2,"w");

  while(1){
    outChar = fgetc(fp1);
    if(outChar == EOF){
      printf("\nEnd of file\n");
      break;
    }
    else{
      if(outChar == 10)
      {
        fprintf(fp2,"\n");
      }
      else if(outChar == 13)
      {
        fprintf(fp2,"\r");
      }
      else if(outChar == 'T')
      {
        outChar2 = fgetc(fp1);
        fprintf(fp2,"\t");
      }
      else
      {
        outChar2 = fgetc(fp1);
        unsigned char f = (chartoint(outChar)*16 + chartoint(outChar2));
        f += 16;
        if(f > 127){
          f -= 112;
        }
        fputc(f, fp2);
      }
    }
  }
  fclose(fp1);
  fclose(fp2);
  printf("\n");

  return 0;
}


int chartoint(char char1) {
  int num;
  if (char1 < 58)
  {
    num = char1 - '0';
  }
  else
  {
    num = char1-'A'+10;
  }

  return num;
}