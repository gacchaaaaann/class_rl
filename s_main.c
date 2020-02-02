// gcc -o HOGE main.c env-one_dimension_space.c reward_function.c

#include <stdio.h>
#include <math.h>
#include "env-one_dimension_space.h"
#include "reward_function.h"
#include "SFMT/SFMT.h"

#define NUM_STATE 6 /* 0(start)を除いた環境の状態数 */
#define NUM_TRIAL 100 /* 試行回数 */

#define ALPHA 0.1 //パラメータα
#define GAMMA 0.9 //パラメータγ
#define TAU 0.3 //パラメータτ

double max_Q(double state[]); //double一次元配列(要素数2)の最大値を返す
int softmax(int state, double Q[][2], sfmt_t *sfmt); //softmax法で行動を選択する

int main(){
  int i,j;
  int now_state,now_act,next_state;
  double reward, total_reward;
  double Q[NUM_STATE+1][2]; //価値関数

  sfmt_t sfmt;
  sfmt_init_gen_rand(&sfmt, 17024124);


  for(int i=0; i<=NUM_STATE; i++){  //価値関数の初期化(NUM_STATEの変更に対応するため，配列定義時ではなく，改めてfor文を回す)
    Q[i][0] = 0;
    Q[i][1] = 0;
  }

  /* 1次元経路問題の環境作成 */
  createEnv(NUM_STATE);
  createRewardFunction(NUM_STATE);

  /* i試行 */
  for(i=1 ; i<=NUM_TRIAL ; i++){
    /* 1試行のプロセス:初期状態からゴールするまで */

    /* エージェントを初期状態にする */
    setStartPos();

    total_reward = 0;

	  /* j行動 */
	  for(j=1; !judgeGoalPos() ; j++){ /* judgeGoalPos:ゴール到達=1,それ以外=0 */
	    /* 1行動のプロセス:現状態の認識・行動決定・行動(とそれによって次状態に変化)・報酬獲得 */

		  /* 現状態の認識 */
		  now_state = perceptive();
  		//printf("--%3d試行---%3d行動-------\n",i,j);
  		//printf("現状態:%d\n", now_state);

      now_act = softmax(now_state, Q, &sfmt);

		  /* 現状態に対する行動決定 */
  		//printf("-----------結果-----------\n");

      /* 現行動(とそれによって次状態に変化) */
	    next_state = move(now_act);

      /* 報酬獲得 */
	    reward = rewardFunction(now_state,now_act, next_state);
      total_reward += reward;

      /* 学習 */
      Q[now_state][now_act] = Q[now_state][now_act] + ALPHA*(reward + GAMMA*max_Q(Q[next_state]) - Q[now_state][now_act]);  //価値関数の更新

      /* 結果の表示 */
	    //printf("現状態:%3d\t", now_state);
	    //printf("現行動:%3d\t", now_act);
  		//printf("次状態:%3d\t", next_state);
  		//printf("報酬:%lf\n", reward);
      //printf("Q[%3d][%3d]=%lf\n", now_state, now_act, Q[now_state][now_act]); //更新した価値関数の表示
  		/* 結果を見えやすくするための改行 */
  		//printf("\n\n");
	  }

    //printf("ゴール到達！\n");
    //printf("ゴール到達までの行動回数:%d\n\n",j-1);

//    for(int i=0; i<=NUM_STATE; i++){  //価値関数全体の表示
//      printf("%lf %lf\n", Q[i][0], Q[i][1]);
//    }

    printf("%d %d %lf ",  i, j-1, total_reward); 

    for(int i=0; i<=NUM_STATE; i++){  //価値関数全体の表示
      printf("%lf %lf ",  Q[i][0], Q[i][1]);
    }

    printf("\n");
      
  }

  /* 1次元経路問題の環境終了 */
  destroyEnv();
  destroyRewardFunction();
  return 0;
}



double max_Q(double state[]){ //double一次元配列(要素数2)の最大値を返す

  return state[0]>state[1] ? state[0] : state[1];
  
}



int softmax(int state, double Q[][2], sfmt_t *sfmt){ //softmax法で行動を選択する

  double e0 = exp(Q[state][0]/TAU);
  double e1 = exp(Q[state][1]/TAU);
  double p = e0 / (e0+e1);

  return sfmt_genrand_real1(sfmt)<p ? 0 : 1;
    
}
