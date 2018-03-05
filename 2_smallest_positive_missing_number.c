/*
 You are given an unsorted array with both positive and negative elements. You have to find the smallest positive number missing from the array in O(n) time using constant extra space.
 
 Input:
 First line consists of T test cases. First line of every test case consists of N, denoting the number of elements in array. Second line of every test case consists of elements in array.
 
 Output:
 Single line output, print the smallest positive number missing.
 
 Constraints:
 1<=T<=100
 1<=N<=100
 
 Example:
 Input:
 2
 5
 1 2 3 4 5
 5
 0 -10 1 3 -20
 Output:
 6
 2
*/

#include<stdio.h>
#define DEBUG 0
/*
    We need to understand that if the size of the array is N, the chances of least positive number lying
    outside of range 1...N is possible ONLY if all indices (0...N-1) are all filled by numbers 1...N itself
    So , we can start hashing between 1...N and then traverse that hash array for least positive missing number.
    If no number is missed out , then N+1 is the answer .
 */
int smallest_positive_missing_number(int arr[], int size) {
    int hash_arr[size];
    for(int i=0; i<size; i++) {
        hash_arr[i] = 0;
    }
    //start hashing
    for(int i=0; i<size; i++) {
        if( (arr[i] > 0) && (arr[i] <= size) ) {
            hash_arr[arr[i]-1] = -1;
        }
    }
    int smallest_positive_missing_number = size+1;
    for(int i=0;i<size;i++) {
        if(hash_arr[i] != -1) {
            smallest_positive_missing_number = i + 1;
            break;
        }
    }
    return smallest_positive_missing_number;
}

int main() {
    int num_test_cases;
    scanf("%d", &num_test_cases);
    while(num_test_cases --) {
        int arr_size;
        scanf("%d",&arr_size);
        int arr[arr_size];
        for(int i=0; i<arr_size; i++) {
            scanf("%d",arr+i);
        }
#if DEBUG
        for(int i=0; i<arr_size; i++) {
            printf("%d\t",arr[i]);
        }
        printf("\n");
#endif
        printf("%d\n",smallest_positive_missing_number(arr,arr_size));
    }
	return 0;
}


/*
 93
 45 -7 -6 -21 40 32 -10 -9 19 -24 -18 11 -8 10 -33 -27 11 31 -41 40 -25 46 17 27 -16 40 -24 -26 7 -36 18 -45 8 -38 36 -50 -4 -24 44 -34 2 28 -21 -4 40 -3 20 1 30 -19 43 7 -23 -38 36 -36 5 -38 40 -38 29 -40 19 39 24 5 -9 -30 -17 37 38 -12 16 20 34 6 -33 -44 10 -1 -13 -45 9 -33 -32 -5 33 23 8 23 -13 39 33
 */
