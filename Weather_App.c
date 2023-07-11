// Please note that you need to replace "YOUR_API_KEY" in the code with your actual OpenWeatherMap API key for it to work properly.

#include <stdio.h>
#include <curl/curl.h>
#include <json-c/json.h>

#define API_KEY "YOUR_API_KEY"

struct MemoryStruct {
    char *memory;
    size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main() {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        struct MemoryStruct chunk;
        chunk.memory = malloc(1);
        chunk.size = 0;

        char city[100];
        printf("Enter the city name: ");
        fgets(city, sizeof(city), stdin);
        city[strcspn(city, "\n")] = 0;

        char url[150];
        sprintf(url, "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric", city, API_KEY);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            json_object *json = json_tokener_parse(chunk.memory);
            json_object *main_object, *temp_object, *weather_array, *weather_object, *description_object;

            if (json_object_object_get_ex(json, "main", &main_object) &&
                json_object_object_get_ex(json, "weather", &weather_array) &&
                json_object_array_length(weather_array) > 0 &&
                json_object_object_get_ex(json_object_array_get_idx(weather_array, 0), "description", &description_object) &&
                json_object_object_get_ex(main_object, "temp", &temp_object)) {

                double temp = json_object_get_double(temp_object);
                const char *description = json_object_get_string(description_object);

                printf("Temperature: %.1f °C\n", temp);
                printf("Description: %s\n", description);
            } else {
                printf("City not found\n");
            }

            json_object_put(json);
        }

        curl_easy_cleanup(curl);
        free(chunk.memory);
    }

    curl_global_cleanup();

    return 0;
}
