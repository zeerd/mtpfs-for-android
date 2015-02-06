
LOCAL_PATH := $(call my-dir)

#=========================================================
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	libusb/core.c
	
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/libusb \
	external/libusb_aah/libusb 

    
LOCAL_MODULE := libusb-compat
LOCAL_SHARED_LIBRARIES := libusb libc libcutils
include $(BUILD_SHARED_LIBRARY)
