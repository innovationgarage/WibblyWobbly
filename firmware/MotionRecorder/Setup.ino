void setup(void)
{
  DBG_OUTPUT_PORT.begin(115200);
  DBG_OUTPUT_PORT.setDebugOutput(true);
  DBG_OUTPUT_PORT.println("Starting");

  //Wire.begin(sda, scl);
  Wire.begin();
  MPU6050_Init();
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  DBG_OUTPUT_PORT.println();

  if (!Rtc.IsDateTimeValid())
  {
    if (Rtc.LastError() != 0)
    {
      // we have a communications error
      // see https://www.arduino.cc/en/Reference/WireEndTransmission for
      // what the number means
      DBG_OUTPUT_PORT.print("RTC communications error = ");
      DBG_OUTPUT_PORT.println(Rtc.LastError());
    }
    else
    {
      // Common Causes:
      //    1) first time you ran and the device wasn't running yet
      //    2) the battery on the device is low or even missing

      DBG_OUTPUT_PORT.println("RTC lost confidence in the DateTime!");
      // following line sets the RTC to the date & time this sketch was compiled
      // it will also reset the valid flag internally unless the Rtc device is
      // having an issue

      Rtc.SetDateTime(compiled);
    }
  }

  if (!Rtc.GetIsRunning())
  {
    DBG_OUTPUT_PORT.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    DBG_OUTPUT_PORT.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    DBG_OUTPUT_PORT.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    DBG_OUTPUT_PORT.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);

  DBG_OUTPUT_PORT.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    DBG_OUTPUT_PORT.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  DBG_OUTPUT_PORT.println("card initialized.");

  if (wifiEnabled)
  {
    DBG_OUTPUT_PORT.print("Configuring WiFi access point...");

    /* You can remove the password parameter if you want the AP to be open. */
    boolean result = WiFi.softAP(String(ssid) + String(" - ") + String(ESP.getChipId())/*, password*/);
    if (result == true) {
      IPAddress myIP = WiFi.softAPIP();

      DBG_OUTPUT_PORT.println("done!");
      DBG_OUTPUT_PORT.println("");
      DBG_OUTPUT_PORT.print("WiFi network name: ");
      DBG_OUTPUT_PORT.println(ssid);
      DBG_OUTPUT_PORT.print("WiFi network password: ");
      //DBG_OUTPUT_PORT.println(password);
      DBG_OUTPUT_PORT.print("Host IP Address: ");
      DBG_OUTPUT_PORT.println(myIP);
      DBG_OUTPUT_PORT.println("");
    }
    else
    {
      DBG_OUTPUT_PORT.println("error! Something went wrong...");
    }

    if (MDNS.begin(host)) {
      MDNS.addService("http", "tcp", 80);
      DBG_OUTPUT_PORT.println("MDNS responder started");
      DBG_OUTPUT_PORT.print("You can now connect to http://");
      DBG_OUTPUT_PORT.print(host);
      DBG_OUTPUT_PORT.println(".local");
    }

    server.on("/list", HTTP_GET, printDirectory);
    server.on("/edit", HTTP_DELETE, handleDelete);
    server.on("/edit", HTTP_PUT, handleCreate);
    server.on("/edit", HTTP_POST, []() {
      returnOK();
    }, handleFileUpload);
    server.onNotFound(handleNotFound);

    server.begin();
    DBG_OUTPUT_PORT.println("HTTP server started");
    timeoutWifiAccess = millis() + TIMEOUT_WIFI;
  }
  if (SD.begin(chipSelect)) {
    DBG_OUTPUT_PORT.println("SD Card initialized.");
    hasSD = true;
  }
}
