# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This makefile builds both for host and target, and so all the
# common definitions are factored out into a separate file to
# minimize duplication between the build rules.

LOCAL_PATH := $(call my-dir)

#================================================
include $(CLEAR_VARS)

LOCAL_SRC_FILES := origin/mtpfs.c glib-lite.c

LOCAL_CFLAGS += \
	-DHAVE_CONFIG_H \
	-D_FILE_OFFSET_BITS=64 \
	-DFUSE_USE_VERSION=25 \
	-Wno-missing-field-initializers \
	-Wno-error=return-type \
	-Wno-sign-compare
 
LOCAL_LDFLAGS += 

LOCAL_C_INCLUDES :=  \
	$(TOP)/system/core/include \
	$(TOP)/external/libusb-compat/libusb \
	$(LOCAL_PATH)/origin \
    $(LOCAL_PATH)/../libmtp/origin/src \
    $(LOCAL_PATH)/../libfuse/origin/include \
    $(LOCAL_PATH)/../libfuse/androidglue/include

LOCAL_STATIC_LIBRARIES := 
LOCAL_SHARED_LIBRARIES := libfuse-origin libcutils libmtp-origin

LOCAL_MODULE:= mtpfs
include $(BUILD_EXECUTABLE)
