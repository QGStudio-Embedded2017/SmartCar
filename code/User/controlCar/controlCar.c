/***************************************************************************************
 *	FileName					: controlCar.c
 *	CopyRight					: JockJo
 *	ModuleName				: controlCar	
 *
 *	CPU							:	STM32F103RC/LQFP64
 *	RTOS						:
 *
 *	Create Data					: 2017-7-26	
 *	Author/Corportation			:	JockJo
 *
 *	Abstract Description		:	control car
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	1		1.0     2017-7-26    JockJo
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

/*********L298N引脚高低电平控制**********/
#define SET_IN1_1	\
	GPIO_SetBits(GPIOA, GPIO_Pin_4);

#define SET_IN1_0 \
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);

#define SET_IN2_1	\
	GPIO_SetBits(GPIOA, GPIO_Pin_5);

#define SET_IN2_0 \
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);

#define SET_IN3_1	\
	GPIO_SetBits(GPIOA, GPIO_Pin_6);

#define SET_IN3_0 \
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);

#define SET_IN4_1	\
	GPIO_SetBits(GPIOA, GPIO_Pin_7);

#define SET_IN4_0 \
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	
#define SET_EN1_1 \
	GPIO_SetBits(GPIOB, GPIO_Pin_0);

#define SET_EN1_0	\
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);

#define SET_EN2_1 \
	GPIO_SetBits(GPIOB, GPIO_Pin_1);

#define SET_EN2_0	\
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);

/**************************************************************
*	Struct Define Section
**************************************************************/


/**************************************************************
*	Prototype Declare Section
**************************************************************/
//左转
static void Turn_Left(void);

//右转
static void Turn_Right(void);

//前进
static void Forward(void);

//后退
static void Backward(void);

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
 *  @name	     Control_Car_GPIO_Config
 *	@description   init PA4\PA5\PA6\PA7\PB0\PB1
 *	@param			none
 *	@return		  none
 *  @notice
 */
void Control_Car_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启L298N的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);

	/*选择要控制的GPIOA引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*设置引脚速率为50MHz*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	/*调用库函数，初始化GPIOA*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*选择要控制的GPIOB引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	
	/*调用库函数，初始化GPIOB*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*使能引脚初始化为1*/
	GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1);
	
	/*控制引脚初始化为1*/
	GPIO_SetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}


/**
 *  @name	     Control_Car_Direction
 *	@description   
 *	@param			none
 *	@return		  none
 *  @notice
 */
void Control_Car_Direction(Direction_Type direction)
{
	if(direction == TURN_LEFT_FORWARD){
		Turn_Left();
	}else if(direction == TURN_RIGHT_FORWARD){
		Turn_Right();
	}else if(direction == TURN_LEFT_BACKWARD){
		
	}else if(direction == TURN_RIGHT_BACKWORD){
	
	}else if(direction == FORWORD){
		Forward();
	}else if(direction == BACKWORD){
		Backward();
	}
}


/**
 *  @name	     Control_Car_Speed
 *	@description   
 *	@param			none
 *	@return		  none
 *  @notice
 */
//控制速度
void Control_Car_Speed(Speed_Type speed)
{
	
}


//左转
static void Turn_Left(void)
{
	SET_IN1_1
	SET_IN2_0
	SET_IN3_0
	SET_IN4_1
}

//右转
static void Turn_Right(void)
{
	SET_IN1_0
	SET_IN2_1
	SET_IN3_1
	SET_IN4_0	
}

//前进
static void Forward(void)
{
	SET_IN1_1
	SET_IN2_0
	SET_IN3_1
	SET_IN4_0
}

//后退
static void Backward(void)
{
	SET_IN1_0
	SET_IN2_1
	SET_IN3_0
	SET_IN4_1
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
