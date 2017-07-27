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

		Car_Control_Init();
		Control_Car_Direction(BACKWORD);
		Control_Car_Speed(SPEED_MID);
		while(1)
		{
			
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
