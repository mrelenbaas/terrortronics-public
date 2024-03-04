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
import android.widget.Toast;

import org.iotivity.OCObtStatusHandler;

public class DeleteCredentialHandler implements OCObtStatusHandler {

    private static final String TAG = DeleteCredentialHandler.class.getSimpleName();

    private OnBoardingActivity activity;

    public DeleteCredentialHandler(OnBoardingActivity activity) {
        this.activity = activity;
    }

    @Override
    public void handler(int status) {
        if (status < 0) {
            final String msg = "Error deleting credential, status = " + status;
            Log.d(TAG, msg);
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    Toast.makeText(activity, msg, Toast.LENGTH_LONG).show();
                }
            });
        }
    }
}
