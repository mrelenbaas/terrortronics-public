// Copyright 2024 Bradley Elenbaas
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package org.iotivity.onboardingtool;

import org.iotivity.OCUuid;

public class OcfDeviceInfo {

    private OCUuid uuid;
    private String name;

    OcfDeviceInfo(OCUuid uuid, String name) {
        this.uuid = uuid;
        this.name = name;
    }

    public OCUuid getUuid() {
        return uuid;
    }

    public String getName() {
        return name;
    }

    public int hashCode() {
        int result = 17;
        result = 37 * result + uuid.hashCode();
        result = 37 * result + name.hashCode();
        return result;
    }

    public boolean equals(Object obj) {
        OcfDeviceInfo other = (OcfDeviceInfo) obj;
        return (uuid.equals(other.uuid) && name.equals(other.name));
    }
}
