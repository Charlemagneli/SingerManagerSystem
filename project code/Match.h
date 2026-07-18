#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Singer.h"
#include "Judge.h"
#include "SingerScoreRecord.h"
using namespace std; 

class Match {
public:
    int matchId;                           
    string matchDate;                           
    LinkedList<Singer> Singers;      // 参加本场比赛的歌手链表
    LinkedList<Judge> Judges;        // 参加本场比赛的评委链表
    LinkedList<SingerScoreRecord> scoreRecords; // 歌手得分情况链表
    LinkedList<SingerScoreRecord> topTen;       // 比赛十佳情况链表

    Match() : matchId(0) {}
    Match(int id, string date) : matchId(id), matchDate(date) {}
};
