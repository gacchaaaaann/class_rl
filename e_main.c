// gcc -o HOGE -DSFMT_MEXP=19937 e_main.c SFMT/SFMT.c env-one_dimension_space.c reward_function.c

#include <stdio.h>
#include <stdlib.h>
#include "env-one_dimension_space.h"
#include "reward_function.h"
#include "SFMT/SFMT.h"

#define NUM_STATE 6 /* 0(start)を除いた環境の状態数 */
#define NUM_TRIAL 100 /* 試行回数 */

#define ALPHA 0.1 //パラメータα
#define GAMMA 0.9 //パラメータγ
#define E 0.05 //パラメータε

double max_Q(double state[]); //double一次元配列(要素数2)の最大値を返す

int main(){

  sfmt_t sfmt; //sfmt実体の生成

  sfmt_init_gen_rand(&sfmt, 17024124);

  int i,j;
  int now_state,now_act,next_state;
  double reward,total_reward=0,ran_d;
  double Q[NUM_STATE+1][2]; //価値関数

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
    
    /* 報酬の総和を0に初期化する */
    total_reward = 0;

	  /* j行動 */
	  for(j=1; !judgeGoalPos() ; j++){ /* judgeGoalPos:ゴール到達=1,それ以外=0 */
	    /* 1行動のプロセス:現状態の認識・行動決定・行動(とそれによって次状態に変化)・報酬獲得 */

		  /* 現状態の認識 */
		  now_state = perceptive();
  		//printf("--%3d試行---%3d行動-------\n",i,j);
  		//printf("現状態:%d\n", now_state);

		  /* 現状態に対する行動決定 */
      ran_d = sfmt_genrand_real1(&sfmt);  //0~1の乱数
      //printf("ran_d = %lf\n", ran_d);
      if(ran_d<E){  //Eの確率で前者を実行
          now_act = sfmt_genrand_uint32(&sfmt) % 2; //ランダムで次の行動を選ぶ

      }else{
          if(Q[now_state][0]==Q[now_state][1]){ //価値関数が同じ時，前者
              now_act = sfmt_genrand_uint32(&sfmt) % 2; //ランダムで次の行動を選ぶ

          }else{
              now_act = Q[now_state][0]>Q[now_state][1] ? 0 : 1;  //価値関数が大きい方を選ぶ
              
          }  
      }

  		//printf("行動番号の入力[0,1]:%d\n\n", now_act);
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
      //printf("Q[%3d][%3d]=%lf\n\n", now_state, now_act, Q[now_state][now_act]); //更新した価値関数の表示
  		/* 結果を見えやすくするための改行 */
  		//printf("\n\n");
	  }

    //printf("ゴール到達！\n");
    //printf("ゴール到達までの行動回数:%d\n\n",j-1);
    

    //結果の出力(データをまとめる用)(試行数 行動回数 報酬の総和 価値関数((NUM_STATE+1)*2)
    printf("%d %d %lf",i,j-1,total_reward);

    for(int i=0; i<=NUM_STATE; i++){  //価値関数全体の表示
      printf(" %lf %lf", Q[i][0], Q[i][1]);
    }
    /**/

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
