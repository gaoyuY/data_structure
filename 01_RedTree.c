/*************************************************************************
	> File Name: 4_红黑树.c
	> Author: GaoYu
	> Mail:2282940822@qq.com 
	> Created Time: 2019年02月18日 星期一 15时45分19秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct RBTNode {
    int key, color; //0 red, 1 black, 2 double black
    struct RBTNode *lchild, *rchild;
} RBTNode;

RBTNode *NIL;
__attribute__((constructor)) //先于主函数执行
void init_NIL() {  //虚拟节点
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->lchild = NIL->rchild = NIL;
    NIL->color = 1;
    NIL->key = -1;
    return ;
}

RBTNode *getNewNode (int key) {
    RBTNode *p = (RBTNode *)malloc(sizeof(RBTNode));
    p->lchild = p->rchild = NIL;
    p->key = key;
    p->color = 0; //新插入的节点一定为红色(red)
    return p;
}

int has_red_child (RBTNode *root) {
    return (root->lchild->color == 0 || root->rchild->color == 0);
}

RBTNode *left_rotate(RBTNode *root) {
    RBTNode *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

RBTNode *right_rotate(RBTNode *root) {
    RBTNode *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

//插入转换为uncle节点为红色，并且父节点为红色且有红孩子时，父亲与红孩子同侧　
RBTNode *insert_maintain(RBTNode *root) {//插入调整
    if (!has_red_child(root)) return root;
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) return root;//父节点为红,但没有红孩子
    } else if (root->lchild->color == 0 && has_red_child(root->lchild)) { //uncle = １即 root->rchild->color == 1
        if (root->lchild->rchild->color == 0) {
            root->lchild = left_rotate(root->lchild);//转换成父亲与红孩子同边
        }
        root = right_rotate(root);//转换成uncle为红色
    } else if (root->rchild->color == 0 && has_red_child(root->rchild)) { //uncle = 1 即 root->lchild->color == 1
        if (root->rchild->lchild->color == 0) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    } else {//　uncle == 0 
        return root;
    }
    root->color = 0;//　红色上顶
    root->lchild->color = root->rchild->color = 1;
    /*root->color = 1; //红色下沉
     root->lchild->color = root->rchild->color = 0;
     */
    return root;
}

RBTNode *__insert(RBTNode *root, int key) {//根据二叉排序树性质插入
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    else if (root->key > key) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

RBTNode *insert (RBTNode *root, int key) {
    root = __insert(root, key);
    root->color = 1;
    return root;
}

//找前驱节点
RBTNode *predecessor(RBTNode *root) {
    RBTNode *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}


//删除调整
RBTNode *erase_maintain(RBTNode *root) {
    if (root->lchild->color != 2 && root->rchild->color != 2)  return root;//没有双重黑时，直接返回root
    #define UNBALANCE(a, b) (root->a->color == 2 && !has_red_child(root->b) && root->b->color == 1)
    //宏定义替换，a为双重黑时，brother节点为黑色, 且brother节点没有红孩子　
    if (UNBALANCE(lchild, rchild) || UNBALANCE(rchild, lchild)) {//符合宏定义时，直接该颜色，
        root->color += 1;    //根节点颜色+１
        root->lchild->color -= 1; //左右孩子均-１
        root->rchild->color -= 1;
        return root;
    }
    #undef UNBALANCE
    if (root->lchild->color == 2) {//左孩子为双重黑
        if (root->rchild->color == 0) {//brother节点为红色,且brother节点没有红孩子
            root = left_rotate(root);
            root->color = 1;
            root->lchild->color = 0;
            //return erase_maintain(root->lchild);
            root->lchild = erase_maintain(root->lchild);
            return root;
        }
        //brother节点为黑色,且brother节点有红孩子
        root->lchild->color = 1;//先将双重黑变成黑色，然后做调整  (1)
        if (root->rchild->rchild->color != 0) {//RL型  (brother在右子树) brother节点的右孩子不为红
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = 1;
            root->rchild->rchild->color = 0;
            //RL型已经转换成了RR型
        } 
        //RR型做调整
        root = left_rotate(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = 1;
        return root;
    } else {//右孩子为双重黑
        if (root->lchild->color == 0) {//(brother在左子树) brother节点为红色,且brother节点没有红孩子
            root = right_rotate(root);
            root->color = 1;
            root->rchild->color = 0;
            root->rchild = erase_maintain(root->rchild);
            return root;
        }
        root->rchild->color = 1;//先将双重黑变成黑色，然后做调整　(1)
        if (root->lchild->lchild->color != 0) { //LR型  (brother在左子树) brother节点的左孩子不为红
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
            root->lchild->lchild->color = 0;
            //LR型已经转换为LL型
        }
        //LL型做调整
        root = right_rotate(root);
        root->color = root->rchild->color;//新根改为旧根颜色
        root->lchild->color = root->rchild->color = 1;//左右孩子均变为黑色
        return root;
    }
}

RBTNode *__erase(RBTNode *root, int key) {
    if (root == NIL) return NIL;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            RBTNode *temp = (root->lchild != NIL ? root->lchild : root->rchild);
            temp->color += root->color;
            free(root);
            return temp;
        } else { // 度为２时
            RBTNode *temp = predecessor(root); //找前驱
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}


RBTNode *erase (RBTNode *root, int key) {
    root = __erase(root, key);
    root->color = 1;
    return root;
}

void output (RBTNode *root) {
    if (root == NIL) return;
    printf ("(%d, %d, %d) = %d\n", root->key, root->lchild->key, root->rchild->key, root->color);
    output(root->lchild);
    output(root->rchild);
}


void clear(RBTNode *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int main () {
    RBTNode *root = NIL;
    int op, val;
    while (scanf ("%d %d", &op, &val) != EOF) {
        switch (op) {
            case 0 : {
                printf ("(insert %d to RBTree)\n", val);
                root = insert(root, val);
            } break;
            case 1 : {
                printf ("(delete %d from RBTree)\n", val);
                root = erase(root, val);
            } break;
        }
        output(root);
        printf ("\n");
    }
    return 0;
}
