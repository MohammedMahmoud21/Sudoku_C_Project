/**
 * @file main.c
 * @author Mohammed Elsayaad.
 * @brief This is the main file in the Sudoku project.
 * @version 0.1
 * @date 2023-01-02
 * @LinkedIn: https://www.linkedin.com/in/mohamed-elsayaad2112/
 * @GitHub:   https://github.com/MohammedAshraf2
 */

/********************** Include section *********************************/
#include "My_Std_Lib.h"
#include "Sudoku_Functions.h"
#include "User_Functions.h"
/********************** Macros section *********************************/
#define BUFFER_SIZE ((char)100)
#define EASY ((char)1)
#define MEDIUM ((char)2)
#define DIFFICULT ((char)3)
/**************** Global Variables Definitions ***************/

/**************** Global Variables Declarations *************/

/**************** Functions Prototype **********************/
void Start_Printf(void);
void My_Printf(void);
void Buffer_Scanf(unsigned char *const Buffer, const signed int Max_Size);
void Buffer_Clean(unsigned char *const Buffer, const signed int Max_Size);
signed char Sub_Mode_Handler(const unsigned char *const Buffer, const signed int Max_Size, unsigned char *const Mode);
void Mode_Handler(unsigned char *const Input_Buffer, unsigned char *const Mode, unsigned char *const Mode_Flag, unsigned char *const Mistakes);
void Reset_Mode(const unsigned char *const Input_Buffer, unsigned char *const Mode_Flag, unsigned char *const Game_Flag);
/**************** Functions Prototype *********************/

int main(void)
{
    unsigned char Input_Buffer[BUFFER_SIZE] = {0};
    // unsigned char Count = 0; // counter for delay.
    unsigned char Mode = 0;
    unsigned char Mode_Flag = 1;
    unsigned char Game_Flag = 1; // for terminating the game.
    unsigned char Input_Ret = 0; // var for receive the return of input function.
    unsigned char Ret_Val = 0;   // used for any return of any function.
    unsigned int X_Value = 0;
    unsigned int Y_Value = 0;
    unsigned int Insert_Value = 0; // value of cell.
    unsigned char Hint_Value = 0;
    unsigned char Hint_Counter = 0;
    unsigned char Submit_Counter = 0;
    unsigned char Mistakes = 0;

    Start_Printf();
    while (Game_Flag)
    {
        // Call Mode function to control user option of mode.
        if (1 == Mode_Flag)
        {
            Mode_Handler(Input_Buffer, &Mode, &Mode_Flag, &Mistakes);
            My_Printf();
        }
        else
        {
            ;
        }
        Sudoku_Array_Printf();
        printf(ANSI_COLOR_RED "Mistakes till now = %u\n" ANSI_COLOR_RESET, Mistakes);
        printf(ANSI_COLOR_YELLOW "~elsayaad@Sudoku/Do : " ANSI_COLOR_RESET);
        fflush(stdin);
        Buffer_Scanf(Input_Buffer, BUFFER_SIZE);
        Input_Ret = User_Input_Handler(Input_Buffer, BUFFER_SIZE);
        switch (Input_Ret)
        {
        case 1:
            // Hint mode.
            Hint_Counter++;
            Ret_Val = User_Hint_Handler(Hint_Counter, Mode);
            if (0 == Ret_Val)
            {
                printf("You Are Out Of Hints. :(((\n");
            }
            else
            {
                printf("Enter Cell Row : ");
                scanf("%i", &X_Value);
                printf("Enter Cell Colum : ");
                scanf("%i", &Y_Value);
                Sudoku_Hint_Function((unsigned char)X_Value, (unsigned char)Y_Value, &Hint_Value);
                printf("The Value is %c\n", Hint_Value);
            }

            break;
        case 2:
            // Submit Mode.
            printf("Calculate Your Result Please Wait\n");
            Ret_Val = Sudoku_Submit_Function(&X_Value, &Y_Value);
            if (1 == Ret_Val)
            {
                Submit_Counter++;
                printf("Wrong Answer\n");
                if ((unsigned char)3 >= Submit_Counter)
                {
                    printf("Look below for free hint.\nRow:%i Colum:%i is wrong \n", X_Value, Y_Value);
                }
                else
                {
                    ;
                }
            }
            else
            {
                printf("Congrats You Won The Game,but not the war :P .\n");
                Reset_Mode(Input_Buffer, &Mode_Flag, &Game_Flag);
            }
            break;
        case 3:
            // Quit mode.
            printf(ANSI_COLOR_BLUE "See You Again.\n" ANSI_COLOR_RESET);
            Game_Flag = 0;
            break;
        case 4:
            // Insert Mode.
            printf("Enter Cell Row : ");
            scanf("%i", &X_Value);
            printf("Enter Cell Colum : ");
            scanf("%i", &Y_Value);
            printf("Enter The Value : ");
            scanf("%i", &Insert_Value);
            Ret_Val = Sudoku_Input_Valid(X_Value, Y_Value, Insert_Value);
            if (1 == Ret_Val)
            {
                Sudoku_Insert_Input(X_Value, Y_Value, Insert_Value);
                Mistakes = Sudoku_Mistakes_Function(X_Value, Y_Value);
                switch (Mode)
                {
                case MEDIUM:
                    if (10 == Mistakes)
                    {
                        printf(ANSI_COLOR_MAGENTA "LOSE\n" ANSI_COLOR_RESET);
                        printf("You Have Reached Maximum Chances\n");
                        Reset_Mode(Input_Buffer, &Mode_Flag, &Game_Flag);
                    }
                    else
                    {
                        ;
                    }
                    break;
                case DIFFICULT:
                    if (2 == Mistakes)
                    {
                        printf(ANSI_COLOR_MAGENTA "LOSE\n" ANSI_COLOR_RESET);
                        printf("You Have Reached Maximum Chances\n");
                        Reset_Mode(Input_Buffer, &Mode_Flag, &Game_Flag);
                    }
                    else
                    {
                        ;
                    }
                    break;
                default:
                    break;
                }
            }
            else if (2 == Ret_Val)
            {
                printf("Reserved place can't wright on it.\n");
            }
            else
            {
                printf("Please Enter Valid Input.\n");
            }
            break;
        case 5:
            // Reset Mode.
            Reset_Mode(Input_Buffer, &Mode_Flag, &Game_Flag);
            break;
        default:
            // Invalid Mode.
            printf("Enter Valid Input.\n");
            break;
        }
        fflush(stdin);
        printf("Press Enter To Continue\n");
        getchar();
        Buffer_Clean(Input_Buffer, BUFFER_SIZE);
        system("cls");
    }

    printf(ANSI_COLOR_RED "Game Ended.\n" ANSI_COLOR_RESET);
    return 0;
}
/**
 * @brief Function used to scan string from user.
 *
 * @param Buffer   pointer to first element address of buffer.
 * @param Max_Size variable hold maximum value could be entered to this buffer.
 */
void Buffer_Scanf(unsigned char *const Buffer, const signed int Max_Size)
{
    signed int Index = 0;
    scanf("%c", &Buffer[Index]);
    for (; ('\n' != Buffer[Index]) && (Index < Max_Size - 1);)
    {
        Index++;
        scanf("%c", &Buffer[Index]);
    }
    Buffer[Index] = 0;
}

/**
 * @brief Function used to clean buffer, put null in it.
 *
 * @param Buffer   pointer to first element address of buffer.
 * @param Max_Size variable hold maximum value could be entered to this buffer.
 */
void Buffer_Clean(unsigned char *const Buffer, const signed int Max_Size)
{
    signed int Counter = 0;
    while ((Buffer[Counter]) && (Counter < Max_Size))
    {
        Buffer[Counter] = 0;
        Counter++;
    }
}

/**
 * @brief Function take buffer and extract the wanted mode from it.
 *
 * @param Buffer   pointer to first element address of buffer.
 * @param Max_Size variable hold maximum value could be entered to this buffer.
 * @param Mode      pointer to return the mode in it, 1 => Easy, 2=> Medium and 3=> Difficult.
 * @return signed char
 *                      0 : No Errors.
 *                      1 : Null pointers.
 */
signed char Sub_Mode_Handler(const unsigned char *const Buffer, const signed int Max_Size, unsigned char *const Mode)
{
    signed char Error_State = 0;
    signed char Flag = 1;
    signed int Index = 0;
    if ((NULL == Buffer) || (NULL == Mode))
    {
        Error_State = 1;
    }
    else
    {
        while ((Index < Max_Size) && ('\0' != Buffer[Index]) && (1 == Flag))
        {
            if (('E' == Buffer[Index]) || ('e' == Buffer[Index]))
            {
                *Mode = EASY;
                Flag = 0;
            }
            else if (('M' == Buffer[Index]) || ('m' == Buffer[Index]))
            {
                *Mode = MEDIUM;
                Flag = 0;
            }
            else if (('D' == Buffer[Index]) || ('d' == Buffer[Index]))
            {
                *Mode = DIFFICULT;
                Flag = 0;
            }
            else if ((' ' == Buffer[Index]) || ('\t' == Buffer[Index]))
            {
                ;
            }
            else
            {
                *Mode = 0;
                Flag = 0;
            }
            Index++;
        }
    }

    return (Error_State);
}
/**
 * @brief Function used for getting the mode type from user.
 *
 * @param Input_Buffer pointer to first element address of buffer
 * @param Mode         pointer to return the mode in it, 1 => Easy, 2=> Medium and 3=> Difficult.
 * @param Mode_Flag    pointer to char, used to control the flow of this function.
 * @param Mistakes     pointer to char, used to reset the mistakes amount, if game was reset.
 */
void Mode_Handler(unsigned char *const Input_Buffer, unsigned char *const Mode, unsigned char *const Mode_Flag, unsigned char *const Mistakes)
{
    if (1 == *Mode_Flag)
    {
        system("cls");
        puts("Please,Choose The Mode [E,M,D]," ANSI_COLOR_GREEN "E for Easy" ANSI_COLOR_RESET ANSI_COLOR_BLUE ",M for Medium " ANSI_COLOR_RESET "and " ANSI_COLOR_RED "D for Difficult:" ANSI_COLOR_RESET);
    }
    else
    {
        ;
    }
    while (*Mode_Flag)
    {
        Buffer_Scanf(Input_Buffer, BUFFER_SIZE);
        Sub_Mode_Handler(Input_Buffer, BUFFER_SIZE, Mode);
        switch (*Mode)
        {
        case EASY:
            printf("Easy.\n");
            *Mode_Flag = 0;
            break;
        case MEDIUM:
            printf("Medium.\n");
            *Mode_Flag = 0;
            break;
        case DIFFICULT:
            printf("Difficult.\n");
            *Mode_Flag = 0;
            break;
        default:
            printf("Enter Valid Mode.\n");
            break;
        }
    }
    *Mistakes = 0;
}

/**
 * @brief function used to print welcome messages and rules of the game.
 *
 */
void Start_Printf(void)
{
    unsigned int Count = 0;
    system("cls");
    puts(ANSI_COLOR_BLUE "Welcome To Sudoku Game, To Have nice game experience\n" ANSI_COLOR_RESET
                         "Please Read " ANSI_COLOR_RED "The Game Rules Carefully!!" ANSI_COLOR_RESET);
    printf("LOADING\n");
    while (Count++ < 30)
    {
        printf("*");
        Sleep(200);
    }
    Count = 0;
    system("cls");
    puts(ANSI_COLOR_RED "First, You have various interactive modes while dealing with the game\n" ANSI_COLOR_RESET
             ANSI_COLOR_BLUE "To Insert cell write Insert, press i or I, anything extra won't work even a space after i.\n" ANSI_COLOR_RESET
                 ANSI_COLOR_GREEN "Second, to have hint, you can write hint or h or H, based on the mode you choose, you will have certain amount of hints.\n" ANSI_COLOR_RESET
                     ANSI_COLOR_YELLOW "Third, if you finished the game only write submit or S or s, and the result will appear on the screen.\n" ANSI_COLOR_RESET
                        "Forth, You can reset the game by press r or R or like before :) write Reset.\n");
    puts("Press enter if you understood This section.");
    getchar();
    system("cls");
    puts("You Have Various challenging Modes In This Game\n" ANSI_COLOR_GREEN "Easy Mode:\nTo choose this mode only when request press e ,E or write Easy\n"
         "This mode doesn't have mistakes counter so, you have unlimited chances and 6 hints.\n" ANSI_COLOR_RESET);
    puts(ANSI_COLOR_BLUE "Medium Mode: Press M, m or write Medium.\n"
                         "In this one you only have 10 chances so be careful to use them wisely and 3 hints.\n" ANSI_COLOR_RESET
                             ANSI_COLOR_RED "Chances here means number of mistakes of placements you do while playing\n" ANSI_COLOR_RESET);
    puts(ANSI_COLOR_RED "Difficult Mode: Press D, d or write Difficult.\n" ANSI_COLOR_RESET
                        "In this mode you only have 5 chances, and only 1 hint.\n");
    puts(ANSI_COLOR_RED "Based on the mode you have as said before, you will have certain number of mistakes so be careful when you insert a cell :) .\n" ANSI_COLOR_RESET);
    puts("Press enter if you understood the rules.");
    getchar();
}

/**
 * @brief Function used to print introduction for the game.
 *
 *
 */
void My_Printf(void)
{
    unsigned char Count = 0;

    printf("Be Ready Game Will Start Soon.\n");
    Sleep(1000);
    system("cls");
    printf(COLOR_BOLD "LOADING\n" COLOR_OFF);
    Count = 0;
    while (Count++ < 10)
    {
        printf("*");
        Sleep(800);
    }
    printf(ANSI_COLOR_RED "\nThe Game Will Start Now." ANSI_COLOR_RESET);
    Sleep(2000);
    system("cls");
}

/**
 * @brief Function used to reset the game from beginning.
 *
 * @param Input_Buffer pointer to first element address of buffer.
 * @param Mode_Flag    pointer to char, used to reset the value of Mode_Flag to its initial value or terminating value.
 * @param Game_Flag    pointer to char, used to reset the Game_Flag to its initial value or terminating value.
 */
void Reset_Mode(const unsigned char *const Input_Buffer, unsigned char *const Mode_Flag, unsigned char *const Game_Flag)
{
    printf("Do You Want To Play Again?(Yes/No)\n");
    fflush(stdin);
    Buffer_Scanf(Input_Buffer, BUFFER_SIZE);
    if (String_Compare(Input_Buffer, "Yes"))
    {
        printf("Game Will Start Again\n");
        *Mode_Flag = 1;
        Sudoku_Reset_Array();
    }
    else
    {
        printf("Bye\n");
        *Game_Flag = 0;
    }
}
