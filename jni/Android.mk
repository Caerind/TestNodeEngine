LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := sfml-example

LOCAL_SRC_FILES := main.cpp

FILE_LIST := $(wildcard $(LOCAL_PATH)/Application/*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

FILE_LIST := $(wildcard $(LOCAL_PATH)/Utils/*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

FILE_LIST := $(wildcard $(LOCAL_PATH)/Core/*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

FILE_LIST := $(wildcard $(LOCAL_PATH)/SimpleGui/*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES += Isometric.cpp

LOCAL_LDLIBS += -lz

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)
