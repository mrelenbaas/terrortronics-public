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
import android.widget.SimpleAdapter;
import android.widget.Toast;

import org.iotivity.OCCred;
import org.iotivity.OCCredUtil;
import org.iotivity.OCCreds;
import org.iotivity.OCObt;
import org.iotivity.OCObtCredsHandler;
import org.iotivity.OCUuidUtil;

import java.util.ArrayList;
import java.util.HashMap;

public class RetrieveCredentialHandler implements OCObtCredsHandler {

    private static final String TAG = RetrieveCredentialHandler.class.getSimpleName();

    private OnBoardingActivity activity;
    private SimpleAdapter credsAdapter;
    private ArrayList<HashMap<String, String>> credsList;

    public RetrieveCredentialHandler(OnBoardingActivity activity, SimpleAdapter credsAdapter, ArrayList<HashMap<String, String>> credsList) {
        this.activity = activity;
        this.credsAdapter = credsAdapter;
        this.credsList = credsList;
    }

    @Override
    public void handler(OCCreds creds) {
        if (creds != null) {
            CredentialListHelper clh = new CredentialListHelper(credsList);
            clh.buildList(creds);

            activity.runOnUiThread(new Runnable() {
                public void run() {
                    credsAdapter.notifyDataSetChanged();
                }
            });

            /* Free the credential structure */
            OCObt.freeCreds(creds);

        } else {
            final String msg = "No credentials found when retrieving /oic/sec/cred";
            Log.d(TAG, msg);
            activity.runOnUiThread(new Runnable() {
                public void run() {
                    Toast.makeText(activity, msg, Toast.LENGTH_LONG).show();
                }
            });
        }
    }
}
