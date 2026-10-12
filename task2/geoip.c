#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct Buffer {
    char *data;
    size_t size;
};

static size_t write_cb(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct Buffer *buf = (struct Buffer *)userp;
    char *ptr = realloc(buf->data, buf->size + realsize + 1);
    if (!ptr) return 0;
    buf->data = ptr;
    memcpy(&(buf->data[buf->size]), contents, realsize);
    buf->size += realsize;
    buf->data[buf->size] = 0;
    return realsize;
}

int main(void) {
    const char *api_key = getenv("GEOAPIFY_API_KEY");
    if (api_key == NULL || api_key[0] == '\0') {
        fprintf(stderr, "Set GEOAPIFY_API_KEY environment variable\n");
        return 1;
    }
    char url[256];
    snprintf(url, sizeof(url),
             "https://api.geoapify.com/v1/ipinfo?apiKey=%s", api_key);

    struct Buffer buf = { .data = malloc(1), .size = 0 };

    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buf);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-arm-router/1.0");
        curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/ssl/certs/ca-certificates.crt");

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Curl error: %s\n", curl_easy_strerror(res));
        } else {
            printf("Location detected using Geoapify:\n%s\n", buf.data);
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    free(buf.data);
    return 0;
}
