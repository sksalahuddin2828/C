#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <commdlg.h>

#define MAX_PATH_LENGTH 260

// Function to select a file
void selectFile(char* filePath)
{
    OPENFILENAME ofn;
    char szFile[MAX_PATH_LENGTH] = { 0 };
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrTitle = "Select an audio file";
    ofn.lpstrFilter = "Audio Files\0*.mp3;*.wav;*.ogg\0";
    ofn.nMaxFile = MAX_PATH_LENGTH;
    ofn.lpstrFile = szFile;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        strcpy(filePath, szFile);
    }
    else
    {
        filePath[0] = '\0';
    }
}

// Function to play the selected file
void playMusic(const char* filePath)
{
    PlaySound(filePath, NULL, SND_FILENAME | SND_ASYNC);
}

// Function to stop the music
void stopMusic()
{
    PlaySound(NULL, NULL, SND_PURGE);
}

int main()
{
    char filePath[MAX_PATH_LENGTH];

    selectFile(filePath);
    if (strlen(filePath) > 0)
    {
        playMusic(filePath);
    }

    while (1)
    {
        printf("1. Select a file\n");
        printf("2. Stop music\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        char choice[10];
        fgets(choice, sizeof(choice), stdin);

        if (strcmp(choice, "1\n") == 0)
        {
            selectFile(filePath);
            if (strlen(filePath) > 0)
            {
                playMusic(filePath);
            }
        }
        else if (strcmp(choice, "2\n") == 0)
        {
            stopMusic();
        }
        else if (strcmp(choice, "3\n") == 0)
        {
            break;
        }
    }

    return 0;
}
