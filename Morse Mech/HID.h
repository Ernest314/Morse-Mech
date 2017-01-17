#ifndef _HID_H_
#define _HID_H_

#include "globals.h"
#include "LUFA/Drivers/USB/USB.h"

void EVENT_USB_Device_Connect();
void EVENT_USB_Device_Disconnect();
void EVENT_USB_Device_ConfigurationChanged();
void EVENT_USB_Device_ControlRequest();
void EVENT_USB_Device_StartOfFrame();

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                    uint8_t* const ReportID,
		                                    const uint8_t ReportType,
		                                    void* ReportData,
		                                    uint16_t* const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                    const uint8_t ReportID,
		                                    const uint8_t ReportType,
		                                    const void* ReportData,
		                                    const uint16_t ReportSize);

#endif	// _HID_H_
