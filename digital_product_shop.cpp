#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
const int TABLE_SIZE = 101;
struct Person{
	string username;
	string password;
	string filename;
	string identity;
	string f_user_ID;
	string f_username;
	string f_password;
	string f_identity;
	string user_id;
};
class login_system{
	private:
		Person P;
	protected:
		void check_identity(){
			if(P.identity == "user"){
				P.filename = "user.txt";
			}
			else if(P.identity == "admin"){
				P.filename = "admin.txt";
			}
			else{
				cout<<"Identity is NOT Valid"<<endl;
			}
		}
		int check_username(){
			ifstream readfile(P.filename);
		
			if(!readfile){
				cout << "Unable to open file "<<P.filename<<endl;
	        	exit(0);
			}
			while(readfile>>P.f_user_ID>>P.f_username>>P.f_password>>P.f_identity){
				if(P.f_username == P.username ){
					cout<<"Your name is repeat.Please change!"<<endl;
					readfile.close();
					return 0;
				}
			}
			readfile.close();
			if(P.username.empty()){
				cout<<"- Please do not use blank as your username"<<endl;
		        return 0;
			}
			for (char ch : P.username){
		        if (ch == ' ') {  
		            std::cout << "- Please do not contain space" << std::endl;
		            return 0;
		        }
		    }
		    return 1;
		}
		int check_password(){
			if(P.password.empty()){
				cout<<"- Please do not use blank as your username"<<endl;
		        return 0;
			}
			
			for (char ch : P.password){
		        if (ch == ' ') {  
		            std::cout << "- Please do not contain space" << std::endl;
		            return 0;
		        }
		    }
		    return 1;
		}
	public:
	login_system(){	
		P.username = "";
		P.password = "";
		P.filename = "";
		P.identity = "";
		P.f_user_ID = "";
		P.f_username = "";
		P.f_password = "";
		P.f_identity = "";
		P.user_id = "";
	}
	~login_system(){
		P.username = "";
		P.password = "";
		P.filename = "";
		P.identity = "";
		P.f_user_ID = "";
		P.f_username = "";
		P.f_password = "";
		P.f_identity = "";
		P.user_id = "";
		cout<<"Your Personal Data Have Been Clear."<<endl;
	}
	int login(){
		check_identity();
		ifstream readfile(P.filename);
		int count = 3;
		do{
			cout<<"You have "<<count<<" chances to try login."<<endl;
			cout<<"Enter your name:";
			cin.ignore();
			getline(cin,P.username);
			cout<<"Enter your password:";
			getline(cin,P.password);
			while(readfile>>P.f_user_ID>>P.f_username>>P.f_password>>P.f_identity){
				if(P.f_username == P.username && P.f_password == P.password){
					cout<<"Successful Login!!"<<endl;
					P.user_id = P.f_user_ID;
					P.identity = P.f_identity;
					readfile.close();
					return 0;
				}
			}
			count--;
		}while(count>0);
		exit(0);
	}
	int register_user(){
		system("cls");
		set("user");
		string line;
		int line_count = 1;
		check_identity();
		cin.ignore();
		cout<<"Enter your name:";
		getline(cin,P.username);
		cout<<"Enter your password:";
		getline(cin,P.password);
		int U_Valid = check_username();
		int P_Valid = check_password();
		if(U_Valid == 1 && P_Valid == 1){
			ofstream openfile(P.filename,ios::app);
			ifstream readfile(P.filename);
			if(!openfile){
			cout << "Unable to open file "<<P.filename<<endl;
        	exit(0);
			}
			if(!readfile){
			cout << "Unable to open file "<<P.filename<<endl;
        	exit(0);
			}
			while (getline(readfile, line)) {
		        line_count++;
		    }
			openfile<<"U"<<line_count<<" "<<P.username<<" "<<P.password<<" "<<P.identity<<endl;
			openfile.close();
			readfile.close();
			cout<<"Successful Registered Account "<<"U"<<line_count<<" "<<P.username<<endl;
			system("pause");
			return 0;
		}else{
			cout<<"Failed to Register Account "<<P.user_id<<" "<<P.username<<endl;
			system("pause");
			return 0;
		}
		return 0;
	}
	void set(string Identity){
		P.identity = Identity;
	}
};
class HashTable {
public:
    int *table;
    HashTable() {
        table = new int[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = -1;
        }
    }
    ~HashTable() {
        delete[] table;
    }
    void hash(int key) {
        int HK = key % TABLE_SIZE;
        if (collision(HK)) {
            quadratic_probing(key);
        } else {
            table[HK] = key;
        }
    }
    void hash(string key) {
        int hashcode = getHashCode(key);
        int HK = hashcode % TABLE_SIZE;
        if (collision(HK)) {
            quadratic_probing(hashcode);
        } else {
            table[HK] = hashcode;
        }
    }
    bool collision(int HK) {
        if (table[HK] != -1) {
            return true;
        }
        return false;
    }
    int quadratic_probing(int key) {
        int times = 1;
        for (int i = 0; i < TABLE_SIZE; i++) {
            int hash_value = (key + (times * times)) % TABLE_SIZE;
            if (collision(hash_value)) {
                times++;
            } else {
                table[hash_value] = key;
                return 1;
            }
        }
        return 0;
    }
    bool exists(int key) {
        int HK = key % TABLE_SIZE;
        if (table[HK] == key) {
            return true;
        }
        int times = 1;
        while (times < TABLE_SIZE) {
            int hash_value = (key + times * times) % TABLE_SIZE;
            if (table[hash_value] == key) {
                return true;
            } else if (table[hash_value] == -1) {
                return false;
            }
            times++;
        }
        return false;
    }
    bool exists(string key) {
        int hashcode = getHashCode(key);
        int HK = hashcode % TABLE_SIZE;
        if (table[HK] == hashcode) {
            return true;
        }
        int times = 1;
        while (times < TABLE_SIZE) {
            int hash_value = (hashcode + times * times) % TABLE_SIZE;
            if (table[hash_value] == hashcode) {
                return true;
            } else if (table[hash_value] == -1) {
                return false;
            }
            times++;
        }
        return false;
    }
    int getHashCode(string key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum;
    }
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " --> " << table[i] << endl;
        }
    }
};

//selectionsort
class SelectionSort {
public:
    void sort(int arr[], int n) {
        int i, j, min_idx;
        for (i = 0; i < n - 1; i++) {
            min_idx = i;
            for (j = i + 1; j < n; j++)
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            swap(arr[min_idx], arr[i]);
        }
    }

    void printArray(int arr[], int size) {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
    
    void sortWithRecord(int price[], string model[], string brand[], int RAM[], int n) {
        int i, j, min_idx;
        for (i = 0; i < n - 1; i++) {
            min_idx = i;
            for (j = i + 1; j < n; j++)
                if (price[j] < price[min_idx])
                    min_idx = j;
            swap(price[min_idx], price[i]);
            swap(model[min_idx], model[i]);
            swap(brand[min_idx], brand[i]);
            swap(RAM[min_idx], RAM[i]);
        }
    }

    void printFull(string model[], string brand[], int price[], int RAM[], int n) {
        for (int i = 0; i < n; i++){
            cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] << " RAM : " << RAM[i] << endl;
        }
    }
    
    void printterbalik(string model[], string brand[], int price[], int RAM[], int count){
    	for (int i = count - 1; i >= 0; i--){
            cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] << " RAM : " << RAM[i] << endl;
        }
	}

private:
    void swap(int &xp, int &yp) {
        int temp = xp;
        xp = yp;
        yp = temp;
    }
    void swap(string &xp, string &yp) {
        string temp = xp;
        xp = yp;
        yp = temp;
    }
};

//inserttionsort
class InsertSort {
public:
    void insertionSort(int arr[], int n) {
        int i, key, j;
        for (i = 1; i < n; i++) {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    void insertionsortall(int price[], string model[], string brand[], int RAM[], int n) {
        int i, keyPrice, j, keyRAM;
        string keyModel, keyBrand;

        for (i = 1; i < n; i++) {
            keyPrice = price[i];
            keyModel = model[i];
            keyBrand = brand[i];
            keyRAM = RAM[i];

            j = i - 1;

            while (j >= 0 && price[j] > keyPrice) {
                price[j + 1] = price[j];
                model[j + 1] = model[j];
                brand[j + 1] = brand[j];
                RAM[j + 1] = RAM[j];
                j = j - 1;
            }
            price[j + 1] = keyPrice;
            model[j + 1] = keyModel;
            brand[j + 1] = keyBrand;
            RAM[j + 1] = keyRAM;
        }
    }

    void printArray(int arr[], int n) {
        for (int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void printFull(string model[], string brand[], int price[], int RAM[], int n) {
        for (int i = 0; i < n; i++){
            cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] << " RAM : " << RAM[i] << endl;
        }
    }
    void printterbalik(string model[], string brand[], int price[], int RAM[], int count){
    	for (int i = count - 1; i >= 0; i--){
    		cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] << " RAM : " << RAM[i] << endl;
		}
	}
};

class Product{
	public:
	struct Item {
		string P_ID;
	    string model;
	    string brand;
	    float price;
	    int RAM;
	    int quantity;
	    Item *next;
	};
	virtual void add_record() = 0;
	virtual void display() = 0;
	virtual void edit() = 0;
	
	virtual void deleteproduct() = 0;
};
class Laptop  : public Product{
	private:
    Item* head, * temp;
    Item Cache;
    public:
    	Laptop(){
    		head = nullptr;
    		temp = nullptr;
    		int count = 0;	
    		ifstream readfile("Laptop.txt");
		    if(!readfile){
			cout << "Unable to open file Laptop.txt"<<endl;
        	exit(0);
			}
			while (readfile >>Cache.model >> Cache.brand >> Cache.price >> Cache.RAM){
				Item* newItem = new Item();
		        newItem->model = Cache.model;
		        newItem->brand = Cache.brand;
		        newItem->price = Cache.price;
		        newItem->RAM = Cache.RAM;
		        newItem->P_ID = "L" + to_string(count++);
		        newItem->next = nullptr;
		        if (head == nullptr) {
		            head = newItem;
		        } else {
		            temp = head;
		            while (temp->next != nullptr) {
		                temp = temp->next;
		            }
		            temp->next = newItem;
		        }
			}
		}
    	void add_record() override {
		    int size;
		    do{
		    cout << "How many Laptop do you want to add? ";
		    cin >> size;
		    if (size <= 0) {
		        cout << "Invalid number of Laptop!\n";
		        return;
		    }
			}while(size<=0);
		    ifstream readfile("Laptop.txt");
		    if (!readfile) {
		        cout << "Unable to open file Laptop.txt" << endl;
		        exit(0);
		    }
		    string line;
		    int count = 0;
		    while (getline(readfile, line)) {
		        count++;
		    }
		    readfile.close();
		    ofstream writefile("Laptop.txt", ios::app);
		    if (!writefile) {
		        cout << "Unable to open file Laptop.txt for writing!" << endl;
		        exit(0);
		    }
		    for (int i = 0; i < size; i++) {
		        Item* newItem = new Item();
		        newItem->P_ID = "L" + to_string(count + i); 
		        cout << "\nEnter details for Laptop #" << (i + 1) << endl;
		        cout << "-------------------------" << endl;
		        cout << "Enter Laptop Model: ";
		        cin.ignore();
		        getline(cin, newItem->model);
		        cout << "Enter Brand: ";
		        getline(cin, newItem->brand);
		        cout << "Enter Price: ";
		        cin >> newItem->price;
		        cout << "Enter RAM (GB): ";
		        cin >> newItem->RAM;
		        cout << "Enter Quantity: ";
		        cin >> newItem->quantity;
		        newItem->next = nullptr;
		        if (head == nullptr) {
		            head = newItem;
		        } else {
		            temp = head;
		            while (temp->next != nullptr) {
		                temp = temp->next;
		            }
		            temp->next = newItem;
		        }
		        writefile << newItem->model << " " 
                  << newItem->brand << " " 
                  << newItem->price << " " 
                  << newItem->RAM << endl;
		        cout << "Laptop added successfully!\n";
		    }
		    writefile.close(); 
		}
		void display() override {
			temp = head;
		    cout << "\nLaptop List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand<< "\tPrice: " << temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
		        temp = temp->next;
		    }
		}
		void edit() override{
			string product_id;
			temp = head;
		    cout << "\nLaptop List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand<< "\tPrice: " << temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
		        temp = temp->next;
		    }
		    cout<<"Enter the Product ID you want to change :";
		    cin>>product_id;
			temp = head;
		    while (temp != nullptr) {
		        if (temp->P_ID == product_id) {
		            cout << "Enter New Laptop Model: ";
		            cin.ignore();
		            getline(cin, temp->model);
		            
		            cout << "Enter New Brand: ";
		            getline(cin, temp->brand);
		            
		            cout << "Enter New Price: ";
		            cin >> temp->price;
		            
		            cout << "Enter New RAM (GB): ";
		            cin >> temp->RAM;
		            
		            cout << "Enter New Quantity : ";
		            cin >> temp->quantity;
		            
		            cout << "Laptop details updated successfully!\n";
		            return;
		        }
		        temp = temp->next;
		    }
		}
		void searchLaptop() {
		    HashTable priceTable;
		    HashTable modelTable;
		
		    ifstream readfile2("Laptop.txt");
		    while (readfile2 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM) {
		        priceTable.hash(Cache.price);
		        modelTable.hash(Cache.model);
		    }
		    readfile2.close();
		    cout << "Search by:\n1. Price\n2. Model\nChoose (1/2): ";
		    int option;
		    cin >> option;
		    if (option == 1) {
		        int searchPrice;
		        cout << "Enter price to search: ";
		        cin >> searchPrice;
		
		        if (priceTable.exists(searchPrice)) {
		            cout << "Price found! Matching laptops:" << endl;
		
		            ifstream readfile3("Laptop.txt");
		            while (readfile3 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM) {
		                if (Cache.price == searchPrice) {
		                    cout << "Model: " << Cache.model << ", Brand: " << Cache.brand
		                         << ", Price: RM " << Cache.price << ", RAM: " << Cache.RAM << endl;
		                }
		            }
		            readfile3.close();
		        } else {
		            cout << "Price not found." << endl;
		        }
		    } else if (option == 2) {
		        string searchModel;
		        cout << "Enter model to search: ";
		        cin >> searchModel;
		        if (modelTable.exists(searchModel)) {
		            cout << "Model found! Matching laptops:" << endl;
		            ifstream readfile4("Laptop.txt");
		            while (readfile4 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM) {
		                if (Cache.model == searchModel) {
		                    cout << "Model: " << Cache.model << ", Brand: " << Cache.brand
		                         << ", Price: RM " << Cache.price << ", RAM: " << Cache.RAM << endl;
		                }
		            }
		            readfile4.close();
		        } else {
		            cout << "Model not found." << endl;
		        }
		    } else {
		        cout << "Invalid option." << endl;
		    }
			system("pause");
		}
		void sortLaptop() {
		    string model[TABLE_SIZE], brand[TABLE_SIZE];
		    int price[TABLE_SIZE], RAM[TABLE_SIZE];
		    int count = 0;
		
		    ifstream readfile2("Laptop.txt");
		
		    while (readfile2 >> model[count] >> brand[count] >> price[count] >> RAM[count]) {
		        count++;
		    }
		
		    for (int i = 0; i < count; i++){
		        cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] << " RAM : " << RAM[i] << endl;
		    }
		
		    int choice;
		    cout << "\nChoose sort from:\n";
		    cout << "1. Low to High\n";
		    cout << "2. High to Low\n";
		    cout << "Enter choice (1 or 2): ";
		    cin >> choice;
		
		    SelectionSort s;
		    s.sortWithRecord(price, model, brand, RAM, count);
		
		    if (choice == 1) {
		        cout << "Sorted laptop data (Low to High):\n";
		        s.printFull(model, brand, price, RAM, count);
		    } else if (choice == 2) {
		        cout << "Sorted laptop data (High to Low):\n";
		        s.printterbalik(model, brand, price, RAM, count);
		    } else {
		        cout << "Invalid choice!" << endl;
		    }
		    system("pause");
		}
		void deleteproduct() override {
		    string product_id;
		    temp = head;
		
		    cout << "\nLaptop List:\n";
		    while (temp != nullptr) {
		        cout << "Product ID: " << temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand
		             << "\tPrice: " << temp->price << "\tRAM: " << temp->RAM << "GB" << endl;
		        temp = temp->next;
		    }
		
		    cout << "Enter the Product ID you want to delete: ";
		    cin >> product_id;
		
		    temp = head;
		    Item* prev = nullptr;   
		
		    while (temp != nullptr) {
		        if (temp->P_ID == product_id) {
		            if (prev == nullptr) {
		                head = temp->next;
		            } else {
		                prev->next = temp->next;
		            }
		            delete temp;
		            cout << "Laptop deleted successfully!\n";
		            return;
		        }
		        prev = temp;
		        temp = temp->next;
		    }
		
		    cout << "Laptop with Product ID " << product_id << " not found.\n";
		}


};
class Handphone : public Product{
	private:
    Item* head, * temp;
    Item Cache;
    public:
    	Handphone() {
    		head = nullptr;
    		temp = nullptr;
    		int count = 0;
    		ifstream readfile("Handphone.txt");
		    
		    if(!readfile){
			cout << "Unable to open file Laptop.txt"<<endl;
        	exit(0);
			}
			while (readfile >>Cache.model >> Cache.brand >> Cache.price >> Cache.RAM){
				Item* newItem = new Item();
		        newItem->model = Cache.model;
		        newItem->brand = Cache.brand;
		        newItem->price = Cache.price;
		        newItem->RAM = Cache.RAM;
		        newItem->P_ID = "H" + to_string(count++);
		        newItem->next = nullptr;
		        if (head == nullptr) {
		            head = newItem;
		        } else {
		            temp = head;
		            while (temp->next != nullptr) {
		                temp = temp->next;
		            }
		            temp->next = newItem;
		        }
			}
		}
    	void add_record() override {
		    int size;
		    do{
		    cout << "How many phones do you want to add? ";
		    cin >> size;
		    if (size <= 0) {
		        cout << "Invalid number of phones!\n";
		        return;
		    }
			}while(size<=0);
		    ifstream readfile("Handphone.txt");
		    if (!readfile) {
		        cout << "Unable to open file Handphone.txt" << endl;
		        exit(0);
		    }
		    string line;
		    int count = 0;
		    while (getline(readfile, line)) {
		        count++;
		    }
		    readfile.close();
		    ofstream writefile("Handphone.txt", ios::app);
		    if (!writefile) {
		        cout << "Unable to open file Handphone.txt for writing!" << endl;
		        exit(0);
		    }
		    for (int i = 0; i < size; i++) {
		        Item* newItem = new Item();
		        newItem->P_ID = "H" + to_string(count + i); 
		        cout << "\nEnter details for Phone #" << (i + 1) << endl;
		        cout << "-------------------------" << endl;
		        cout << "Enter Handphone Model: ";
		        cin.ignore();
		        getline(cin, newItem->model);
		        cout << "Enter Brand: ";
		        getline(cin, newItem->brand);
		        cout << "Enter Price: ";
		        cin >> newItem->price;
		        cout << "Enter RAM (GB): ";
		        cin >> newItem->RAM;
		        cout << "Enter Quantity: ";
		        cin >> newItem->quantity;
		        newItem->next = nullptr;
		        if (head == nullptr) {
		            head = newItem;
		        } else {
		            temp = head;
		            while (temp->next != nullptr) {
		                temp = temp->next;
		            }
		            temp->next = newItem;
		        }
		        writefile << newItem->model << " " 
                  << newItem->brand << " " 
                  << newItem->price << " " 
                  << newItem->RAM << endl;
		        cout << "Phone added successfully!\n";
		    }
		    writefile.close(); 
		}
		void display() override {
			temp = head;
		    cout << "\nLaptop List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand<< "\tPrice: " << temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
		        temp = temp->next;
		    }
		}
		void edit() override{
			string product_id;
			temp = head;
		    cout << "\nHandphone List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand<< "\tPrice: " << temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
		        temp = temp->next;
		    }
		    cout<<"Enter the Product ID you want to change :";
		    cin>>product_id;
			temp = head;
		    while (temp != nullptr) {
		        if (temp->P_ID == product_id) {
		            cout << "Enter New Laptop Model: ";
		            cin.ignore();
		            getline(cin, temp->model);
		            cout << "Enter New Brand: ";
		            getline(cin, temp->brand);
		            cout << "Enter New Price: ";
		            cin >> temp->price; 
		            cout << "Enter New RAM (GB): ";
		            cin >> temp->RAM;
		            cout << "Enter New Quantity : ";
		            cin >> temp->quantity;
		            cout << "Handphone details updated successfully!\n";
		            return;
		        }
		        temp = temp->next;
		    }
		}
		void searchHandphone() {
		    HashTable priceTable;
		    HashTable modelTable;
		
		    ifstream readfile2("Handphone.txt");
		    while (readfile2 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM) {
		        priceTable.hash(Cache.price);
		        modelTable.hash(Cache.model);
		    }
		    readfile2.close();
		
		    cout << "Search by:\n1. Price\n2. Model\nChoose (1/2): ";
		    int option;
		    cin >> option;
		
		    if (option == 1) {
		        int searchPrice;
		        cout << "Enter price to search: ";
		        cin >> searchPrice;
		
		        if (priceTable.exists(searchPrice)) {
		            cout << "Price found! Matching handphones:" << endl;
		
		            ifstream readfile3("Handphone.txt");
		            while (readfile3 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM) {
		                if (Cache.price == searchPrice) {
		                    cout << "Model: " << Cache.model << ", Brand: " << Cache.brand
		                         << ", Price: RM " << Cache.price << ", RAM: " << Cache.RAM << endl;
		                }
		            }
		            readfile3.close();
		        } else {
		            cout << "Price not found." << endl;
		        }
		
		    } else if (option == 2) {
		        string searchModel;
		        cout << "Enter model to search: ";
		        cin >> searchModel;
		
		        if (modelTable.exists(searchModel)) {
		            cout << "Model found! Matching handphones:" << endl;
		
		            ifstream readfile4("Handphone.txt");
		            while (readfile4 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM) {
		                if (Cache.model == searchModel) {
		                    cout << "Model: " << Cache.model << ", Brand: " << Cache.brand
		                         << ", Price: RM " << Cache.price << ", RAM: " << Cache.RAM << endl;
		                }
		            }
		            readfile4.close();
		        } else {
		            cout << "Model not found." << endl;
		        }
		    } else {
		        cout << "Invalid option." << endl;
		    }
		
		    system("pause");
		}
		void sortHandphone() {
		    string model[TABLE_SIZE], brand[TABLE_SIZE];
		    int price[TABLE_SIZE], RAM[TABLE_SIZE];
		    int count = 0;
		
		    ifstream readfile2("Handphone.txt");
		
		    while (readfile2 >> model[count] >> brand[count] >> price[count] >> RAM[count]) {
		        count++;
		    }
		
		    cout << "Original handphone data:\n";
		    for (int i = 0; i < count; i++)
		        cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] << " RAM : " << RAM[i] << endl;
		
		    int choice;
		    cout << "Choose sort order:\n";
		    cout << "1. Low to High\n";
		    cout << "2. High to Low\n";
		    cout << "Enter choice (1 or 2): ";
		    cin >> choice;
		
		    InsertSort is;
		    is.insertionsortall(price, model, brand, RAM, count);
		
		    if (choice == 1) {
		        cout << "Sorted handphone data (Low to High):\n";
		        is.printFull(model, brand, price, RAM, count);
		    } else if (choice == 2) {
		        cout << "Sorted handphone data (High to Low):\n";
		        is.printterbalik(model, brand, price, RAM, count);
		    } else {
		        cout << "Invalid choice!" << endl;
		    }
		}
		void deleteproduct() override {
		    string product_id;
		    temp = head;
		
		    cout << "\nHandphone List:\n";
		    while (temp != nullptr) {
		        cout << "Product ID: " << temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand
		             << "\tPrice: " << temp->price << "\tRAM: " << temp->RAM << "GB" << endl;
		        temp = temp->next;
		    }
		
		    cout << "Enter the Product ID you want to delete: ";
		    cin >> product_id;
		
		    temp = head;
		    Item* prev = nullptr;
		
		    while (temp != nullptr) {
		        if (temp->P_ID == product_id) {
		            if (prev == nullptr) {
		                head = temp->next;
		            } else {
		                prev->next = temp->next;
		            }
		            delete temp;
		            cout << "Handphone deleted successfully!\n";
		            return;
		        }
		        prev = temp;
		        temp = temp->next;
		    }
		
		    cout << "Handphone with Product ID " << product_id << " not found.\n";
		}

};
class User : public login_system{	
	public:
		int Menu(){
			int back = 0;
			int choice;
			while(back == 0){
				system("cls");
				cout<<"*******************"<<endl;
				cout<<"     User Menu     "<<endl;
				cout<<"*******************"<<endl;
				cout<<"1.Login\n2.Register\n3.Back to previous"<<endl;
				cout<<"Enter your choice:";
				cin>>choice;
				cin.ignore();
				switch(choice){
					case 1:
						set("user");
						back = login();
						break;
					case 2:
						back = register_user();
						break;
					case 3:
						return 1;
						break;
				}
			}
			return 0;
		}
};
class Admin : public login_system{
	public:
		int Menu(){
			int back = 0;
			int choice;
			while(back == 0){
				system("cls");
				cout<<"--------------------"<<endl;
				cout<<"     Admin Menu     "<<endl;
				cout<<"--------------------"<<endl;
				cout<<"1.Login\n2.Back to previous"<<endl;
				cout<<"Enter your choice:";
				cin>>choice;
				switch(choice){
					case 1:
						set("admin");
						login();
						back = functionMenua();
						break;
					case 2:
						return 1;
						break;
				}
			}
			return 0;
		}	
		int functionMenua() {
	        system("cls");
	        int choice;
	        int back = 0;
			Laptop laptop;
			Handphone handphone;
	        while (back == 0) {
	            cout << "-----------------------------" << endl;
	            cout << "     Admin Function Menu     " << endl;
	            cout << "-----------------------------" << endl;
	            cout << "1. Add Laptop\n2. Add Handphone\n3. Edit Laptop\n4. Edit Handphone\n5. Display Laptop\n6. Display Handphone\n7. Search Laptop \n8. Search Handphone\n9. Sort Laptop\n10.Sort Handphone\n11.Delate Laptop\n12.Delete Handphone\n-1. Back to previous" << endl;
	            cout << "Enter your choice:";
	            cin >> choice;
	            switch (choice) {
	                case 1: {
	                    laptop.add_record();  
	                    break;
	                }
	                case 2: {
	                    handphone.add_record();  
	                    break;
	                }
	                case 3: {
	                    laptop.edit();
	                    break;
	                }
	                case 4: {
	                    handphone.edit();
	                    break;
	                }
	                case 5: {
	                    laptop.display();
	                    break;
	                }
	                case 6: {
	                    handphone.display();
	                    break;
	                }
					case 7: {
	                    laptop.searchLaptop();  
	                    break;
	                }
					case 8: {
	                    handphone.searchHandphone();  
	                    break;
	                }
	                case 9: {
	                    laptop.sortLaptop();  
	                    break;
	                }
	                case 10: {
	                    handphone.sortHandphone();  
	                    break;
	                }
	                case 11:
	                	laptop.deleteproduct();
	                	break;
	                case 12:
	                	handphone.deleteproduct();
	                	break;
	                case -1:
	                    return 0;  
	                    break;
	            }
	        }
	        return 0;
	    }
};

int main(){
	int choice,back=1;
	User U;
	Admin A;
	while (back == 1) {
		system("cls");
		cout<<"========================================"<<endl;
		cout<<"   Welcome to LK Digital Product Shop   "<<endl;
		cout<<"========================================"<<endl;
		cout<<"1.Admin\n2.User\n3.Exit"<<endl;
		cout<<"Enter your choice:";
		cin>>choice;
		switch(choice){
			case 1:
				back = A.Menu();
				break;
			case 2:
				back = U.Menu();
				break;
			case 3:
				exit(0);
				break;
		}
	}	
	return 0;
}