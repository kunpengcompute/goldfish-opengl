LOCAL_PATH := $(call my-dir)

$(call emugl-begin-shared-library,libOpenglSystemCommon)
$(call emugl-import,libGLESv1_enc libGLESv2_enc)

LOCAL_SRC_FILES := \
    FormatConversions.cpp \
    HostConnection.cpp \
    QemuPipeStream.cpp \
    ThreadInfo.cpp

ifdef IS_AT_LEAST_OPD1
LOCAL_HEADER_LIBRARIES += libnativebase_headers

$(call emugl-export,HEADER_LIBRARIES,libnativebase_headers)
endif

ifdef IS_AT_LEAST_OPD1
LOCAL_HEADER_LIBRARIES += libhardware_headers
$(call emugl-export,HEADER_LIBRARIES,libhardware_headers)
endif

LOCAL_C_INCLUDES += \
    $(EMUGL_PATH)/goldfishinclude

LOCAL_SHARED_LIBRARIES += \
    libInstructionEngine \
    libVmiInsCommon \
    libVmiCommonInstr

$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private)

$(call emugl-end-module)
