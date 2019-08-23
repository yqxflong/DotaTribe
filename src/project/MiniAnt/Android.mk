LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := miniant_static
APP_STL := gnustl_static
LOCAL_MODULE_FILENAME := miniant
LOCAL_CPPFLAGS += -fexceptions

LOCAL_SRC_FILES := lib/$(TARGET_ARCH_ABI)/miniant.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/


include $(PREBUILT_STATIC_LIBRARY)
