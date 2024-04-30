#ifndef _GC9A01_H_
#define _GC9A01_H_

//-----------------LCD¶Ë¿Ú¶¨Òå----------------
#define LCD_RES_Clr()  GPIOB->BSRR = 1U << (0+ 16)
#define LCD_RES_Set()  GPIOB->BSRR = 1U << 0

#define LCD_DC_Clr()   GPIOC->BSRR = 1U << (4+ 16)
#define LCD_DC_Set()   GPIOC->BSRR = 1U << 4


#define LCD_CS_Clr()   GPIOC->BSRR = 1U << (5+ 16)
#define LCD_CS_Set()   GPIOC->BSRR = 1U << 5


#define LCD_SCLK_Clr()   GPIOA->BSRR = 1U << (0+ 16)
#define LCD_SCLK_Set()   GPIOA->BSRR = 1U << 0

#define LCD_MOSI_Clr()   GPIOA->BSRR = 1U << (0+ 16)
#define LCD_MOSI_Set()   GPIOA->BSRR = 1U << (0)
void LCD_Init(void);


#endif
