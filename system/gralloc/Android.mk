ifneq (false,$(BUILD_EMULATOR_OPENGL_DRIVER))

LOCAL_PATH := $(call my-dir)

define gralloc_recipe
$$(call emugl-begin-shared-library,gralloc.$(1))
$$(call emugl-import,libGLESv1_enc libOpenglSystemCommon)
$$(call emugl-set-shared-library-subpath,hw)

LOCAL_CFLAGS += -DLOG_TAG=\"gralloc_$(1)\"
LOCAL_CFLAGS += -Wno-missing-field-initializers

LOCAL_SRC_FILES := gralloc.cpp

# Need to access the special OPENGL TLS Slot
LOCAL_C_INCLUDES += bionic/libc/private
LOCAL_SHARED_LIBRARIES += libdl
ifdef USE_PREBUILT_LIBS
LOCAL_C_INCLUDES += \
    $(REPO_ROOT_DIR)/CloudDemo/InstructionEngine/Libs/Cloud/InstructionEngine \
    $(REPO_ROOT_DIR)/CloudDemo/InstructionEngine/Libs/libs/Common
else ifdef USE_PREBUILT_LIBS_KGPU
LOCAL_C_INCLUDES += \
    $(REPO_ROOT_DIR)/VMI_Cloud/3rd_groupware/instruction_engine/libs/Cloud/InstructionEngine \
    $(REPO_ROOT_DIR)/VMI_Cloud/3rd_groupware/instruction_engine/libs/libs/Common
else
LOCAL_C_INCLUDES += \
    $(REPO_ROOT_DIR)/Cloud/InstructionEngine \
    $(REPO_ROOT_DIR)/libs/Common
endif

LOCAL_SHARED_LIBRARIES += \
    libInstructionEngine

$$(call emugl-end-module)
endef  # define gralloc_recipe

$(eval $(call gralloc_recipe,goldfish))
$(eval $(call gralloc_recipe,ranchu))
ifeq ($(TARGET_BOARD_PLATFORM),brilloemulator)
$(eval $(call gralloc_recipe,$(TARGET_BOARD_PLATFORM)))
endif  # defined(BRILLO)

endif # BUILD_EMULATOR_OPENGL_DRIVER != false
