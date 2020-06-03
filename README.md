
# BUFFER-Library
This program module is for create your data buffer.

### Version : 0.0.0

- #### Type : Universal Software.

- #### Support : All C/C++ compiler.

- #### Program Language : C

- #### Properties :

### Initialization and de-initialization functions:
- Buffer_Init()

### Operation functions:
- Save_In_Buffer()
- Available_In_Buffer()
- Peek_From_Buffer()
- Read_From_Buffer()
- Increment_Read_Index()
- Clean_Buffer()
- Buffer_Compare()

### Macros:
- _BUFFER_LENGTH
- _NUMBER_OF_OVERFLOW

## How to use this library

### The Buffer library can be used as follows:
#### 1.  Add .h and source file in project.      
#### 2.  Config buffer options in 'buffer_conf.h' header, for example:  
   * Options:  
      ```c++
      #define _BUFFER_LENGTH        10
      #define _NUMBER_OF_OVERFLOW   5
      ```
   * Parameters:  
      * _BUFFER_LENGTH      : Length of buffer  
      * _NUMBER_OF_OVERFLOW : Number of overflows  
          
          
#### 3.  Create Buffers and initialize it, for example:           
* Example:
  ```c++  
  Buffer_TypeDef serialDataBuff;
  Buffer_TypeDef sensorDataBuff;
   
  Buffer_Init(&serialDataBuff);
  Buffer_Init(&sensorDataBuff);
   
  ``` 
     
#### 4.  Using operation methods for manage data, for example:  
```c++
int main(void)
{
   
   int nmbOfData = 0;
      
   Buffer_TypeDef serialDataBuff;
   Buffer_TypeDef sensorDataBuff;
   
   Buffer_Init(&serialDataBuff);
   Buffer_Init(&sensorDataBuff);
      
   while()
   {
     Save_In_Buffer(&serialDataBuff, 'a');
     Save_In_Buffer(&sensorDataBuff, 15);
     
     nmbOfData = Available_In_Buffer(&serialDataBuff); /* nmbOfData is number of available data in buffer */
     
     if (nmbOfData > 5)
     {
       Clean_Buffer(&serialDataBuff);
     }
     
   }
}
   
``` 
    
## Buffer Type:
- [ ] Linear
- [x] Circular 

#### Developer: Majid Derhambakhsh
