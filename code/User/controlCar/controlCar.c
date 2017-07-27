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

/**************速度大小*******************/
#define MAX_SPEED 1000
#define MID_SPEED 500
#define MIN_SPEED 100
#define STOP_SPEED 0

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
u16 ControlLeftSpeed = 0;		//左轮速度控制
u16 ControlRightSpeed = 0;	//右轮速度控制

/***TIM1 GPIOA GPIOB引脚初始化********/
static void Control_Car_GPIO_Config(void);
static void TIM3_GPIO_Config(void);
static void TIM3_Mode_Config(void);

/**************方向控制*************/
//前左转
static void Turn_Left_Forward(void);

//前右转
static void Turn_Right_Forward(void);

//前进
static void Forward(void);

//后左转
static void Turn_Left_Backward(void);

//后右转
static void Turn_Right_Backward(void);

//后退
static void Backward(void);

/***********速度控制*********/
//快速
static void Speed_Fast(void);

//中速
static void Speed_Mid(void);

//低速
static void Speed_Low(void);

//停止
static void Speed_Stop(void);

//修改定时器计数值
static void Change_Speed(void);
/**************************************************************
*	Global Variable Declare Section
**************************************************************/


/**************************************************************
*	File Static Variable Define Section
**************************************************************/


/**************************************************************
*	Function Define Section
**************************************************************/

void Car_Control_Init(void)
{
	Control_Car_GPIO_Config();
	TIM3_GPIO_Config();
	TIM3_Mode_Config();
	
}

/**
 *  @name	     Control_Car_GPIO_Config
 *	@description   init PA4\PA5\PA6\PA7
 *	@param			none
 *	@return		  none
 *  @notice
 */
static void Control_Car_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启L298N的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);

	/*选择要控制的GPIOA引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*设置引脚速率为50MHz*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	/*调用库函数，初始化GPIOA*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*控制引脚初始化为1*/
	GPIO_SetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}

/**
 *  @name	     TIM1_GPIO_Config
 *	@description   init PB0\PB1
 *	@param			none
 *	@return		  none
 *  @notice
 */
static void TIM3_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

  /*设置TIM1CLK为72MHZ*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	/*开启GPIOB的时钟使能*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);

	/*部分映射，将TIM3_CHN3映射到PB0,TIM3_CHN4映射到PB1*/
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
  /*选择要控制的GPIOB引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	
	/*设置引脚模式为复用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
	/*设置引脚速率为50MHz*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	/*调用库函数，初始化GPIOB*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*使能引脚初始化为1*/
	//GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1);
}


/**
 *  @name	     TIM3_Mode_Config
 *	@description   
 *	@param			none
 *	@return		  none
 *  @notice
 */
static void TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/*PWM信号电平跳变值*/
 	u16 CCR1_Val = ControlLeftSpeed;        
 	u16 CCR2_Val = ControlRightSpeed;

	
/* ----------------------------------------------------------------------- 
    TIM3 Channel3 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% 
    TIM3 Channel4 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100%
  ----------------------------------------------------------------------- */
	

	/*Time base configuration*/
	TIM_TimeBaseStructure.TIM_Period = 999;						//1000次为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//设置预分频：不预分频，即为72MHZ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//设置始终分频系数，不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	/*PWM1 Mode configuration:Channel3*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;		//配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;			
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //小于CCR1_Val时为高电平
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/*PWM1 Mode configuration:Channel4*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;			
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	   //设置跳变值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //小于CCR2_Val时为高电平
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	 //使能通道4
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);	
	TIM_ARRPreloadConfig(TIM3, ENABLE);			//使能TIM3重载寄存器ARR
	
	/*TIM3 enable counter*/
	TIM_Cmd(TIM3,ENABLE);
}
	
/**
 *  @name	     Control_Car_Direction
 *	@description   
 *	@param			type of direction parameter is Direction_Type, its values are below
 *              TURN_LEFT_FORWARD
 *              TURN_RIGHT_FORWARD
 *              TURN_LEFT_BACKWARD
 *              TURN_RIGHT_BACKWORD
 *              FORWORD
 *              BACKWORD
 *	@return		  none
 *  @notice
 */
void Control_Car_Direction(Direction_Type direction)
{
	if(direction == TURN_LEFT_FORWARD){
		Turn_Left_Forward();
	}else if(direction == TURN_RIGHT_FORWARD){
		Turn_Right_Forward();
	}else if(direction == TURN_LEFT_BACKWARD){
		Turn_Left_Backward();
	}else if(direction == TURN_RIGHT_BACKWORD){
		Turn_Right_Backward();
	}else if(direction == FORWORD){
		Forward();
	}else if(direction == BACKWORD){
		Backward();}
}


/**
 *  @name	     Control_Car_Speed
 *	@description   
 *	@param			type of speed parameter is Speed_Type, its values are below
 *              SPEED_FAST
 *              SPEED_MID
 *              SPEED_LOW
 *              SPEED_STOP
 *	@return		  none
 *  @notice
 */
//控制速度
void Control_Car_Speed(Speed_Type speed)
{
		if(speed == SPEED_FAST){
			Speed_Fast();
		}else if(speed == SPEED_MID){
			Speed_Mid();
		}else if(speed == SPEED_LOW){
			Speed_Low();
		}else if(speed == SPEED_STOP){
			Speed_Stop();}
		
}




//前左转
static void Turn_Left_Forward(void)
{
	SET_IN1_0
	SET_IN2_1
	SET_IN3_1
	SET_IN4_0
}

//前右转
static void Turn_Right_Forward(void)
{
	SET_IN1_1
	SET_IN2_0
	SET_IN3_0
	SET_IN4_1	
}

//前进
static void Forward(void)
{
	SET_IN1_1
	SET_IN2_0
	SET_IN3_1
	SET_IN4_0
}

//后左转
static void Turn_Left_Backward(void)
{

	SET_IN1_1
	SET_IN2_1
	SET_IN3_0
	SET_IN4_1
}

//后右转
static void Turn_Right_Backward(void)
{
	SET_IN1_0
	SET_IN2_1
	SET_IN3_1
	SET_IN4_1
}

//后退
static void Backward(void)
{
	SET_IN1_0
	SET_IN2_1
	SET_IN3_0
	SET_IN4_1
}

static void Change_Speed(void)
{
	TIM_Cmd(TIM3,DISABLE);
	TIM3_Mode_Config();
	
}
static void Speed_Fast(void)
{
	ControlLeftSpeed = ControlRightSpeed = MAX_SPEED;
	Change_Speed();	
}

static void Speed_Mid(void)
{
	ControlLeftSpeed = ControlRightSpeed = MID_SPEED;	
	Change_Speed();
}

static void Speed_Low(void)
{
	ControlLeftSpeed = ControlRightSpeed = MIN_SPEED;	
	Change_Speed();
}

static void Speed_Stop(void)
{
	ControlLeftSpeed = ControlRightSpeed = STOP_SPEED;
	Change_Speed();
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
