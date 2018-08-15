#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"



//内部温度传感器实验 -库函数版本 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com	
    
		
int main(void)
{ 
	short temp; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);     //初始化延时函数
	uart_init(115200);	 //初始化串口波特率为115200

	LED_Init();					//初始化LED 
 	LCD_Init();         //液晶初始化
	Adc_Init();         //内部温度传感器ADC初始化
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Mcudev STM32F4");	
	LCD_ShowString(30,70,200,16,16,"ADC TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao.com");
	LCD_ShowString(30,110,200,16,16,"2015/8/6");	  
	POINT_COLOR=BLUE;//设置字体为蓝色      
	LCD_ShowString(30,140,200,16,16,"TEMPERATE: 00.00C");//先在固定位置显示小数点	      
	while(1)
	{
		temp=Get_Temprate();	//得到温度值 
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowString(30+10*8,140,16,16,16,"-");	    //显示负号
		}else LCD_ShowString(30+10*8,140,16,16,16," ");	//无符号
		
		LCD_ShowxNum(30+11*8,140,temp/100,2,16,0);		//显示整数部分
		LCD_ShowxNum(30+14*8,140,temp%100,2,16,0);		//显示小数部分 
		 
		LED0=!LED0;
		delay_ms(250);	
	}
}
