#include <BLE_API.h>
#include <stdio.h>

BLE & ble = BLE::Instance();

const unsigned char bit_mask[8] = {
        1,
        2,
        4,
        8,
        16,
        32,
        64,
        128
};


void sendManufactureData(const uint8_t len, const uint8_t * data)
{
    if (len == 8) 
    {
        short manufactureId = 0;
        long deviceId = 0;
        short temperature = 0;
        uint8_t i = 0;                
        while (i < 2) 
        {
            manufactureId = manufactureId << 8;
            manufactureId = manufactureId | data[i++];
        }

        if (manufactureId) 
        {
            while (i >= 2 && i < 6) 
            {
                deviceId = deviceId << 8;
                deviceId = deviceId | data[i++];
            }
            while (i >= 6 && i < 8) 
            {
                temperature = temperature << 8;
                temperature = temperature | data[i++];
            }
            
            for(i=0;i < 8;i++)
            {
                Serial.write(data[i]);    
            }
            Serial.print("\n");
        }
    } 
}


void printDataField(uint8_t len, const uint8_t * data, uint8_t fieldType) 
{
    switch (fieldType) 
    {
        case 0x01:
            break;
        case 0xFF:
            sendManufactureData(len, data);
            break;
    }
}


void printAdvertisedData(const uint8_t len, const uint8_t * data) 
{
    uint8_t dataSize = 0;
    uint8_t fieldType = 0;
    uint8_t i = 0;

//    /* Print the entire ADV data */
//    {
//        uint8_t counter = 0;
//        Serial.print("Data: ");
//        for(; counter < len; counter++)
//        {
//            Serial.write(data[counter]);
//        }
//        Serial.println();
//    }
    
    /* Iterate through the ADV data and split fields */
    while (i < len) 
    {
        dataSize = data[i] - 1;
        fieldType = data[++i];
        ++i;
        printDataField(dataSize, (data + i), fieldType);
        i = i + dataSize;
    }
}


void advertisementCallback(const Gap::AdvertisementCallbackParams_t * params) 
{
    if (params->type == GapAdvertisingParams::ADV_NON_CONNECTABLE_UNDIRECTED) 
    {
        printAdvertisedData(params->advertisingDataLen, params->advertisingData);
    } 
    else 
    {
        /* Drop all other packets */
    }
}


void setup() 
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    ble.init();
    ble.gap().setScanParams();
    ble.gap().startScan(advertisementCallback);
    ble.gap().setDeviceName((const uint8_t * ) "Observer");
}


void loop() 
{
    // put your main code here, to run repeatedly:
    ble.waitForEvent();
}

