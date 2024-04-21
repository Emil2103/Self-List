#include <iostream>

template<typename T>
class SelfList{
private:
    struct Node{
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    
    Node* head;
    
public:
    
    SelfList() : head(nullptr){}
    
    ~SelfList(){
        while(head){
            Node* temp = head;
            head = temp->next;
            delete temp;
        }
    }
    
    class Iterator{
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node){}
        
        Iterator& operator++(){
            if(current){
                current = current->next;
            }
            return *this;
        }
        
        Iterator operator++(int){
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        T& operator*() const{
            return current->data;
        }
        
        bool operator!=(const Iterator& other) const{
            return current != other.current;
        }
    };
    
    // Проверка на пустой лист
    bool is_empty(){
        return head == nullptr;
    }
    
    // Функция для добавления элемента в начало листа
    void insert_node_begin(const T& data){
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }
    
    // Функция для добавления элемента в конец листа
    void insert_node_end(const T& data){
        Node* newNode = new Node(data);
        if(is_empty()){
            head = newNode;
        }else{
            Node* temp = head;
            //цикл для нахождения последнего элемента в списке
            while(temp->next){
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    
    
    //Функция выыводящая все элементы листа
    void show_list(){
        if(is_empty()){
            return;
        }
        
        Node* temp = head;
        while(temp){
            std::cout << temp->data << ' ';
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    
    
    // ФУнкция для проверки есть ли элемент в списке
    bool search_node(const T& data){
        Node* temp = head;
        while(temp){
            if(temp->data == data){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    
    
    // Функция для вставки элемента между двумя другими (существующими в листе)
    void insertBetween(const T& data, const T& prevData, const T& nextData){
        Node* newNode = new Node(data);
        Node* prevNode = nullptr;
        Node* nextNode = head;
        
        //Находим узел, после которого нужно вставить значение
        while(nextNode && nextNode->data != prevData){
            prevNode = nextNode;
            nextNode = nextNode->next;
        }
        
        // Проверяем, найден ли узел с предыдущим значением
        if (!nextNode) {
            std::cout << "Node with prevData not found." << std::endl;
            delete newNode; // Удаляем newNode, так как его не нужно вставлять в список
            return;
        }
        
        // Перемещаем указатель на следующий узел
        prevNode = nextNode;
        nextNode = nextNode->next;
        
        // Проверяем, найден ли узел с следующим значением
        if (!nextNode || nextNode->data != nextData) {
            std::cout << "Node with nextData not found." << std::endl;
            delete newNode; // Удаляем newNode, так как его не нужно вставлять в список
            return;
        }
        
        // Вставляем новый узел между prevNode и nextNode
        prevNode->next = newNode;
        newNode->next = nextNode;
    }
    
    
    // Удаление выбранного элемента из листа
    void remove_node(const T& data){
        Node* prev = nullptr;
        Node* next = head;
        while(next){
            if(next->data == data){
                if(prev){
                    prev->next = next->next;
                }else{
                    head = next->next;
                }
                delete next;
                return;
            }
            prev = next;
            next = next->next;
        }
        std::cout << "Element " << data << " not found in the list" << std::endl;
    }
    
    // Удаление первого элемента из листа
    void remove_first_node(){
        if (head) {
            Node* first = head;
            head = head->next;
            delete first;
        } else {
            std::cout << "List is empty, cannot remove first node." << std::endl;
        }
    }
    
    // Удаление последнего элемента из листа
    void remove_last_node(){
        if(head){
            if(!head->next){
                delete head;
                head = nullptr;
                return;
            }
            Node* prev = nullptr;
            Node* next = head;
            while(next->next){
                prev = next;
                next = next->next;
            }
            delete next;
            prev->next =  nullptr;
            
        }else {
            std::cout << "List is empty, cannot remove last node." << std::endl;
        }
    }
    
    // Функция для вывода количества элементов в списке
    int size(){
        int count = 0;
        Node* temp = head;
        while(temp){
            count++;
            temp = temp->next;
        }
        return count;
    }
    
    Iterator begin(){
        return Iterator(head);
    }
    
    Iterator end(){
        return Iterator(nullptr);
    }
};

int main(){
    SelfList<int> list;
    list.insert_node_end(15);
    list.insert_node_end(10);
    list.insert_node_end(3);
    list.show_list();
    list.insertBetween(4, 10, 3);
    list.insertBetween(77, 10, 4);
    list.show_list();
    list.remove_node(77);
    list.show_list();
    std::cout << list.size() << std::endl;
    list.insert_node_begin(80);
    list.show_list();
    std::cout << "------" << std::endl;
    list.remove_first_node();
    list.show_list();
    std::cout << "------" << std::endl;
    list.remove_last_node();
    list.show_list();
    std::cout << "------" << std::endl;
    list.remove_last_node();
    list.remove_last_node();
    list.remove_last_node();
    list.remove_last_node();
    list.remove_first_node();
    
    // Пример использования итератора для обхода списка
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}
