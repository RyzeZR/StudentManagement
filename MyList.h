#pragma once
#include <iostream>

template<typename TYPE>
class CMyList
{
public:
    //���
    struct CMyNode {
        CMyNode() {
            m_pPrev = nullptr;
            m_pNext = nullptr;
        }
        CMyNode(const TYPE& Data, 
                CMyNode* pPrev = nullptr, 
                CMyNode* pNext = nullptr)
            :m_Data { Data }, m_pPrev{ pPrev }, m_pNext{ pNext }
        {

        }
        TYPE m_Data;   //����
        CMyNode* m_pPrev; //ǰ��
        CMyNode* m_pNext; //���
    };
public:
    class iterator {
    private:
        iterator(CMyNode* pNode = nullptr);
    public:   
        TYPE& operator *();
        iterator& operator++ ();
        iterator operator++ (int);
        iterator& operator-- ();
        iterator operator-- (int);
        bool operator==(const iterator& obj);
        bool operator!=(const iterator& obj);

        friend class CMyList;
    private:
        CMyNode* m_pCurrent;
    };


public:
    CMyList();
    CMyList(const CMyList& obj);
    CMyList(CMyList&& obj);
    ~CMyList();
    CMyList& operator= (const CMyList& obj);
    CMyList& operator= (CMyList&& obj);

    //������
    iterator begin() const;  //��ȡͷ��������λ��
    iterator end() const;    //��ȡ����������λ��


    int Size() const;  //��ȡ���С
    TYPE& Front() const;  //��ȡͷ��Ԫ��
    TYPE& Back() const;  //��ȡβ��Ԫ��

    void PushBack(const TYPE& Obj); //����Ԫ�ص�β��
    void PushBack(TYPE&& Obj); //����Ԫ�ص�β��

    void PushFront(const TYPE& Obj); //����Ԫ�ص�ͷ��
    void PushFront(TYPE&& Obj); //����Ԫ�ص�ͷ��

    iterator Insert(const iterator& it, const TYPE& Obj);    //����Ԫ�ص�ָ��λ��֮ǰ
    iterator Insert(const iterator& it, const TYPE&& Obj);  //����Ԫ�ص�ָ��λ��֮ǰ

    void PopBack();  //ɾ��βԪ��
    void PopFront(); //ɾ��ͷԪ��
    iterator Erase(const iterator& it); //ɾ��ָ��λ�õ�Ԫ��
    iterator Erase(const iterator& from, const iterator& to); //��Χɾ��Ԫ��

    void Clear();       //��ձ�
    bool Empty() const; //�Ƿ�ձ�
private:
    void Init();
private:
    CMyNode* m_pHead; //ͷ���
    CMyNode* m_pTail; //β���
    int      m_nSize; //�������
};


template<typename TYPE>
CMyList<TYPE>::CMyList()
{
    Init();
}

template<typename TYPE>
CMyList<TYPE>::CMyList(const CMyList& obj)
{
    Init();
    for (auto& e : obj) {
        PushBack(e);
    }
}

template<typename TYPE>
CMyList<TYPE>::CMyList(CMyList&& obj)
{
    m_nSize = obj.m_nSize;
    m_pHead = obj.m_pHead;
    m_pTail = obj.m_pTail;

    obj.m_nSize = 0;
    obj.m_pHead = nullptr;
    obj.m_pTail = nullptr;
}

template<typename TYPE>
CMyList<TYPE>& CMyList<TYPE>::operator=(const CMyList<TYPE>& obj)
{
    if (this == &obj)
        return *this;

    CMyList copy(obj); //���
    std::swap(*this, copy);
    //Clear();
    //for (auto& e : obj) {
    //    PushBack(e);
    //}
    return *this;
}

template<typename TYPE>
CMyList<TYPE>& CMyList<TYPE>::operator=(CMyList<TYPE>&& obj)
{
    if (this == &obj)
        return *this;

    //*this == const CMyList&
    std::swap(m_nSize, obj.m_nSize);
    std::swap(m_pHead, obj.m_pHead);
    std::swap(m_pTail, obj.m_pTail);
    return *this;
}

template<typename TYPE>
CMyList<TYPE>::~CMyList()
{
    Clear();
    delete m_pHead;
    delete m_pTail;
}


template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::begin() const
{
    return m_pHead->m_pNext;
}

template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::end() const
{
    return m_pTail;
}

template<typename TYPE>
int CMyList<TYPE>::Size() const
{
    return m_nSize;
}

template<typename TYPE>
TYPE& CMyList<TYPE>::Front() const
{
    return m_pHead->m_pNext->m_Data;
}

template<typename TYPE>
TYPE& CMyList<TYPE>::Back() const
{
    return m_pTail->m_pPrev->m_Data;
}

template<typename TYPE>
void CMyList<TYPE>::PushBack(const TYPE& Obj)
{
    //CMyNode* p = m_pTail;
    //p->m_pPrev = p->m_pPrev->m_pNext = new CMyNode(Obj, p->m_pPrev, p);
    //m_nSize++;
    Insert(end(), Obj);
}

template<typename TYPE>
void CMyList<TYPE>::PushBack(TYPE&& Obj)
{
    /*
    * [head]   .....  2  [1]   [tail]
    *
    * 1.prev = tail.prev
    * 1.next = tail
    *
    * tail.prev->next = 1
    *
    * tail.prev = 1
    */
    // CMyNode* p = m_pTail;
    // p->m_pPrev = p->m_pPrev->m_pNext = new CMyNode(std::move(Obj), p->m_pPrev, p);
    // m_nSize++;
    Insert(end(), Obj);
}

template<typename TYPE>
void CMyList<TYPE>::PushFront(const TYPE& Obj)
{
    m_pHead->m_pNext = m_pHead->m_pNext->m_pPrev = new CMyNode(Obj, m_pHead, m_pHead->m_pNext);
    m_nSize++;
}

template<typename TYPE>
void CMyList<TYPE>::PushFront(TYPE&& Obj)
{
    m_pHead->m_pNext = m_pHead->m_pNext->m_pPrev = new CMyNode(
        std::move(Obj), m_pHead, m_pHead->m_pNext);
    m_nSize++;
}

template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::Insert(const iterator& it, const TYPE& Obj)
{
    CMyNode* p = it.m_pCurrent;
    m_nSize++;
    return p->m_pPrev = p->m_pPrev->m_pNext = new CMyNode(Obj, p->m_pPrev, p);
}


template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::Insert(const iterator& it, const TYPE&& Obj)
{
    CMyNode* p = it.m_pCurrent;
    m_nSize++;
    return p->m_pPrev = p->m_pPrev->m_pNext = new CMyNode(std::move(Obj), p->m_pPrev, p);
}

template<typename TYPE>
void CMyList<TYPE>::PopBack()
{
    Erase(--end());
    /*
    * [] 1, 2, 3, [4] []
    *
    * 4->prev->next =  4->next;
    * 4->next->prev = 4->prev
    */
    //CMyNode* p = m_pTail->m_pPrev;
    //p->m_pPrev->m_pNext = p->m_pNext;
    //p->m_pNext->m_pPrev = p->m_pPrev;
    //m_nSize--;
    //delete p;

}

template<typename TYPE>
void CMyList<TYPE>::PopFront()
{
    Erase(begin());
}


template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::Erase(const iterator& it)
{
    /*
   * [] 1, 2, [3], 4 []
   *
   * 3->prev->next =  3->next;
   * 3->next->prev = 3->prev
   */
    CMyNode* p = it.m_pCurrent;
    iterator ret(p->m_pNext);
    p->m_pPrev->m_pNext = p->m_pNext;
    p->m_pNext->m_pPrev = p->m_pPrev;
    m_nSize--;
    p = nullptr;
    delete p;
    return ret;
}

template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::Erase(const iterator& from, const iterator& to)
{
    for (iterator it = from; it != to;) {
        it = Erase(it);
    }
    return to;
}


template<typename TYPE>
void CMyList<TYPE>::Clear()
{
    while (!Empty()) {
        PopBack();
    }
}

template<typename TYPE>
bool CMyList<TYPE>::Empty() const
{
    return m_nSize == 0;
}

template<typename TYPE>
void CMyList<TYPE>::Init()
{
    m_nSize = 0;
    m_pHead = new CMyNode();
    m_pTail = new CMyNode();

    m_pHead->m_pNext = m_pTail;
    m_pTail->m_pPrev = m_pHead;
}

template<typename TYPE>
CMyList<TYPE>::iterator::iterator(CMyNode* pNode)
{
    m_pCurrent = pNode;
}

template<typename TYPE>
TYPE& CMyList<TYPE>::iterator::operator*()
{
    return m_pCurrent->m_Data;
}

template<typename TYPE>
typename CMyList<TYPE>::iterator& CMyList<TYPE>::iterator::operator++()
{
    m_pCurrent = m_pCurrent->m_pNext;
    return *this;
}

template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::iterator::operator++(int)
{
    iterator Old(m_pCurrent);
    m_pCurrent = m_pCurrent->m_pNext;
    return Old;
}

template<typename TYPE>
typename CMyList<TYPE>::iterator& CMyList<TYPE>::iterator::operator--()
{
    m_pCurrent = m_pCurrent->m_pPrev;
    return *this;
}

template<typename TYPE>
typename CMyList<TYPE>::iterator CMyList<TYPE>::iterator::operator--(int)
{
    iterator Old(m_pCurrent);
    m_pCurrent = m_pCurrent->m_pPrev;
    return Old;
}

template<typename TYPE>
bool CMyList<TYPE>::iterator::operator==(const iterator& obj)
{
    return m_pCurrent == obj.m_pCurrent;
}

template<typename TYPE>
bool CMyList<TYPE>::iterator::operator!=(const iterator& obj)
{
    return m_pCurrent != obj.m_pCurrent;
}

