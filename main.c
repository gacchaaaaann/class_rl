#include <stdio.h>
#include "env-one_dimension_space.h"
#include "reward_function.h"

#define NUM_STATE 6 /* 0(start)を除いた環境の状態数 */
#define NUM_TRIAL 3 /* 試行回数 */

int main(){
  int i,j;
  int now_state,now_act,next_state;
  double reward;

  /* 1次元経路問題の環境作成 */
  createEnv(NUM_STATE);
  createRewardFunction(NUM_STATE);

  /* i試行 */
  for(i=1 ; i<=NUM_TRIAL ; i++){
    /* 1試行のプロセス:初期状態からゴールするまで */

    /* エージェントを初期状態にする */
    setStartPos();

	  /* j行動 */
	  for(j=1; !judgeGoalPos() ; j++){ /* judgeGoalPos:ゴール到達=1,それ以外=0 */
	    /* 1行動のプロセス:現状態の認識・行動決定・行動(とそれによって次状態に変化)・報酬獲得 */

		  /* 現状態の認識 */
		  now_state = perceptive();
  		printf("--%3d試行---%3d行動-------\n",i,j);
  		printf("現状態:%d\n", now_state);

		  /* 現状態に対する行動決定 */
  		printf("行動番号の入力[0,1]:");
	    scanf("%d",&now_act);
  		printf("-----------結果-----------\n");

      /* 現行動(とそれによって次状態に変化) */
	    next_state = move(now_act);

      /* 報酬獲得 */
	    reward = rewardFunction(now_state,now_act, next_state);

      /* 学習 */

      /* 結果の表示 */
	    printf("現状態:%3d\t", now_state);
	    printf("現行動:%3d\t", now_act);
  		printf("次状態:%3d\t", next_state);
  		printf("報酬:%lf\n", reward);
  		/* 結果を見えやすくするための改行 */
  		printf("\n\n");
	  }

    printf("ゴール到達！\n");
    printf("ゴール到達までの行動回数:%d\n\n",j-1);
  }

  /* 1次元経路問題の環境終了 */
  destroyEnv();
  destroyRewardFunction();
  return 0;
}
