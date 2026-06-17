#include <graphics.h>

// 棋盘全局变量
char board_data[3][3] = {
    {'-', '-', '-'},
    {'-', '-', '-'},
    {'-', '-', '-'}
};

// 当前棋子
char currentPiece = 'O';

// 检验指定棋子玩家是否获胜
bool CheckWin(char c) {
    if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c) return true;
    if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c) return true;
    if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c) return true;
    if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c) return true;
    if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c) return true;
    if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c) return true;
    if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c) return true;
    if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c) return true;
    return false;
}

// 检验当前是否出现平局
//bool CheckDraw() {
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            if (board_data[i][j] == '-') {
//                return false;
//            }
//        }
//    }
//    return true;
//}

// 绘制棋盘网格
void DrawBoard() {
    line(0, 200, 600, 200);
    line(0, 400, 600, 400);
    line(200, 0, 200, 600);
    line(400, 0, 400, 600);
}

// 绘制棋子
void DrawPiece() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board_data[i][j] == 'O') {
                circle(i * 200 + 100, j * 200 + 100, 50);
            }
            else if(board_data[i][j] == 'X') {
                line(i * 200 + 50, j * 200 + 50, i * 200 + 150, j * 200 + 150);
                line(i * 200 + 150, j * 200 + 50, i * 200 + 50, j * 200 + 150);
            }
        }
    }
}

// 绘制提示信息
void DrawTipText() {
    static TCHAR str[64];
    swprintf_s(str, _T("当前玩家: %c"), currentPiece);
    settextcolor(RGB(225, 175, 45));
    outtextxy(0, 0, str);
}

int main() {
    initgraph(600, 600);
    bool running = true;
    ExMessage msg;
    BeginBatchDraw();
    // 步数
    int count = 0;
    while (running) {
        while (peekmessage(&msg)) {
            // 检测鼠标点击事件
            if (msg.message == WM_LBUTTONDOWN) {
                // 计算点击位置
                int index_x = msg.x / 200; // 每个格子宽度为200
                int index_y = msg.y / 200; // 每个格子高度为200

                // 尝试落子
                if(board_data[index_x][index_y] == '-') {
                    board_data[index_x][index_y] = currentPiece;
                    count++;
                    currentPiece = (currentPiece == 'O') ? 'X' : 'O';
                }
            }
        }

        cleardevice();
        DrawBoard();
        DrawPiece();
        DrawTipText();
        FlushBatchDraw();

        if (CheckWin('X')) {
            MessageBox(GetHWnd(), _T("X wins!"), _T("Game Over"), MB_OK);
            running = false;
        }
        else if (CheckWin('O')) {
            MessageBox(GetHWnd(), _T("O wins!"), _T("Game Over"), MB_OK);
            running = false;
        }
        else if (count == 9) {
            MessageBox(GetHWnd(), _T("Draw!"), _T("Game Over"), MB_OK);
            running = false;
        }

    }
    EndBatchDraw();
    return 0;
}