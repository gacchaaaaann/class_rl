#include <stdlib.h>
#include "reward_function.h"

static int state_num_=0;
static double *for_V;

int createRewardFunction(int state_num){
	int i;
	if(state_num < 2) return -1;

	state_num_ = state_num;
	for_V = (double*)malloc(sizeof(double)*(state_num+1));

	for(i=0 ; i<=state_num ; i++){
		for_V[i]=0;
	}

	/* ゴール地点に対する報酬 */
	for_V[state_num]=10.0;
	for_V[state_num-1]=-10.0;
	return 0;
}

int destroyRewardFunction(){
	if(for_V==NULL) return 0;
	free(for_V);
	return 0;
}

double rewardFunction(int now_state, int now_act, int next_state){
	if(next_state>state_num_) return -1;

	return for_V[next_state];
}
