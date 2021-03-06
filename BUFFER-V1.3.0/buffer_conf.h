/*
------------------------------------------------------------------------------
~ File   : buffer_conf.h
~ Author : Majid Derhambakhsh
~ Version: V1.3.0
~ Created: 06/27/2019 08:07:00 AM
~ Brief  :
~ Support: Majid.do16@gmail.com
------------------------------------------------------------------------------
~ Description:    This driver is for create buffer from user data.
                  Support C/C++ compiler.

~ Attention  :    

~ Changes	 :
				- Add 	  : Buffer_TypeDef structure for create buffer.
				- Improve : Code structure.
				
				- Change driver name to buffer.x
------------------------------------------------------------------------------
*/
				  
#ifndef __BUFFER_CONF_H_
#define __BUFFER_CONF_H_

/* ~~~~~~~~~~~~ Configuration ~~~~~~~~~~~~ */

#define _BUFFER_LENGTH			10
#define _NUMBER_OF_OVERFLOW 	5

/*
	Guide   :
			 _BUFFER_LENGTH      : Length of buffers.
			 _NUMBER_OF_OVERFLOW : Maximum blocked overflow (Maximum value is 255).
			
	Example :
			 #define _BUFFER_LENGTH			50
			 #define _NUMBER_OF_OVERFLOW 	5
	
*/

#endif /* __BUFFER_CONFIG_H_ */
