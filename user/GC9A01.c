#include "GC9A01.h"
#include "main.h"
#include "spi.h"
#include "lvgl.h"


#define u8 uint8_t
#define u16 uint16_t

#define USE_HORIZONTAL 0
#define delay_ms HAL_Delay
u8 data[20000];
u16 frameBuffer[57600];

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
	u8 i;
	LCD_CS_Clr();
//	for(i=0;i<8;i++)
//	{			  
//		LCD_SCLK_Clr();
//		if(dat&0x80)
//		{
//		   LCD_MOSI_Set();
//		}
//		else
//		{
//		   LCD_MOSI_Clr();
//		}
//        for(int i=0;i<2;i++)
//            __NOP;
//		LCD_SCLK_Set();
//		dat<<=1;
//        for(int i=0;i<2;i++)
//            __NOP();
//	}	
    HAL_SPI_Transmit_DMA(&hspi1,&dat,1);
    
    while(hspi1.State != HAL_SPI_STATE_READY);
  LCD_CS_Set();	
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
    
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
   
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();//写命令
	LCD_Writ_Bus(dat);
    LCD_DC_Set();//写数据
	
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
}

void LCD_Init(void)
{

	
	LCD_RES_Clr();//复位
	delay_ms(100);
	LCD_RES_Set();
	delay_ms(100);
	

  delay_ms(100);
	
	LCD_WR_REG(0xEF);
	LCD_WR_REG(0xEB);
	LCD_WR_DATA8(0x14); 
	
  LCD_WR_REG(0xFE);			 
	LCD_WR_REG(0xEF); 

	LCD_WR_REG(0xEB);	
	LCD_WR_DATA8(0x14); 

	LCD_WR_REG(0x84);			
	LCD_WR_DATA8(0x40); 

	LCD_WR_REG(0x85);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_REG(0x86);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_REG(0x87);			
	LCD_WR_DATA8(0xFF);

	LCD_WR_REG(0x88);			
	LCD_WR_DATA8(0x0A);

	LCD_WR_REG(0x89);			
	LCD_WR_DATA8(0x21); 

	LCD_WR_REG(0x8A);			
	LCD_WR_DATA8(0x00); 

	LCD_WR_REG(0x8B);			
	LCD_WR_DATA8(0x80); 

	LCD_WR_REG(0x8C);			
	LCD_WR_DATA8(0x01); 

	LCD_WR_REG(0x8D);			
	LCD_WR_DATA8(0x01); 

	LCD_WR_REG(0x8E);			
	LCD_WR_DATA8(0xFF); 

	LCD_WR_REG(0x8F);			
	LCD_WR_DATA8(0xFF); 


	LCD_WR_REG(0xB6);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x20);

	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x68);
	else LCD_WR_DATA8(0xA8);

	LCD_WR_REG(0x3A);			
	LCD_WR_DATA8(0x05); 


	LCD_WR_REG(0x90);			
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08); 

	LCD_WR_REG(0xBD);			
	LCD_WR_DATA8(0x06);
	
	LCD_WR_REG(0xBC);			
	LCD_WR_DATA8(0x00);	

	LCD_WR_REG(0xFF);			
	LCD_WR_DATA8(0x60);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x04);

	LCD_WR_REG(0xC3);			
	LCD_WR_DATA8(0x13);
	LCD_WR_REG(0xC4);			
	LCD_WR_DATA8(0x13);

	LCD_WR_REG(0xC9);			
	LCD_WR_DATA8(0x22);

	LCD_WR_REG(0xBE);			
	LCD_WR_DATA8(0x11); 

	LCD_WR_REG(0xE1);			
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x0E);

	LCD_WR_REG(0xDF);			
	LCD_WR_DATA8(0x21);
	LCD_WR_DATA8(0x0c);
	LCD_WR_DATA8(0x02);

	LCD_WR_REG(0xF0);   
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_REG(0xF1);    
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37);  
 	LCD_WR_DATA8(0x6F);


 	LCD_WR_REG(0xF2);   
 	LCD_WR_DATA8(0x45);
 	LCD_WR_DATA8(0x09);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x08);
 	LCD_WR_DATA8(0x26);
 	LCD_WR_DATA8(0x2A);

 	LCD_WR_REG(0xF3);   
 	LCD_WR_DATA8(0x43);
 	LCD_WR_DATA8(0x70);
 	LCD_WR_DATA8(0x72);
 	LCD_WR_DATA8(0x36);
 	LCD_WR_DATA8(0x37); 
 	LCD_WR_DATA8(0x6F);

	LCD_WR_REG(0xED);	
	LCD_WR_DATA8(0x1B); 
	LCD_WR_DATA8(0x0B); 

	LCD_WR_REG(0xAE);			
	LCD_WR_DATA8(0x77);
	
	LCD_WR_REG(0xCD);			
	LCD_WR_DATA8(0x63);		


	LCD_WR_REG(0x70);			
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x03);

	LCD_WR_REG(0xE8);			
	LCD_WR_DATA8(0x34);

	LCD_WR_REG(0x62);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xED);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xEF);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_REG(0x63);			
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x71);
	LCD_WR_DATA8(0xF3);
	LCD_WR_DATA8(0x70); 
	LCD_WR_DATA8(0x70);

	LCD_WR_REG(0x64);			
	LCD_WR_DATA8(0x28);
	LCD_WR_DATA8(0x29);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0xF1);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x07);

	LCD_WR_REG(0x66);			
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xCD);
	LCD_WR_DATA8(0x67);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);

	LCD_WR_REG(0x67);			
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x3C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x32);
	LCD_WR_DATA8(0x98);

	LCD_WR_REG(0x74);			
	LCD_WR_DATA8(0x10);	
	LCD_WR_DATA8(0x85);	
	LCD_WR_DATA8(0x80);
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x4E);
	LCD_WR_DATA8(0x00);					
	
  LCD_WR_REG(0x98);			
	LCD_WR_DATA8(0x3e);
	LCD_WR_DATA8(0x07);

	LCD_WR_REG(0x35);	
	LCD_WR_REG(0x21);

	LCD_WR_REG(0x11);
	delay_ms(120);
	LCD_WR_REG(0x29);
	delay_ms(20);
} 
static inline void DMA2D_Fill( void * pDst, uint32_t width, uint32_t height, uint32_t lineOff, uint32_t pixelFormat,   lv_color_t * color_p) {

    /* DMA2D配置 */  
    DMA2D->CR      = 0x00000000UL | (1 << 9) ;                                  // 配置为寄存器到储存器模式
    DMA2D->FGMAR    = (uint32_t)(&(color_p->full));                                         // 设置填充使用的颜色，格式应该与设置的颜色格式相同
    
    DMA2D->OMAR    = (uint32_t)pDst;                                // 填充区域的起始内存地址
    DMA2D->FGOR    = 0;

    
    DMA2D->OOR     = lineOff;                                       // 行偏移，即跳过的像素，注意是以像素为单位
    DMA2D->FGPFCCR= pixelFormat; 
    DMA2D->OPFCCR  = pixelFormat;                                   // 设置颜色格式
    DMA2D->NLR     = (uint32_t)(width << 16) | (uint16_t)height;    // 设置填充区域的宽和高，单位是像素

    /* 启动传输 */
    DMA2D->CR   |= DMA2D_CR_START;   

    /* 等待DMA2D传输完成 */
    
}
//void LCD_Fill(int16_t xsta,int16_t ysta,int16_t xend,int16_t yend,lv_color_t * color_p)
//{          
//	u16 i,j; 
//	LCD_Address_Set(xsta,ysta,xend,yend);//设置显示范围
//    uint32_t d=0;
//    uint32_t transdata_len=60000;
//    void* pDist = &(((uint16_t*)frameBuffer)[ysta*240 + xsta]);
//    DMA2D_Fill(pDist, xend-xsta+1, yend-ysta+1, 240-xend+xsta-1, DMA2D_OUTPUT_RGB565, color_p);
////	for(i=ysta;i<yend;i++)
////	{													   	 	
////		for(j=xsta;j<xend;j++)
////		{            
////			memcpy(data+d,&(color),2);
////            d+=2;
////            if(d>=10000){
////                LCD_CS_Clr();
////                HAL_SPI_Transmit_DMA(&hspi1,data,d);        
////                while(hspi1.State != HAL_SPI_STATE_READY);
////                LCD_CS_Set();
////                d=0;
////            }
////		}}

//    void* pdata = ((uint8_t*)(frameBuffer+(ysta)*240 + xsta));
//    unsigned int data_l=(xend-xsta+1)*(yend-ysta+1)*2;
//   memcpy(data,&(color_p->full),data_l);
//    
//        LCD_CS_Clr();
//       
//            HAL_SPI_Transmit_DMA(&hspi1,&(color_p->full), data_l);
//        while(hspi1.State != HAL_SPI_STATE_READY);
//        LCD_CS_Set();	

//    
//	 					  	    
//}
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,lv_color_t * color_p)
{          
	u16 i,j; 
    uint32_t d=0;
	LCD_Address_Set(xsta,ysta,xend,yend);//设置显示范围
    unsigned int data_l=(xend-xsta+1)*(yend-ysta+1)*2;
//	for(i=ysta;i<=yend;i++)
//	{													   	 	
//		for(j=xsta;j<=xend;j++)
//		{
//            memcpy(data+d,&(color_p->full),2);
//            color_p++;
//            d+=2;
//		}
//	} 
         LCD_CS_Clr();
        
            HAL_SPI_Transmit_DMA(&hspi1,(&(color_p->full)),data_l);
       
}

