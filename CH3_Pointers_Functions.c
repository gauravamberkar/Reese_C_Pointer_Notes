/**
 * USAGE: All functions are compiled and run. Whenever you want to run any function simply 
 *        un-comment the function from the main(). 
*/
#include <stdio.h>
#include <string.h>

//Enabling CRT Library 
#define _CRTDBG_MAP_ALLOC 

#include <stdlib.h>  
#include <crtdbg.h>

#ifdef _DEBUG
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
#else
    #define DBG_NEW new
#endif

#define RAII_VARIABLE(vartype,varname,initval,dtor) \
 void _dtor_ ## varname (vartype * v) { dtor(*v); } \
 vartype varname __attribute__((cleanup(_dtor_ ## varname))) = (initval)

void existing_data(void); 
void swap_with_pointer(int *ptr_n1, int *ptr_n2);

void existing_data_2(void); 
void swap_with_pointer_2(int _n1, int _n2); 

void existing_data_3(void); 
void sendAddressOfConstant(const int *ptr_1, int *ptr_2);

float* create_array(int size, float value);
void use_array(void);


int main (void)
{
    //existing_data(); 
    //existing_data_2();
    //existing_data_3();  
    //use_array(); 
    use_string();
    _CrtDumpMemoryLeaks(); 
    return 0; 
}

/**
 * NOTE: When working with functions, there are two areas where pointers become useful. The
        first is when we pass a pointer to a function.n. This allows the function to modify data
        referenced by the pointer and to pass blocks of information more efficiently
        The second area is declaring a pointer to a function.
    NOTE: What is inside of stack frame -> Return address used to return to program after function ran, 
        storage for local data, storage for parameters, stack and base pointers.  
 */

/**
 * TOPIC: Passing data using pointer.
 * NOTE:  Main primary reason of passing data using pointer 
 *      is to modify the existing data. 
 * USAGE: We will create one function which has existing data and build another swap()function
 *      to modify it. 
 */

void existing_data(void)
{
    int number_1 = 10; 
    int number_2 = 20; 
    printf("Existing values stored in number_1 is %d and number_2 is %d.\n", number_1, number_2); 
    swap_with_pointer(&number_1, &number_2);
    printf("After swapping number_1 is %d and number_2 is %d.\n", number_1, number_2);  
}

void swap_with_pointer(int *ptr_n1, int *ptr_n2)
{
    int dummy; 
    dummy = *ptr_n1; 
    *ptr_n1 = *ptr_n2; 
    *ptr_n2 = dummy; 
}
//********************************************************************************************* */
/**
 * NOTE: Now lets do the same with passing data by value. This example shows that this method will 
 *      not work as number_1 and number_2 are never changed after the swap function. 
 */

void existing_data_2(void)
{
    int number_1 = 50; 
    int number_2 = 100; 
    printf("Pass by value: Existing values stored in number_1 is %d and number_2 is %d.\n", number_1, number_2); 
    swap_with_pointer_2(number_1, number_2); 
    printf("Pass by value: After swapping number_1 is %d and number_2 is %d.\n", number_1, number_2);  
}

void swap_with_pointer_2(int _n1, int _n2)
{
    int temp; 
    temp = _n1; 
    _n1 = _n2; 
    _n2 = temp; 
}

//********************************************************************************************* */
/**
 * TOPIC: Passing a pointer to a constant.
 * NOTE:  Main primary reason of passing data using pointer to constant is we are accessing the
 *          data using pointer but we do not want to modify it. (Accidentally) 
 * USAGE: We will create one function which has existing data and build another sendAddressOfConstant()
 *         function to modify it. 
 */

void sendAddressOfConstant(const int *ptr_1, int *ptr_2)
{
    *ptr_2 = *ptr_1; 
}

void existing_data_3(void)
{
    const int var = 100; 
    int var2 = 200; 
    printf("Passing pointer to constant: Existing values stored in var is %d and var2 is %d.\n", var, var2); 
    sendAddressOfConstant(&var, &var2); 
    printf("Passing pointer to constant: Existing values stored in var is %d and var2 is %d.\n", var, var2);

}

//********************************************************************************************* */
/**
 * TOPIC: Returning a pointer from a function
 * NOTE:  Two techniques can be used. Allocate memory inside function using malloc(). Deallocation will be done by 
 *      caller function. Second, pass an object to a function where it is modified. In this case, 
 *      allocation and de-allocation is callers responsibility. 
 * USAGE: We will create one function in which we are allocating memory and we will return the address. 
 */

 //Lets first create array and we return it from the function. We will create array by using malloc()

 float* create_array(int size, float value)
 {
    float* arr = (float*)malloc(size*sizeof(float)); //If we declare array here, then error c occur as
                                                        //array is local and it might be popped from the stack. unknown behaviour. 
    for(int i = 0; i < size; i++)
    {
        arr[i] = value;
    }
    return arr; 
 }

 void use_array(void)
 {
    float* var = create_array(5, 1.1); 
    for(int i = 0; i < 5; i++)
    printf("Value stored in array is: %d-  %f\n", i+1,var[i]); 
    free(var); 
 }
/**
 * NOTE: 1. Problem with this type of application (returning pointer from a function) is 
 *          a. we might return uninitialized pointer.
 *          b. we might return a pointer to an invalid address. 
 *          c. We might return a pointer to local variable. 
 *          d. Returning a pointer but failing to free it.
 * NOTE: In above function we did not allocate memory in returning function. Below we
 *       will create a function with allocated memory by passing a null pointer. 
 */


