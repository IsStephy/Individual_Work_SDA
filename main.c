#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.c"

#define MAX_NAME_LENGTH 50
#define MAX_SURNAME_LENGTH 50
#define MAX_PAYMENTS 30
#define MAX_KNP_TYPES 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    float val;
} Knp;

struct Person {
    char name[MAX_NAME_LENGTH];
    char surname[MAX_SURNAME_LENGTH];
    char dateOfBirth[11];
    int code;
    char post[MAX_NAME_LENGTH];
    float before;
    float after;
    int stare;
    float T;
    float payments[MAX_PAYMENTS];
    int numPayments;
    Knp knp[MAX_KNP_TYPES];
    float numKnp;
    float Vav;
    float P;
};

void print(struct Person x) {
    printf("Name - %s\n", x.name); 
    printf("Surname - %s\n", x.surname); 
    printf("Date of birth - %s\n", x.dateOfBirth); 
    printf("Fee taxes paid:\n"); 
    for (int j = 0; j < x.numPayments; j++) {
        printf("%.2f\n", x.payments[j]);
    }
    printf("\nTotal worked: %.0f\n", x.T); 
    if (x.stare == 1) {
        printf("Severe degree of disability\n"); 
        printf("Pension  = %.2f\n", x.P);
    } else if (x.stare == 2) {
        printf("Accentuated degree of disability\n"); 
        printf("Pension  = %.2f\n", x.P);
    } else if (x.stare == 3) {
        printf("Low degree of disability\n");
        printf("Pension  = %.2f\n", x.P);
    } else if (x.stare == 4){
        printf("survivorship pension\n");
        printf("Pension  = %.2f\n", x.P);
    }else{
        printf("Age Pension\n");
        printf("Pension  = %.2f\n", x.P);
    }
}

int main() {
    FILE *file = fopen("info.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    struct Person people[10]; 
    int currentPersonIndex = 0;
    char line[100]; 
    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '\n') {
            continue;
        }
        char field[20];
        char value[100];
        sscanf(line, "%s %[^\n]", field, value);
        if (strcmp(field, "Name:") == 0) {
            sscanf(value, "%s", people[currentPersonIndex].name);
        } else if (strcmp(field, "Surname:") == 0) {
            sscanf(value, "%s", people[currentPersonIndex].surname);
        } else if (strcmp(field, "Date_of_Birth:") == 0) {
            sscanf(value, "%s", people[currentPersonIndex].dateOfBirth);
        } else if (strcmp(field, "Code:") == 0) {
            sscanf(value, "%d", &people[currentPersonIndex].code);
        } else if (strcmp(field, "Post:") == 0) {
            sscanf(value, "%s", people[currentPersonIndex].post);
        } else if (strcmp(field, "Stare:") == 0) {
            sscanf(value, "%d", &people[currentPersonIndex].stare);
        } else if (strcmp(field, "Before:") == 0) {
            sscanf(value, "%f", &people[currentPersonIndex].before);
        } else if (strcmp(field, "After:") == 0) {
            sscanf(value, "%f", &people[currentPersonIndex].after);
        } else if (strcmp(field, "Payments:") == 0) {
            int i = 0;
            while (fgets(line, sizeof(line), file) != NULL && line[0] != '\n') {
                sscanf(line, "Year %*d: %f", &people[currentPersonIndex].payments[i]);
                i++;
            }
            people[currentPersonIndex].numPayments = i;
            people[currentPersonIndex].T = people[currentPersonIndex].before + people[currentPersonIndex].after;
            currentPersonIndex++;
        }
    }

    
    fclose(file);
    
    file = fopen("funct.txt", "r"); 
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Knp knp[MAX_KNP_TYPES];
    int knp_index = 0;
    while (fscanf(file, "%s %f", knp[knp_index].name, &knp[knp_index].val) == 2) {
        knp_index++;
    }

    fclose(file);

    for (int i = 0; i < currentPersonIndex; i++) {
        for (int j = 0; j < knp_index; j++) {
            if (strcmp(people[i].post, knp[j].name) == 0) {
                people[i].numKnp = knp[j].val;
                break;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < currentPersonIndex;i++){
        for (int j = 0;j< people[i].numPayments;j++){
            sum += people[i].payments[j];
        }
        people[i].Vav = sum / (people[i].numPayments*12);
        sum = 0;
    }
    char name[50];
    char surname[50];
    float P1,P2;
    int save;
    scanf("%s \n",name);
    scanf("%s \n",surname);
    for (int i = 0; i< currentPersonIndex;i++){
        if (strcmp(people[i].name,name)==0 && strcmp(people[i].surname,surname) == 0){
            if (people[i].stare == 0){
                if (people[i].T < 5 && people[i].T > 0){
                    people[i].P = fara_stagiu_ori_mai_mic_de_5_ani(people[i].numKnp,people[i].T);
                }else if (people[i].T > 5){
                    people[i].P = stagiu_complet(people[i].T,people[i].Vav, people[i].numKnp);
                }else {
                    people[i].P = 2778;
                }
            }else if (people[i].stare == 1){
                if (people[i].T < 5 && people[i].T > 0){
                    P1 = fara_stagiu_ori_mai_mic_de_5_ani(people[i].numKnp,people[i].T);
                    P2 = diz_grad_1(people[i].Vav,people[i].T);
                    if (P1> P2){
                        people[i].P = P1;
                    }else{people[i].P = P2;}
                }else if (people[i].T > 5){
                    P1 = stagiu_complet(people[i].T,people[i].Vav, people[i].numKnp);
                    P2 = diz_grad_1(people[i].Vav,people[i].T);
                    if (P1> P2){
                        people[i].P = P1;
                    }else{people[i].P = P2;}
                }else{
                    people[i].P = diz_grad_1(people[i].Vav,people[i].T);
                }
            }else if (people[i].stare == 2){
                if (people[i].T < 5 && people[i].T > 0){
                    P1 = fara_stagiu_ori_mai_mic_de_5_ani(people[i].numKnp,people[i].T);
                    P2 = diz_grad_2(people[i].Vav,people[i].T);
                    if (P1 > P2){
                        people[i].P = P1;
                    }else{people[i].P = P2;}
                }else if (people[i].T > 5){
                    P1 = stagiu_complet(people[i].T,people[i].Vav, people[i].numKnp);
                    P2 = diz_grad_2(people[i].Vav,people[i].T);
                    if (P1 > P2){
                        people[i].P = P1;
                    }else{people[i].P = P2;}
                }else{
                    people[i].P = diz_grad_2(people[i].Vav,people[i].T); 
                }
            }else if (people[i].stare == 3){
                if (people[i].T < 5 && people[i].T > 0){
                    P1 = fara_stagiu_ori_mai_mic_de_5_ani(people[i].numKnp,people[i].T);
                    P2 = diz_grad_3(people[i].Vav,people[i].T);
                    if (P1 > P2){
                        people[i].P = P1;
                    }else{people[i].P = P2;}
                }else if (people[i].T > 5){
                    P1 = stagiu_complet(people[i].T,people[i].Vav, people[i].numKnp);
                    P2 = diz_grad_3(people[i].Vav,people[i].T);
                    if (P1 > P2){
                        people[i].P = P1;
                    }else{people[i].P = P2;}
                }else{
                    people[i].P = diz_grad_3(people[i].Vav,people[i].T);
                }
            }else if (people[i].stare == 4){
                people[i].P = urmas(people[i].Vav,people[i].T);
            }
            save = i;
            break;
        }
    }
    print(people[save]);
    return 0;
}
