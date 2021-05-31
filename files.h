#ifndef FILES_LIBRARY 
#define FILES_LIBRARY 

#include "define.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////

map<int,string> songList;
map<int,string> songArtist;
map<int,string> songTitle;
map<int,string> songDuration;

void tokenize(std::string const &str, const char delim,std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

string getList()
{
    DIR *dir;
    struct dirent *diread;
    if ((dir = opendir("./songs/")) != nullptr)
    {
        string list,filename,extension;
        int fl;
        int index = 1;
        while (((diread = readdir(dir)) != nullptr)&&(index<=9))
        {
            filename = diread->d_name;
            fl = filename.length();
            if (fl >= 3)
                extension = filename.substr(fl - 3);
            if (extension == "mp3")
                list = list + to_string(index++) + " " + filename.substr(0,fl) + "\n";
        }
        return list;
        closedir(dir);
    }
    else
    {
        perror("opendir");
    }
    return "";
}

void toMap(string list)
{
    ifstream fin;
    string line;
    int index;
    string songName;
    fin.open("./songs/list.txt"); // by default open mode = ios::in mode
    while (fin) // Execute a loop until EOF (End of File)
    {
        getline(fin, line);
        if(line.length()>=8)
        {
            index=line[0]-48;
            songName=line.substr(2,line.length()-6);
            songList.insert(pair<int, string>(index, songName));
        }
    }
    map<int, string>::iterator itr;
    for (itr=songList.begin(); itr != songList.end(); itr++) 
    {
        vector<string> songDetails;
        tokenize(itr->second, '-', songDetails);
        songArtist.insert(pair<int, string>(itr->first, songDetails[0] ));
        songTitle.insert(pair<int, string>(itr->first, songDetails[1]));
        vector<string> ms;
        tokenize(songDetails[2], '.', ms);
        songDuration.insert(pair<int, string>(itr->first, ms[0]+":"+ms[1]));
    }
}

void updateList()
{   
    ofstream file;
    file.open ("./songs/list.txt");
    file << getList();
    file.close();
    toMap(getList());
}

string getSongFileName(int songIndex)
{
    return songList[songIndex]+".mp3";
}

int getNumberOfSongs()
{
    return songList.size();
}

string getSongArtist(int songIndex)
{
    return songArtist[songIndex];
}
string getSongTitle(int songIndex)
{
    return songTitle[songIndex];
}
string getSongDuration(int songIndex)
{
    return songDuration[songIndex];
}

void errorSequence(int currentSongIndex)
{
    clearLineY(yZero+3) horizontalBlank
    clearLineY(yZero+5 ) xMargin cout<<"*                   Error In File                  *";
    clearLineY(yZero+6) track1 cout<<currentSongIndex; track2 
    clearLineY(yZero+7) xMargin cout<<"*                 Playing Next Song                *";
    clearLineY(yZero+13) horizontalBlank
    clearLineY(yZero+11)  xMargin cout<<"*                    .                             *"; Sleep(1000) ; 
    clearLineY(yZero+11)  xMargin cout<<"*                    .  .                          *"; Sleep(1000) ;
    clearLineY(yZero+11)  xMargin cout<<"*                    .  .  .                       *"; Sleep(1000) ;
    clearLineY(yZero+11)  xMargin cout<<"*                    .  .  .  .                    *"; Sleep(1000) ;
}

void displaySongListShowList()
{
    for(int x=1;x<=getNumberOfSongs();x++)
    {
        string st = getSongTitle(x); 
        if(st.length()>18) {st=st.substr(0,16)+"..";}
        else { int d=18-st.length();  for(int y=d;y>=1;y--){st=st+" ";}}

        string sa = getSongArtist(x); 
        if(sa.length()>11) {sa=sa.substr(0,9)+"..";}
        else { int d=11-sa.length();  for(int y=d;y>=1;y--){sa=sa+" ";}}

        clearLineY(yZero+(4+x)) xMargin cout<<"*   "<<x<<"    "<<st<<"  "<<sa<<"   "<<getSongDuration(x)<<"    *\n";
    }

}

////////////////////////////////////////////////////////////////////////////////////////////
#endif
