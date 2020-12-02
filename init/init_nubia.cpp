/*
 * Copyright (C) 2020 Paranoid Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android-base/properties.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

using android::base::GetProperty;

void OverrideProperty(const std::string& name, const std::string& value) {
    size_t valuelen = value.size();

    prop_info* pi = (prop_info*)__system_property_find(name.c_str());
    if (pi != nullptr) {
        __system_property_update(pi, value.c_str(), valuelen);
    } else {
        __system_property_add(name.c_str(), name.size(), value.c_str(), valuelen);
    }
}

void vendor_load_properties() {
    std::string build_type = GetProperty("ro.build.type", "");
    if (build_type == "userdebug") {
        OverrideProperty("ro.adb.secure", "0");
    }
}
