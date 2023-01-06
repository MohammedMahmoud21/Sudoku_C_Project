#ifndef USER_FUNCTIONS_H
#define USER_FUNCTIONS_H

/**************** Functions Prototype **********************/

/**
 * @brief Function used to handle the input entered from user during play time.
 *
 * @param Buffer   pointer to first element address of buffer.
 * @param Max_Size variable hold maximum value could be entered to this buffer.
 * @return unsigned char
 *                       0 : Null Pointer.
 *                       1 : Function Hint was called and continue play.
 *                       2 : Call Submit.
 *                       3 : Quit Game.
 *                       4 : insert cells.
 *                       5 : Reset.
 *                       6 : Invalid Input.
 */
unsigned char User_Input_Handler(const unsigned char *const Buffer, const signed int Max_Size);

/**
 * @brief Function used to compare two strings with each others.
 *
 * @param Str1 pointer to first character address of string one.
 * @param Str2 pointer to first character address of string one.
 * @return unsigned char
 *                        1 : Equal.
 *                        0 : Not Equal.
 */
unsigned char String_Compare(const unsigned char *const Str1, const unsigned char *const Str2);

/**
 * @brief Function used to know if its still valid to help user or not.
 *
 * @param Count variable hold amount of times this function was called.
 * @param Mode  variable hold mode chose by user.
 * @return unsigned char
 *                         0 : Not Valid.
 *                         1 : Valid.
 */
unsigned char User_Hint_Handler(const unsigned char Count, const unsigned char Mode);

#endif /* USER_FUNCTIONS_H */
