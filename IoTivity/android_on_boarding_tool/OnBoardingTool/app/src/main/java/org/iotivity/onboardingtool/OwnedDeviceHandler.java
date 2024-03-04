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

import org.iotivity.OCEndpoint;
import org.iotivity.OCObtDiscoveryHandler;
import org.iotivity.OCQos;
import org.iotivity.OCUuid;
import org.iotivity.OCUuidUtil;
import org.iotivity.oc.OcUtils;

public class OwnedDeviceHandler implements OCObtDiscoveryHandler {

    private static final String TAG = OwnedDeviceHandler.class.getSimpleName();

    private OnBoardingActivity activity;

    public OwnedDeviceHandler(OnBoardingActivity activity) {
        this.activity = activity;
    }

    @Override
    public void handler(OCUuid uuid, OCEndpoint endpoints) {
        OCEndpoint ep = endpoints;
        String deviceId = OCUuidUtil.uuidToString(uuid);
        Log.d(TAG, "discovered owned device: " + deviceId + " at:");
        while (endpoints != null) {
            String endpointStr = OcUtils.endpointToString(endpoints);
            Log.d(TAG, endpointStr);
            endpoints = endpoints.getNext();
        }

        OcUtils.doGet("/oic/d", ep, null, new GetDeviceNameHandler(activity, true), OCQos.HIGH_QOS);
    }
}
