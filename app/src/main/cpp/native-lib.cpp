#include <jni.h>
#include <string>
#include <curl.h>
#include "Apis.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_consciousapps_cmakecurltest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    const char *response = loginApi();
    return env->NewStringUTF(response);
}


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

const char *loginApi() {

    std::string readBuffer;

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();


    return readBuffer.c_str();
}