int createRewardFunction(int state_num);
int destroyRewardFunction();
/* now_state:現状態, now_act:現行動, next_state:行動によって遷移した次状態, 返り値:報酬 */
double rewardFunction(int now_state, int now_act, int next_state);
