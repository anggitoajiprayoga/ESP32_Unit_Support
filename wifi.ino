void setup_wifi() {
  // Connect to WiFi network ------------------------------------------------
  Serial.println();
  Serial.print("System Start");
  Serial.println();
  AsyncElegantOTA.begin(&server);

  String APssid2 = cn_unit;
  WiFi.softAP(APssid2.c_str(), pass_wifi_ap.c_str());
  WiFi.mode(WIFI_AP);

  server.begin();
  AsyncElegantOTA.begin(&server);
  server_begin();
}

void loop_wifi() {
  AsyncElegantOTA.loop();
}
