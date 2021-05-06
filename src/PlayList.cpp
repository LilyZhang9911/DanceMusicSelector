#include "PlayList.h"
#include <string.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <algorithm>
#include <ctime>

#define FILENAME_SIZE 40

using namespace std;

PlayList::PlayList()
{
    string directory;
    ifstream path ("audio_path.txt");

    getline(path, dir);
    get_play_list();
    shuffle_play_list();
    cd = 10;
}

void PlayList::get_play_list() {
    ifstream playlist;
    playlist.open(dir + "PlayList.txt");
    string line = "";
    int cutoff = 0;
    count = 0;
    // every line in the file is specified by "num name"
    // save all songs in playList
    while (getline(playlist, line)) {
        cutoff = 0;
        while (line[cutoff] != ' ') {
            cutoff++;
        }
        line = line.substr(cutoff+1);
        playList.push_back(line);
        count++;
    }
    playlist.close();
    // create curPlayList for shuffling
    for (int i = 0; i < count; i++) {
        curPlayList.push_back(i);
    }
}

static int myrandom (int i) {
    srand(time(NULL));
    return std::rand()%i;
}

void PlayList::shuffle_play_list(){
    random_shuffle(curPlayList.begin(), curPlayList.end(), myrandom);
}

void PlayList::print_cur_play_list() {
    system("CLS");
    cout << "Current Play List" << endl;
    cout << count << " songs" << endl;
    cout << "-----------------------------"  << endl;
    for (int i = 0; i < count; i++) {
        int cur = curPlayList[i];
        cout << playList[cur] << endl;
    }
    cout << endl << endl;
}

void PlayList::play_play_list(){
    for (int i = 0; i < count; i++) {
        int cur = curPlayList[i];
        play_song(cur);
        // no countdown for last one
        if (i < count-1) {
            countdown();
        }
    }
}

void PlayList::play_song(int num){
    string s_audio_command = "open \"" + dir + to_string(num) + ".mp3\" type mpegvideo alias mp3";
    // convert type
    char audio_command[FILENAME_SIZE];
    strcpy(audio_command, s_audio_command.c_str());

    //play music
    mciSendString(audio_command, NULL, 0, NULL);
    mciSendString("play mp3 wait", NULL, 0, NULL);
    mciSendString("close mp3", NULL, 0, NULL);
}

void PlayList::print_play_list() {
    system("CLS");
    cout << "Play List" << endl;
    cout << count << " songs" << endl;
    cout << "-----------------------------"  << endl;
    for (int i = 0; i < count; i++) {
        cout << i << " " << playList[i] << endl;
    }
    cout << endl << endl;
}

void PlayList::menu() {
    cout << "Play List Menu" << endl;
    cout << "-----------------------------" << endl;
    cout << "0 Shuffle and Show Current Play List" << endl;
    cout << "1 Play Current Play List" << endl;
    cout << "2 View Imported Play List" << endl;
    cout << "3 Show Current Song Path" << endl;
    cout << "4 Update Song Path" << endl;
    cout << "5 Reimport Play List" << endl;
    cout << "6 Modify Countdown - current: " << cd << " seconds" << endl;
    cout << "q quit" << endl;
}

void PlayList::countdown (){
    int t_start = clock();
    int t_cur = clock();
    while ((t_cur - t_start)/1000 < cd) {
        t_cur = clock();
    }
}

bool PlayList::process_cmd(char cmd) {
    string new_path;
    switch(cmd) {
        case '0':
            shuffle_play_list();
            print_cur_play_list();
            menu();
            break;
        case '1':
            play_play_list();
            break;
        case '2':
            print_play_list();
            menu();
            break;
        case '3':
            cout << dir << endl;
            break;
        case '4':
            cout << "Please enter new file path: ";
            cin >> new_path;
            modify_file_path(new_path);
            cout << "Path updated..." << endl;
            break;
        case '5':
            get_play_list();
            cout << "Play list updated..." << endl;
        case '6':
            break;
        case 'q':
            cout << "bye!" << endl;
            return false;
        default:
            cout << "invalid input" << endl;
            break;
    }
    return true;
}

void PlayList::modify_file_path (string s) {
    ofstream path;
    path.open("audio_path.txt");
    path << s;
    path << "/";
    path.close();
    // modify dir
    dir = s + "/";
}
