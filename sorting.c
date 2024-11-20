/**
 * @author Eliandro Pizzonia 
 * 
 * this program takes user input to sort an array of integers using Quick sort or Bubble sort
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// prototypes
void n_m_values();
void random_ints();
void diff_sorting();
void quick_sort();
int partition();
void swap();
void bubble_sort();
void menu();


/**
 * main method calls method to initialize n and m values
 */
int main(){
    n_m_values();
    return 0;
}


/**
 * this method initializes the 2d array using the n and m values specified by the user
 */
void n_m_values(){
    
    // receiving valid n value
    int n = 0;
    do{
        printf("Enter the number of elements you would like to eneter (n). n must be an even number: ");
        scanf("%d", &n);
    } while (n % 2 != 0);

    // receiving valid m value
    int m;
    do{
        printf("Enter the length of the array (m). must be an even number and >= n: ");
        scanf("%d", &m);   
    } while (m < n || m % 2 != 0);

    int numbers[2][m];
    int user_nums;
    int diff = m - n;

    // setting the users numbers to the first row of the array
    printf("Enter n elements: ");
    for(int i = 0; i < n; i++){
        scanf(" %d" , &user_nums);
        numbers[0][i] = user_nums;
    }

    // creating pointers to the rows of the array 
    int * unsort_row = numbers[0];
    int * sort_row = numbers[1];

    // call to method to add random ints
    random_ints(numbers[0],numbers[1], m, n, diff);
    return;
}


/**
 * @param unsort_row
 * @param sort_row
 * @param m
 * @param n
 * @param diff
 * 
 * this method adds (m - n) number of random ints to fill empty collumns in array
 */
void random_ints(int * unsort_row, int * sort_row, int m, int n, int diff){
    
    // adding random ints to array if empty collumns
    if (n < m){
            for (int i = n; i < m; i++){
                unsort_row[i] = rand() % 10001;
            }
    }

    // copying first row of the unsorted array to the second row of array
    for (int i = 0; i < m; i++){
                sort_row[i] = unsort_row[i];
        }

    printf("You entered %d numbers, %d random numbers will be generated.\n",n,diff);
    
    // call to sorting menu
    diff_sorting(unsort_row, sort_row, m, n, diff);
    return;
}


/**
 * @param unsort_row
 * @param sort_row
 * @param m
 * @param n
 * @param diff
 * 
 * this method allows the user to choose between quick sort or bubble sort
 */
void diff_sorting(int * unsort_row, int * sort_row, int m, int n, int diff){
    
    int sort_algo;
    printf("::Choose a sorting algorithm::\n");
    printf("|| (0)Quick sort | (1)Bubble sort ||\n");
    scanf("%d", &sort_algo);

    // validating the sorting algorithm user wants to use
    while (sort_algo != 0 && sort_algo != 1){
        printf("Invalid choice, try again!\n");
        printf("::Choose a sorting algorithm::\n");
        printf("|| (0)Quick sort | (1)Bubble sort ||\n");
        scanf("%d", &sort_algo);
    }
    
    // finding the lowest and highest index of the unsorted array
    int lowest = 0;
    int highest = m - 1;
    
    time_t time1;
    time_t time2;
    
    // start time for the sorting algorithm
    time1 = time(&time1);
    
    // printing the unsorted row (first row)
    printf("\nRaw array\n");
    for(int i = 0; i < m; i++){
       printf("%6d", unsort_row[i]);
    }

    // call to quick sort method and printing the sorted row (second row)
    while (sort_algo == 0){
        printf("\n\nSorted array\n");
        quick_sort(sort_row,m,lowest,highest);
        for(int i = 0; i < m; i++){
            printf("%6d", sort_row[i]);
        }
        break;
    }

    // call to the bubble sort method and printing the sorted row (second row)
    while (sort_algo == 1){
        printf("\n\nSorted array\n");
        bubble_sort(sort_row,m,lowest,highest);
        for(int i = 0; i < m; i++){
            printf("%6d", sort_row[i]);
        }
        break;
    }

    // subtracting the start time by the end time to get the duration of algorithm
    time2 = time(&time2);
    int duration = difftime(time2, time1);

    // call to menu method
    printf("\n\nSorting duration (Sec): %d\n", duration);
    menu(unsort_row, sort_row,m, n, diff);
    return;
}    


/**
 * @param arr
 * @param m
 * @param lowest
 * @param highest
 * 
 * this method performs the quick sort algorithm on the row to sort of the 2d array
 */
void quick_sort(int* arr, int m, int lowest, int highest){
    
    // base case for recursion
    if(lowest < highest){

        // partitioning the array and getting the pivot index
        int j = partition(arr,m,lowest,highest);
        // recursively sorting the elements before and after the partition
        quick_sort(arr, m, lowest, j - 1);
        quick_sort(arr, m, j + 1, highest);
    }      
}


/**
 * @return j
 * @param arr
 * @param m
 * @param lowest
 * @param highest
 * 
 * this method partitions the row to sort in the 2d numbers array (second row)
 */
int partition(int* arr, int m, int lowest, int highest){
    
    // setting pivot
    int pivot = arr[lowest];
    int i = lowest;
    int j = highest;

    // sorting elements based on pivot
    while (i < j){
        
        // finding element greater than pivot
        while (i <= highest && arr[i] <= pivot){
            i++;
        }
        
        // finding element less than or equal to pivot
        while (j >= lowest && arr[j] > pivot){
            j--;
        }
        
        // swap of elements
        if (i < j){
            swap(&arr[i],&arr[j]);
        }
    }
    // putting pivot element in correct order
    swap(&arr[lowest], &arr[j]);
    return j;
}
 

/**
 * @param x
 * @param y
 * 
 * this method swaps two elements
 */
void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}


/**
 * @param arr
 * @param m
 * @param lowest
 * @param highest
 * 
 * this method performs the bubble sort algorithm on the row to sort of the 2d array
 */
void bubble_sort(int* arr, int m, int lowest, int highest){

    // compares adjacent elements in array and swaps if in wrong order
    for (int i = 0; i < m - 1; i++){
        for (int j = 0; j < m - 1 - i; j++){
            if (arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


/**
 * @param unsort_row
 * @param sort_row
 * @param m
 * @param n
 * @param diff
 * 
 * this method acts as a menu to allow the user to perform next steps
 */
void menu(int * unsort_row, int * sort_row, int m, int n, int diff){

    // variable to store if user enters q to quit
    int entered_Q = 0;
    char user_selection;
    
    do{
        do{
            // prompting user for command
            printf("\nEnter a command from the following list:\n"
                "(R) Re-generate random numbers and choose a different sorting algorthim\n"
                "(N) Enter another value for n and m, and enter new n numbers\n"
                "(S) Use a different sorting algorithm\n"
                "(Q) Quit\n" );
                scanf(" %c", &user_selection);

            // allowing for lowercase inputs and checking for user entering 'q' or 'Q'
            if (user_selection == 'q' || user_selection == 'Q'){
                user_selection = 'Q';
                entered_Q = 1;
            }
            else if (user_selection == 'r' || user_selection == 'R'){
                user_selection = 'R';
            }
            else if (user_selection == 'n'|| user_selection == 'N'){
                user_selection = 'N';
            }
            else if (user_selection == 's' || user_selection == 'S'){
                user_selection = 'S';
            }

            // handling invalid input
            else{
                printf("Invalid choice, try again\n");
                user_selection = '\0';
            }
        // loop menu until user enters valid input
        }while (user_selection == '\0');
        

        // calling different methods based on users choice
        switch (user_selection){
        
        case 'R': random_ints(unsort_row, sort_row, m, n, diff);
                    return;
            break;
        case 'N': n_m_values();
                    return;
            break;
        case 'S': diff_sorting(unsort_row, sort_row, m, n, diff);
                    return;
            break;
        case 'Q': return;
            break;
        default:
            break;
        }
    } while (!entered_Q);
}