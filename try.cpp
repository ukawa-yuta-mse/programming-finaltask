#include <iostream>
#include <string>
#include <map> //mapを使用するために導入
#include <fstream>
#include <vector>
#include <iomanip> //マニピュレータを使用するために導入
using namespace std;

//Baseballクラスの定義
class Baseball {
public:
    string teamName;

    double winrate = 0;

    string backyard;

    double era = 0;

public:
    //メンバ関数の定義
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
    //プログラムの説明を表示するときに使用する文字の説明
    string te = "チーム名";
    string win = "勝率";
    string bac = "本拠地（県名）";
    string era = "チーム防御率";

start: //入力された文字に当てはまるものがなかった場合、ここに戻ってくるためのラベル

    //以下、プログラムのタイトル
    cout << "<セリーグの8月9日の勝率と防御率とホーム球場の位置>" << "\n";

    //以下、キーボードに打ち込むべき文字の説明
    cout << " 勝率が高い順に表示したい場合は、'w'とEnterキーを押してください。\n" ;
    cout << " 本拠地がある県名をアルファベット順に表示したい場合は、'b'とEnterキーを押してください。\n";
    cout << " 防御率が低い順に表示したい場合は、'e'とEnterキーを押してください。\n";

    string sort;
    cin >> sort; //標準入力から打ち込まれた文字を読み込む

    ifstream infile("ranking table(1).txt"); //テキストファイルを開く

    string TeamName;
    double Winrate;
    string Backyard;
    double Era;

    vector<Baseball> v; //Vectorの宣言

    //mapはkeyとvalueの組
    //multimapは、keyが同じものがあっても、異なるvalueが追加される。
    
    map<double, int,greater<double>> list1; //勝率が高い順に並べる list1
    multimap<string, int> list2; //本拠地がある県名をアルファベット順に並べる list2
    multimap<double, int> list3; //チーム防御率を低い順に並べる list3

    int i = 0;

    while (infile >> TeamName >> Winrate >> Backyard >> Era) {
        v.emplace_back(); //Vectorに要素を追加

        v[i].setTeamName(TeamName);
        v[i].setWinrate(Winrate);
        v[i].setBackyard(Backyard);
        v[i].setEra(Era);
        list1[Winrate] = i; //mapのkey(TeamName)とvalueの追加
        list2.insert(make_pair(Backyard, i)); 
        list3.insert(make_pair(Era, i));
        i++;
    }
    infile.close();

    static int x = 0; //staticを使うことで、xの値が初期化されずに維持される。
    static int y = 0;
    size_t size = v.size(); //Vectorのサイズを読み込む。
    //列の最大文字数を取得する。
    for (size_t i = 0; i < size; ++i) {
        size_t s = v[i].getTeamName().length();
        size_t t = v[x].getTeamName().length();
        size_t u = v[i].getBackyard().length();
        size_t w = v[y].getBackyard().length();
        if (s >= t) //「s >= t」のとき、
            x = i; //「x = i」を代入する。
        if (u >= w)
            y = i;
    }

    //キーボードで'w'と入力された場合
    if (sort == "w") {
        cout << setw(v[x].getTeamName().length()) << left << te << " (" << win << ") "
            << setw(v[y].getBackyard().length()) << left << bac << " (" << era << ") " << "\n";

        for (const auto& p : list1) {
            //valueとvectorを対応付けて、勝率が高い順に表示
            //イテレータの使用
            cout << setw(v[x].getTeamName().length()) << left << v[p.second].getTeamName() << " (" << setw(win.length()) << left << v[p.second].getWinrate() << ") "
                << setw(v[y].getBackyard().length()) << left << v[p.second].getBackyard() << " (" << v[p.second].getEra() << ") " << endl;
        }
    }
        
    
    //キーボードで'b'と入力された場合
    else if (sort == "b") {
        cout << setw(v[x].getTeamName().length()) << left << te << " (" << win << ") "
            << setw(v[y].getBackyard().length()) << left << bac << " (" << era << ") " << "\n";

        for (const auto& p : list2) {
            //valueとvectorを対応付けて、本拠地がある県名をアルファベット順に表示
            //イテレータの使用
            cout << setw(v[x].getTeamName().length()) << left << v[p.second].getTeamName() << " (" << setw(win.length()) << left << v[p.second].getWinrate() << ") "
                << setw(v[y].getBackyard().length()) << left << v[p.second].getBackyard() << " (" << v[p.second].getEra() << ") " << endl;
        }
    }
    
    //キーボードで'e'と入力された場合
    else if (sort == "e") {
        cout << setw(v[x].getTeamName().length()) << left << te << " (" << win << ") "
            << setw(v[y].getBackyard().length()) << left << bac << " (" << era << ") " << "\n";

        for (const auto& p : list3) {
            //valueとvectorを対応付けて、チーム防御率を低い順に表示
            //イテレータの使用
            cout << setw(v[x].getTeamName().length()) << left << v[p.second].getTeamName() << " (" << setw(win.length()) << left << v[p.second].getWinrate() << ") "
                << setw(v[y].getBackyard().length()) << left << v[p.second].getBackyard() << " (" << v[p.second].getEra() << ") " << endl;
        }
     }
    
    //キーボードで入力された文字が上のどれにも当てはまらない場合
    else {
        //エラーメッセージの表示
        cout << "　　　＃ERROR＃　　　" << endl;
        goto start; //ラベルのstartの位置まで戻る
    }
}