#include<stdio.h>
#include<stdlib.h>

int encrypt(void);
int decrypt(void);
int encrypt_view(void);
int decrypt_view(void);

FILE *fp1, *fp2;
char outChar;
char outChar2;

int main(void){
    int pick;

    while(1){
        printf("Select one of the following:\n");
        printf("\n1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. View the Encrypted File\n");
        printf("4. View the Decrypted file\n");
        printf("5. Exit");

        printf("\nWhich one?:\t");
        scanf("%d", &pick);

        switch(pick){
            case 1:
                encrypt();
                break;
            case 2:
                decrypt();
                break;
            case 3:
                encrypt_view();
                break;
            case 4:
                decrypt_view();
                break;
            case 5:
                exit(1);
        }
    }
    printf("\n");
    return 0;    
}

int encrypt(){
    printf("\n");
    fp1 = fopen("C:/Users/ahmed/Desktop/myFile.txt","r");

    if(fp1 == NULL){
        printf("File not found\n");
        exit(1);
    }

    fp2 = fopen("C:/Users/ahmed/Desktop/myFile.crp","w");

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
                fprintf(fp2,"%X", outChar & 0xff);
            }
        }
        
    }
    fclose(fp1);
    fclose(fp2);
    printf("\n");
    return 0;
}

int decrypt(){
    printf("\n");
    fp1 = fopen("C:/Users/ahmed/Desktop/myFile.crp","r");

    if(fp1 == NULL){
        printf("File not found\n");
        exit(1);
    }

    fp2 = fopen("C:/Users/ahmed/Desktop/myFile.txt","w");

    while(1){
        outChar = fgetc(fp1);
        outChar2 = fgetc(fp1);
        if(outChar == EOF){
            printf("\nEnd of file\n");
            break;
        }
        else{
            int f = (outChar*16) + outChar2;
            printf("%d\t%d\n",outChar,outChar2);
            printf("%d",f);
            if(f == 9){
                fprintf(fp2,"\t");
            }
            else if(f == 10){
                fprintf(fp2,"\n");
            }
            else{
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

int encrypt_view(){
    printf("\n");
    fp1 = fopen("C:/Users/ahmed/Desktop/myFile.crp","r");
    if(fp1 == NULL){
        printf("No file found\n");
        exit(1);
    }
    else{
        while(1){
            outChar = fgetc(fp1);
            if(outChar == EOF){
                break;
            }
            else{
                printf("%c", outChar);
            }
        }

        printf("\n");
        fclose(fp1);
    }
    printf("\n");
    return 0;
}

int decrypt_view(){
    printf("\n");
    fp1 = fopen("C:/Users/ahmed/Desktop/myFile.txt","r");
    if(fp1 == NULL){
        printf("No file found\n");
        exit(1);
    }
    else{
        while(1){
            outChar = fgetc(fp1);
            if(outChar == EOF){
                break;
            }
            else{
                printf("%c", outChar);
            }
        }

        printf("\n");
        fclose(fp1);
    }
    printf("\n");
    return 0;
}