#include<stdio.h>
#include<stdlib.h>

//����
#define PROCESS_NAME_LEN 32     //����������
#define MIN_SLICE 10            //��С��Ƭ��С
#define DEFAULT_MEM_SIZE 1024   //�ڴ��С
#define DEFAULT_MEM_START 0     //��ʼλ��

//���䵽�ڴ�������
struct get_block {
    int pid;
    int size;
    int start_addr;
    char process_name[PROCESS_NAME_LEN];
    struct get_block* next;
};

//�ڴ���з���
struct free_block {
    int size;
    int start_addr;
    struct free_block* next;
};


//�ڴ�����㷨
#define MA_FF 1
#define MA_BF 2
#define MA_WF 3

int mem_size = DEFAULT_MEM_SIZE;    //�ڴ��С
int ma_algorithm = MA_FF;           //��ǰ�㷨
static int pid = 0;                 //��ʼ��pid
int flag = 0;                       //�����ڴ��С��־

//��������
int display_menu(void);         //չʾ���ܲ˵�
int set_mem_size(void);         //���������ڴ�ռ��С
int set_algorithm(void);        //�����㷨
int rearrange_FF(void);         //�״������㷨
int rearrange_BF(void);         //���������㷨
int rearrange_WF(void);         //������㷨

int kill_process(void);         //ɾ�����̣��黹����Ĵ���ռ�
int do_exit(void);              //�˳������ͷſռ�
int display_mem_usage(void) ;   //��ʾ��ǰ�ڴ��ʹ��������������������Ѿ���������
int rearrange(int algorithm) ;              //ѡ���㷨


int free_mem(struct get_block *ab);     //�ͷ�����
int allocate_mem(struct get_block *ab);     //�����ڴ�ģ��
int dispose(struct get_block* free_ab);     //����free�������

int FF(void);           //����ַ�ɵ͵�������
int BF(void);           //���ڴ��С��С��������
int WF(void);           //���ڴ��С�ɴ�С����
struct get_block* find_process(int pid);            //��pid�ҵ���Ҫ�ͷŵ�����ڵ�
struct free_block* init_free_block(int mem_size);   //��ʼ�����п�


struct free_block* free_b;//�ڴ���п����������ָ��



struct get_block* get_block_head = NULL; //���̷����ڴ���������ָ��

struct free_block*  init_free_block(int mem_size) {
    struct free_block *fb,*ptemp;
    get_block_head = (struct get_block*)malloc(sizeof(struct get_block));
    fb = (struct free_block*)malloc(sizeof(struct free_block));
    ptemp=(struct free_block*)malloc(sizeof(struct free_block));
    if (fb == NULL) {
        printf("No nen \n");
    }
    get_block_head->next=NULL;
    fb->next=ptemp;
    ptemp->size = mem_size;
    ptemp->start_addr = DEFAULT_MEM_START;
    ptemp->next = NULL;
    return fb;
}

int  display_menu()
{
    printf("\n");
    printf("1- Set memory size (%d)\n",mem_size);
    printf("2- Select memory size allocation algorithm \n");
    printf("3- New process \n");
    printf("4- Terminate a process \n");
    printf("5- Display memory usage \n");
    printf("0- Exit\n");
    return 1;
}

int set_mem_size() {
    int size;
    if (flag != 0) {//��ֹ�ظ�����
        printf("Cannot set memory size again\n");
        return 0;
    }
    printf("Total memory size =");
    scanf("%d", &size);
    if (size>0) {
        mem_size = size;
        free_b->next->size = mem_size;
    }
    flag = 1;
    return 1;
}
int FF(){
    struct free_block* fbh=free_b->next;
    struct free_block* fbp=free_b->next;
    int sizep;
    int addrp;
    while(fbh!=NULL){
        while(fbp->next!=NULL){
                if(fbp->start_addr>fbp->next->start_addr){
                    addrp=fbp->start_addr;
                    fbp->start_addr=fbp->next->start_addr;
                    fbp->next->start_addr=addrp;
                    sizep=fbp->size;
                    fbp->size=fbp->next->size;
                    fbp->next->size=sizep;
                }
                fbp=fbp->next;
        }
        fbp=free_b->next;
        fbh=fbh->next;
    }
    while(fbh!=NULL){
        printf("%d,%d",fbh->size,fbh->start_addr);
        fbh=fbh->next;
    }
    return 0;
}

int rearrange_FF() {
    FF();
    return 0;
}

int BF(){
    struct free_block* fbh=free_b->next;
    struct free_block* fbp=free_b->next;
    int sizep;
    int addrp;
    while(fbh!=NULL){
        while(fbp->next!=NULL){
                if(fbp->size>fbp->next->size){
                    addrp=fbp->start_addr;
                    fbp->start_addr=fbp->next->start_addr;
                    fbp->next->start_addr=addrp;
                    sizep=fbp->size;
                    fbp->size=fbp->next->size;
                    fbp->next->size=sizep;
                }
                fbp=fbp->next;
        }
        fbp=free_b->next;
        fbh=fbh->next;
    }
    while(fbh!=NULL){
        printf("%d,%d",fbh->size,fbh->start_addr);
        fbh=fbh->next;
    }
    return 0;
}

int rearrange_BF() {
    BF();
    return 0;
}

int WF(){
    struct free_block* fbh=free_b->next;
    struct free_block* fbp=free_b->next;
    int sizep;
    int addrp;
    while(fbh!=NULL){
        while(fbp->next!=NULL){
                if(fbp->size<fbp->next->size){
                    addrp=fbp->start_addr;
                    fbp->start_addr=fbp->next->start_addr;
                    fbp->next->start_addr=addrp;
                    sizep=fbp->size;
                    fbp->size=fbp->next->size;
                    fbp->next->size=sizep;
                }
                fbp=fbp->next;
        }
        fbp=free_b->next;
        fbh=fbh->next;
    }
    while(fbh!=NULL){
        printf("%d,%d",fbh->size,fbh->start_addr);
        fbh=fbh->next;
    }
    return 0;
}

int rearrange_WF() {
    WF();
    return 0;
}

int rearrange(int algorithm) {
    switch (algorithm) {
    case MA_FF: rearrange_FF(); break;
    case MA_BF:rearrange_BF(); break;
    case MA_WF:rearrange_WF(); break;
    }
    return 0;
}

int set_algorithm() {
    int algorithm;
    printf("\t1 - First Fit \n");
    printf("\t2 - Best Fit \n");
    printf("\t3 - Worst Fit \n");
    scanf("%d", &algorithm);
    if (algorithm >= 1 && algorithm <= 3) {
        ma_algorithm = algorithm;
        //��ָ���㷨�������п���������
        rearrange(ma_algorithm);
    }
    return 0;
}

int allocate_mem(struct get_block *ab) {    //�����ڴ�ģ��
    struct free_block* fbt, *pre;
    int request_size = ab->size;
    fbt = pre = free_b->next;
    while(fbt!=NULL){
        if(fbt->size>=request_size){
            ab->start_addr=fbt->start_addr+fbt->size-request_size;
            fbt->size=fbt->size-request_size;
            return 1;
        }
        else {
            pre=fbt;
            fbt=fbt->next;
        }
    }
    printf("������������\n");
    return 0;
}

int new_process() {
    int size,ret;
    struct get_block *ab,*temp;
    ab = (struct get_block*)malloc(sizeof(struct get_block));
    temp=get_block_head->next;
    if (!ab) {
        exit(-5);
    }
    ab->next = NULL;
    pid++;
    sprintf(ab->process_name, "PROCESS-%02d", pid);
    ab->pid = pid;
    printf("Memory for %s:\n", ab->process_name);
    scanf("%d", &size);
    ab->size = size;
    ret = allocate_mem(ab);     //�ӿ����������ڴ棬ret==1��ʾ�������
    if ((ret == 1) && (get_block_head->next == NULL)) {//get_b_hû�и�ֵ�����и�ֵ
        get_block_head->next= ab;
        printf("ret==1");
        return 1;
    }
    else if (ret == 1) {
        printf("����ɹ�\n");
        while(temp->next!=NULL){
            temp=temp->next;
        }

        temp->next=ab;
        return 2;
    }
    else if (ret == -1) {
        printf("Allocation fail\n");
        free(ab);
        return 1;
    }
    return 3;
}

struct get_block* find_process(int pid){
    struct get_block* get_temp=get_block_head;
    while(get_temp!=NULL){
        if(get_temp->pid==pid){
            return get_temp;
        }
        else{
            get_temp=get_temp->next;
        }
    }
    printf("��������\n");
    return NULL;
}

int free_mem(struct get_block *ab) {
    int algorithm = ma_algorithm;
    struct free_block *fbt, *pre, *work;
    fbt = (struct free_block*) malloc(sizeof(struct free_block));
    if (!fbt) return -1;
    // ���п��ܵĺϲ���������������
    // 1. �����ͷŵĽ����뵽���з�������ĩβ
    // 2. �Կ��������յ�ַ��������
    // 3. ��鲢�ϲ����ڵĿ��з���
    // 4. �������������°��յ�ǰ�㷨����
    fbt->size=ab->size;
    fbt->start_addr=ab->start_addr;
    pre=free_b->next;
    while(pre->next!=NULL){
        pre=pre->next;
    }
    pre->next=fbt;
    fbt->next=NULL;
    FF();
    pre=free_b->next;
    while(pre->next!=NULL){
        if(pre->start_addr+pre->size==pre->next->start_addr){
            pre->size=pre->size+pre->next->size;
            if(pre->next->next!=NULL){
                pre->next=pre->next->next;
            }else{
                    pre->next=NULL;
                    break;
            }
        }
        pre=pre->next;
    }
    pre=free_b->next;
    while(pre->next!=NULL){
        if(pre->start_addr+pre->size==pre->next->start_addr){
            pre->size=pre->size+pre->next->size;
            if(pre->next->next!=NULL){
                pre->next=pre->next->next;
            }else{
                    pre->next=NULL;
                    break;
            }
        }
        pre=pre->next;
    }
    printf("�ڴ�������");
    rearrange(ma_algorithm);
    return 1;
}

int dispose(struct get_block* free_ab){
    struct get_block *pre, *ab;
    if (free_ab == get_block_head) {//���Ҫ�ͷŵ�һ���ڵ�
        get_block_head = get_block_head->next;
        free(free_ab);
        return 1;
    }
    pre = get_block_head;
    ab = get_block_head->next;
    while (ab != free_ab) {
        pre = ab;
        ab = ab->next;
    }
    pre->next = ab->next;
    free(ab);
    return 2;
}

int display_mem_usage() {//��ʾ��ǰ�ڴ��ʹ��������������������Ѿ���������
    struct free_block *fbt = free_b->next;
    struct get_block *ab = get_block_head->next;

    if (fbt == NULL) return 1;
    printf("------------------------------------\n");

    //��ʾ������
    printf("Free Memory:\n");
    while(fbt!=NULL){
        printf("%20d%20d\n", fbt->start_addr, fbt->size);
        fbt = fbt->next;
    }
    //��ʾ�ѷ�����
    printf("\nUsed Memory:\n");
    printf("%10s %20s %10s %10s \n", "PID", "ProcessName    ", "start_addr", "size");
    while (ab != NULL) {
        printf("%10d %20s %10d %10d \n",ab->pid,ab->process_name,ab->start_addr,ab->size);
        ab = ab->next;
    }
    printf("------------------------------------------\n");
    return 0;
}
int kill_process() {//ɾ�����̣��黹����Ĵ���ռ�
                    //��ɾ�������ý��̵��ڴ����Ľڵ�
    struct get_block *ab;
    int pid;
    printf("Kill Process , pid =");
    scanf("%d",&pid);
    ab = find_process(pid);
    if (ab != NULL) {
        free_mem(ab);//�ͷ�ab��ʾ�ķ�����
        dispose(ab);//�ͷ�ab���ݽṹ�Ľڵ�
    }
    return 0;
}
int do_exit() {
    struct get_block *temp;
    while (get_block_head != NULL) {
        temp = get_block_head;
        get_block_head = get_block_head->next;
        free(temp);
    }
    return 0;
}
int main() {
    char choice;
    pid = 0;
    free_b = init_free_block(mem_size);//��ʼ��������
    while (1) {
        display_menu();//��ʾ�˵�
        fflush(stdin);
        choice = getchar();//��ȡ�û�����
        switch (choice) {
        case'1':set_mem_size();flag=1;break;        //�����ڴ��С
        case'2':set_algorithm(); flag = 1; break;   //�����㷨
        case'3':new_process(); flag = 1; break;     //�����½���
        case'4':kill_process(); flag = 1; break;    //ɾ������
        case'5':display_mem_usage(); flag = 1; break;//��ʾ�ڴ�ʹ��
        case'0': do_exit(); exit(0);                //�ͷ������˳�
        default:break;
        }
    }
}
