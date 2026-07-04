/*
【问题描述】
假定在当今家庭中，每个人最多可以养育两个孩子，请建立一个从曾祖父开始
的家谱，用二叉树的数据结构表示(二叉树的层数可以为3-4层)。
【基本要求】
1.实现整个家谱成员的输出。
2.实现家谱中成员的查找与定位，比如该成员位于家谱的第几代。
3.实现家谱中某个成员的双亲结点、子女结点的输出。
 */

#include <bits/stdc++.h>
using namespace std;

typedef struct node
{
public:
    string name;
    struct node *lchild, *rchild;
    int generation;

    node()
    {
        this->name = "无名氏";
        this->lchild = NULL;
        this->rchild = NULL;
        this->generation = -1;
    }
    node(string name)
    {
        this->name = name;
        this->lchild = NULL;
        this->rchild = NULL;
        this->generation = -1;
    }
} *BiTree, BiNode;

BiTree CreateBiTree(BiTree root)
{
    string temp;
    cin >> temp;
    if (temp == "#")
        return NULL;
    else
    {
        root = new BiNode(temp);
        root->lchild = CreateBiTree(root->lchild);
        root->rchild = CreateBiTree(root->rchild);
    }
}

BiNode *BFS(BiTree root, string name)
{
    // 广度优先搜索
    queue<BiNode *> q;
    q.push(root);
    root->generation = 1;
    while (!q.empty())
    {
        BiNode *temp = q.front();
        q.pop();
        if (temp->name == name)
        {
            return temp;
        }
        if (temp->lchild != NULL)
        {
            temp->lchild->generation = temp->generation + 1;
            q.push(temp->lchild);
        }
        if (temp->rchild != NULL)
        {
            temp->rchild->generation = temp->generation + 1;
            q.push(temp->rchild);
        }
    }
    return NULL;
}
class PrintBS
{
    int getPos(int h) { return h != 0 ? 3 * pow(2, h - 1) : 1; }
    void printSpace(int t = 1)
    {
        while (t-- > 0)
        {
            printf(" ");
        }
    }
    void printLine() { printf("_"); }
    void print3SpaceNum(int x)
    {
        if (x / 100 > 0)
        {
            printf("%d", x);
        }
        else if (x / 10 > 0)
        {
            printf("%d ", x);
        }
        else
        {
            printf(" %d ", x);
        }
    }
    void print3SpaceNum(string x)
    {
        cout << x;
    }
    int dfs(vector<BiNode *> &node, BiNode *root, int x)
    {
        node[x] = root;
        int lchildHeight = root->lchild == nullptr ? -1 : dfs(node, root->lchild, 1 + x * 2);
        int rchildHeight = root->rchild == nullptr ? -1 : dfs(node, root->rchild, 2 + x * 2);
        return 1 + max(lchildHeight, rchildHeight);
    }

public:
    void print(BiNode *root)
    {
        vector<BiNode *> node(10e6);
        int rootHeight = dfs(node, root, 0);
        BiNode *cur = root;
        // 遍历每一层, 分别打印这一层所有的值和延长线, 以及一行"/"和"\"
        for (int curHeight = rootHeight; curHeight > 1; curHeight--)
        {
            // 打印值, 这些值最左侧的序号先要确定, 值的个数也要确定, 都基于curHeight
            int indexOffset = pow(2, rootHeight - curHeight) - 1; // 这一层最左侧的元素序号
            // x代表现在在打印这一层的第几个
            for (int x = 0; x < pow(2, rootHeight - curHeight); x++)
            {
                cur = node[indexOffset + x];
                if (cur == nullptr)
                {
                    for (int i = 0; i < getPos(curHeight); i++)
                        printSpace();
                }
                if (cur->lchild == nullptr)
                {
                    for (int i = 0; i < getPos(curHeight) - 2; i++)
                        printSpace();
                }
                else
                {
                    for (int i = 0; i < getPos(curHeight - 1) + 1; i++)
                        printSpace();
                    for (int i = getPos(curHeight - 1) + 1; i < getPos(curHeight) - 2; i++)
                        printLine();
                }
                print3SpaceNum(cur->name);
                if (cur->rchild == nullptr)
                {
                    for (int i = 0; i < getPos(curHeight) - 1; i++)
                        printSpace();
                }
                else
                {
                    for (int i = getPos(curHeight - 1) + 1; i < getPos(curHeight) - 2; i++)
                        printLine();
                    for (int i = 0; i < getPos(curHeight - 1) + 2; i++)
                        printSpace();
                }
            }
            printf("\n");
            // 这里处理下一行的"/"和"\"
            for (int x = 0; x < pow(2, rootHeight - curHeight); x++)
            {
                cur = node[indexOffset + x];
                if (cur == nullptr)
                {
                    for (int i = 0; i < getPos(curHeight); i++)
                        printSpace();
                }
                if (cur->lchild == nullptr)
                {
                    for (int i = 0; i < getPos(curHeight); i++)
                        printSpace();
                }
                else
                {
                    for (int i = 0; i < getPos(curHeight - 1); i++)
                        printSpace();
                    printf("/");
                    for (int i = 0; i < getPos(curHeight - 1) - 1; i++)
                        printSpace();
                }
                if (cur->rchild == nullptr)
                {
                    for (int i = 0; i < getPos(curHeight); i++)
                        printSpace();
                }
                else
                {
                    for (int i = 0; i < getPos(curHeight - 1) - 2; i++)
                        printSpace();
                    printf("\\");
                    for (int i = 0; i < getPos(curHeight - 1) + 1; i++)
                        printSpace();
                }
            }
            printf("\n");
        }
        // 处理倒数第二层
        int indexOffset = pow(2, rootHeight - 1) - 1; // 这一层最左侧的元素序号
        for (int x = 0; x < indexOffset + 1; x++)
        {
            if ((cur = node[indexOffset + x]) == nullptr)
            {
                printSpace(6);
            }
            else
            {
                printSpace(1);
                print3SpaceNum(cur->name);
                printSpace(2);
            }
        }
        printf("\n");
        for (int x = 0; x < indexOffset + 1; x++)
        {
            if ((cur = node[indexOffset + x]) == nullptr)
            {
                printSpace(6);
            }
            else
            {
                if (cur->lchild == nullptr)
                    printSpace(3);
                else
                {
                    printSpace();
                    printf("/");
                    printSpace();
                }
                if (cur->rchild == nullptr)
                    printSpace(3);
                else
                {
                    printf("\\");
                    printSpace(2);
                }
            }
        }
        printf("\n");
        // 处理最后一层的叶节点
        indexOffset = pow(2, rootHeight) - 1; // 这一层最左侧的元素序号
        for (int x = 0; x < pow(2, rootHeight); x++)
        {
            if ((cur = node[indexOffset + x]) == nullptr)
            {
                printSpace(3);
            }
            else
            {
                if (x & 1)
                {
                    printf("%-3d", cur->name);
                }
                else
                {
                    print3SpaceNum(cur->name);
                }
            }
        }
        printf("\n");
    }
};

int main()
{
    // 数据(先序顺序): 曾祖 祖壹 父壹 # 子壹 # # # 祖贰 父贰 子贰 # # 子叁 # # 父叁 # 子肆 # # #
    BiTree root;
    root = CreateBiTree(root);
    cin.ignore();

    // 打印二叉树
    PrintBS print;
    print.print(root);

    // 查找成员, 并打印代数和双亲结点、子女结点
    cout << "请输入查询成员的姓名:";
    string name;
    cin.ignore();
    cin >> name;
    BiNode *result = BFS(root, name);
    if (result != NULL)
    {
        cout << name << "位于家谱的第" << result->generation << "代" << endl;
        cout << name << "的父亲结点: " << result->name << endl;
        if (result->lchild != NULL)
        {
            cout << name << "的长子结点: " << result->lchild->name << " ";
        }
        else
        {
            cout << name << "没有长子结点 " << endl;
        }
        if (result->rchild != NULL)
        {
            cout << name << "的次子结点: " << result->rchild->name << " ";
        }
        else
        {
            cout << name << "没有次子结点 " << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "查无此人!" << endl;
    }
}