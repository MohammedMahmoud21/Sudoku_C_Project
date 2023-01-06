#ifndef SUDOKU_FUNCTIONS_H
#define SUDOKU_FUNCTIONS_H

/**************** Functions Prototype Section ********************/

/**
 * @brief Function used to print Sudoku Array.
 *
 */
void Sudoku_Array_Printf(void);
/**
 * @brief Function used to give hints to user.
 *
 * @param X_Value variable hold row index of wanted cell.
 * @param Y_Value variable hold colum index of wanted cell.
 * @param Value   pointer to return wanted value in it.
 * @return unsigned char
 *                        0 : No Errors.
 *                        1 : NULL Pointer.
 */
unsigned char Sudoku_Hint_Function(const unsigned char X_Value, const unsigned char Y_Value, unsigned char *const Value);
/**
 * @brief Function used to check if user input is right or not.
 *
 * @param X_Value pointer to return row index in it, if this function was called and user didn't finish
 *                  certain cell it will report him the indexes of this cell.
 * @param Y_Value pointer to return colum index in it, if this function was called and user didn't finish
 *                  certain cell it will report him the indexes of this cell.
 * @return unsigned char
 *                       0 : No Errors (right answer).
 *                       1 : Wrong answer.
 */
unsigned char Sudoku_Submit_Function(unsigned char *const X_Value, unsigned char *const Y_Value);
/**
 * @brief Function used to count how many time did user entered wrong cells.
 *
 * @param X_Value variable hold row location entered by user.
 * @param Y_Value variable hold colum location entered by user.
 * @return unsigned char Number of Mistakes.
 */
unsigned char Sudoku_Mistakes_Function(const unsigned char X_Value, const unsigned char Y_Value);
/**
 * @brief Function used to check if user insert input is valid or not.
 *
 * @param X_Value  variable hold row location entered by user.
 * @param Y_Value  variable hold colum location entered by user.
 * @param In_Value variable hold value of cell entered by user.
 * @return unsigned char
 *                       0 : Invalid.
 *                       1 : Valid.
 *                       2 : Reserved place.
 */
unsigned char Sudoku_Input_Valid(const unsigned char X_Value, const unsigned char Y_Value, const unsigned char In_Value);
/**
 * @brief Function used to wright values to sudoku array.
 *
 * @param X_Value  variable hold row location entered by user.
 * @param Y_Value  variable hold colum location entered by user.
 * @param In_Value variable hold value of cell entered by user.
 */
void Sudoku_Insert_Input(const unsigned char X_Value, const unsigned char Y_Value, unsigned char In_Value);
/**
 * @brief Function used to reset Sudoku array.
 *
 */
void Sudoku_Reset_Array(void);

#endif /* SUDOKU_FUNCTIONS_H */
