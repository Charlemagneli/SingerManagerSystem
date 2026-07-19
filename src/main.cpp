#include <iostream>
#include "SystemManager.h"
using namespace std;

// ==================== 菜单界面声明 ====================
void MainMenu();
void singerMenu(SystemManager& manager);
void judgeMenu(SystemManager& manager);
void matchMenu(SystemManager& manager);
void queryMenu(SystemManager& manager);

// ==================== 主函数 ====================
int main() {
    SystemManager manager;

    cout << "============================================\n";
    cout << "          正在初始化系统与历史数据...       \n";
    cout << "============================================\n";
    // 加载全局的基础歌手和评委数据
    manager.loadData();
    
    int choice;
    while (true) {
        MainMenu();
        cin >> choice;

        // 输入检查：防止用户输入非数字导致死循环
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n'); 
            cout << "【输入错误】请输入有效的数字编号！\n";
            continue;
        }

        switch (choice) {
            case 1: singerMenu(manager); break;
            case 2: judgeMenu(manager); break;
            case 3: matchMenu(manager); break;
            case 4: manager.operateMatch(); break; // 模拟打分与排序
            case 5: manager.MatchDetails(); break; // 浏览打分与十佳
            case 6: queryMenu(manager); break;
            case 0:
                cout << "\n============================================\n";
                cout << "             正在同步保存系统数据...        \n";
                cout << "============================================\n";
                manager.saveData();
                cout << "【退出】数据保存完毕。感谢使用歌手比赛管理系统，再见！\n";
                return 0;
            default:
                cout << "【输入错误】请在 0-6 之间进行选择。\n";
                break;
        }
    }
}

// 主菜单
void MainMenu() {
    cout << "\n============================================\n";
    cout << "             歌手比赛管理系统            \n";
    cout << "============================================\n";
    cout << "  [1] 歌手信息管理 (录入/修改/删除/浏览)\n";
    cout << "  [2] 评委信息管理 (录入/修改/删除/浏览)\n";
    cout << "  [3] 比赛场次管理 (新建/修改/删除/浏览)\n";
    cout << "  [4] 模拟比赛运行 (评委打分/成绩计算)\n";
    cout << "  [5] 比赛赛况查看 (成绩明细/排行榜单)\n";
    cout << "  [6] 综合查询中心 (精确/模糊/跨场次统计)\n";
    cout << "  [0] 保存数据并退出系统\n";
    cout << "============================================\n";
    cout << "请输入您的选择 (0-6): ";
}

// 歌手管理子菜单
void singerMenu(SystemManager& manager) {
    int choice;
    while (true) {
        cout << "\n--- 歌手信息管理 ---\n";
        cout << " [1] 录入/追加新歌手\n";
        cout << " [2] 修改歌手信息\n";
        cout << " [3] 删除歌手信息\n";
        cout << " [4] 浏览全部歌手列表\n";
        cout << " [0] 返回主菜单\n";
        cout << "请选择操作: ";
        cin >> choice;
        
        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }

        switch (choice) {
            case 1: manager.addSinger(); break;
            case 2: manager.modifySinger(); break;
            case 3: manager.deleteSinger(); break;
            case 4: manager.viewSingers(); break;
            case 0: return;
            default: cout << "【提示】无效选择。\n";
        }
    }
}

// 评委管理子菜单 
void judgeMenu(SystemManager& manager) {
    int choice;
    while (true) {
        cout << "\n--- 评委信息管理 ---\n";
        cout << " [1] 录入/追加新评委\n";
        cout << " [2] 修改评委信息\n";
        cout << " [3] 删除评委信息\n";
        cout << " [4] 浏览全部评委列表\n";
        cout << " [0] 返回主菜单\n";
        cout << "请选择操作: ";
        cin >> choice;

        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }

        switch (choice) {
            case 1: manager.addJudge(); break;
            case 2: manager.modifyJudge(); break;
            case 3: manager.deleteJudge(); break;
            case 4: manager.viewJudges(); break;
            case 0: return;
            default: cout << "【提示】无效选择。\n";
        }
    }
}

// 比赛管理子菜单
void matchMenu(SystemManager& manager) {
    int choice;
    while (true) {
        cout << "\n--- 比赛场次管理 ---\n";
        cout << " [1] 新建比赛场次\n";
        cout << " [2] 修改比赛时间\n";
        cout << " [3] 删除比赛场次\n";
        cout << " [4] 查看全部场次\n";
        cout << " [0] 返回主菜单\n";
        cout << "请选择操作: ";
        cin >> choice;

        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }

        switch (choice) {
            case 1: manager.createMatch(); break;
            case 2: manager.modifyMatch(); break;
            case 3: manager.deleteMatch(); break;
            case 4: manager.viewMatches(); break;
            case 0: return;
            default: cout << "【提示】无效选择。\n";
        }
    }
}

// 综合查询子菜单
void queryMenu(SystemManager& manager) {
    int choice;
    while (true) {
        cout << "\n--- 综合查询中心 ---\n";
        cout << " [1] 查找歌手\n";
        cout << " [2] 查找评委\n";
        cout << " [3] 歌手跨场次成绩汇总 (历史参赛统计)\n";
        cout << " [4] 评委跨场次打分汇总 (历史参评统计)\n";
        cout << " [0] 返回主菜单\n";
        cout << "请选择查询类型: ";
        cin >> choice;

        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }

        switch (choice) {
            case 1: manager.searchSinger(); break;  // 可实现模糊查询
            case 2: manager.searchJudge(); break;   // 可实现模糊查询
            case 3: manager.querySinger(); break;   // 跨场次 
            case 4: manager.queryJudge(); break;    // 跨场次
            case 0: return;
            default: cout << "【提示】无效选择。\n";
        }
    }
}
