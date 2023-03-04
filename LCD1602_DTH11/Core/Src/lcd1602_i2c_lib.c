// подключаем наши define
#include "lcd1602_i2c_lib.h"

//-----прописываем переменные-----//
#define Adress 0x27 << 1                //Адрес устройства.
extern I2C_HandleTypeDef   hi2c1; // получаем доступ к переменным библиотеки I2C
uint8_t buf[1]={0}; // переменная для передачи данных
char strl[20]; // переменная для нашего текста
uint8_t portlcd = 0;


//--------------------------запись байта--------------------------//
void WriteByteI2CLCD(uint8_t bt)
{
  buf[0]=bt;
  HAL_I2C_Master_Transmit(&hi2c1,(uint16_t) Adress, buf,1,1000);
/*
&hi2c2 – индефикатор шины
(uint16_t) 0x4E – адрес устройства, в данном случае – запись
Buf – наши данные
1 – количество байт, которые передаем
1000 – время, за которое должно выполнится передача данных, если не выполниться –выйдем из цикла с выдачей ошибки, которую можно будет обработать.
*/
}


//--------------------------стандартная функция задержки--------------------------//
__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{// 72000000/1000000=72    72/72=1 микросекунда
  micros *= (SystemCoreClock / 1000000) / 72;
  while (micros--);
}
// так как у нас экран настроен на 4 битный режим, передаем байт по частям
void sendhalfbyte(uint8_t  c)
{
   c<<=4;
   e_set();
   DelayMicro(200);
   WriteByteI2CLCD(portlcd|c);
   e_reset();
   DelayMicro(200);
}
void sendbyte(uint8_t  c, uint8_t  mode)
{
uint8_t hc=0;
if (mode==0) rs_reset(); else rs_set();//установка на передачу команды или на передачу слова
hc=c>>4;
sendhalfbyte(hc); sendhalfbyte(c);
}


//--------------------------очистка экрана--------------------------//
void LCD_Clear(void)
{
sendbyte(0x01, 0);
DelayMicro(6000);
}

//------------------------отправка  символа------------------------//
void LCD_SendChar(char ch)
{
sendbyte(ch,1);
}


//---установка символа в нужную позицию, начальные адреса взяты с документации---///
void LCD_SetPos(uint8_t x, uint8_t y)
{
switch(y)
    {
     case 0: sendbyte(x|0x80,0);//первая строка
        HAL_Delay(1);break;
     case 1:sendbyte((0x40+x)|0x80,0);//вторая строка
            HAL_Delay(1);break;
     case 2:sendbyte((0x10+x)|0x80,0);//третья строка
            HAL_Delay(1);break;
     case 3:sendbyte((0x50+x)|0x80,0);//четвертая строка
            HAL_Delay(1);break;
     }
}


//------инициализация дисплея согласно документации на выбранный дисплей------//
void LCD_init(void)
{
  HAL_Delay(15);
  sendhalfbyte(0x03);
  HAL_Delay(4);
  sendhalfbyte(0x03);
  DelayMicro(100);
  sendhalfbyte(0x03);
  HAL_Delay(1);
  sendhalfbyte(0x02);
  HAL_Delay(1);
  sendbyte(0x28, 0);
  HAL_Delay(1);
 sendbyte(0x01, 0);
  HAL_Delay(1);
 sendbyte(0x06, 0);
  HAL_Delay(2);
  sendbyte(0x02, 0);
  HAL_Delay(1);
 sendbyte(0x0C, 0);
  setled();
  setwrite();
}


//--------------------------отправка строки--------------------------//
void LCD_String(char* st)
{
  uint8_t  i=0;
  while(st[i]!=0) {sendbyte(st[i],1);i++;}
}

