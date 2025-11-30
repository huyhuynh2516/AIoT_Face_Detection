#include <WiFi.h>
#include "esp_camera.h"
#include "camera_config.h"
#include "wifi_config.h"
#include "blynk_config.h"

#define PIR_PIN 14  // GPIO PIR

void setup() {
    Serial.begin(115200);

    pinMode(PIR_PIN, INPUT);

    // WiFi connect
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");

    // Camera Setup
    camera_config_t config = getCameraConfig();

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.println("Camera init failed!");
        return;
    }

    Serial.println("Camera ready!");
}

void loop() {
    int motion = digitalRead(PIR_PIN);

    if (motion == HIGH) {
        Serial.println("Motion detected!");

        // Capture image
        camera_fb_t *fb = esp_camera_fb_get();

        if (!fb) {
            Serial.println("Failed to capture image!");
            return;
        }

        // Encode Base64
        String image_base64 = base64::encode(fb->buf, fb->len);

        // Free memory
        esp_camera_fb_return(fb);

        // Send to Blynk
        sendImageToBlynk(image_base64);

        Serial.println("Image sent to Blynk!");
        delay(3000);
    }
}
