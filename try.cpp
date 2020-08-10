#include <iostream>
#include <string>
#include <map> //map���g�p���邽�߂ɓ���
#include <fstream>
#include <vector>
#include <iomanip> //�}�j�s�����[�^���g�p���邽�߂ɓ���
using namespace std;

//Baseball�N���X�̒�`
class Baseball {
public:
    string teamName;

    double winrate = 0;

    string backyard;

    double era = 0;

public:
    //�����o�֐��̒�`
    void setTeamName(const string& newTeamName) { teamName = newTeamName; }
    string getTeamName() { return teamName; }

    void setWinrate(double newWinrate) { winrate = newWinrate; }
    double getWinrate() { return winrate; }

    void setBackyard(const string& newBackyard) { backyard = newBackyard; }
    string getBackyard() { return backyard; }

    void setEra(double newEra) { era = newEra; }
    double getEra() { return era; }
};

int main() {
    //�v���O�����̐�����\������Ƃ��Ɏg�p���镶���̐���
    string te = "�`�[����";
    string win = "����";
    string bac = "�{���n�i�����j";
    string era = "�`�[���h�䗦";

start: //���͂��ꂽ�����ɓ��Ă͂܂���̂��Ȃ������ꍇ�A�����ɖ߂��Ă��邽�߂̃��x��

    //�ȉ��A�v���O�����̃^�C�g��
    cout << "<�Z���[�O��8��9���̏����Ɩh�䗦�ƃz�[������̈ʒu>" << "\n";

    //�ȉ��A�L�[�{�[�h�ɑł����ނׂ������̐���
    cout << " �������������ɕ\���������ꍇ�́A'w'��Enter�L�[�������Ă��������B\n" ;
    cout << " �{���n�����錧�����A���t�@�x�b�g���ɕ\���������ꍇ�́A'b'��Enter�L�[�������Ă��������B\n";
    cout << " �h�䗦���Ⴂ���ɕ\���������ꍇ�́A'e'��Enter�L�[�������Ă��������B\n";

    string sort;
    cin >> sort; //�W�����͂���ł����܂ꂽ������ǂݍ���

    ifstream infile("ranking table(1).txt"); //�e�L�X�g�t�@�C�����J��

    string TeamName;
    double Winrate;
    string Backyard;
    double Era;

    vector<Baseball> v; //Vector�̐錾

    //map��key��value�̑g
    //multimap�́Akey���������̂������Ă��A�قȂ�value���ǉ������B
    
    map<double, int,greater<double>> list1; //�������������ɕ��ׂ� list1
    multimap<string, int> list2; //�{���n�����錧�����A���t�@�x�b�g���ɕ��ׂ� list2
    multimap<double, int> list3; //�`�[���h�䗦��Ⴂ���ɕ��ׂ� list3

    int i = 0;

    while (infile >> TeamName >> Winrate >> Backyard >> Era) {
        v.emplace_back(); //Vector�ɗv�f��ǉ�

        v[i].setTeamName(TeamName);
        v[i].setWinrate(Winrate);
        v[i].setBackyard(Backyard);
        v[i].setEra(Era);
        list1[Winrate] = i; //map��key(TeamName)��value�̒ǉ�
        list2.insert(make_pair(Backyard, i)); 
        list3.insert(make_pair(Era, i));
        i++;
    }
    infile.close();

    static int x = 0; //static���g�����ƂŁAx�̒l�����������ꂸ�Ɉێ������B
    static int y = 0;
    size_t size = v.size(); //Vector�̃T�C�Y��ǂݍ��ށB
    //��̍ő啶�������擾����B
    for (size_t i = 0; i < size; ++i) {
        size_t s = v[i].getTeamName().length();
        size_t t = v[x].getTeamName().length();
        size_t u = v[i].getBackyard().length();
        size_t w = v[y].getBackyard().length();
        if (s >= t) //�us >= t�v�̂Ƃ��A
            x = i; //�ux = i�v��������B
        if (u >= w)
            y = i;
    }

    //�L�[�{�[�h��'w'�Ɠ��͂��ꂽ�ꍇ
    if (sort == "w") {
        cout << setw(v[x].getTeamName().length()) << left << te << " (" << win << ") "
            << setw(v[y].getBackyard().length()) << left << bac << " (" << era << ") " << "\n";

        for (const auto& p : list1) {
            //value��vector��Ή��t���āA�������������ɕ\��
            //�C�e���[�^�̎g�p
            cout << setw(v[x].getTeamName().length()) << left << v[p.second].getTeamName() << " (" << setw(win.length()) << left << v[p.second].getWinrate() << ") "
                << setw(v[y].getBackyard().length()) << left << v[p.second].getBackyard() << " (" << v[p.second].getEra() << ") " << endl;
        }
    }
        
    
    //�L�[�{�[�h��'b'�Ɠ��͂��ꂽ�ꍇ
    else if (sort == "b") {
        cout << setw(v[x].getTeamName().length()) << left << te << " (" << win << ") "
            << setw(v[y].getBackyard().length()) << left << bac << " (" << era << ") " << "\n";

        for (const auto& p : list2) {
            //value��vector��Ή��t���āA�{���n�����錧�����A���t�@�x�b�g���ɕ\��
            //�C�e���[�^�̎g�p
            cout << setw(v[x].getTeamName().length()) << left << v[p.second].getTeamName() << " (" << setw(win.length()) << left << v[p.second].getWinrate() << ") "
                << setw(v[y].getBackyard().length()) << left << v[p.second].getBackyard() << " (" << v[p.second].getEra() << ") " << endl;
        }
    }
    
    //�L�[�{�[�h��'e'�Ɠ��͂��ꂽ�ꍇ
    else if (sort == "e") {
        cout << setw(v[x].getTeamName().length()) << left << te << " (" << win << ") "
            << setw(v[y].getBackyard().length()) << left << bac << " (" << era << ") " << "\n";

        for (const auto& p : list3) {
            //value��vector��Ή��t���āA�`�[���h�䗦��Ⴂ���ɕ\��
            //�C�e���[�^�̎g�p
            cout << setw(v[x].getTeamName().length()) << left << v[p.second].getTeamName() << " (" << setw(win.length()) << left << v[p.second].getWinrate() << ") "
                << setw(v[y].getBackyard().length()) << left << v[p.second].getBackyard() << " (" << v[p.second].getEra() << ") " << endl;
        }
     }
    
    //�L�[�{�[�h�œ��͂��ꂽ��������̂ǂ�ɂ����Ă͂܂�Ȃ��ꍇ
    else {
        //�G���[���b�Z�[�W�̕\��
        cout << "�@�@�@��ERROR���@�@�@" << endl;
        goto start; //���x����start�̈ʒu�܂Ŗ߂�
    }
}