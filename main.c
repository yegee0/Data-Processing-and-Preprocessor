#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "P_header.h"

struct ArrayTable {
    char name[10];
    int dim;
    char size1[10];
    char size2[10];
};

struct ArrayTable AT[20];
int arrayCount = 0;

struct ParseTabel {
    char oper[10];
    char lhs[10];
    char rhs1[10];
    char rhs2[10];
};

struct ParseTabel PT;

void parser(char* line);
char* declareArray();
char* readArray();
char* copyArray();
char* initArray();
char* printArray();
char* dotProduct();
char* arrayAddition();
char* arrayMultiplication();
char* arraySum();
char* arrayAverage();

void parser(char* line) {
    
    //Clean PT Fields
    strcpy(PT.oper, "");
    strcpy(PT.lhs, "");
    strcpy(PT.rhs1, "");
    strcpy(PT.rhs2, "");

    char* token = strtok(line, " .+*(),=<>\n");

    //Save Elements from Line
    if (token != NULL) {
    strcpy(PT.oper, token);

        token = strtok(NULL, " .+*(),=<>\n");
        if (token != NULL) {
            strcpy(PT.lhs, token);
        }

        token = strtok(NULL, " .+*(),=<>\n");
        if (token != NULL) {
            strcpy(PT.rhs1, token);
        }

        token = strtok(NULL, " .+*(),=<>\n");
        if (token != NULL) {
            strcpy(PT.rhs2, token);
        }
    }

};

char* declareArray() {
    
    static char expandedLine[100];
    strcpy(expandedLine, "");

    char arrayName[10];
    int dim = 1;
    char size1[10], size2[10];

    //Copy Array Attributes
    strcpy(arrayName, PT.lhs);
    strcpy(size1, PT.rhs1);

    //If array is 2D copy depth of array
    if(PT.rhs2[0] != '\0') {
        dim = 2;
        strcpy(size2, PT.rhs2);
    };

    //Update ArrayTable
    strcpy(AT[arrayCount].name, arrayName);
    AT[arrayCount].dim = dim;
    strcpy(AT[arrayCount].size1, size1);
    strcpy(AT[arrayCount].size2, size2);
    arrayCount++;


    //Generate expanded line
    if(dim == 1) {
        //Generate Code for 1D
        sprintf(expandedLine, "    int %s[%s];\n", arrayName, size1);
    }else {
        //Generate Code for 2D
        sprintf(expandedLine, "    int %s[%s][%s];\n", arrayName, size1, size2);
    }

    return expandedLine;
};

char* readArray() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char arrayName[10];
    char fileName[20];

    //Copy Array Attributes
    strcpy(arrayName, PT.lhs);
    strcpy(fileName, PT.rhs1);

    //Open File
    sprintf(expandedLine, "    FILE *file%s = fopen(\"../%s\", \"r\");\n", fileName, fileName);
    

    //Expand Line Based on Dimension
    for(int i = 0; i < arrayCount; i++) {
        if(strcmp(AT[i].name , arrayName) == 0){
            if(AT[i].dim == 1){
                //Generate Code for 1D
                sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        fscanf(file%s, \"%%d\", &%s[i]);\n", fileName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }else {
                //Generate Code for 2D
                sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < (int)(sizeof(%s[0])/sizeof(%s[0][0])); j++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "            fscanf(file%s, \"%%d\", &%s[i][j]);\n", fileName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        }\n");
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }
            break;
        }

    }

    //Close File
    sprintf(expandedLine + strlen(expandedLine), "    fclose(file%s);\n", fileName);

    return expandedLine;

};

char* copyArray() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char targetArray[10];
    char sourceArray[10];

    //Copy Array Attributes
    strcpy(targetArray, PT.lhs);
    strcpy(sourceArray, PT.rhs1);

    //Expand Line Based on Dimension
    for (int i = 0; i < arrayCount; i++) {
        if (strcmp(AT[i].name, targetArray) == 0) {
            if (AT[i].dim == 1) {
                //Generate Code for 1D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", sourceArray, sourceArray);
                sprintf(expandedLine + strlen(expandedLine), "        %s[i] = %s[i];\n", targetArray, sourceArray);
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            } else {
                //Generate Code for 2D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", sourceArray, sourceArray);
                sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < (int)(sizeof(%s[0])/sizeof(%s[0][0])); j++) {\n", sourceArray, sourceArray);
                sprintf(expandedLine + strlen(expandedLine), "            %s[i][j] = %s[i][j];\n", targetArray, sourceArray);
                sprintf(expandedLine + strlen(expandedLine), "        }\n");
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }
            break;
        }
    }

    return expandedLine;
};

char* initArray() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char arrayName[10];
    char initValue[10];

    //Copy Array Attributes
    strcpy(arrayName, PT.lhs);
    strcpy(initValue, PT.rhs1);

    //Expand Line Based on Dimension
    for (int i = 0; i < arrayCount; i++) {
        if (strcmp(AT[i].name, arrayName) == 0) {
            if (AT[i].dim == 1) {
                //Generate Code for 1D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        %s[i] = %s;\n", arrayName, initValue);
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            } else {
                //Generate Code for 2D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < (int)(sizeof(%s[0])/sizeof(%s[0][0])); j++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "            %s[i][j] = %s;\n", arrayName, initValue);
                sprintf(expandedLine + strlen(expandedLine), "        }\n");
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }
            break;
        }
    }

    return expandedLine;
};

char* printArray() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char arrayName[10];

    //Copy Array Attributes
    strcpy(arrayName, PT.lhs);

    //Expand Line Based on Dimension
    for (int i = 0; i < arrayCount; i++) {
        if (strcmp(AT[i].name, arrayName) == 0) {
            if (AT[i].dim == 1) {
                //Generate Code for 1D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        printf(\"%%d \", %s[i]);\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
                sprintf(expandedLine + strlen(expandedLine), "    printf(\"\\n\");\n");
            } else {
                //Generate Code for 2D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < (int)(sizeof(%s[0])/sizeof(%s[0][0])); j++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "            printf(\"%%d \", %s[i][j]);\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        }\n");
                sprintf(expandedLine + strlen(expandedLine), "        printf(\"\\n\");\n");
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }

            break;
        }
    }

    return expandedLine;
};

char* dotProduct() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char array1[10];
    char array2[10];

    //Copy Array Attributes
    strcpy(array1, PT.rhs1);
    strcpy(array2, PT.rhs2);

    //Generate Code for Dot Product
    sprintf(expandedLine + strlen(expandedLine), "    P_dot = 0;\n");
    sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", array1, array1);
    sprintf(expandedLine + strlen(expandedLine), "        P_dot += %s[i] * %s[i];\n", array1, array2);
    sprintf(expandedLine + strlen(expandedLine), "    }\n");

    return expandedLine;
};

char* arrayAddition() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char resultArray[10];
    char array1[10];
    char array2[10];

    //Copy Array Attributes
    strcpy(resultArray, PT.lhs);
    strcpy(array1, PT.rhs1);
    strcpy(array2, PT.rhs2);

    //Expand Line Based on Dimension
    for (int i = 0; i < arrayCount; i++) {
        if (strcmp(AT[i].name, resultArray) == 0) {
            if (AT[i].dim == 1) {
                //Generate Code for 1D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", array1, array1);
                sprintf(expandedLine + strlen(expandedLine), "        %s[i] = %s[i] + %s[i];\n", resultArray, array1, array2);
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            } else {
                //Generate Code for 2D
                sprintf(expandedLine, "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", array1, array1);
                sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < (int)(sizeof(%s[0])/sizeof(%s[0][0])); j++) {\n", array1, array1);
                sprintf(expandedLine + strlen(expandedLine), "            %s[i][j] = %s[i][j] + %s[i][j];\n", resultArray, array1, array2);
                sprintf(expandedLine + strlen(expandedLine), "        }\n");
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }

            break;
        }
    }

    return expandedLine;
};

char* arrayMultiplication() {

    static char expandedLine[500];
    strcpy(expandedLine, "");

    char resultMatrix[10];
    char matrix1[10];
    char matrix2[10];

    //Copy Array Attributes
    strcpy(resultMatrix, PT.lhs);
    strcpy(matrix1, PT.rhs1);
    strcpy(matrix2, PT.rhs2);

    //Get Dimensions
    int rowsA = 0, colsA = 0, rowsB = 0, colsB = 0;
    for (int i = 0; i < arrayCount; i++) {
        if (strcmp(AT[i].name, matrix1) == 0) {
            rowsA = atoi(AT[i].size1);
            colsA = atoi(AT[i].size2);
        }
        if (strcmp(AT[i].name, matrix2) == 0) {
            rowsB = atoi(AT[i].size1);
            colsB = atoi(AT[i].size2);
        }
    }

    // Generate code for matrix multiplication
    sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < %d; i++) {\n", rowsA);
    sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < %d; j++) {\n", colsB);
    sprintf(expandedLine + strlen(expandedLine), "            %s[i][j] = 0;\n", resultMatrix);
    sprintf(expandedLine + strlen(expandedLine), "            for (int k = 0; k < %d; k++) {\n", colsA);
    sprintf(expandedLine + strlen(expandedLine), "                %s[i][j] += %s[i][k] * %s[k][j];\n", resultMatrix, matrix1, matrix2);
    sprintf(expandedLine + strlen(expandedLine), "            }\n");
    sprintf(expandedLine + strlen(expandedLine), "        }\n");
    sprintf(expandedLine + strlen(expandedLine), "    }\n");

    return expandedLine;

};

char* arraySum() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char arrayName[10];

    //Copy Array Attributes
    strcpy(arrayName, PT.lhs);


    sprintf(expandedLine, "    P_sum = 0;\n");

    for (int i = 0; i < arrayCount; i++) {
        if (strcmp(AT[i].name, arrayName) == 0) {
            if (AT[i].dim == 1) {
                //Generate Code for 1D
                sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        P_sum += %s[i];\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            } else if (AT[i].dim == 2) {
                //Generate Code for 2D
                sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < (int)(sizeof(%s)/sizeof(%s[0])); j++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "            P_sum += %s[i][j];\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        }\n");
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }

            break;
        }
    }

    return expandedLine;
};

char* arrayAverage() {

    static char expandedLine[300];
    strcpy(expandedLine, "");

    char arrayName[10];

    //Copy Array Attributes
    strcpy(arrayName, PT.lhs);

    sprintf(expandedLine, "    P_aver = 0;\n");
    sprintf(expandedLine + strlen(expandedLine), "    int total_elements%s = 0;\n", arrayName);

    for (int i = 0; i < arrayCount; i++) {
        if (strcmp(AT[i].name, arrayName) == 0) {
            if (AT[i].dim == 1) {
                //Generate Code for 1D
                sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        P_aver += %s[i];\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        total_elements%s++;\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            } else if (AT[i].dim == 2) {
                //Generate Code for 2D
                sprintf(expandedLine + strlen(expandedLine), "    for (int i = 0; i < (int)(sizeof(%s)/sizeof(%s[0])); i++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        for (int j = 0; j < (int)(sizeof(%s)/sizeof(%s[0])); j++) {\n", arrayName, arrayName);
                sprintf(expandedLine + strlen(expandedLine), "            P_aver += %s[i][j];\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "            total_elements%s++;\n", arrayName);
                sprintf(expandedLine + strlen(expandedLine), "        }\n");
                sprintf(expandedLine + strlen(expandedLine), "    }\n");
            }

            break;

        }
    }

    //Calculate Average and Assign
    sprintf(expandedLine + strlen(expandedLine), "    if (total_elements%s > 0) {\n", arrayName);
    sprintf(expandedLine + strlen(expandedLine), "        P_aver /= total_elements%s;\n", arrayName);
    sprintf(expandedLine + strlen(expandedLine), "    }\n");

    return expandedLine;
};

int main(int argc, char *argv[]) {
    // Open Input File
    FILE *inputFile = fopen(argv[1], "r");

    // Open Output File
    FILE *outputFile = fopen("expanded.c", "w");

    char line[300];
    while (fgets(line, sizeof(line), inputFile)) {
        // Check for "@"
        int index = 0;
        
        while(line[index] == ' '){
            index++;
        }

        if (line[index] == '@') {
            // Parse Line
            parser(line);

            char *expandedLine;

            // Call Needed Function
            if (strcmp(PT.oper, "@int") == 0) {
                expandedLine = declareArray();
            } else if (strcmp(PT.oper, "@read") == 0) {
                expandedLine = readArray();
            } else if (strcmp(PT.oper, "@copy") == 0) {
                expandedLine = copyArray();
            } else if (strcmp(PT.oper, "@init") == 0) {
                expandedLine = initArray();
            } else if (strcmp(PT.oper, "@print") == 0) {
                expandedLine = printArray();
            } else if (strcmp(PT.oper, "@dotp") == 0) {
                expandedLine = dotProduct();
            } else if (strcmp(PT.oper, "@add") == 0) {
                expandedLine = arrayAddition();
            } else if (strcmp(PT.oper, "@mmult") == 0) {
                expandedLine = arrayMultiplication();
            } else if (strcmp(PT.oper, "@sum") == 0) {
                expandedLine = arraySum();
            } else if (strcmp(PT.oper, "@aver") == 0) {
                expandedLine = arrayAverage();
            }

            fprintf(outputFile, "%s", expandedLine);
        } else {
            // Write Line if No "@"
            fprintf(outputFile, "%s", line);
        }
    }

    // Close Files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}