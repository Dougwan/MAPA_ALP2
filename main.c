#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct  
{
    int id;
    char date[15];
    char name[100];
    char vaccine[30];
    char document[15];
    char lot_number[30];
} Vaccination;

int lastId = 0;

int menu();
int select_menu_option();
int register_vacinnation();

bool save_data(char *filename, Vaccination data, int total);
Vaccination *read_data(char *filename, int *total);

void init_system();
void read_vaccinations();


int main(void) {
    setlocale(LC_ALL, "Portuguese");

    init_system();    

    return EXIT_SUCCESS;
}

int select_menu_option() {
    char buf[sizeof(int)];

    printf("Selecione uma opção: ");
    fgets(buf, sizeof(buf), stdin);

    return  strtol(buf, NULL, 0);
}

int menu() {
    printf("============== Sistema de controle de vacinação =============\n");
    printf("==                                                         ==\n");
    printf("== 1) Cadastrar Vacina                                     ==\n");
    printf("== 2) Listar Aplicações                                    ==\n");
    printf("== 3) Consultar CPF                                        ==\n");
    printf("== 4) Sair                                                 ==\n");
    printf("==                                                         ==\n");
    printf("=============================================================\n\n");

    return select_menu_option();
}

void init_system() {
    system("clear");

    int seletecOption = menu();
    system("clear");


    switch (seletecOption)
    {
        case 1:
            register_vacinnation();
            system("clear");
            init_system();

            break;
        case 2:
            read_vaccinations();
           
            break;
        case 3:
            /* code */
            break;
        case 4:
            system("clear");
            printf("Saindo do sistema. Obrigado pela preferência!");
            sleep(1);

            break;
        default:
            system("read -p 'Opção não encontrada, presione enter para continuar...' var"); 
            sleep(1);
            system("clear");
            init_system();
            
            break;
    }
}

void read_vaccinations() {
    int total = 2;
    Vaccination *vaccinations;

    vaccinations = read_data("vaccinations.bin", &total);

    if(vaccinations == NULL) {
        system("read -p 'Erro ao inesperado ao tentar ler registro de vacinas, presione enter para continuar...' var"); 
        sleep(1);
        system("clear");
        init_system();
    }

    system("clear");

    for(int i = 0; i < total; i++) {
        printf("======================= Vacinação Nº %d =======================\n\n", i + 1);
            
        printf("COD: ....................: %d\n\n", vaccinations[i].id);

        printf("Nome: ...................: %s\n", vaccinations[i].name);

        printf("CPF (Sem dígitos): ......: %s\n", vaccinations[i].document);

        printf("Data (DD/MM/AAAA): ......: %s\n", vaccinations[i].date);

        printf("Vacina: .................: %s\n", vaccinations[i].vaccine);

        printf("Lote: ...................: %s\n", vaccinations[i].lot_number);

        printf("\n");
    }

    system("read -p '\n\nPresione enter para continuar...' var"); 
}

int register_vacinnation() {

    Vaccination vaccination;

    char name[100];
    char date[15], document[15];
    char vaccine[30], lot_number[30];

    system("clear");

  
    printf("==================== Cadastrar Vacinação Nº ====================\n\n");
            
    printf("Nome: ...................: ");
    fgets(name, sizeof name, stdin);
    strcpy(vaccination.name, name);

    printf("CPF (Sem dígitos): ......: ");
    fgets(document, sizeof document, stdin);
    strcpy(vaccination.document, document);


    printf("Data (DD/MM/AAAA): ......: ");
    fgets(date, sizeof date, stdin);
    strcpy(vaccination.date, date);

    printf("Vacina: .................: ");
    fgets(vaccine, sizeof vaccine, stdin);
    strcpy(vaccination.vaccine, vaccine);


    printf("Lote: ...................: ");
    fgets(lot_number, sizeof lot_number, stdin);
    strcpy(vaccination.lot_number, lot_number);

    vaccination.id = lastId + 1;
    lastId += 1;

    printf("\n\n================================================================\n\n");

    system("clear");

    if(save_data("vaccinations.bin", vaccination, 1)) {
        system("read -p 'Vacina registrada com sucesso, presione enter para continuar...' var");
        init_system();
       
    }else {
        system("read -p 'Erro ao registrar vacina, presione enter para continuar...' var");
        init_system();
    }

    return 0;
}

bool save_data(char *filename, Vaccination data, int total) {
    FILE *file;

    file = fopen(filename, "ab");

    if(file == NULL) return false;

    if (fwrite(&total, sizeof(int), 1, file) != 1) return false;

    if (fwrite(&data, sizeof(Vaccination), total, file) != total) return false;

    if (fwrite("\n", sizeof(char), 1, file) != 1) return false;


    if (fclose(file) == EOF) return false;

    return true;
}

Vaccination *read_data(char *filename, int *total) {
    FILE *file;

    file = fopen(filename, "rb");

    if(file == NULL) return false;

    // if(fread(total, sizeof(int), *total, file) != *total) return NULL;

    Vaccination *data = malloc(sizeof(Vaccination) * *total);

    if(fread(data, sizeof(Vaccination), *total, file) != *total) {
        free(data);
        return NULL;
    }

    if(fclose(file) == EOF) {
        free(data);
        return NULL;
    }

    return data;
}