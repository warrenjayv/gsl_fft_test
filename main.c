/* author: wjv
 * github.com/warrenjayv
 * date: 07-19-2021
 * dev notes: 
 *    GNU GSL 
 *    GNU PLOT
 * output: 
 *     fft.plot 
 *  sample.plot 
 * 
 *  plot with GNU PLOT 
 *  user@host$ plot "fft.plot" with lines 
 */
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_fft_complex.h>
#include <math.h> 

#define REAL(z, i) ((z)[2*(i)])
#define IMAG(z, i) ((z)[2*(i)+1])

/* injector properties */
#define _AMP 1 //amplitude of our sample
#define _CYC 5 //number of cycles
	
/* int main () */
int
main ( void ) {

	/* output file */
	FILE *out, *sample;  

	/* open file for write / read */
	out = fopen("fft.plot", "w"); 
	sample = fopen("sample.plot", "w"); 

	/* iterator */
 	int i;

	/* magnitude */
	double mag = 0.0 ; 

	/* frequency bin size */
	/* sample rate / number of samples */
	double sample_rate = 1 / (1024.00 * 0.005) ; 
	
	printf("sample rate: %f\n", sample_rate); 
		
	/* samples */
    double data[2*1024]; 

    /* generate data to NULL */
    for (i = 0; i < 1024; i++) {
       REAL(data, i) = 0.0; IMAG(data, i) = 0.0;
    }//for(){}

	/* DC COMPONENT */
	/* we don't need to plug in the DC component for the sample 
    REAL(data, 0) = 1.0;
	for( i = 1; i <= 100; i++) 
	{
	 	* look at this recursion thats pretty amazing *
		REAL(data, i) = REAL(data, 1024-i) = 1.0;
	}
	*/

	/* inject a 5 hz  sample */
	for ( i = 0; i < 1024; i++ ) {	

		/* store the data */		
		if (i < 361) {
      		data[i] = _AMP * sin ( _CYC * i  * ( M_PI / 180 )); 
		} else if (i > 692) {
			data[i] = _AMP * sin ( 10 * _CYC * i * ( M_PI / 180 )); 
		} else { 
			data[i] = 0; 
		}
		
		/* print out the data */
		 fprintf(sample, "%d %e \n", i, data[i]); 	
		
	}//for(){}
	
	/* PRINT SAMPLES */

	/* inject sample of 100 hz at 10 magnitude */
	/*
	 * REMOVE INJECTOR ROUTINE 
	injector ( data ); 

	for(i = 0; i < (2*1024); i++) {
		fprintf(out, "%d %e\n", i, data[i]); 
	}
	*/

	/* DC COMPONENT */
	// REAL(data, 0) = 1.0; 


	/* TERMINAL PRINT DISABLED 
	for (i = 0; i < 128; i++) {
		printf("%d %e %e\n", i, REAL(data, 128), IMAG(data, i)); 
	}//for(){}	
	printf("\n\n"); 
	*/
		
	/* FFT algorithm */
	gsl_fft_complex_radix2_forward (data, 1, 1024 ); 

	printf("OUTPUT DATA: \n"); 


	/* WRITE TO TERMINAL & FILE  a*/
	for (i = 0; i < 512; i++  ) 
    {
		//printf("%d %e %e\n", i, REAL(data, i)/sqrt(1024), 
                               //  IMAG(data, i)/sqrt(1024));

		/* scale the frequency in the first half by 2 */
	
		/* obtain magnitude */
		mag = sqrt(REAL(data, i) * REAL(data, i) + IMAG(data, i) * IMAG(data, i)); 
		mag = mag/1024; 

		fprintf(out, "%f %e \n", sample_rate * i, mag); 
                                 
    }//for(){}

	/* notify */
	printf("file 'fft.plot' generated for gnuplot\n"); 

	/* close file */
	fclose(out); 
	fclose(sample); 

	return 0; 
}
