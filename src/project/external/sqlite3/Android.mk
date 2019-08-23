LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sqlite_static
APP_STL := stlprot_static
LOCAL_MODULE_FILENAME := sqlite

LOCAL_SRC_FILES := lib/$(TARGET_ARCH_ABI)/sqlite.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/

include $(PREBUILT_STATIC_LIBRARY)
