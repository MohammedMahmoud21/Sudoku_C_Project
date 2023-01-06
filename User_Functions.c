/**
 * @file main.c
 * @author Mohammed Elsayaad.
 * @brief This file contain functions that deal with user options.
 * @version 0.1
 * @date 2023-01-02
 * @LinkedIn: https://www.linkedin.com/in/mohamed-elsayaad2112/
 * @GitHub:   https://github.com/MohammedAshraf2
 */
/********************** Include section *********************************/
#include "My_Std_Lib.h"
/**************** Functions Prototype **********************/

/**
 * @brief Function to get absolute value.
 *
 * @param Num number we want to get its absolute.
 * @return signed int
 */
static signed int My_Abs(signed int Num);

/**************** Functions Implementations ***************/

static signed int My_Abs(signed int Num)
{
    return (Num * (((2 * Num) + 1) % 2));
}

unsigned char String_Compare(const unsigned char *const Str1, const unsigned char *const Str2)
{
    unsigned char Ret_Val = 1; // They are the same.
    unsigned char Index = 0;
    signed char Diff = 'a' - 'A';
    signed char Temp = 0;
    while ((' ' == Str1[Index]) || (' ' == Str2[Index]))
    {
        Index++;
    }
    for (; (Str1[Index]) || (Str2[Index]); Index++)
    {
        Temp = Str1[Index] - Str2[Index];
        Temp = (signed char)My_Abs((signed int)Temp);
        if (!((0 == Temp) || (Diff == Temp)))
        {
            Ret_Val = 0;
            break;
        }
        else
        {
            ;
        }
    }

    return (Ret_Val);
}

unsigned char User_Input_Handler(const unsigned char *const Buffer, const signed int Max_Size)
{
    unsigned char Error_State = 0;
    unsigned char Flag = 0;
    unsigned char Index = 0;
    unsigned int Length = 0;
    while (Buffer[Index] && (Index < Max_Size) && (0 == Error_State))
    {
        if (('H' == Buffer[Index]) || ('h' == Buffer[Index]))
        {
            Length = strlen(&Buffer[Index]);
            if ((Length > 1) && (String_Compare(&Buffer[Index], "Hint")))
            {
                Error_State = 1; // means call user hint.
            }
            else if (1 == Length)
            {
                Error_State = 1;
            }
            else
            {
                Error_State = 0;
            }
        }
        else if ((' ' == Buffer[Index]))
        {
            ;
        }
        else if (('s' == Buffer[Index]) || ('S' == Buffer[Index]))
        {
            Length = strlen(&Buffer[Index]);
            if ((Length > 1) && (String_Compare(&Buffer[Index], "Submit")))
            {
                Error_State = 2; // means call user submit.
            }
            else if (1 == Length)
            {
                Error_State = 2;
            }
            else
            {
                Error_State = 0;
            }
        }
        else if (('q' == Buffer[Index]) || ('Q' == Buffer[Index]))
        {
            Length = strlen(&Buffer[Index]);
            if ((Length > 1) && (String_Compare(&Buffer[Index], "Quit")))
            {
                Error_State = 3; // means quit game.
            }
            else if (1 == Length)
            {
                Error_State = 3;
            }
            else
            {
                Error_State = 0;
            }
        }
        else if (('i' == Buffer[Index]) || ('I' == Buffer[Index]))
        {
            Length = strlen(&Buffer[Index]);
            if ((Length > 1) && (String_Compare(&Buffer[Index], "Insert")))
            {
                Error_State = 4; // User Try to insert cell.
            }
            else if (1 == Length)
            {
                Error_State = 4; // User Try to insert cell.
            }
            else
            {
                Error_State = 0;
            }
        }
        else if (('r' == Buffer[Index]) || ('R' == Buffer[Index]))
        {
            Length = strlen(&Buffer[Index]);
            if ((Length > 1) && (String_Compare(&Buffer[Index], "Reset")))
            {
                Error_State = 5; // Reset Game.
            }
            else if (1 == Length)
            {
                Error_State = 5; // Reset Game.
            }
            else
            {
                Error_State = 0;
            }
        }
        else
        {
            Error_State = 6; // undefined.
        }
        Index++;
    }

    return (Error_State);
}

unsigned char User_Hint_Handler(const unsigned char Count, const unsigned char Mode)
{
    unsigned char Still_Valid = 0; // Not Valid.
    switch (Mode)
    {
    case 1:
        if (Count <= 6)
        {
            Still_Valid = 1;
        }
        else
        {
            Still_Valid = 0;
        }
        break;
    case 2:
        if (Count <= 3)
        {
            Still_Valid = 1;
        }
        else
        {
            Still_Valid = 0;
        }
        break;
    case 3:
        if (Count <= 1)
        {
            Still_Valid = 1;
        }
        else
        {
            Still_Valid = 0;
        }
        break;
    default:
        break;
    }

    return (Still_Valid);
}
