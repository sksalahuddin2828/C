#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

#define MAX_BUFFER_SIZE 4096

struct SatelliteData {
    char name[256];
    char tle_line1[256];
    char tle_line2[256];
    double angle;
};

struct SatelliteDbEntry {
    char name[256];
    char country[256];
};

struct MemoryStruct {
    char *memory;
    size_t size;
};

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        printf("Error: Out of memory\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char *SendGetRequest(const char *url) {
    CURL *curl = curl_easy_init();
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Error in SendGetRequest: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            free(chunk.memory);
            return NULL;
        }

        curl_easy_cleanup(curl);
    }

    return chunk.memory;
}

int main() {
    CURLcode init_res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (init_res != CURLE_OK) {
        printf("Error initializing libcurl: %s\n", curl_easy_strerror(init_res));
        return 1;
    }

    // Step 1: Retrieve satellite data from the API
    const char *satelliteDataApiUrl = "API_URL_HERE";
    char *satelliteDataJson = SendGetRequest(satelliteDataApiUrl);
    if (satelliteDataJson == NULL) {
        curl_global_cleanup();
        return 1;
    }

    // Step 2: Parse TLE data using Skyfield
    json_error_t error;
    json_t *root = json_loads(satelliteDataJson, 0, &error);
    free(satelliteDataJson);
    if (!root) {
        printf("Error parsing satellite data JSON: %s (line %d)\n", error.text, error.line);
        curl_global_cleanup();
        return 1;
    }

    json_t *satelliteDataArray = json_object_get(root, "satelliteData");
    if (!json_is_array(satelliteDataArray)) {
        printf("Error: Invalid satellite data format\n");
        json_decref(root);
        curl_global_cleanup();
        return 1;
    }

    size_t satelliteDataCount = json_array_size(satelliteDataArray);
    struct SatelliteData *satelliteData = malloc(satelliteDataCount * sizeof(struct SatelliteData));

    for (size_t i = 0; i < satelliteDataCount; i++) {
        json_t *satelliteObj = json_array_get(satelliteDataArray, i);
        if (!json_is_object(satelliteObj)) {
            printf("Error: Invalid satellite data format\n");
            json_decref(root);
            free(satelliteData);
            curl_global_cleanup();
            return 1;
        }

        json_t *nameObj = json_object_get(satelliteObj, "name");
        json_t *tleLine1Obj = json_object_get(satelliteObj, "tle_line1");
        json_t *tleLine2Obj = json_object_get(satelliteObj, "tle_line2");
        json_t *angleObj = json_object_get(satelliteObj, "angle");

        if (!json_is_string(nameObj) || !json_is_string(tleLine1Obj) || !json_is_string(tleLine2Obj) ||
            !json_is_number(angleObj)) {
            printf("Error: Invalid satellite data format\n");
            json_decref(root);
            free(satelliteData);
            curl_global_cleanup();
            return 1;
        }

        strcpy(satelliteData[i].name, json_string_value(nameObj));
        strcpy(satelliteData[i].tle_line1, json_string_value(tleLine1Obj));
        strcpy(satelliteData[i].tle_line2, json_string_value(tleLine2Obj));
        satelliteData[i].angle = json_number_value(angleObj);
    }

    json_decref(root);

    // Step 3: Visualize satellite orbits in 3D
    // TODO: Implement the visualization in C++
    // Refer to the C++ code provided for this step

    // Step 4: Map satellites to countries using the satellite database API
    const char *satelliteDbApiUrl = "SATELLITE_DB_API_URL_HERE";
    char *satelliteDbJson = SendGetRequest(satelliteDbApiUrl);
    if (satelliteDbJson == NULL) {
        free(satelliteData);
        curl_global_cleanup();
        return 1;
    }

    root = json_loads(satelliteDbJson, 0, &error);
    free(satelliteDbJson);
    if (!root) {
        printf("Error parsing satellite database JSON: %s (line %d)\n", error.text, error.line);
        free(satelliteData);
        curl_global_cleanup();
        return 1;
    }

    json_t *satelliteDbArray = json_object_get(root, "satelliteDb");
    if (!json_is_array(satelliteDbArray)) {
        printf("Error: Invalid satellite database format\n");
        json_decref(root);
        free(satelliteData);
        curl_global_cleanup();
        return 1;
    }

    size_t satelliteDbCount = json_array_size(satelliteDbArray);
    struct SatelliteDbEntry *satelliteDb = malloc(satelliteDbCount * sizeof(struct SatelliteDbEntry));

    for (size_t i = 0; i < satelliteDbCount; i++) {
        json_t *entryObj = json_array_get(satelliteDbArray, i);
        if (!json_is_object(entryObj)) {
            printf("Error: Invalid satellite database format\n");
            json_decref(root);
            free(satelliteData);
            free(satelliteDb);
            curl_global_cleanup();
            return 1;
        }

        json_t *nameObj = json_object_get(entryObj, "name");
        json_t *countryObj = json_object_get(entryObj, "country");

        if (!json_is_string(nameObj) || !json_is_string(countryObj)) {
            printf("Error: Invalid satellite database format\n");
            json_decref(root);
            free(satelliteData);
            free(satelliteDb);
            curl_global_cleanup();
            return 1;
        }

        strcpy(satelliteDb[i].name, json_string_value(nameObj));
        strcpy(satelliteDb[i].country, json_string_value(countryObj));
    }

    json_decref(root);

    // Mapping satellite names to countries
    size_t satelliteDataSize = sizeof(satelliteData) / sizeof(satelliteData[0]);
    struct SatelliteDbEntry *satelliteCountryMap = malloc(satelliteDataSize * sizeof(struct SatelliteDbEntry));

    for (size_t i = 0; i < satelliteDataSize; i++) {
        const char *name = satelliteData[i].name;
        const char *country = "Unknown";

        for (size_t j = 0; j < satelliteDbCount; j++) {
            if (strcmp(satelliteDb[j].name, name) == 0) {
                country = satelliteDb[j].country;
                break;
            }
        }

        strcpy(satelliteCountryMap[i].name, name);
        strcpy(satelliteCountryMap[i].country, country);
    }

    // Printing satellite information
    for (size_t i = 0; i < satelliteDataSize; i++) {
        printf("Satellite Name: %s\n", satelliteData[i].name);
        printf("Orbital Angle: %lf degrees\n", satelliteData[i].angle);
        printf("Country: %s\n\n", satelliteCountryMap[i].country);
    }

    // Cleanup
    free(satelliteData);
    free(satelliteDb);
    free(satelliteCountryMap);
    curl_global_cleanup();

    return 0;
}
