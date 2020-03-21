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

// Initializing required variables
int TimeQuantum=0, FacultyCount=0, StudentCount=0, MixCount=0, TotalQueries=0;
int TQ=0, WaitTime=0, TATime=0, counter=0, i, total=0, CTarr[120], maximumCT=0;

void InputsForProcess() {
    int QueryType, AT=1000, BT=0;
    ValidQuery:
    printf("\nEnter total number of Queries: ");
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
                    if (AT>=1000 && AT<1100) {
                        Faculty[FacultyCount].ArrivalTime = AT-1000;
                    }
                    else {
                        Faculty[FacultyCount].ArrivalTime = AT-1040;
                    }
                }
                FBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(Faculty[FacultyCount].ArrivalTime + BT>120 || BT<=0 || BT>30) {
                    if(BT<=0 || BT>30) {
                    printf("\nBurst Time cannot be less than 0 or greater than 30\n"); }
                    else {
                        printf("Invalid Burst time for corresponding Arrival Time\n");
                    }
                    printf("Please enter valid Burst Time\n");
                    goto FBTime;
                }
                else {
                    Faculty[FacultyCount].BurstTime = BT;
                }
                Faculty[FacultyCount].TotalTime = Faculty[FacultyCount].BurstTime;
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
                    if (AT>=1000 && AT<1100) {
                        Student[StudentCount].ArrivalTime = AT-1000;
                    }
                    else {
                        Student[StudentCount].ArrivalTime = AT-1040;
                    }
                }
                SBTime:
                printf("Enter Burst Time: ");
                scanf("%d", &BT);
                if(Student[StudentCount].ArrivalTime + BT>120 || BT<=0 || BT>30) {
                    if(BT<=0 || BT>30) {
                    printf("\nBurst Time cannot be less than 0 or greater than 30\n"); }
                    else {
                        printf("Invalid Burst time for corresponding Arrival Time\n");
                    }
                    printf("Please enter valid Burst Time\n");
                    goto SBTime;
                }
                else {
                    Student[StudentCount].BurstTime = BT;
                }
                Student[StudentCount].TotalTime = Student[StudentCount].BurstTime;
                StudentCount++;
            }
            else {  // In case any error
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
}

void MinAT() {
    total = Mix[0].ArrivalTime;
    for(int i=1;i<MixCount;i++) {
        if(total>Mix[i].ArrivalTime) {
            total = Mix[i].ArrivalTime;
        }
    }
}

void MaxCT() {
    maximumCT=CTarr[0];
    for(i=1;i<MixCount;i++) {
        if(maximumCT<CTarr[i]) {
            maximumCT = CTarr[i];
        }
    }
}

void RoundRobin() {
    printf("\nQuery ID\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\tCompletionTime\n");
    for(i = 0; TQ != 0;) {
        if(Mix[i].TotalTime <= TimeQuantum && Mix[i].TotalTime > 0) {   // (First if) Process will complete without any preemption
            total = total + Mix[i].TotalTime;
            Mix[i].TotalTime = 0;
            counter = 1;
        }
        else if(Mix[i].TotalTime > 0) { // Process will preempt according to TimeQuantum
            Mix[i].TotalTime -= TimeQuantum;
            total = total + TimeQuantum;
        }
        if(Mix[i].TotalTime == 0 && counter == 1) {     // continue after first if
            TQ--;
            int ATCalc = Mix[i].ArrivalTime+1000;
            int CTCalc = total+1000;
            CTarr[i] = CTCalc;
            if(ATCalc>1059) {
                ATCalc += 40;
            }
            if(CTCalc>1059) {
                CTCalc += 40;
            }
            printf("\n%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", 
                Mix[i].QueryID, ATCalc, Mix[i].BurstTime, 
                total-Mix[i].ArrivalTime-Mix[i].BurstTime, total-Mix[i].ArrivalTime, CTCalc);
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

    MaxCT(); MinAT();
    printf("\n\nSummary of Execution: \n\n");
    printf("Total Time Spent on handling Queries: %d minutes\n", maximumCT-total-1000);
    float avgWaitTime = WaitTime * 1.0 / TotalQueries;
    float avgTATime = TATime * 1.0 / TotalQueries;
    printf("Average TurnAround Time : %.2f minutes\n", avgTATime);
    printf("Average Waiting Time : %.2f minutes", avgWaitTime);
    printf("\n\nProgram Execution Completed!\n\n");
}

void displayRawData() {
    printf("\nQueryID\tAT\tBT\tTT\n\n");
    for(int i=0; i<MixCount; i++) {
        printf("%s\t%d\t%d\t%d\t%d\n",Mix[i].QueryID,Mix[i].ArrivalTime,Mix[i].BurstTime,Mix[i].TotalTime);
    }
    printf("\n%d",total);
}

void main() {
    printf("\nWelcome to the OS Project made by Dhiraj Kelhe.\n\n"
        "Please follow these instructions:\n"
        "1. Enter number of queries between 0 & 120\n"
        "2. Make sure to keep value of TimeQuantum minimum\n"
        "3. Enter Query Arrival Time in the format of HHMM\n"
        "    Example: 10:25 should be entered as 1025\n"
        "4. Next Query's arrival time must be less than previous Query's (Arrival Time + Burst Time)\n"
        "5. Queries must be entered in sequential order of Arrival Time\n"
        "6. Burst Time must be entered such that [Arrival Time < (Arrival Time + Burst Time) <= 120] & (0 < BT <= 30)\n");
    InputsForProcess();
    MergeQueries();
    // displayRawData();    // For testing purpose
    RoundRobin();
}