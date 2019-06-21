long wait = 0;

/*void loop()
{

  if (millis() > wait)
  {
    Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
    Serial.print(AccelX);
    Serial.println();


    if (!Rtc.IsDateTimeValid())
    {
      if (Rtc.LastError() != 0)
      {
        // we have a communications error
        // see https://www.arduino.cc/en/Reference/WireEndTransmission for
        // what the number means
        Serial.print("RTC communications error = ");
        Serial.println(Rtc.LastError());
      }
      else
      {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
      }
    }

    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();
    wait = millis() + 100;

    // make a string for assembling the data to log:
    String dataString = "";

    // read three sensors and append to the string:
    //for (int analogPin = 0; analogPin < 3; analogPin++) {
    //  int sensor = analogRead(analogPin);
    //  dataString += String(sensor);
    //  if (analogPin < 2) {
    //    dataString += ",";
    //  }
    //}
    dataString += String(Rtc.GetDateTime());
    dataString += String(",");
    dataString += String(AccelX);

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("capture.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }


  }
}
*/
