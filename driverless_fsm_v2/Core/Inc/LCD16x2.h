/*
 * LCD16x2.h
 *
 *  Created on: Aug 27, 2021
 *      Author: issacjy
 */

#ifndef LCD16X2_H_
#define LCD16X2_H_

#include "stm32l4xx_hal.h"

typedef struct
{
    GPIO_TypeDef * GPIO_GROUP_D4;
    uint16_t D4_PIN;
    GPIO_TypeDef * GPIO_GROUP_D5;
    uint16_t D5_PIN;
    GPIO_TypeDef * GPIO_GROUP_D6;
    uint16_t D6_PIN;
    GPIO_TypeDef * GPIO_GROUP_D7;
    uint16_t D7_PIN;
    GPIO_TypeDef * GPIO_GROUP_EN;
    uint16_t EN_PIN;
    GPIO_TypeDef * GPIO_GROUP_RS;
    uint16_t RS_PIN;
    uint16_t LCD_EN_Delay;
}LCD16x2_CfgType;


//-----[ Prototypes For All Functions ]-----

void LCD_Init();                  // Initialize The LCD For 4-Bit Interface
void LCD_Clear();                 // Clear The LCD Display
void LCD_SL();                    // Shift The Entire Display To The Left
void LCD_SR();                    // Shift The Entire Display To The Right
void LCD_CMD(unsigned char);      // Send Command To LCD
void LCD_DATA(unsigned char);     // Send 4-Bit Data To LCD
void LCD_Set_Cursor(unsigned char, unsigned char);  // Set Cursor Position
void LCD_Write_Char(char);        // Write Character To LCD At Current Position
void LCD_Write_String(char*);     // Write A String To LCD


#endif /* LCD16X2_H_ */
