/*
 * lcd.c
 *
 *  Created on: Sep 13, 2021
 *      Author: Bheem
 */

#include <lcd.h>

/*--------------- Initialize LCD ------------------*/

void lcd_init(void)
{

	HAL_Delay(30);

	PIN_LOW(lcd_d4_GPIO_Port, lcd_d4_Pin);
	PIN_HIGH(lcd_d5_GPIO_Port, lcd_d5_Pin);
	PIN_LOW(lcd_d6_GPIO_Port, lcd_d6_Pin);
	PIN_LOW(lcd_d7_GPIO_Port, lcd_d7_Pin);
	PIN_LOW(lcd_rs_GPIO_Port, lcd_rs_Pin);
	PIN_HIGH(lcd_Enable_GPIO_Port, lcd_Enable_Pin);
	PIN_LOW(lcd_Enable_GPIO_Port, lcd_Enable_Pin);

	HAL_Delay(50);

	lcd_write(0, 0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_write(0, 0x0c);
	HAL_Delay(1);
	lcd_write(0, 0x06); // Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_write(0, 0x01); // clear display
	HAL_Delay(1);
	lcd_write(0, 0x80); // clear display
	HAL_Delay(1);
}

/*--------------- Write To LCD ---------------*/
void lcd_write(uint8_t type, uint8_t data)
{
	HAL_Delay(2);
	if (type)
	{
		PIN_HIGH(lcd_rs_GPIO_Port, lcd_rs_Pin);
	}
	else
	{
		PIN_LOW(lcd_rs_GPIO_Port, lcd_rs_Pin);
	}

	// Send High Nibble
	if (data & 0x80)
	{
		PIN_HIGH(lcd_d7_GPIO_Port, lcd_d7_Pin);
	}
	else
	{
		PIN_LOW(lcd_d7_GPIO_Port, lcd_d7_Pin);
	}

	if (data & 0x40)
	{
		PIN_HIGH(lcd_d6_GPIO_Port, lcd_d6_Pin);
	}
	else
	{
		PIN_LOW(lcd_d6_GPIO_Port, lcd_d6_Pin);
	}

	if (data & 0x20)
	{
		PIN_HIGH(lcd_d5_GPIO_Port, lcd_d5_Pin);
	}
	else
	{
		PIN_LOW(lcd_d5_GPIO_Port, lcd_d5_Pin);
	}

	if (data & 0x10)
	{
		PIN_HIGH(lcd_d4_GPIO_Port, lcd_d4_Pin);
	}
	else
	{
		PIN_LOW(lcd_d4_GPIO_Port, lcd_d4_Pin);
	}
	PIN_HIGH(lcd_Enable_GPIO_Port, lcd_Enable_Pin);
	PIN_LOW(lcd_Enable_GPIO_Port, lcd_Enable_Pin);

	// Send Low Nibble
	if (data & 0x08)
	{
		PIN_HIGH(lcd_d7_GPIO_Port, lcd_d7_Pin);
	}
	else
	{
		PIN_LOW(lcd_d7_GPIO_Port, lcd_d7_Pin);
	}

	if (data & 0x04)
	{
		PIN_HIGH(lcd_d6_GPIO_Port, lcd_d6_Pin);
	}
	else
	{
		PIN_LOW(lcd_d6_GPIO_Port, lcd_d6_Pin);
	}

	if (data & 0x02)
	{
		PIN_HIGH(lcd_d5_GPIO_Port, lcd_d5_Pin);
	}
	else
	{
		PIN_LOW(lcd_d5_GPIO_Port, lcd_d5_Pin);
	}

	if (data & 0x01)
	{
		PIN_HIGH(lcd_d4_GPIO_Port, lcd_d4_Pin);
	}
	else
	{
		PIN_LOW(lcd_d4_GPIO_Port, lcd_d4_Pin);
	}
	PIN_HIGH(lcd_Enable_GPIO_Port, lcd_Enable_Pin);
	PIN_LOW(lcd_Enable_GPIO_Port, lcd_Enable_Pin);
}

void lcd_puts(uint8_t x, uint8_t y, int8_t *string)
{
// Set Cursor Position
#ifdef LCD16xN // For LCD16x2 or LCD16x4
	switch (x)
	{
	case 0: // Row 0
		lcd_write(0, 0x80 + 0x00 + y);
		break;
	case 1: // Row 1
		lcd_write(0, 0x80 + 0x40 + y);
		break;
	case 2: // Row 2
		lcd_write(0, 0x80 + 0x10 + y);
		break;
	case 3: // Row 3
		lcd_write(0, 0x80 + 0x50 + y);
		break;
	}
#endif

#ifdef LCD20xN // For LCD20x4
	switch (x)
	{

	case 0: // Row 0
		lcd_write(0, 0x80 + 0x00 + y);
		break;
	case 1: // Row 1
		lcd_write(0, 0x80 + 0x40 + y);
		break;
	case 2: // Row 2
		lcd_write(0, 0x80 + 0x14 + y);
		break;
	case 3: // Row 3
		lcd_write(0, 0x80 + 0x54 + y);
		break;
	}
#endif

	while (*string)
	{
		lcd_write(1, *string);
		string++;
	}
}

// void clr_data(uint8_t pos)
//{
//
//	switch (pos)
//	{
//	case _intensity:
//		lcd_puts(1, 7, (int8_t *)"  ");
//		lcd_puts(1, 8, (int8_t *)"  ");
//		lcd_puts(1, 9, (int8_t *)"  ");
//		break;
//	case _color:
//		lcd_puts(2, 7, (int8_t *)"  ");
//		break;
//	case _sensor:
//		lcd_puts(3, 7, (int8_t *)"  ");
//		lcd_puts(3, 8, (int8_t *)"  ");
//		lcd_puts(3, 9, (int8_t *)"  ");
//		break;
//
//	case _lamp:
//		lcd_puts(1, 17, (int8_t *)"  ");
//		lcd_puts(1, 18, (int8_t *)"  ");
//		lcd_puts(1, 19, (int8_t *)"  ");
//		break;
//	case _endo:
//		lcd_puts(2, 17, (int8_t *)"  ");
//		lcd_puts(2, 18, (int8_t *)"  ");
//		lcd_puts(2, 19, (int8_t *)"  ");
//		break;
//	case _depth:
//		lcd_puts(3, 17, (int8_t *)" ");
//		lcd_puts(3, 18, (int8_t *)" ");
//		lcd_puts(3, 19, (int8_t *)" ");
//		break;
//
//	case _focus:
//		lcd_puts(0, 10, (int8_t *)" ");
//		lcd_puts(0, 11, (int8_t *)" ");
//		lcd_puts(0, 12, (int8_t *)" ");
//		lcd_puts(0, 13, (int8_t *)" ");
//		lcd_puts(0, 14, (int8_t *)" ");
//		lcd_puts(0, 15, (int8_t *)" ");
//		break;
//
//
//	case _small:
//		lcd_puts(1, 10, (int8_t *)" ");
//		lcd_puts(1, 10, (int8_t *)" ");
//		lcd_puts(1, 10, (int8_t *)" ");
//		break;
//
//
//
//	case _medium:
//		lcd_puts(2, 10, (int8_t *)" ");
//		lcd_puts(2, 10, (int8_t *)" ");
//		lcd_puts(2, 10, (int8_t *)" ");
//		break;
//
//
//	case _wide:
//		lcd_puts(3, 10, (int8_t *)" ");
//		lcd_puts(3, 10, (int8_t *)" ");
//		lcd_puts(3, 10, (int8_t *)" ");
//		break;
//	}
// }
void clr_select()
{
	lcd_puts(1, 0, (int8_t *)" ");
	lcd_puts(2, 0, (int8_t *)" ");
	lcd_puts(3, 0, (int8_t *)" ");
	lcd_puts(1, 10, (int8_t *)" ");
	lcd_puts(2, 10, (int8_t *)" ");
	lcd_puts(3, 10, (int8_t *)" ");
}
void lcd_clear(void)
{
	lcd_write(0, 0x01);
	lcd_puts(0, 0, (int8_t *)"                     ");
	lcd_puts(1, 0, (int8_t *)"                     ");
	lcd_puts(2, 0, (int8_t *)"                     ");
	lcd_puts(3, 0, (int8_t *)"                     ");
	// lcd_puts(1, 10, (int8_t *)"                    ");
	// lcd_puts(2, 10, (int8_t *)" ");
	// lcd_puts(3, 10, (int8_t *)" ");
}

void default_lcd_print_page1(void)
{
	// lcd_puts(0, 0, (int8_t *)"                   ");
	lcd_puts(1, 7, (int8_t *)"STANDBY");
	// lcd_puts(2, 0, (int8_t *)"                   ");
	// lcd_puts(3, 0, (int8_t *)"                   ");
}
void default_lcd_print_page2(void)
{

	lcd_puts(0, 1, (int8_t *)"TIME :");
	lcd_puts(1, 1, (int8_t *)"DATE :");
	lcd_puts(2, 1, (int8_t *)"BATT :");
	lcd_puts(3, 1, (int8_t *)"CHRG :");
	lcd_puts(2,11, (int8_t *)"WATT :");
}

void default_lcd_print_page3(void)
{

	lcd_puts(0, 1, (int8_t *)"DC_9V :");
	lcd_puts(1, 1, (int8_t *)"DC_12V:");
	lcd_puts(2, 1, (int8_t *)"AC    :");
	lcd_puts(0,12, (int8_t *)"QC :");
	lcd_puts(1,12, (int8_t *)"PD :");
}
