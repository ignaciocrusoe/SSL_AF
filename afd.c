#include <stdlib.h>
#include <stdio.h>

#define CANT_ESTADOS 4
#define CANT_SIMBOLOS 3

// Definición de los estados del AFD
typedef enum {
    Q0,
    Q1,
    Q2,
    Q3
} t_estado;

typedef enum {
    A,
    B,
    C
} t_caracter;

#define ESTADO_FINAL Q2

// Definición de la tabla de transiciones
int tabla_transiciones[CANT_ESTADOS][CANT_SIMBOLOS] = {
    {Q1, Q3, Q2},
    {Q3, Q0, Q3},
    {Q3, Q2, Q3},
    {Q3, Q3, Q3}
};

t_estado char_to_enum(char c){
    switch (c)
    {
    case 'a':
        return A;
        break;

    case 'b':
        return B;
        break;

    case 'c':
        return C;
        break;
    
    default:
        break;
    }
}

// Función para verificar si la cadena es aceptada por el AFD
void transicion(FILE* input, FILE* output) {
    char c;
    int estado = 0;
    while((c = fgetc(input)) != EOF){
        if(c!=','){
            fputc(c, output);
            estado = tabla_transiciones[estado][char_to_enum(c)];
        }
        else{
            fputs("    ", output);
            if(estado == ESTADO_FINAL){
                fputs("Acepatda", output);
            }
            else{
                 fputs("No Acepatda", output);
            }
            estado = 0;
        }
    }
    fputs("    ",output);
    if(estado == ESTADO_FINAL){
                fputs("Acepatda", output);
            }
            else{
                 fputs("No Acepatda", output);
            }
}

int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("Debe pasar un nombre de archivo como parámetro.\n");
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("Error al intentar abrir el archivo %s.\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    transicion(file, stdout);

    fclose(file);
    return EXIT_SUCCESS;
}
