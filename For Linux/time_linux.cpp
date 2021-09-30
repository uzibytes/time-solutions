/*Time Solution Project by UziByte (Ujjwal Raj)*/
/*This code is designed only for mac/linux users*/
//Begin of Code

#include <iostream>
#include <stdlib.h>
#include <string>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#define Linux
#include "conioLinux.h" /* Header for using getch() on Linux/Mac */
using namespace std;

#include <sys/ioctl.h>
#include <termios.h>
bool kbhit() // Source: https://www.flipcode.com/archives/_kbhit_for_Linux.shtml
{            // To detect keyboard press for Linux
    termios term;
    tcgetattr(0, &term);
    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    tcsetattr(0, TCSANOW, &term);
    return byteswaiting > 0;
}

void liveClock()
{
restart_clock:
    int sec_prev = 0;
    cout << "\033[2J\033[1;1H";     //Clears the Screen
    cout << "\n\nPress any key to start the Live Clock : ";
    getch();
    fflush(stdin);
    while (!kbhit())    //Runs the code till keyboard press is detected
    {
        int seconds, minutes, hours;
        string mer;
        time_t total_seconds = time(0);     //Detects the system time
        struct tm *ct = localtime(&total_seconds);
        seconds = ct->tm_sec;
        minutes = ct->tm_min;
        hours = ct->tm_hour;
        if (hours >= 12)
            mer = "PM";
        else
            mer = "AM";
        if(hours==0)
            hours+=12;
        hours = hours > 12 ? hours - 12 : hours;
        if (seconds == sec_prev + 1 || (sec_prev == 59 && seconds == 0))
        {
            cout << "\033[2J\033[1;1H";
            cout << "\n\x1b[32;1m"  //adds colour and text formating
                 << (hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << " " << mer << "\n";
            cout << "\x1b[0mPress any key to end clock\n";
        }
        sec_prev = seconds;
    }
    getch();
    cout << "\033[2J\033[1;1H";
    char key;
    cout << "\n Press '\x1b[33;1m1\x1b[0m' to restart the clock : \n";
    cout << " Press any key to return to main menu : \n";
    key = getch();
    if (key == '1')
        goto restart_clock;
}

void timer()
{
reset_timer:
    cout << "\033[2J\033[1;1H";
    int hh, mm, ss;
    char xd;
    cout << "**SET TIMER**\n\n";
    cout << "Enter hours, minutes and seconds as asked below : ";
    cout << "\nHH: \x1b[36;1m";
    cin >> hh;
    if (hh > 5)
    {
        cout << "\x1b[31;1mTimer cannot be set for more than 5 hours\n\x1b[0m";
        cout << "Press any key to reset the Timer : ";
        fflush(stdin);
        xd = getch();
        goto reset_timer;
    }
    cout << "\n\x1b[0mMM: \x1b[36;1m";
    cin >> mm;
    if (mm >= 60)
    {
        cout << "\x1b[31;1mINVALID Minutes, must be less than 60\n\x1b[0m";
        cout << "Press any key to reset the Timer : ";
        fflush(stdin);
        xd = getch();
        goto reset_timer;
    }
    cout << "\n\x1b[0mSS: \x1b[36;1m";
    cin >> ss;
    if (ss >= 60)
    {
        cout << "\x1b[31;1mINVALID Seconds, must be less than 60\n\x1b[0m";
        cout << "Press any key to reset the Timer : ";
        fflush(stdin);
        xd = getch();
        goto reset_timer;
    }
    cout << "\033[2J\033[1;1H";
    while (hh-- >= 0)
    {
        while (mm-- >= 0)
        {
            while (ss-- >= 0)
            {
                cout << "\n\n\t\t\t______________\n\x1b[32;1m"<<setw(26);
                if (hh + 1 < 10 && mm + 1 < 10 && ss + 1 < 10)
                    cout << " 0" << hh + 1 << " : 0" << mm + 1 << " : 0" << ss + 1 << " ";
                else if (hh + 1 < 10 && mm + 1 >= 10 && ss + 1 < 10)
                    cout << " 0" << hh + 1 << " : " << mm + 1 << " : 0" << ss + 1 << " ";
                else if (hh + 1 < 10 && mm + 1 < 10 && ss + 1 >= 10)
                    cout << " 0" << hh + 1 << " : 0" << mm + 1 << " : " << ss + 1 << " ";
                else if (hh + 1 < 10 && mm + 1 >= 10 && ss + 1 >= 10)
                    cout << " 0" << hh + 1 << " : " << mm + 1 << " : " << ss + 1 << " ";
                else
                    cout << " " << hh + 1 << " : " << mm + 1 << " : " << ss + 1 << " ";
                cout << "\x1b[0m\n\t\t\t--------------\n";
                usleep(1000000);   //Sleeps for 1 second
                cout << "\033[2J\033[1;1H";
            }
            ss = 59;    //Reset seconds
        }
        mm = 59;    //Reset minutes
    }
    cout << "\n\n\n\t\t\t\x1b[31;1m**TIMEOUT**\x1b[0m\n";
    cout << "\n\nPress '\x1b[33;1m1\x1b[0m' to restart TIMER : ";
    cout << "\nPress any key to return to main menu : ";
    char key;
    fflush(stdin);
    key = getch();
    if (key == '1')
        goto reset_timer;
}

void stopwatch()
{
reset_stopwatch:
    int m = 0, s = 0, h = 0, x = 0;
    cout << "\033[2J\033[1;1H";
    cout << "\n\t Press any key to start the Stopwatch.\n";
    cout << "\n\t  **STOP-WATCH** \n";
    cout << "\n\t\t  HH : MM : SS";

    cout << "\n\t\t  \x1b[32;1m" << h << " : " << m << " : " << s << "\x1b[0m";
    getch();
    fflush(stdin);
    while (!kbhit())
    {
        usleep(1000000);
        s++;
        if (s > 59)
        {
            m++;
            s = 0;
        }
        if (m > 59)
        {
            h++;
            m = 0;
            s = 0;
        }
        cout << "\033[2J\033[1;1H";
        cout << "\n\t\t - STOP-WATCH\n";
        cout << "\n\t\t Press any key to stop\n\n";
        cout << "\n\t\t HH: MM: SS";
        cout << "\n\t\t \x1b[32;1m" << h << " : " << m << " : " << s << "\x1b[0m";
        cout << "\n";
    }
    getch();
    cout << "\n\t\t Elapsed Time : ";
    cout << "\n\t\t \x1b[33;1m" << h << " : " << m << " : " << s<<"\x1b[0m";
    cout << "\n\nPress '\x1b[33;1m1\x1b[0m' to restart STOPWATCH : ";
    cout << "\nPress any key to return to main menu : ";
    char key;
    fflush(stdin);
    key = getch();
    if (key == '1')
        goto reset_stopwatch;
}

void worldclock()
{
    reset_wc:
    cout << "\033[2J\033[1;1H";
    cout << "\n\n\t\tWelcome to World Time Solutions by \x1b[35;3m<Uzi>\x1b[0m\n";
    cout << "\t\x1b[35;3m----------------------------------------------------------\n\n\n\x1b[0m";
    cout << "Press the \x1b[33;4mindex number\x1b[0m of the given regions/areas to view their Local Time --->\n";
    cout << "\n  \x1b[33;1m01\x1b[0m. Beijing, China";
    cout << "\n  \x1b[33;1m02\x1b[0m. Singapore, Singapore";
    cout << "\n  \x1b[33;1m03\x1b[0m. Tokyo, Japan";
    cout << "\n  \x1b[33;1m04\x1b[0m. Seoul, South Korea";
    cout << "\n  \x1b[33;1m05\x1b[0m. Sydney, Australia";
    cout << "\n  \x1b[33;1m06\x1b[0m. Dubai, U.A.E.";
    cout << "\n  \x1b[33;1m07\x1b[0m. Paris, France";
    cout << "\n  \x1b[33;1m08\x1b[0m. Amsterdam, Netherlands";
    cout << "\n  \x1b[33;1m09\x1b[0m. Berlin, Germany";
    cout << "\n  \x1b[33;1m10\x1b[0m. Zurich, Swizerland";
    cout << "\n  \x1b[33;1m11\x1b[0m. Rome, Italy";
    cout << "\n  \x1b[33;1m12\x1b[0m. London, England";
    cout << "\n  \x1b[33;1m13\x1b[0m. New York, U.S.A.";
    cout << "\n  \x1b[33;1m14\x1b[0m. Los Angeles, U.S.A.";
    cout << "\n  \x1b[33;1m15\x1b[0m. New Delhi, India";
    string cty[16]={"","Beijing, China","Singapore, Singapore","Tokyo, Japan","Seoul, South Korea","Sydney, Australia","Dubai, U.A.E.","Paris, France","Amsterdam, Netherlands","Berlin, Germany","Zurich, Swizerland","Rome, Italy","London, England","New York, U.S.A.","Los Angeles, U.S.A.","New Delhi, India"};
    index:
    cout << "\n\nEnter the Index Number : \x1b[33;1m";
    int c;
    cin>>c;
    // input validation
    while (cin.fail())
    {
        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input
        cout << "\n\n\t\t\x1b[31;1m!! INVALID INDEX NUMBER !!\x1b[0m\n";
        goto index;
    }
    cout<<"\x1b[0m";
    if (c <= 0 || c > 15)
    {
        cout << "\n\n\t\t\x1b[31;1m!! INVALID INDEX NUMBER !!\x1b[0m\n";
        goto index;
    }
    else
    {
        int sec_prev = 0;
        cout << "\033[2J\033[1;1H";
        while (!kbhit())
        {

            int seconds, minutes, hours;
            string mer;
            time_t total_seconds = time(0);
            struct tm *ct = localtime(&total_seconds);
            seconds = ct->tm_sec;
            minutes = ct->tm_min;
            hours = ct->tm_hour;
            if(hours==0)
                hours+=12;
            if (c < 6 && c > 0)
            {
                minutes += 30;
                if (c < 3)
                    hours += 2;
                else if (c > 2 && c < 5)
                    hours += 3;
                else
                    hours += 4;
            }
            else if (c > 5 && c < 15)
            {
                if (minutes >= 30)
                    minutes -= 30;
                else
                {
                    minutes = minutes + 60 - 30;
                    hours -= 1;
                }

                if (c == 6)
                    hours -= 1;
                else if (c > 6 && c < 12)
                    hours -= 3;
                else if (c == 12)
                    hours -= 4;
                else if (c == 13)
                    hours -= 9;
                else
                    hours -= 12;
            }
            if (minutes >= 60)
            {
                minutes -= 60;
                hours += 1;
            }
            if (hours >= 12 && hours <= 23)
                mer = "PM";
            else if (hours<=0)
            {
                hours+=12;
                mer="PM";
            }
            else
                mer = "AM";
            hours = hours > 12 ? hours - 12 : hours;
            hours = hours > 12 ? hours - 12 : hours;
            if (seconds == sec_prev + 1 || (sec_prev == 59 && seconds == 0))
            {
                cout << "\033[2J\033[1;1H";
                cout<<"\n\n\t\x1b[33;4m"<<cty[c];
                cout << "\x1b[0m\n\n\t\t\x1b[32;1m"
                     << (hours < 10 ? "0" : "") << hours << ":" << (minutes < 10 ? "0" : "") << minutes << ":" << (seconds < 10 ? "0" : "") << seconds << " " << mer << "\n\x1b[0m";
                cout << "\n\n\tPress any key to end clock : \n";
            }
            sec_prev = seconds;
        }
    }
    getch();
    cout << "\033[2J\033[1;1H";
    char key;
    cout << "\n Press '\x1b[33;1m1\x1b[0m' to restart the world clock : \n";
    cout << " Press any key to return to main menu : \n";
    fflush(stdin);
    key = getch();
    if (key == '1')
        goto reset_wc;
}

int main()
{
mainmenu:
    cout << "\033[2J\033[1;1H";
    cout << "\n\n\t\t\x1b[35;5m**\x1b[0m Welcome to \x1b[35;3m<Uzi>\x1b[0m Time Management Solutions \x1b[35;5m**\x1b[0m\t\t\t\x1b[34;4m" << __DATE__ << "\x1b[0m\n";
    cout << "\t\x1b[35;3m----------------------------------------------------------------\x1b[0m\n\n\n";
    cout << "Press '\x1b[33;1m1\x1b[0m' to view live Digital Clock\n";
    cout << "Press '\x1b[33;1m2\x1b[0m' to set Timer\n";
    cout << "Press '\x1b[33;1m3\x1b[0m' to use Stopwatch\n";
    cout << "Press '\x1b[33;1m4\x1b[0m' to view World Clock\n\n";
    int x = -1;
    char ch;
    fflush(stdin);
    cout << "Please Enter your Choice : ";
    ch = getch();
    switch (ch)
    {
    case '1':
        liveClock();
        goto mainmenu;
        break;
    case '2':
        timer();
        goto mainmenu;
        break;
    case '3':
        stopwatch();
        goto mainmenu;
        break;
    case '4':
        worldclock();
        goto mainmenu;
        break;
    default:
        cout << "\033[2J\033[1;1H";
        cout << "\n\n\n\t\t\x1b[31;1m!! INVALID CHOICE !!\x1b[0m";
        cout << "\n\nPress any key to return to main menu : ";
        char sd = getch();
        goto mainmenu;
        break;
    }
    return 0;
}

//End of Code
