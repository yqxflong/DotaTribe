LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cobra_win_static
APP_STL := gnustl_static
LOCAL_MODULE_FILENAME := cobra_win

LOCAL_SRC_FILES := lib/$(TARGET_ARCH_ABI)/cobra_win.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/


include $(PREBUILT_STATIC_LIBRARY)
