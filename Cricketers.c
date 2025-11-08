#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct CricketPlayers{
    int jerseyno;
    char name[20];
    int matches;
    int runs;
    int wickets;
    float average;
    float strikerate;
    float economy;
};


int main(){
    int choice;

    while(1){
        printf("------ Cricketers Stats ------ \n");
        printf("1.Add New Player \n");
        printf("2.Display All Players \n");
        printf("3.Search Player by Jersey number \n");
        printf("4.Delete Player by Jersey number \n");
        printf("5.Update Players Stats by Jersey Number \n");
        printf("6.Exit \n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                addPlayer();
                break;
            case 2:
                displayPlayers();
                break;
            case 3:
                searchPlayer();
                break;
            case 4:
                deletePlayer();
                break;
            case 5:
                updatePlayer();
                break;
            case 6:
                printf("Exiting......");
                exit(0);
            default:
                printf("Invalid Choice!Enter valid Choice");
        }
    }
}

void addPlayer(){
    FILE *fp;

    struct CricketPlayers c;

    fp = fopen("Cricketers.txt","a");
    if(fp == NULL){
        printf("Error opening file");
        return;
    }

    printf("\t Enter Jersey Number : ");
    scanf("%d",&c.jerseyno);
    printf("\t Enter name of the player [without space] : ");
    getchar();
    fgets(c.name,sizeof(c.name),stdin);
    c.name[strcspn(c.name,"\n")] = '\0';
    printf("\t No of matches played : ");
    scanf("%d",&c.matches);
    printf("\t Enter no of runs scored : ");
    scanf("%d",&c.runs);
    printf("\t Enter no of wickets taken by a player : ");
    scanf("%d",&c.wickets);
    printf("\t Enter the average runs of a player : ");
    scanf("%f",&c.average);
    printf("\t Enter strike rate of a player : ");
    scanf("%f",&c.strikerate);
    printf("\t ENter economy of a player : ");
    scanf("%f",&c.economy);

    fprintf(fp, "%d %s %d %d %d %.2f %.2f %.2f\n",
        c.jerseyno, c.name, c.matches, c.runs,
        c.wickets, c.average, c.strikerate, c.economy);


    fclose(fp);

    printf("Player Added Successfully !\n");
}
 

void displayPlayers(){
    FILE *fp;
    struct CricketPlayers c;

    fp = fopen("Cricketers.txt","r");
    if(fp == NULL){
        printf("No Players record found!\n");
        return;
    }

    printf("\n---- Players Records ----\n");

    while (fscanf(fp, "%d %s %d %d %d %f %f %f",
                  &c.jerseyno, c.name, &c.matches, &c.runs,
                  &c.wickets, &c.average, &c.strikerate, &c.economy) == 8){
        printf("\nJersey No: %d\nName: %s\nMatches: %d\nRuns: %d\nWickets: %d\nAverage: %.2f\nStrike Rate: %.2f\nEconomy: %.2f\n",
               c.jerseyno, c.name, c.matches, c.runs, c.wickets,
               c.average, c.strikerate, c.economy);
    }

    fclose(fp);
}


void searchPlayer(){
    FILE *fp;

    struct CricketPlayers c;
    
    int jerseyno,found = 0;

    fp = fopen("Cricketers.txt","r");
    if(fp == NULL){
        printf("No player records found!\n");
        return;
    }

    printf("Enter jersey number to search : ");
    scanf("%d",&jerseyno);

    while (fscanf(fp, "%d %s %d %d %d %f %f %f",
                  &c.jerseyno, c.name, &c.matches, &c.runs,
                  &c.wickets, &c.average, &c.strikerate, &c.economy) == 8){
        if(c.jerseyno == jerseyno){
            printf("\nJersey No: %d\nName: %s\nMatches: %d\nRuns: %d\nWickets: %d\nAverage: %.2f\nStrike Rate: %.2f\nEconomy: %.2f\n",
               c.jerseyno, c.name, c.matches, c.runs, c.wickets,
               c.average, c.strikerate, c.economy);

               found = 1;
               break;
        }
    }    
    if(!found){
        printf("\n Player not found!\n");
    }

    fclose(fp);
}

void deletePlayer(){
    FILE *fp, *temp;
    struct CricketPlayers c;
    int jerseyno, found = 0;
    
    fp = fopen("Cricketers.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter jersey number to delete player: ");
    scanf("%d", &jerseyno);

    while (fscanf(fp, "%d %s %d %d %d %f %f %f",
                  &c.jerseyno, c.name, &c.matches, &c.runs,
                  &c.wickets, &c.average, &c.strikerate, &c.economy) == 8) {

        if (c.jerseyno == jerseyno) {
            found = 1;
            printf("\nDeleted Player Details:\n");
            printf("Jersey No: %d\nName: %s\nMatches: %d\nRuns: %d\nWickets: %d\nAverage: %.2f\nStrike Rate: %.2f\nEconomy: %.2f\n",
                   c.jerseyno, c.name, c.matches, c.runs, c.wickets,
                   c.average, c.strikerate, c.economy);
        } else {
            fprintf(temp, "%d %s %d %d %d %.2f %.2f %.2f\n",
                    c.jerseyno, c.name, c.matches, c.runs,
                    c.wickets, c.average, c.strikerate, c.economy);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("Cricketers.txt");
    rename("temp.txt", "Cricketers.txt");

    if (found)
        printf("\n Player deleted successfully!\n");
    else
        printf("\n Player not found!\n");
}


void updatePlayer(){
    FILE *fp;
    FILE *temp;

    struct CricketPlayers c;

    fp = fopen("Cricketers.txt","r");
    temp = fopen("temp.txt","w");

    int jerseyno,found = 0;

    if(fp == NULL || temp == NULL){
        printf("Error opening File \n");
    }

    printf("Enter jersey number to update the stats of a player : ");
    scanf("%d",&jerseyno);

    while (fscanf(fp, "%d %s %d %d %d %f %f %f",
                  &c.jerseyno, c.name, &c.matches, &c.runs,
                  &c.wickets, &c.average, &c.strikerate, &c.economy) == 8){

        if(c.jerseyno == jerseyno){
            found = 1;
            printf("\n ---UPDATE DETAIL---\n");
            printf("\t No of matches played : ");
            scanf("%d",&c.matches);
            printf("\t Enter no of runs scored : ");
            scanf("%d",&c.runs);
            printf("\t Enter no of wickets taken by a player : ");
            scanf("%d",&c.wickets);
            printf("\t Enter the average runs of a player : ");
            scanf("%f",&c.average);
            printf("\t Enter strike rate of a player : ");
            scanf("%f",&c.strikerate);
            printf("\t ENter economy of a player : ");
            scanf("%f",&c.economy);
        }
        fprintf(temp, "%d %s %d %d %d %.2f %.2f %.2f\n",
                c.jerseyno, c.name, c.matches, c.runs,
                c.wickets, c.average, c.strikerate, c.economy);
    }

    fclose(fp);
    fclose(temp);

    if(!found){
        printf("Player NOT FOUND !!!");
    }

    remove("Cricketers.txt");
    rename("temp.txt","Cricketers.txt");
}
