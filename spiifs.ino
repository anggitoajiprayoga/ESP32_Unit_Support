void data_default() // kalau masih  perawan, belum ada database // ntar lu isi defaultnya apa
{
  if (String(readFile(SPIFFS, "/sn.txt")) == "") {
    sn = 999;
    writeFile(SPIFFS, "/sn.txt", "000000");
  }
  else {
    sn = readFile(SPIFFS, "/sn.txt");
  }
  writeFile(SPIFFS, "/reset.txt", "1");
  writeFile(SPIFFS, "/cn_unit.txt", cn_default.c_str());
  writeFile(SPIFFS, "/serial_number.txt", sn_default.c_str());
  writeFile(SPIFFS, "/http_username.txt", "admin");
  writeFile(SPIFFS, "/http_password.txt", "admin");
  writeFile(SPIFFS, "/ssid_wifi_client.txt", "SS6");
  writeFile(SPIFFS, "/pass_wifi_client.txt", "");
  writeFile(SPIFFS, "/ssid_wifi_ap.txt", cn_default.c_str());
  writeFile(SPIFFS, "/pass_wifi_ap.txt", "12345678");
  Serial.println("default ok");
}

void read_setting()
{
  http_username = readFile(SPIFFS, "/http_username.txt");
  http_password = readFile(SPIFFS, "/http_password.txt");

  if (http_username == "" and http_password == "") // kalau masih perawan, belum ada database // ntar lu isi defaultnya apa
  {
    data_default();
    delay(200);
  }

  http_username = readFile(SPIFFS, "/http_username.txt");
  http_password = readFile(SPIFFS, "/http_password.txt");
  SN = readFile(SPIFFS, "/serial_number.txt");
  serial_number = readFile(SPIFFS, "/serial_number.txt");
  cn_unit = readFile(SPIFFS, "/cn_unit.txt");
  cn = readFile(SPIFFS, "/cn_unit.txt");
  ssid_wifi_ap = cn_unit;
  ssid_wifi_ap =  readFile(SPIFFS, "/ssid_wifi_ap.txt");
  pass_wifi_ap =  readFile(SPIFFS, "/pass_wifi_ap.txt");

  Serial.print("SPIFFS Free: "); Serial.println(humanReadableSize((SPIFFS.totalBytes() - SPIFFS.usedBytes())));
  Serial.print("SPIFFS Used: "); Serial.println(humanReadableSize(SPIFFS.usedBytes()));
  Serial.print("SPIFFS Total: "); Serial.println(humanReadableSize(SPIFFS.totalBytes()));
}

void notFoundd(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char * path) {
  File file = fs.open(path, "r");
  if (!file || file.isDirectory())
  {
    return String();
  }
  String fileContent;
  while (file.available())
  {
    fileContent += String((char)file.read());
  }
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message)
{
  File file = fs.open(path, "w");
  if (!file)
  {
    return;
  }
  file.print(message);
}

String processor(const String& var)
{
  if (var == "version")
  {
    return version;
  }
  else if (var == "longitude")
  {
    return readFile(SPIFFS, "/longitude.txt");
  }
  else if (var == "latitude") {
    return readFile(SPIFFS, "/latitude.txt");
  }
  else if (var == "serial_number")
  {
    return readFile(SPIFFS, "/serial_number.txt");
  }

  else if (var == "cn_unit")
  {
    return readFile(SPIFFS, "/cn_unit.txt");
  }

  else if (var == "set_time")
  {
    return times;
  }

  else if (var == "set_date")
  {
    return dates;
  }

  else if (var == "freespace") {
    int xfreesp = SD.totalBytes() / (1024 * 1024);
    freesp = String(xfreesp) + " MB";
    return freesp;
  }

  else if (var == "usedstorage") {
    int xusedstr = SD.usedBytes() / (1024 * 1024);
    usedstr = String(xusedstr) + " MB";
    return usedstr;
  }

  else if (var == "totalStorage") {
    int xtotalstr = SD.cardSize() / (1024 * 1024);
    totalstr = String(xtotalstr) + " MB";
    return totalstr;
  }

  else
  {
    return String();
  }
}

void server_begin()
{
  server.serveStatic("/", SPIFFS, "/");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();
    read_setting();
    request->send(SPIFFS, "/dashboard.html", String(), false, processor);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->redirect("/");
  });

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(401, "text/html", "<script>alert('Logout Success!'); window.location='/';</script>");
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request)
  {
    if (!request->authenticate(http_username.c_str(), http_password.c_str()))
      return request->requestAuthentication();

    String inputMessage;
    if (request->hasParam("set_date") and request->hasParam("set_time"))
    {
      inputMessage = request->getParam("set_date")->value();
      writeFile(SPIFFS, "/set_date.txt", inputMessage.c_str());

      inputMessage = request->getParam("set_time")->value();
      writeFile(SPIFFS, "/set_time.txt", inputMessage.c_str());

      delay(500);
      String set_date = readFile(SPIFFS, "/set_date.txt");
      String set_time = readFile(SPIFFS, "/set_time.txt") + ":0";
      parsing_setDateTime(set_date, set_time);
      delay(500);
      Rtc.SetDateTime(RtcDateTime(value_year.toInt(), value_month.toInt(), value_day.toInt(), value_hour.toInt(), value_minute.toInt(), value_second.toInt())); //tahun, bulan, tanggal, jam, menit, detik
      Serial.println("/n===============================");
      Serial.println("Set Jam Sukses");
      Serial.println("data_set: " + set_date + " " + set_time);
      Serial.println("===============================/n");
      delay(1000);
    }

    else if (request->hasParam("serial_number") and request->hasParam("cn_unit"))
    {
      inputMessage = request->getParam("serial_number")->value();
      writeFile(SPIFFS, "/serial_number.txt", inputMessage.c_str());

      inputMessage = request->getParam("cn_unit")->value();
      writeFile(SPIFFS, "/cn_unit.txt", inputMessage.c_str());
    }

    read_setting();
    request->redirect("/");
  });

  server.onNotFound(notFoundd);
  server.begin();
}
