/* Problem Statement:
 Sudesh Sharma is a Linux expert who wants to have an online system where he can handle student queries. 
 Since there can be multiple requests at any time,
 he wishes to dedicate a fixed amount of time (i.e. Time Quantum) to every request so that everyone gets a fair share of his time. //i.e. Round Robin algo
 He will log into the system from 10am to 12am only. 
 He wants to have separate requests queues for students and faculty. 
 Implement a strategy for the same. 
 The summary at the end of the session should include the total time he spent on handling queries and average query time.
 */

#include<stdio.h>
 /* Since a process/query can have multiple attributes like: 
 ProcessID, ArrivalTime, BurstTime, WaitingTime, TurnAroundTime and CompletionTime,
 we need to define structure for that and have to create variables/objects of structure*/
struct Query {
    char QueryID[3];
    int ArrivalTime;
    int BurstTime;
    int CompletionTime;
    int TotalTime;
}Faculty[120], Student[120];

// Initializing starting queries
int TimeQuantum, FacultyQuery=0, StudentQuery=0;

void InputsForProcess() {
    int TotalQueries, i, QueryType, AT=1000, BT=0;
    printf("Enter total number of Queries: ");
    scanf("%d", &TotalQueries);
    // Check whether entered query number is <0 or >120
    if(TotalQueries<=0 || TotalQueries>120) {
        printf("\nQueries cannot be less than 0 or more than 120!\n");
    }
    else {
        printf("\nEnter Time Quantum for each query: ");
        scanf("%d", &TimeQuantum);
        // Taking inputs for all the queries
        for(i=0; i<TotalQueries; i++) {
            TryQuery:
            printf("\nType of Query (1 for Faculty, 2 for Student): ");
            scanf("%d", &QueryType);
            // Query Processing For Faculty
            if(QueryType == 1) {
                printf("\nEnter Query ID: ");
                scanf("%s", &Faculty[FacultyQuery].QueryID);
                FTime:
                printf("Enter Query Arrival Time: ");
                scanf("%d", &AT);
                // Check Time constraint
                if(AT<1000 || AT>1200 || (AT<1100 && AT>1059) || (AT<1200 && AT>1159)) {
                    printf("\nEnter Correct Time!\n");
                    goto FTime;
                }
                else {
                    Faculty[FacultyQuery].ArrivalTime = AT-1000;
                }
                FBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(BT>=120 || BT<=0) {
                    printf("\nBurst Time cannot be less than 0 or greater than 120!.\nPlease enter valid Burst Time.\n");
                    goto FBTime;
                }
                else {
                    Faculty[FacultyQuery].BurstTime = BT;
                }
                Faculty[FacultyQuery].TotalTime = Faculty[FacultyQuery].BurstTime;
                FacultyQuery++;
            }
            // Query Processing For Student
            else if(QueryType == 2) {
                printf("\nEnter Query ID: ");
                scanf("%s", &Student[StudentQuery].QueryID);
                STime:
                printf("Enter Query Arrival Time: ");
                scanf("%d", &AT);
                // Check Time constraint
                if(AT<1000 || AT>1200 || (AT<1100 && AT>1060) || (AT<1200 && AT>1160)) {
                    printf("\nEnter Correct Time!\n");
                    goto STime;
                }
                else {
                    Student[StudentQuery].ArrivalTime = AT-1000;
                }
                SBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(BT>=120 || BT<=0) {
                    printf("\nBurst Time cannot be less than 0 or greater than 120!.\nPlease enter valid Burst Time.\n");
                    goto SBTime;
                }
                else {
                    Student[StudentQuery].BurstTime = BT;
                }
                Student[StudentQuery].TotalTime = Student[StudentQuery].BurstTime;
                StudentQuery++;
            }
            else {
                printf("\nInvalid Input. Please try again.\n");
                goto TryQuery;
            }
        }
    }
}

void main() {
    printf("\nWelcome\n\n");
    InputsForProcess();
}