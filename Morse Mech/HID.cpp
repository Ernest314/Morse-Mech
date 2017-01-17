#include "HID.h"

bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                    uint8_t* const ReportID,
		                                    const uint8_t ReportType,
		                                    void* ReportData,
		                                    uint16_t* const ReportSize)
{
	USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;
	
	*ReportSize = sizeof(USB_KeyboardReport_Data_t);
	return false;
}

void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                    const uint8_t ReportID,
		                                    const uint8_t ReportType,
		                                    const void* ReportData,
		                                    const uint16_t ReportSize)
{
}
