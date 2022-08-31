#include <DynamixelSerial.h>

#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>

#include <Wire.h>

float angles[3]; // yaw pitch roll

// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();


//inisialisasi awal
float panjang_paha = 10.97;
float panjang_betis = 13.41;
float tinggi_kaki = 15.0;

void setup(){
  Serial.begin(9600);
  Wire.begin();

  delay(5);
  sixDOF.init(); //begin the IMU
  delay(5);
Dynamixel.setSerial(&Serial); // &Serial - Arduino UNO/NANO/MICRO, &Serial1, &Serial2, &Serial3 - Arduino Mega
Dynamixel.begin(1000000,2);  // Inicialize the servo at 1 Mbps and Pin Control 2
delay(1000);
}

void loop(){
  sixDOF.getEuler(angles);
float sudut = angles[1];
Serial.println(sudut);
  float tinggi_kaki_depan = tinggi_kaki + (sin(sudut*3.14159/180) * 11.5);
  float tinggi_kaki_belakang = tinggi_kaki - (sin(sudut*3.14159/180) * 11.5);
  
  float c_kanan_depan = (200-((acos((pow(panjang_paha,2)+pow(tinggi_kaki_depan,2)-pow(panjang_betis,2))/(2*panjang_paha*tinggi_kaki_depan))) * 180 / 3.14159)) / 360 *1024;
  float c_kiri_depan = (160+((acos((pow(panjang_paha,2)+pow(tinggi_kaki_depan,2)-pow(panjang_betis,2))/(2*panjang_paha*tinggi_kaki_depan))) * 180 / 3.14159)) / 360 *1024;
  float c_kanan_belakang = (200-((acos((pow(panjang_paha,2)+pow(tinggi_kaki_belakang,2)-pow(panjang_betis,2))/(2*panjang_paha*tinggi_kaki_belakang))) * 180 / 3.14159)) / 360 *1024;
  float c_kiri_belakang = (160+((acos((pow(panjang_paha,2)+pow(tinggi_kaki_belakang,2)-pow(panjang_betis,2))/(2*panjang_paha*tinggi_kaki_belakang))) * 180 / 3.14159)) / 360 *1024;
  
  float b_kanan_depan = (360 - ((acos((pow(panjang_paha,2)+pow(panjang_betis,2)-pow(tinggi_kaki_depan,2))/(2*panjang_paha*panjang_betis))) * 180 / 3.14159)) / 360 *1024;
  float b_kiri_depan = (0 + ((acos((pow(panjang_paha,2)+pow(panjang_betis,2)-pow(tinggi_kaki_depan,2))/(2*panjang_paha*panjang_betis))) * 180 / 3.14159)) / 360 *1024;
  float b_kanan_belakang = (360 - ((acos((pow(panjang_paha,2)+pow(panjang_betis,2)-pow(tinggi_kaki_belakang,2))/(2*panjang_paha*panjang_betis))) * 180 / 3.14159)) / 360 *1024;
  float b_kiri_belakang = (0 + ((acos((pow(panjang_paha,2)+pow(panjang_betis,2)-pow(tinggi_kaki_belakang,2))/(2*panjang_paha*panjang_betis))) * 180 / 3.14159)) / 360 *1024;
  
  int id_1 = b_kanan_depan;
  int id_2 = b_kiri_depan;
  int id_3 = c_kanan_depan;
  int id_4 = c_kiri_depan;
  int id_5 = 200;
  int id_6 = 824;
  int id_7 = b_kanan_belakang;
  int id_8 = b_kiri_belakang;
  int id_9 = c_kanan_belakang;
  int id_10 = c_kiri_belakang;
  int id_11 = 200;
  int id_12 = 824;
  //Kaki kanan depan
    Dynamixel.move(1,id_1);
    Dynamixel.move(3,id_3);
    Dynamixel.move(5,(id_5));


  //Kaki kiri depan   
    Dynamixel.move(2,id_2);
    Dynamixel.move(4,id_4);
    Dynamixel.move(6,(id_6));

    
  //Kaki kanan belakang
    Dynamixel.move(7,id_7);
    Dynamixel.move(9,id_9);
    Dynamixel.move(11,(id_11));


  //Kaki kiri belakang    
    Dynamixel.move(8,id_8);
    Dynamixel.move(10,id_10);
    Dynamixel.move(12,(id_12));  


  

}
