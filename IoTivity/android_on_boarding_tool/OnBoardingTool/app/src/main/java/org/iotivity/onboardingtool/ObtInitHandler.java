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

import android.util.Log;

import org.iotivity.OCMainInitHandler;
import org.iotivity.oc.OcDevice;
import org.iotivity.oc.OcPlatform;

public class ObtInitHandler implements OCMainInitHandler {

    private static final String TAG = ObtInitHandler.class.getSimpleName();

    private OnBoardingActivity activity;
    private OcPlatform obtPlatform;

    public ObtInitHandler(OnBoardingActivity activity, OcPlatform obtPlatform) {
        this.activity = activity;
        this.obtPlatform = obtPlatform;
    }

    @Override
    public int initialize() {
        Log.d(TAG, "inside ObtInitHandler.initialize()");
        int ret = obtPlatform.platformInit("OCF");
        if (ret >= 0) {
            OcDevice device = new OcDevice("/oic/d", "oic.d.dots", "OBT", "ocf.2.0.5", "ocf.res.1.0.0,ocf.sh.1.0.0");
            ret |= obtPlatform.addDevice(device);
            // Note: device must be added to platform before additional resource types can be added
            device.bindResourceType("oic.d.ams");
            device.bindResourceType("oic.d.cms");
        }

        return ret;
    }

    @Override
    public void registerResources() {
        Log.d(TAG, "inside ObtInitHandler.registerResources()");
    }

    @Override
    public void requestEntry() {
        Log.d(TAG, "inside ObtInitHandler.requestEntry()");
    }
}
