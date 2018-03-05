
/*
 Given a string, your task is to find the number of patterns of form 1[0]1 where [0] represents any number of zeroes (minimum requirement is one 0) there should not be any other character except 0 in the [0] sequence.
 
 
 
 Input:
 The first line contains T denoting the number of testcases. Then follows description of testcases. Each case contains a string.
 
 
 Output:
 For each test case, output the number of patterns.
 
 
 
 Constraints:
 1<=T<=20
 1<=Length of String<=2000
 
 
 Example:
 Input:
 2
 100001abc101
 1001ab010abc01001
 
 
 
 Output:
 2
 2
 */
#include<stdio.h>
#include<string.h>

#if 0 //The below logic uses O(N^2) time
int find_pattern_count(char *str) {
    int str_len = strlen(str);
    int pattern_start_index = 0;
    int pattern_count = 0;
    while(pattern_start_index < str_len) {
        if(str[pattern_start_index] != '1') {
            pattern_start_index ++;
            continue;
        }
        //found pattern_start = '1' , now check for sequence
        int pattern_search_index = pattern_start_index + 1;
        if(pattern_search_index >= str_len) {
            break;
        }
        while (pattern_search_index < str_len) {
            if(str[pattern_search_index] == '0') {
                //found 0, continue searching
                pattern_search_index++;
                continue;
            }else if(str[pattern_search_index] == '1' && (pattern_search_index - pattern_start_index > 1)) {
                //pattern found
                pattern_count++;
                //position pattern_start_index to pattern_search_index as it could be start of another sequence
                pattern_start_index = pattern_search_index;
            }else {
                //pattern search failed at an index, start new search from the failed index
                pattern_start_index = pattern_search_index;
                break;
            }
        }
    }
    return pattern_count;
}
#else //The below logic executes in O(N) time. We incorporate a State Maching here
int find_pattern_count(char *str) {
    int str_len = strlen(str);
    int state = 0, count = 0;
    //state = 0, indicates pattern sequence has not yet been identified
    //state = 1, indicates that the start of pattern  (starting 1) is reached
    //state = 2, indicates that it's in the state of consuming 0's
    //state = 3, indicates that the end of pattern (ending 1) is reached
    /*
        1) 0 to 1 is possible
        2) 1 to 0 and 1 to 2 is possible
        3) 2 to 0 and 2 to 3 is possible
        4) 3 to 0 ; 3 to 1 and 3 to 2 is possible
     */
    for(int index = 0; index < str_len; index ++) {
        if(state == 0) {
            if(str[index] == '1') {
                //move to state 1
                state = 1;
            }else {
                //stay at state 0
            }
        }else if(state == 1) {
            if(str[index] == '1') {
                //stay at state 1
            }else if(str[index] == '0') {
                //move to state 2
                state = 2;
            }else {
                //move back to state 0
                state = 0;
            }
        }else if(state == 2) {
            if(str[index] == '0') {
                //stay at state 2
            }else if(str[index] == '1') {
                //move to state 3 , increment sequence found count
                state = 3;
                count++;
            }else {
                //move back to state 0
                state = 0;
            }
        }else if(state == 3) {
            if(str[index] == '1') {
                //move to state 1
                state = 1;
            }else if(str[index] == '0') {
                //move to state 2
                state = 2;
            }else {
                //move to state 0
                state = 0;
            }
        }
    }
    return count;
}
#endif


int main() {
    int num_test_cases;
    scanf("%d",&num_test_cases);
    while (num_test_cases --) {
        char str[2000];
        scanf("%s",str);
        printf("%d\n",find_pattern_count(str));
    }
    return 0;
}
