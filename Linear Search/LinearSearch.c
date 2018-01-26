#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/timeb.h>
#include"plotsdl/llist.h"
#include"plotsdl/plot.h"
#include"LabArc.h"

/* Plotter Structures Decl. Start*/
 captionlist caption_list = NULL;
 coordlist coordinate_list=NULL;
 plot_params params;
/* Plotter Structures Decl. End*/

int BEST_CASE[7];
int WORST_CASE[7];
int AVG_CASE[7];

int getRandRange(int x,int y)
{
    return (rand()%(y-x)+x);
}

void init_plotterLab1()
{
    caption_list=push_back_caption(caption_list,"Search Time",0,0xE1620C);
    params.screen_width=1366;
    params.screen_heigth=700;
    params.plot_window_title="Charanjit Singh";
    params.font_text_size=18;
    params.caption_text_x="Number of Elements";
    params.caption_text_y="Average time for Searching";
    params.caption_list = caption_list;
    params.scale_x = 400;
    params.font_text_path="opensans.ttf";
    params.scale_y = 1;
    params.max_x = 6500;
    params.max_y = 1;
}

int search_function(int key,int *a,int n,int l)
{
int i;
int FOUND=0;
int comparison=0;
    for( i=0; i<n; i++)
    {comparison++;

      //  printf(" ");  //To get an appropriate delay
        fflush(stdout);
        if(a[i]==key)
        {
        FOUND = 1;
            break;

        }
    }
    if(FOUND)
    {
    if (i==0||i==1)
    {
    BEST_CASE[l]++;

    AVG_CASE[l]--;

    }
    if (i>(n-5))
    {
    WORST_CASE[l]++;
    }
    else
    {
    AVG_CASE[l]++;
    }
    }
    else
    WORST_CASE[l]++;
    return comparison;
}
int Lab1(int argc, char* argv[])
{
srand(time(NULL));//Seeding The time
    clock_t start_milli,end_time; //Temporary variables Storing start and End time

    init_plotterLab1(); //Initialising the plotter Structures
    for(int i=0;i<7;i++)
    {
    BEST_CASE[i]=0;
    AVG_CASE[i]=0;
    BEST_CASE[i]=0;
    }

    double timings[7];
    long long int comparisons[7];
    for(int i=0;i<7;i++)
    comparisons[i]=0;
    int k=0;
    for(int numberOfElements=100, l=0; numberOfElements<=6400;l++, numberOfElements*=2)
    {
        double time_taken_for_this_number=0;
        for(int loop=0; loop<1500; loop++)
        {
            int *arr;
            arr=(int *)malloc(sizeof(int)*numberOfElements);
            for(int i=0; i<numberOfElements; i++)
            {
                arr[i]=0*getRandRange(10,1500);
            }
            int key=0;//getRandRange(10,1500);
            //Start Clock
            start_milli=clock();
            comparisons[l]+=search_function(key,arr,numberOfElements,l);
            //Stop Clock
            end_time=clock();
            double time_taken=(double)end_time-start_milli;
            //time_taken*=100;   //Convert Clock into units
            time_taken_for_this_number+=time_taken;
            free(arr);
        }
        timings[k]=time_taken_for_this_number/1500;
        time_taken_for_this_number=0;
        k++;
    }

    k=50;   //X co-ordinate Variable
    for(int i=0; i<7; i++)
    {
        k=k*2;
        //printf("\nk=%d ",k);
        coordinate_list=push_back_coord(coordinate_list,0,k,timings[i]);
        //printf("%f",timings[i]);

    }

    params.coordinate_list = coordinate_list;
    for(int i=0,k=100;i<7;k*=2,i++)
    {
    printf("\n[%d ] B: %3d | A: %3d | W: %3d | TC:%8lld\n",k,BEST_CASE[i],AVG_CASE[i],WORST_CASE[i],comparisons[i]);
    }
    return  plot_graph(&params);
    }
