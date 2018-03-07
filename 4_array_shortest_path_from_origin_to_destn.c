/*
Given a boolean 2D matrix (0-based index), find whether there is path from (0,0) to (x,y) and if there is one path, print the minimum no of steps needed to reach it, else print -1 if the destination is not reachable. You may move in only four direction ie up, down, left and right. The path can only be created out of a cell if its value is 1.

Input:
The first line of input contains an integer T denoting the no of test cases. Then T test cases follow. Each test case contains two lines . The first line of each test case contains two integers n and m denoting the size of the matrix. Then in the next line are n*m space separated values of the matrix. The following line after it contains two integers x and y denoting the index of the destination.

Output:
For each test case print in a new line the min no of steps needed to reach the destination.

Constraints:
1<=T<=100
1<=n,m<=20

Example:
Input:
2
3 4
1 0 0 0 1 1 0 1 0 1 1 1
2 3
3 4
1 1 1 1 0 0 0 1 0 0 0 1
0 3
Output:
5
3
*/

#include<stdio.h>
#include<string.h>
#include<limits.h>
#define MAX_ROW 20
#define MAX_COLUMN 20


typedef struct{
    int x;
    int y;
}pair;


int is_equal(pair point1, pair point2) {
    return (point1.x == point2.x) && (point1.y == point2.y);
}

int shortest_path(pair from_point, pair to_point, int path_matrix[MAX_ROW][MAX_COLUMN], int visited_matrix[MAX_ROW][MAX_COLUMN], int shortest_path_matrix[MAX_ROW][MAX_COLUMN], pair size) {
    //decide exit points
    if(from_point.x < 0 || from_point.x >= size.x) {
        return INT_MAX; //we are trying to go out of the matrix
    }
    if(from_point.y < 0 || from_point.y >= size.y) {
        return INT_MAX; //we are trying to go out of the matrix
    }
    if(path_matrix[to_point.x][to_point.y] == 0) {
        return INT_MAX; //no path exists :/
    }
    if(path_matrix[from_point.x][from_point.y] == 0) {
        return INT_MAX; //no path exists :/
    }
    
    if( (from_point.x == to_point.x) && (from_point.y == to_point.y)) {
        return 0;
    }
    
    if(visited_matrix[from_point.x][from_point.y] == 1) {
        return INT_MAX; //already visited. stop cycling . this is not a valid path
    }
    
    pair traverse_point;
    int short_path_hop = INT_MAX;
    //check if already memoized
    if(shortest_path_matrix[from_point.x][from_point.y] < INT_MAX) {
        return shortest_path_matrix[from_point.x][from_point.y];
    }
    //mark as visited
    visited_matrix[from_point.x][from_point.y] = 1;
    
    //check if we can traverse to TOP
    traverse_point.x = from_point.x - 1;
    traverse_point.y = from_point.y;
    if(is_equal(traverse_point, to_point)) {
        return 1;
    }
    short_path_hop = shortest_path(traverse_point, to_point, path_matrix, visited_matrix, shortest_path_matrix, size);
    if(shortest_path_matrix[from_point.x][from_point.y] > short_path_hop) {
        shortest_path_matrix[from_point.x][from_point.y] = short_path_hop + 1;
    }
    //check if we can traverse to LEFT
    traverse_point.x = from_point.x;
    traverse_point.y = from_point.y - 1;
    if(is_equal(traverse_point, to_point)) {
        return 1;
    }
    short_path_hop = shortest_path(traverse_point, to_point, path_matrix, visited_matrix, shortest_path_matrix, size);
    if(shortest_path_matrix[from_point.x][from_point.y] > short_path_hop) {
        shortest_path_matrix[from_point.x][from_point.y] = short_path_hop + 1;
    }
    //check if we can traverse to RIGHT
    traverse_point.x = from_point.x;
    traverse_point.y = from_point.y + 1;
    if(is_equal(traverse_point, to_point)) {
        return 1;
    }
    short_path_hop = shortest_path(traverse_point, to_point, path_matrix, visited_matrix, shortest_path_matrix, size);
    if(shortest_path_matrix[from_point.x][from_point.y] > short_path_hop) {
        shortest_path_matrix[from_point.x][from_point.y] = short_path_hop + 1;
    }
    //check if we can traverse to BOTTOM
    traverse_point.x = from_point.x + 1;
    traverse_point.y = from_point.y;
    if(is_equal(traverse_point, to_point)) {
        return 1;
    }
    short_path_hop = shortest_path(traverse_point, to_point, path_matrix, visited_matrix, shortest_path_matrix, size);
    if(shortest_path_matrix[from_point.x][from_point.y] > short_path_hop) {
        shortest_path_matrix[from_point.x][from_point.y] = short_path_hop + 1;
    }
    
    //once traversal completed; mark as unvisited
    visited_matrix[from_point.x][from_point.y] = 0;
    return shortest_path_matrix[from_point.x][from_point.y];
}

int shortest_path_from_origin(int arr[][MAX_COLUMN], pair size, pair destn)  {
    int visited[MAX_ROW][MAX_COLUMN];
    int short_path[MAX_ROW][MAX_COLUMN];
    memset(visited,0, sizeof(int) * MAX_ROW * MAX_COLUMN);
    for(int i=0; i<size.x; i++) {
        for(int j=0; j<size.y; j++) {
            short_path[i][j] = INT_MAX;
        }
    }
    pair origin = {.x=0, .y=0};
    return shortest_path(origin, destn, arr, visited, short_path, size);
}

int main() {
    int n_test_cases;
    int arr[MAX_ROW][MAX_COLUMN];
    scanf("%d",&n_test_cases);
    while (n_test_cases--) {
        pair size;
        pair destn;
        memset(arr,0, sizeof(int) * MAX_ROW * MAX_COLUMN);
        scanf("%d %d",&size.x,&size.y);
        for(int i=0; i < size.x; i ++) {
            for(int j=0; j<size.y; j++) {
                scanf("%d",&arr[i][j]);
            }
        }
        scanf("%d %d",&destn.x,&destn.y);
        int short_path_size = shortest_path_from_origin(arr,size,destn);
        if(short_path_size == INT_MAX) {
            short_path_size = -1;
        }
        printf("%d\n",short_path_size);
    }
    return 0;
}

/*
 3 15
 
 1 1 1 0 0 0 0 1 1 1 1 1 0 1 1
 1 1 1 1 0 0 0 0 1 1 0 0 0 1 1
 0 0 0 0 0 1 0 0 0 1 1 1 0 0 0
 
 2 3
 */

/*
 3 1
 0 1 1
 0 0
 */


/*
 2 6
 1 1 1 0 1 0 0 1 1 0 1 0
 0 0
 */
