void setup_SD() {
  Serial.println(F("Initialization SD Card"));
  SD.begin(SD_CS);
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("Tidak Ada Kartu SD");
  }
  Serial.println(F("Succes initialization SD Card"));
  check_dir();
}

void check_dir() {
  File file = SD.open("/shift_1_eng_operation.csv");
  if (!file) {
    Serial.println("File /shift_1_eng_operation.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/shift_1_eng_operation.csv", "cn, sn, date, time, shift, condition, time_on, time_off, duration, longitude, latitude, altitude, heading, speed, fuel_voltage\n");
  }
  else {
    Serial.println("File /shift_1_eng_operation.csv already exists");
  }
  file.close();

  File file1 = SD.open("/shift_1_eng_idle.csv");
  if (!file1) {
    Serial.println("File /shift_1_eng_idle.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/shift_1_eng_idle.csv", "cn, sn, date, time, shift, condition, time_on, time_off, duration, longitude, latitude, altitude, heading, speed, fuel_voltage\n");
  }
  else {
    Serial.println("File /shift_1_eng_idle.csv already exists");
  }
  file1.close();

  File file2 = SD.open("/shift_1_eng_off.csv");
  if (!file2) {
    Serial.println("File /shift_1_eng_off.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/shift_1_eng_off.csv", "cn, sn, date, time, shift, condition, time_on, time_off, duration, longitude, latitude, altitude, heading, speed, fuel_voltage\n");
  }
  else {
    Serial.println("File /shift_1_eng_off.csv already exists");
  }
  file2.close();

  File file3 = SD.open("/shift_2_eng_operation.csv");
  if (!file3) {
    Serial.println("File /shift_2_eng_operation.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/shift_2_eng_operation.csv", "cn, sn, date, time, shift, condition, time_on, time_off, duration, longitude, latitude, altitude, heading, speed, fuel_voltage\n");
  }
  else {
    Serial.println("File /shift_2_eng_operation.csv already exists");
  }
  file3.close();

  File file4 = SD.open("/shift_2_eng_idle.csv");
  if (!file4) {
    Serial.println("File /shift_2_eng_idle.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/shift_2_eng_idle.csv", "cn, sn, date, time, shift, condition, time_on, time_off, duration, longitude, latitude, altitude, heading, speed, fuel_voltage\n");
  }
  else {
    Serial.println("File /shift_2_eng_idle.csv already exists");
  }
  file4.close();

  File file5 = SD.open("/shift_2_eng_off.csv");
  if (!file5) {
    Serial.println("File /shift_2_eng_off.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/shift_2_eng_off.csv", "cn, sn, date, time, shift, condition, time_on, time_off, duration, longitude, latitude, altitude, heading, speed, fuel_voltage\n");
  }
  else {
    Serial.println("File /shift_2_eng_off.csv already exists");
  }
  file5.close();

  File file6 = SD.open("/log.csv");
  if (!file6) {
    Serial.println("File /log.csv doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/log.csv", "cn, sn, date, time, shift, condition, time_on, time_off, total_time, longitude, latitude, altitude, heading, speed, fuel_voltage\n");
  }
  else {
    Serial.println("File /log.csv already exists");
  }
  file6.close();

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void logging(String kondisi, String shift, String time_On, String time_Off, String total_waktu, bool en_log, String status) {
  while (kondisi == "engine_operation" and shift == "1" and en_log == true and status == "reset") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + ",reseting device\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_1_eng_operation.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_operation" and shift == "2" and en_log == true and status == "reset") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + ",reseting device\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_2_eng_operation.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_idle" and shift == "1" and en_log == true and status == "reset") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + ",reseting device\n";
    Serial.println("1dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_1_eng_idle.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_idle" and shift == "2" and en_log == true and status == "reset") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + ",reseting device\n";
    Serial.println("2dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_2_eng_idle.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_off" and shift == "1" and en_log == true and status == "reset") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + ",reseting device\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_1_eng_off.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_off" and shift == "2" and en_log == true and status == "reset") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + ",reseting device\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_2_eng_off.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }

  while (kondisi == "engine_operation" and shift == "1" and en_log == true and status == "normal") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_1_eng_operation.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_operation" and shift == "2" and en_log == true and status == "normal") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_2_eng_operation.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_idle" and shift == "1" and en_log == true and status == "normal") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + "\n";
    Serial.println("3dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_1_eng_idle.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_idle" and shift == "2" and en_log == true and status == "normal") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + "\n";
    Serial.println("4dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_2_eng_idle.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_off" and shift == "1" and en_log == true and status == "normal") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_1_eng_off.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
  while (kondisi == "engine_off" and shift == "2" and en_log == true and status == "normal") {
    dataLog = cn_unit + "," + serial_number + "," + dates + "," + times + "," + shift + "," + kondisi + "," + time_On + "," + time_Off + "," + total_waktu + "," + longitude + "," + latitude + "," + altitude + "," + heading + "," + speed + "," + fuel_voltage + "\n";
    Serial.println("dataLog: " + dataLog);
    check_dir();
    appendFile(SD, "/shift_2_eng_off.csv", dataLog.c_str());
    appendFile(SD, "/log.csv", dataLog.c_str());
    delay(1000);
    en_log = false;
  }
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.print(F("Message appending : "));
    Serial.println(message);
    Serial.println("Message appended");
  }
  else {
    Serial.println("Append failed");
  }
  file.close();
}
