//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name :Caleb Lee
 * UCLA ID : 305330193
 * Email :bkcaleb45@ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k, u, v, w,store,store2,store3,store4;
  int ton = 0;
  int a_secret = 5;
  int was_smart = 16;
  long compute_it, moving_average;
  double pi, pi2, x , y, sum, step = 0.0;
  double x1,y1;
  double r=1.0;
  double r1 = r*r;
  long dot_product,t=0;
  long nCirc = 0;
  long aggregate=1.0;
  long temp, temp1;

  for(i = 0; i < DIM-2;i+=2){
	temp = simple[i];
	temp1 = simple[i+1];
	super[i] +=temp;
	super[i+1] +=temp1;
  }
  for(; i < DIM-1; i++){
	super[i] +=simple[i];
  }

  for(i=0; i<DIM-1;i++)
  {
    dot_product += (super[i]*simple[i]);
    
    moving_average = 0;
    for(ton=i;ton<DIM-1-WINDOW_SIZE;ton++)
    {
      moving_average += simple[ton];
    }
  }

  fibonacci[0] = 1;
  fibonacci[1] = 1;
  for(i=2; i<DIM-2;i+=2)
  {
    temp1 = fibonacci[i-1];
    temp = fibonacci[i] = temp1+fibonacci[i-2];
    fibonacci[i+1]=temp+temp1;   
    if(i==3||i+1 == 3)
    {
      printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));
    }
  }

  step = 1.0 / NUM_STEPS;
#pragma omp parallel for private(x) reduction(+:sum) 
 for (i=0;i<NUM_STEPS; i++)
  {
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 

  for(i=0;i<NUM_TRIALS-1; i+=2)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    x1 = (random()%10000000)/10000000.0;
    y1 = (random()%10000000)/10000000.0;

    if (( x*x + y*y) <= r1) {
      nCirc++;
    }
    if((x1*x1 + y1*y1) <=r1){
      nCirc++;
    }
  }
  for(;i<NUM_TRIALS; i++){
    x = (random()%10000000)/10000000.0;
    y = (random()%10000000)/10000000.0;
    if ((x*x + y*y) <= r1) {
      nCirc++;
    }
  } 
  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 

  for (i=1; i<DIM-1; i++) {
	store = i*DIM*DIM;
    for (j=1; j<DIM-1; j++) {
        store2 = store+j*DIM;
      for (k=1; k<DIM-1; k++) {
        compute_it = old[store2+k] * we_need_the_func();
        aggregate+= compute_it / gimmie_the_func();
      }
    }
  }

  printf("AGGR:%ld\n",aggregate);
 #pragma omp parallel for private(j,k,u,v,w,store3,store,store2,store4,t)
  for (i=1; i<DIM-1; i++) {
	store = i*DIM*DIM;
    for (j=1; j<DIM-1; j++) {
        store2 = store+j*DIM;
      for (k=1; k<DIM-1; k++) {
          store3=store2+k;
          new[store3]=0;
        for (u=-1; u<=1; u++) {
          for (v=-1; v<=1; v++) {
            store4 = (i+u)*DIM*DIM+(j+v)*DIM;
            for (w=-1; w<=1; w++) {
               t+=old[store4+(k+w)];
            }
          }
        }
        new[store3] = t/27;
	t = 0;
      }
    }
  }

  for (i=1; i<DIM-1; i++) {
	store = i*DIM*DIM;
    for (j=1; j<DIM-1; j++) {
	store2 = store+j*DIM;
      for (k=1; k<DIM-1; k++) {
        	u=(new[store2+k]/100);
        	if (u<=0) u=0;
        	if (u>=9) u=9;
        	histogrammy[u]++;
	    }
          }
  }

  return (double) (dot_product+moving_average+pi+pi2);
}
