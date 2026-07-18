#pragma once
#include <fstream>
#include "LinkedList.h"
#include "Singer.h"
#include "Judge.h"
#include "Match.h"
using namespace std;

class SystemManager {
public:
    LinkedList<Singer> allSingers;
    LinkedList<Judge> allJudges;
    LinkedList<Match> allMatches;

    // 1. 歌手管理
    void addSinger();               // 录入/追加
    void modifySinger();            // 修改
    void deleteSinger();            // 删除
    void viewSingers();             // 浏览全部歌手 
    Singer* findSinger(int id);     // 精确查找
    void searchSinger();            // 模糊查找

    // 2. 评委管理
    void addJudge();
    void modifyJudge();
    void deleteJudge();
    void viewJudges();
    Judge* findJudge(int id);
    void searchJudge();

    // 3. 比赛管理
    void createMatch();         // 新建比赛
    void modifyMatch();         // 修改比赛时间
    void deleteMatch();         // 删除比赛
    void viewMatches();         // 查看全部比赛
    Match* findMatch(int id);   // 查找比赛 

    // 4. 运行比赛与计算排序
    void operateMatch();   // 运作打分流程
    void sortT(LinkedList<SingerScoreRecord>& list); // 内部总分排序算法
    void sortS(LinkedList<SingerScoreRecord>& list, int jId); // 单评委分数排序
    void MatchDetails(); // 浏览单场打分、名次、十佳情况

    // 5. 跨场次统计
    void querySinger(); // 查询某歌手历次成绩
    void queryJudge();  // 查询某评委历次打分

    // 6. 文件管理 
	void saveData();    // 文件保存主入口 
    void loadData();	// 文件读取主入口 
    
	void saveSingers();
    void saveJudges();
    void saveMatches();

    void loadSingers();
    void loadJudges();
    void loadMatches();
    
private:
    // 辅助交换数据函数 
    void swapRecordData(SingerScoreRecord& a, SingerScoreRecord& b);
};
