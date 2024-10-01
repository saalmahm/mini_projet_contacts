#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

struct Contact {
    int id;
    char name[20];
    char phone[15];
    char email[30];
};
struct Contact table[100];
int cpt = 0;

void ajouter_contacts_defaut() {
    const char noms[10][20] = {
        "salma", "manal", "karim", "souhail", "ayoub",
        "bilal", "ahmad", "naima", "amal", "kamal"
    };
    const char telephones[10][15] = {
        "0673897654", "0987654321", "0763437907",
        "0754332422", "0976543222", "0673523263",
        "5678901234", "0654343790", "0763438903", "8901234567"
    };
    const char emails[10][30] = {
        "salma@gmail.com", "amal@gmail.com", "manal@gmail.com",
        "ahlam@gmail.com", "akram@gmail.com", "mouad@gmail.com",
        "oumaima@gmail.com", "hanane@gmail.com", "hamza@gmail.com",
        "hamza@gmail.com"
    };
    for (int i = 0; i < 10 && cpt < 100; i++) {
        table[cpt].id = cpt + 1;
        strcpy(table[cpt].name, noms[i]);
        strcpy(table[cpt].phone, telephones[i]);
        strcpy(table[cpt].email, emails[i]);
        cpt++;
    }

    printf(GREEN "deja 10 contact sont ajouter par default.\n" RESET);
}

void ajout_contact() {
    if (cpt >= 100) {
        printf(RED "le Carnet est plein!!\n" RESET);
        return;
    }

    struct Contact newContact;
    newContact.id = cpt + 1;
    printf("entrer le nom: ");
    scanf("%s", newContact.name);

    printf("entrer telephone: ");
    scanf("%s", newContact.phone);

    for (int i = 0; i < cpt; i++) {
        if (strcmp(table[i].phone, newContact.phone) == 0) {
            printf(RED "ce numero est deja existe!!\n" RESET);
            return;
        }
    }

    printf("entrer l\'email: ");
    scanf("%s", newContact.email);

    for (int i = 0; i < cpt; i++) {
        if (strcmp(table[i].email, newContact.email) == 0) {
            printf(RED "l\'email que tu as saisit deja existe !!\n" RESET);
            return;
        }
    }

    table[cpt++] = newContact;
    printf(GREEN "bien ajouté.\n" RESET);
}
void afficher_contacts() {
    if (cpt == 0) {
        printf(RED "pas de contact!!\n" RESET);
        return;
    }

    printf("+-----+----------------+-------------+--------------------------+\n");
    printf("| ID  |      Nom       |  Téléphone  |           Email          |\n");
    printf("+-----+----------------+-------------+--------------------------+\n");

    for (int i = 0; i < cpt; i++) {
        printf("| %3d | %-14s | %-11s | %-24s |\n",
               table[i].id, table[i].name, table[i].phone, table[i].email);
    }

    printf("+-----+----------------+-------------+--------------------------+\n");
}
void rechercher_contact() {
    char search[15];
    printf("entrer le telephone du contact a chercher: ");
    scanf("%s", search);

    for (int i = 0; i < cpt; i++) {
        if (strcmp(table[i].phone, search) == 0) {
            printf(BLUE "ID: %d, Nom: %s, Téléphone: %s, Email: %s\n" RESET,
                   table[i].id, table[i].name, table[i].phone, table[i].email);
            return;
        }
    }
    printf(RED "Contact non trouvé.\n" RESET);
}

void modifier_contact() {
    char search[15];
    printf("Pour modifier les infos de contact, merci de saisir son numéro de téléphone: ");
    scanf("%s", search);

    for (int i = 0; i < cpt; i++) {
        if (strcmp(table[i].phone, search) == 0) {
            printf("Nouveau nom: ");
            char newName[20];
            scanf("%s", newName);
            strcpy(table[i].name, newName);

            printf("Nouveau téléphone: ");
            char newPhone[15];
            scanf("%s", newPhone);

            for (int j = 0; j < cpt; j++) {
                if (strcmp(table[j].phone, newPhone) == 0 && j != i) {
                    printf(RED "le numero est deja utilisé!!\n" RESET);
                    return;
                }
            }
            strcpy(table[i].phone, newPhone);

            printf("Nouveau email: ");
            char newEmail[30];
            scanf("%s", newEmail);
            strcpy(table[i].email, newEmail);
            printf(GREEN "Contact bien modifié.\n" RESET);
            return;
        }
    }
    printf(RED "Contact non trouvé.\n" RESET);
}

int main() {
    ajouter_contacts_defaut();
    int choix;
    do {
        printf(YELLOW "1. Ajouter un contact\n" RESET);
        printf(YELLOW "2. Afficher les contacts\n" RESET);
        printf(YELLOW "3. Rechercher un contact\n" RESET);
        printf(YELLOW "4. Modifier un contact\n" RESET);
        printf(YELLOW "5. Quitter\n" RESET);
        printf("Choisissez une option: " RESET);
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajout_contact();
                break;
            case 2:
                afficher_contacts();
                break;
            case 3:
                rechercher_contact();
                break;
            case 4:
                modifier_contact();
                break;
            case 5:
                printf(GREEN "Au revoir!\n" RESET);
                break;
            default:
                printf(RED "Option invalide.\n" RESET);
        }

    } while (choix != 5);

    return 0;
}
