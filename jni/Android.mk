LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := rambw
LOCAL_SRC_FILES := rambw.c
LOCAL_LDLIBS	:= -llog

include $(BUILD_SHARED_LIBRARY)
