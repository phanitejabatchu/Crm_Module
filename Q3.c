#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 50

int front = 0;
int rear = -1;
static int itemCount = 0;
#define MAX_CYCLES 11000
#define MIN_CYCLES 1000
#define MAX_SIZE 100
#define MIN_SIZE 1
#define MEAN_SIZE 20

int Memory();
int Cycles();
static int total_cycle_count=0;
static int total_waiting_time=0;
static int Total_penality=0;
static int cycle_count=1;
static int temp_cycles=1;
static int total_cycles=0;
static int count=1;
static int slices=5; 
static int totalmem=0;

struct Create_process { 
	int process_memory;
	int process_cycles;
	int process_id;
	int arrival_time;
	int turn_around_time;
	int penality_time;
	int waiting_time;
	int process_cycles_temp;
};
int Ready_Queue[MAX_QUEUE_SIZE];
int peek(){
   return Ready_Queue[front];
}
bool isEmpty(){
   return itemCount == 0;
}
bool isFull(){
   return itemCount == MAX_QUEUE_SIZE;
}
int size(){
   return itemCount;
}

void insert(int data){
   if(!isFull()){
      if(rear == MAX_QUEUE_SIZE-1){
         rear = -1;            
      }
      Ready_Queue[++rear] = data;
      itemCount++;
   }
}
int removeData(){
   int data = Ready_Queue[front++];	
   if(front == MAX_QUEUE_SIZE){
      front = 0;
   }	
   itemCount--;
   return data;  
}

void main(int argc, char* argv[])
{
int i,j, pid;
struct Create_process process[atoi(argv[1])];
struct Create_process process1;
int pro1;
for(i=0; i < atoi(argv[1]); i++) {
    pid = fork();
    if(pid < 0) {
        printf("Error");
        exit(1);
    } else if (pid == 0) {
         exit(0);
    } else {
		process[i].process_id= pid;
		process[i].process_memory= Memory();
		process[i].process_cycles=Cycles();
		process[i].process_cycles_temp=process[i].process_cycles;
		process[i].arrival_time=i*50;
		process[i].penality_time=0;
		process[i].waiting_time=0;
    }
}
//printf("total_cycles: %d", total_cycles);
i=0;
insert(i);
while(1)
{
if(i < atoi(argv[1])-1)
{
i=i+1;
insert(i);
}
while(!isEmpty())
{
pro1 = removeData();
process1=process[pro1];
if(process[pro1].process_cycles<50)
{
printf("Executed %d Cycles of %d\n", process[pro1].process_cycles, process[pro1].process_id);
total_cycle_count=total_cycle_count+process[pro1].process_cycles;
process[pro1].process_cycles=0;
process[pro1].turn_around_time=total_cycle_count-process[pro1].arrival_time;
process[pro1].waiting_time=process[pro1].turn_around_time-process[pro1].process_cycles_temp;
total_waiting_time=total_waiting_time+process[pro1].waiting_time;
}
else if(isEmpty()&&i==atoi(argv[1])-1) {
printf("Executed %d Cycles of %d\n", process[pro1].process_cycles, process[pro1].process_id);
total_cycle_count=total_cycle_count+process[pro1].process_cycles;
process[pro1].process_cycles=0;
process[pro1].turn_around_time=total_cycle_count-process[pro1].arrival_time;
process[pro1].waiting_time=process[pro1].turn_around_time-process[pro1].process_cycles_temp;
total_waiting_time=total_waiting_time+process[pro1].waiting_time;
}
else
{
printf("Executed 50 Cycles of %d\n", process[pro1].process_id);
process[pro1].process_cycles=process[pro1].process_cycles-50;
total_cycle_count=total_cycle_count+50;
}
if(!isEmpty())
{
Total_penality=Total_penality+10;
process[pro1].penality_time=process[pro1].penality_time+10;
//printf("Penality Time  : %d\n",process[pro1].penality_time);
if(process[pro1].process_cycles!=0)
{
insert(pro1);
}
//printf("size: %d",size());
break;
}
}
if(total_cycle_count==total_cycles){
for(j = 0; j < atoi(argv[1]); j++) {
	printf("Process Id: %d\n",process[j].process_id);
	printf("Cycles    : %d\n",process[j].process_cycles_temp);
	printf("Waiting Time   : %d\n",process[j].waiting_time);
	printf("Penality Time  : %d\n",process[j].penality_time);
	printf("-------------------\n");
}
printf("Average Waiting Time   : %d\n",total_waiting_time/atoi(argv[1]));
printf("Average Penality Time  : %d\n",Total_penality/atoi(argv[1]));
exit(0);
}
}
}
int Memory()
{
	if(count%2==1)
	{
		count++;
		int mem= abs((rand() % MAX_SIZE));
		totalmem=mem;
		return mem;
	}
	else
	{
	count++;
	int memory=MAX_SIZE-totalmem;
	return memory;
	}
	 
}
int Cycles()
{
int cycle=0;
	if(cycle_count%2==1)
	{
		cycle_count++;
		cycle= abs((rand() % MAX_CYCLES));
		temp_cycles=cycle;
	}
	else
	{
	cycle_count++;
	cycle=MAX_CYCLES-temp_cycles;
	}
total_cycles=total_cycles+cycle;
return cycle;
}