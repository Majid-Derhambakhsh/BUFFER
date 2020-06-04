/*
------------------------------------------------------------------------------
~ File   : buffer.h
~ Author : Majid Derhambakhsh
~ Version: V1.4.0
~ Created: 07/23/2019 02:55:00 AM
~ Brief  :
~ Support: Majid.do16@gmail.com
------------------------------------------------------------------------------
~ Description:    This driver is for create buffer from user data.
                  Support C/C++ compiler.

~ Attention  :    This file is for Standard C-C++ compiler

~ Changes	 :
				- Add 	  : vector of available data in buffer compare function.
------------------------------------------------------------------------------
*/
				  
#ifndef __BUFFER_H_
#define __BUFFER_H_

#ifdef __cplusplus

extern "C"
{

#endif /* __cplusplus */

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Library Include ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */ 

#include "buffer_conf.h" /* Import config file */

#include <stdint.h> /* Import standard integer library */

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Start Defines ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

/*----------------------------- Public -----------------------------*/

#ifndef _TRUE

 #define _TRUE  1 /* True value */

#endif

#ifndef _FALSE

 #define _FALSE 0 /* False value */

#endif

#ifndef NULL

 #define NULL '\0' /* Null value */
 
#endif

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Structure ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

typedef struct /* Structure for buffer control */
{
	
	uint8_t BuffEnd : 1;    /* This flag set when counter buffer is end */
	uint8_t OvfControl : 8;  /* This flag is for control the write overflow */
	
}ControllFlagTypeDef;

typedef struct /* Structure for data control */
{
	
	uint16_t AvbData; /* Variable for check available data */
	uint16_t WriteCounter; /* Variable for write count */
	uint16_t ReadCounter; /* Variable for read count */
	
}DataControllerTypeDef;

typedef struct /* Structure for status check by user */
{
 
 uint8_t BufferIsFull : 1; /* This flag set when buffer is full */
 uint8_t DataSave     : 1; /* This flag set when data is saved */
 uint8_t DataPeek     : 1; /* This flag set when data is peeked and saved */
 uint8_t DataRead     : 1; /* This flag set when data is read and saved */
 uint8_t IncIndex     : 1; /* This flag set when incremented read index */ 
 
}BufferStatusTypeDef; 

typedef struct /* Structure for create buffer */
{
	
	ControllFlagTypeDef   ControlFlags; /* Buffer control */
	DataControllerTypeDef DataControl; /* Data control */
	BufferStatusTypeDef   Status; /* Check buffer status */
	
	uint8_t Data[_BUFFER_LENGTH]; /* User data */
	
}Buffer_TypeDef;

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Prototype ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

void Buffer_Init( Buffer_TypeDef *ubuffer); /* This function is for initialize buffer */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
			 Return Values :
			
	Example :
				BufferTypeDef usart_buffer;
				
				Buffer_Init(&usart_buffer);
				
*/

void Save_In_Buffer( Buffer_TypeDef *ubuffer, uint8_t udata ); /* Function for save data in the buffer */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
							udata   : Data for save in buffer.
							
			 Return Values :
	
	Example :
				uint8_t usart_data;
				BufferTypeDef usart_buffer;
				
				Save_In_Buffer(&usart_buffer , usart_data);
				
*/

uint16_t Available_In_Buffer(Buffer_TypeDef *ubuffer); /* Function for check number of data in the buffer */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
							
			 Return Values :
							available data in buffer.
			
	Example :
				uint8_t number_of_available_data;
				BufferTypeDef usart_buffer;
				
				number_of_available_data = Available_In_Buffer(&usart_buffer);
				
					result is between 0 ~ x
				
*/

void Peek_From_Buffer( Buffer_TypeDef *ubuffer, uint8_t *udata, uint16_t size ); /* Function for read data from the buffer without index increment */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
							udata   : Pointer for save peeked data from buffer.
							size    : Amount of data to be peek.
							
			 Return Values :
			
	Example :
				uint8_t my_data[20];
				BufferTypeDef usart_buffer;
				
				Peek_From_Buffer(&usart_buffer , 10 , my_data);
				
*/

void Read_From_Buffer( Buffer_TypeDef *ubuffer, uint8_t *udata, uint16_t size ); /* Function for read data from the buffer with index increment */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
							udata   : Pointer for save peeked data from buffer.
							size    : Amount of data to be peek.
							
			 Return Values :
			
	Example :
				uint8_t my_data[20];
				BufferTypeDef usart_buffer;
				
				Read_From_Buffer(&usart_buffer , 10 , my_data);
				
*/

void Increment_Read_Index( Buffer_TypeDef *ubuffer,uint16_t size ); /* Function for index increment */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
							size    : Amount of increment.
							
			 Return Values :
			
	Example :
				BufferTypeDef usart_buffer;
				
				Increment_Read_Index(&usart_buffer , 13);
				
*/

void Clean_Buffer(Buffer_TypeDef *ubuffer); /* Function for clean buffer */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
			 Return Values :
			
	Example :
				BufferTypeDef usart_buffer;
				
				Clean_Buffer(&usart_buffer);
				
*/

uint8_t Buffer_Compare( Buffer_TypeDef *ubuffer,uint8_t *udata,uint16_t *vect); /* Function for compare string with data buffer */
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
							udata   : Pointer for save peeked data from buffer.
							vect    : vector of first available data byte.
							
			 Return Values :
							_TRUE / _FALSE
			
	Example :
				uint8_t result;
				uint16_t data_vect;
				BufferTypeDef usart_buffer;
				
				result = Buffer_Compare(&usart_buffer, "HELLO", &data_vect);
				
					result is _TRUE or _FALSE
				
*/

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ End Of The Program ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /* __BUFFER_H_ */
