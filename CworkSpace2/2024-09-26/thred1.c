//스레드 이진트리는 일반적인 이진 탐색 트리의 변형이다.
//트리의 자식 노드뿐만 아니라,중위 순회에서 선행자와 후속자를 가리키도록 하는 구조이다.
//이로 인하여 트리의 순회를 효율적으로 수행할수 있도록 돕는다.
#include <stdio.h>
#include <stdlib.h>
//1.스레드포인터: 일반 적인 이진 트리에서는 각 노드가 두개의 자식포인터 즉 오른쪽 왼쪽을 가집니다.
//2.그러나 많은 경우 이 포인터들은 null이 됩니다. 이러한 null포인터를 쓰레드 이진트리는 중위 순휘에서 
//선행자나 후속자를 가리키도록 설정합니다.
//왼쪽 스레드(ithread):왼쪽 포인터가 null인 경우 중위순회에서 선행자를 가르킵니다.
//오른쪽 스레드 (rthead):오른쪽 포인터가 null인 경우 이포인터는 중위순회에서 후속자를 가리킵니다.
//이러한 구조를 가진 쓰레드 이진트리는 중위 순회를 수행할때 스택이나,재귀 호출 없이도 순회를 수행할수 있습니다.
//따라서 메모리 사용을 줄이고 순회시의 성능을 개선하는데 중요합니다.

  typedef struct TreeNode {
      int data;
      struct TreeNode *left, *right;
      int lthread, rthread; // 스레드 플래그: 1이면 스레드, 0이면 자식 노드
  } TreeNode;

  void InOrderTraversalThreaded(TreeNode* root) {
    //쓰레드 이진 탐색 트리에서 중위 순회를 수행하는 함수.
      if (root == NULL) return;

      
      TreeNode* ptr = root;
      //중위 순회 시작. 가장 왼쪽 노드로 이동해야함.
      while (ptr->lthread == 0) {
        //왼쪽 스레드가  0일동안 
          ptr = ptr->left;
          //왼쪽 자식으로 계속이동합니다.

      }

      // 본격적인 중위 순회
      while (ptr != NULL) {
          printf("%d ", ptr->data);
          //현재 노드의 데이터를 출력합니다.
          //중위 순회는 왼쪽 자식,현재,오른쪽 자식으로 방문합니다. 
          if (ptr->rthread == 1) {
              ptr = ptr->right;
              //현재 노드의 오른쪽 포인터가 스레드 인경우.(1인 경우)
              //이는 중위순회에서 후속자를 가르킨다. 따라서 ptr을 right로 이동하여 다음 노드로 이동합니다.
          } else {
              // 오른쪽 서브트리의 가장 왼쪽 노드로 이동
              ptr = ptr->right;
              while (ptr != NULL && ptr->lthread == 0) {
                //ptr에 값이 없거나 레프트쓰레드노드가 0이될떄 까지.(스레드가 아닌경우.)
                  ptr = ptr->left;
                  //오른쪽 서브트리의 가장 왼쪽 노드로 이동.
              }
          }
      }
  }