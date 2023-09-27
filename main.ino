void mainn() {
  if (running == 1) { //hm
    if (hm == 0) {
      hm = 1;
      idle = 0;
      standby = 0;
      en_writehm = 1;
      timer_hmOn = times;
      tanggal_hmOn = dates;
      timer_hmOff = "";
      tanggal_hmOff = "";
      status_http = "engine_operation";
      //      Data = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi_http\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time_http\":\"" + times + "\",\"time\":\"" + times + "\",\"shift_http\":\"" + String(shift) + "\",\"time_On_http\":\"" + timer_hmOn + "\",\"time_Off_http\":\"" + timer_hmOff + "\",\"total_waktu_http\":\"" + String("") + "\",\"longitude_http\":\"" + longi + "\",\"latitude_http\":\"" + latd + "\",\"altitude_http\":\"" + altitude + "\",\"heading_http\":\"" + dir + "\",\"speed_http\":\"" + sped + "\",\"fuel_voltage_http\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(false) + "\"}";
      Data = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition_http\":\"" + status_http + "\",\"time_full_http\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_hm_http\":\"" + tanggal_hmOn + " " + timer_hmOn + "\",\"time_off_hm_http\":\"" + tanggal_hmOff + " " + timer_hmOff + "\",\"duration_hm_http\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    }

    if (pto == 0) {
      hm = 1;
      idle = 0;
      standby = 0;
      en_writehm = 1;
    }
  }

  if (running == 1 and pto == 1) { //idle
    if (idle == 0) {
      hm = 1;
      idle = 1;
      standby = 0;
      en_writeidle = 1;
      en_writehm = 1;
      timer_idleOn = times;
      tanggal_idleOn = dates;
      timer_idleOff = "";
      tanggal_idleOff = "";
      status_http = "engine_idle";
      //      Data = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi_http\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time_http\":\"" + times + "\",\"time\":\"" + times + "\",\"shift_http\":\"" + String(shift) + "\",\"time_On_http\":\"" + timer_idleOn + "\",\"time_Off_http\":\"" + timer_idleOff + "\",\"total_waktu_http\":\"" + String("") + "\",\"longitude_http\":\"" + longi + "\",\"latitude_http\":\"" + latd + "\",\"altitude_http\":\"" + altitude + "\",\"heading_http\":\"" + dir + "\",\"speed_http\":\"" + sped + "\",\"fuel_voltage_http\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(false) + "\"}";
      Data = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition_http\":\"" + status_http + "\",\"time_full_http\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_idle_http\":\"" + tanggal_idleOn + " " + timer_idleOn + "\",\"time_off_idle_http\":\"" + tanggal_idleOff + " " + timer_idleOff + "\",\"duration_idle_http\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    }
  }

  if (running == 0) { //standby
    if (standby == 0) {
      hm = 0;
      idle = 0;
      standby = 1;
      en_writestandby = 1;
      timer_standbyOn = times;
      tanggal_standbyOn = dates;
      timer_standbyOff = "";
      tanggal_standbyOff = "";
      status_http = "engine_off";
      //      Data = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi_http\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time_http\":\"" + times + "\",\"time\":\"" + times + "\",\"shift_http\":\"" + String(shift) + "\",\"time_On_http\":\"" + timer_standbyOn + "\",\"time_Off_http\":\"" + timer_standbyOff + "\",\"total_waktu_http\":\"" + String("") + "\",\"longitude_http\":\"" + longi + "\",\"latitude_http\":\"" + latd + "\",\"altitude_http\":\"" + altitude + "\",\"heading_http\":\"" + dir + "\",\"speed_http\":\"" + sped + "\",\"fuel_voltage_http\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(false) + "\"}";
      Data = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition_http\":\"" + status_http + "\",\"time_full_http\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_standby_http\":\"" + tanggal_standbyOn + " " + timer_standbyOn + "\",\"time_off_standby_http\":\"" + tanggal_standbyOff + " " + timer_standbyOff + "\",\"duration_standby_http\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    }
  }

  if (hm == 0 and en_writehm == true) {
    timer_hmOff = times;
    tanggal_hmOff = dates;
    lat_hmOff = latd;
    long_hmOff = longi;
    altid_hmOff = altitude;
    dir_hmOff = dir;
    speed_hmOff = sped;
    fuel_voltagehmOff = String(Vin, 1);
    parsing_hm();
    total_waktu("eng_operation", jam_hmOn.toInt(), mnt_hmOn.toInt(), dtk_hmOn.toInt(), jam_hmOff.toInt(), mnt_hmOff.toInt(), dtk_hmOff.toInt(), hari_hmOn.toInt(), bulan_hmOn.toInt(), tahun_hmOn.toInt(), hari_hmOff.toInt(), bulan_hmOff.toInt(), tahun_hmOff.toInt());
    total_jamhm = String(selisih_jamhm) + ":" + String(selisih_mnthm) + ":" + String(selisih_dtkhm);
    status = "engine_operation";
    //    final_hm = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi\":\"" + status + "\",\"date\":\"" + dates + "\",\"time\":\"" + times + "\",\"shift\":\"" + String(shift) + "\",\"time_On\":\"" + timer_hmOn + "\",\"time_Off\":\"" + timer_hmOff + "\",\"total_waktu\":\"" + String(selisih_hm) + "\",\"longitude\":\"" + long_hmOff + "\",\"latitude\":\"" + lat_hmOff + "\",\"altitude\":\"" + altid_hmOff + "\",\"heading\":\"" + dir_hmOff + "\",\"speed\":\"" + String(speed_hmOff) + "\",\"fuel_voltage\":\"" + String(fuel_voltagehmOff) + "\",\"en_log\":\"" + String(true) + "\"}";
    final_hm = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition\":\"" + status + "\",\"time_full\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_hm\":\"" + tanggal_hmOn + " " + timer_hmOn + "\",\"time_off_hm\":\"" + tanggal_hmOff + " " + timer_hmOff + "\",\"duration_hm\":\"" + String(selisih_hm) + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    Serial.println("send final hm OK");
    Serial.println();
    logging(status, String(shift), timer_hmOn, timer_hmOff, String(selisih_hm), true, "normal");
    en_send = false;
    Serial_atmel.println(final_hm);
    en_writehm = 0;
    counthm = 0;
    delay(3000);
    en_send = true;
  }

  if (idle == 0 and en_writeidle == true) {
    timer_idleOff = times;
    tanggal_idleOff = dates;
    lat_idleOff = latd;
    long_idleOff = longi;
    altid_idleOff = altitude;
    dir_idleOff = dir;
    speed_idleOff = sped;
    fuel_voltageidleOff = String(Vin, 1);
    parsing_idle();
    total_waktu("eng_idle", jam_idleOn.toInt(), mnt_idleOn.toInt(), dtk_idleOn.toInt(), jam_idleOff.toInt(), mnt_idleOff.toInt(), dtk_idleOff.toInt(), hari_idleOn.toInt(), bulan_idleOn.toInt(), tahun_idleOn.toInt(), hari_idleOff.toInt(), bulan_idleOff.toInt(), tahun_idleOff.toInt());
    total_jamidle = String(selisih_jamidle) + ":" + String(selisih_mntidle) + ":" + String(selisih_dtkidle);
    status = "engine_idle";
    //    final_idle = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi\":\"" + status + "\",\"date\":\"" + dates + "\",\"time\":\"" + times + "\",\"shift\":\"" + String(shift) + "\",\"time_On\":\"" + timer_idleOn + "\",\"time_Off\":\"" + timer_idleOff + "\",\"total_waktu\":\"" + String(selisih_idle) + "\",\"longitude\":\"" + long_idleOff + "\",\"latitude\":\"" + lat_idleOff + "\",\"altitude\":\"" + altid_idleOff + "\",\"heading\":\"" + dir_idleOff + "\",\"speed\":\"" + String(speed_idleOff) + "\",\"fuel_voltage\":\"" + String(fuel_voltagehmOff) + "\",\"en_log\":\"" + String(true) + "\"}";
    final_idle = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition\":\"" + status + "\",\"time_full\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_idle\":\"" + tanggal_idleOn + " " + timer_idleOn + "\",\"time_off_idle\":\"" + tanggal_idleOff + " " + timer_idleOff + "\",\"duration_idle\":\"" + String(selisih_idle) + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    Serial.println("send final idle OK");
    Serial.println();
    logging(status, String(shift), timer_idleOn, timer_idleOff, String(selisih_idle), true, "normal");
    en_send = false;
    Serial_atmel.println(final_idle);
    en_writeidle = 0;
    countidle = 0;
    delay(3000);
    en_send = true;
  }

  if (standby == 0 and en_writestandby == true) {
    timer_standbyOff = times;
    tanggal_standbyOff = dates;
    lat_standbyOff = latd;
    long_standbyOff = longi;
    altid_standbyOff = altitude;
    dir_standbyOff = dir;
    speed_standbyOff = sped;
    fuel_voltagestandbyOff = String(Vin, 1);
    parsing_standby();
    total_waktu("eng_off", jam_standbyOn.toInt(), mnt_standbyOn.toInt(), dtk_standbyOn.toInt(), jam_standbyOff.toInt(), mnt_standbyOff.toInt(), dtk_standbyOff.toInt(), hari_standbyOn.toInt(), bulan_standbyOn.toInt(), tahun_standbyOn.toInt(), hari_standbyOff.toInt(), bulan_standbyOff.toInt(), tahun_standbyOff.toInt());
    total_jamstandby = String(selisih_jamstandby) + ":" + String(selisih_mntstandby) + ":" + String(selisih_dtkstandby);
    status = "engine_off";
    //    final_standby = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi\":\"" + status + "\",\"date\":\"" + dates + "\",\"time\":\"" + times + "\",\"shift\":\"" + String(shift) + "\",\"time_On\":\"" + timer_standbyOn + "\",\"time_Off\":\"" + timer_standbyOff + "\",\"total_waktu\":\"" + String(selisih_standby) + "\",\"longitude\":\"" + long_standbyOff + "\",\"latitude\":\"" + lat_standbyOff + "\",\"altitude\":\"" + altid_standbyOff + "\",\"heading\":\"" + dir_standbyOff + "\",\"speed\":\"" + String(speed_standbyOff) + "\",\"fuel_voltage\":\"" + String(fuel_voltagestandbyOff) + "\",\"en_log\":\"" + String(true) + "\"}";
    final_standby = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition\":\"" + status + "\",\"time_full\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_standby\":\"" + tanggal_standbyOn + " " + timer_standbyOn + "\",\"time_off_standby\":\"" + tanggal_standbyOff + " " + timer_standbyOff + "\",\"duration_standby\":\"" + String(selisih_standby) + "\"\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    Serial.println("send final standby OK");
    Serial.println();
    logging(status, String(shift), timer_standbyOn, timer_standbyOff, String(selisih_standby), true, "normal");
    en_send = false;
    Serial_atmel.println(final_standby);
    en_writestandby = 0;
    countstandby = 0;
    delay(3000);
    en_send = true;
  }

  if (hm == 1) {
    kondisi = "engine_operation";
    //    Data = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi_http\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time_http\":\"" + times + "\",\"time\":\"" + times + "\",\"shift_http\":\"" + String(shift) + "\",\"time_On_http\":\"" + timer_hmOn + "\",\"time_Off_http\":\"" + timer_hmOff + "\",\"total_waktu_http\":\"" + String("") + "\",\"longitude_http\":\"" + longi + "\",\"latitude_http\":\"" + latd + "\",\"altitude_http\":\"" + altitude + "\",\"heading_http\":\"" + dir + "\",\"speed_http\":\"" + sped + "\",\"fuel_voltage_http\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(false) + "\"}";
    Data = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition_http\":\"" + status_http + "\",\"time_full_http\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_hm_http\":\"" + tanggal_idleOn + " " + timer_hmOn + "\",\"time_off_hm_http\":\"" + tanggal_hmOff + " " + timer_hmOff + "\",\"duration_hm_http\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
  }

  if (idle == 1) {
    kondisi = "engine_idle";
    //    Data = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi_http\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time_http\":\"" + times + "\",\"time\":\"" + times + "\",\"shift_http\":\"" + String(shift) + "\",\"time_On_http\":\"" + timer_idleOn + "\",\"time_Off_http\":\"" + timer_idleOff + "\",\"total_waktu_http\":\"" + String("") + "\",\"longitude_http\":\"" + longi + "\",\"latitude_http\":\"" + latd + "\",\"altitude_http\":\"" + altitude + "\",\"heading_http\":\"" + dir + "\",\"speed_http\":\"" + sped + "\",\"fuel_voltage_http\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(false) + "\"}";
    Data = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition_http\":\"" + status_http + "\",\"time_full_http\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_idle_http\":\"" + tanggal_idleOn + " " + timer_idleOn + "\",\"time_off_idle_http\":\"" + tanggal_idleOff + " " + timer_idleOff + "\",\"duration_idle_http\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
  }

  if (standby == 1) {
    kondisi = "engine_off";
    //    Data = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi_http\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time_http\":\"" + times + "\",\"time\":\"" + times + "\",\"shift_http\":\"" + String(shift) + "\",\"time_On_http\":\"" + timer_standbyOn + "\",\"time_Off_http\":\"" + timer_standbyOff + "\",\"total_waktu_http\":\"" + String("") + "\",\"longitude_http\":\"" + longi + "\",\"latitude_http\":\"" + latd + "\",\"altitude_http\":\"" + altitude + "\",\"heading_http\":\"" + dir + "\",\"speed_http\":\"" + sped + "\",\"fuel_voltage_http\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(false) + "\"}";
    Data = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition_http\":\"" + status_http + "\",\"time_full_http\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_standby_http\":\"" + tanggal_standbyOn + " " + timer_standbyOn + "\",\"time_off_standby_http\":\"" + tanggal_standbyOff + " " + timer_standbyOff + "\",\"duration_standby_http\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
  }

  if (millis() - prevv > 1000) {
    count_second++;
    prevv = millis();
  }

  if (count_second > 10) {
    if (en_send == true) {
      Serial_atmel.println(Data);
    }
    count_second = 0;
  }
}

void backup_changeshift() {
  if (hm == 1) {
    parsing_backup();
    parsing_hm();
    total_waktu("eng_operation", jam_hmOn.toInt(), mnt_hmOn.toInt(), dtk_hmOn.toInt(), jam_backupOff.toInt(), mnt_backupOff.toInt(), dtk_backupOff.toInt(), hari_hmOn.toInt(), bulan_hmOn.toInt(), tahun_hmOn.toInt(), hari_backupOff.toInt(), bulan_backupOff.toInt(), tahun_backupOff.toInt());
    //    final_payload = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time\":\"" + times + "\",\"shift\":\"" + String(shift) + "\",\"time_On\":\"" + timer_hmOn + "\",\"time_Off\":\"" + times + "\",\"total_waktu\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + dir + "\",\"speed\":\"" + sped + "\",\"fuel_voltage\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(true) + "\",\"en_rst\":\"" + String(true) + "\"}";
    final_payload = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition\":\"" + status_http + "\",\"time_full\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_hm\":\"" + tanggal_hmOn + " " + timer_hmOn + "\",\"time_off_hm\":\"" + dates + " " + times + "\",\"duration_hm\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    logging(status, String(shift), timer_hmOn, times, String(selisih_hm), true, "reset");
    Serial_atmel.println("{\"en_rst\":\"" + String(true) + "\"}");
    delay(1000);
    writeFile(SPIFFS, "/reset.txt", "0");
    Serial.println("Reset!!!!");
    ESP.restart();
  }
  else if (idle == 1) {
    parsing_backup();
    parsing_idle();
    total_waktu("eng_idle", jam_idleOn.toInt(), mnt_idleOn.toInt(), dtk_idleOn.toInt(), jam_backupOff.toInt(), mnt_backupOff.toInt(), dtk_backupOff.toInt(), hari_idleOn.toInt(), bulan_idleOn.toInt(), tahun_idleOn.toInt(), hari_backupOff.toInt(), bulan_backupOff.toInt(), tahun_backupOff.toInt());
    //    final_payload = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time\":\"" + times + "\",\"shift\":\"" + String(shift) + "\",\"time_On\":\"" + timer_idleOn + "\",\"time_Off\":\"" + times + "\",\"total_waktu\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + dir + "\",\"speed\":\"" + sped + "\",\"fuel_voltage\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(true) + "\",\"en_rst\":\"" + String(true) + "\"}";
    final_payload = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition\":\"" + status_http + "\",\"time_full\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_idle\":\"" + tanggal_idleOn + " " + timer_idleOn + "\",\"time_off_idle\":\"" + dates + " " + times + "\",\"duration_idle\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    logging(status, String(shift), timer_idleOn, times, String(selisih_idle), true, "reset");
    Serial_atmel.println("{\"en_rst\":\"" + String(true) + "\"}");
    delay(1000);
    writeFile(SPIFFS, "/reset.txt", "0");
    Serial.println("Reset!!!!");
    ESP.restart();
  }
  else if (standby == 1) {
    parsing_backup();
    parsing_standby();
    total_waktu("eng_off", jam_standbyOn.toInt(), mnt_standbyOn.toInt(), dtk_standbyOn.toInt(), jam_backupOff.toInt(), mnt_backupOff.toInt(), dtk_backupOff.toInt(), hari_standbyOn.toInt(), bulan_standbyOn.toInt(), tahun_standbyOn.toInt(), hari_backupOff.toInt(), bulan_backupOff.toInt(), tahun_backupOff.toInt());
    //    final_payload = "{\"CN\":\"" + cn + "\",\"SN\":\"" + SN + "\",\"kondisi\":\"" + status_http + "\",\"date\":\"" + dates + "\",\"time\":\"" + times + "\",\"shift\":\"" + String(shift) + "\",\"time_On\":\"" + timer_standbyOn + "\",\"time_Off\":\"" + times + "\",\"total_waktu\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + dir + "\",\"speed\":\"" + sped + "\",\"fuel_voltage\":\"" + String(Vin, 1) + "\",\"en_log\":\"" + String(true) + "\",\"en_rst\":\"" + String(true) + "\"}";
    final_payload = "{\"cn\":\"" + cn + "\",\"sn\":\"" + SN + "\",\"condition\":\"" + status_http + "\",\"time_full\":\"" + dates + " " + times + "\",\"shift\":\"" + String(shift) + "\",\"time_on_standby\":\"" + tanggal_standbyOn + " " + timer_standbyOn + "\",\"time_off_standby\":\"" + dates + " " + times + "\",\"duration_standby\":\"" + String("") + "\",\"longitude\":\"" + longi + "\",\"latitude\":\"" + latd + "\",\"altitude\":\"" + altitude + "\",\"heading\":\"" + heading + "\",\"speed\":\"" + speed + "\",\"fuel_voltage\":\"" + fuel_voltage + "\",\"device_date\":\"" + dates + " " + times + "\"}";
    logging(status, String(shift), timer_standbyOn, times, String(selisih_standby), true, "reset");
    Serial_atmel.println("{\"en_rst\":\"" + String(true) + "\"}");
    delay(1000);
    writeFile(SPIFFS, "/reset.txt", "0");
    Serial.println("Reset!!!!");
    ESP.restart();
  }

  Serial.println("payload_backup: " + final_payload);
  Serial_atmel.println(final_payload);
  delay(3000);
}

void parsing() {
  while (Serial_atmel.available() > 0) {
    paketData = Serial_atmel.readStringUntil('\n');
    Serial.print("paket: ");
    Serial.println(paketData);
    json_parse();
  }
}

void json_parse() {
  DynamicJsonDocument doc(1024);
  String input = paketData;
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();

  longitude = obj["longitude"].as<String>();
  latitude = obj["latitude"].as<String>();
  altitude = obj["altitude"].as<String>();
  heading = obj["heading"].as<String>();
  speed = obj["speed"].as<String>();

  if (longitude != "null" and latitude != "null") {
    writeFile(SPIFFS, "/longitude.txt", longitude.c_str());
    writeFile(SPIFFS, "/latitude.txt", latitude.c_str());
  }

  if (longitude == "null") {
    longitude = "";
  }
  if (latitude == "null") {
    latitude = "";
  }
  if (altitude == "null") {
    altitude = "";
  }
  if (heading == "null") {
    heading = "";
  }
  if (speed == "null") {
    speed = "";
  }

  String output;
  serializeJson(doc, output);
}

void serial_monitor() {
  if (millis() - prev > 1500) {
    Serial.println("value_pto: " + String(value_pto) + " | value_running: " + String(value_running) + " | value_netral: " + String(value_netral) + " | value_Fuel: " + String(value));
    Serial.println("pto: " + String(pto) + " | running: " + String(running) + " | netral: " + String(netral) + " | Fuel: " + String(Vin));
    Serial.println("kondisi_sekarang: " + kondisi + " | kondisi terakhir: " + status + " | shift: " + String(shift) + " | xshift: " + String(xshift));
    Serial.println("dates: " + dates + " | times: " + times);
    Serial.println("longitude: " + longitude + " | latitude: " + latitude + " | altitude: " + altitude + " | heading: " + heading + " | speed: " + speed);
    Serial.println("hm: " + String(hm) + " | idle: " + String(idle) + " | standby: " + String(standby));
    Serial.println("timerSBon: " + String(timer_standbyOn) + " | timerSBoff: " + String(timer_standbyOff) + " | tanggalSB: " + String(tanggal_standbyOn));
    Serial.println("timerHMon: " + String(timer_hmOn) + " | timerHMoff: " + String(timer_hmOff) + " | tanggalHM: " + String(tanggal_hmOn));
    Serial.println("timeridleon: " + String(timer_idleOn) + " | timeridleoff: " + String(timer_idleOff) + " | tanggalidle: " + String(tanggal_idleOn));
    Serial.println("final_hm: " + final_hm);
    Serial.println("final_idle: " + final_idle);
    Serial.println("final_standby: " + final_standby);
    Serial.println();
    prev = millis();
  }
}
