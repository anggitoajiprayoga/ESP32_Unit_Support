#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "WiFi.h"
#include "HTTPClient.h"
#include <ArduinoJson.h>
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <RtcDS3231.h>
#include <TimeLib.h>
#include <Wire.h>

#define Serial_atmel Serial2
#define SD_CS 5
#define p_pto 35
#define p_running 34
#define p_fuel 39
#define p_netral 36

String version = "Firm v3.2 - Unit Support Board V2";
String board = "V2";
String type_board = "Unit Support - V2";

String sn_default = "SS6 - COE";
String cn_default = "Unit Support";

String http_username;
String http_password;

const char* ssid = "SS6";     // Nama SSID AP/Hotspot
const char* password = "";    // Password Wifi

const String default_ssid = "";
const String default_wifipassword = "SS6";
const String default_httpuser = "admin";
const String default_httppassword = "admin";
const int default_webserverporthttp = 80;

struct Config {
  String ssid;
  String wifipassword;
  String httpuser;
  String httppassword;
  int webserverporthttp;
};

bool shouldReboot = false;
String listFiles(bool ishtml = false);

String sn;
String ssid_wifi_client;
String pass_wifi_client;
String ssid_wifi_ap;
String pass_wifi_ap;

String ip_local_client;
String rssi_wifi;
String ip_type;

String cn_unit;
String serial_number;;

boolean state_reset_default = false;
boolean state_restart = false;
bool parking, alt;

String url;
String method;
String status_wifi;
int httpResponseCode;

byte countbackup = 0;
byte rst;
long proveusbackup;

String longitude_str, latitude_str;
String freesp, usedstr, totalstr;
String paketData;
String latitude, longitude, speed, altitude, heading, en_rst;

String Data, dataLog, cn, latd , longi, sped, wtanggal, hmTime, idleTime, standbyTime;
int cnt = 30; //Second restart
unsigned long previousMillisCnt = 1000;

unsigned long intervalW = 5000; //In Second
unsigned long previousMillisW = 0;
unsigned long previousMillisLogging = 5000;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long proveussend;
unsigned long prev_check;
long prev, prevv;

int Year;
byte Month;
byte Day;
byte Hour;
byte Minute;
byte Second;

float Vin = 0.0;
float Vout = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
float fuel_voltage;
int value = 0;
int running, pto, netral;
int value_running, value_pto, value_netral;
int idleSecond, hmSecond, standbySecond, idleMinute, hmMinute, standbyMinute, idleHour, hmHour, standbyHour;
String SN;
byte shift, xshift, count_second;
unsigned long previousMillisDebug;
String direction, dir, status;
String altid_hmOff, dir_hmOff, altid_idleOff, dir_idleOff, altid_standbyOff, dir_standbyOff;
String speed_hmOff, fuel_voltagehmOff, speed_idleOff, fuel_voltageidleOff, speed_standbyOff, fuel_voltagestandbyOff;

String times, dates;
char tanggalx[15];
char waktux[15];

bool hm, idle, standby;
byte counthm = 0, countidle = 0, countstandby = 0;
long proveushm, proveusidle, proveusstandby, prev_http;

String total_jamhm;
String total_jamidle;
String total_jamstandby;

String final_hm;
String final_idle;
String final_standby;
String final_payload;

int selisih_jamhm;
int selisih_mnthm;
int selisih_dtkhm;
int selisih_jamidle;
int selisih_mntidle;
int selisih_dtkidle;
int selisih_jamstandby;
int selisih_mntstandby;
int selisih_dtkstandby;

char selisih_hm[15];
char selisih_idle[15];
char selisih_standby[15];

String jam_backupOff;
String mnt_backupOff;
String dtk_backupOff;

String hari_backupOff;
String bulan_backupOff;
String tahun_backupOff;

String jam_idleOn;
String jam_idleOff;
String mnt_idleOn;
String mnt_idleOff;
String dtk_idleOn;
String dtk_idleOff;

String jam_hmOn;
String jam_hmOff;
String mnt_hmOn;
String mnt_hmOff;
String dtk_hmOn;
String dtk_hmOff;

String jam_standbyOn;
String jam_standbyOff;
String mnt_standbyOn;
String mnt_standbyOff;
String dtk_standbyOn;
String dtk_standbyOff;

String tahun_hmOn, bulan_hmOn, hari_hmOn;
String tahun_hmOff, bulan_hmOff, hari_hmOff;
String tahun_idleOn, bulan_idleOn, hari_idleOn;
String tahun_idleOff, bulan_idleOff, hari_idleOff;
String tahun_standbyOn, bulan_standbyOn, hari_standbyOn;
String tahun_standbyOff, bulan_standbyOff, hari_standbyOff;

String value_day, value_month, value_year;
String value_hour, value_minute, value_second;
String tahun, bulan, tanggal, jam, menit, detik, waktu;

String timer_hmOn, timer_idleOn, timer_standbyOn;
String tanggal_hmOn, tanggal_idleOn, tanggal_standbyOn;
String timer_hmOff, timer_idleOff, timer_standbyOff;
String tanggal_hmOff, tanggal_idleOff, tanggal_standbyOff;
String lat_hmOff, lat_idleOff, lat_standbyOff;
String long_hmOff, long_idleOff, long_standbyOff;
String durationr, kondisi;
String date_backup, time_backup;

unsigned int countHm;
unsigned int countStandby;
unsigned int countIdle;

bool en_send = true;
bool en_writehm;
bool en_writeidle;
bool en_writestandby;

String timerOn_http;
String timerOff_http;
String selisih_http;
String status_http;

Config config;
WiFiClient espClient;
HTTPClient http;
AsyncWebServer server(80);
RtcDS3231<TwoWire> Rtc(Wire);
time_t prevDisplay = 0;

void setup()
{
  Serial.begin(115200);
  Serial_atmel.begin(57600);
  setup_SD();
  SPIFFS.begin();
  read_setting();
  setup_webserver();
  setup_wifi();
  setup_RTC();
  setup_svoltage();
}

void loop() {
  loop_svoltage();
  loop_RTC();
  loop_wifi(); 
  mainn();
  parsing();
  serial_monitor();
}
