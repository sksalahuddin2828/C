#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <stdbool.h>

void speak(const char* text)
{
    char command[500];
    snprintf(command, sizeof(command), "PowerShell -Command \"Add-Type -TypeDefinition 'using System.Speech.Synthesis; class T { static void M() { using (var synth = new SpeechSynthesizer()) { synth.Speak(\\\"%s\\\"); }}}'; [T]::M();\"", text);
    system(command);
}

void clockTime()
{
    time_t rawTime;
    struct tm* timeInfo;
    char buffer[80];
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(buffer, sizeof(buffer), "%I:%M %p", timeInfo);

    int hour = timeInfo->tm_hour;

    if (hour >= 0 && hour < 12)
        speak("शुभ प्रभात");
    else if (hour >= 12 && hour < 18)
        speak("अभी दोपहर");
    else if (hour >= 18 && hour < 20)
        speak("अभी शाम");
    else
        speak("शुभ रात्रि");
}

void openWebsite(const char* url)
{
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void getIpAddress()
{
    HINTERNET hInternet;
    HINTERNET hConnect;
    DWORD bytesRead;
    char buffer[4096];
    DWORD bufferSize = sizeof(buffer);

    hInternet = InternetOpen("IPChecker", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet != NULL)
    {
        hConnect = InternetOpenUrl(hInternet, "https://api.ipify.org", NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (hConnect != NULL)
        {
            InternetReadFile(hConnect, buffer, bufferSize, &bytesRead);
            buffer[bytesRead] = '\0';
            printf("Your IP address is: %s\n", buffer);
            speak(buffer);
            InternetCloseHandle(hConnect);
        }
        else
        {
            printf("Failed to connect to IP API.\n");
            speak("अपने इंटरनेट प्रोटोकॉल (आईपी) पते की जाँच करने में विफल रहा।");
        }

        InternetCloseHandle(hInternet);
    }
    else
    {
        printf("Failed to open internet connection.\n");
        speak("इंटरनेट कनेक्शन खोलने में विफल रहा।");
    }
}

void getDateAndTime()
{
    time_t rawTime;
    struct tm* timeInfo;
    char buffer[80];
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M %p", timeInfo);

    printf("Today's date and time is: %s\n", buffer);
    speak(buffer);
}

void handleCommand(const char* command)
{
    if (strstr(command, "time") != NULL || strstr(command, "date") != NULL)
   
    {
        getDateAndTime();
    }
    else if (strstr(command, "ip address") != NULL)
    {
        getIpAddress();
    }
    else if (strstr(command, "youtube") != NULL)
    {
        openWebsite("https://www.youtube.com/");
    }
    else if (strstr(command, "google") != NULL)
    {
        openWebsite("https://www.google.com/");
    }
    else if (strstr(command, "wikipedia") != NULL)
    {
        openWebsite("https://wikipedia.org/");
    }
    else if (strstr(command, "who made you") != NULL || strstr(command, "creator") != NULL)
    {
        printf("Full Name: Sk. Salahuddin,\nAddress: House/Holding No. 173,\nVillage/Road: Maheshwar Pasha Kalibari,\nPost Office: KUET, \nPostal Code: 9203,\nPolice Station: Daulatpur,\nDistrict: Khulna, \nCountry: Bangladesh, \nMobile No. +8801767902828\nEmail: sksalahuddin2828@gmail.com\n");
        speak("नाम: शेख सलाहुद्दीन ने मुझे बनाया। वह जिला स्तर (12 जिला) परियोजना में आईटी/हाई-टेक पार्क की स्थापना का छात्र है। बांग्लादेश हाई-टेक पार्क अथॉरिटी। आईसीटी मंत्रालय, आईसीटी टावर, अगरगांव, ढाका। उनके कोर्स का नाम है: पायथन प्रोग्रामिंग का परिचय। उन्होंने इसे सिटी आईटी पार्क, खलीशपुर, खुलना से पूरा किया। उसका विवरण स्क्रीन पर छपा हुआ है। चलिए मैं आपको उसका गिठूब अकाउंट पर लेकर जा रहा हूं, ताकि आप उसको पहचान सके।");
        openWebsite("https://github.com/sksalahuddin2828");
    }
    else if (strstr(command, "close") != NULL || strstr(command, "exit") != NULL || strstr(command, "good bye") != NULL || strstr(command, "ok bye") != NULL || strstr(command, "turn off") != NULL || strstr(command, "shut down") != NULL)
    {
        speak("अपना ध्यान रखना, बाद में मिलते हैं! धन्यवाद");
        break;

    else if (strstr(command, "close") != NULL || strstr(command, "exit") != NULL || strstr(command, "good bye") != NULL || strstr(command, "ok bye") != NULL || strstr(command, "turn off") != NULL || strstr(command, "shut down") != NULL)
    {
        speak("अपना ध्यान रखना, बाद में मिलते हैं! धन्यवाद");
        printf("Stopping Program\n");
        exit(0);
    }
    else
    {
        speak("में आपकी आवाज समझ नहीं पा रहा हूं। कृपया फिर से बोलिए");
        printf("Unrecognized Voice, Say that again please.\n");
    }
}

int main()
{
    clockTime();
    speak("हैलो मेरा नाम शेख सलाहुद्दीन है, बताइये में आपकी क्या मदद कर सकता हूं");
    
    while (1)
    {
        printf("Listening...\n");
        
        char command[500];
        printf("Enter your command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        handleCommand(command);
    }
    
    return 0;
}
