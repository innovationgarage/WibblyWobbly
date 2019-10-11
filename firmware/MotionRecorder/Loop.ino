unsigned long wait;

bool wifiEnabled = WIFI_ENABLED;
unsigned long timeoutWifiAccess = 0;

void loop() {
  if (wifiEnabled && millis() < timeoutWifiAccess)
  {
    server.handleClient();
    MDNS.update();
  }
  else
  {
    if (wifiEnabled)
    {
      // Disable wifi
      DBG_OUTPUT_PORT.print("Checking if nobody is actually connected");

      if (wifi_softap_get_station_num() == 0)
      {
        DBG_OUTPUT_PORT.print("Turning WiFi access point off...");
        WiFi.softAPdisconnect(true);
        WiFi.enableAP(false);
        wifiEnabled = false;
      }
      else
        timeoutWifiAccess = millis() + TIMEOUT_WIFI;
    }
    else
    {
      // Do SD data collection
      // Create the output file
      String filename = String("capture_");
      filename += random(100000, 999999);
      filename += ".txt";

      String d = String("time,diff_ms,ax,ay,az,gx,gy,gz,temp,batt");
      DBG_OUTPUT_PORT.println(filename);

      delay(5000);
      unsigned long startup = millis();
      while (true)
      {
        if (millis() > wait)
        {
          //DBG_OUTPUT_PORT.println("inside");

          File file = SD.open(filename, FILE_WRITE);
          if (file)
          {
            file.println(d);
            file.close();
            digitalWrite(D4, (millis() % 1000) > 500);
          }
          else
          {
            DBG_OUTPUT_PORT.println("error opening file");
          }
          //DBG_OUTPUT_PORT.println("outside");

          // Dump next one
          Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
          d = String(",");
          d += String(AccelX);
          d += String(",");
          d += String(AccelY);
          d += String(",");
          d += String(AccelZ);
          d += String(",");
          d += String(GyroX);
          d += String(",");
          d += String(GyroY);
          d += String(",");
          d += String(GyroZ);
          d += String(",");
          d += String(Temperature);
          d += String(",");
          d += String(analogRead(A0));

          String d2 = String(millis());
          d2 += ",";

          int time_it_took = (millis() - startup);
          startup = millis();

          d2 += time_it_took;
          d = d2 + d;

          wait = millis() + (70 - time_it_took);

          //DBG_OUTPUT_PORT.println("outside4");
          //DBG_OUTPUT_PORT.println(wait);
        }
      }
    }

  }
}
