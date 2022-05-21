#include <stdio.h>

void RLEComp(char *fileNAME, char *compNAME){
    FILE * file;
    FILE * comp;
    file = fopen(fileNAME,"r");
    comp = fopen(compNAME,"w");

    char c1, c2;
    int repetition = 0;
    c1 = getc(file);

    while (!feof (file)){
        c2 = getc(file);
        if (c1 == c2)
        {
            repetition++;
        }else{
            if (repetition==0)
            {
                fprintf(comp, "%c", c1);
            }else{
                if (repetition >= 3){
                    char temp3[500];
                    repetition++;
                    sprintf(temp3, "$%d%c", repetition, c1);
                    fprintf(comp, "%s", temp3);
                    repetition = 0;
                }
                if (repetition == 2){
                    fprintf(comp, "%c%c%c", c1, c1, c1);
                    repetition = 0;
                }
                if(repetition == 1){
                    fprintf(comp, "%c%c", c1, c1);
                    repetition = 0;
                }
            }
        }
        c1=c2;
    }
    fclose(file);
    fclose(comp);
}

void RLEDecomp(char *compNAME, char *decompNAME){
    FILE * compfile;
    FILE * decompfile;
    compfile = fopen(compNAME,"r");
    decompfile = fopen(decompNAME,"w");

    char c;
    int repetition = 0;

    size_t pos2 = ftell(compfile);    // Current position
    fseek(compfile, 0, SEEK_END);    // Go to end
    size_t length2 = ftell(compfile); // read the position which is the size
    fseek(compfile, pos2, SEEK_SET);

    for (int i = 0; i < length2; i++){
        c = getc(compfile);
        if (c == '$'){
        }else{
            if (c >= '0' && c<= '9'){
                if (repetition == 0)
                {
                    repetition = c - '0';
                    //printf("%d ", repetition);
                }else{
                    repetition = 10*repetition + c - '0';
                    //printf("%d \n", repetition);
                }
            }else{
                if (repetition == 0){
                    fprintf(decompfile, "%c", c);
                }
                if( repetition != 0){
                    for (int i = 0; i < repetition; i++){
                        fprintf(decompfile, "%c", c);
                    }
                    repetition = 0;
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

    size_t pos2 = ftell(comp);    // Current position
    fseek(comp, 0, SEEK_END);    // Go to end
    size_t length2 = ftell(comp); // read the position which is the size
    fseek(comp, pos2, SEEK_SET);
    F=length2;

    rate = (100-((F/I)*100));
    
    /*nom du fichier, type compression, compression rate
    char temp[555];
    sprintf(temp, "%s - RLE - Compression Rate : %f", fileNAME, rate);
    fprintf(stat, "%s", temp);*/

    fclose(file);
    fclose(comp);
    return rate;
}

int main(){
    char * fileNAME ="rle.txt";
    char * compNAME = "compressedRLE.txt";
    char * decompNAME = "decompressRLE.txt";
    char * statNAME = "stat.txt";
    double compRate;

    RLEComp(fileNAME, compNAME);
    RLEDecomp(compNAME, decompNAME);
    compRate = compressionRate(fileNAME, compNAME);
    
    FILE * stat;
    stat = fopen(statNAME, "w");
    char temp[555];
    sprintf(temp, "%s - RLE - Compression Rate : %f\n", fileNAME, compRate);
    fprintf(stat, "%s", temp);
    printf("%s", temp);
    fclose(stat);

    return 0;
}