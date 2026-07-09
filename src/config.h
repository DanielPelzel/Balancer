#ifndef CONFIG_H
#define CONFIG_H


//Pin Belegungen
//In
#define In4 25
#define In3 26
#define In2 33
#define  In1 32

#define SLEEP_PIN 12 

//MPU 6050
#define SCL_PIN 22
#define SDA_PIN 23

#define PWM_FREQ 1000
#define PWM_RES  8
#define PWM_CH_A1 0
#define PWM_CH_A2 1
#define PWM_CH_B1 2
#define PWM_CH_B2 3

//MPU Range
#define MPU_accel_Range MPU6050_RANGE_4_G
#define MPU_gyro_Range MPU6050_RANGE_500_DEG
#define MPU_filter_bandwidth MPU6050_BAND_44_HZ

constexpr float KP = 5.0f;
constexpr float KI = 0.0f;
constexpr float KD = 0.0f;
constexpr float ANGLE_OFFSET = 0.0f;

#define drehachse az //auswhählen zwischen ax ay und az

#define TOTPUNKT 40


#endif
