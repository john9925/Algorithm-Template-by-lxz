void ini()
{
    head=-1,idx=1;
}
void add_to_head(int x)
{
    e[idx]=x,ne[idx]=head,head=idx++;
}
void add(int k,int x)//第k个数后插入
{
    e[idx]=x,ne[idx]=ne[k],ne[k]=idx++;
}
void remove(int k)
{
    ne[k]=ne[ne[k]];
}
//双链表
// 在节点a的右边插入一个数x
void insert(int a, int x)
{
    e[idx] = x;
    l[idx] = a, r[idx] = r[a];
    l[r[a]] = idx, r[a] = idx ++ ;
}

// 删除节点a
void remove(int a)
{
    l[r[a]] = l[a];
    r[l[a]] = r[a];
}
//遍历
for(int i=head;i!=-1;i=ne[i])cout<<e[i]<<' ';