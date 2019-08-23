LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := DOTATribe_static
LOCAL_MODULE_FILENAME := DOTATribe
LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -w
LOCAL_CPP_EXTENSION += .cc
LOCAL_CPP_EXTENSION += .c
LOCAL_CPP_EXTENSION += .cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../cobra_win
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../cocos2dx
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../cocos2dx/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../cocos2dx/platform
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../cocos2dx/platform/android
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../cocos2dx/kazmath/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../CocosDenshion/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../extensions
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../external
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../external/sqlite3
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../MiniAnt
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../lua

LOCAL_SRC_FILES := source.cpp

LOCAL_WHOLE_STATIC_LIBRARIES := cobra_win_static
LOCAL_WHOLE_STATIC_LIBRARIES += sqlite_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += extensions_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += miniant_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cobra_win)
$(call import-module,cocos2dx)
$(call import-module,extensions)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,external/sqlite3)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,external/libwebsockets/android)
$(call import-module,MiniAnt)
$(call import-module,lua/proj.android)
