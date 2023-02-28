#include "knight.h"

const int inf = 2e9 + 7;
const int maxN = 200010;

int maxHP = 999;
const int maxLevel = 10;
const int maxRemedy = 99;
const int maxMaidenKiss = 99;
const int maxPhoenixDown = 99;

const int minHP = 0;
const int minLevel = 0;
const int minRemedy = 0;
const int minMaidenKiss = 0;
const int minPhoenixDown = 0;

const int maxPrefixOdd = 110;
int prefixOdd[maxPrefixOdd];

const int maxPrime = 1500, maxFibo = 1500, maxFiboSeq = 30;
bool isPrime[maxPrime], isFibo[maxFibo];
int fibo[maxFiboSeq];

void lowercase(string &s)
{
    for (int i = 0; i < s.length(); ++i)
    {
        if ('A' <= s[i] && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
    }
}

string intToString(int num) {
    string s = "";
    while (num != 0) {
        s.insert(0, 1, (char)((num % 10) + '0'));
        num /= 10;
    }
    return s;
}

void initialSetUp() {
    for (int i = 0; i <= 1100; ++i) {
        isPrime[i] = true;
        isFibo[i] = false;
    }

    int tmp = 99;
    prefixOdd[1] = tmp;
    for (int i = 2; i <= 100; ++i) {
        tmp -= 2;
        prefixOdd[i] = prefixOdd[i - 1] + tmp;
    }

    fibo[0] = fibo[1] = 1;
    for (int i = 2; i <= 20; ++i) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        isFibo[fibo[i]] = true;
    }

    isPrime[1] = false;
    for (int i = 2; i <= 33; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= 1100; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

struct Tiny
{
    bool is_tiny = false;
    int duration = 0;
};

struct Frog
{
    bool is_frog = false;
    int duration = 0;
};

struct Knights
{
    int HP, level, remedy, maidenKiss, phoenixDown;
    int rescue = -1;

    int prevLevel = 1;
    bool Arthur = false, Lancelot = false;
    bool continueable = true;
    
    bool meetAclepius = false, meetMerlin = false;
    Tiny tiny;
    Frog frog;
    void init(string s)
    {
        stringstream info(s);
        info >> HP >> level >> remedy >> maidenKiss >> phoenixDown;
        maxHP = HP;
        if (isPrime[HP]) Lancelot = true;
        if (HP == 999) Arthur = true;
    }

void display()
    {
        cout << "HP=" << HP << ", level=" << level << ", remedy=" << remedy << ", maidenkiss=" << maidenKiss << ", phoenixdown=" << phoenixDown << ", rescue=" << rescue << endl;
    }

void check()
    {
        if (tiny.is_tiny)
        {
            if (remedy)
            {
                tiny.is_tiny = false;
                tiny.duration = 0;
                remedy = max(minRemedy, remedy - 1);
                HP = min(HP * 5, maxHP);
            }
            else
            {
                tiny.duration = max(0, tiny.duration - 1);
                if (tiny.duration == 0)
                {
                    tiny.is_tiny = false;
                    HP = min(HP * 5, maxHP);
                }
            }
        }

        if (frog.is_frog)
        {
            if (maidenKiss)
            {
                frog.is_frog = false;
                frog.duration = 0;
                maidenKiss = max(minMaidenKiss, maidenKiss - 1);
                level = prevLevel;
            }
            else
            {
                frog.duration = max(0, frog.duration - 1);
                if (frog.duration == 0)
                {
                    frog.is_frog = false;
                    level = prevLevel;
                }
            }
        }

        if (HP < 0)
        {
            if (phoenixDown > 0)
            {
                HP = maxHP;
                phoenixDown = max(minPhoenixDown, phoenixDown - 1);
                return;
            }
            rescue = 0;
        }
    }
} knight;

struct Loots
{
    string lootFile[10];
    int num = 0;

    void init(string s)
    {
        string tmp = "";
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == ',')
            {
                lootFile[num++] = tmp;
                tmp = "";
            }
            else tmp += s[i];
        }

        lootFile[num] = tmp;
    }
} loot;

struct Events
{
    int arr[maxN];
    int num = 0;

    void init(string s)
    {
        stringstream ss(s);
        int intInp;
        while (ss >> intInp) arr[++num] = intInp;
    }

    struct List
    {
        struct MushGhost
        {
            int arr[200], transArr[200];
            int n; 

            void init(string file_mush_ghost)
            {
                ifstream fileIn;
                fileIn.open(file_mush_ghost);

                fileIn >> n;

                string s; getline(fileIn, s); getline(fileIn, s);
                stringstream ss(s);

                int i = 0;
                string a[1000];
                while (ss.good())
                {
                    string tmp;
                    getline(ss, tmp, ',');
                    a[i++] = tmp;
                }

                for (int i = 0; i < n; ++i)
                {
                    int tmp;
                    stringstream(a[i]) >> arr[i];
                }

                fileIn.close();
            }

            void transform()
            {
                for (int i = 0; i < n; ++i) transArr[i] = arr[i];
                for (int i = 0; i < n; ++i)
                {
                    if (arr[i] < 0) transArr[i] = -transArr[i];
                    transArr[i] = (17 * transArr[i] + 9) % 257;
                }
            }

            void mushTypeOne(int &minIndex, int &maxIndex)
            {
                int mn = inf, mx = -inf;
                for (int i = 0; i < n; ++i)
                {
                    if (arr[i] <= mn)
                    {
                        mn = arr[i]; minIndex = i;
                    }

                    if (arr[i] >= mx)
                    {
                        mx = arr[i]; maxIndex = i;
                    }
                }
            }

            void mushTypeTwo(int &mtMax, int &mtIndex)
            {
                mtMax = -2, mtIndex = -3;

                int x = 0, y = n - 1;
                while (arr[x] < arr[x + 1]) x++;
                while (arr[y - 1] > arr[y]) y--;

                if (x != y) return; 
                mtMax = arr[x]; mtIndex = x;
            }
                    
            void mushTypeThree(int &minIndex, int &maxIndex)
            {
                int mn = inf, mx = -inf;
                for (int i = 0; i < n; ++i)
                {
                    if (transArr[i] < mn)
                    {
                        mn = transArr[i]; minIndex = i;
                    }

                    if (transArr[i] > mx)
                    {
                        mx = transArr[i]; maxIndex = i;
                    }
                }
            }

            void mushTypeFour(int &mtMax, int &mtIndex)
            {
                int mx = -inf, mxIndex = -1, sMx = -inf, sMxIndex = -1;
                
                for (int i = 0; i < 3; ++i)
                {
                    if (transArr[i] > mx)
                    {
                        mx = transArr[i]; mxIndex = i;
                    }
                }

                for (int i = 0; i < 3; ++i)
                {
                    if (transArr[i] > sMx && transArr[i] != mx)
                    {
                        sMx = transArr[i]; sMxIndex = i;
                    }
                }

                if (sMxIndex == -1) mtMax = -5, mtIndex = -7;
                else mtMax = sMx, mtIndex = sMxIndex;
            }

        } mushGhost;

void princessRescued(Knights &knight)
        {
            knight.rescue = 1;
        }

void meetMonster(Knights &knight, int type, int index)
        {
            int damage[6] = {0, 10, 15, 45, 75, 95};
            int levelO = index > 6 ? (index % 10 > 5 ? index % 10 : 5) : index % 10;

            if (knight.level > levelO || knight.Arthur || knight.Lancelot)
            {
                knight.level = min(maxLevel, knight.level + 1); return;
            }
            if (knight.level == levelO) return;

            knight.HP -= levelO * damage[type];
            knight.check();
        }

        void meetShaman(Knights &knight, int index) 
        {
            if (knight.tiny.is_tiny) return;

            int levelO = index > 6 ? (index % 10 > 5 ? index % 10 : 5) : index % 10;
            if (knight.level > levelO  || knight.Arthur || knight.Lancelot)
            {
                knight.level = min(maxLevel, knight.level + 2); return;
            }
            if (knight.level == levelO) return;

            knight.HP = max(knight.HP / 5, 1);
            knight.tiny.is_tiny = true;
            knight.tiny.duration = 4;
            knight.check();
        }
        
        void meetSirenVajsh(Knights &knight, int index) 
        {
            if (knight.frog.is_frog) return;

            int levelO = index > 6 ? (index % 10 > 5 ? index % 10 : 5) : index % 10;
            if (knight.level > levelO  || knight.Arthur || knight.Lancelot)
            {
                knight.level = min(maxLevel, knight.level + 2); return;
            }
            if (knight.level == levelO) return;

            knight.prevLevel = knight.level;
            knight.level = 1;
            knight.frog.is_frog = true;
            knight.frog.duration = 4;
            knight.check();
        }

        void pickUpItem(Knights &knight, int type)
        {
            if (type == 15) knight.remedy = min(maxRemedy, knight.remedy + 1);
            if (type == 16) knight.maidenKiss = min(maxMaidenKiss, knight.maidenKiss + 1);
            if (type == 17) knight.phoenixDown = min(maxPhoenixDown, knight.phoenixDown + 1);

            knight.check();
        }

        void pickUpMushMario(Knights &knight)
        {
            int addedHP = prefixOdd[((knight.level + knight.phoenixDown) % 5 + 1) * 3] % 100;
            knight.HP = min(maxHP, knight.HP + addedHP);
            knight.HP++;
            while(!isPrime[knight.HP]) knight.HP++;
        }

        void pickUpMushFibo(Knights &knight)
        {
            if (knight.HP == 1) return;
            int i = knight.HP - 1;
            while (!isFibo[i]) i--;
            knight.HP = i;
        }

        void pickUpMushGhost(Knights &knight, string s)
        {   
            int order[2000], n = 0;
            for (int i = 2; i < s.length(); ++i) order[n++] = s[i] - '0';

            mushGhost.init(loot.lootFile[0]);
            mushGhost.transform();

            int x, y;
            for (int i = 0; i < n; ++i)
            {
                if (order[i] == 1) mushGhost.mushTypeOne(x, y);
                if (order[i] == 2) mushGhost.mushTypeTwo(x, y);
                if (order[i] == 3) mushGhost.mushTypeThree(x, y);
                if (order[i] == 4) mushGhost.mushTypeFour(x, y);
                
                knight.HP = min(maxHP, knight.HP - (x + y));
                knight.check();
            }
        }

        void meetAsclepius(Knights &knight)
        {   
            ifstream fileIn;
            fileIn.open(loot.lootFile[1]);

            knight.meetAclepius = true;

            int rows, columns; fileIn >> rows >> columns;

            int table[110][110];
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < columns; ++j) 
                {
                    fileIn >> table[i][j];
                }
            }   

            for (int i = 0; i < rows; ++i)
            {
                int cnt = 0;
                for (int j = 0; j < columns; ++j)
                {
                    int inp = table[i][j];
                    if (!(16 <= inp && inp <= 18)) continue;  
                    pickUpItem(knight, --inp); 
                    if (++cnt == 3) break;
                }
            }

            fileIn.close();
        }

        void meetMerlin(Knights &knight)
        {   
            ifstream fileIn;
            fileIn.open(loot.lootFile[2]);

            knight.meetMerlin = true;

            int n; fileIn >> n;
            string checkStr = "merlin";

            for (int i = 0; i < n; ++i)
            {
                int ok[200];
                for (int i = 0; i < 200; ++i) ok[i] = false;

                string s;
                fileIn >> s;
                lowercase(s); 

                for (int i = 0; i < s.length(); ++i) ok[s[i]] = true;
                if (ok['m'] && ok['e'] && ok['r'] && ok['l'] && ok['i'] && ok['n']) 
                    knight.HP = min(maxHP, knight.HP + 2);
                
                if (s.length() < 6) continue;
                for (int i = 0; i < s.length() - 5; ++i)
                {
                    bool flag = true;
                    for (int j = 0; j < 6; ++j)
                    {
                        if (s[i + j] != checkStr[j]) flag = false;
                    }
                    if (flag) 
                    {
                        knight.HP = min(maxHP, knight.HP + 1);;
                        continue;
                    }
                }
            }

            fileIn.close();
        }

        void meetBowser(Knights &knight)
        {
            if (knight.Arthur || (knight.Lancelot && knight.level >= 8) || (knight.level == 10))
            {
                knight.level = 10; return;
            }
            knight.rescue = 0;
            knight.continueable = 0;
        }

    } eventList;

    void lookUp(Knights &knight, int index)
    {
        string sTmp = intToString(arr[index]);
        if (arr[index] == 0) 
            eventList.princessRescued(knight);
        if (1 <= arr[index] && arr[index] <= 5) 
            eventList.meetMonster(knight, arr[index], index);
        if (arr[index] == 6) 
            eventList.meetShaman(knight, index);
        if (arr[index] == 7) 
            eventList.meetSirenVajsh(knight, index);
        if (15 <= arr[index] && arr[index] <= 17) 
            eventList.pickUpItem(knight, arr[index]);
        if (arr[index] == 11) 
            eventList.pickUpMushMario(knight);
        if (arr[index] == 12) 
            eventList.pickUpMushFibo(knight);
        if (sTmp[0] == '1' && sTmp[1] == '3')
            eventList.pickUpMushGhost(knight, sTmp);
        if (arr[index] == 18 && !knight.meetMerlin) 
            eventList.meetMerlin(knight);
        if (arr[index] == 19 && !knight.meetAclepius) 
            eventList.meetAsclepius(knight);
        if (arr[index] == 99) 
            eventList.meetBowser(knight);
    }
} events;

void dataInput(string file_input, Knights &knight, Events &events)
{
    ifstream fileIn;
    fileIn.open(file_input);

    string firstInpStr, secondInpStr, thirdInpStr;
    getline(fileIn, firstInpStr);
    getline(fileIn, secondInpStr);
    getline(fileIn, thirdInpStr);

    knight.init(firstInpStr);
    events.init(secondInpStr);
    loot.init(thirdInpStr);

    fileIn.close();
}

void adventureToKoopa(string file_input, int &HP, int &level, int &remedy, int &maidenKiss, int &phoenixDown, int &rescue) 
{
    initialSetUp();
    dataInput(file_input, knight, events);
    int index = 0;
    for (int i = 0; i < events.num; i++) 
    {
        events.lookUp(knight, i+1);
        if (i == events.num - 1) {
            if (knight.HP >= 0 && knight.continueable) {
                knight.rescue = 1;
            } else {
                knight.rescue = 0;
            }
        }
        knight.display();

        if (knight.rescue == 1 || knight.HP < 0 || !knight.continueable) {
            break;
        }
    }
}