
#include <stdlib.h>
#include <stdio.h>


int apply_kernel ( int img_rows, int img_cols, double* img, int kernel_size, double* kernel, double** result_img ) {
    // Check that the kernel size is oddd
    if( kernel_size % 2 == 0 ) {
        //~ some error handling
    }
    
    // compute delta
    int delta = (kernel_size - 1)/2;

    // allocate memory for result
    int result_rows = img_rows - 2 * delta;
    int result_columns = img_cols - 2 * delta;
    double* result = malloc( ( result_rows ) * ( result_columns ) * sizeof( double ) );
    printf("result_rows: %d\n", result_rows);
    printf("result_cols: %d\n", result_columns);
    
    for ( int r = 0; r < img_rows; r += 1 ) {
        printf("\nr > %d",r);
        int kernel_row_start_index = 0 > r - ( (img_rows - 1) - delta ) + 1 ? 0 : r - ( (img_rows - 1) - delta ) + 1;

        int kernel_row_range;
        if ( r <= delta ) {
            kernel_row_range = r + 1;
        } else if ( r >= (img_rows - 1) - delta ) {
            kernel_row_range = (img_rows - 1) - r + 1;
        } else {
            kernel_row_range = kernel_size;
        }
        printf(" -- k_row_s_index: %d, k_row_range: %d\n", kernel_row_start_index, kernel_row_range);
        // for each reachable row in the kernel
        for ( int kr = kernel_row_start_index; kr < kernel_row_start_index + kernel_row_range; kr += 1 ) {
            
            for ( int c = 0; c < img_cols; c += 1 ) {
                printf("  c > %d", c);
                int kernel_column_start_index = 0 > c - ( (img_cols - 1) - delta ) + 1 ? 0 : c - ( (img_cols - 1) - delta ) + 1;

                int kernel_column_range;
                if ( c <= delta ) {
                    kernel_column_range = c + 1;
                } else if ( c >= (img_cols - 1) - delta ) {
                    kernel_column_range = (img_cols - 1) - c + 1;
                    
                } else {
                    kernel_column_range = kernel_size;
                }
                printf(" -- k_col_s_index: %d, k_col_range: %d\n", kernel_column_start_index, kernel_column_range);
                for ( int kc = kernel_column_start_index; kc < kernel_column_start_index + kernel_column_range; kc += 1 ) {
                    double product = img[ img_cols * r + c ] * kernel[ kernel_size * kr + kc ];
                    int r_prime = r + delta - kr;
                    int c_prime = c + delta - kc;
                    int result_row = r_prime - delta;
                    int result_column = c_prime - delta;
                    result[ result_columns * result_row + result_column ] += product;
                    printf("-> r'=%d, c'=%d\n", r_prime, c_prime);
                    printf("-> u=%d, v=%d\n", result_row, result_column);
                    printf(">> r=%d,c=%d | kr=%d, kc=%d   %d: %f (%f x %f) -- %d\n", r,c,kr,kc,result_columns * result_row + result_column, product,img[ img_rows * r + c ],kernel[ kernel_size * kr + kc ],img_cols * r + c);
                }
            }


        }
    }
    *result_img = result;
    printf("\nresult_img_r:%p\n", result_img);
    return 0;
}

int main() {
    
    // TEST
    // Change the numbers to verify that the kernel is applied correctly
    double kernel[9] = {1.0,2.0,3.0,
                     4.0,5.0,6.0,
                     7.0,8.0,9.0};
    
    double image[30] = {1.0,1.0,1.0,1.0,1.0,
                     1.0,1.0,1.0,1.0,1.0,
                     1.0,1.0,1.0,1.0,1.0,
                     1.0,1.0,1.0,1.0,1.0,
                     1.0,1.0,1.0,1.0,1.0,
                     1.0,1.0,1.0,1.0,1.0};
    int j = 0;
    for (int i=0; i < 30; i += 1){
        j++;
        printf("%d : %f\n",j,image[i]);
    }
    printf("==================================================================================\n");

    double* r;
    printf("r:%p\n", r);
    apply_kernel(6,5, image, 3, kernel, &r);
    printf("r:%p\n", r);
    printf("\n\n");
    int count = 0;
    for (int i=0; i <12; i += 1) {
        printf("%2.1f ", r[ i ] );
        count += 1;
        if(count == 3) {
            printf("\n");
            count = 0;
        }
    }

    return 0;
}
