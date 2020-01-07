/* 1次元経路問題の環境作成, num_of_state:作成する状態数 */
int createEnv(int num_of_state);
/* 1次元経路問題の環境終了 */
void destroyEnv(void);
/* エージェントを初期状態にする */
int setStartPos(void);
/* judgeGoalPos:ゴール到達=1,それ以外=0 */
int judgeGoalPos(void);
/* 現状態の認識 */
int perceptive(void);
/* act:エージェントの行動{0:左移動,1:右移動}, 返り値:行動によって遷移した次状態 */
int move(int act);
