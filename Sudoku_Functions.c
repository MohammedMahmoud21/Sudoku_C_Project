/**
 * @file Sudoku_Functions.c
 * @author Mohammed Elsayaad.
 * @brief This file contain all functions deal directly with sudoku array.
 * @version 0.1
 * @date 2023-01-02
 * @LinkedIn: https://www.linkedin.com/in/mohamed-elsayaad2112/
 * @GitHub:   https://github.com/MohammedAshraf2
 */
/********************** Include section *********************************/
#include "My_Std_Lib.h"
#include "Sudoku_Functions.h"
/********************** #Define section *********************************/
#define ARRAY_2D_SIZE ((char)10)
/**************** Global Variables Definations ***************/
static unsigned char Sudoku_Array[ARRAY_2D_SIZE][ARRAY_2D_SIZE] =
    {
        {' ', '1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', ' ', ' ', ' ', '8', ' ', ' ', ' ', ' ', ' '},
        {'2', '7', '8', '9', ' ', '1', ' ', ' ', ' ', '6'},
        {'3', ' ', ' ', ' ', ' ', ' ', '6', '1', ' ', ' '},
        {'4', ' ', ' ', '7', ' ', ' ', ' ', ' ', '5', ' '},
        {'5', '5', ' ', '8', '7', ' ', '9', '3', ' ', '4'},
        {'6', ' ', '4', ' ', ' ', ' ', ' ', '2', ' ', ' '},
        {'7', ' ', ' ', '3', '2', ' ', ' ', ' ', ' ', ' '},
        {'8', '8', ' ', ' ', ' ', '7', ' ', '4', '3', '9'},
        {'9', ' ', ' ', ' ', ' ', ' ', '1', ' ', ' ', ' '}};

static const unsigned char Reference_Array[ARRAY_2D_SIZE][ARRAY_2D_SIZE] =
    {
        {0, '1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '1', '6', '5', '8', '4', '7', '9', '2', '3'},
        {'2', '7', '8', '9', '3', '1', '2', '5', '4', '6'},
        {'3', '4', '3', '2', '5', '9', '6', '1', '7', '8'},
        {'4', '2', '9', '7', '4', '6', '3', '8', '5', '1'},
        {'5', '5', '1', '8', '7', '2', '9', '3', '6', '4'},
        {'6', '3', '4', '6', '1', '5', '8', '2', '9', '7'},
        {'7', '9', '7', '3', '2', '8', '4', '6', '1', '5'},
        {'8', '8', '2', '1', '6', '7', '5', '4', '3', '9'},
        {'9', '6', '5', '4', '9', '3', '1', '7', '8', '2'}};

static unsigned char Reset_Flag;
/**************** Functions Implementations ***************/

void Sudoku_Array_Printf(void)
{
    signed int Index_1 = 0;
    signed int Index_2 = 0;
    for (; Index_1 < 10; Index_1++)
    {
        for (Index_2 = 0; Index_2 < 10; Index_2++)
        {
            printf("\x1b[32;40m%3c  \x1b[0m", Sudoku_Array[Index_1][Index_2]);
            printf("\x1b[34;40m|\x1b[0m");
        }
        puts(ANSI_COLOR_RED "\x1b[31m\n  ----------------------------------------------------------\x1b[0m" ANSI_COLOR_RESET);
    }
}

unsigned char Sudoku_Hint_Function(const unsigned char X_Value, const unsigned char Y_Value, unsigned char *const Value)
{
    unsigned char Error_State = 0;
    if (0 == Value)
    {
        Error_State = 1;
    }
    else
    {
        *Value = Reference_Array[X_Value][Y_Value];
    }
    return (Error_State);
}

unsigned char Sudoku_Submit_Function(unsigned char *const X_Value, unsigned char *const Y_Value)
{
    unsigned char Error_State = 0;
    unsigned char Flag = 1;
    unsigned char Index_1 = 1;
    unsigned char Index_2 = 1;
    for (; (Index_1 < ARRAY_2D_SIZE) && (1 == Flag); Index_1++)
    {
        for (Index_2 = 1; (Index_2 < ARRAY_2D_SIZE) && (1 == Flag); Index_2++)
        {
            if (Sudoku_Array[Index_1][Index_2] != Reference_Array[Index_1][Index_2])
            {
                Flag = 0;
                *X_Value = Index_1;
                *Y_Value = Index_2;
                Error_State = 1; // Means There is wrong cell or cells.
            }
            else
            {
                ;
            }
        }
    }
    return (Error_State);
}

unsigned char Sudoku_Mistakes_Function(const unsigned char X_Value, const unsigned char Y_Value)
{
    static unsigned char Mistakes;
    if (1 == Reset_Flag)
    {
        Mistakes = 0;
        Reset_Flag = 0;
    }
    else
    {
        ;
    }
    if (Sudoku_Array[X_Value][Y_Value] != Reference_Array[X_Value][Y_Value])
    {
        Mistakes++;
    }
    else
    {
        ;
    }
    return (Mistakes);
}

unsigned char Sudoku_Input_Valid(const unsigned char X_Value, const unsigned char Y_Value, const unsigned char In_Value)
{
    unsigned char Is_Valid = 1;
    unsigned int Index_Array[9] = {4u, 12359u, 67u, 38u, 134679u, 27u, 34u, 15789u, 6u};
    unsigned int Temp = 0u;
    unsigned char Digit = 0;
    if (((0 < X_Value) && (9 >= X_Value)) && ((0 < Y_Value) && (9 >= Y_Value)) && ((0 < In_Value) && (9 >= In_Value)))
    {
        Temp = Index_Array[X_Value - 1];
        while (Temp)
        {
            Digit = (unsigned char)(Temp % 10u);
            if (Digit == Y_Value)
            {
                Is_Valid = 2; // reserved place ... can't wright here.!!
                break;
            }
            Temp /= 10u;
        }
    }
    else
    {
        Is_Valid = 0;
    }

    return (Is_Valid);
}

void Sudoku_Insert_Input(const unsigned char X_Value, const unsigned char Y_Value, unsigned char In_Value)
{
    In_Value += '0';
    Sudoku_Array[X_Value][Y_Value] = In_Value;
}

void Sudoku_Reset_Array(void)
{
    unsigned int Index_Array[9] = {4u, 95321u, 76u, 83u, 976431u, 72u, 43u, 98751u, 6u};
    unsigned char Array_Index_Row = 0;
    unsigned char Sudoku_Array_Row = 1;
    unsigned char Sudoku_Array_Colum = 1;
    unsigned int Gain = 10u;
    unsigned int Value = 0;
    unsigned char Temp = 0;
    for (; Sudoku_Array_Row < ARRAY_2D_SIZE; Sudoku_Array_Row++, Array_Index_Row++)
    {
        Temp = 0;
        Value = Index_Array[Array_Index_Row];
        for (Sudoku_Array_Colum = 1; Sudoku_Array_Colum < ARRAY_2D_SIZE; Sudoku_Array_Colum++)
        {
            if (0 == Temp)
            {
                Temp = (unsigned char)(Value % Gain);
                Value /= 10u;
            }
            else
            {
                ;
            }
            if (!(Sudoku_Array_Colum == Temp))
            {
                Sudoku_Array[Sudoku_Array_Row][Sudoku_Array_Colum] = ' ';
            }
            else
            {
                Temp = 0;
            }
        }
    }
    Reset_Flag = 1;
}
