/* ==================================================
** Libraries
**
** =============================================== */


#include "sort_lsd.h"


/* ==================================================
** Macro definition
**
** =============================================== */


//


/* ==================================================
** Type definition
**
** =============================================== */


//


/* ==================================================
** Extern variables
**
** =============================================== */


//


/* ==================================================
** Static variables
**
** =============================================== */


//


/* ==================================================
** Static function declaration
**
** =============================================== */


static uint16_t get_max(uint16_t arr[], uint8_t size);
static uint8_t  get_digit(uint16_t num);


/* ==================================================
** Static function definition
**
** =============================================== */


uint16_t get_max(uint16_t arr[], uint8_t size)
{
    uint8_t max = arr[0];

    for(uint8_t i=0; i<size; ++i){
        max = max<arr[i] ? arr[i] : max;
    }

    return max;
}


uint8_t get_digit(uint16_t num)
{
    uint8_t digit = 0;

    while(num > 0){
        digit += 1;
        num   /= 10;
    }

    return digit;
}


/* ==================================================
** Extern function definition
**
** =============================================== */


void SortLSD(uint16_t arr[], uint8_t size)
{

    // In the first step (step 1), we fina the maximum value in the array.
    uint16_t max = get_max(arr, size);

    // In the second step (step 2), we are calculating the number of digits of
    // the maximum element of the array
    uint8_t digit = get_digit(max);

    // We are now updating a new array (Steps 3,4 and 5)
    for(uint8_t i=0; i<digit; ++i)
    {
        int pwr = pow(10, i);
        uint16_t arr_temp[size];

        // This is a count_array which is used for the counting array
        // to sort digits 0 to 9.
        uint8_t count_array[10];
        memset(count_array, 0, sizeof(count_array));

        // Calculating the frequency of each element of the array
        for(uint8_t j=0; j<size; ++j)
        {
            uint8_t num = (arr[j]/pwr) % 10;
            count_array[num]++;
        }

        // This is a comulative frequency
        for(uint8_t j=1; j<10 ;++j){
            count_array[j] += count_array[j-1];
        }

        // We are mapping the frequency array with each element
        // of the array to find out desired position in the updated array
        for(int16_t j=size-1; j>=0; --j){
            uint8_t num = (arr[j]/pwr) % 10;
            arr_temp[count_array[num]-1] = arr[j];
            count_array[num]--;
        }

        // Now, we are updating the array with the new array
        for(uint8_t j=0; j<size; ++j){
            arr[j] = arr_temp[j];
        }
    }
}

