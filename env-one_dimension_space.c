#include <stdlib.h>
#include "env-one_dimension_space.h"

typedef struct _state{
  int state_num;
  struct _state* next[2];
} state;

static int _num_of_state=0;
static state* _start;
static state* _agent_state;

int createEnv(int num_of_state){
  int i;

  /* 状態数は2以上あるか? */
  if(num_of_state < 2) return -1;

  /* スタートの状態を作成 */
  _start = (state*)malloc(sizeof(state));
  _start->state_num=0;
  _start->next[0]=NULL;
  _start->next[1]=NULL;

  /* 奇数個の状態数ならひとつ減らして偶数個にしておく */
  /* 奇数個の状態数なら関数の最後でひとつ加える(flag) */
  int flag_odd_state=0;
  if(num_of_state % 2 == 1){
    num_of_state--;
    flag_odd_state = 1;
  }

  state* target[2];
  target[0]=_start;
  target[1]=_start;
  for(i=0 ; i<num_of_state ; i=i+2){
    /* i-1とiの状態の外側に新しい状態を二つを作成 */
    target[0]->next[0]=(state*)malloc(sizeof(state));
    target[0]->next[0]->state_num=i+1;
    target[0]->next[0]->next[0]=NULL;
    target[0]->next[0]->next[1]=target[0];

    target[1]->next[1]=(state*)malloc(sizeof(state));
    target[1]->next[1]->state_num=i+2;
    target[1]->next[1]->next[0]=target[1];
    target[1]->next[1]->next[1]=NULL;

    target[0]=target[0]->next[0];
    target[1]=target[1]->next[1];
  }

  if(flag_odd_state==1){ /* 奇数個の状態だったならひとつ付け加える */
    target[0]->next[0]=(state*)malloc(sizeof(state));
    target[0]->next[0]->state_num=i+1;
    target[0]->next[0]->next[0]=NULL;
    target[0]->next[0]->next[1]=target[0];

    target[0]=target[0]->next[0];
  }

  setStartPos();
  return 0;
}

void destroyEnv(void){
  state* target=_start;
  /* まず状態の端まで移動 */
  while(target=NULL){
    target = target->next[0];
  }
  while(target=NULL){
    state* tmp=target;
    target = target->next[1];
    free(tmp);
  }
  return;
}

int setStartPos(void){
  _agent_state=_start;
  return _agent_state->state_num;
}

int judgeGoalPos(void){
  if(_agent_state->next[0] == NULL || _agent_state->next[1] == NULL){
    return 1;
  }else{
    return 0;
  }
}

int perceptive(void){
  return _agent_state->state_num;
}

/* act={0,1} */
int move(int act){
  if(act!=0 && act!=1){
    return -1;
  }

  if(_agent_state->next[act] != NULL){
    _agent_state = _agent_state->next[act];
  }

  return _agent_state->state_num;
}
