#include <iostream>
#include <ctime>

using namespace std;


template<typename T>
class List {
public:
    List();
    ~List();

    void add(T nData);
    void buble_sort();
    void show();

    template<typename T>
    class SNode {
    public:
        T nData;
        SNode* pPrev, * pNext;
        SNode(T nData = T(), SNode* pPrev = nullptr,
            SNode* pNext = nullptr)
        {
            this->nData = nData;
            this->pPrev = pPrev;
            this->pNext = pNext;
        }
    };

    void swap_pointer_for_two_elements(SNode <T>* pFirst, SNode <T>* pSecond);
    SNode <T>* pHead;
};

template<typename T>
List<T>::List() {
    pHead = nullptr;
}

template<typename T>
List<T>::~List() {
    while (pHead) {
        SNode<T>* ptemp = pHead;
        pHead = pHead->pNext;
        delete ptemp;
    }
}

//функция добавления элемента в конец списка
template<typename T>
void List<T>::add(T nData)
{
    if (pHead == nullptr) {
        pHead = new SNode<T>(nData);
    }
    else {
        SNode<T>* pCurrent = pHead;

        while (pCurrent->pNext != nullptr) {
            pCurrent = pCurrent->pNext;
        }
        pCurrent->pNext = new SNode<T>(nData);
        pCurrent->pNext->pPrev = pCurrent;
    }
}

//функция реализующая сортировку методом пузырька в двусвязном списке, переставляя указатели
template<typename T>
void List<T>::buble_sort() {
    //размер списка
    int nSize = 0;
    //проверка списка на отсортированность
    bool bCheck = true;

    SNode<T>* pTemp = pHead;
    while (pTemp) {
        pTemp = pTemp->pNext;
        nSize++;
    }
    if (nSize == 1) {
        cout << "Для списка состоящего из одного элемента, сортировка не возможна." << endl;
        return;
    }

    //если больше двух то true, иначе false

    SNode<T>* pFirst = pHead;
    SNode<T>* pSecond = pFirst->pNext;

    //смысл переменной nCounter_in_cycle 
    //в следующем, после каждого прохода, 
    //один элемент абсолютно точно занимает 
    //своё место, в моём случае,
    //это элемент с максимальным значением, 
    //следовательно, на следующей итерации я могу
    //смотреть до элемента предпоследнего элемента
    //затем до элемента который был перед предпоследним
    //и так далее
    int nCounter_in_cycle = 1;

    //как только bCheck после выполнения 
    //сортировки примет значение false,
    //то список отсортирован
    while (bCheck) {
        bCheck = false;
        //Здесь nSize - nCounter_in_cycle, это 
        //оптимизация количества элементов которые
        //нужно просматривать
        for (int i = 0; i < nSize - nCounter_in_cycle; i++) {
            if ((pFirst->nData) > (pSecond->nData)) {
                swap_pointer_for_two_elements(pFirst, pSecond);
                //перестановка произошла
                bCheck = true;
            }
            else {
                pFirst = pFirst->pNext;
            }
            pSecond = pFirst->pNext;
        }

        // Сдвигаем голову в начало списка
        while (pHead->pPrev) {
            pHead = pHead->pPrev;
        }

        //Начинаем обход с головы списка
        pFirst = pHead;
        pSecond = pFirst->pNext;
        //инкерминтируем счётчик
        nCounter_in_cycle++;
    }
}

template<typename T>
void List<T>::show() {
    SNode<T>* pTemp = pHead;
    if (!(pTemp->pPrev) && !(pTemp->pNext)) {
        cout << "NULL <--- [" << pTemp->nData << "] ---> NULL" << endl << endl;
    }
    else {
        while (pTemp->pNext) {

            //вывод для первого элемента
            if (!(pTemp->pPrev) && pTemp->pNext) {
                cout << "NULL <--- [" << pTemp->nData << "] <--->";
            }

            //вывод для всех элементов начиная со второго, кроме последнего
            else {
                cout << " [" << pTemp->nData << "] <--->";
            }
            pTemp = pTemp->pNext;
        }
        //вывод последнего элемента
        cout << " [" << pTemp->nData << "] ---> NULL";
        cout << endl << endl;
    }

}

//функция меняющая указатели, вызывается
//из функции buble_sort
template<typename T>
void List<T>::swap_pointer_for_two_elements(SNode<T>* pFirst, SNode<T>* pSecond) {
    //Тут стандартная смена указателей, 
    //в случае когда два элемента
    //требуют сортировки
    pSecond->pPrev = pFirst->pPrev;
    pFirst->pPrev = pSecond;
    pFirst->pNext = pSecond->pNext;
    pSecond->pNext = pFirst;

    //для первого элемента
    if (!(pSecond->pPrev) && pFirst->pNext) {
        pFirst->pNext->pPrev = pFirst;
    }

    //для последнего
    else if (!(pFirst->pNext) && pSecond->pPrev) {
        pSecond->pPrev->pNext = pSecond;
    }

    //для оставшихся
    else if (pFirst->pNext && pSecond->pPrev) {
        pFirst->pNext->pPrev = pFirst;
        pSecond->pPrev->pNext = pSecond;
    }

}

int main() {
    setlocale(LC_ALL, "ru");
    List<int> CList;
    int nCount;				//количество элементов в списке
    srand(time(NULL));
    try {
        cout << "Введите количество элементов списка:\n";
        cin >> nCount;
        if (nCount < 1) throw 1;
    }
    catch (int nCount) {
        cout << "Введены неправильные данные.\n";
        return 0;
    }
    for (int i = 0; i < nCount; i++)
    {
        //создаем элементы списка и заполняем их
        CList.add(rand() % 200 - 100);
    }
    cout << "Неотсортированный список:" << endl << endl;
    CList.show();
    CList.buble_sort();

    if (nCount > 1) {
        cout << "Отсортированный список:" << endl << endl;
        CList.show();
    }

}
