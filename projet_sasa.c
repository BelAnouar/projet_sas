#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    int deadline;
    char status[30];
    Collaborateur collaborateur;
} Tache;

// /initialisation
#define MAX_Tache 100

Tache Taches[MAX_Tache];
Collaborateur collaborateurs[MAX_Tache];
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

int main()
{
    int choice;

    do
    {
        printf("\n1.\tAjouter une nouvelle tâche:");
        printf("\n2.\tAfficher la liste de toutes les tâches:");
        printf("\n3.\tModifier une tâche:");
        printf("\n4.\tSupprimer une tâche par identifiant:");
        printf("\n5.\tRechercher les Tâches :");
        printf("\n6.\tStatistiques  :");
        printf("\n7.\tajouter un  collaborateur :");
        printf("\n0.\t Quit:");

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
    scanf("%d", &choice);

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
    int currentDAys = 0, days = 0;
    int currentYear = date.tm_year + 1900;
    int currentday = date.tm_mday;
    int currentmonth = date.tm_mon + 1;
    currentDAys += 2023 * 365;
    currentDAys += 9 * 30;
    currentDAys += 20;
    days += year * 365;
    days += month * 30;
    days += day;

    return days - currentDAys;
}
// creation
void Ajoute()
{
    int number;
    FILE *F;

    printf("\nEnter the number of Taches you want to enter: ");
    scanf("%d", &number);
    F = fopen("stu.csv", "a");

    if (count + number > MAX_Tache)
    {
        printf("Exceeded the maximum number of Taches (%d).\n", MAX_Tache);
        return;
    }
    if (count == 0)
    {
        fprintf(F, "identifiant_unique, titre, description,deadline ,son statut\n");
    }

    for (int i = count; i < count + number; i++)
    {
        Taches[i].id = i;
        printf("\nEnter the Title of the Tache: ");
        scanf("%s", Taches[i].Title);
        printf("Enter the description of the Tache: ");
        scanf("%s", Taches[i].description);
        strcpy(Taches[i].status, statusTask());
        printf("Enter the day  of the TAche: ");
        scanf("%d", &Taches[i].creation_date.day);
        printf("Enter the mounth  of the TAche: ");
        scanf("%d", &Taches[i].creation_date.month);
        printf("Enter the year  of the TAche: ");
        scanf("%d", &Taches[i].creation_date.year);
        // fflush(stdin);
        Taches[i].deadline = calcDeadline(Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year);
        Taches[i].collaborateur.idC = 0;
    }
    for (int i = 0; i <count ; i++)
    {
        fprintf(F, "%d,%s, %s, %d, %s\n",Taches[i].id,Taches[i].Title,Taches[i].description,Taches[i].deadline,Taches[i].status);
    }
    count += number;
    

    fclose(F);
}
// Trier par ordre alphabétique

void Order()
{
    Tache Temp;

    int lenght = count;

    for (int i = 0; i < lenght - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < lenght; j++)
        {
            if (Taches[min].Title[0] > Taches[j].Title[0])
            {
                min = j;
            }
        }
        Temp = Taches[min];
        Taches[min] = Taches[i];
        Taches[i] = Temp;
    }
    for (int i = 0; i < count; i++)
    {
        printf("%s, %s, %d/%d/%d, %d, %d\n", Taches[i].Title, Taches[i].description, Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year, Taches[i].id, Taches[i].deadline);
    }
}

// les tâches par deadline
void Deadline()
{
    Tache Temp;

    int lenght = count;

    for (int i = 0; i < lenght - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < lenght; j++)
        {
            if (Taches[min].deadline > Taches[j].deadline)
            {
                min = j;
            }
        }
        Temp = Taches[min];
        Taches[min] = Taches[i];
        Taches[i] = Temp;
    }
    for (int i = 0; i < lenght; i++)
    {
        printf("%s, %s, %d/%d/%d, %d , %d\n", Taches[i].Title, Taches[i].description, Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year, Taches[i].id, Taches[i].deadline);
    }
}
// Afficher les tâches dont le deadline est dans 3 jours ou moins.

void Date_Deadline()
{
    Tache Temp;

    int lenght = count;

    for (int i = 0; i < lenght; i++)
    {
        if (Taches[i].deadline < 3)
        {
            printf("%s, %s, %d/%d/%d, %d\n", Taches[i].Title, Taches[i].description, Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year, Taches[i].id);
        }
    }
}
// Afficher
void Afficher()
{
    int ch;

    while (1)
    {
        printf("\n1.\tTrier les tâches par ordre alphabétique.:");
        printf("\n2.\tTrier les tâches par deadline:");
        printf("\n3.\tAfficher les tâches dont le deadline est dans 3 jours ou moins.:");
        printf("\n4.\tBack  :");

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

// Modifier la description d'une tâche
void Modifier_By_Description()
{

    if (count == 0)
    {
        printf("No data to update.\n");
        return;
    }

    printf("Enter the index of the tasks to update: ");
    int index;
    scanf("%d", &index);

    if (index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }

    printf("Enter the updated description of the Tache: ");
    scanf("%s", Taches[index].description);
    printf("Tache information updated successfully.\n");

    return Modifier();
}
// Modifier le statut d’une tâche:
void Modifier_By_Status()
{

    if (count == 0)
    {
        printf("No data to update.\n");
        return;
    }

    printf("Enter the index of the tasks to update: ");
    int index;
    scanf("%d", &index);

    if (index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }

    printf("Enter the updated status of the Tache: ");
    scanf("%s", Taches[index].status);
    printf("Tache information updated successfully.\n");

    return Modifier();
}
// Modifier le deadline d’une tâche
void Modifier_By_DeaDline()
{

    if (count == 0)
    {
        printf("No data to update.\n");
        return;
    }

    printf("Enter the index of the tasks to update: ");
    int index;
    scanf("%d", &index);

    if (index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }

    printf("Enter the updated deadline of the Tache: ");
    scanf("%s", Taches[index].deadline);
    printf("Tache information updated successfully.\n");
    return Modifier();
}
// Modifier

void Modifier()
{
    int ch;

    printf("\n1.\tModifier la description d'une tâche.:");
    printf("\n2.\tModifier le statut d’une tâche:");
    printf("\n3.\tModifier le deadline d’une tâche:");
    printf("\n0.\tBack  :");

    printf("\nEnter your choice: ");
    scanf("%d", &ch);
    do
    {

        switch (ch)
        {
        case 1:
            Modifier_By_Description();
            break;
        case 2:
            Modifier_By_Status();
            break;
        case 3:
            Modifier_By_DeaDline();
            break;
        case 0:
            main();
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    } while (ch != 0);
}

void Supprimer()
{
    if (count == 0)
    {
        printf("No data to delete.\n");
        return;
    }

    printf("Enter the index of the tasks to delete: ");
    int index;
    scanf("%d", &index);

    if (index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }

    printf("Are you sure you want to delete the tasks %d %s %s? (1 for yes, 0 for no): ", Taches[index].id, Taches[index].Title, Taches[index].description);
    int confirmation;
    scanf("%d", &confirmation);

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
    }
}

// Rechercher une tâche par son Identifiant.
void Recheche_By_Identifiant()
{
    int index;
    if (count == 0)
    {
        printf("data doesn't exist.\n");
        return;
    }

    printf("Enter the index of the task to find: ");

    scanf("%d", &index);

    if (index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (Taches[i].id == index)
        {
            printf("%s, %s, %d/%d/%d, %d, %d\n", Taches[i].Title, Taches[i].description, Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year, Taches[i].id, Taches[i].deadline);
        }
    }

    return Recherche();
}
// Rechercher une tâche par son Titre:
void Recheche_By_Title()
{

    char title[50];
    if (count == 0)
    {
        printf("data doesn't exist.\n");
        return;
    }

    printf("Enter the title of the task to find: ");

    scanf("%s", title);

    for (int i = 0; i < count; i++)
    {
        if (strcmp(Taches[i].Title, title) == 0)
        {
            printf("%s, %s, %d/%d/%d, %d, %d\n", Taches[i].Title, Taches[i].description, Taches[i].creation_date.day, Taches[i].creation_date.month, Taches[i].creation_date.year, Taches[i].id, Taches[i].deadline);
        }
    }

    return Recherche();
}
// REcherche
void Recherche()
{
    int ch;

    printf("\n1.\tRechercher une tâche par son Identifiant..:");
    printf("\n2.\tRechercher une tâche par son Titre:");

    printf("\n0.\tBack  :");

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
        case 0:
            main();
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    } while (ch != 0);
}

// Afficher le nombre total des tâches:
void Total_task()
{
    printf("le nombre total des tâches:");
    printf("\n%d", count);
}
// Afficher le nombre de tâches complètes et incomplètes
void complete()
{
    int cptNf = 0, cptf = 0;
    for (int i = 0; i < count; i++)
    {
        if (Taches[i].status == 'todo' || Taches[i].status == 'doing')
        {
            cptNf++;
        }
        else
        {
            cptf++;
        }
    }

    printf("\nle nombre de tâches complètes : %d ", cptf);
    printf("\nle nombre de tâches  incomplètes: %d ", cptNf);
}
// Afficher le nombre de jours restants jusqu'au délai de chaque tâche
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

    printf("\n1.\tAfficher le nombre total des tâches:");
    printf("\n2.\tAfficher le nombre de tâches complètes et incomplètes.");
    printf("\n2.\tAfficher le nombre de jours restants jusqu'au délai de chaque tâche.");

    printf("\n0.\tBack  :");

    printf("\nEnter your choice: ");
    scanf("%d", &ch);
    do
    {

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
            main();
        default:
            printf("This choice doesn't exist in the menu\n");
            break;
        }
    } while (ch != 0);
}

// Ajouter un collaborateur
void ajouter_collaborateur()
{

    int number;

    if (count == 0)
    {
        printf("no tasks in data.\n");
        return;
    }

    printf("Enter the index of the tasks to find: ");
    int index;
    scanf("%d", &index);

    if (index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }

    printf("\nEnter the number of collaborateur you want to enter: ");
    scanf("%d", &number);

    if (countC + number > MAX_Tache)
    {
        printf("Exceeded the maximum number of collaborateur (%d).\n", MAX_Tache);
        return;
    }

    for (int i = countC; i < countC + number; i++)
    {
        collaborateurs[i].idC = i;
        printf("\nEnter first name of the collaborateur: ");
        scanf("%s", collaborateurs[i].nom);
        printf("Enter last name of the collaborateur: ");
        scanf("%s", collaborateurs[i].prenom);
        printf("Enter email of the collaborateur: ");
        scanf("%s", &collaborateurs[i].email);
        strcpy(Taches[index].collaborateur.idC, collaborateurs[i].idC);
    }

    countC += number;
}