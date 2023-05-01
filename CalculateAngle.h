#ifndef __CALCULATEANGELE_H__
#define __CALCULATEANGELE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "MPU6050.h"

#define RADIAN_TO_DEGREE 180/3.141592f

typedef struct _Angle{
	float acc_roll;
	float acc_pitch;
	float acc_yaw;

	float gyro_roll;
	float gyro_pitch;
	float gyro_yaw;

	float ComFilt_roll;
	float ComFilt_pitch;
	float ComFilt_yaw;
}Struct_Angle;


extern Struct_Angle Angle;

void CalculateAccAngle(Struct_Angle* Angle, Struct_MPU6050* MPU6050);
void CalculateGyroAngle(Struct_Angle* Angle, Struct_MPU6050* MPU6050);
void CalculateCompliFilter(Struct_Angle* Angle, Struct_MPU6050* MPU6050);

#ifdef __cplusplus
}
#endif
#endif
