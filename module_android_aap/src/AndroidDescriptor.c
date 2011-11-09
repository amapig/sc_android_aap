#include "USBHostLLD.h"
#include "usb_descriptors.h"

/*

Descriptors from an Android Device from MAC OS X USB Prober

High Speed device @ 6 (0xFA130000): .............................................   Composite device: "Nexus One" 
   Port Information:   0x0018 
   Device Descriptor   
   Configuration Descriptor (current config)   
       Length (and contents):   32 
       Number of Interfaces:   1 
       Configuration Value:   1 
       Attributes:   0xC0 (self-powered) 
       MaxPower:   500 ma 
       Interface #0 - Vendor-specific ..............................................   "Android Accessory Interface" 
           Alternate Setting   0 
           Number of Endpoints   2 
           Interface Class:   255   (Vendor-specific) 
           Interface Subclass;   255   (Vendor-specific) 
           Interface Protocol:   0 
           Endpoint 0x83 - Bulk Input   
           Endpoint 0x03 - Bulk Output   

*/

#define EP_DESC_COUNT   2
#define IF_DESC_COUNT   1

int nDeviceEPs = EP_DESC_COUNT;
s_usb_endpoint deviceEPs[EP_DESC_COUNT] =
{
    {
        EPTransferType_Bulk,
        EPSyncType_None,
        EPUsageType_Data,
        1, // EP Dir = IN
        0, // Unset (internal)
        0, // Unset (internal)
        0, // Unset (internal)
        0, // Unset (Internal)
        0, // Interface Num 0
        0, // bInterval Unset
        (int (*)(streaming_chanend, char[], int, int, int))&android_rx // function called on data coming RX'd in response for an IN
    },
    {
        EPTransferType_Bulk,
        EPSyncType_None,
        EPUsageType_Data,
        0, // EP Dir = OUT
        0, // Unset (internal)
        0, // Unset (internal)
        0, // Unset (internal)
        0, // Unset (Internal)
        0, // Interface Num 0
        0, // bInterval Unset
        (int (*)(streaming_chanend, char[], int, int, int))&dummyrx // we don't want to do anything with data that has gone OUT
    }
}

int nDeviceInterfaces = IF_DESC_COUNT ;
s_usb_interface deviceInterfaces[IF_DESC_COUNT] =
{
    {
      0, // Unset (internal)
      0, // Unset (Internal)
      0, // Not alternate
      2, // Num EPs in this IF
      EPIFClass_VendorSpecific,
      EPIFSubClass_VendorSpecific,
      0, // IF Protocol (0 for AAP)
      0, // Unset - will indicate descriptor string index
      (int (*)(char[], int))&dummyfn, // Descriptor FnPtr
      (int (*)(streaming_chanend, int, int))&android_ctrl, // Ctrl FnPtr - channel interface for for interface
      (int (*)(streaming_chanend, int))&dummytimeout, // Timeout fnptr
      (int (*)(streaming_chanend))&dummyflush,
      (void (*)(void))&dummyinit,
    }
}
