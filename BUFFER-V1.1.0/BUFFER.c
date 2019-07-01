/*
------------------------------------------------------------------------------
~ File   : BUFFER.c
~ Author : Majid Derhambakhsh
~ Version: V1.1.0
~ Created: 4/12/2019 03:09:20 AM
~ Brief  :
~ Support: Majid.do16@gmail.com
------------------------------------------------------------------------------
~ Description:    Create your data buffer

~ Attention  :    This file is for Standard C-C++ compiler

~ Changes	 :
				- Add 	  : Buffer_Compare Function for compare data.
				- Improve : Code structure.
------------------------------------------------------------------------------
*/

/******************** Librarys Include ********************/ 

#include "BUFFER.h"

/*--------------- Create Pointer ----------------*/

static struct ControllFlag 
{
 
 uint8_t BufferEnd : 1;    /* This flag set when counter buffer is end */
 uint8_t OvfControll : 3;  /* This flag is for controll the write overflow */
        
}BufferControll; /* Pointer for buffer controll */

struct StatusFlag BufferStatus; /* Pointer for status check by user */

/*--------------- Create Variable ---------------*/

static volatile uint16_t available_data_quantity = 0; /* Variable for check available data */
static volatile uint16_t write_counter=0; /* Variable for write count */
static volatile uint16_t read_counter=0; /* Variable for read count */
static uint8_t buffer[BUFFER_LENGTH]; /* Array for save data */

/********************** Functions ************************/

void Save_In_Buffer( uint8_t data_for_save ) /* Function for save data in the buffer */
{
	
	if( (( write_counter >= read_counter ) & ( BufferControll.BufferEnd == 0 )) | (( write_counter < read_counter ) & ( BufferControll.BufferEnd == 1 )) ) /* Buffer scrutiny */
	{
		
		BufferControll.OvfControll = 0; /* Reset overflow status */
		
		buffer[write_counter] = data_for_save; /* Save data in the buffer */

		/*--------------------------------------------------------------------------*/

		if( write_counter == ( BUFFER_LENGTH - 1 ) ) /* Data number scrutiny for next write */
		{
			
			write_counter = 0; /* Reset write counter */
			BufferControll.BufferEnd = 1; /* Set 'buffer end' bit */
			
		}
		else
		{
			
			write_counter++; /* Increment write counter */
			
		}
		
		/*--------------------------------------------------------------------------*/
		
		available_data_quantity = Available_In_Buffer(); /* Receive number of available data */
		
		if( available_data_quantity == BUFFER_LENGTH ) /* available data scrutiny for set 'buffer is full' bit */
		{
			
			BufferStatus.BufferIsFull = 1; /* Set 'buffer is full' bit */
			
		}
		else
		{
			
			BufferStatus.BufferIsFull = 0; /* Reset 'buffer is full' bit */
			
		}
		
		BufferStatus.DataSave = 1; /* Set 'Data is saved' bit */
		
	}
	
	/*---------------------------------------------------------------------------------------------*/
	
	else
	{
		
		BufferStatus.DataSave = 0; /* Reset 'Data is saved' bit */
		BufferControll.OvfControll += 1; /* Increment number of overflow */
		
		if( BufferControll.OvfControll == NUMBER_OF_OVERFLOW ) /* number of overflow scrutiny */
		{
			
			BufferControll.BufferEnd = 0; /* Reset 'buffer end' bit */
			
		}
		
	}
	/* End function */
}

/*-----------------------------------------------*/

uint16_t Available_In_Buffer(void) /* Function for check number of data in the buffer */
{

	if( ( write_counter >= read_counter ) & ( BufferControll.BufferEnd == 0 ) & ( BufferControll.OvfControll < NUMBER_OF_OVERFLOW ) ) /* Buffer scrutiny */
	{
		
		return ( write_counter -  read_counter ); /* Return number of data */
		
	}

	else if( ( write_counter <= read_counter ) & ( BufferControll.BufferEnd == 1 ) & ( BufferControll.OvfControll < NUMBER_OF_OVERFLOW ) ) /* Buffer scrutiny */
	{
		
		return (( BUFFER_LENGTH - read_counter ) + write_counter ); /* Return number of data */
		
	}
	
	else if( ( write_counter >= read_counter ) & ( BufferControll.BufferEnd == 0 ) & ( BufferControll.OvfControll == NUMBER_OF_OVERFLOW ) ) /* Buffer scrutiny */
	{
		
		return (( BUFFER_LENGTH - read_counter ) + write_counter ); /* Return number of data */
		
	}
	
	else
	{
		/* Data don't return */
	}
	/* Function End */
	
}

/*-----------------------------------------------*/

void Peek_From_Buffer( uint16_t number_of_peek , uint8_t *location_for_save_peeked_data ) /* Function for read data from the buffer without index increment */
{
	
	/*------------------------- Create variable -------------------------*/
	
	uint16_t peek_counter = read_counter; /* Variable for count data read */
	
	/*-------------------------------------------------------------------*/
	
	available_data_quantity = Available_In_Buffer(); /* Receive number of available data */
	
	if( available_data_quantity >= number_of_peek ) /* Number of data scrutiny */
	{
		
		for( ; number_of_peek > 0 ; number_of_peek-- ) /* Loop for data copy */
		{
			
			*location_for_save_peeked_data = buffer[ peek_counter ]; /* Copy data in the data location */
			
			location_for_save_peeked_data++; /* Increment 'location for save peeked data' for select next location */
			peek_counter++; /* Increment 'peek counter' for select next data byte */
			
			if( peek_counter == BUFFER_LENGTH ) /* Check for end buffer length */
			{
				
				peek_counter = 0; /* Set new address */
				
			}
			
		} 
		/* End loop */	
		BufferStatus.DataPeek = 1; /* Set 'data is peeked' bit */
			
	}
		
	/*-------------------------------------------------------------------*/
		
	else
	{
			
		BufferStatus.DataPeek = 0; /* Reset 'data is peeked' bit */
			
	}
	/* Function End */
	
}

/*-----------------------------------------------*/

void Read_From_Buffer( uint16_t number_of_read , uint8_t *location_for_save_readed_data ) /* Function for read data from the buffer with index increment */
{

	available_data_quantity = Available_In_Buffer(); /* Receive number of available data */
	
	if( available_data_quantity >= number_of_read ) /* Number of data scrutiny */
	{
		
		for( ; number_of_read > 0 ; number_of_read-- ) /* Loop for data copy */
		{
			*location_for_save_readed_data = buffer[ read_counter ]; /* Copy data in the data location */

			location_for_save_readed_data++; /* Increment 'location for save peeked data' for select next location */
			read_counter++; /* Increment 'peek counter' for select next data byte */
			
			if( read_counter == BUFFER_LENGTH ) /* Check for end buffer length */
			{
				
				BufferControll.BufferEnd = 0; /* Reset 'buffer end' flag */
				read_counter = 0; /* Set new address */
				
			}
			
		}
		/* End loop */
		BufferStatus.DataRead = 1; /* Set 'data read' flag */
		BufferStatus.BufferIsFull = 0; /* Reset 'buffer is full' flag */
		
	}
	
	/*-------------------------------------------------------------------*/
	
	else
	{
		
		BufferStatus.DataRead = 0; /* Reset 'data read' flag */
		
	}
	/* Function End */

}

/*-----------------------------------------------*/

void Increment_Read_Index( uint16_t number_of_increment ) /* Function for index increment */
{
	
	available_data_quantity = Available_In_Buffer(); /* Receive number of available data */
	
	if( available_data_quantity >= number_of_increment ) /* Number of data scrutiny */
	{
		
		read_counter += number_of_increment; /* Increment read counter */
		
		if( read_counter >= BUFFER_LENGTH ) /* Check buffer and set the length */
		{
			
			BufferControll.BufferEnd = 0; /* Reset 'buffer end' flag */
			read_counter -= BUFFER_LENGTH; /* Set the length */
			
		}
		
		BufferStatus.IncIndex = 1; /* Set 'inc index' flag*/
		
	}

	/*-------------------------------------------------------------------*/
	
	else
	{
		
		BufferStatus.IncIndex = 0; /* Reset 'inc index' flag*/
		
	}
	/* Function End */

}

/*-----------------------------------------------*/

uint8_t Buffer_Compare(uint8_t *str) /* Function for compare string with data buffer */
{
	/*------------------------- Create variable -------------------------*/
	
	uint8_t *first_address = str; /* Variable for keep first string address */
	uint16_t data_counter = read_counter; /* Variable for read count */
	uint16_t correct_characters = 0; /* Variable for count correct characters */
	uint16_t input_data_quantity = 0; /* Variable for count number of str data */

	/*-------------------------------------------------------------------*/
	
	available_data_quantity = Available_In_Buffer(); /* Receive number of available data */
	
	while ( *str != NULL )
	{
		str++; /* Select next byte */
		input_data_quantity++; /* Increment value */
	}

	/* ------------------------- */

	str = first_address; /* Go to first address */

	/* ------------------------- */

	while ( (*str != NULL) && (available_data_quantity > 0) ) /* Loop for string check */
	{
		
		if ( *str == buffer[data_counter] ) /* Character is correct */
		{
			str++; /* Select next byte */
			correct_characters++; /* Increment count correct characters */
		}
		else
		{
			str = first_address; /* Go to first address */
			correct_characters = 0; /* Reset count correct characters */
		}
		
		data_counter++; /* Select next byte */
		
		if ( data_counter > BUFFER_LENGTH ) /* Check value */
		{
			data_counter = 0; /* Reset value */
		}
		
		available_data_quantity--; /* Decrement value */
		
	}
	
	/*-------------------------------------------------------------------*/
	
	if ( correct_characters == input_data_quantity ) /* Check value */
	{
		return _TRUE;
	}
	else
	{
		return _FALSE;
	}
	/* Function End */
	
}

/* Program End */