#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
using std::string;

class PlayList
{
    public:
        // get playlist using path from audio_path.txt, populate count and playList
        PlayList();
        void menu();
        // returns false if user wants the program to terminate terinate
        bool process_cmd(char cmd);

        void countdown();
    private:
        string dir;
        int count;
        std::vector<string> playList;
        std::vector<int> curPlayList;
        int cd;

        void play_play_list();
        // play the song num.mp3
        void play_song(int num);
        // change current audio directory and path speficied txt file
        void modify_file_path (string s);
        // must have a PlayList.h in music folder
        void get_play_list();

        void shuffle_play_list();
        void print_cur_play_list();
        void print_play_list();
};

#endif // PLAYLIST_H
