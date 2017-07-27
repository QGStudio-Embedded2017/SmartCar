/***************************************************************************************
 *	File Name				: controlCar.h
 *	CopyRight				: JockJo
 *	ModuleName				:	controlCar
 *
 *	CPU						: STM32F103RC/LQFP64
 *	RTOS					:
 *
 *	Create Data				:	2017-7-26
 *	Author/Corportation		: JockJo
 *
 *	Abstract Description	:	
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *	1    1.0      2017-7-26    JockJo   
 *
 ***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef __CONTROL_H
#define __CONTROL_H


/**************************************************************
*	Debug switch Section
**************************************************************/


/**************************************************************
*	Include File Section
**************************************************************/
#include "stm32f10x.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
#ifndef uchar
#define uchar unsigned char
#endif //uchar

#ifndef uint
#define uint unsigned int
#endif //uint

/**************************************************************
*	Struct Define Section
**************************************************************/
#ifndef DTYPE
#define DTYPE
typedef enum{
	TURN_LEFT_FORWARD,			//向前左转
	TURN_RIGHT_FORWARD,     //向前右转
	TURN_LEFT_BACKWARD,			//向后左转
	TURN_RIGHT_BACKWORD,    //向后右转
	FORWORD,								//向前直走
	BACKWORD                //向后直走
} Direction_Type;
#endif		//DTYPE


#ifndef STYPE
#define STYPE	
typedef enum{
	SPEED_FAST,		//高速
	SPEED_MID,		//中速
	SPEED_LOW,    //低速
	SPEED_STOP		//停止
} Speed_Type;
#endif		//STYPE

/**************************************************************
*	Prototype Declare Section
**************************************************************/
//引脚初始化
void Car_Control_Init(void);

//控制方向
void Control_Car_Direction(Direction_Type direction);

//控制速度
void Control_Car_Speed(Speed_Type speed);

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************Tpro************************/
#endif  //_CONTROL_H
