/*
------------------------------------------------------------------------------
~ File   : buffer.c
~ Author : Majid Derhambakhsh
~ Version: V1.4.0
~ Created: 07/23/2019 02:55:00 AM
~ Brief  :
~ Support: Majid.do16@gmail.com
------------------------------------------------------------------------------
~ Description:    This driver is for create buffer from user data.
                  Support C/C++ compiler.

~ Attention  :    

~ Changes	 :
				- Add 	  : vector of available data in buffer compare function.
------------------------------------------------------------------------------
*/

/******************** Librarys Include ********************/ 

#include "buffer.h"

/********************** Functions ************************/

void Buffer_Init( Buffer_TypeDef *ubuffer) /* This function is for initialize buffer */
{
	
	ubuffer -> DataControl.AvbData = 0; /* Set default value */
	ubuffer -> DataControl.ReadCounter   = 0; /* Set default value */
	ubuffer -> DataControl.WriteCounter  = 0; /* Set default value */
	
}
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
			 Return Values :
			
	Example :
				BufferTypeDef usart_buffer;
				
				Buffer_Init(&usart_buffer);
				
*/

/*-----------------------------------------------*/

void Save_In_Buffer( Buffer_TypeDef *ubuffer, uint8_t udata ) /* Function for save data in the buffer */
{
	
	if( (( ubuffer -> DataControl.WriteCounter >= ubuffer -> DataControl.ReadCounter ) && ( ubuffer -> ControlFlags.BuffEnd == 0 )) || (( ubuffer -> DataControl.WriteCounter < ubuffer -> DataControl.ReadCounter ) && ( ubuffer -> ControlFlags.BuffEnd == 1 )) ) /* Buffer scrutiny */
	{
		
		ubuffer -> ControlFlags.OvfControl = 0; /* Reset overflow status */
		
		ubuffer -> Data[ubuffer -> DataControl.WriteCounter] = udata; /* Save data in the buffer */
		
		/*--------------------------------------------------------------------------*/
		
		if( ubuffer -> DataControl.WriteCounter == ( _BUFFER_LENGTH - 1 ) ) /* Data number scrutiny for next write */
		{
			
			ubuffer -> DataControl.WriteCounter = 0; /* Reset write counter */
			ubuffer -> ControlFlags.BuffEnd = 1; /* Set 'buffer end' bit */
			
		}
		else
		{
			
			ubuffer -> DataControl.WriteCounter++; /* Increment write counter */
			
		}
		
		/*--------------------------------------------------------------------------*/
		
		//buff_x -> DataController.available_data_quantity = Available_In_Buffer(); /* Receive number of available data */
		
		if( ubuffer -> DataControl.AvbData == _BUFFER_LENGTH ) /* available data scrutiny for set 'buffer is full' bit */
		{
			
			ubuffer -> Status.BufferIsFull = 1; /* Set 'buffer is full' bit */
			
		}
		else
		{
			
			ubuffer -> Status.BufferIsFull = 0; /* Reset 'buffer is full' bit */
			
		}
		
		ubuffer -> Status.DataSave = 1; /* Set 'Data is saved' bit */
		
	}
	
	/*---------------------------------------------------------------------------------------------*/
	
	else
	{
		
		ubuffer -> Status.DataSave = 0; /* Reset 'Data is saved' bit */
		ubuffer -> ControlFlags.OvfControl += 1; /* Increment number of overflow */
		
		if( ubuffer -> ControlFlags.OvfControl == _NUMBER_OF_OVERFLOW ) /* number of overflow scrutiny */
		{
			
			ubuffer -> ControlFlags.BuffEnd = 0; /* Reset 'buffer end' bit */
			
		}
		
	}
	/* End function */
}
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

/*-----------------------------------------------*/

uint16_t Available_In_Buffer(Buffer_TypeDef *ubuffer) /* Function for check number of data in the buffer */
{
	
	uint16_t avb_data = _FALSE; /* Available data */
	
	if( ( ubuffer -> DataControl.WriteCounter >= ubuffer -> DataControl.ReadCounter ) && ( ubuffer -> ControlFlags.BuffEnd == 0 ) && ( ubuffer -> ControlFlags.OvfControl < _NUMBER_OF_OVERFLOW ) ) /* Buffer scrutiny */
	{
		
		avb_data = ( ubuffer -> DataControl.WriteCounter -  ubuffer -> DataControl.ReadCounter ); /* Return number of data */
		
	}
	else if( ( ubuffer -> DataControl.WriteCounter <= ubuffer -> DataControl.ReadCounter ) && ( ubuffer -> ControlFlags.BuffEnd == 1 ) && ( ubuffer -> ControlFlags.OvfControl < _NUMBER_OF_OVERFLOW ) ) /* Buffer scrutiny */
	{
		
		avb_data = (( _BUFFER_LENGTH - ubuffer -> DataControl.ReadCounter ) + ubuffer -> DataControl.WriteCounter ); /* Return number of data */
		
	}
	else if( ( ubuffer -> DataControl.WriteCounter >= ubuffer -> DataControl.ReadCounter ) && ( ubuffer -> ControlFlags.BuffEnd == 0 ) && ( ubuffer -> ControlFlags.OvfControl == _NUMBER_OF_OVERFLOW ) ) /* Buffer scrutiny */
	{
		
		avb_data = (( _BUFFER_LENGTH - ubuffer -> DataControl.ReadCounter ) + ubuffer -> DataControl.WriteCounter ); /* Return number of data */
		
	}
	else
	{
		/* Data don't return */
	}
	
	return avb_data;
	
	/* Function End */
}
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

/*-----------------------------------------------*/

void Peek_From_Buffer( Buffer_TypeDef *ubuffer, uint8_t *udata, uint16_t size ) /* Function for read data from the buffer without index increment */
{
	
	/*------------------------- Create variable -------------------------*/
	
	uint16_t peek_counter = ubuffer -> DataControl.ReadCounter; /* Variable for count data read */
	
	/*-------------------------------------------------------------------*/
	
	ubuffer -> DataControl.AvbData = Available_In_Buffer(ubuffer); /* Receive number of available data */
	
	if( ubuffer -> DataControl.AvbData >= size ) /* Number of data scrutiny */
	{
		
		for( ; size > 0 ; size-- ) /* Loop for data copy */
		{
			
			*udata = ubuffer -> Data[ peek_counter ]; /* Copy data in the data location */
			
			udata++; /* Increment 'location for save peeked data' for select next location */
			peek_counter++; /* Increment 'peek counter' for select next data byte */
			
			if( peek_counter == _BUFFER_LENGTH ) /* Check for end buffer length */
			{
				peek_counter = 0; /* Set new address */
			}
			
		}
		
		ubuffer -> Status.DataPeek = 1; /* Set 'data is peeked' bit */
		
	}
		
	/*-------------------------------------------------------------------*/
		
	else
	{
		ubuffer -> Status.DataPeek = 0; /* Reset 'data is peeked' bit */
	}
	
	/* Function End */
}
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

/*-----------------------------------------------*/

void Read_From_Buffer( Buffer_TypeDef *ubuffer, uint8_t *udata, uint16_t size ) /* Function for read data from the buffer with index increment */
{
	
	ubuffer -> DataControl.AvbData = Available_In_Buffer(ubuffer); /* Receive number of available data */
	
	if( ubuffer -> DataControl.AvbData >= size ) /* Number of data scrutiny */
	{
		
		for( ; size > 0 ; size-- ) /* Loop for data copy */
		{
			
			*udata = ubuffer -> Data[ ubuffer -> DataControl.ReadCounter ]; /* Copy data in the data location */
			ubuffer -> Data[ubuffer -> DataControl.ReadCounter] = NULL;
			
			udata++; /* Increment 'location for save peeked data' for select next location */
			ubuffer -> DataControl.ReadCounter++; /* Increment 'peek counter' for select next data byte */
			
			if( ubuffer -> DataControl.ReadCounter == _BUFFER_LENGTH ) /* Check for end buffer length */
			{
				
				ubuffer -> ControlFlags.BuffEnd = 0; /* Reset 'buffer end' flag */
				ubuffer -> DataControl.ReadCounter = 0; /* Set new address */
				
			}
			
		}
		
		ubuffer -> Status.DataRead = 1; /* Set 'data read' flag */
		ubuffer -> Status.BufferIsFull = 0; /* Reset 'buffer is full' flag */
		
	}
	
	/*-------------------------------------------------------------------*/
	
	else
	{
		ubuffer -> Status.DataRead = 0; /* Reset 'data read' flag */
	}
	
	/* Function End */
}
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

/*-----------------------------------------------*/

void Increment_Read_Index( Buffer_TypeDef *ubuffer,uint16_t size ) /* Function for index increment */
{
	
	ubuffer -> DataControl.AvbData = Available_In_Buffer(ubuffer); /* Receive number of available data */
	
	if( ubuffer -> DataControl.AvbData >= size ) /* Number of data scrutiny */
	{
		
		ubuffer -> DataControl.ReadCounter += size; /* Increment read counter */
		
		if( ubuffer -> DataControl.ReadCounter >= _BUFFER_LENGTH ) /* Check buffer and set the length */
		{
			
			ubuffer -> ControlFlags.BuffEnd = 0; /* Reset 'buffer end' flag */
			ubuffer -> DataControl.ReadCounter -= _BUFFER_LENGTH; /* Set the length */
			
		}
		
		ubuffer -> Status.IncIndex = 1; /* Set 'inc index' flag*/
		
	}
	
	/*-------------------------------------------------------------------*/
	
	else
	{
		ubuffer -> Status.IncIndex = 0; /* Reset 'inc index' flag*/
	}
	
	/* Function End */
}
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

/*-----------------------------------------------*/

void Clean_Buffer(Buffer_TypeDef *ubuffer) /* Function for clean buffer */
{
	
	/* ------------- Variable ------------- */
	
	uint32_t cleaner_counter = 0; /* Variable for count values */
	
	/* -------------- Reload -------------- */
	
	ubuffer -> DataControl.WriteCounter = 0; /* Reset value */
	ubuffer -> DataControl.ReadCounter = 0; /* Reset value */
	
	ubuffer -> ControlFlags.BuffEnd = _FALSE; /* Reset flag */
	ubuffer -> ControlFlags.OvfControl = _FALSE; /* Reset flag */
	
	/* ------------------------------------ */
	
	while ( cleaner_counter < _BUFFER_LENGTH ) /* Loop for clean buffer data */
	{
		
		ubuffer -> Data[cleaner_counter] = NULL; /* Set value */
		cleaner_counter++; /* Select next data */
		
	}
	
	/* Function End */
}
/*
	Guide   :
			 Parameters    :
							ubuffer : Pointer to user buffer.
			 Return Values :
			
	Example :
				BufferTypeDef usart_buffer;
				
				Clean_Buffer(&usart_buffer);
				
*/

/*-----------------------------------------------*/

uint8_t Buffer_Compare( Buffer_TypeDef *ubuffer,uint8_t *udata,uint16_t *vect) /* Function for compare string with data buffer */
{
	/*------------------------- Create variable -------------------------*/
	
	uint8_t stat = _FALSE; /* status variable */
	uint8_t *first_address = udata; /* Variable for keep first string address */
	uint16_t data_counter = ubuffer -> DataControl.ReadCounter; /* Variable for read count */
	uint16_t correct_characters = 0; /* Variable for count correct characters */
	uint16_t input_data_quantity = 0; /* Variable for count number of udata data */
	
	/*-------------------------------------------------------------------*/
	
	ubuffer -> DataControl.AvbData = Available_In_Buffer(ubuffer); /* Receive number of available data */
	
	while ( *udata != NULL )
	{
		udata++; /* Select next byte */
		input_data_quantity++; /* Increment value */
	}
	
	/*-------------------------------------------------------------------*/
	
	udata = first_address; /* Go to first address */
	
	/*-------------------------------------------------------------------*/
	
	while ( (*udata != NULL) && (ubuffer -> DataControl.AvbData > 0) ) /* Loop for string check */
	{
		
		stat++; /* Increase for get vector */
		
		/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
		
		if ( *udata == ubuffer -> Data[data_counter] ) /* Character is correct */
		{
			
			if (correct_characters == 0)
			{
				*vect = stat; /* Set vector */
			}
			
			/* ------------------------- */
			
			udata++; /* Select next byte */
			correct_characters++; /* Increment count correct characters */
			
		}
		else
		{
			
			udata = first_address; /* Go to first address */
			correct_characters = 0; /* Reset count correct characters */
			*vect = 0; /* Reset vector */
			
		}
		
		/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
		
		data_counter++; /* Select next byte */
		
		if ( data_counter > _BUFFER_LENGTH ) /* Check value */
		{
			data_counter = 0; /* Reset value */
		}
		
		ubuffer -> DataControl.AvbData--; /* Decrement value */
		
	}
	
	/*-------------------------------------------------------------------*/
	
	if ( correct_characters == input_data_quantity ) /* Check value */
	{
		stat = _TRUE;
	}
	else
	{
		stat = _FALSE;
	}
	
	return stat;
	
	/* Function End */
}
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

/* Program End */
