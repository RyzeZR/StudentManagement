#pragma once
#include <iostream>
#include "CAVLTree.h"
#include "CString.h"
#include "CFile.h"
#include "CMyStack.h"

//���scanf�Ļ�����
#define CLEAR_BUFF scanf("%*[^\n]%*c")
//ѧ����Ϣ�ļ�·��
#define STUDENT_FILE_PATH "dat\\student1"
//�γ��б��ļ�·��
#define COURSE_FILE_PATH "dat\\course1"
//ѡ�� ��¼�ļ�·��
#define Course_Selection_Record_FILE_PATH "dat\\record1"

/// <summary>
/// 
/// </summary>
struct CStudent {
    int m_nID;
    int* m_pLink;
    std::string m_szName;
};

struct CCourse {
    int m_nID;
    int* m_pLink;
    std::string m_szName;
};

struct CRecord {
    int m_nStuID;
    int m_nClsID;
    int m_nScore;
};

typedef struct _STSTUDENTSAVEINFO {
    int len;
    struct CStudent _stu;
}STSTUDENTSAVEINFO,*PSTSTUDENTSAVEINFO;

typedef struct _STCLASSSAVEINFO {
    int len;
    struct CCourse _cls;
}STCLASSSAVEINFO, *PSTCLASSSAVEINFO;

std::ostream& operator<< (std::ostream& out, const CStudent& obj) {
    out << "ѧ������:" << obj.m_szName.c_str() << " ѧ�ţ�ID��:" << obj.m_nID;
    return out;
}

std::ostream& operator<< (std::ostream& out, const CCourse& obj) {
    out << "�γ�����:" << obj.m_szName.c_str() << " �γ�id:" << obj.m_nID;
    return out;
}

template<typename KEY, typename VALUE>
struct CStudentPair {
    KEY   m_Key; //�ؼ���
    VALUE m_Value; //ֵ

    CStudentPair(const KEY& Key) {
        m_Key = Key;
    }
    CStudentPair(const KEY& Key, const VALUE& value) {
        m_Key = Key;
        m_Value = value;
    }
    bool operator== (const CStudentPair& obj) const {
        return m_Key == obj.m_Key;
    }
    bool operator> (const CStudentPair& obj) const {
        return m_Key > obj.m_Key;
    }
    bool operator< (const CStudentPair& obj) const {
        return m_Key < obj.m_Key;
    }
};

template<typename KEY, typename VALUE>
std::ostream& operator<< (std::ostream& out, const CStudentPair<KEY, VALUE>& obj) {
    out << obj.m_Value;
    return out;
}

typedef CStudentPair<int, CStudent> STUIDPair;
typedef CStudentPair<int, CCourse> CLSIDPair;

//ѧ��id��
CAVLTree<STUIDPair> StuIDTree;
//�γ�ID��
CAVLTree<CLSIDPair> ClsIDTree;

//ɾ�����޸ġ����Ҳ���
template<typename T,typename T2,typename TYPE,typename TYPE2>
class CManage {
public:
    //����ѧ��ID�Ϳγ�ID
    void ErgodicStuClsID(T* pRoot, const char* str);
    //ͨ��ѧ��ID���߿γ�ID����ѧ����γ�
    void FindStuClsByID(CAVLTree<TYPE>& obj,int id);
    //ͨ��ѧ�������߿γ�������ѧ����γ�
    void FindStuClsByName(CAVLTree<TYPE>& obj,const char* name);
    //ͨ��ѧ��ID���߿γ�ID����ѡ�μ�¼
    void FindSelLogByID(CAVLTree<TYPE>& obj, int id);
    //ͨ��ѧ��ID���߿γ�ID�޸�ѧ������γ���
    void ModifyStuClsByID(CAVLTree<TYPE>& obj, int id , const char* name);
    //ͨ��ѧ��ID���߿γ�IDɾ��ѧ����γ�
    void DeleteStuClsByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int id);
};

//ѧ���Ϳγ��ļ�����(���£���ȡ��д��)
template<typename T, typename T2, typename TYPE>
class CFileAct {
public:
    //�ļ�ĩβ�������ѧ����γ�
    void InsertStuClsToFile(const T2& Element, const char* path);
    //��ʼ��ѧ��ID����γ�ID��
    void InitStuClsIDTree(CAVLTree<TYPE>& obj, const char* path);
    //���޸Ļ�ɾ����������������¸���д���ļ�
    void UpdateStuClsToFile(CAVLTree<TYPE>& obj, const char* path);
};

//ѡ�μ�¼�ļ�����
template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
class CSelRecord {
public:
    //��ѡ�μ�¼���޸ģ������д���ļ�
    void UpdateSelLogToFile(CAVLTree<TYPE2>& obj, const char* path);
    //����ѡ�μ�¼��ֱ���ļ�ĩβ����
    void InsertSelLogToFile(const TYPE3& Element, const char* path);

    void ModifySelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID, int nScore);
    void DeleteSelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID);
    //����ѡ�μ�¼�����뵽ѧ��ID���Ϳγ�ID��
    void AddSelLog(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuId, int nClsID, int nScore);
    void InitSelLogTree(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, const char* path);
};
CSelRecord<CAVLTree<STUIDPair>::CAVLNode, CAVLTree<CLSIDPair>::CAVLNode, STUIDPair, CLSIDPair, CRecord> selRecord;

CFileAct<CAVLTree<CLSIDPair>::CAVLNode, CCourse, CLSIDPair> clsFileAct;
CFileAct<CAVLTree<STUIDPair>::CAVLNode, CStudent, STUIDPair> stuFileAct;

CManage<CAVLTree<STUIDPair>::CAVLNode, CAVLTree<CLSIDPair>::CAVLNode, STUIDPair, CLSIDPair> stuManage;
CManage<CAVLTree<CLSIDPair>::CAVLNode, CAVLTree<STUIDPair>::CAVLNode, CLSIDPair, STUIDPair> clsManage;

template<typename T,typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2,TYPE, TYPE2>::FindStuClsByID(CAVLTree<TYPE>& obj, int id) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "ͨ��ID���ҵ�:>>>" << pNode->m_Element << std::endl;
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "������ʱ:>>>" << end - start << "����" << endl;
        std::cout << "��������:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "δ���ҵ�" << endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::DeleteStuClsByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int id) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "ͨ��ID���ҵ�:>>>" << pNode->m_Element << std::endl;
        if (pNode->m_Element.m_Value.m_pLink != NULL) {
            CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
            //CMyList<struct CRecord>::iterator it = plist->begin();
            for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
                //std::cout << "ѧ��ID��" << e.m_nStuID << " �γ�ID��" << e.m_nClsID << " �ɼ���" << e.m_nScore << endl;
                T2* pClsNode = obj2.Find((*it).m_nClsID);
                while (pClsNode != nullptr) {
                    std::cout << "ͨ��ID���ҵ�:>>>" << pClsNode->m_Element << std::endl;
                    if (pClsNode->m_Element.m_Value.m_pLink != NULL) {
                        CMyList<struct CRecord>* pSelList = ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink));
                        //CMyList<struct CRecord>::iterator itSel = pSelList->end();
                        for (CMyList<struct CRecord>::iterator itSel = (--pSelList->end()); itSel != (--pSelList->begin()); itSel--) {
                            cout << (*itSel).m_nStuID << ' ' << endl;
                            if ((*itSel).m_nStuID == (*it).m_nStuID) {
                                cout << "ɾ��:>>>" << (*itSel).m_nStuID << endl;
                                pSelList->Erase(itSel);
                            }
                        }
                    }
                    pClsNode = pClsNode->m_pNext;
                }
            }

            plist->Clear();
            pNode->m_Element.m_Value.m_pLink = nullptr;
            delete pNode->m_Element.m_Value.m_pLink;
        }
        obj.Remove(id);
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "ɾ����ʱ:>>>" << end - start << "����" << endl;
        std::cout << "��������:>>>" << StuIDTree.Size() << endl;
    }
    else {
        std::cout << "δ���ҵ�" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::ModifyStuClsByID(CAVLTree<TYPE>& obj, int id,const char* name) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "ͨ��ID���ҵ�:>>>" << pNode->m_Element << std::endl;
        pNode->m_Element.m_Value.m_szName = name;
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "������ʱ:>>>" << end - start << "����" << endl;
        std::cout << "��������:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "δ���ҵ�" << end;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::FindSelLogByID(CAVLTree<TYPE>& obj, int id) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "ͨ��ID���ҵ�:>>>" << pNode->m_Element << std::endl;
        CMyList<struct CRecord>* pList = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
        if (pList == nullptr)
        {
            nFlag = 0;
            break;
        }
        CMyList<struct CRecord>::iterator it = pList->begin();
        for (auto& e : *pList) {
            std::cout << "ѧ��ID��" << e.m_nStuID << " �γ�ID��" << e.m_nClsID << " �ɼ���" << e.m_nScore << endl;
        }
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "������ʱ:>>>" << end - start << "����" << endl;
        std::cout << "��������:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "δ���ҵ�" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::FindStuClsByName(CAVLTree<TYPE>& obj, const char* name) {
    clock_t start, end;
    start = clock();
    CManage<T, T2, TYPE, TYPE2> manage1;
    manage1.ErgodicStuClsID(obj.GetRoot(), name);
    end = clock();
    std::cout << "������ʱ:>>>" << end - start << "����" << endl;
    std::cout << "��������:>>>" << endl;
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2,TYPE, TYPE2>::ErgodicStuClsID(T* pRoot, const char* str)
{
    if (pRoot != nullptr) {
        ErgodicStuClsID(pRoot->m_pLeft, str);
        //if (strcmp((char*)pRoot->m_Element.m_Value.m_szName.c_str(), str) == 0) {
        //�������֣�����ȥ�����ֲ������char
        if (pRoot->m_Element.m_Value.m_szName.find(str) != std::string::npos) {
            for (int i = 0; i < pRoot->m_Element.m_Value.m_szName.length(); i = i + 2) {
                if (pRoot->m_Element.m_Value.m_szName[i] == str[0] && pRoot->m_Element.m_Value.m_szName[i + 1] == str[1]) {
                    std::cout << "���ҵ�:>>>" << pRoot->m_Element << std::endl;
                    break;
                }
            }
        }
        //��ʾ����
        T* pNext = pRoot->m_pNext;
        while (pNext != nullptr) {
            pNext = pNext->m_pNext;
        }
        ErgodicStuClsID(pRoot->m_pRight, str);
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::InitSelLogTree(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, const char* path) {
    CFile cFileStu;
    try {
        cFileStu = CFile(path, "rb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    struct CRecord rec = { 0 };
    while (!cFileStu.Feof()) {
        try {
            size_t size = cFileStu.Read(&rec.m_nStuID, 1, 4);
            if (size <= 0)break;
            size = cFileStu.Read(&rec.m_nClsID, 1, 4);
            if (size <= 0)break;
            cFileStu.Read(&rec.m_nScore, 1, 4);
        }
        catch (CFileError& e) {
            std::cout << e.GetErrorMsg() << endl;
        }
        T* pStuNode = obj.Find(rec.m_nStuID);
        if (pStuNode != nullptr) {
            if (pStuNode->m_Element.m_Value.m_pLink == NULL) {
                CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
                plist->PushBack(rec);
                pStuNode->m_Element.m_Value.m_pLink = (int*)plist;
            }
            else {
                ((CMyList<struct CRecord>*)(pStuNode->m_Element.m_Value.m_pLink))->PushBack(rec);
            }
        }
        T2* pClsNode = obj2.Find(rec.m_nClsID);
        if (pClsNode != nullptr) {
            if (pClsNode->m_Element.m_Value.m_pLink == NULL) {
                CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
                plist->PushBack(rec);
                pClsNode->m_Element.m_Value.m_pLink = (int*)plist;
            }
            else {
                ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink))->PushBack(rec);
            }
        }
    }
    cFileStu.Close();
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::AddSelLog(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuId, int nClsID, int nScore) {
    clock_t start, end;
    struct CRecord rec = { nStuId ,nClsID ,nScore };
    start = clock();
    int nFlag = 0;
    T2* pClsNode = obj2.Find(nClsID);
    while (pClsNode != nullptr) {
        nFlag = 1;
        if (pClsNode->m_Element.m_Value.m_pLink == NULL) {
            CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
            plist->PushBack(rec);
            pClsNode->m_Element.m_Value.m_pLink = (int*)plist;
        }
        else {
            ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink))->PushBack(rec);
        }
        pClsNode = pClsNode->m_pNext;
    }
    if (nFlag == 0) {
        cout << "û�иÿγ�" << endl;
        return;
    }
    T* pStuNode = obj.Find(nStuId);
    while (pStuNode != nullptr) {
        //std::cout << "ͨ��ѧ��ID���ҵ�:>>>" << pNode->m_Element << std::endl;
        if (pStuNode->m_Element.m_Value.m_pLink == NULL) {
            CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
            plist->PushBack(rec);
            pStuNode->m_Element.m_Value.m_pLink = (int*)plist;
        }
        else {
            ((CMyList<struct CRecord>*)(pStuNode->m_Element.m_Value.m_pLink))->PushBack(rec);
        }
        pStuNode = pStuNode->m_pNext;
    }
    selRecord.InsertSelLogToFile({ nStuId, nClsID, nScore }, Course_Selection_Record_FILE_PATH);
    end = clock();
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::DeleteSelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(nStuID);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "ͨ��ѧ��ID���ҵ�:>>>" << pNode->m_Element << std::endl;
        if (pNode->m_Element.m_Value.m_pLink != NULL) {
            CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
            //CMyList<struct CRecord>::iterator it = plist->begin();
            for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
                //std::cout << "ѧ��ID��" << e.m_nStuID << " �γ�ID��" << e.m_nClsID << " �ɼ���" << e.m_nScore << endl;
                if ((*it).m_nClsID == nClsID) {
                    cout << "ɾ��:>>>" << (*it).m_nStuID << (*it).m_nClsID << endl;
                    plist->Erase(it);
                }
            }
        }
        pNode = pNode->m_pNext;
    }

    T2* pClsNode = obj2.Find(nClsID);
    while (pClsNode != nullptr) {
        nFlag = 1;
        std::cout << "ͨ���γ�ID���ҵ�:>>>" << pClsNode->m_Element << std::endl;
        if (pClsNode->m_Element.m_Value.m_pLink != NULL) {
            CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink));
            //CMyList<struct CRecord>::iterator it = plist->begin();
            for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
                //std::cout << "ѧ��ID��" << e.m_nStuID << " �γ�ID��" << e.m_nClsID << " �ɼ���" << e.m_nScore << endl;
                if ((*it).m_nStuID == nStuID) {
                    cout << "ɾ��:>>>" << (*it).m_nStuID << (*it).m_nClsID << endl;
                    plist->Erase(it);
                }
            }
        }
        pClsNode = pClsNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "ɾ����ʱ:>>>" << end - start << "����" << endl;
        std::cout << "��������:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "δ���ҵ�" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::ModifySelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID, int nScore) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(nStuID);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "ͨ��ѧ��ID���ҵ�:>>>" << pNode->m_Element << std::endl;
        CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
        if (plist == nullptr) {
            nFlag = 0;
            break;
        }
        for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
            if ((*it).m_nClsID == nClsID) {
                (*it).m_nScore = nScore;
            }
        }
        pNode = pNode->m_pNext;
    }

    T2* pNode2 = obj2.Find(nClsID);
    while (pNode2 != nullptr) {
        nFlag = 1;
        std::cout << "ͨ���γ�ID���ҵ�:>>>" << pNode2->m_Element << std::endl;
        CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode2->m_Element.m_Value.m_pLink));
        if (plist == nullptr) {
            nFlag = 0;
            break;
        }
        for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
            if ((*it).m_nStuID == nStuID) {
                (*it).m_nScore = nScore;
            }
        }
        pNode2 = pNode2->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "������ʱ:>>>" << end - start << "����" << endl;
        std::cout << "��������:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "δ���ҵ�" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::InsertSelLogToFile(const TYPE3& Element, const char* path) {
    CFile cFileSel;
    try {
        cFileSel = CFile(path, "ab+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    try {
        cFileSel.Write((void*)&Element.m_nStuID, 1, sizeof(Element.m_nStuID));
        cFileSel.Flush();
        cFileSel.Write((void*)&Element.m_nClsID, 1, sizeof(Element.m_nClsID));
        cFileSel.Flush();
        cFileSel.Write((void*)&Element.m_nScore, 1, sizeof(Element.m_nScore));
        cFileSel.Flush();
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    cFileSel.Close();
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::UpdateSelLogToFile(CAVLTree<TYPE2>& obj,const char* path)
{
    CFile cFileSel;
    try {
        cFileSel = CFile(path, "wb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    CMyStack<T2*> stack;
    T2* pRoot = obj.GetRoot();
    //�������
    while (true) {
        while (pRoot != nullptr) {
            CMyList<struct CRecord>* pList = ((CMyList<struct CRecord>*)(pRoot->m_Element.m_Value.m_pLink));
            if (pList == nullptr) {
                pRoot = pRoot->m_pLeft;
                continue;
            }
            //CMyList<struct CRecord>::iterator it = pList->begin();
                struct CRecord* rec = new struct CRecord[pList->Size()];
                struct CRecord* pRec = rec;
                for (auto& e : *pList) {
                    
                    pRec->m_nStuID = e.m_nStuID;
                    pRec->m_nClsID = e.m_nClsID;
                    pRec->m_nScore = e.m_nScore;
                    pRec++;
                
                }
                try {
                    cFileSel.Write(rec, 1, pList->Size()*12);
                    cFileSel.Flush();
                }
                catch (CFileError& e) {

                }
                delete[] rec;
            stack.Push(pRoot);
            pRoot = pRoot->m_pLeft;
        }
        if (stack.Empty()) {
            break;
        }
        pRoot = stack.Top();
        stack.Pop();
        pRoot = pRoot->m_pRight;
    }
    cFileSel.Close();
}

template<typename T, typename T2, typename TYPE>
inline void CFileAct<T, T2, TYPE>::UpdateStuClsToFile(CAVLTree<TYPE>& obj, const char* path) {
    CFile cFileCls;
    try {
        cFileCls = CFile(path, "wb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    CMyStack<T*> stack;
    T* pRoot = obj.GetRoot();

    //�������
    while (true) {
        while (pRoot != nullptr) {
            int nLength = sizeof(pRoot->m_Element.m_Value.m_nID) + pRoot->m_Element.m_Value.m_szName.length() + 1;
            try {
                cFileCls.Write(&nLength, 1, sizeof(nLength));
                cFileCls.Flush();
                cFileCls.Write(&pRoot->m_Element.m_Value.m_nID, 1, sizeof(pRoot->m_Element.m_Value.m_nID));
                cFileCls.Flush();
                cFileCls.Write((char*)pRoot->m_Element.m_Value.m_szName.c_str(), 1, pRoot->m_Element.m_Value.m_szName.length() + 1);
                cFileCls.Flush();
            }
            catch (CFileError& e) {
                std::cout << e.GetErrorMsg() << endl;
            }
            stack.Push(pRoot);
            pRoot = pRoot->m_pLeft;
        }
        if (stack.Empty()) {
            break;
        }
        pRoot = stack.Top();
        stack.Pop();
        pRoot = pRoot->m_pRight;
    }
    cFileCls.Close();
}

template<typename T , typename T2, typename TYPE>
inline void CFileAct<T, T2, TYPE>::InitStuClsIDTree(CAVLTree<TYPE>& obj, const char* path) {
    CFile cFile;
    try {
        cFile = CFile(path, "rb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    int nLength = 0;
    //struct CClass cls = { 0 };
    int nID;
    std::string str(1000, '\0');
    while (!cFile.Feof()) {
        try {
            size_t size = cFile.Read(&nLength, 1, 4);
            if (size <= 0)
                break;
            size = cFile.Read(&nID, 1, 4);
            if (size <= 0)
                break;
            cFile.Read((char*)str.c_str(), 1, nLength - 4);
        }
        catch (CFileError& e) {
            std::cout << e.GetErrorMsg() << endl;
        }
        obj.Insert({ nID, {nID,NULL,str.c_str() } });
    }
    cFile.Close();
}

template<typename T , typename T2, typename TYPE>
inline void CFileAct<T, T2, TYPE>::InsertStuClsToFile(const T2& Element, const char* path)
{
    CFile cFile;
    try {
        cFile = CFile(path, "ab+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    int nLength = sizeof(Element.m_nID) + Element.m_szName.length() + 1;
    try {
        //cFileStu.Seek(0, SEEK_END);
        cFile.Write(&nLength, 1, sizeof(nLength));
        cFile.Flush();
        cFile.Write((int*)&Element.m_nID, 1, sizeof(Element.m_nID));
        cFile.Flush();
        cFile.Write((char*)Element.m_szName.c_str(), 1, Element.m_szName.length() + 1);
        cFile.Flush();
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    cFile.Close();
}

void CoutCText(const char* str) {
    cout << str << endl;
}





const char* LASTNAME[444] = { "��", "Ǯ", "��", "��", "��", "��", "֣", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʩ", "��", "��", "��", "��", "��", "��", "κ", "��", "��", "��", "л", "��", "��", "��", "ˮ", "�", "��", "��", "��", "��", "��", "��", "��", "��", "��", "³", "Τ", "��", "��", "��", "��", "��", "��", "��", "��", "Ԭ", "��", "ۺ", "��", "ʷ", "��", "��", "��", "�", "Ѧ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʱ", "��", "Ƥ", "��", "��", "��", "��", "��", "Ԫ", "��", "��", "��", "ƽ", "��", "��", "��", "��", "��", "Ҧ", "��", "տ", "��", "��", "ë", "��", "��", "��", "��", "��", "�", "��", "��", "��", "��", "̸", "��", "é", "��", "��", "��", "��", "��", "��", "ף", "��", "��", "��", "��", "��", "��", "ϯ", "��", "��", "ǿ", "��", "·", "¦", "Σ", "��", "ͯ", "��", "��", "÷", "ʢ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "֧", "��", "��", "��", "¬", "Ī", "��", "��", "��", "��", "��", "��", "Ӧ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʯ", "��", "��", "ť", "��", "��", "��", "��", "��", "��", "½", "��", "��", "��", "��", "�", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ɽ", "��", "��", "��", "�", "��", "ȫ", "ۭ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ղ", "��", "��", "Ҷ", "��", "˾", "��", "۬", "��", "��", "��", "ӡ", "��", "��", "��", "��", "ۢ", "��", "��", "��", "��", "��", "��", "׿", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "˫", "��", "ݷ", "��", "��", "̷", "��", "��", "��", "��", "��", "��", "��", "Ƚ", "��", "۪", "Ӻ", "��", "�", "ɣ", "��", "�", "ţ", "��", "ͨ", "��", "��", "��", "��", "ۣ", "��", "��", "ũ", "��", "��", "ׯ", "��", "��", "��", "��", "��", "Ľ", "��", "��", "ϰ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "»", "��", "��", "Ź", "�", "��", "��", "ε", "Խ", "��", "¡", "ʦ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ɳ", "ؿ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "Ȩ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "۳", "Ϳ", "��", "��", "��", "��", "˧", "��", "��", "��", "��", "��", "��", "��", "Ĳ", "��", "٦", "��", "��", "ī", "��", "��", "��", "��", "��", "��", "١", "��", "��" };

const char* NAME[305] = { "ΰ", "��", "��", "��", "��", "��", "ǿ", "��", "ƽ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "־", "��", "��", "��", "��", "ɽ", "��", "��", "��", "��", "��", "��", "��", "Ԫ", "ȫ", "��", "ʤ", "ѧ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "˳", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ï", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "׳", "��", "˼", "Ⱥ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ԣ", "��", "��", "��", "��", "��", "��", "��", "ǫ", "��", "��", "��", "֮", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ά", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʿ", "��", "��", "��", "��", "��", "��", "��", "��", "ʱ", "̩", "ʢ", "��", "��", "Ӣ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "֥", "��", "Ƽ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "÷", "��", "��", "��", "��", "��", "��", "ѩ", "��", "��", "��", "ϼ", "��", "��", "ݺ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "�", "Ҷ", "�", "�", "�", "��", "��", "��", "��", "��", "ɺ", "ɯ", "��", "��", "��", "ٻ", "��", "�", "��", "�", "�", "ӱ", "¶", "��", "��", "�", "��", "��", "��", "��", "��", "��", "��", "ü", "��", "��", "��", "ޱ", "ݼ", "��", "�", "Է", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ܿ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "Ӱ", "��", "֦", "˼", "��", "��", "Ʈ", "��", "�", "��", "��", "��", "��", "��", "ɺ", "ɯ", "��", "��", "��", "ٻ", "��", "��", "��", "��", "Է", "�", "ܰ", "�", "��", "��", "��", "԰", "��", "ӽ", "��", "��", "��", "��", "ع", "��", "��", "��", "ˬ", "��", "��", "��", "ϣ" };

const char* course[741] = {
    "רҵ����",
    "��ѧ",
    "�߼�ѧ",
    "�ڽ�ѧ",
    "����ѧ",
    "����ѧ",
    "����ͳ��ѧ",
    "���񾭼ù���",
    "��Դ�뻷������ѧ",
    "���񾭼�ѧ",
    "��Դ����",
    "�Ͷ�����ѧ",
    "���ù���",
    "���־���",
    "����ѧ",
    "˰��ѧ",
    "����ѧ",
    "���ڹ���",
    "����ѧ",
    "Ͷ��ѧ",
    "������ѧ",
    "���ù���",
    "���������",
    "����ѧ",
    "����������",
    "���ڿƼ�",
    "���ʾ�����ó��",
    "ó�׾���",
    "��ѧ",
    "֪ʶ��Ȩ",
    "����ѧ",
    "���÷��չ����뷨�ɷ���",
    "���ʾ�ó����",
    "˾������ѧ",
    "��������",
    "����ѧ������ѧ",
    "��������",
    "�⽻ѧ",
    "������������ʹ�ϵ",
    "����ѧ������ѧ����ѧ",
    "������֯��ȫ������",
    "���ѧ",
    "��Ṥ��",
    "����ѧ",
    "Ů��ѧ",
    "����ѧ",
    "����ѧ",
    "�������",
    "����ѧ",
    "��ѧ�������",
    "�й���������ʷ",
    "˼�����ν���",
    "���˼��������",
    "�ΰ�ѧ",
    "���ѧ",
    "�߷�����",
    "����ѧ",
    "��Ȯ����",
    "���÷������",
    "�߷�ָ��",
    "����ָ��",
    "����ѧ",
    "�����鱨ѧ",
    "����ѧ",
    "��������ѧ",
    "���⾯��",
    "���ڰ�ȫ����",
    "����ָ����ս��",
    "�������ѧ",
    "����ִ��",
    "�������ι���",
    "�������",
    "���뾳����",
    "���־���",
    "�������ι���",
    "����ѧ",
    "��ѧ����",
    "���Ľ���",
    "��������ѧ",
    "��������",
    "ѧǰ����",
    "Сѧ����",
    "�������",
    "���Ľ���",
    "��������ѧ",
    "��������",
    "��֪��ѧ�뼼��",
    "�ںϽ���",
    "��������",
    "�˶�ѵ��",
    "�������ָ�������",
    "���������崫ͳ����",
    "�˶������ѧ",
    "�˶�����",
    "��������",
    "����ѵ��",
    "��ѩ�˶�",
    "���Ӿ����˶������",
    "������������",
    "��������",
    "�˶���������",
    "��������ѧ",
    "������",
    "������ʽ���",
    "�й���������������ѧ",
    "�ŵ�����ѧ",
    "Ӧ������ѧ",
    "����ѧ",
    "�й��������Ļ�",
    "���﷭��",
    "ɣ����",
    "Ӣ��",
    "����",
    "����",
    "����",
    "��������",
    "��������",
    "����",
    "��˹��",
    "������",
    "���ɱ���",
    "����ѧ",
    "�����������",
    "צ����",
    "��������",
    "���������",
    "ӡ����������",
    "ӡ����",
    "����կ��",
    "������",
    "�����",
    "������",
    "�ɹ���",
    "ɮ٤����",
    "̩��",
    "�ڶ�����",
    "ϣ������",
    "Խ����",
    "������",
    "˹��ϣ����",
    "������������",
    "����������",
    "������",
    "�ݿ���",
    "˹�工����",
    "����������",
    "��������",
    "�����",
    "����ά����",
    "��������",
    "ϣ����",
    "��������",
    "�������",
    "̩�׶���",
    "��ʲͼ��",
    "������",
    "�ϼ�����",
    "�Ჴ����",
    "���޵�����",
    "������",
    "������",
    "�ڿ�����",
    "Ų����",
    "������",
    "������",
    "��������",
    "����ά����",
    "��������",
    "˹����������",
    "��ɳ������",
    "�������",
    "��������",
    "���ȱ����",
    "��³��",
    "������",
    "����",
    "����Ӣ��",
    "��ķ������",
    "������˹��",
    "��������",
    "��������",
    "��̩��������",
    "Լ³����",
    "����������",
    "����˹����",
    "��³������",
    "�����ݽ���",
    "����������",
    "�������",
    "��������",
    "��������",
    "���Ա�����",
    "��Ħ����",
    "����¶���",
    "������",
    "�����������",
    "�׶���˹��",
    "ë����",
    "������",
    "��Ħ����",
    "�������",
    "��˹������",
    "������",
    "�¶���",
    "��άϣ��",
    "쳼���",
    "���Ⱥ��ë����",
    "¡����",
    "¬ɭ����",
    "¬������",
    "Ŧ����",
    "Ƥ����",
    "������",
    "��������",
    "����ѧ",
    "�㲥����ѧ",
    "���ѧ",
    "����ѧ",
    "�༭����ѧ",
    "��������ý��",
    "���ֳ���",
    "ʱ�д���",
    "���������봫��",
    "��չ",
    "��ʷѧ",
    "����ʷ",
    "����ѧ",
    "�����벩���ѧ",
    "���ﱣ������",
    "��������������ʷ",
    "�Ļ��Ų�",
    "������ѧ",
    "��ѧ��Ӧ����ѧ",
    "��Ϣ������ѧ",
    "���������ѧ",
    "���ݼ��㼰Ӧ��",
    "����ѧ",
    "Ӧ������ѧ",
    "������",
    "��ѧ",
    "ϵͳ��ѧ�빤��",
    "������Ϣ��ѧ",
    "��ѧ",
    "Ӧ�û�ѧ",
    "��ѧ����ѧ",
    "���ӿ�ѧ�빤��",
    "��Դ��ѧ",
    "��ѧ����ѧ�뼼��",
    "����ѧ",
    "�����ѧ",
    "��Ȼ��������Դ����",
    "���ĵ��������滮",
    "������Ϣ��ѧ",
    "������ѧ",
    "Ӧ������ѧ",
    "�������빤��",
    "�����ѧ",
    "������",
    "������Դ�뻷��",
    "���º���ѧ",
    "��������ѧ",
    "�ռ��ѧ�뼼��",
    "���ּ��ֿ�ѧ�빤��",
    "����ѧ",
    "����ѧ",
    "������Ϣ��ѧ�뼼��",
    "������ѧ",
    "�����ѧ",
    "���＼��",
    "������Ϣѧ",
    "��̬ѧ",
    "���Ͽ�ѧ",
    "�񾭿�ѧ",
    "����ѧ",
    "Ӧ������ѧ",
    "ͳ��ѧ",
    "Ӧ��ͳ��ѧ",
    "������Ӧ����ѧ",
    "������ѧ",
    "��е����",
    "��е������켰���Զ���",
    "���ϳ��ͼ����ƹ���",
    "��е���ӹ���",
    "��ҵ���",
    "����װ������ƹ���",
    "��������",
    "�������񹤳�",
    "��е���ռ���",
    "΢����ϵͳ����",
    "���缼������",
    "����ά�޹��̽���",
    "�������칤��",
    "���ܳ�������",
    "������ѧ�빤��",
    "����Դ��������",
    "�������칤��",
    "���ܽ������",
    "Ӧ��װ�������빤��",
    "��ؼ���������",
    "��������",
    "���ܸ�֪����",
    "���Ͽ�ѧ�빤��",
    "��������",
    "���ϻ�ѧ",
    "ұ�𹤳�",
    "�������Ϲ���",
    "�޻��ǽ������Ϲ���",
    "�߷��Ӳ����빤��",
    "���ϲ����빤��",
    "������Ͽ�ѧ�빤��",
    "��ʯ�����Ϲ���ѧ",
    "���Ӽ����빤��",
    "���ܲ���",
    "���ײ����뼼��",
    "����Դ����������",
    "������ƿ�ѧ�빤��",
    "���ϲ��ϳ��͹���",
    "���ܲ�����ṹ",
    "��Դ�붯������",
    "��Դ�뻷��ϵͳ����",
    "����Դ��ѧ�빤��",
    "���ܿ�ѧ�빤��",
    "��Դ���񹤳�",
    "�������̼����Զ���",
    "���ܵ�����Ϣ����",
    "��Դ������",
    "�������������ܿ���",
    "����������ܻ�",
    "���¹���",
    "��Դ����������",
    "������Ϣ����",
    "���ӿ�ѧ�뼼��",
    "ͨ�Ź���",
    "΢���ӿ�ѧ�빤��",
    "�����Ϣ��ѧ�빤��",
    "��Ϣ����",
    "�㲥���ӹ���",
    "ˮ������",
    "���ӷ�װ����",
    "���ɵ�·����뼯��ϵͳ",
    "ҽѧ��Ϣ����",
    "��ų������߼���",
    "�粨����������",
    "������Ϣ��ѧ�뼼��",
    "���Ź��̼�����",
    "Ӧ�õ��Ӽ�������",
    "�˹�����",
    "������Ϣ����",
    "���Ե���ѧ",
    "���ܲ�ع���",
    "�Զ���",
    "�����ͨ�ź������",
    "�����˹���",
    "��������",
    "�˵缼������ƹ���",
    "����װ����ϵͳ",
    "��ҵ����",
    "���ܹ����봴�����",
    "�������ѧ�뼼��",
    "�������",
    "���繤��",
    "��Ϣ��ȫ",
    "����������",
    "����ý�弼��",
    "���ܿ�ѧ�뼼��",
    "�ռ���Ϣ�����ּ���",
    "��������������",
    "���ݿ�ѧ������ݼ���",
    "����ռ䰲ȫ",
    "��ý�弼��",
    "��Ӱ����",
    "���ܼ���",
    "�����ѧ�빤��",
    "������ʵ����",
    "����������",
    "�����ѧ�뼼��",
    "��ľ����",
    "������������ԴӦ�ù���",
    "����ˮ��ѧ�빤��",
    "�������������ܻ�",
    "���е��¿ռ乤��",
    "��·������ɺӹ���",
    "��������",
    "���ܽ���",
    "��ľ��ˮ���뺣�󹤳�",
    "��ľ��ˮ���뽻ͨ����",
    "����ˮϵͳ����",
    "ˮ��ˮ�繤��",
    "ˮ����ˮ��Դ����",
    "�ۿں����뺣������",
    "ˮ�񹤳�",
    "ˮ����ѧ�빤��",
    "��湤��",
    "ң�п�ѧ�뼼��",
    "��������",
    "���������",
    "����ռ���Ϣ����",
    "��ѧ�����빤��",
    "��ҩ����",
    "��Դѭ����ѧ�빤��",
    "��Դ��ѧ����",
    "��ѧ�����빤ҵ���﹤��",
    "������ȫ����",
    "Ϳ�Ϲ���",
    "��ϸ����",
    "���ʹ���",
    "���鼼���빤��",
    "��Դ���鹤��",
    "����ˮ��ѧ�빤��",
    "���ε�ѧ��滮����",
    "኿󹤳�",
    "ʯ�͹���",
    "����ӹ�����",
    "�������˹���",
    "������Դ����",
    "������������",
    "���ܲɿ󹤳�",
    "��֯����",
    "��װ����빤��",
    "��֯������빤��",
    "��װ����빤�ս���",
    "˿������빤��",
    "�ữ����",
    "��װ����",
    "ӡˢ����",
    "�����㾫�����빤��",
    "��ױƷ�����빤��",
    "��ͨ����",
    "��ͨ����",
    "��������",
    "�ֻ�����",
    "���м���",
    "��ͨ�豸����ƹ���",
    "��������̹���",
    "�������ӵ�������",
    "�����ͨ���������",
    "���ֹ��������",
    "�ǻ۽�ͨ",
    "�����뺣�󹤳�",
    "���󹤳��뼼��",
    "������Դ��������",
    "���������",
    "���պ��칤��",
    "����������빤��",
    "���������칤��",
    "��������������",
    "�������������������Ϲ���",
    "������������ɿ���",
    "�������ʺ�����",
    "��������������Ϣ����",
    "���˼�ʻ������ϵͳ����",
    "���ܷ���������",
    "����ϵͳ�빤��",
    "�������乤��",
    "̽���Ƶ�����Ƽ���",
    "��ҩ�����뱬ը����",
    "������Դ�����빤��",
    "װ�׳�������",
    "��Ϣ�Կ�����",
    "��������ϵͳ����",
    "�˹�����˼���",
    "���������˰�ȫ",
    "��������",
    "�˻������ȼ�Ϲ���",
    "ũҵ����",
    "ũҵ��е�������Զ���",
    "ũҵ������",
    "ũҵ������������Դ����",
    "ũҵˮ������",
    "�������ι���",
    "ũҵ����װ������",
    "ɭ�ֹ���",
    "ľ�Ŀ�ѧ�빤��",
    "�ֲ�����",
    "�Ҿ�����빤��",
    "������ѧ�빤��",
    "��������",
    "������ѧ",
    "������̬����",
    "�����豸����",
    "��Դ������ѧ",
    "ˮ�ʿ�ѧ�뼼��",
    "����ҽѧ����",
    "��֫���ι���",
    "�ٴ����̼���",
    "��������",
    "ʳƷ��ѧ�빤��",
    "ʳƷ�����밲ȫ",
    "��ʳ����",
    "��Ʒ����",
    "��ƹ���",
    "���������Ѿƹ���",
    "ʳƷӪ����������",
    "�����Ӫ������",
    "ʳƷ��ȫ����",
    "ʳƷӪ���뽡��",
    "ʳ�þ���ѧ�빤��",
    "�׾����칤��",
    "����ѧ",
    "����滮",
    "�羰԰��",
    "��ʷ������������",
    "�˾ӻ�����ѧ�뼼��",
    "�������",
    "�ǻ۽����뽨��",
    "��ȫ����",
    "Ӧ�����������",
    "ְҵ��������",
    "���﹤��",
    "������ҩ",
    "�ϳ�����ѧ",
    "���¿�ѧ����",
    "��������",
    "��ͨ������",
    "��ȫ��������",
    "������������",
    "���վ�Ԯָ���뼼��",
    "���ֿ���",
    "���簲ȫ��ִ��",
    "����������",
    "������ָͧ���뼼��",
    "���ݾ�����",
    "ʳƷҩƷ����������鼼��",
    "ũѧ",
    "԰��",
    "ֲ�ﱣ��",
    "ֲ���ѧ�뼼��",
    "���ӿ�ѧ�빤��",
    "��ʩũҵ��ѧ�빤��",
    "��ѧ",
    "�̲�",
    "Ӧ�������ѧ",
    "ũ�ս���",
    "԰�ս���",
    "�ǻ�ũҵ",
    "�����ѧ�빤��",
    "ũҩ����",
    "����ũҩ��ѧ�빤��",
    "ũҵ��Դ�뻷��",
    "Ұ����������Ȼ����������",
    "ˮ���������Į������",
    "�����ʿ�ѧ�빤��",
    "���ؿ�ѧ�뼼��",
    "�����ѧ",
    "��ѧ",
    "��ѧ",
    "���ö���ѧ",
    "��ҵ��ѧ",
    "���Ϲ���",
    "�ǻ���ҵ��ѧ�빤��",
    "����ҽѧ",
    "����ҩѧ",
    "��ֲ�����",
    "ʵ�鶯��ѧ",
    "����ҽѧ",
    "��ҽ��������",
    "��ѧ",
    "԰��",
    "ɭ�ֱ���",
    "������",
    "ˮ����ֳѧ",
    "������ҵ��ѧ�뼼��",
    "ˮ���ѧ�뼼��",
    "ˮ������ҽѧ",
    "��ҵ��ѧ",
    "��ƺ��ѧ�빤��",
    "����ҽѧ",
    "����ҽѧ",
    "����ҽѧ��ѧ",
    "�ٴ�ҽѧ",
    "����ѧ",
    "ҽѧӰ��ѧ",
    "���ӹ�ҽѧ",
    "����ҽѧ",
    "����ҽѧ",
    "����ѧ",
    "��ǻҽѧ",
    "Ԥ��ҽѧ",
    "ʳƷ������Ӫ��ѧ",
    "���ױ���ҽѧ",
    "�����ල",
    "ȫ�򽡿�ѧ",
    "�˶��빫������",
    "��ҽѧ",
    "�������ѧ",
    "��ҽѧ",
    "��ҽѧ",
    "άҽѧ",
    "׳ҽѧ",
    "��ҽѧ",
    "��ҽѧ",
    "��ҽѧ",
    "��ҽ����ѧ",
    "��ҽ����ѧ",
    "��ҽ����ѧ",
    "��ҽ���˿�ѧ",
    "����ҽ�ٴ�ҽѧ",
    "ҩѧ",
    "ҩ���Ƽ�",
    "�ٴ�ҩѧ",
    "ҩ�¹���",
    "ҩ�����",
    "ҩ�ﻯѧ",
    "����ҩѧ",
    "��ױƷ��ѧ�뼼��",
    "��ҩѧ",
    "��ҩ��Դ�뿪��",
    "��ҩѧ",
    "��ҩѧ",
    "��ҩ��ҩ",
    "�в�ҩ���������",
    "��ҽѧ",
    "ҽѧ���鼼��",
    "ҽѧʵ�鼼��",
    "ҽѧӰ����",
    "���ӹ�ѧ",
    "��������ѧ",
    "��ǻҽѧ����",
    "�������������",
    "���������￵��ѧ",
    "������������",
    "������ҵ����",
    "����ҽѧ����",
    "����ҽҩ���ݿ�ѧ",
    "����Ӱ�񹤳�",
    "����ѧ",
    "����ѧ",
    "�����ѧ",
    "��Ϣ��������Ϣϵͳ",
    "���̹���",
    "���ز����������",
    "�������",
    "���ܹ���",
    "��������",
    "�����ݹ�����Ӧ��",
    "�������",
    "�������",
    "Ӧ������",
    "���̹���",
    "�г�Ӫ��",
    "���ѧ",
    "�������",
    "��������",
    "������Դ����",
    "���ѧ",
    "�ʲ�����",
    "��ҵ����",
    "�Ļ���ҵ����",
    "�Ͷ���ϵ",
    "�������������",
    "�����ƽ���",
    "�г�Ӫ������",
    "����ҵ����",
    "��ҵ����",
    "ũ�־��ù���",
    "ũ������չ",
    "������ҵ����",
    "��������",
    "�Ͷ�����ᱣ��",
    "������Դ����",
    "���й���",
    "���ع���",
    "��ͨ����",
    "���¹���",
    "������ϵѧ",
    "�������������",
    "�������ڹ���",
    "ҽ�Ʋ�Ʒ����",
    "ҽ�Ʊ���",
    "���Ϸ������",
    "���ؼ�����߰�ȫ",
    "���ⰲȫ����",
    "��Ȼ��Դ�Ǽ������",
    "ͼ���ѧ",
    "����ѧ",
    "��Ϣ��Դ����",
    "��������",
    "��������",
    "ኹ�����",
    "��Ӧ������",
    "��ҵ����",
    "��׼������",
    "����������",
    "��������",
    "�������񼰷���",
    "�羳��������",
    "���ι���",
    "�Ƶ����",
    "��չ���������",
    "���ι�����������",
    "����ʷ��",
    "��������",
    "�������Ļ��Ų�����",
    "���ֱ���",
    "����ѧ",
    "������������������",
    "�赸����",
    "�赸ѧ",
    "�赸�ർ",
    "�赸����",
    "���շ������������",
    "��������",
    "��������",
    "�����赸",
    "���ֽ���",
    "����",
    "Ϸ��ѧ",
    "��Ӱѧ",
    "Ϸ��Ӱ����ѧ",
    "�㲥���ӱർ",
    "Ϸ��Ӱ�ӵ���",
    "Ϸ��Ӱ���������",
    "¼������",
    "��������������",
    "����",
    "Ӱ����Ӱ������",
    "Ӱ�Ӽ���",
    "Ϸ�����",
    "����ѧ",
    "�滭",
    "����",
    "��Ӱ",
    "�鷨ѧ",
    "�й���",
    "ʵ������",
    "��ý������",
    "���ﱣ�����޸�",
    "����",
    "��ά����",
    "�������ѧ",
    "�Ӿ��������",
    "�������",
    "��Ʒ���",
    "��װ��������",
    "��������",
    "��������",
    "����ý������",
    "������Ƽ�",
    "�մ��������",
    "��ý������",
    "��װ���"
};

