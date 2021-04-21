#include <iostream>
#include <ctime>

template<typename T>
class TNode 
{
public:
	T nData;
	TNode* pPrev, * pNext;
	TNode(T nData)
	{
		this->nData = nData;
		this->pPrev = nullptr;
		this->pNext = nullptr;
	}
};

template<typename T>
class TList 
{
private:
    TNode <T>* m_pHead;

public:
    TList();
    ~TList();

    void InsertToTail(T nData);

    void bubbleSort();

    void DisplayList();

    void SwapPointers(TNode <T>* pCurrent, TNode <T>* pCurrentNext);
};

template<typename T>
TList<T>::TList() 
{
    m_pHead = nullptr;
}

template<typename T>
TList<T>::~TList() 
{
    while (m_pHead) 
    {
        TNode<T>* ptemp = m_pHead;
        m_pHead = m_pHead->pNext;
        delete ptemp;
    }
}

//функция добавления элемента в конец списка
template<typename T>
void TList<T>::InsertToTail(T nData)
{

    if (m_pHead == nullptr) 
    {
        m_pHead = new TNode<T>(nData);
    }

    else 
    {

        TNode<T>* pCurrent = m_pHead;

        while (pCurrent->pNext != nullptr) 
        {
            pCurrent = pCurrent->pNext;
        }

        pCurrent->pNext = new TNode<T>(nData);

        pCurrent->pNext->pPrev = pCurrent;
    }
}

//функция реализующая сортировку методом пузырька в двусвязном списке, переставляя указатели
template<typename T>
void TList<T>::bubbleSort() 
{

    if (!m_pHead && !m_pHead->pNext) return;

    //размер списка
    int nSize = 0;


    TNode<T>* pTemp = m_pHead;

    while (pTemp) 
    {
        pTemp = pTemp->pNext;
        nSize++;
    }

    TNode<T>* pCurrent = m_pHead;

    for (int nCounter = 0; nCounter < nSize; nCounter++ )
    {

        bool bSorted = false;

        for (int i = 0; i < nSize - nCounter - 1; i++) 
        {

            TNode<T>* pCurrentNext = pCurrent->pNext;

            if ((pCurrent->nData) > (pCurrentNext->nData)) 
            {

                SwapPointers(pCurrent, pCurrentNext);

                //перестановка произошла
                bSorted = true;

                if (pCurrent == m_pHead)
                {
                    m_pHead = pCurrentNext;
                }
            }

            else 
            {
                pCurrent = pCurrent->pNext;
            }

        }

        if (!bSorted) break;

        pCurrent = m_pHead;
    }
}

template<typename T>
void TList<T>::DisplayList() 
{

    TNode<T>* pCurrent = m_pHead;

    while (pCurrent)
    {
        std::cout << pCurrent->nData << " ";
        pCurrent = pCurrent->pNext;
    }

    std::cout << std::endl;
}

template<typename T>
void TList<T>::SwapPointers(TNode<T>* pCurrent, TNode<T>* pCurrentNext) 
{

    pCurrentNext->pPrev = pCurrent->pPrev;
    pCurrent->pPrev = pCurrentNext;
    pCurrent->pNext = pCurrentNext->pNext;
    pCurrentNext->pNext = pCurrent;

    if (!(pCurrentNext->pPrev) && pCurrent->pNext) 
    {
        pCurrent->pNext->pPrev = pCurrent;
    }

    else if (!(pCurrent->pNext) && pCurrentNext->pPrev) 
    {
        pCurrentNext->pPrev->pNext = pCurrentNext;
    }

    else if (pCurrent->pNext && pCurrentNext->pPrev) 
    {
        pCurrent->pNext->pPrev = pCurrent;
        pCurrentNext->pPrev->pNext = pCurrentNext;
    }

}

int main() {
    using namespace std;
    
    setlocale(LC_ALL, "ru");

    TList<int> list;

    int nCount;

    srand((unsigned int)time(NULL));

    try 
    {
        cout << "Введите количество элементов списка:\n";
        cin >> nCount;
        if (nCount < 1) throw 1;
    }
    catch (int nCount) 
    {
        cout << "Введены неправильные данные.\n";
        return 0;
    }
    for (int i = 0; i < nCount; i++)
    {
        list.InsertToTail(rand() % 200 - 100);
    }

    cout << "Неотсортированный список:" << endl << endl;
    list.DisplayList();

    list.bubbleSort();

    if (nCount > 1) 
    {
        cout << "Отсортированный список:" << endl << endl;
        list.DisplayList();
    }

}
