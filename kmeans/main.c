#include <stdio.h>
#include <math.h>

int main() {
	char infile[100];
	char outfile[100];
	int k = 0;
//	printf("Please enter the name of the input file containing the data to be clustered:\n");
//	scanf("%99s", &infile);
	printf("Please enter the value of k:\n");
	scanf("%d", &k);
//	printf("Please enter the name of the output file:\n");
//	scanf("%99s", &outfile);
	
	FILE *fpRead = NULL;
	FILE *fpWrite = NULL;
	
	int num, dim;
	int i, j;
 
	fpRead = fopen("test.txt", "r");  // infile   "faithful-Kmeans.txt"
	fpWrite = fopen("labeled-data.txt", "w"); //outfile

	if (fpRead == NULL) {
		printf("Error opening file.\n");
	} else {
		if ( !feof(fpRead) ) {
			fscanf(fpRead, "%d %d", &num, &dim);
			//printf("%d %d\n", num, dim);
			
			fprintf(fpWrite, "%d %d %d\n", num, dim, k);
			
			double A[num][dim]; //store the coordinate into an 2-d array
			for ( i=0; i<num; i++ ) { //each row represent a datapoint
				for ( j=0; j<dim; j++ ) { // each column of a row represent the different dimension of a datapoint
					fscanf(fpRead, "%lf", &A[i][j]);
				}
			}
			fclose(fpRead);
			
			int cluster[num];  // each row correspond to the cluster of the same data in the same row of A
			for ( i=0; i<num; i++) {
				cluster[i] = 0;
			}
			
			double centroid[k][dim]; // each row represent a centroid
			for ( i=0; i<k; i++) {  //choose the first k coordinates to be the starting centroid
				for (j=0; j<dim; j++) {
					centroid[i][j] = A[i][j];
					//printf("%f ", centroid[i][j]);
				}
			}
			//printf("\n");
			
			int cnt = 0;
			while(cnt<20){
				int ii, jj;
                double sumDist = 0;
                double var = 0;
                
				for (ii=0; ii<num; ii++){
					double dist[k]; // store the distance between each datapoint and k centroids
					for ( i=0; i<k; i++) {
						dist[i] = 0;
					}
					for (i=0; i<k; i++) {
						for (jj=0; jj<dim; jj++) {
							dist[i] += pow((A[ii][jj]-centroid[i][jj]), 2);
						}
                        sumDist += dist[i];
						//printf("\n%f", dist[i]);
					}
					int min = dist[0];
					int index = 0;
					for (i=0; i<k; i++) {
						if (dist[i]<min) { // find the minimum distance from a datapoint to one of the centroids
							min = dist[i];
							index = i;
						}
					}
					cluster[ii] = index;	//mark the cluseter of each point
					//printf("\n%d", cluster[ii]);
                    
				}
                var = sumDist/num;
                //printf("sum of varience:%lf \n", var);
                
                
				for (i=0; i<k; i++) {
					for (j=0; j<dim; j++) {
						int sum = 0;
						centroid[i][j] = 0;
						for (ii=0; ii<num; ii++) {							
							if ( cluster[ii]==i) {
								sum++;
								centroid[i][j] += A[ii][j];
							}							
						}
						centroid[i][j] /= sum;
					}
					printf("%f %f\n", centroid[i][0], centroid[i][1]);
				}
				//printf("\n");
				cnt++;
			}
			
			// output type 1
			for (i=0; i<num; i++) {
				for (j=0; j<dim; j++) {
					fprintf(fpWrite, "%f ", A[i][j]);
				}
				fprintf(fpWrite, "%d\n", cluster[i]);
			}
			
//			// output type 2
//			for (j=0; j<dim; j++) {
//				for (i=0; i<num; i++) {
//					fprintf(fpWrite, "%f ", A[i][j]);
//				}
//				fprintf(fpWrite, "\n");
//			}
//			for (i=0; i<num; i++) {
//				fprintf(fpWrite, "%d ", cluster[i]);
//			}
						
		}
		
	}
	
	fclose(fpRead);
	fclose(fpWrite);
	
	return 0;
}
