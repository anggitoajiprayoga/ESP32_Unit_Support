void setup_svoltage() {
  pinMode(p_pto, INPUT_PULLUP);
  pinMode(p_running, INPUT_PULLUP);
  pinMode(p_fuel, INPUT_PULLUP);
  pinMode(p_netral, INPUT_PULLUP);
}

void loop_svoltage() {
  value = analogRead(p_fuel);
  Vout = (value * 5.0) / 1024.0;
  Vin  = Vout / (R2 / (R1 + R2));
  fuel_voltage = Vin;

  value_pto = analogRead(p_pto);
  value_running = analogRead(p_running);
  value_netral = analogRead(p_netral);

  if (value_pto > 2000) {
    pto = 1;
  }
  else {
    pto = 0;
  }

  if (value_running > 2000) {
    running = 1;
  }
  else {
    running = 0;
  }

  if (value_netral > 2000) {
    netral = 1;
  }
  else {
    netral = 0;
  }
}
