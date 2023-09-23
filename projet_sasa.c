#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// /initialisation Max_value
#define MAX_Tache 100
#define MAX_collaborateur 100

//   Structure Tache
typedef struct
{

    int day;
    int month;
    int year;
} Date;
typedef struct
{
    int idC;
    char nom[30];
    char prenom[30];
    char email[30];
} Collaborateur;
typedef struct
{
    int id;
    char Title[50];
    char description[50];
    Date creation_date;
    Date deadline;
    char status[30];
    Collaborateur collaborateurs[MAX_collaborateur];
} Tache;

// /initialisation Max_value
Tache Taches[MAX_Tache];

int count = 0;
int countC = 0;

//   Function prototype

void Ajoute();

void Afficher();

void Modifier();

void Supprimer();

void Recherche();

void Statistique();
void collaborateur();
void createFile();

// main Function
int main()
{
    int choice;

    do
    {
        printf("+---------------------------------------------------+\n");
        printf("|                 Task Management Menu              |\n");
        printf("+---------------------------------------------------+\n");
        printf("|  Option |                Description               |\n");
        printf("+---------------------------------------------------+\n");
        printf("|    1    | Ajouter une nouvelle tache              |\n");
        printf("|    2    | Afficher la liste de toutes les taches  |\n");
        printf("|    3    | Modifier une tache                     |\n");
        printf("|    4    | Supprimer une tache par identifiant    |\n");
        printf("|    5    | Rechercher les Taches                  |\n");
        printf("|    6    | Statistiques                           |\n");
        printf("|    7    | Collaborateur                          |\n");
        printf("|    8    | Sauvgarde au file                         |\n");
        printf("|    0    | Quit                                   |\n");
        printf("+---------------------------------------------------+\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Ajoute();
            break;
        case 2:
            Afficher();
            break;
        case 3:
            Modifier();
            break;
        case 4:
            Supprimer();
            break;
        case 5:
            Recherche();
            break;
        case 6:
            Statistique();
            break;
        case 7:
            collaborateur();
            break;
        case 8:
            createFile();
            break;
        case 0:
            exit(0);
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    } while (choice != 0);

    return 0;
}
// Status
char *statusTask()
{
    int choice;
    printf("\n1.\tto do:");
    printf("\n2.\tdoing");
    printf("\n3.\tdone:");
    printf("\n entrer your choice:");

    scanf("\n%d", &choice);

    switch (choice)
    {
    case 1:
        return "to do";
    case 2:
        return "doing";
    case 3:
        return "done";
    default:
        printf("This choice doesn't exist in the menu\n");
        return "Null";
    }
}
// calcule deadline
int calcDeadline(int day, int month, int year)
{
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    int currentYear = date.tm_year + 1900;
    int currentday = date.tm_mday;
    int currentmonth = date.tm_mon + 1;

    if (year < currentYear || (year == currentYear && month < currentmonth) ||
        (year == currentYear && month == currentmonth && day < currentday))
    {
        printf("Deadline date cannot be in the past.\n");
        return 0;
    }

    int days = (year - currentYear) * 365 + (month - currentmonth) * 30 + (day - currentday);
    return days;
}

// creation
void Ajouter_struct(int num)
{
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    int currentDAys = 0, days = 0;
    int currentYear = date.tm_year + 1900;
    int currentday = date.tm_mday;
    int currentmonth = date.tm_mon + 1;
    for (int i = count; i < count + num; i++)
    {
        if (count + num > MAX_Tache)
        {
            printf("Exceeded the maximum number of Taches (%d).\n", MAX_Tache);
            return;
        }
        Taches[i].id = rand() % 100 + 1;
        printf("\nEnter the Title of the Tache: ");
        scanf(" %[^\n]", Taches[i].Title);
        Taches[i].Title[0] = toupper(Taches[i].Title[0]);
        printf("Enter the description of the Tache: ");
        scanf(" %[^\n]", Taches[i].description);
        strcpy(Taches[i].status, statusTask());

        int deadlineValid = 0;

        do
        {
            printf("Input a deadline (dd/mm/yyyy):\n");
            scanf("%d/%d/%d", &Taches[i].deadline.day, &Taches[i].deadline.month, &Taches[i].deadline.year);

            if (calcDeadline(Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year) > 0)
            {
                deadlineValid = 1;
            }
            else
            {
                printf("Invalid deadline date. Please enter a future date.\n");
            }
        } while (!deadlineValid);
        Taches[i].creation_date.day = currentday;
        Taches[i].creation_date.month = currentmonth;
        Taches[i].creation_date.year = currentYear;
        // fflush(stdin);
    }

    count += num;
}
void Ajoute()
{

    int number, choice;

    printf("\nEnter 1 to add multiple tasks or 2 to add a single task: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\nEnter the number of tasks you want to enter: ");
        scanf("%d", &number);

        Ajouter_struct(number);
    }
    else if (choice == 2)

    {
        Ajouter_struct(1);
        return;
    }
    else
    {

        printf("This choice doesn't exist in the menu\n");
        return;
    }
}

// Trier par ordre alphabÃ©tique

void Order()
{
    Tache Temp;

    int lenght = count;

    for (int i = 0; i < lenght - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < lenght; j++)
        {
            if (strcmp(Taches[min].Title[0] , Taches[j].Title)==0)
            {
                min = j;
            }
        }
        Temp = Taches[min];
        Taches[min] = Taches[i];
        Taches[i] = Temp;
    }

    printf("| %-4s | %-20s | %-20s | %-12s | %-12s | %-10s | %-10s |\n", "ID", "Title", "Description", "Creation Date", "Deadline", "Status");
    printf("+------+----------------------+----------------------+--------------+--------------+------------+\n");

    for (int i = 0; i < count; i++)
    {
        printf("| %-4d | %-20s | %-20s | %02d/%02d/%04d   | %02d/%02d/%04d   | %-10s   |%-10d  |\n",
               Taches[i].id, Taches[i].Title, Taches[i].description,
               Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year,
               Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year,
               Taches[i].status);
    }

    printf("+------+----------------------+----------------------+--------------+--------------+------------+\n");
}

// les tÃ¢ches par deadline
void Deadline()
{
    Tache Temp;

    int lenght = count;

    for (int i = 0; i < lenght - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < lenght; j++)
        {
            if (calcDeadline(Taches[min].deadline.day, Taches[min].deadline.month, Taches[min].deadline.year) > calcDeadline(Taches[j].deadline.day, Taches[j].deadline.month, Taches[j].deadline.year))
            {
                min = j;
            }
        }
        Temp = Taches[min];
        Taches[min] = Taches[i];
        Taches[i] = Temp;
    }
    printf("| %-4s | %-20s | %-20s | %-12s | %-12s | %-10s |\n", "ID", "Title", "Description", "Creation Date", "Deadline", "Status");
    printf("+------+----------------------+----------------------+--------------+--------------+------------+\n");

    for (int i = 0; i < count; i++)
    {
        printf("| %-4d | %-20s | %-20s | %02d/%02d/%04d   | %02d/%02d/%04d   | %-10s   |\n",
               Taches[i].id, Taches[i].Title, Taches[i].description,
               Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year,
               Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year,
               Taches[i].status);
    }

    printf("+------+----------------------+----------------------+--------------+--------------+------------+\n");
}
// Afficher les tÃ¢ches dont le deadline est dans 3 jours ou moins.

void Date_Deadline()
{
    Tache Temp;

    int lenght = count;

    for (int i = 0; i < lenght; i++)
    {
        if (calcDeadline(Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year) < 3)
        {
            printf("| %-4s | %-20s | %-20s | %-12s | %-12s | %-10s |\n", "ID", "Title", "Description", "Creation Date", "Deadline", "Status");
            printf("+------+----------------------+----------------------+--------------+--------------+------------+\n");

            for (int i = 0; i < count; i++)
            {
                printf("| %-4d | %-20s | %-20s | %02d/%02d/%04d   | %02d/%02d/%04d   | %-10s   |\n",
                       Taches[i].id, Taches[i].Title, Taches[i].description,
                       Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year,
                       Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year,
                       Taches[i].status);
            }

            printf("+------+----------------------+----------------------+--------------+--------------+------------+\n");
        }
    }
}
// Afficher
void Afficher()
{
    int ch;

    while (1)
    {
        printf("\n-------------------------------------------------------");
        printf("\n| Option |                  Description                |");
        printf("\n-------------------------------------------------------");
        printf("\n|   1    | Trier les taches par ordre alphabetique.   |");
        printf("\n|   2    | Trier les taches par deadline.             |");
        printf("\n|   3    | Afficher les taches dans 3 jours ou moins. |");
        printf("\n|   4    | Back                                       |");
        printf("\n-------------------------------------------------------");

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            Order();
            break;
        case 2:
            Deadline();
            break;
        case 3:
            Date_Deadline();
            break;
        case 4:
            return; // Return to the previous menu
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    }
}

// get the index

int get_Index(int ops)
{
    int index, id;
    char op[20];

    if (ops == 1)
    {
        strcpy(op, "update");
    }
    else if (ops == 2)
    {
        strcpy(op, "delete");
    }
    else
    {
        strcpy(op, "find");
    }
    printf("continue %s or back to main menu ? (1 for yes, 0 for no): ", op);
    int confirmation;
    scanf("%d", &confirmation);
    if (confirmation == 1)
    {

        if (count == 0)
        {
            printf("No data to %s.\n", op);
            return -1; // Return -1 to indicate an error or not found
        }

        printf("Enter the id of the tasks to %s: ", op);
        scanf("%d", &id);

        for (int i = 0; i < count; i++)
        {
            if (Taches[i].id == id)
            {
                index = i;
                return index;
            }
        }

        printf("Task with ID %d not found.\n", id);
        return main();
    }
    else
    {
        return main();
    }
}
// Modifier la description d'une tÃ¢che
void Modifier_By_Description(int index)
{

    printf("Enter the updated description of the Tache: ");
    scanf(" %[^\n]", Taches[index].description);
    printf("Tache information updated successfully.\n");

    return Modifier();
}
// Modifier le statut dâ€™une tÃ¢che:
void Modifier_By_Status(int index)
{

    printf("Enter the updated status of the Tache:\n ");
    strcpy(Taches[index].status, statusTask());
    printf("Tache information updated successfully.\n");

    return Modifier();
}
// Modifier le deadline dâ€™une tÃ¢che
void Modifier_By_DeaDline(int index)
{

    int deadlineValid = 0;

    do
    {
        printf("update a deadline (dd/mm/yyyy):\n");
        scanf("%d/%d/%d", &Taches[index].deadline.day, &Taches[index].deadline.month, &Taches[index].deadline.year);

        if (calcDeadline(Taches[index].deadline.day, Taches[index].deadline.month, Taches[index].deadline.year) > 0)
        {
            deadlineValid = 1;
        }
        else
        {
            printf("Invalid deadline date. Please enter a future date.\n");
        }
    } while (!deadlineValid);
    printf("Tache information updated successfully.\n");
    return Modifier();
}
// Modifier

void Modifier()
{
    int ch, index;
    int operation = 1;
    index = get_Index(operation);

    printf("+------------------------------------+");
    printf("\n| Modifier Menu                      |");
    printf("\n+------------------------------------+");
    printf("\n| 1. Modifier la description d'une tache |");
    printf("\n| 2. Modifier le statut d'une tache     |");
    printf("\n| 3. Modifier le deadline d'une tache   |");
    printf("\n| 0. Back                              |");
    printf("\n+------------------------------------+");

    printf("\nEnter your choice: ");
    scanf("%d", &ch);
    do
    {

        switch (ch)
        {
        case 1:
            Modifier_By_Description(index);
            break;
        case 2:
            Modifier_By_Status(index);
            break;
        case 3:
            Modifier_By_DeaDline(index);
            break;
        case 0:
            main();
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    } while (ch != 0);
}
// Supprimer
void Supprimer()
{
    int index;
    char operation = 2;
    index = get_Index(operation);

    printf("\nAre you sure you want to delete the tasks %d %s %s? (1 for yes, 0 for no): ", Taches[index].id, Taches[index].Title, Taches[index].description);
    int confirmation;
    scanf("\n%d", &confirmation);

    if (confirmation == 1)
    {

        for (int i = index; i < count - 1; i++)
        {
            Taches[i] = Taches[i + 1];
        }

        count--;
        printf("tasks deleted successfully.\n");
    }
    else
    {
        printf("Deletion canceled.\n");
        return;
    }
}

// Rechercher une tÃ¢che par son Identifiant.
void Recheche_By_Identifiant()
{
    int index;
    int operation = 3;
    index = get_Index(operation);

    for (int i = 0; i < count; i++)
    {
        if (Taches[i].id == index)
        {
            printf("| %-4s | %-20s | %-20s | %02d/%02d/%04d | %02d/%02d/%04d | %-10s |\n",
                   "ID", "Title", "Description", "Creation Date", "Deadline", "Status");

            printf("| %-4d | %-20s | %-20s | %02d/%02d/%04d | %02d/%02d/%04d | %-10s |\n",
                   Taches[i].id, Taches[i].Title, Taches[i].description,
                   Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year,
                   Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year,
                   Taches[i].status);
        }
    }

    return Recherche();
}
// Rechercher une tÃ¢che par son Titre:
void Recheche_By_Title()
{

    char title[50];
    if (count == 0)
    {
        printf("data doesn't exist.\n");
        return;
    }

    printf("Enter the title of the task to find: ");

    scanf(" %[^\n]", title);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(Taches[i].Title, title) == 0) //                 Design
        {
            printf("| %-4s | %-20s | %-20s | %02d/%02d/%04d | %02d/%02d/%04d | %-10s |\n",
                   "ID", "Title", "Description", "Creation Date", "Deadline", "Status");

            printf("| %-4d | %-20s | %-20s | %02d/%02d/%04d | %02d/%02d/%04d | %-10s |\n",
                   Taches[i].id, Taches[i].Title, Taches[i].description,
                   Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year,
                   Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year,
                   Taches[i].status);
        }
    }

    return Recherche();
}
// recherche description status deadline
void RDescription(char *value)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(Taches[i].description, value) == 0)
        {
            printf("| %-4s | %-20s | %-20s | %02d/%02d/%04d | %02d/%02d/%04d | %-10s | %-10d |\n",
                   "ID", "Title", "Description", "Creation Date", "Deadline", "Status", "Date Passed");

            printf("%s, %s, %d/%d/%d, %d, %d\n", Taches[i].Title, Taches[i].description, Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year, Taches[i].id, Taches[i].deadline);
        }
    }
}
void RStatus(char *value)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(Taches[i].status, value) == 0)
        {
            printf("| %-4s | %-20s | %-20s | %02d/%02d/%04d | %02d/%02d/%04d | %-10s | %-10d |\n",
                   "ID", "Title", "Description", "Creation Date", "Deadline", "Status", "Date Passed");

            printf("%s, %s, %d/%d/%d, %d, %d\n", Taches[i].Title, Taches[i].description, Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year, Taches[i].id, Taches[i].deadline);
        }
    }
}


// criteria_specific
void criteria_specific()
{
    char value[100];
    char key[100];
    printf("\nEnter a specific criteria: ");
    scanf(" %[^\n]", key);

    if (strcmp(key, "description") == 0)
    {
        printf("\nEnter a value for %s: ", key);
        scanf(" %[^\n]", value);
        RDescription(value);
    }
    else if (strcmp(key, "status") == 0)
    {
        printf("\nEnter a value for %s: ", key);
        scanf(" %[^\n]", value);
        RStatus(value);
    }  
    else
    {
        printf("%s doesn't exist\n", key);
    }
}
// REcherche
void Recherche()
{
    int ch;

    printf("+-------------------------------------------+");
    printf("\n| Recherche Menu                            |");
    printf("\n+-------------------------------------------+");
    printf("\n| 1. Rechercher une tache par son Identifiant  |");
    printf("\n| 2. Rechercher une tache par son Titre        |");
    printf("\n| 3. Rechercher par critere specifique (Autre) |");
    printf("\n| 0. Back                                     |");
    printf("\n+-------------------------------------------+");

    printf("\nEnter your choice: ");
    scanf("%d", &ch);
    do
    {

        switch (ch)
        {
        case 1:
            Recheche_By_Identifiant();
            break;
        case 2:
            Recheche_By_Title();
            break;
        case 3:
            criteria_specific();
            break;
        case 0:
            main();
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    } while (ch != 0);
}

// Afficher le nombre total des tÃ¢ches:
void Total_task()
{
    printf("le nombre total des tÃ¢ches: %d", count);
}
// Afficher le nombre de tÃ¢ches complÃ¨tes et incomplÃ¨tes
void complete()
{
    int cptNf = 0, cptf = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(Taches[i].status, "to do") == 0 || strcmp(Taches[i].status, "doing") == 0)
        {
            cptNf++;
        }
        else
        {
            cptf++;
        }
    }

    printf("\nle nombre de taches completes : %d ", cptf);
    printf("\nle nombre de taches  incompletes: %d ", cptNf);
}
// Afficher le nombre de jours restants jusqu'au dÃ©lai de chaque tÃ¢che
void Rest_Date()
{
    for (int i = 0; i < count; i++)
    {
        printf("%d, %s, %s , jours restants: %d\n", Taches[i].id, Taches[i].Title, Taches[i].description, Taches[i].deadline);
    }
}
// Statistique
void Statistique()
{

    int ch;
    while (1)
    {

        printf("+----------------------------------------------+");
        printf("\n| Statistique Menu                             |");
        printf("\n+----------------------------------------------+");
        printf("\n| 1. Afficher le nombre total des taches        |");
        printf("\n| 2. Afficher le nombre de taches completes et incompletes |");
        printf("\n| 3. Afficher le nombre de jours restants jusqu'au delai de chaque tache |");
        printf("\n| 0. Back                                        |");
        printf("\n+----------------------------------------------+");

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            Total_task();
            break;
        case 2:
            complete();
            break;
        case 3:
            Rest_Date();
            break;
        case 0:
            return;
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    }
}

// Ajouter un collaborateur
void ajouter_collaborateur(Tache *tache)
{

    if (count == 0)
    {
        printf("no tasks in data.\n");
        return;
    }

    if (countC > MAX_Tache)
    {
        printf("Exceeded the maximum number of collaborateur (%d).\n", MAX_Tache);
        return;
    }

    Collaborateur addCollaborateur;

    addCollaborateur.idC = rand() % 100 + 1;
    printf("\nEnter first name of the collaborateur: ");
    scanf(" %[^\n]", addCollaborateur.nom);
    printf("Enter last name of the collaborateur: ");
    scanf(" %[^\n]", addCollaborateur.prenom);
    printf("Enter email of the collaborateur: ");
    scanf(" %[^\n]", addCollaborateur.email);
    tache->collaborateurs[countC] = addCollaborateur;

    countC++;
}
// SÃ©lectionner le Collaborateur de la TÃ¢che FinalisÃ©e
void SelectTaskPerformer()
{
    if (count == 0)
    {
        printf("No tasks available.\n");
        return;
    }

    if (countC == 0)
    {
        printf("No collaborators available for this task.\n");
        return;
    }

    for (int j = 0; j < count; j++)
    {

        if (strcmp(Taches[j].status, "done") == 0)
        {
            for (int i = 0; i < countC; i++)
            {
                printf("\nCollaborateur ID: %d\n", Taches[j].collaborateurs[i].idC);
                printf("\nTache ID: %d\n", Taches[j].id);
                printf("Nom: %s\n", Taches[j].collaborateurs[i].nom);
                printf("Prenom: %s\n", Taches[j].collaborateurs[i].prenom);
                printf("Email: %s\n", Taches[j].collaborateurs[i].email);
                printf("----------------------------\n");
            }
        }
        else
        {
            printf("no task has been finish yet");
        }
    }
}

// collaborateur
void collaborateur()
{

    int ch;

    while (1)
    {
        printf("+-------------------------------------------+");
        printf("\n| Collaborateur Menu                        |");
        printf("\n+-------------------------------------------+");
        printf("\n| 1. Ajouter collaborateur                  |");
        printf("\n| 2. Selectionner le Collaborateur de la Tache Finalisee |");
        printf("\n| 3. Back                                   |");
        printf("\n+-------------------------------------------+");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            if (count > 0)
            {
                int tacheId;

                tacheId = get_Index(3);

                ajouter_collaborateur(&Taches[tacheId]);
            }
            else
            {
                printf("Aucune tache disponible pour l'ajout de collaborateurs!\n");
            }

            break;
        case 2:
            SelectTaskPerformer();
            break;
        case 4:
            return; // Return to the previous menu
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    }
}

void createFile()
{
    FILE *F;
    if (count==0)
    {
       printf("No tasks available.\n");
       return;
    }
    
    F = fopen("projet_sasb.csv", "a");

    fprintf(F, "identifiant_unique, titre, description, creation_date, deadline, statut\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(F, "%d,%s,%s,%d/%d/%d,%d/%d/%d,%s\n",
                Taches[i].id, Taches[i].Title, Taches[i].description,
                Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year,
                Taches[i].deadline.day, Taches[i].deadline.month, Taches[i].deadline.year,
                Taches[i].status);
    }
    fclose(F);
}