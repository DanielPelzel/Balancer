#ifndef CONFIG_H
#define CONFIG_H


//Pin Belegungen
//In
#define In4 26
#define In3 25
#define In2 33
#define  In1 32

//PWM
#define ENB 14
#define ENA 13

//Encoder rechts
#define Enc_A_R 36
#define Enc_B_R 39

//Encoder links
#define Enc_A_L 35
#define Enc_B_L 34

//MPU 6050
#define SCL_PIN 22
#define SDA_PIN 21

#define PWM_FREQ 1000
#define PWM_RES  8
#define PWM_CH_A 0
#define PWM_CH_B 1

//MPU Range
#define MPU_accel_Range MPU6050_RANGE_4_G
#define MPU_gyro_Range MPU6050_RANGE_500_DEG
#define MPU_filter_bandwidth MPU6050_BAND_44_HZ

constexpr float KP = 10.0f;
constexpr float KI = 0.2;
constexpr float KD = 2.0f;
constexpr float ANGLE_OFFSET = 0.0f;

#define drehachse ax //auswhählen zwischen ax ay und az


#endif
