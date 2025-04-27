/**
 * USAGE: All functions are compiled and ready to run. Whenever you want to run any function simply 
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


void SIMPLE_malloc(void); 
void loseTheAddress(void);
int callocAndMalloc(void);
void realloc_Example (void); 

int main()
{
    //SIMPLE_malloc(); 
    //loseTheAddress(); 
    callocAndMalloc();
    //realloc_Example(); 
    _CrtDumpMemoryLeaks(); 
    return 0;
}

/**
 * NOTE: This is simple malloc example explained on Page 34
 */
void SIMPLE_malloc(void)
{
    //NOTE: malloc() always returns a pointer to memory from heap if and only if memory is allocated.
    //If it fails it returns a null pointer. 

    int a = 0; 
    int *p; 
    p = (int*) malloc(sizeof(int));
    *p = 5; 
    printf("Value saved is: %d", *p); 
    
    *p += 4; 
    printf("Value saved is: %d", *p); 
    //printf("Value saved is: %lu", &p); 
    free(p);
}

/**
 * NOTE: This is to try to lose the address and create a possibility of memory leak. 
 * This is explained on page 37 of the book. 
 */

void loseTheAddress(void)
{
    int *pi = (int*) malloc(sizeof(int)); 
    //malloc returned one address of this memory region and this address is saved 
    //in pointer value. so address is 500 is saved in pointer value and pointers 
    //own address is lets say 100. 
    printf("pi pointer value is %d and address is %d\n", *pi,&pi); 
    *pi = 5;
    printf("After dereferencing pi pointer value is %d and address is %d\n", *pi,&pi); 
    //Now value 5 is written by dereferencing on the address which is saved in pointers value. 
    //so 500 is saved in pointer and 5 is written on memory address 500. 

    //Now lets write different memory address to pointer so that it forgets previous memory
    //address which was 500 in our case. 
    
    *pi = (int*)malloc(sizeof(int));
    printf("After new memory allocation, pi pointer value is %d and address is %d\n", *pi,&pi);  
    //Lets say now address 600 is saved into pointer value (pointing to).
    *pi = 6; 
    //Using dereferencing 6 is written on memory 600.
    printf("After dereferencing pi pointer value is %d and address is %d\n", *pi,&pi); 
    free(pi); 
    /**
     * This is another example by string 
     */
    char *name = (char*)malloc(strlen("Gaurav")+1); 
    strcpy(name, "Gaurav"); 
    while(*name != 0)
    {
        printf("%c", *name); 
        name++;
    }
    //After running this loop pointer points to '/0' means initial address is lost. 
    //Hence memory leak is possible when memory address is lost and when free function is never used. 
}

/**
 * NOTE: This function revises calloc and malloc memory allocation as per page 43. 
 * We will create memory allocation as per calloc() and then do the same by using 
 * malloc() + memset()
 */

int callocAndMalloc(void)
{
    //Create memory to store 5 int values (20B) and memory to store name 'Gaurav' using calloc()
    printf("Running callocAndMalloc Function\n"); 
    int *p = NULL;
    //calloc syntax is void *calloc(size_t numElements, size_t elementSize)
    p = calloc(5, sizeof(int)); 
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    //If calloc is unable to allocate memory, a null pointer is returned and the global variable,
    //errno, is set to ENOMEM (out of memory). 
    for (int i = 0; i < 5; i++) printf("Values stored in memory are %d\n", p[i]); 
    //Lets store something in this this memory. 

    *(p+2)= 10; 
    for (int i = 0; i < 5; i++) printf("Values stored in memory are %d\n", p[i]); 
    free(p); 

    //Now lets create memory to store my name "Gaurav"
    char *myName = "Gaurav"; 
    char *p_myName; 
    p_myName = calloc(7, sizeof(char));
    if (p_myName == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    } 
    printf("Values stored in memory before saving my name are: \n"); 
    for (int i = 0; i < 6; i++) printf(" %d\n", p_myName[i]); 
    // Now lets save my name
    for (int i = 0; i < strlen(myName) + 1; ++i)
    {
        *(p_myName+i) = myName[i];    
    }
    printf("Name stored in memory is:"); 
    for (int j=0; j<strlen(myName) + 1; j++) printf("%c", *(p_myName+j)); 
    free(p_myName); 
    //Now lets do this using malloc() and memset() function to get the same idea as calloc()

    printf("*************************************************************************\n"); 
    printf("We are now going to use malloc() and memset() function\n"); 
    int *q = NULL; 
    q = (int*)malloc(5*sizeof(int)); 
    if(q== NULL){
         printf("Memory allocation failed!\n");
        return 1;
    }
    //write 5 times memset function to remember the syntax first
    /**
     * memset requires following arguments
     * 1. pointer to buffer to fill
     * 2. Value used to fill the buffer
     * 3. No. of bytes to set
     * memset(p, 0, 5*sizeof(int)); 
     * memset(p, 0, 5*sizeof(int)); 
     * memset(p, 0, 5*sizeof(int)); 
     * memset(p, 0, 5*sizeof(int)); 
     * memset(p, 0, 5*sizeof(int)); 
     */
    memset(q, 0, 5*sizeof(int)); 

    for(int i=0; i< 5; i++)printf("Values stored after memset are: %d\n", *(q+i)); 
    //Lets store something at memory location 3
    *(q+2)=10; 
    for(int i=0; i< 5; i++)printf("Values stored after memset are: %d\n", *(q+i)); 
    free(q); 

    printf("Performing the same to save my name\n");
    char *name2 = "Amberkar"; 
    char *p_name = NULL; 
    p_name  = (char*)malloc(8*sizeof(char)); 
     
    for(int i = 0; i< strlen(name2)+1; i++)
    {
        *(p_name+i) = name2[i]; 
        //printf("%c",*(p_myName+i)); 
    }
    printf("Name stored in memory is:"); 
    for (int j=0; j<strlen(name2) + 1; j++) printf("%c", *(p_name+j)); 
    printf("\n"); 
    printf("*****Exercise Complete*****"); 
    return (0); 
}

/**
 * NOTE: Visiting realloc(): Its used to increase/decrease allocated memory size. 
 * SYNTAX: void *realloc(void *ptr, size_t size)
 * 
 * USAGE: realloc returns a pointer to a block of memory. In argument first argument is pointer to
 * original block of memory, second block is requested size. 
 * PRACTICE: void *realloc(void *ptr, size_t size)
 *           void *realloc(void *ptr, size_t size)
 *           void *realloc(void *ptr, size_t size)
 *           void *realloc(void *ptr, size_t size)
 *           void *realloc(void *ptr, size_t size)
 * NOTE: If we decrease the memory then extra memory will be returned to heap and it wont be freed 
 * by this function. It has to be done manually. If more memory is needed then its cant be said 
 * that new memory is sequencial and if its not then and new memory is at different location then
 * old memory will be copied to new location to create new large sequential memory. 
 * 
 * TABLE: 
 * |     First Parameter       |         Second Parameter       |         Behaviour             |
 * _____________________________________________________________________________________________
 *      null                   |         NA                     |            malloc
 *      Not NULL               |         0                      |     Original Block is freed
 *      Not NULL               |        Less than Original      |    smaller block is allocated 
 *                                                                    using current block
 *      Not NULL               |        Greater than original   |    A larger block is allocated 
 *                                                                   either from the current location 
 *                                                                  or another location of the heap
  _______________________________________________________________________________________________         
 * 
 * 
 */
void realloc_Example (void)
{
    char *sample_string = "12345678"; 
    char *pointer = NULL; 

    pointer = (char*)malloc(10*sizeof(char));
    memset(pointer, 0, 10); 

    printf("Memory print of newly created memory is: \n"); 
    for(int i = 0; i < 10; i++)printf("%d",*(pointer+i)); 
    //Now lets copy our string in this memory. 
    for (int i = 0; i < strlen(sample_string); i++)
    {
        *(pointer+i) = sample_string[i]; 
    }
    printf("\n"); 
    for(int i = 0; i < 10; i++)printf("%c",*(pointer+i));

    //Now lets remove the extra memory (2 bytes) using re-alloc 
    //Memory address before using realloc should be printed
    printf("Before realloc: %s\n", pointer);
    printf("Memory address after realloc: %p\n", (void*)pointer);
    pointer = realloc(pointer, 8); 
    printf("Memory address after realloc: %p\n", (void*)pointer);
    free(pointer); 
} 

/**
 * NOTE: If a pointer still references the original memory after it has been freed, it is called a
        dangling pointer. The pointer does not point to a valid object. This is sometimes referred
        to as a premature free.

   NOTE: Automatic Garbage Collection for C/C++: One alternative to manual memory management is the 
        Boehm-Weiser Collector. However, this is not part of the language.
    NOTE: Resource Acquisition Is Initialization. We have wrote one macro for it. Then in the comments we
    are attaching example to check. No actual implementation is done in this code.We need to add some notes here 
    for RAII. 
    EXAMPLE: void raiiExample() {
                RAII_VARIABLE(char*, name, (char*)malloc(32), free);
                strcpy(name,"RAII Example");
                printf("%s\n",name);
            }
            In this example in function, pointer name will go out of scope after exiting from function and 
            free() function will automatically executed.       
    NOTE: We can also use several different methods of exception handling. Refer link 
    LINK: https://adom.as/excc/    
 */

