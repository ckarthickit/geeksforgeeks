/********************** PROBLEM ***********************
Given an array of n positive integers and a number k. Find the minimum number of swaps required to bring all the numbers less than or equal to k together.

Input:
The first line of input contains integer T denoting the number of test cases. For each test case,  the first line of input contains an integer n denoting the size of the array. Next line contains n space separated integers denoting the elements of the array. Next line contains an integer k denoting the number such that elements less than and equal to k are group together. 

Output:
For each test case, the output is an integer displaying the minimum swaps required.

Constraints:
1<=T<=100
1<=n<=50

Example:
Input
2
5
2 1 5 6 3
3
7
2 7 9 5 8 7 4
6
Output
1
2

Explanation:
1. To bring elements 2, 1, 3 together, swap element '5' with '3' such that final array will be- arr[] = {2, 1, 3, 6, 5}
2. To bring elements 2, 5, 4 together, swap element 7 with 5 & 9 with 4 such that the final array will be {2,5,4,7,8,7,9}   
**********************************************/

/*************************************************************************************************************************/

#include<stdio.h>
#define printf(...) dummy()

void dummy() {
}
int minimum_swaps(int arr[], int size, int kValue) {
   int values_less_than_k = 0;
   for(int i = 0; i < size ; i++) { 
    //Find the number ofvalues less than or equal to K in array 
	if(arr[i] <= kValue) {
		values_less_than_k++;
    }
   }
   // we start with a window of size values_less_than_k 
   // and check all possible windows for minumum swap to achieve the result 
   int window_size = values_less_than_k;
   //worst case possibility : we have to swap the whole window 
   int min_swap = window_size;
   for(int win_start=0; (win_start + window_size - 1) <= size -1; win_start++) {
       int cur_swap = 0;	
       int win_ptr = win_start;
       int swap_ptr = (win_start + window_size - 1 == size -1)? win_start-1: size -1;
	   //Use 2 pointer technique to swap places		
       printf("win_start = %d, win_size=%d, swap_ptr=%d\n",win_start, (win_start+window_size -1),swap_ptr); 
	   while(swap_ptr >= 0 && (win_ptr <= size-1)) {
			while(arr[win_ptr] <= kValue){
				//win_ptr is less than or equal to kValue already, so move win_ptr to right
				win_ptr++; 
            }
            printf("arr[swap_ptr]= %d kValue=%d\n",arr[swap_ptr],kValue);
			if(arr[swap_ptr] <= kValue) {	
                printf("swap %d and %d\n",arr[win_ptr],arr[swap_ptr]);
				//do swap and move swap_ptr to left
				//increment swap count
				cur_swap++;
				//swap done , so move win_ptr as well
				win_ptr++;  
            }
			//moving swap_ptr to left
			swap_ptr--;
			if( (win_start <= swap_ptr) && (swap_ptr <= (win_start + window_size -1)) ){
                printf("skipping window \n");
				swap_ptr = win_start -1;
            }          
       	}
        printf("cur_swap = %d\n",cur_swap);
        if(cur_swap < min_swap) {
			min_swap = cur_swap;
        }
   }
   return min_swap;
}


int main() {
	int test_cases = 0;
    scanf("%d",&test_cases); 
    while(test_cases--) {
       int size_of_array; 
       int arr[50];
       int kValue = 0;
       int min_swaps = 0;
	   scanf("%d",&size_of_array); 
       for(int i =0; i < size_of_array; i++) {
			scanf("%d",arr+i);
       }
       scanf("%d",&kValue);
	   fprintf(stdout,"%d\n", minimum_swaps(arr, size_of_array, kValue));
    }
    return 0;
}


/*
12
353 371 305 352 256 373 121 300 318 67 53 450
208
*/