/*
 * lcd1602_i2c_lib.h
 *
 *  Библиотека для китайских дисплеев
 *  Created on: Nov 24, 2020
 *      Authors: Oleg Volkov & Konstantin Golinskiy
 *      Создать свой символ: https://www.quinapalus.com/hd44780udg.html
 */

#ifndef INC_LCD1602_I2C_LIB_H_
#define INC_LCD1602_I2C_LIB_H_

// подключаем  библиотеки
#include <main.h>
#include <string.h>
#include <stdbool.h>
#include <stm32f4xx_hal.h> // стандартная для работы готовой библиотеки
#include <stdio.h>// для работы функции обработки текста

/*В соответствии с документацией на используемый модуль  прописываем команды
для ножек экрана, E, RS, RW,  а так же включение подсветки*/
#define e_set()      	WriteByteI2CLCD(portlcd|=0x04) //установка E в 1
#define e_reset()   	WriteByteI2CLCD(portlcd&=~0x04)  // сброс  E в 0
#define rs_set()      	WriteByteI2CLCD(portlcd|=0x01) // установка RS в 1
#define rs_reset()   	WriteByteI2CLCD(portlcd&=~0x01)  // сброс RS в 0
#define setled()      	WriteByteI2CLCD(portlcd|=0x08) // включаем светодиод
#define setwrite()   	WriteByteI2CLCD(portlcd&=~0x02)  //установка записи RW


//----Прописываем функции с которыми будем работать----//
void WriteByteI2CLCD(uint8_t bt);  //запись байта
__STATIC_INLINE void DelayMicro(uint32_t __IO micros); // задержка в микросекундах
void sendhalfbyte(uint8_t c); //передача пол байта
void sendbyte(uint8_t c, uint8_t mode);//отправка байта
void LCD_Clear(void);// очистка экрана
void LCD_SendChar(char ch);//отправка символа
void LCD_SetPos(uint8_t x, uint8_t y);// установка позиции
void LCD_init(void);// инициализация экрана
void LCD_String(char* st);// отправка текста

#endif /* INC_LCD1602_I2C_LIB_H_ */
