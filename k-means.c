#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int dim=0,n,nclus,cen[20],cluster[20][20]={-1};
float dist[20][20]={0},a[20][5];

int centroids(int x)
{
 int i,j,selcount=0,flag=0,maxdist=0;
 int sel[20],max;
 float d[20]={0};
 //printf("\n\n");
 
		for(j=0;j<20;j++)
			{flag=0;
			 for(i=0;i<x;i++)
					{if(j==cen[i])
						{ flag=1;
		 	 			}
					}
		 	 if(flag==0)
 	 	 			{
 	 	 			sel[selcount]=j;
 	 				selcount++;
 	 	 			}
					
			  
			}
				
for(i=0;i<selcount;i++)
	{
	 for(j=0;j<x;j++)
	 	 d[sel[i]]+=dist[sel[i]][cen[j]];	 
	}
/*	printf("\n");

for(i=0;i<selcount;i++)
	{
	printf("%f ",d[sel[i]]);
	 
	}*/
for(i=0;i<selcount;i++)
	{
		if(d[(sel[i])]>maxdist)
			{maxdist=d[(sel[i])];
			 max=sel[i];
			}
	}
//printf("\nMax is %d data item ",max);
return max;
}
 
/*void kmean()
{int i,j,k,min[5];
	for(i=0;i<5;i++)
		{min[i]=100;
		 k=0;
			for(j=0;j<nclus;j++)
				{
					if((dist[i][cen[j]]<min[i]) && (dist[i][cen[j]]>0))
						{min[i]=dist[i][j];
						 cluster[j][k]=i;
						 k++;
						}						
				}	
		}
	printf("\nClusters are as follows \n" );
	for(i=0;i<nclus;i++)
		{
			printf("\nCluster %d  " ,i+1);
			for(j=0;j<10;j++)
				{
					if(cluster[i][j]!=-1)
						printf("%d ",cluster[i][j]);
				}
			
		}
			
}*/

main()
{
	
	float data[20][5]={0};
	float sum[5]={0,0,0,0,0};
    float mean[5];
	float var[5]={0,0,0,0,0};
	float ssum[5]={0,0,0,0,0};
	int i,j,k,clcount;
	float maxdist=0;	
	int selected[5]={0,0,0,0,0};
	float meanofvar=0,sumofvar=0;
	
	printf("\nEnter no of data items(data attibutes size taken as 5) ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
		{for(j=0;j<5;j++)
			{
				data[i][j]= (int) rand()%20;
			}
		}
	for(j=0;j<5;j++)
		{for(i=0;i<n;i++)
			{
				sum[j]+=data[i][j];
				
			}
			mean[j]=sum[j]/5;
		}
	for(i=0;i<n;i++)
		{for(j=0;j<5;j++)
			{
				printf("%.2f  ",data[i][j]);
				
			}
		printf("\n");
		}
	
	for(j=0;j<5;j++)
		{for(i=0;i<n;i++)
			{
				ssum[j]+=((data[i][j]-mean[j])*(data[i][j]-mean[j]));
				
			}
			var[j]=ssum[j]/5;
		}	
	printf("\n\n");
	for(j=0;j<5;j++)
		{printf("Mean:%.2f\tSum:%.2f ",mean[j],sum[j]);
		 printf("\tsquared-sum:%.2f \tVariance : %.2f\n",ssum[j],var[j]);
		}
	
	
	for(k=0;k<5;k++)
		{		
			sumofvar+=var[k];		
		}

	meanofvar=sumofvar/5;
	printf("\nMean of var=%.2f ",meanofvar);
	
	for(j=0;j<5;j++)
		{
			if(var[j]>meanofvar)
				selected[j]=1;
		}
	printf("\n\nBy means of PCA, following attributes were omitted from k-means custering :\t");
	for(k=0;k<5;k++)
		if(selected[k]==0)
			printf("Attribute %d  ",k+1);

	printf("\n\nThe reduced data set is : \n");

	for(i=0;i<n;i++)
		{dim=0;
		 for(j=0;j<5;j++)
			{
				if(selected[j]==1)
					{//printf("%f ",data[i][j]);
					 a[i][dim]=data[i][j];
					 dim++;
					}
					
			}
				//printf("\n");
		}
		for(i=0;i<n;i++)
			{for(j=0;j<dim;j++)
				{printf("%.2f ",a[i][j]);
				}
			 printf("\n");
			}
		
	for(i=0;i<n;i++)
		{for(j=0;j<n;j++)	
			{
			 if(i==j)
				dist[i][j]=0;
			else
				{
					for(k=0;k<dim;k++)
						dist[i][j]+=(a[j][k]-a[i][k])*(a[j][k]-a[i][k]);
					dist[i][j]=sqrt(dist[i][j]);
				}				
			}
		}
	
	printf("\n\n Distance matrix for data points is \n");
	for(i=0;i<n;i++)
		{for(j=0;j<n;j++)
			{printf("%.2f  ",dist[i][j]);
			}
		 printf("\n");
		}
		
	printf("\nEnter no. of clusters : ");
	scanf("%d",&nclus);
	for(i=0;i<n;i++)
		{for(j=0;j<n;j++)	
			{ if(dist[i][j]>0)
					{if(dist[i][j]>maxdist)
					 		{maxdist=dist[i][j];
					 		 cen[0]=i;
					 		 cen[1]=j;
					 		}
					}
			}
		}	
	if(nclus==1)
		printf("\nNo point in clsutering. All data sets belong to one cluster");
	else if(nclus==2)
		{printf("\n\nThe chosen initial centroids based on distances are data-items\n ");
		 printf("%d and %d \n",cen[0]+1,cen[1]+1);		
		}	
	else
		{		 
		 clcount=2;
		 while(clcount<nclus)
			{cen[clcount]=centroids(clcount);
			 clcount++;
			}
		printf("\n\nThe chosen initial centroids based on distances are data-items\n ");
		for(i=0;i<nclus;i++)
			printf("data-item %d ",cen[i]); 
		}
	//kmean();
}
