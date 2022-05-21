#include <stdio.h>

void BlankRemovalComp(char *fileNAME, char *compNAME){
    FILE * file;
    FILE * comp;
    file = fopen(fileNAME,"r");
    comp = fopen(compNAME,"w");

    char c;
    int space = 0;

    size_t pos = ftell(file);    // Current position
    fseek(file, 0, SEEK_END);    // Go to end
    size_t length = ftell(file); // read the position which is the size
    fseek(file, pos, SEEK_SET);

    for (int i = 0; i < length; i++){
        c = getc(file);
        if (c == ' '){
            space++;
        }else{
            if (space == 0){
                fprintf(comp, "%c", c);
            }
            if(space == 1){
                fprintf(comp, " ");
                fprintf(comp, "%c", c);
            }
            if (space == 2){
                fprintf(comp, "  ");
                fprintf(comp, "%c", c);
            }
            if (space >= 3){
                char temp[555];
                sprintf(temp, "$%d", space);
                fprintf(comp, "%s", temp);
                fprintf(comp, "%c", c);
            }
            space =0;
        }
    }
    fclose(file);
    fclose(comp);
}

void BlankRemovalDecomp(char *compNAME, char *decompNAME){
    FILE * compfile;
    FILE * decompfile;
    compfile = fopen(compNAME,"r");
    decompfile = fopen(decompNAME,"w");

    char c;
    int space = 0;

    size_t pos2 = ftell(compfile);    // Current position
    fseek(compfile, 0, SEEK_END);     // Go to end
    size_t length2 = ftell(compfile); // read the position which is the size
    fseek(compfile, pos2, SEEK_SET);

    for (int i = 0; i < length2; i++){
        c = getc(compfile);
        if (c == '$'){
        }else{
            if( c >= '0' && c<= '9'){  //c est un number
                if(space == 0 ){
                    space = c - '0';
                    //printf("%d ", space);
                }else{
                    space = 10*space + c - '0';
                    //printf("%d \n", space);
                }
            }else{  //c n'est pas un number
                if (space == 0){
                    fprintf(decompfile, "%c", c);
                }
                if (space != 0){
                    for (int i = 0; i < space; i++){
                        fprintf(decompfile, " ");
                    }
                    fprintf(decompfile, "%c", c);
                    space = 0;
                }
            }
        }
    }
    fclose(compfile);
    fclose(decompfile);
}

double compressionRate(char *fileNAME, char *compNAME){
    FILE * file;
    FILE * comp;
    file = fopen(fileNAME,"r");
    comp = fopen(compNAME,"r");

    char c;
    double I=0, F=0;
    double rate;

    size_t pos = ftell(file);    // Current position
    fseek(file, 0, SEEK_END);    // Go to end
    size_t length = ftell(file); // read the position which is the size
    fseek(file, pos, SEEK_SET);
    I=length;
    printf("%f\n", I);

    size_t pos2 = ftell(comp);    // Current position
    fseek(comp, 0, SEEK_END);     // Go to end
    size_t length2 = ftell(comp); // read the position which is the size
    fseek(comp, pos2, SEEK_SET);
    F=length2;
    printf("%f\n", F);

    rate = (100-((F/I)*100));

    fclose(file);
    fclose(comp);
    return rate;
}

int main(){
    char * fileNAME ="white.txt";
    char * compNAME = "compressedWhite.txt";
    char * decompNAME = "decompressWhite.txt";
    char * statNAME = "stat.txt"; 
    double compRate;

    BlankRemovalComp(fileNAME, compNAME);
    BlankRemovalDecomp(compNAME, decompNAME);
    compRate = compressionRate(fileNAME, compNAME);

    FILE * stat;
    stat = fopen(statNAME, "w");
    char temp[555];
    sprintf(temp, "%s - Blank Removal - Compression Rate : %f\n", fileNAME, compRate);
    fprintf(stat, "%s", temp);
    printf("%s", temp);
    fclose(stat);

    return 0;
}