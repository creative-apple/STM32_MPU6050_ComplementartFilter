#include "CalculateAngle.h"

Struct_Angle Angle;

void CalculateAccAngle(Struct_Angle* Angle, Struct_MPU6050* MPU6050)
{
	Angle->acc_roll  = atan(-MPU6050->acc_x / sqrt(pow(MPU6050->acc_y,2) + pow(MPU6050->acc_z,2))) * RADIAN_TO_DEGREE;
	Angle->acc_pitch = atan(MPU6050->acc_y / sqrt(pow(MPU6050->acc_x,2) + pow(MPU6050->acc_z,2))) * RADIAN_TO_DEGREE;
	//	Angle->acc_yaw = atan(sqrt(pow(MPU6050->acc_x, 2) + pow(MPU6050->acc_y, 2)) / MPU6050->acc_z) * RADIAN_TO_DEGREE;
	//Can't use Angle->acc_yaw there is no reliability. It's based on my personal experimental view.
}

static float dt = 1/200.f; //Sample rate is 200Hz
void CalculateGyroAngle(Struct_Angle* Angle, Struct_MPU6050* MPU6050)
{
	Angle->gyro_roll  += MPU6050->gyro_y * dt;
	Angle->gyro_pitch += MPU6050->gyro_x * dt;
	Angle->gyro_yaw   += MPU6050->gyro_z * dt;
}

void CalculateCompliFilter(Struct_Angle* Angle, Struct_MPU6050* MPU6050)
{
	CalculateAccAngle(Angle, MPU6050); //Prepare Acc Angle before using Complimentary Filter.

	static float alpha = 0.96f;
	Angle->ComFilt_roll  = alpha*(MPU6050->gyro_y * dt + Angle->ComFilt_roll) + (1-alpha) * Angle->acc_roll;
	Angle->ComFilt_pitch = alpha*(MPU6050->gyro_x * dt + Angle->ComFilt_pitch) + (1-alpha) * Angle->acc_pitch;
	Angle->ComFilt_yaw   = Angle->ComFilt_yaw + MPU6050->gyro_z * dt;
}
