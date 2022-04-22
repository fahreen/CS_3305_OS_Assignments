#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Process{
	char *id;
	int CPU_burst_time;
	int wait_time;
	int turnaround_time;
	int time_picked_up_from_q;
	int picked_up;
	};

struct Queue{
	int name;
	int current_time;
	int tq;
	int size;
	struct Process *FCFS;
	struct Process *SJF;
	struct Process *RR;
	};

void swap (struct Process *xp, struct Process *yp){
	struct Process temp = *xp;
	*xp = *yp;
	*yp = temp;
	};




struct Queue initialize_queue(char *processes, struct Queue q) {
		
	// allocate memory for  FCFS, SJF, and RR arrays
	// get size estimation for procceses 
	size_t len = strlen(processes);
	len = len/5;
	
	// dynamically allocate queues
	q.FCFS = malloc(len*sizeof(struct Process));
	q.SJF = malloc(len*sizeof(struct Process));
	q.RR = malloc(len*sizeof(struct Process));
	
	int i = 0;
	char *process_id;
	int CPU_bt;
	
	// enter first process into FCFS and RR
	char *pch;
	pch = strtok(processes, " ");
	process_id = pch;
	pch = strtok(NULL, " ");
	CPU_bt = atoi(pch);
	struct Process p = {process_id,CPU_bt, 0, 0, 0, 0};
	q.FCFS[i] = p;
	q.RR[i] = p;
	q.SJF[i] = p;
	
	
	// enter rest of the  processes into FCFS and RR
	while (pch != NULL ){
		pch = strtok(NULL, " "); 
		process_id = pch;
		pch = strtok(NULL, " ");
		if (pch == NULL)
			break;
		CPU_bt = atoi(pch);
		i ++;
		struct Process p = {process_id,CPU_bt, 0, 0, 0, 0};
		q.FCFS[i] = p;
		q.RR[i] = p;
		q.SJF[i] = p;
		}
		q.size = i+1 ;

	
	// fill SJF by sorting one of the arrays we've already filled
	int z,j, min_index;
	for (z = 0; z <= q.size-2; z++){
		min_index = z;
		for (j = z+1; j <= q.size-1; j++){
			if((q.SJF[j]).CPU_burst_time < (q.SJF[min_index]).CPU_burst_time)
				swap(&(q.SJF[j]),&(q.SJF[min_index]) );
	
	}}
	return q;
	
	};

// execute

void fcfs(FILE *fp, struct Queue *q){
	q-> current_time = 0;
	fprintf(fp, "Order of selection by CPU: \n");
	for(int i = 0; i < q->size; i++){
		fprintf(fp, "%s ", (q->FCFS)[i].id);
		(q->FCFS)[i].wait_time = q-> current_time;
		q-> current_time = (q-> current_time) + (q->FCFS)[i].CPU_burst_time;
	}
	
	
	
	fprintf(fp, "\n");	
	int sum = 0;
	fprintf(fp, "\nIndividual waiting times for each process: \n");
	for(int j= 0; j < q->size; j++){
		fprintf(fp, "%s = ", (q->FCFS)[j].id);
		fprintf(fp, "%d\n", (q->FCFS)[j].wait_time);
		sum = sum +((q->FCFS)[j].wait_time) ;
	}
	
	float average_waiting_time = (float)sum/q->size;
	fprintf(fp, "\nAverage waiting time =  %.1f\n\n",average_waiting_time );
	
	};




void sjf(FILE *fp, struct Queue *q){
	q-> current_time = 0;
	fprintf(fp, "Order of selection by CPU: \n");
	for(int i = 0; i < q->size; i++){
		fprintf(fp, "%s ", (q->SJF)[i].id);
		(q->SJF)[i].wait_time = q-> current_time;
		q-> current_time = (q-> current_time) + (q->SJF)[i].CPU_burst_time;
	}
	
	fprintf(fp, "\n");	
	int sum = 0;
	fprintf(fp, "\nIndividual waiting times for each process: \n");
	for(int j= 0; j < q->size; j++){
		fprintf(fp, "%s = ", (q->SJF)[j].id);
		fprintf(fp, "%d\n", (q->SJF)[j].wait_time);
		sum = sum +((q->SJF)[j].wait_time) ;
	}
	
	float average_waiting_time = (float)sum/q->size;
	fprintf(fp, "\nAverage waiting time =  %.1f\n\n",average_waiting_time );
	};


void rr(FILE *fp , struct Queue *q){
	q-> current_time = 0;
	fprintf(fp, "Order of selection by CPU: \n");
	int processes_done = 0;
	int index = 0;
	
	while(processes_done != q->size){
		
		if((q->RR)[index].CPU_burst_time >0){
			fprintf(fp, "%s ", (q->RR)[index].id);
		
			/*save when process was first picked up from queue*/
			if((q->RR)[index].picked_up == 0){
				(q->RR)[index].time_picked_up_from_q = q-> current_time;
				// set boolean
				(q->RR)[index].picked_up = 1;}
			
			//if quantum time is greater than time left for the process
			if((q->RR)[index].CPU_burst_time <= q->tq){
				//update current time
				q-> current_time = q-> current_time + (q->RR)[index].CPU_burst_time;
				(q->RR)[index].CPU_burst_time = 0;
				(q->RR)[index].turnaround_time =(q-> current_time) - ((q->RR)[index].time_picked_up_from_q);
				processes_done++;
			}
			
			else if ((q->RR)[index].CPU_burst_time > (q->tq)){
			(q->RR)[index].CPU_burst_time = (q->RR)[index].CPU_burst_time - (q->tq);
			q-> current_time = q-> current_time + (q->tq);
			
			}}
		
		index++;
		if(index == q->size ){
			index = 0;}
	}
	
	fprintf(fp, "\n");	
	fprintf(fp, "\nTurnaround times for each process: \n");
	for(int j= 0; j < q->size; j++){
		fprintf(fp, "%s = ", (q->RR)[j].id);
		fprintf(fp, "%d  \n", (q->RR)[j].turnaround_time);
	}
	
	};



int main(void){
	
	FILE *fptr;
	
	/*open file for reading */
	if ((fptr = fopen("cpu_scheduling_input_file.txt", "r")) == NULL) {
		printf("ERROR opening file!");
		exit(1);
		}
	/* open file for writing*/
	FILE *fp;
	fp = fopen("cpu_scheduling_output_file.txt", "w");
	
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	int line_count = 0;
	ssize_t line_size;
	
	line_size = getline(&line_buf, &line_buf_size, fptr);
	
	while (line_size >= 0){
		line_count++;
		
		/* get queue name */
		char queue_name [1];
		strncpy(queue_name, &(line_buf[2]), 2);
		int name = atoi(queue_name);
		/* get quantum time for RR*/
		char qt[2];
		strncpy(qt, &(line_buf[6]), 3);
		int qtime = atoi(qt);
		struct Queue q = {name, 0, qtime, 0, NULL, NULL,NULL};
		
		/* initialize*/
		q = initialize_queue(&(line_buf[9]), q);
		
		//execute
		fprintf (fp, "Ready Queue %d Applying FCFS SCheduling: \n\n", q.name);
		fcfs(fp, &q);

		fprintf (fp, "\nReady Queue %d Applying SJF SCheduling: \n\n", q.name);
		sjf(fp, &q);

		fprintf (fp, "\nReady Queue %d Applying RR SCheduling: \n\n", q.name);
		rr(fp, &q);

		fprintf(fp, "\n\n\n");
	        free(q.FCFS);
		free(q.SJF);
		free(q.RR);	
		line_size = getline(&line_buf, &line_buf_size, fptr);
	}
	fclose(fp);
	fclose(fptr);
	return 0;
}



