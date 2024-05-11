void pantalla_Mostrar(){
  //Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  //Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(1, 0, "Remitente " +String(dir_remite, HEX));
  Heltec.display->drawString(1, 10, "Num of pack revd: "+ String(paqrcbID));
  //Heltec.display->drawString(0, 50, "dir Local: " + String(dir_local, HEX));
  Heltec.display->drawString(7, 20, "* RSSI: " + String(rssi_lora)+ " dBm");
  Heltec.display->drawString(7, 30, "* S_R: " + String(snr_lora)+ " dBm");
  //Heltec.display -> display();
}