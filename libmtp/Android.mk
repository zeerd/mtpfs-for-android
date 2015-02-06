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

define my-all-dir-under
$(addprefix $(LOCAL_PATH)/, \
  $(shell cd $(LOCAL_PATH) ; \
          find -L $(1) -name "*" -and -not -name "*.*" -type d) \
 )
endef

# ============================================================
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := \
	external/libusb/libusb \
	external/libusb-compat/libusb \
	external/icu4c/common \
	$(LOCAL_PATH)/../libiconv/include \
	$(LOCAL_PATH)/config \

LOCAL_C_INCLUDES += $(call my-all-dir-under, \
                         origin/src)

LOCAL_SRC_FILES := \
	origin/src/playlist-spl.c \
	origin/src/ptp.c \
	origin/src/unicode.c \
	origin/src/libmtp.c \
	origin/src/libusb-glue.c \
	origin/src/util.c

LOCAL_CFLAGS := \
	-Wno-sign-compare

$(call print-vars, LOCAL_PATH)
$(call print-vars, LOCAL_C_INCLUDES)
$(call print-vars, LOCAL_SRC_FILES)

LOCAL_MODULE := libmtp-origin
LOCAL_SHARED_LIBRARIES := libiconv libusb-compat
                          
include $(BUILD_SHARED_LIBRARY)

