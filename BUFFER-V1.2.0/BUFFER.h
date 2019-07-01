/*
------------------------------------------------------------------------------
~ File   : BUFFER.h
~ Author : Majid Derhambakhsh
~ Version: V1.2.0
~ Created: 05/07/2019 04:41:20 AM
~ Brief  :
~ Support: Majid.do16@gmail.com
------------------------------------------------------------------------------
~ Description:    Create your data buffer

~ Attention  :    This file is for Standard C-C++ compiler

~ Changes	 :
				- Add 	  : Clean_Buffer Function for erase all buffer data.
				- Improve : Read_From_Buffer Function.
------------------------------------------------------------------------------
*/
				  
#ifndef __BUFFER_H_

#ifdef __cplusplus

extern "C"
{

#endif

#define __BUFFER_H_

/******************** Librarys Include ********************/ 

#include <stdint.h> /* Import standard integer library */

/*************************************** Start Defines ***************************************/

/*---------------------- Define For IC Number ----------------------*/   /* Set By User */

#define _BUFFER_LENGTH 100          /* Set the max buffer length */
#define _NUMBER_OF_OVERFLOW 5      /* Set the max number of overflow */

/*----------------------------- Public -----------------------------*/   /* Set By User */

#define _TRUE  1
#define _FALSE 0

#ifndef NULL

 #define NULL '\0'
 
#endif

/**************************************** End Defines ****************************************/

/*--------------- Create Pointer ----------------*/

extern struct StatusFlag /* Pointer for status check by user */
{
 
 uint8_t BufferIsFull : 1; /* This flag set when buffer is full */
 uint8_t DataSave : 1;     /* This flag set when data is saved */
 uint8_t DataPeek : 1;     /* This flag set when data is peeked and saved */
 uint8_t DataRead : 1;     /* This flag set when data is readed and saved */
 uint8_t IncIndex : 1;     /* This flag set when incremented read index */ 
        
}BufferStatus; 

/*---------------- End Pointer ------------------*/

/************************************** Create Functions *************************************/

void Save_In_Buffer( uint8_t data_for_save ); /* Function for save data in the buffer */
uint16_t Available_In_Buffer(void); /* Function for check number of data in the buffer */
void Peek_From_Buffer( uint16_t number_of_peek , uint8_t *location_for_save_peeked_data ); /* Function for read data from the buffer without index increment */ 
void Read_From_Buffer( uint16_t number_of_read , uint8_t *location_for_save_readed_data ); /* Function for read data from the buffer with index increment */
void Increment_Read_Index( uint16_t number_of_increment ); /* Function for index increment */
void Clean_Buffer(void); /* Function for clean buffer */
uint8_t Buffer_Compare(uint8_t *str); /* Function for compare string with data buffer */

/************************************* End Of The Program ************************************/

#ifdef __cplusplus

}

#endif

#endif
