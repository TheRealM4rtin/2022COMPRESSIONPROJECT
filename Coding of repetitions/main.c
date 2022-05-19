#include <stdio.h>
#include <stdlib.h>

void Compress( char * filename_input, char * filename_output ){

    char c;
    int count = 0;
    FILE * file_out;
    FILE * file_in;
	file_in = fopen(filename_input, "r");
    file_out = fopen(filename_output, "w");

    //Loop over the file
    while( ( c = fgetc(file_in) ) != EOF ){

        if( c == ' ' ){
            count ++;
        }
        else{
            if( count == 0 ){
                fprintf(file_out, "%c", c);
            }
            if( count == 1 ){
                fprintf(file_out, "%s", " ");
                count = 0;
            }
            if( count == 2 ){
                fprintf(file_out, "%s", "  ");
                count = 0;
            }
            if( count >= 3 ){
                char out[50];
                sprintf(out, "$%d", count);
                fprintf(file_out, out);
                count = 0;
            }
            
        }
    }

    fclose(file_in);
    fclose(file_out);
}

void Decompress(char * filename_input, char * filename_output){

    int a = 0, count = 0, i, LINES = 0;
    char c;
    FILE * file_in;
    FILE * file_out;
    file_in = fopen(filename_input, "r");
    file_out = fopen(filename_output, "w");


    while ( (c = fgetc(file_in)) !=EOF){
        
        if(LINES >= 200){
            fprintf(file_out, "%s", "\r");
            LINES = LINES - 200 ;
        }

        if( c == '$'){
            fprintf(file_out, "%s", " ");
            LINES++;
        }

        if (c >= '0' && c <= '9'){
            if(count == 0){
                a = c - '0';
                count++;
            }
            
            else{
                a = (10*a + (c - '0') );
                count++;
            }
        }
       
        if( (c < '0' || c > '9') ){
            if(count > 0){
                for(i = 0; i < a-1; i++){
                    fprintf(file_out, "%s", " ");

                    if(LINES >= 200){
                        fprintf(file_out, "%s", "\n");
                        LINES = LINES - 200 ;
                    }
                    LINES++;
                }
                a = 0;
                count = 0;
            }
            if(c != '$'){
                fprintf(file_out, "%c", c);
                LINES++;
            }
        }
    }
    
    fclose(file_in);
    fclose(file_out);
}




int main(){

    char * a ="white.txt";
    char * b = "compressed.txt";
    char * c = "decompressed.txt";

    Compress(a, b);
    Decompress(b, c);
}