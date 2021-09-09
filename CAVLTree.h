#pragma once
#include <iostream>
#include "CMyStack.h"

using namespace std;

template<typename TYPE>
class CAVLTree
{
public:
    struct CAVLNode {
        CAVLNode(const TYPE& e, CAVLNode* pParent, CAVLNode* pLeft, CAVLNode* pRight)
            :m_Element(e)
        {
            m_nHeight = 1;
            m_pParent = pParent;
            m_pLeft = pLeft;
            m_pRight = pRight;
            m_pNext = nullptr;
        }
        ~CAVLNode() {
           // std::cout << "delete " << m_Element << std::endl;
            if (m_pNext != nullptr)
                delete m_pNext;
        }
        TYPE m_Element;
        CAVLNode* m_pParent;
        CAVLNode* m_pLeft;
        CAVLNode* m_pRight;
        CAVLNode* m_pNext; //�ظ��ڵ�����
        int m_nHeight;
    };
public:
    CAVLTree();
    ~CAVLTree();
    bool Insert(const TYPE& e);
    void Remove(const TYPE& e);

    CAVLNode* Find(const TYPE& Element);

    bool Empty() const;

    void MakeEmpty();

    //AVLƽ��
    void Balance(CAVLNode* pParent);
    int Height(CAVLNode* pRoot);

    CAVLNode* FindMax(CAVLNode* pRoot);

    //�ҵ���ת
    void RotateWithRight(CAVLNode* pK1);
    void RotateWithLeft(CAVLNode* pK1);

    //��˫��ת
    void DoubleWithRight(CAVLNode* pK1);

    //��˫��ת
    void DoubleWithLeft(CAVLNode* pK1);

    int Size() const;
    CAVLNode* GetRoot() const;
    CAVLNode* GetNode(const TYPE& Element);

    void PrintTree(CAVLNode* pRoot) const;
private:
    CAVLNode* m_pRoot;
    int m_nCount;
};

template<typename TYPE>
CAVLTree<TYPE>::CAVLTree()
{
    m_pRoot = nullptr;
    m_nCount = 0;
}

template<typename TYPE>
CAVLTree<TYPE>::~CAVLTree()
{
    MakeEmpty();
}

template<typename TYPE>
bool CAVLTree<TYPE>::Insert(const TYPE& Element)
{

    //����
    if (m_pRoot == nullptr) {
        m_pRoot = new CAVLNode(Element, nullptr, nullptr, nullptr);
        m_nCount++;
        return true;
    }

    CAVLNode* pFindNode = m_pRoot;
    while (pFindNode != nullptr) {
        //��ͬ���������
        if (pFindNode->m_Element == Element) {
            //������ [1] -> 
            //�ҵ�β���ڵ�
            /*CAVLNode* pTail = pFindNode;
            while (pTail->m_pNext != nullptr)
                pTail = pTail->m_pNext;
            pTail->m_pNext = new CAVLNode(Element, nullptr, nullptr, nullptr);
            m_nCount++;*/
            return true;
        }
        //�ұ��Ҳ����
        else if (Element > pFindNode->m_Element) {
            if (pFindNode->m_pRight == nullptr) {
                //�����ұ߲���
                pFindNode->m_pRight = new CAVLNode(Element, pFindNode, nullptr, nullptr);
                break;
            }
            pFindNode = pFindNode->m_pRight;

        }
        //����Ҳ����
        else if (Element < pFindNode->m_Element) {
            if (pFindNode->m_pLeft == nullptr) {
                pFindNode->m_pLeft = new CAVLNode(Element, pFindNode, nullptr, nullptr);
                break;
            }
            pFindNode = pFindNode->m_pLeft;
        }
    }

    //ƽ�⸸�ڵ�
    Balance(pFindNode);
    m_nCount++;

    return true;
}

template<typename TYPE>
void CAVLTree<TYPE>::Balance(CAVLNode* pParent)
{
    //�������ڵ�����߶�
    while (pParent != nullptr) {
        pParent->m_nHeight = std::max<int>(Height(pParent->m_pLeft),
            Height(pParent->m_pRight)) + 1;

        //1.����������������
        int nSubHeight = Height(pParent->m_pLeft) - Height(pParent->m_pRight);

        //�������Ƚϸ�
        if (nSubHeight > 1) {
            //�ҵ���ת
            if (Height(pParent->m_pLeft->m_pLeft) > Height(pParent->m_pLeft->m_pRight)) {
                RotateWithRight(pParent);
            }
            //�������Ƚϸ� 
            //��˫��ת(������ת��������ת��
            else {
                DoubleWithRight(pParent);
            }
        }
        //2.����������������
        else if (nSubHeight < -1) {
            //����ת
            if (Height(pParent->m_pRight->m_pLeft) < Height(pParent->m_pRight->m_pRight)) {
                RotateWithLeft(pParent);
            }
            //��˫��ת(������ת��������ת��
            else {
                DoubleWithLeft(pParent);
            }
        }
        pParent = pParent->m_pParent;
    }
}

template<typename TYPE>
int CAVLTree<TYPE>::Height(CAVLNode* pRoot)
{
    return pRoot == nullptr ? 0 : pRoot->m_nHeight;
}

template<typename TYPE>
typename CAVLTree<TYPE>::CAVLNode* CAVLTree<TYPE>::FindMax(CAVLTree<TYPE>::CAVLNode* pRoot)
{
    while (pRoot != nullptr) {
        if (pRoot->m_pRight == nullptr)
            return pRoot;

        pRoot = pRoot->m_pRight;
    }

    return nullptr;
}

//����ת
template<typename TYPE>
void CAVLTree<TYPE>::RotateWithLeft(CAVLNode* pK1)
{
    CAVLNode* pParent = pK1->m_pParent;
    CAVLNode* pK2 = pK1->m_pRight;

    pK1->m_pRight = pK2->m_pLeft;
    pK1->m_pParent = pK2;

    pK2->m_pLeft = pK1;
    pK2->m_pParent = pParent;

    //B�ı仯
    if (pK1->m_pRight != nullptr) {
        pK1->m_pRight->m_pParent = pK1;
    }

    //�߶ȵı仯
    pK1->m_nHeight = max(Height(pK1->m_pLeft), Height(pK1->m_pRight)) + 1;
    pK2->m_nHeight = max(Height(pK2->m_pLeft), Height(pK2->m_pRight)) + 1;

    //�޸ĸ��ڵ����ӻ����Һ���
    if (pParent == nullptr) {
        m_pRoot = pK2;
    }
    else {
        if (pParent->m_pLeft == pK1) {
            pParent->m_pLeft = pK2;
        }
        else {
            pParent->m_pRight = pK2;
        }
    }
}

template<typename TYPE>
void CAVLTree<TYPE>::RotateWithRight(CAVLNode* pK1)
{
    CAVLNode* pParent = pK1->m_pParent;
    CAVLNode* pK2 = pK1->m_pLeft;

    pK1->m_pLeft = pK2->m_pRight;
    pK1->m_pParent = pK2;

    pK2->m_pRight = pK1;
    pK2->m_pParent = pParent;

    //C�ı仯
    if (pK1->m_pLeft != nullptr) {
        pK1->m_pLeft->m_pParent = pK1;
    }

    //�߶ȵı仯
    pK1->m_nHeight = max(Height(pK1->m_pLeft), Height(pK1->m_pRight)) + 1;
    pK2->m_nHeight = max(Height(pK2->m_pLeft), Height(pK2->m_pRight)) + 1;

    //�޸ĸ��ڵ����ӻ����Һ���
    if (pParent == nullptr) {
        m_pRoot = pK2;
    }
    else {
        if (pParent->m_pLeft == pK1) {
            pParent->m_pLeft = pK2;
        }
        else {
            pParent->m_pRight = pK2;
        }
    }
}

template<typename TYPE>
void CAVLTree<TYPE>::DoubleWithRight(CAVLNode* pK1)
{
    RotateWithLeft(pK1->m_pLeft);
    RotateWithRight(pK1);
}

template<typename TYPE>
void CAVLTree<TYPE>::DoubleWithLeft(CAVLNode* pK1)
{
    RotateWithRight(pK1->m_pRight);
    RotateWithLeft(pK1);
}

template<typename TYPE>
int CAVLTree<TYPE>::Size() const
{
    return m_nCount;
}

template<typename TYPE>
typename CAVLTree<TYPE>::CAVLNode* CAVLTree<TYPE>::GetRoot() const
{
    return m_pRoot;
}

template<typename TYPE>
typename CAVLTree<TYPE>::CAVLNode* CAVLTree<TYPE>::GetNode(const TYPE& Element)
{
    CAVLNode* pFindNode = m_pRoot;
    while (pFindNode != nullptr) {
        if (pFindNode->m_Element == Element) {
            //�ҵ�
            return pFindNode;
        }
        //�ұ��Ҳ����
        else if (Element > pFindNode->m_Element) {
            pFindNode = pFindNode->m_pRight;

        }
        //����Ҳ����
        else if (Element < pFindNode->m_Element) {
            pFindNode = pFindNode->m_pLeft;
        }
    }

    return nullptr;
}

template<typename TYPE>
void CAVLTree<TYPE>::Remove(const TYPE& Element)
{
    CAVLNode* pDelNode = GetNode(Element);
    if (pDelNode == nullptr)
        return;


    //ɾ���ڵ�
    while (true) {
        CAVLNode* pParent = pDelNode->m_pParent;

        //1.Ҷ�ӽڵ��ɾ��
        if (pDelNode->m_pLeft == nullptr && pDelNode->m_pRight == nullptr) {
            if (pParent == nullptr) {
                m_pRoot = nullptr;
            }
            else if (pDelNode == pParent->m_pLeft) {
                pParent->m_pLeft = nullptr;
            }
            else if (pDelNode == pParent->m_pRight) {
                pParent->m_pRight = nullptr;
            }
        }
        //3.�������ӽڵ��ɾ��
        else if (pDelNode->m_pLeft != nullptr && pDelNode->m_pRight != nullptr) {
            //��������Ľڵ�
            CAVLNode* pMaxNode = FindMax(pDelNode->m_pLeft);

            //��������
            pDelNode->m_Element = pMaxNode->m_Element;

            //��������
            CAVLNode* pMaxNext = pMaxNode->m_pNext;
            pMaxNode->m_pNext = pDelNode->m_pNext;
            pDelNode->m_pNext = pMaxNext;
            
            //ɾ��������Ľڵ�
            pDelNode = pMaxNode;
            continue;
        }
        //2.һ�����ӽڵ��ɾ��
        else {
            CAVLNode* pParent = pDelNode->m_pParent;
            CAVLNode* pChild = pDelNode->m_pLeft != nullptr ? pDelNode->m_pLeft : pDelNode->m_pRight;

            /*
            *      A
            *        B
            *       C  D
            *
            *      A
            *    B
            *  C  D
            *
            */
            //���ڵ�ı仯
            if (pParent == nullptr) {
                m_pRoot = pChild;
            }
            else if (pDelNode == pParent->m_pLeft) {
                pParent->m_pLeft = pChild;
            }
            else if (pDelNode == pParent->m_pRight) {
                pParent->m_pRight = pChild;
            }

            //���ӽڵ�仯
            pChild->m_pParent = pParent;
        }
        break;
    }

    Balance(pDelNode->m_pParent);
    pDelNode = nullptr;
    delete pDelNode;
    m_nCount--;
}

template<typename TYPE>
typename CAVLTree<TYPE>::CAVLNode* CAVLTree<TYPE>::Find(const TYPE& Element)
{
    //����
    if (m_pRoot == nullptr) {
        return nullptr;
    }
    
    CAVLNode* pFindNode = m_pRoot;
    while (pFindNode != nullptr) {
        if (pFindNode->m_Element == Element) {
            return pFindNode;
        }
        //�ұ��Ҳ����
        else if (Element > pFindNode->m_Element) {
            pFindNode = pFindNode->m_pRight;

        }
        //����Ҳ����
        else if (Element < pFindNode->m_Element) {
            pFindNode = pFindNode->m_pLeft;
        }
    }
    return nullptr;
}

template<typename TYPE>
void CAVLTree<TYPE>::MakeEmpty()
{
    CMyStack<CAVLNode*> s;
    CAVLNode* pRoot = m_pRoot;
    CAVLNode* pPrev = nullptr;

    while (true) {
        //������������
        while (pRoot != nullptr) {
            s.Push(pRoot);
            pRoot = pRoot->m_pLeft;
        }

        //�����Һ���
        if (s.Empty()) {
            break;
        }

        pRoot = s.Top();
        s.Pop();

        //Ҷ�ӽڵ������ʾ�����Һ������ϴ�һ�ε�������
        if (pRoot->m_pLeft == nullptr && pRoot->m_pRight == nullptr
            || pRoot->m_pRight == pPrev || pRoot->m_pRight == nullptr) {
            pPrev = pRoot;
            delete pRoot;
            pRoot = nullptr;
            continue;
        }
        else {
            s.Push(pRoot);
        }

        pRoot = pRoot->m_pRight;
    }
}

template<typename TYPE>
bool CAVLTree<TYPE>::Empty() const
{
    return m_pRoot == nullptr;
}

template<typename TYPE>
void CAVLTree<TYPE>::PrintTree(CAVLNode* pRoot) const
{
    if (pRoot != nullptr) {
        PrintTree(pRoot->m_pLeft);
        //��ʾ����
        CAVLNode* pNext = pRoot->m_pNext;
        while (pNext != nullptr) {
            pNext = pNext->m_pNext;
        }
        PrintTree(pRoot->m_pRight);
    }
}