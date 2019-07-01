/**
******************************************************************************
* @file    BUFFER.h
* @author  Majid Derhambakhsh
* @version V1.0.0
* @date    10-25-2018
* @brief
* @support Majid.do16@gmail.com
******************************************************************************
* @description  Create your data buffer
*   
* @attention    This file is for Standard C-C++ compiler 
******************************************************************************
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

#define BUFFER_LENGTH 10          /* Set the max buffer length */
#define NUMBER_OF_OVERFLOW 2      /* Set the max number of overflow */

/*----------------------------- Public -----------------------------*/   /* Set By User */


/**************************************** End Defines ****************************************/

/*--------------- Create Pointer ----------------*/

extern struct StatusFlag 
{
 
 uint8_t BufferIsFull : 1; /* This flag set when buffer is full */
 uint8_t DataSave : 1;     /* This flag set when data is saved */
 uint8_t DataPeek : 1;     /* This flag set when data is peeked and saved */
 uint8_t DataRead : 1;     /* This flag set when data is readed and saved */
 uint8_t IncIndex : 1;     /* This flag set when incremented read index */ 
        
}BufferStatus; /* Pointer for status check by user */

/*---------------- End Pointer ------------------*/

/************************************** Create Functions *************************************/

void Save_In_Buffer( uint8_t data_for_save ); /* Function for save data in the buffer */
uint16_t Available_In_Buffer(void); /* Function for check number of data in the buffer */
void Peek_From_Buffer( uint16_t number_of_peek , uint8_t *location_for_save_peeked_data ); /* Function for read data from the buffer without index increment */ 
void Read_From_Buffer( uint16_t number_of_read , uint8_t *location_for_save_readed_data ); /* Function for read data from the buffer with index increment */
void Increment_Read_Index( uint16_t number_of_increment ); /* Function for index increment */

/************************************* End Of The Program ************************************/

#ifdef __cplusplus

}

#endif

#endif
