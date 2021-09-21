#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
using namespace std;

default_random_engine dre;
uniform_int_distribution<> uidName{ 'a','z' };
normal_distribution<> ndScore{ 0.0 ,1.0 };
int playernum = 100'000;

class Player
{
    string id;
    unsigned int breakout;
    unsigned int championsLeague;
public:
    Player()
    {
        // id ����
        for (int j = 0; j < 10; ++j)
            id += uidName(dre);
        // ��������
        double n1 = ndScore(dre);
        n1 += 5;               // 0 ~ 10
        n1 *= 290'588'702.6;
        n1 = clamp(n1, 0., 2'905'887'026.);
        breakout = n1;
        double n2 = ndScore(dre);
        n2 += 5;
        n2 *= 111'267'038.4;
        n2 = clamp(n2, 0., 1'112'670'384.);
        championsLeague = n2;
    }
    Player(string id, unsigned int breakout, unsigned int championsLeague)
        : id{ id }, breakout{ breakout }, championsLeague{ championsLeague }{}

    string GetName() const
    {
        return id;
    }
    unsigned int GetBreakoutScore() const
    {
        return breakout;
    }
    unsigned int GetChampionsLeague() const 
    {
        return championsLeague;
    }
    unsigned int GetBreakoutScore() 
    {
        return breakout;
    }
    unsigned int GetChampionsLeague() 
    {
        return championsLeague;
    }

    void SetBreakoutScore(unsigned int score) 
    {
        breakout = score;
    }
    void SetChampionsLeague(unsigned int score)
    {
        championsLeague = score;
    }
};

bool cmpbreakoutScore(const Player a, const Player b)
{
    return a.GetBreakoutScore() > b.GetBreakoutScore();
}
bool cmpchampionsLeague(const Player& a, const Player& b)
{
    return a.GetChampionsLeague() > b.GetChampionsLeague();
}

int main()
{
    vector<Player> players;
    players.reserve(playernum);
    {
        // "PlayerList.txt" ������ ����.
        ifstream in("PlayerList.txt");
        // ������ ���ٸ� ���� �����Ѵ�.
        if (!in.is_open())
            players.resize(playernum);
        else {
            // ������ �����Ѵٸ� ���Ϳ� �����Ѵ�.
            string id;
            unsigned int breakout, championsLeague;
            while (in >> id >> breakout >> championsLeague)
            {
                Player plays(id, breakout, championsLeague);
                players.push_back(plays);
            }
        }
    }

    char select{ 0 };
    while (select != '4')
    {
        cout << "1. ���� ����  2. �÷��̾� �˻�  3. ����  4. ����" << endl;
        cin >> select;
        switch (select)
        {
            // ���� ����
        case '1':
        {
            random_device rd;
            // shuffle �̿��Ͽ� ������ �� 50000�� ��Ż�� �� 50000�� è��
            shuffle(players.begin(), players.end(), rd);
            for (int i = 0; i < playernum; ++i)
            {
                // ��Ż��
                if (i < 50'000)
                {
                    double score = ndScore(dre);
                    score += 5;               // 0 ~ 10
                    score *= 290'588'702.6;
                    score = clamp(score, 0., 2'905'887'026.);
                    if (players[i].GetBreakoutScore() < score)
                        players[i].SetBreakoutScore(score);
                }
                // è��
                else if (i >= 50'000)
                {
                    double score = ndScore(dre);
                    score += 5;               // 0 ~ 10
                    score *= 111'267'038.4;
                    score = clamp(score, 0., 1'112'670'384.);
                    if (players[i].GetChampionsLeague() < score)
                        players[i].SetChampionsLeague(score);
                }
            }
            break;
        }
        // �÷��̾� �˻�
        case '2':
        {
            int breakoutrank = 0;
            int championsLeaguerank = 0;
            string searchName;
            cout << "�˻��� �÷��̾� ID: ";
            cin >> searchName;
            cout << endl;

            sort(players.begin(), players.end(), cmpbreakoutScore);
            for (auto p = players.begin(); p != players.end(); ++p)
            {
                breakoutrank++;
                if (searchName == p->GetName())
                {
                    if ((p - 1)->GetBreakoutScore() != NULL)
                    {
                        cout << "\t\t";
                        cout << (p - 1)->GetName() << "  ";
                        cout << (breakoutrank - 1) << "��  ";
                        cout << "���� " << ((float)(breakoutrank - 1) / 100'000) * 100 << "%  ";
                        cout << "���� " << (p - 1)->GetBreakoutScore() << endl;
                    }
                    //------------------------------------------------------------------
                    cout << "     ��Ż��\t";
                    cout << p->GetName() << "  ";
                    cout << breakoutrank << "��  ";
                    cout << "���� " << ((float)breakoutrank / 100'000) * 100 << "%  ";
                    cout << "���� " << p->GetBreakoutScore() << endl;
                    //------------------------------------------------------------------
                    if ((p + 1)->GetBreakoutScore() != NULL)
                    {
                        cout << "\t\t";
                        cout << (p + 1)->GetName() << "  ";
                        cout << (breakoutrank + 1) << "��  ";
                        cout << "���� " << ((float)(breakoutrank + 1) / 100'000) * 100 << "%  ";
                        cout << "���� " << (p + 1)->GetBreakoutScore() << endl;
                    }
                }
            }
            cout << endl;
            sort(players.begin(), players.end(), cmpchampionsLeague);
            for (auto p = players.begin(); p != players.end(); ++p)
            {
                championsLeaguerank++;
                if (searchName == p->GetName())
                {
                    if ((p - 1)->GetChampionsLeague() != NULL)
                    {
                        cout << "\t\t";
                        cout << (p - 1)->GetName() << "  ";
                        cout << (championsLeaguerank - 1) << "��  ";
                        cout << "���� " << ((float)(championsLeaguerank - 1) / 100'000) * 100 << "%  ";
                        cout << "���� " << (p - 1)->GetChampionsLeague() << endl;
                    }
                    //------------------------------------------------------------------
                    cout << "  è�Ǿ𽺸���\t";
                    cout << p->GetName() << "  ";
                    cout << championsLeaguerank << "��  ";
                    cout << "���� " << ((float)championsLeaguerank / 100'000) * 100 << "%  ";
                    cout << "���� " << p->GetChampionsLeague() << endl;
                    //------------------------------------------------------------------
                    if ((p + 1)->GetBreakoutScore() != NULL)
                    {
                        cout << "\t\t";
                        cout << (p + 1)->GetName() << "  ";
                        cout << (championsLeaguerank + 1) << "��  ";
                        cout << "���� " << ((float)(championsLeaguerank + 1) / 100'000) * 100 << "%  ";
                        cout << "���� " << (p + 1)->GetChampionsLeague() << endl;
                    }
                }
            }
            break;
        }
        // ����
        case '3':
            for (auto p = players.begin(); p != players.end(); ++p)
            {
                double score1 = ndScore(dre);
                score1 += 5;               // 0 ~ 10
                score1 *= 290'588'702.6;
                score1 = clamp(score1, 0., 2'905'887'026.);
                p->SetBreakoutScore(score1);
                double score2 = ndScore(dre);
                score2 += 5;               // 0 ~ 10
                score2 *= 111'267'038.4;
                score2 = clamp(score2, 0., 1'112'670'384.);
                p->SetChampionsLeague(score2);
            }
            break;
        // ����
        case '4':
            break;
        default:
            cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
            break;
        }
    }

    // �÷��̾��� ������ ����
    ofstream out("PlayerList.txt");
    for (int i = 0; i < playernum; ++i)
        out << players[i].GetName() << ' ' << players[i].GetBreakoutScore() << ' ' << players[i].GetChampionsLeague() << endl;
}