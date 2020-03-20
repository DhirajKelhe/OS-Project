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
}Faculty[120], Student[120], Mix[120];

// Initializing starting queries
int TimeQuantum=0, FacultyCount=0, StudentCount=0, MixCount=0, TotalQueries=0;
int TQ=0, total=0, WaitTime=0, TATime=0, counter=0, i;

void InputsForProcess() {
    int QueryType, AT=1000, BT=0;
    ValidQuery:
    printf("Enter total number of Queries: ");
    scanf("%d", &TotalQueries);
    // Check whether entered query number is <0 or >120
    if(TotalQueries<=0 || TotalQueries>120) {
        printf("\nQueries cannot be less than 0 or more than 120!\n");
        goto ValidQuery;
    }
    else {
        TQ = TotalQueries;
        printf("\nEnter Time Quantum for each query: ");
        scanf("%d", &TimeQuantum);
        // Taking inputs for all the queries
        for(int i=0; i<TotalQueries; i++) {
            TryQuery:
            printf("\nType of Query (1 for Faculty, 2 for Student): ");
            scanf("%d", &QueryType);

            // Query Processing For Faculty
            if(QueryType == 1) {
                printf("\nEnter Query ID: ");
                scanf("%s", &Faculty[FacultyCount].QueryID);
                FTime:
                printf("Enter Query Arrival Time: ");
                scanf("%d", &AT);
                // Check Time constraint
                if(AT<1000 || AT>1200 || (AT<1100 && AT>1059) || (AT<1200 && AT>1159)) {
                    printf("\nEnter Correct Time!\n");
                    goto FTime;
                }
                else {
                    Faculty[FacultyCount].ArrivalTime = AT-1000;
                }
                FBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(BT>=120 || BT<=0) {
                    printf("\nBurst Time cannot be less than 0 or greater than 120.\nPlease enter valid Burst Time.\n");
                    goto FBTime;
                }
                else {
                    Faculty[FacultyCount].BurstTime = BT;
                }
                Faculty[FacultyCount].TotalTime += Faculty[FacultyCount].BurstTime;
                FacultyCount++;
            }

            // Query Processing For Student
            else if(QueryType == 2) {
                printf("\nEnter Query ID: ");
                scanf("%s", &Student[StudentCount].QueryID);
                STime:
                printf("Enter Query Arrival Time: ");
                scanf("%d", &AT);
                // Check Time constraint
                if(AT<1000 || AT>1200 || (AT<1100 && AT>1060) || (AT<1200 && AT>1160)) {
                    printf("\nEnter valid Time!\n");
                    goto STime;
                }
                else {
                    Student[StudentCount].ArrivalTime = AT-1000;
                }
                SBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(BT>=120 || BT<=0) {
                    printf("\nBurst Time cannot be less than 0 or greater than 120!.\nPlease enter valid Burst Time.\n");
                    goto SBTime;
                }
                else {
                    Student[StudentCount].BurstTime = BT;
                }
                Student[StudentCount].TotalTime += Student[StudentCount].BurstTime;
                StudentCount++;
            }
            else {
                printf("\nInvalid Input. Please try again.\n");
                goto TryQuery;
            }
        }
    }
}

// function to merge faculty and student's queries into one variable.
void MergeQueries() {
    int iSC=0, iFC=0;
    if( FacultyCount !=0  && StudentCount !=0){	// got entries for both
		while(iSC < StudentCount && iFC < FacultyCount ){
			if(Faculty[iFC].ArrivalTime == Student [iSC].ArrivalTime){	// both entries arrives at same time
				Mix[MixCount] = Faculty[iFC];	// priority to faculty
				MixCount++;
				iFC++;
				Mix[MixCount] = Student [iSC];	// and then student
				MixCount++;
				iSC++;
			}
			else if(Faculty[iFC].ArrivalTime < Student [iSC].ArrivalTime) {	// faculty entry came before
				Mix[MixCount]= Faculty[iFC];
				MixCount++;
				iFC++;
			}
			else if(Faculty[iFC].ArrivalTime > Student [iSC].ArrivalTime){	// student entry came first
				Mix[MixCount]= Student [iSC];
				MixCount++;
				iSC++;
			}
			else;
		}
		if(MixCount != (FacultyCount + StudentCount )){	// in case there's any error
			if(FacultyCount != iFC){
				while(iFC!=FacultyCount ){	
					Mix[MixCount] = Faculty[iFC];
					MixCount++;
					iFC++;
				}
			}
			else if(StudentCount !=iSC){
				while(iSC!=StudentCount ){
					Mix[MixCount]= Student [iSC];
					MixCount++;
					iSC++;
				}
			}
		}
	}
	else if(FacultyCount == 0){	//got entries for student
		while(iSC!=StudentCount ){
			Mix[MixCount]= Student [iSC];
			MixCount++;
			iSC++;
		}
	}
	else if(StudentCount == 0){	//got entries for faculty
		while(iFC!=FacultyCount ){
			Mix[MixCount]= Faculty[iFC];
			MixCount++;
			iFC++;
		}
	}
	else {
		printf("\n No valid Jobs available\n");
	}
}

void RoundRobin() {
    printf("\nQuery ID\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\tCompletionTime\n");
    // printf("%s",Mix[0].QueryID);
    for(total = 0, i = 0; TQ != 0;) {
        if(Mix[i].TotalTime <= TimeQuantum && Mix[i].TotalTime > 0) {
            total = total + Mix[i].TotalTime;
            Mix[i].TotalTime = 0;
            counter = 1;
        }
        else if(Mix[i].TotalTime > 0) {
            Mix[i].TotalTime -= TimeQuantum;
            total = total + TimeQuantum;
        }
        if(Mix[i].TotalTime == 0 && counter == 1) {
            TQ--;
            printf("\n%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", 
                Mix[i].QueryID, Mix[i].ArrivalTime+1000, Mix[i].BurstTime, 
                total-Mix[i].ArrivalTime-Mix[i].BurstTime, total-Mix[i].ArrivalTime, total+1000);
            WaitTime += total - Mix[i].ArrivalTime - Mix[i].BurstTime;
            TATime += total - Mix[i].ArrivalTime;
            counter = 0;
        }
        if(i == TotalQueries - 1) {
            i = 0;
        }
        else if(Mix[i+1].ArrivalTime <= total) {
            i++;
        }
        else {
            i = 0;
        }
    }
    float avgWaitTime = WaitTime * 1.0 / TotalQueries;
    float avgTATime = TATime * 1.0 / TotalQueries;
    printf("\n\nAverage Waiting Time : %f", avgWaitTime);
    printf("\nAverage TurnAround Time : %f\n", avgTATime);
}

void main() {
    printf("\nWelcome\n\n");
    InputsForProcess();
    MergeQueries();
    RoundRobin();
}