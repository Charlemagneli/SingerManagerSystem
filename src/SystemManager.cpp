#include <fstream>
#include <iostream>
#include <string> 
#include <sstream>
#include "SystemManager.h"
#include "Validator.h"
using namespace std;

// 交换两个成绩记录的数据
void SystemManager::swapRecordData(SingerScoreRecord& a, SingerScoreRecord& b) {
    SingerScoreRecord temp = a;
    a = b;
    b = temp;
}

// 1. 歌手管理 
void SystemManager::addSinger() {
    cout << "\n--- 录入/追加新歌手 ---" << endl;
    cout << "请输入歌手编号 (正整数): ";
    int id = Validator::validId();
    if (findSinger(id) != NULL) {
        cout << "[错误] 该编号的歌手已存在！\n";
        return;
    }
    string name, gender, birthday, addr, group, awards;
    cout << "请输入姓名: "; cin >> name;
    cout << "请输入性别 (男/女): "; gender = Validator::validGender();
    cout << "请输入出生年月信息：\n"; birthday = Validator::validDate();
    cout << "请输入地址: "; cin >> addr;
    cout << "请输入组别: "; cin >> group;
    cout << "请输入历次获奖信息: "; cin >> awards;

    allSingers.append(Singer(id, name, gender, birthday, addr, group, awards));
    saveData(); 
    cout << "[成功] 歌手录入成功并已自动保存！\n";
}

void SystemManager::modifySinger() {
    cout << "\n--- 修改歌手数据 ---" << endl;
    cout << "请输入要修改的歌手编号: ";
    int id = Validator::validId();
    Singer* s = findSinger(id);
    if (s == NULL) {
        cout << "[错误] 未找到该歌手。\n";
        return;
    }
    while (true) {
        cout << "\n=================================" << endl;
        cout << "  正在修改歌手【" << s->name << "】的信息" << endl;
        cout << "=================================" << endl;
        cout << "  1. 修改姓名       (当前: " << s->name << ")" << endl;
        cout << "  2. 修改性别       (当前: " << s->gender << ")" << endl;
        cout << "  3. 修改出生年月   (当前: " << s->birthday << ")" << endl;
        cout << "  4. 修改联系地址   (当前: " << s->address << ")" << endl;
        cout << "  5. 修改参赛组别   (当前: " << s->group << ")" << endl;
        cout << "  6. 修改获奖情况   (当前: " << s->awards << ")" << endl;
        cout << "  0. 结束修改" << endl;
        cout << "---------------------------------" << endl;
        cout << "请输入要修改的项目序号 (0-6): ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {           // 防止非法输入导致死循环 
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[错误] 请输入有效的数字序号！\n";
            continue;
        }

        if (choice == 0) {
            cout << "已退出该歌手的修改。" << endl;
            saveData();				//自动保存 
            break; 
        }

        cout << "\n请输入新的数据: ";
        switch (choice) {
            case 1:
                cin >> s->name;
                cout << "[成功] 姓名已更新！\n";
                break;
            case 2:
                s->gender = Validator::validGender();
                cout << "[成功] 性别已更新！\n";
                break;
            case 3:
                cout << endl;
                s->birthday = Validator::validDate();
                cout << "[成功] 出生年月已更新！\n";
                break;
            case 4:
                cin >> s->address;
                cout << "[成功] 联系地址已更新！\n";
                break;
            case 5:
                cin >> s->group;
                cout << "[成功] 参赛组别已更新！\n";
                break;
            case 6:
                cin >> s->awards;
                cout << "[成功] 获奖情况已更新！\n";
                break;
            default:
                cout << "[错误] 无效的选择，请输入 0 到 6 之间的数字。\n";
                break;
        }
    }
}

void SystemManager::deleteSinger() {
    cout << "\n--- 删除歌手 ---" << endl;
    cout << "请输入要删除的歌手编号: ";
    int id = Validator::validId();
    Node<Singer>* curr = allSingers.getHead();
    Node<Singer>* prev = NULL;
    while (curr != NULL) {
        if (curr->data.id == id) {
            allSingers.removeNode(curr, prev);
            cout << "[成功] 歌手已成功删除！\n";
            saveData();				//自动保存 
            return;
        }
        prev = curr; curr = curr->next;
    }
    cout << "[失败] 未找到该歌手。\n";
}

void SystemManager::viewSingers() {
    cout << "\n--- 浏览全部歌手 ---" << endl;
    Node<Singer>* t = allSingers.getHead();
    if (t == NULL) { cout << "暂无歌手数据。\n"; return; }
    while (t != NULL) {
        cout << "ID: " << t->data.id << "\t| 姓名: " << t->data.name 
             << "\t| 性别: " << t->data.gender << "\t| 生日: " << t->data.birthday 
             << "\t| 地址：" << t->data.address  << "\t| 组别: " << t->data.group
			 << "\t| 获奖: " << t->data.awards << endl;
        t = t->next;
    }
}

Singer* SystemManager::findSinger(int id) {
    Node<Singer>* t = allSingers.getHead();
    while (t != NULL) {
        if (t->data.id == id) return &(t->data);
        t = t->next;
    }
    return NULL;
}

void SystemManager::searchSinger() {
    cout << "\n--- 模糊查找歌手 ---" << endl;
    cout << "请输入名字关键字: "; 
	string keywords; 
	cin >> keywords;
    Node<Singer>* t = allSingers.getHead();
    bool found = false;
    while (t != NULL) {
        if (t->data.name.find(keywords) != string::npos) {
            cout << "[匹配] ID: " << t->data.id << " | 姓名: " << t->data.name 
			<< "\t| 性别: " << t->data.gender << "\t| 生日: " << t->data.birthday 
            << "\t| 地址：" << t->data.address  << "\t| 组别: " << t->data.group
			<< "\t| 获奖: " << t->data.awards << endl;
            found = true;
        }
        t = t->next;
    }
    if (!found) cout << "无匹配结果。\n";
}

// ==================== 2. 评委管理 ====================
void SystemManager::addJudge() {
    cout << "\n--- 录入/追加新评委 ---" << endl;
    cout << "请输入评委编号: "; int id = Validator::validId();
    if (findJudge(id) != NULL) { cout << "[错误] 该编号已存在！\n"; return;}
    string name, gender, birthday, addr, group, title;
    cout << "请输入姓名: "; cin >> name;
    cout << "请输入性别: "; gender = Validator::validGender();
    cout << "请输入出生年月：\n"; birthday = Validator::validDate();
    cout << "请输入地址: "; cin >> addr;
    cout << "请输入组别: "; cin >> group;
    cout << "请输入评委头衔: "; cin >> title;
    allJudges.append(Judge(id, name, gender, birthday, addr, group, title));
    saveData(); 
    cout << "[成功] 评委录入成功并已自动保存！\n";
}

void SystemManager::modifyJudge() {
    cout << "\n--- 修改评委数据 ---" << endl;
    cout << "请输入评委编号: "; int id = Validator::validId();
    Judge* j = findJudge(id);
    if (j == NULL) { cout << "未找到该评委。\n"; return; }
    while (true) {
        cout << "\n=================================" << endl;
        cout << "  正在修改评委【" << j->name << "】的信息" << endl;
        cout << "=================================" << endl;
        cout << "  1. 修改姓名       (当前: " << j->name << ")" << endl;
        cout << "  2. 修改性别       (当前: " << j->gender << ")" << endl;
        cout << "  3. 修改出生年月   (当前: " << j->birthday << ")" << endl;
        cout << "  4. 修改联系地址   (当前: " << j->address << ")" << endl;
        cout << "  5. 修改评审组别   (当前: " << j->group << ")" << endl;
        cout << "  6. 修改评委头衔   (当前: " << j->title << ")" << endl;
        cout << "  0. 放弃/结束修改" << endl;
        cout << "---------------------------------" << endl;
        cout << "请输入要修改的项目序号 (0-6): ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[错误] 请输入有效的数字序号！\n";
            continue;
        }

        if (choice == 0) {
            cout << "已退出该评委的修改。" << endl;
            saveData();				//自动保存 
			break; 
        }

        cout << "\n请输入新的数据: ";
        switch (choice) {
            case 1:
                cin >> j->name;
                cout << "[成功] 姓名已更新！\n";
                break;
            case 2:
                j->gender = Validator::validGender(); 
                cout << "[成功] 性别已更新！\n";
                break;
            case 3:
                cout << endl; 
                j->birthday = Validator::validDate(); 
                cout << "[成功] 出生年月已更新！\n";
                break;
            case 4:
                cin >> j->address;
                cout << "[成功] 联系地址已更新！\n";
                break;
            case 5:
                cin >> j->group;
                cout << "[成功] 评审组别已更新！\n";
                break;
            case 6:
                cin >> j->title;
                cout << "[成功] 评委头衔已更新！\n";
                break;
            default:
                cout << "[错误] 无效的选择，请输入 0 到 6 之间的数字。\n";
                break;
        }
	}
}

void SystemManager::deleteJudge() {
    cout << "\n--- 删除评委 ---" << endl;
    cout << "请输入评委编号: "; int id = Validator::validId();
    Node<Judge>* curr = allJudges.getHead(); 
	Node<Judge>* prev = NULL;
    while (curr != NULL) {
        if (curr->data.id == id) {
			allJudges.removeNode(curr, prev); 
			cout << "删除成功！\n"; 
			saveData();				//自动保存 
			return; 
		}
        prev = curr; curr = curr->next;
    }
    cout << "未找到该评委。\n";
}

void SystemManager::viewJudges() {
    cout << "\n--- 浏览全部评委 ---" << endl;
    Node<Judge>* t = allJudges.getHead();
    if (t == NULL) { cout << "暂无评委数据。\n"; return; }
    while (t != NULL) {
        cout << "ID: " << t->data.id << "\t| 姓名: " << t->data.name 
		<< "\t| 性别: " << t->data.gender << "\t| 生日: " 
		<< t->data.birthday<< "\t| 地址：" << t->data.address 
        << "\t| 头衔: " << t->data.title << "\t| 组别: " << t->data.group << endl;
        t = t->next;
    }
}

Judge* SystemManager::findJudge(int id) {   	// 精确查找 
    Node<Judge>* t = allJudges.getHead();
    while (t != NULL) { 
	if (t->data.id == id) return &(t->data); 
	t = t->next; 
	}
    return NULL;
}

void SystemManager::searchJudge() {  		 // 模糊查找 
    cout << "\n--- 模糊查找评委 ---" << endl;
    cout << "请输入名字关键字: "; 
	string keywords; 
	cin >> keywords;
    Node<Judge>* t = allJudges.getHead(); bool found = false;
    while (t != NULL) {
        if (t->data.name.find(keywords) != string::npos) {
            cout << "[匹配] ID: " << t->data.id << " | 姓名: " << t->data.name
            << "\t| 性别: " << t->data.gender << "\t| 生日: " 
			<< t->data.birthday<< "\t| 地址：" << t->data.address 
        	<< "\t| 头衔: " << t->data.title << "\t| 组别: " << t->data.group << endl;
        	t = t->next;
            found = true;
        }
        t = t->next;
    }
    if (!found) cout << "无匹配结果。\n";
}

// ==================== 3. 比赛管理 ====================
void SystemManager::createMatch() {
    cout << "\n--- 新建比赛场次 ---" << endl;
    cout << "请输入比赛场次编号: "; int id = Validator::validId();
    if (findMatch(id) != NULL) { cout << "[错误] 该场次已存在！\n"; return; }
    cout << "请输入比赛日期: \n"; 
	string date = Validator::validDate();  
    allMatches.append(Match(id, date));
    cout << "[成功] 第 " << id << " 场比赛创建成功！\n";
    saveData(); 
}

void SystemManager::modifyMatch() {
    cout << "\n--- 修改比赛时间 ---" << endl;
    cout << "请输入场次编号: "; int id = Validator::validId();
    Match* m = findMatch(id);
    if (m == NULL) { cout << "未找到该场次。\n"; return; }
    cout << "当前日期: " << m->matchDate << "，请输入新日期: \n"; 
	m->matchDate = Validator::validDate();
    cout << "[成功] 比赛日期更新完成！\n";
    saveData();
}

void SystemManager::deleteMatch() {
    cout << "\n--- 删除比赛 ---" << endl;
    cout << "请输入场次编号: "; int id = Validator::validId();
    Node<Match>* curr = allMatches.getHead(); 
	Node<Match>* prev = NULL;
    while (curr != NULL) {
        if (curr->data.matchId == id) { 
		allMatches.removeNode(curr, prev); 
		cout << "删除成功！\n"; 
		saveData();
		return; 
		}
        prev = curr; curr = curr->next;
    }
    cout << "未找到该场次。\n";
}

void SystemManager::viewMatches() {
    cout << "\n--- 查看全部比赛 ---" << endl;
    Node<Match>* t = allMatches.getHead();
    if (t == NULL) { cout << "暂无比赛信息。\n"; return; }
    while (t != NULL) {
        cout << "场次ID: " << t->data.matchId << " | 日期: " << t->data.matchDate 
             << " | 参赛人数: " << t->data.scoreRecords.getSize() << endl;
        t = t->next;
    }
}

Match* SystemManager::findMatch(int id) {
    Node<Match>* t = allMatches.getHead();
    while (t != NULL) { 
		if (t->data.matchId == id) return &(t->data); 
		t = t->next; 
	}
    return NULL;
}

// ==================== 4. 运行比赛与计算排序 ====================
void SystemManager::operateMatch() {
    cout << "\n===== 运作打分流程 =====" << endl;
    cout << "请输入要运作的场次ID: "; int mId = Validator::validId();
    Match* m = findMatch(mId);
    if (m == NULL) { cout << "[错误] 无此场次，请先新建！\n"; return; }

    int judgeCount; 
	cout << "请输入本场评委人数: "; 
	judgeCount = Validator::validId();
	bool flag; 
    if (judgeCount < 3) {
		cout << "[提示] 比赛采用整体平均得分计分。\n"; 
		flag = false;
	}
	else{
		cout << "[提示] 比赛采用去掉最高最低分后平均得分计分。\n";
		flag = true;
	}

    m->Judges.clear();
    for (int i = 0; i < judgeCount; i++) {
        while (true) {
            cout << "请输入第 " << (i + 1) << " 位评委的ID: "; 
            int jId = Validator::validId();
            
            Judge* j = findJudge(jId);
            if (j == NULL) { 
                cout << "[错误] 系统库无此评委，请重新输入该评委ID！\n\n"; 
			}
			else { 
                m->Judges.append(*j); 
                cout << "[成功] 成功添加[" << j->name << "]评委 。\n";
                break; 
	        }
	    }
	}

	int singerCount; 
    cout << "请输入本场参赛选手人数: "; 
	cin >> singerCount;
    m->scoreRecords.clear();

    for (int i = 0; i < singerCount; i++) {
        Singer* s = NULL; 
        
        while (true) {
            cout << "\n-> 请输入第 " << (i + 1) << " 位出场选选手编号: "; 
            int sId = Validator::validId();
            
            s = findSinger(sId);
            if (s == NULL) { 
                cout << "[错误] 系统库无此选手，请重新输入该选手ID！\n"; 
            } 
			else { 
                m->Singers.append(*s); 
                cout << "[成功] 选手[" << s->name << "]开始进行打分。\n";
                break; 
            }
        }

        SingerScoreRecord record;
        record.singerId = s->id;
        record.singerName = s->name;

        double maxScore = -1.0, minScore = 101.0, sum = 0.0;
        
        Node<Judge>* judgeA = m->Judges.getHead();
        while (judgeA != NULL) {
            cout << "评委 [" << judgeA->data.name << "] 给分: ";
            double sc = Validator::validScore();
            
            record.scoreList.append(Score(judgeA->data.id, sc));
            sum += sc;
            
			if (sc > maxScore) maxScore = sc;
            if (sc < minScore) minScore = sc;

            judgeA = judgeA->next;
        }

        	if(flag){
				record.totalScore = sum - maxScore - minScore;
        		record.averageScore = record.totalScore / (judgeCount - 2);
			}
			else{
				record.totalScore = sum;
        		record.averageScore = record.totalScore / judgeCount;
			}

        m->scoreRecords.append(record);
    }

    sortT(m->scoreRecords);               //冒泡排序 
	m->topTen.clear(); 
	
    Node<SingerScoreRecord>* recCurr = m->scoreRecords.getHead();
    int currentRank = 1;
    while (recCurr != NULL) {
        recCurr->data.rank = currentRank;
        if (currentRank <= 10) 
		{ m->topTen.append(recCurr->data); }
        currentRank++;
        recCurr = recCurr->next;
    }
    
	saveData();
    cout << "\n[成功] 本场打分结束，名次已生成！\n";
}

// 采用冒泡排序：按总成绩降序排列
void SystemManager::sortT(LinkedList<SingerScoreRecord>& list) {
    if (list.getSize() < 2) return;               // 少于2人不需要排序

    Node<SingerScoreRecord>* lastNode = NULL;     //记录已排好的第一个节点 
	for (Node<SingerScoreRecord>* i = list.getHead(); i != NULL; i = i->next) {
		Node<SingerScoreRecord>* currNode = NULL;
		for (Node<SingerScoreRecord>* j = list.getHead(); j->next != lastNode; j = j->next) {
            if (j->data.totalScore < j->next->data.totalScore) {
                swapRecordData(j->data, j->next->data);
                currNode = j->next;
            }
        }
        if (currNode == NULL) {break;}           //未排序则提前退出 
        lastNode = currNode;
    }
}

// 采用冒泡排序：按指定单个评委分数降序排列
void SystemManager::sortS(LinkedList<SingerScoreRecord>& list, int jId) {
    if (list.getSize() < 2) return;          

    Node<SingerScoreRecord>* lastNode = NULL; 

    for (Node<SingerScoreRecord>* i = list.getHead(); i != NULL; i = i->next) {
        
		Node<SingerScoreRecord>* currNode = NULL; 
        
		for (Node<SingerScoreRecord>* j = list.getHead(); j->next != lastNode; j = j->next) {  
            double score1 = 0.0; 			// 提取当前选手的分数
            Node<Score>* currScore1 = j->data.scoreList.getHead();
            while (currScore1 != NULL) { 
                if (currScore1->data.id == jId) { 
                    score1 = currScore1->data.score; 
                    break; 
                } 
                currScore1 = currScore1->next; 
            }
            
            
            double score2 = 0.0;			// 提取下一个选手的分数
            Node<Score>* currScore2 = j->next->data.scoreList.getHead();
            while (currScore2 != NULL) { 
                if (currScore2->data.id == jId) { 
                    score2 = currScore2->data.score; 
                    break; 
                } 
                currScore2 = currScore2->next; 
            }

            if (score1 < score2) {
                swapRecordData(j->data, j->next->data);
                currNode = j->next;                            
            }
        }
        if (currNode == NULL) {
            break; 
        }
        
        lastNode = currNode;         //记录已排好的第一个节点
    }
}

void SystemManager::MatchDetails() {
    cout << "\n--- 浏览单场比赛详情 ---" << endl;
    cout << "请输入要浏览的场次编号: "; int id = Validator::validId();
    Match* m = findMatch(id);
    if (m == NULL || m->scoreRecords.getSize() == 0) { 
		cout << "该场次无打分数据。\n"; return; 
	}

    cout << "\n排序模式：1.按总成绩(默认) | 2.按某位评委分数: ";
    int choice; cin >> choice;
    if (choice == 2) {
        cout << "请输入指定的评委ID: "; int jId = Validator::validId();
        sortS(m->scoreRecords, jId);
    } 
	else{sortT(m->scoreRecords);}

    Node<SingerScoreRecord>* curr = m->scoreRecords.getHead();
    while (curr != NULL) {
        cout << "\n排名: " << curr->data.rank << " | 选手ID: " << curr->data.singerId 
             << " | 姓名: " << curr->data.singerName << " | 最终总分: " << curr->data.totalScore << "\n  [详打分]: ";
        
        Node<Score>* a = curr->data.scoreList.getHead();
        while (a != NULL) {
            cout << "(评委" << a->data.id << "号: " << a->data.score << ") ";
            a = a->next;
        }
        cout << "\n--------------------------------------------------------------\n";
        curr = curr->next;
    }
}

// ==================== 5. 跨场次统计 ====================
void SystemManager::querySinger() {
    cout << "\n--- 查询歌手历次成绩 ---" << endl;
    cout << "请输入该歌手编号: "; int sId = Validator::validId();
    Singer* s = findSinger(sId);
    if (s == NULL) { cout << "档案库无此歌手！\n"; return; }

    cout << "\n歌手 [" << s->name << "] 的历史成绩：\n";
    bool flag = false;
    Node<Match>* curr1 = allMatches.getHead();
    while (curr1 != NULL) {
        Node<SingerScoreRecord>* curr2 = curr1->data.scoreRecords.getHead();
        while (curr2 != NULL) {
            if (curr2->data.singerId == sId) {
                cout << "-> 场次: " << curr1->data.matchId << " | 总分: " << curr2->data.totalScore 
                     << " | 名次: 第 " << curr2->data.rank << " 名\n";
                flag = true;
                break;
            }
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }
    if (!flag) cout << "暂无参赛记录。\n";
}

void SystemManager::queryJudge() {
    cout << "\n--- 查询评委历次打分 ---" << endl;
    cout << "请输入评委编号: "; int jId = Validator::validId();
    Judge* j = findJudge(jId);
    if (j == NULL) { cout << "档案库无此评委。\n"; return; }

    cout << "\n评委 [" << j->name << "] 的历史打分记录：\n";
    Node<Match>* curr1 = allMatches.getHead();
    while (curr1 != NULL) {
        Node<SingerScoreRecord>* curr2 = curr1->data.scoreRecords.getHead();
        while (curr2 != NULL) {
            Node<Score>* curr3 = curr2->data.scoreList.getHead();
            while (curr3 != NULL) {
                if (curr3->data.id == jId) {
                    cout << "-> 场次: " << curr1->data.matchId << " | 给选手 [" 
                         << curr2->data.singerName << "] 打出: " << curr3->data.score << " 分\n";
                }
                curr3 = curr3->next;
            }
            curr2 = curr2->next;
        }
        curr1 = curr1->next;
    }
}

// ==================== 6. 文件管理重构  ====================
void SystemManager::saveData() {
    saveSingers();
    saveJudges();
    saveMatches();
}

void SystemManager::loadData() {
    loadSingers();
    loadJudges();
    loadMatches();
}

// 6.1 歌手数据保存
void SystemManager::saveSingers() {
    ofstream fout("singers.csv", ios::out); 
    if (!fout) {
        cout << "[警告] 无法创建歌手数据文件！\n";
        return;
    }
    Node<Singer>* curr = allSingers.getHead();
    while (curr != NULL) {
        fout << curr->data.id << ","
             << curr->data.name << ","
             << curr->data.gender << ","
             << curr->data.birthday << ","
             << curr->data.address << ","
             << curr->data.group << ","
             << curr->data.awards << "\n";
        curr = curr->next;
    }
    fout.close();
}

// 6.2 歌手数据加载
void SystemManager::loadSingers() {
    ifstream fin("singers.csv", ios::in);
    if (!fin) {
        cout << "[提示] 未找到歌手本地数据文件，跳过加载。\n";
        return;
    }
    allSingers.clear(); // 清空当前链表防止重复加载
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, gender, birthday, address, group, awards;
        
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, gender, ',');
        getline(ss, birthday, ',');
        getline(ss, address, ',');
        getline(ss, group, ',');
        getline(ss, awards, '\n');
        
        Singer s(stoi(id), name, gender, birthday, address, group, awards);
        allSingers.append(s);
    }
    fin.close();
    cout << "[成功] 歌手数据加载成功。\n";
}

// 6.3 评委数据保存
void SystemManager::saveJudges() {
    ofstream fout("judges.csv", ios::out);
    if (!fout) {
        cout << "[警告] 无法创建评委数据文件！\n";
        return;
    }
    Node<Judge>* curr = allJudges.getHead();
    while (curr != NULL) {
        fout << curr->data.id << ","
             << curr->data.name << ","
             << curr->data.gender << ","
             << curr->data.birthday << ","
             << curr->data.address << ","
             << curr->data.group << ","
             << curr->data.title << "\n";
        curr = curr->next;
    }
    fout.close();
}

// 6.4 评委数据单独加载
void SystemManager::loadJudges() {
    ifstream fin("judges.csv", ios::in);
    if (!fin) {
        cout << "[提示] 未找到评委本地数据文件，跳过加载。\n";
        return;
    }
    allJudges.clear();
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, gender, birthday, address, group, title;
        
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, gender, ',');
        getline(ss, birthday, ',');
        getline(ss, address, ',');
        getline(ss, group, ',');
        getline(ss, title, '\n');
        
        Judge j(stoi(id), name, gender, birthday, address, group, title);
        allJudges.append(j);
    }
    fin.close();
    cout << "[成功] 评委数据加载成功。\n";
}

// 6.5 比赛数据保存 
void SystemManager::saveMatches() {
    ofstream fout("matches_detail.csv", ios::out);
    if (!fout) {
        cout << "[警告] 无法创建比赛完整数据保存文件！\n";
        return;
    }

    Node<Match>* currMatch = allMatches.getHead();
    while (currMatch != NULL) {
        Match& m = currMatch->data;
        
        // 1. 保存 Match 的基础字段
        fout << "[MATCH]\n";
        fout << m.matchId << "," << m.matchDate << "\n";

        // 2. 保存 LinkedList<Singer> Singers
        fout << "[SINGERS]\n" << m.Singers.getSize() << "\n";
        Node<Singer>* sNode = m.Singers.getHead();
        while (sNode != NULL) {
            fout << sNode->data.id << "," << sNode->data.name << "," << sNode->data.gender << ","
                 << sNode->data.birthday << "," << sNode->data.address << "," << sNode->data.group << ","
                 << sNode->data.awards << "\n";
            sNode = sNode->next;
        }

        // 3. 保存 LinkedList<Judge> Judges
        fout << "[JUDGES]\n" << m.Judges.getSize() << "\n";
        Node<Judge>* jNode = m.Judges.getHead();
        while (jNode != NULL) {
            fout << jNode->data.id << "," << jNode->data.name << "," << jNode->data.gender << ","
                 << jNode->data.birthday << "," << jNode->data.address << "," << jNode->data.group << ","
                 << jNode->data.title << "\n";
            jNode = jNode->next;
        }

        // 4. 保存 LinkedList<SingerScoreRecord> scoreRecords
        fout << "[SCORERECORDS]\n" << m.scoreRecords.getSize() << "\n";
        Node<SingerScoreRecord>* rNode = m.scoreRecords.getHead();
        while (rNode != NULL) {
            fout << rNode->data.singerId << "," << rNode->data.singerName << ","
                 << rNode->data.totalScore << "," << rNode->data.averageScore << ","
                 << rNode->data.rank << ",";
            
            // 嵌套保存该选手的各个评委打分 scoreList 
			// (格式: 评委ID:分数|评委ID:分数)
            Node<Score>* scoreNode = rNode->data.scoreList.getHead();
            while (scoreNode != NULL) {
                fout << scoreNode->data.id << ":" << scoreNode->data.score;
                if (scoreNode->next != NULL) fout << "|";
                scoreNode = scoreNode->next;
            }
            fout << "\n";
            rNode = rNode->next;
        }

        // 5. 保存 LinkedList<SingerScoreRecord> topTen
        fout << "[TOPTEN]\n" << m.topTen.getSize() << "\n";
        Node<SingerScoreRecord>* tNode = m.topTen.getHead();
        while (tNode != NULL) {
            fout << tNode->data.singerId << "," << tNode->data.singerName << ","
                 << tNode->data.totalScore << "," << tNode->data.averageScore << ","
                 << tNode->data.rank << ",";
            
            // 嵌套保存前十选手的各个评委打分 scoreList
            Node<Score>* scoreNode = tNode->data.scoreList.getHead();
            while (scoreNode != NULL) {
                fout << scoreNode->data.id << ":" << scoreNode->data.score;
                if (scoreNode->next != NULL) fout << "|";
                scoreNode = scoreNode->next;
            }
            fout << "\n";
            tNode = tNode->next;
        }

        currMatch = currMatch->next;
    }

    fout.close();
    cout << "[成功] 比赛数据已保存！\n";
}

// 6.6 比赛数据加载 
void SystemManager::loadMatches() {
    ifstream fin("matches_detail.csv", ios::in);
    if (!fin) {
        cout << "[提示] 未找到比赛数据文件，跳过加载。\n";
        return;
    }

    allMatches.clear(); // 清空当前已有数据防止重复追加
    string line;

    while (getline(fin, line)) {
        if (line.empty()) continue;
		if (line == "[MATCH]") {
            // 读取场次基础信息
            string line1;
            if (!getline(fin, line1)) break; 
            stringstream ss(line1);
            string matchIdStr, matchDate;    // 拆分数据 
            getline(ss, matchIdStr, ',');
            getline(ss, matchDate, '\n');

            Match m(stoi(matchIdStr), matchDate);

            string tag, countStr;

            // 1. 读取 Singers 链表
            getline(fin, tag); // 读取 "[SINGERS]" 标签
            getline(fin, countStr);
            int sCount = stoi(countStr);
            for (int i = 0; i < sCount; i++) {
                string sLine;
                getline(fin, sLine);
                stringstream ss1(sLine);
                string id, name, gender, birthday, address, group, awards;
                getline(ss1, id, ',');
                getline(ss1, name, ',');
                getline(ss1, gender, ',');
                getline(ss1, birthday, ',');
                getline(ss1, address, ',');
                getline(ss1, group, ',');
                getline(ss1, awards, '\n');
                m.Singers.append(Singer(stoi(id), name, gender, birthday, address, group, awards));
            }

            // 2. 读取 Judges 链表
            getline(fin, tag); // 读取 "[JUDGES]" 标签
            getline(fin, countStr);
            int jCount = stoi(countStr);
            for (int i = 0; i < jCount; i++) {
                string jLine;
                getline(fin, jLine);
                stringstream ss2(jLine);
                string id, name, gender, birthday, address, group, title;
                getline(ss2, id, ',');
                getline(ss2, name, ',');
                getline(ss2, gender, ',');
                getline(ss2, birthday, ',');
                getline(ss2, address, ',');
                getline(ss2, group, ',');
                getline(ss2, title, '\n');
                m.Judges.append(Judge(stoi(id), name, gender, birthday, address, group, title));
            }

            // 3. 读取 scoreRecords 链表
            getline(fin, tag); // 读取 "[SCORERECORDS]" 标签
            getline(fin, countStr);
            int rCount = stoi(countStr);
            for (int i = 0; i < rCount; i++) {
                string rLine;
                getline(fin, rLine);
                stringstream ss3(rLine);
                string sIdStr, sName, tScoreStr, aScoreStr, rankStr, scoresStr;
                getline(ss3, sIdStr, ',');
                getline(ss3, sName, ',');
                getline(ss3, tScoreStr, ',');
                getline(ss3, aScoreStr, ',');
                getline(ss3, rankStr, ',');
                getline(ss3, scoresStr, '\n');

                SingerScoreRecord record;
                record.singerId = stoi(sIdStr);
                record.singerName = sName;
                record.totalScore = stod(tScoreStr);
                record.averageScore = stod(aScoreStr);
                record.rank = stoi(rankStr);

                // 恢复底层的评委细分 scoreList
                if (!scoresStr.empty()) {
                    stringstream ss4(scoresStr);
                    string t;
                    while (getline(ss4, t, '|')) {
                        if (t.empty()) continue;
                        
						size_t pos = t.find(':');
                        
						if (pos != string::npos) {
                            int jId = stoi(t.substr(0, pos));
                            double sc = stod(t.substr(pos + 1));
                            record.scoreList.append(Score(jId, sc));
                        }
                    }
                }
                m.scoreRecords.append(record);
            }

            // 4. 读取 topTen 链表
            getline(fin, tag); // 读取 "[TOPTEN]" 标签
            getline(fin, countStr);
            int tCount = stoi(countStr);
            for (int i = 0; i < tCount; i++) {
                string tLine;
                getline(fin, tLine);
                stringstream ss5(tLine);
                string sIdStr, sName, tScoreStr, aScoreStr, rankStr, scoresStr;
                getline(ss5, sIdStr, ',');
                getline(ss5, sName, ',');
                getline(ss5, tScoreStr, ',');
                getline(ss5, aScoreStr, ',');
                getline(ss5, rankStr, ',');
                getline(ss5, scoresStr, '\n');

                SingerScoreRecord record;
                record.singerId = stoi(sIdStr);
                record.singerName = sName;
                record.totalScore = stod(tScoreStr);
                record.averageScore = stod(aScoreStr);
                record.rank = stoi(rankStr);

                // 恢复 topTen 选手的各个评委细分 scoreList
                if (!scoresStr.empty()) {
                    stringstream ss6(scoresStr);
                    string t;
                    while (getline(ss6, t, '|')) {
                        if (t.empty()) continue;
                        size_t pos = t.find(':');
                        if (pos != string::npos) {
                            int jId = stoi(t.substr(0, pos));
                            double sc = stod(t.substr(pos + 1));
                            record.scoreList.append(Score(jId, sc));
                        }
                    }
                }
                m.topTen.append(record);
            }
            allMatches.append(m);
    	}
    fin.close();
    cout << "[成功] 比赛数据加载完毕。\n";
	}        
}
