#ifndef BLYNK_CONFIG_H
#define BLYNK_CONFIG_H

#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi_config.h"

String blynk_image_pin = "V1";  // Image Widget

void sendImageToBlynk(String base64Image) {
    HTTPClient http;

    String url = String("http://") + BLYNK_SERVER + "/external/api/update?"
                "token=" + BLYNK_TOKEN +
                "&" + blynk_image_pin + "=" + base64Image;

    http.begin(url);
    int httpResponse = http.GET();
    http.end();
}

#endif
