/*-------------------------------------------
Program 1: Twenty-Four
Course: CS 211, Spring 2023, UIC
System: Replit
Author: Ivan Tang
Starter code provided by: Ellen Kidane
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

//--------------------------declare functions------------------------------
void displayStart();
void displayGame(int* num, char* choice);
void displayResult(char* input, int* number_set);
void initializeGame(int* gamemode, int* num_set, int* num_set_index);
void getArguments(int argc, char* argv[], int* gamemode);
void debugHelper(int* count, int* num_set, int* gamemode, int* number_set, int* set_index);
void debugValid(int* count, char* input, int* num_set, int* gamemode, int* number_set, int* set_index);
short int play(char* input, int* number_set);
int power(int base, int exp);

//--------------------------write functions--------------------------------

//displays the starting message fo the program (not necessary so can remove to shorten lines)
void displayStart(){
  printf("Welcome to the game of TwentyFour.\nUse each of the four numbers shown below exactly once, \ncombining them somehow with the basic mathematical operators (+,-,*,/) \nto yield the value twenty-four.\n");
}

//retrieves any args accompanying the main file call. Edits the gamemode variable to determine the user option
void getArguments(int argc, char* argv[], int* gamemode){
  if (argc == 1) return;  //No arguments
  else {
    while ((argc -= 2) > 0) { // while there is another pair of strings
      if (argv[1][0] != '-') return; // Invalid syntax, no "-" before option
      switch (argv[1][1]) { // determines what to do for debug or easy mode
        case 'd':
          if(atoi(argv[2]) == 1){    //checks for [on]
           *gamemode = 2;
          }
          break;
        case 'e':
          if(atoi(argv[2]) == 0){ 
            *gamemode *= -1;  //negative to turn easy mode off (easy and standard mode are determiend by the sign of the int)
          }
          break;
        default:
          return;
       } 
      argv += 2; // advance to next pair of command line options
    }            
  }
}

//returns base raised to the exp power
int power(int base, int exp){
  int result = 1;
  for (int i = exp; i > 0; i--){
    result *= base;
  }
  return result;
}

//displays the four numbers and prompts the user input
void displayGame(int* num_set, char* op_inputs){
  printf("\nThe numbers to use are: %d, %d, %d, %d.\n", (*num_set) / 1000, ((*num_set) / 100) % 10, ((*num_set) / 10) % 10, (*num_set) % 10);
  printf("Enter the three operators to be used, in order (+,-,*, or /): ");
  scanf("%s", op_inputs);
}

//Determines whther or not the move is correct and displays the operations
//  returns 0 if the equation is not equal to 24
//  returns 1 if the equation is equal to 24
//  returns 3 if the user input produced an error
//Prompts the user if they would like to play again
short int play(char* input, int* number_set){
  //check for invalid user input length
  while(strlen(input) != 3){  
    printf("Error! The number of operators is incorrect. Please try again.\n");
    return 3;
  }
  //check for invalid characters
  for(int i = 0; i < 3; i++){
    if(input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/'){
      printf("Error! Invalid operator entered. Please try again.\n");
      return 3;
    }
  }
  
  int num3 = 0;
  int num2 = 0;
  int num1 = ((*number_set) / (int)(power(10, 3)) % 10);
  //prints the calculations according to user input  (num1 [+,-,*,/] num2 = num3)
  for(int i = 0; i < 3; i++){//definitely room for optimization
    num2 = ((*number_set) / (int)(power(10, 2 - i)) % 10);
    
    switch(input[i]){        //depending on user operator input, different arithmatic will execute
      case '+':
        num3 = num1 + num2;
        break;
      case '-':
        num3 = num1 - num2;
        break;
      case '*':
        num3 = num1 * num2;
        break;
      case '/':
        num3 = num1 / num2;
        break;
    }
    printf("%d %c %d = %d.\n", num1, input[i], num2, num3);
    num1 = num3;              //make sure the equations are building on top of each other
  }

  //checks whether or not user input is correct
  if(num3 == 24){
    return 1;  //returns correct
  }
  return 0;    //returns incorrect
}

//displays whether or not the player's input is correct and prompts user for another orund
void displayResult(char* input, int* num_set){
  short int correct_check = play(input, num_set);    //calling play to print and determine correctness
  if(correct_check == 3){return;}                    //in the case there was an error or unwanted input
  else if(correct_check){            
    printf("Well done! You are a math genius.");
  }
  else{
    printf("Sorry. Your solution did not evaluate to 24.");
  }
  printf("\n\nWould you like to play again? Enter N for no and any other character for yes. ");
  scanf("%s", input);
}

//takes in gamemode and determines the number_set and if debug mode is active
//debug and standard mode call helper functions to generate all possibe solutions
void initializeGame(int* gamemode, int* num_set, int* set_index){
  *num_set = 0;                       //reset set of numbers
  if((*gamemode) < 0){                //standard mode  (explanation for logic in main function)
    (*set_index) = (rand() %  3188);
  }
  else{  //easy mode
    int pArray[10] = {3941, 8581, 6151, 2878, 5292, 2684, 5543, 6626, 8426, 6281};  //create array holding all possible game options for easy mode
    (*num_set) = pArray[rand() % 10];                                               //assign num_set with one of the 10 preset number sets
  }
  if((*gamemode) < 0 || (abs(*gamemode) == 2)){  //debug mode or standard mode. the two follow the same process of generating all possible solutions
    int count = 0;
    int test_set = 0;

    //nested for-loops to get every permutation of numbers 0 through 9 for 4 slots
    for(int num1 = 1; num1 < 10; num1++){
      test_set += num1 * 1000;                                //set most left number to num1
      for(int num2 = 1; num2 < 10; num2++){
        test_set += num2 * 100;                               //set second most left number to num2
        for(int num3 = 1; num3 < 10; num3++){
          test_set += num3 * 10;                              //set third most left number to num3
          for(int num4 = 1; num4 < 10; num4++){
            test_set += num4;                                 //set most right number to num4
            debugHelper(&count, &test_set, gamemode, num_set, set_index);  //All number permutations generated and now being tested with all permutations of operators for three slots
            test_set -= num4;                                 //resets most right number
          }
          test_set -= num3 *  10;                             //resets third most left number
        }
        test_set -= num2 *  100;                              //resets second most left number
      }
      test_set -= num1 *  1000;                               //resets most left number
    }
    if(abs(*gamemode) == 2){
      *gamemode /= 2;    //makes sure the debugger printfs do not run more than once, turns off first debugger command
    }
  }
}

//takes in a combination of 4 numbers and finds all viable solutions for the set of elements
//using all permutations of the signs (+-*/)
void debugHelper(int* count, int* test_set, int* gamemode, int* num_set, int* set_index){
  char op_choices[4] = "+-*/";        //stores the four choices for the available operators
  char op_current[3] = "";

  //loop through permutations of the operators
  for(int op1 = 0; op1 < 4; op1++){
    op_current[0] = op_choices[op1];    //adding chosen operators to a string to be tested in helper function
    for(int op2 = 0; op2 < 4; op2++){
      op_current[1] = op_choices[op2];  //same as line 199
      for(int op3 = 0; op3 < 4; op3++){
        op_current[2] = op_choices[op3];  //same as line 199
        debugValid(count, op_current, test_set, gamemode, num_set, set_index);  //determine correct outputs and prints depending on mode
      }
    }
  }
}

//Determines whether or not the move is correct and displays the operations
//takes string input and calculates all possible solutions
//increments count depending on solutions
//set_index used for the random solution generated for standard mode
//num_set being a pointer to the set of numbers used for the game
void debugValid(int* count, char* input, int* test_set, int* gamemode, int* num_set, int* set_index){
  double num3 = 0;
  double num1 = (double)((*test_set) / (int)(power(10, 3)) % 10);             //grab left most element of num-set
  //calculates whether or not the sequence of numbers and operators equals 24
  for(int i = 0; i < 3; i++){
    double num2 = (double)((*test_set) / (int)(power(10, 2 - i)) % 10);      //parse through num_set for each num in position
    
    switch(input[i]){    //matches operation with corresponding operators
      case '+':
        num3 = num1 + num2;
        break;
      case '-':
        num3 = num1 - num2;
        break;
      case '*':
        num3 = num1 * num2;
        break;
      case '/':
        num3 = num1 / num2;
        break;
    }
    num1 = num3;
  }
  
  if((fabs(num3 - 24) < 0.00001)){    //the equation is valid
    (*count) += 1;
    if(abs(*gamemode) == 2){  //if in debug mode, then print out all solutions
      //print out the valid equation
      printf("%d. %d%c%d%c%d%c%d\n", *count, ((*test_set) / 1000), input[0], (((*test_set) / 100) % 10), input[1], (((*test_set) / 10) % 10), input[2], (*test_set) % 10);
    }
    if((*count == *set_index + 1) && (*gamemode < 0)){    //if not in debug mode and only on standard mode, assign num_set to the [set_index]th solution
    *num_set = *test_set;
    } 
  }
}

//----------------------------------game engine------------------------------------------
int main(int argc, char *argv[]) {
  srand(1);
  //gamemode < 0 : standard mode  (negative sign)
  //gamemode = 2 : debug on        (just 2)
  //gamemode >= 0, gamemode != 3 : easy mode   (positive sign or 0)
  int gamemode = 1;  //debug off, easy mode (defult)
  int number_set = 0;            //holds the set of valid puzzle numbers
  int set_index = 3186;          //index of solution to be assigned to number_set
  char* user_input = malloc(50 * sizeof(char));   //make sure user input can be as long as 50 characters (allows more than just three inputs)
  
  getArguments(argc, argv, &gamemode);      
  displayStart();                           
  //game starting engine
  do{
    initializeGame(&gamemode, &number_set, &set_index);
    displayGame(&number_set, user_input);                
    displayResult(user_input, &number_set);             
  }while(!(user_input[0] == 'N'));          //lop until user no longer wants to play
  
  printf("\nThanks for playing!\n");    //end game message
	return 0;
}



