/***************************************************************************************
 *	FileName					:	mian.c
 *	CopyRight					:	JockJo
 *	ModuleName					:	smartCar
 *
 *	CPU							:	STM32F103RC/LQFP64
 *	RTOS						:
 *
 *	Create Data					: 2017-7-26
 *	Author/Corportation			: JockJo
 *
 *	Abstract Description		:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	1    1.0      2017-7-26    JockJo       
 *
 ***************************************************************************************/


/**************************************************************
*	Debug switch Section
**************************************************************/


/**************************************************************
*	Include File Section
**************************************************************/
#include "controlCar.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
//debug调试宏定义，根据表达式a的真假执行has_bug或no_bug 
#define BUG_DETECT_PRINT(a,has_bug,no_bug) { if(a) \
printf("%s",has_bug); \
else \
printf("%s",no_bug);}


/**************************************************************
*	Struct Define Section
**************************************************************/


/**************************************************************
*	Prototype Declare Section
**************************************************************/
extern uchar ControlLeftSpeed;		//左轮速度控制
extern uchar ControlRightSpeed;		//右轮速度控制

/**************************************************************
*	Global Variable Declare Section
**************************************************************/


/**************************************************************
*	File Static Variable Define Section
**************************************************************/


/**************************************************************
*	Function Define Section
**************************************************************/

/**
 *  @name
 *	@description
 *	@param			
 *	@return		
 *  @notice
 */
 int main()
 {
		u32 status1,status2;              //0表示有障碍物，1表示无障碍物
		Car_Control_Init();
		Control_Car_Direction(BACKWORD);
		Control_Car_Speed(SPEED_MID);
		while(1)
		{
				status1 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11);    //将正前方有无障碍物赋值于status1
				status2 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12);    //将左侧有无障碍物赋值于status2
				Control_Car_Direction(FORWORD);
				if(status1 == 0 && status2 == 0)                      //正前方且左侧均有障碍物
				{
					Control_Car_Direction(TURN_RIGHT_BACKWORD);					//改变方向，向右行驶
				}
				else if(status1 == 0 && status2 == 1)                 //正前方有障碍物，左侧无障碍物
				{
					Control_Car_Direction(TURN_LEFT_BACKWARD);          //改变方向，向左行驶
				}
		}
 }
 

 
 #ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{
          /* User can add his own implementation to report the file name and line number,
             ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
        
          while (1)
          {}
}
#endif
