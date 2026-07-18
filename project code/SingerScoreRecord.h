#pragma once
#include <iostream>
#include "LinkedList.h"
using namespace std;

struct Score {					// 评委打分单个记录结构体 
    int id;        
    double score;       

    Score() : id(0), score(0.0) {}
    Score(int i, double s) : id(i), score(s) {}
};

class SingerScoreRecord {
public:
    int singerId;                       
    string singerName;             
    LinkedList<Score> scoreList;        // 存放比赛评委打分的结构体 

    double totalScore;                  // 总成绩（去掉最高最低分）
    double averageScore;                // 平均成绩
    int rank;                           // 比赛名次

    SingerScoreRecord() : singerId(0), totalScore(0.0), averageScore(0.0), rank(0) {}
};
