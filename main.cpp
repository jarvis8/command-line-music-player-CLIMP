#include "define.h"
#include "files.h"

class run
{
    private:
    
    bool paused=false;
    char input;
    string currentSongFileName;
    int currentSongIndex;
    int titleArtistDisplayLength;
    bool error;

    void border()
    {
        clear
        updateList();
        hideCursor

        horizontalFill

        welcomeExitUnselected

        horizontalFill
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        horizontalBlank
        instructionBox
        selectExitWelcome();
    }

    void selectExitWelcome()
    {  
        welcomeExitSelected

        shuffleUnselected

        showListUnselected

        input=_getch();
        if(input==SPACE){clear;exit(0);}
        if(input==DOWN){  selectShuffleWelcome();}
        else{selectExitWelcome();}
    }

    void selectShuffleWelcome()
    {        
        welcomeExitUnselected

        shuffleSelected

        showListUnselected

        input=_getch();
        if(input==SPACE)
        {
            clearLineY(yZero+6) horizontalBlank
            clearLineY(yZero+10) horizontalBlank
            srand(time(0));
            currentSongIndex=(rand()%getNumberOfSongs());
            if(currentSongIndex==0){currentSongIndex=1;}
            playingSongAndShowingDetails();
            selectBackPlaying();
        }
        if(input==UP){ selectExitWelcome();}
        if(input==DOWN){  selectShowListWelcome();}
        else{selectShuffleWelcome();}
    }

    void selectShowListWelcome() 
    {
        shuffleUnselected

        showListSelected

        input=_getch();
        if(input==SPACE) 
        {
            updateList();
            clearLineY(yZero+6) horizontalBlank
            clearLineY(yZero+10) horizontalBlank

            selectBackShowList();
        } 
        if(input==UP){ selectShuffleWelcome();}
        else{ selectShowListWelcome();}
    }

    void selectBackShowList()
    {
        PlayingBackSelected

        selectSongUnselected

        heading

        displaySongListShowList();

        input=_getch();
        if(input==SPACE) 
        {
            for(int x=3;x<=13;x++) { clearLineY(yZero+x) horizontalBlank }
            selectExitWelcome();
        } 
        if(input==RIGHT){ selectExitShowList();}
        if(input==DOWN){ selectSongShowList();}
        else{ selectBackShowList();}
    }

    void selectExitShowList()
    {
        PlayingExitSelected

        selectSongUnselected

        input=_getch();
        if(input==SPACE) { clear;exit(0);} 
        if(input==LEFT){ selectBackShowList();}
        if(input==DOWN){ selectSongShowList();}
        else{ selectExitShowList();}
    } 

    void selectSongShowList()
    {
        PlayingBackAndExitUnselected

        selectSongSelected

        input=_getch();
        if(input==SPACE){playSelectedSongShowList();} 
        if(input==LEFT){ selectBackShowList();}
        if(input==UP){ selectBackShowList();}
        if(input==RIGHT){ selectExitShowList();}
        else{ selectSongShowList();}
    }

    void playSelectedSongShowList()
    {
        fflush(stdin);
        int num;
        clearLineY(yZero+3) xMargin cout<<"*   Press Song Track Number Key [1-"; cout<<getNumberOfSongs()<<"] or 'esc'     *\n";
        num=_getch();
        if(num==ESC) {selectSongShowList();}
        else if(num<(1+48)||num>(getNumberOfSongs()+48)) { playSelectedSongShowList(); }
        else
        {
            currentSongIndex=(num-48);
            for(int x=3;x<=13;x++) { clearLineY(yZero+x) horizontalBlank }
            playingSongAndShowingDetails();
            selectBackPlaying();
        }
    }

    void playingSongAndShowingDetails()
    {
        currentSongFileName=getSongFileName(currentSongIndex);
        playSong(currentSongFileName,"play");
        paused=false;
        int temp=getSongTitle(currentSongIndex).length()+4+getSongArtist(currentSongIndex).length();
        titleArtistDisplayLength = int( ((pixelWidth-2)-(temp)) / 2 );
        int t=titleArtistDisplayLength;
        if(  ((2*t)+temp)==(pixelWidth-2)) {clearLineY(yZero+5) xMargin cout<<"*"; for(int x=t;x>=1;x--){cout<<" ";} cout<<""<<getSongTitle(currentSongIndex)<<" by "<<getSongArtist(currentSongIndex)<<""; for(int x=t;x>=3;x--){cout<<" ";} cout<<"*\n";}
        else{clearLineY(yZero+5) xMargin cout<<"*"; for(int x=t;x>=1;x--){cout<<" ";} cout<<""<<getSongTitle(currentSongIndex)<<" by "<<getSongArtist(currentSongIndex)<<""; for(int x=t;x>=2;x--){cout<<" ";} cout<<"*\n";}

        track1 cout<<currentSongIndex; track2

        duration1 cout<<getSongDuration(currentSongIndex); duration2
    }

    void selectBackPlaying()
    {
        PlayingBackSelected

        nowPlaying 

        if(!paused) {pauseUnselected}
        if(paused) {playUnselected}

        replayUnselected

        prevAndNextUnselected

        input=_getch();
        if(input==SPACE)
        { 
            clearLineY(yZero+3) horizontalBlank  
            clearLineY(yZero+5) horizontalBlank
            clearLineY(yZero+7) horizontalBlank
            clearLineY(yZero+9) horizontalBlank
            clearLineY(yZero+11) horizontalBlank 
            clearLineY(yZero+13) horizontalBlank 
            if(error==false) { playSong(currentSongFileName,"close");}

            selectExitWelcome();
        }
        if(input==RIGHT){ selectExitPlaying();}
        if(input==DOWN){ selectPausePlayPlaying();}
        else{selectBackPlaying();}
    }

    void selectExitPlaying()
    {
        PlayingExitSelected

        if(!paused) { pauseUnselected}
        if(paused) { playUnselected}

        input=_getch();
        if(input==SPACE){clear;playSong(currentSongFileName,"close");exit(0);}
        if(input==LEFT){ ; selectBackPlaying();}
        if(input==DOWN){ ; selectPausePlayPlaying();}
        else{ selectExitPlaying();}
    }

    void selectPausePlayPlaying()
    {
        PlayingBackAndExitUnselected
        
        if(!paused) { pauseSelected}
        if(paused)  { playSelected}

        replayUnselected

        input=_getch();
        if(input==SPACE)
        {
            if(!paused) 
            {
                playSong(currentSongFileName,"pause");
                paused=true; selectPausePlayPlaying();
            }
            else 
            {
                playSong(currentSongFileName,"play");
                paused=false; selectPausePlayPlaying();
            }
        }
        if(input==UP){selectBackPlaying();}
        if(input==DOWN){ selectReplayPlaying();}
        else{ selectPausePlayPlaying();}
    }

    void selectReplayPlaying()
    { 
        if(!paused) { pauseUnselected}
        if(paused)  { playUnselected}

        replaySelected

        prevAndNextUnselected
        
        input=_getch();
        if(input==SPACE)
        {
            playSong(currentSongFileName,"close"); 
            playSong(currentSongFileName,"play");
            paused=false;
        }
        if(input==UP){selectPausePlayPlaying();}
        if(input==DOWN){ selectNextPlaying();}
        if(input==RIGHT){ selectNextPlaying();}
        if(input==LEFT){ selectPreviousPlaying();}
        else{ selectReplayPlaying();}
    }

    void selectNextPlaying()
    {
        PlayingBackAndExitUnselected

        if(!paused) { pauseUnselected}
        if(paused)  { playUnselected}

        replayUnselected

        nextSelected

        input=_getch();
        if(input==SPACE){ playNextSong();}
        if(input==UP){ selectReplayPlaying();}
        if(input==LEFT){ selectPreviousPlaying();}
        else{ selectNextPlaying();}
    }

    void selectPreviousPlaying()
    {
        if(!paused) { pauseUnselected}
        if(paused)  { playUnselected}

        replayUnselected

        prevSelected

        input=_getch();
        if(input==SPACE){ playPreviousSong();}
        if(input==UP){selectReplayPlaying();}                    
        if(input==RIGHT){ selectNextPlaying();}     
        else{ selectPreviousPlaying();}   
    }

    void playSong(string songName,string command)
    {
        command=command+" ./songs/"+songName;
        const char *cmd = &command[0];
        MCIERROR f=mciSendStringA(cmd, NULL, 0, NULL);
        if(f!=0)
        {
            error=true;
            errorSequence(currentSongIndex);
            playNextSong();
        }
        else{error=false;}
    }

    void playNextSong()
    {
        nowPlaying 

        if(error==false){playSong(currentSongFileName,"close");}
        currentSongIndex=currentSongIndex+1;
        if(currentSongIndex>getNumberOfSongs()) {currentSongIndex=1;}

        playingSongAndShowingDetails();

        paused=false;
        selectNextPlaying();
    }

    void playPreviousSong()
    {
        playSong(currentSongFileName,"close");
        currentSongIndex=currentSongIndex-1;
        if(currentSongIndex<1) {currentSongIndex=getNumberOfSongs();}

        playingSongAndShowingDetails();
        
        paused=false;
        selectPreviousPlaying();
    }

    public:
    run() { border();}
};

int main(void)
{
    run MusicPlayer;
    return 0;
}
