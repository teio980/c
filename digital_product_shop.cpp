#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
const int TABLE_SIZE = 101;
bool checkEmpty(string input);
bool containH(string input);
bool containL(string input);
void makepayment(string userID);
void salesSummaryReport();
void viewsalesSummaryReport();
void consumptionReport(string userID);
void viewconsumptionReport(string userID);
struct purchaseRecord {
    string O_ID;
    string U_ID;
    string P_ID;
    string model;
    double price;
    int quantity;
    double total_price;
    string status;
};
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
			for (int i = 0; i < P.username.length(); i++) {
			    if (P.username[i] == ' ') {
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
	string getUserID(){
		return P.user_id;
	}
	friend void editHandphoneCart(login_system &user);
	friend void editLaptopCart(login_system &user);
	friend void viewCart(login_system &user);
	friend void deleteHandphoneCart(login_system &user);
	friend void deleteLaptopCart(login_system &user);
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
    
    void sortWithRecord(double price[], string model[], string brand[], int RAM[],int QTY[], int n) {
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

    void printFull(string model[], string brand[], double price[], int RAM[],int QTY[], int n) {
        for (int i = 0; i < n; i++){
            cout <<"Model : "<< model[i] << " Brand : " << brand[i] <<fixed<<setprecision(2) << " Price : RM" << price[i] << " RAM : " << RAM[i] <<"Quantity: "<< QTY[i] << endl;
        }
    }
    
    void printterbalik(string model[], string brand[], double price[], int RAM[],int QTY[], int count){
    	for (int i = count - 1; i >= 0; i--){
            cout <<"Model : "<< model[i] << " Brand : " << brand[i] <<fixed<<setprecision(2) << " Price : RM" << price[i] << " RAM : " << RAM[i] <<"Quantity: "<< QTY[i]  << endl;
        }
	}

private:
    void swap(int &xp, int &yp) {
        int temp = xp;
        xp = yp;
        yp = temp;
    }
    void swap(double &xp, double &yp) {
        double temp = xp;
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

    void insertionsortall(double price[], string model[], string brand[], int RAM[], int QTY[], int n) {
        int i,  j, keyRAM, keyQTY;
        double keyPrice;
        string keyModel, keyBrand;

        for (i = 1; i < n; i++) {
            keyPrice = price[i];
            keyModel = model[i];
            keyBrand = brand[i];
            keyRAM = RAM[i];
            keyQTY = QTY[i];

            j = i - 1;

            while (j >= 0 && price[j] > keyPrice) {
                price[j + 1] = price[j];
                model[j + 1] = model[j];
                brand[j + 1] = brand[j];
                RAM[j + 1] = RAM[j];
                QTY[j + 1] = QTY[j];
                j = j - 1;
            }
            price[j + 1] = keyPrice;
            model[j + 1] = keyModel;
            brand[j + 1] = keyBrand;
            RAM[j + 1] = keyRAM;
            QTY[j + 1] = keyQTY;
        }
    }

    void printArray(int arr[], int n) {
        for (int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void printFull(string model[], string brand[], double price[], int RAM[],int QTY[], int n) {
        for (int i = 0; i < n; i++){
            cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] 
			<< " RAM : " << RAM[i] << "Quantity:" << QTY[i] << endl;
        }
    }
    void printterbalik(string model[], string brand[], double price[], int RAM[],int QTY[], int count){
    	for (int i = count - 1; i >= 0; i--){
    		cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" << price[i] 
			<< " RAM : " << RAM[i] << "Quantity:" << QTY[i] << endl;
		}
	}
};

class Product{
	public:
	struct Item {
		string P_ID;
	    string model;
	    string brand;
	    double price;
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
			while (readfile >>Cache.P_ID>>Cache.model >> Cache.brand >> Cache.price >> Cache.RAM >>Cache.quantity){
				Item* newItem = new Item();
		        newItem->model = Cache.model;
		        newItem->brand = Cache.brand;
		        newItem->price = Cache.price;
		        newItem->RAM = Cache.RAM;
		        newItem->quantity = Cache.quantity;
		        newItem->P_ID = Cache.P_ID;
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
		    int L_ID,H_ID,O_ID;
		    do{
		    cout << "How many laptop do you want to add? ";
		    cin >> size;
		    if (size <= 0) {
		        cout << "Invalid number of laptop!\n";
		        return;
		    }
			}while(size<=0);
		    ofstream writefile("Laptop.txt", ios::app);
		    if (!writefile) {
		        cout << "Unable to open file Handphone.txt for writing!" << endl;
		        exit(0);
		    }
		    for (int i = 0; i < size; i++) {
		    	Item* newItem = new Item();
		    	ifstream readfile("id_record.txt");
			    if (!readfile) {
			        cout << "Unable to open file Laptop.txt" << endl;
			        exit(0);
			    }
			    readfile >> L_ID >> H_ID >> O_ID;
			    readfile.close();
		        newItem->P_ID = "L" + to_string(L_ID); 
		        cout << "\nEnter details for Laptop #" << (i + 1) << endl;
		        cout << "-------------------------" << endl;
		        cout << "Enter Laptop Model: ";
		        cin.ignore();
		        getline(cin, newItem->model);
		        while (checkEmpty(newItem->model)) {
				    cout << "- Input cannot be empty or contain space."<<endl;
				    cout<<"You may use the _ to replace"<<endl;
				    cout<<"Enter Laptop Model: ";
				    getline(cin, newItem->model);
				}
		        cout << "Enter Brand: ";
		        getline(cin, newItem->brand);
		        while (checkEmpty(newItem->brand)) {
				    cout << "- Input cannot be empty or contain space."<<endl;
				    cout<<"You may use the _ to replace"<<endl;
				    cout<<"Enter Brand: ";
				    getline(cin, newItem->brand);
				}
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
                  writefile 
				  <<newItem->P_ID <<" " 
				  <<newItem->model << " " 
				  <<newItem->brand << " " 
                  << newItem->price << " "
				  << newItem->quantity << " " 
                  << newItem->RAM << endl;
                ofstream openfile("id_record.txt");
			    if (!openfile) {
			        cout << "Unable to open file Laptop.txt" << endl;
			        exit(0);
			    }
			    openfile << (L_ID+1) <<" "<< H_ID << " "<< O_ID;
			    openfile.close();
		        cout << "Laptop added successfully!\n";
		    }
		    writefile.close(); 
		}
		void display() override {
			temp = head;
		    cout << "\nLaptop List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand<< "\tPrice: " <<fixed<<setprecision(2)<< temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
		        temp = temp->next;
		    }
		}
		void edit() override{
			string product_id;
			temp = head;
		    cout << "\nLaptop List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand<< "\tPrice: " <<fixed<<setprecision(2)<< temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
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
		            break;
		        }
		        temp = temp->next;
		    }
		    
		    ofstream outFile("Laptop.txt"); 
		    if (!outFile) {
		        cerr << "Error opening file for writing!" << endl;
		        return;
		    }
		    
		    temp = head;
		    while (temp != nullptr) {
		        outFile << temp->P_ID << " " << temp->model << " " << temp->brand << " "
		                << temp->price << " " << temp->RAM << " " << temp->quantity << endl;
		        temp = temp->next;
		    }
		    
		    outFile.close();
		    cout << "Product updated successfully!" << endl;
		    return;
		}
		void searchLaptop() {
		    HashTable priceTable;
		    HashTable modelTable;
		
		    ifstream readfile2("Laptop.txt");
		    while (readfile2 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM >> Cache.quantity) {
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
		            while (readfile3 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM >> Cache.quantity) {
		                if (Cache.price == searchPrice) {
		                    cout << "Model: " << Cache.model << ", Brand: " << Cache.brand
		                         << ", Price: RM " <<fixed<<setprecision(2)<< Cache.price << ", RAM: " << Cache.RAM << " " << Cache.quantity << endl;
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
		            while (readfile4 >> Cache.model >> Cache.brand >> Cache.price >> Cache.RAM >> Cache.quantity) {
		                if (Cache.model == searchModel) {
		                    cout << "Model: " << Cache.model << ", Brand: " << Cache.brand
		                         << ", Price: RM " <<fixed<<setprecision(2)<< Cache.price << ", RAM: " << Cache.RAM << "Quantity" << Cache.quantity << endl;
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
		    double price[TABLE_SIZE];
			int RAM[TABLE_SIZE], QTY[TABLE_SIZE];
		    int count = 0;
		
		    ifstream readfile2("Laptop.txt");
		
		    while (readfile2 >> model[count] >> brand[count] >> price[count] >> RAM[count]>>QTY[count]) {
		        count++;
		    }
		
		    for (int i = 0; i < count; i++){
		        cout <<"Model : "<< model[i] << " Brand : " << brand[i] << " Price : RM" <<fixed<<setprecision(2)<< price[i] << " RAM : " << RAM[i] <<"Quantity:"<<QTY[i]<<endl;
		    }
		
		    int choice;
		    cout << "\nChoose sort from:\n";
		    cout << "1. Low to High\n";
		    cout << "2. High to Low\n";
		    cout << "Enter choice (1 or 2): ";
		    cin >> choice;
		
		    SelectionSort s;
		    s.sortWithRecord(price, model, brand, RAM, QTY, count);
		
		    if (choice == 1) {
		        cout << "Sorted laptop data (Low to High):\n";
		        s.printFull(model, brand, price, RAM, QTY, count);
		    } else if (choice == 2) {
		        cout << "Sorted laptop data (High to Low):\n";
		        s.printterbalik(model, brand, price, RAM, QTY, count);
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
		             << "\tPrice: " <<fixed<<setprecision(2)<< temp->price << "\tRAM: " << temp->RAM << "GB" << endl;
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
		            ofstream outFile("Laptop.txt"); 
				    if (!outFile) {
				        cerr << "Error opening file for writing!" << endl;
				        return;
				    }
				    
				    temp = head;
				    while (temp != nullptr) {
				        outFile << temp->P_ID << " " << temp->model << " " << temp->brand << " "
				                << temp->price << " " << temp->RAM << " " << temp->quantity << endl;
				        temp = temp->next;
				    }
				    
				    outFile.close();
		            cout << "Laptop deleted successfully!\n";
		            return;
		        }
		        prev = temp;
		        temp = temp->next;
		    }
		
		    cout << "Laptop with Product ID " << product_id << " not found.\n";
		}

		void buyLaptop(string U_ID){
			string product_id;
			int L_ID,H_ID,O_ID;
			string order_id;
			login_system L;
			int found = 0;
			int buy_qty;
			double total_price;
			ifstream readfile("id_record.txt");
		    if (!readfile) {
		        cout << "Unable to open file Laptop.txt" << endl;
		        exit(0);
		    }
		    readfile >> L_ID >> H_ID >> O_ID;
		    readfile.close();
		    order_id = "ORD" + to_string(O_ID);
			ofstream openfile("purchase_record.txt",ios::app);
			cin.ignore();
			cout<<"Enter the Product ID you want to add to cart:";
			getline(cin,product_id);
			
			temp = head;
		    while (temp != nullptr) {
		        if (temp->P_ID == product_id) {
		        	found = 1;
		        	cout<<"This is the product's details:"<<endl;
		        	cout<<"-------------------------------------------------------"<<endl;
		            cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand
					<< "\tPrice: " << <<fixed<<setprecision(2)temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
					
					cout<<"How many you want to buy?";
					cin>>buy_qty;
					while(buy_qty>temp->quantity){
						cout<<"Invalid buy quantity. Please Try Again."<<endl;
						cout<<"How many you want to buy?";
						cin>>buy_qty;
					}
					total_price = buy_qty * temp->price;
					if (!openfile) {
				        cerr << "Error opening file  purchase_record.txt for writing!" << endl;
				        return;
				    }
					openfile << order_id << " " << U_ID << " " <<  temp->P_ID << " " << temp->model << " " << temp->price << " " << buy_qty << " " << total_price << " pending" << endl;
					openfile.close();
					cout<<"Your order successful add to cart"<<endl;
					ofstream openfile("id_record.txt");
				    if (!openfile) {
				        cout << "Unable to open file Laptop.txt" << endl;
				        exit(0);
				    }
				    openfile << L_ID <<" "<< H_ID << " "<< (O_ID+1);
				    openfile.close();
					temp->quantity = temp->quantity - buy_qty;
					
					ofstream outFile("Laptop.txt"); 
				    if (!outFile) {
				        cerr << "Error opening file for writing!" << endl;
				        return;
				    }
				    
				    temp = head;
				    while (temp != nullptr) {
				        outFile << temp->P_ID << " " << temp->model << " " << temp->brand << " "
				                << temp->price << " " << temp->RAM << " " << temp->quantity << endl;
				        temp = temp->next;
				    }
				    outFile.close();
					
		            break;
		        }
		        temp = temp->next;
		    }
		    
		    if(found == 0){
		    	cout<<"Invalid Product ID. Please Try Again."<<endl;
			}
		}
		void updateLaptopLinkedList(string selected_P_ID, int change_quantity){
			temp = head;
			int found = 0;
			while (temp != nullptr) {
	        if (temp->P_ID == selected_P_ID) {
	        	found = 1;
	        	if(change_quantity<0){
	        		change_quantity = change_quantity * -1;
	        		temp->quantity += change_quantity;
				}
				else if(change_quantity>=0){
					temp->quantity -= change_quantity;
				}
				break;
		        }
		        temp = temp->next;
		    }
		
		    if (found==0) {
		        cout << "Product ID " << selected_P_ID << " not found in the linked list!" << endl;
		        return;
		    }
		    ofstream openfile("Laptop.txt");
		    if (!openfile) {
		        cerr << "Error opening Laptop.txt for writing!" << endl;
		        return;
		    }
		
		    temp = head;
		    while (temp != nullptr) {
		        openfile << temp->P_ID << " " 
		                << temp->model << " " 
		                << temp->brand << " "
		                << temp->price << " " 
		                << temp->RAM << " " 
		                << temp->quantity << endl;
		        temp = temp->next;
		    }
		
		    openfile.close();
		    cout<<"Laptop data updated"<<endl;
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
			cout << "Unable to open file Handphone.txt"<<endl;
        	exit(0);
			}
			while (readfile >>Cache.P_ID>>Cache.model >> Cache.brand >> Cache.price >> Cache.RAM >> Cache.quantity){
				Item* newItem = new Item();
		        newItem->model = Cache.model;
		        newItem->brand = Cache.brand;
		        newItem->price = Cache.price;
		        newItem->RAM = Cache.RAM;
		        newItem->quantity = Cache.quantity;
		        newItem->P_ID = Cache.P_ID;
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
		    int L_ID,H_ID,O_ID;
		    do{
		    cout << "How many phones do you want to add? ";
		    cin >> size;
		    if (size <= 0) {
		        cout << "Invalid number of phones!\n";
		        return;
		    }
			}while(size<=0);
		    ofstream writefile("Handphone.txt", ios::app);
		    if (!writefile) {
		        cout << "Unable to open file Handphone.txt for writing!" << endl;
		        exit(0);
		    }
		    for (int i = 0; i < size; i++) {
		    	Item* newItem = new Item();
		    	ifstream readfile("id_record.txt");
			    if (!readfile) {
			        cout << "Unable to open file Laptop.txt" << endl;
			        exit(0);
			    }
			    readfile >> L_ID >> H_ID >>O_ID;
			    readfile.close();
		        newItem->P_ID = "H" + to_string(H_ID); 
		        cout << "\nEnter details for Phone #" << (i + 1) << endl;
		        cout << "-------------------------" << endl;
		        cout << "Enter Handphone Model: ";
		        cin.ignore();
		        getline(cin, newItem->model);
		        while (checkEmpty(newItem->model)) {
				    cout << "- Input cannot be empty or contain space."<<endl;
				    cout<<"You may use the _ to replace"<<endl;
				    cout<<"Enter Hanphone Model: ";
				    getline(cin, newItem->model);
				}
		        cout << "Enter Brand: ";
		        getline(cin, newItem->brand);
		        while (checkEmpty(newItem->brand)) {
				    cout << "- Input cannot be empty or contain space."<<endl;
				    cout<<"You may use the _ to replace"<<endl;
				    cout<<"Enter Brand: ";
				    getline(cin, newItem->brand);
				}
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
                  writefile 
				  <<newItem->P_ID <<" " 
				  <<newItem->model << " " 
				  <<newItem->brand << " " 
                  << newItem->price << " "
				  << newItem->quantity << " " 
                  << newItem->RAM << endl;
                ofstream openfile("id_record.txt");
			    if (!openfile) {
			        cout << "Unable to open file Laptop.txt" << endl;
			        exit(0);
			    }
			    openfile << L_ID <<" "<< (H_ID+1) <<" "<<O_ID;
			    openfile.close();
		        cout << "Phone added successfully!\n";
		    }
		    writefile.close(); 
		}
		void display() override {
			temp = head;
		    cout << "\nHandphone List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand
				<< "\tPrice: " <<fixed<<setprecision(2)<< temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
		        temp = temp->next;
		    }
		}
		void edit() override{
			string product_id;
			temp = head;
		    cout << "\nHandphone List:\n";
		    while (temp != nullptr) {
		        cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand
				<< "\tPrice: " <<fixed<<setprecision(2)<< temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
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
		            while (checkEmpty(temp->model)) {
				    cout << "- Input cannot be empty or contain space."<<endl;
				    cout<<"You may use the _ to replace"<<endl;
				    cout << "Enter New Laptop Model: ";
				    getline(cin, temp->model);
					}
		            cout << "Enter New Brand: ";
		            getline(cin, temp->brand);
		            while (checkEmpty(temp->brand)) {
				    cout << "- Input cannot be empty or contain space."<<endl;
				    cout<<"You may use the _ to replace"<<endl;
				    cout << "Enter New Brand: ";
				    getline(cin, temp->brand);
					}
		            cout << "Enter New Price: ";
		            cin >> temp->price; 
		            cout << "Enter New RAM (GB): ";
		            cin >> temp->RAM;
		            cout << "Enter New Quantity : ";
		            cin >> temp->quantity;
		            cout << "Handphone details updated successfully!\n";
		            break;
		        }
		        temp = temp->next;
		    }
		    
		    ofstream outFile("Handphone.txt"); 
		    if (!outFile) {
		        cerr << "Error opening file for writing!" << endl;
		        return;
		    }
		    
		    temp = head;
		    while (temp != nullptr) {
		        outFile << temp->P_ID << " " << temp->model << " " << temp->brand << " "
		                << temp->price << " " << temp->RAM << " " << temp->quantity << endl;
		        temp = temp->next;
		    }
		    
		    outFile.close();
		    cout << "Product updated successfully!" << endl;
		    return;
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
		                         << ", Price: RM " <<fixed<<setprecision(2)<< Cache.price << ", RAM: " << Cache.RAM << endl;
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
		                         << ", Price: RM " <<fixed<<setprecision(2)<< Cache.price << ", RAM: " << Cache.RAM << endl;
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
		    double price[TABLE_SIZE];
			int RAM[TABLE_SIZE],QTY[TABLE_SIZE];
		    int count = 0;
		
		    ifstream readfile2("Handphone.txt");
		
		    while (readfile2 >> model[count] >> brand[count] >> price[count] >> RAM[count] >> QTY[count]) {
		        count++;
		    }
		
		    cout << "Original handphone data:\n";
		    for (int i = 0; i < count; i++)
		        cout <<"Model : "<< model[i] << " Brand : " << brand[i] 
				<< " Price : RM" <<fixed<<setprecision(2)<< price[i] << " RAM : " << RAM[i] << "Quantity" << QTY[i] <<endl;
		
		    int choice;
		    cout << "Choose sort order:\n";
		    cout << "1. Low to High\n";
		    cout << "2. High to Low\n";
		    cout << "Enter choice (1 or 2): ";
		    cin >> choice;
		
		    InsertSort is;
		    is.insertionsortall(price, model, brand, RAM, QTY, count);
		
		    if (choice == 1) {
		        cout << "Sorted handphone data (Low to High):\n";
		        is.printFull(model, brand, price, RAM, QTY, count);
		    } else if (choice == 2) {
		        cout << "Sorted handphone data (High to Low):\n";
		        is.printterbalik(model, brand, price, RAM, QTY, count);
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
		             << "\tPrice: " <<fixed<<setprecision(2)<< temp->price << "\tRAM: " << temp->RAM << "GB" << "\tQuantity:" << temp->quantity << endl;
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
		            ofstream outFile("Handphone.txt"); 
				    if (!outFile) {
				        cerr << "Error opening file for writing!" << endl;
				        return;
				    }
				    
				    temp = head;
				    while (temp != nullptr) {
				        outFile << temp->P_ID << " " << temp->model << " " << temp->brand << " "
				                << temp->price << " " << temp->RAM << " " << temp->quantity << endl;
				        temp = temp->next;
				    }
				    
				    outFile.close();
		            cout << "Handphone deleted successfully!\n";
		            return;
		        }
		        prev = temp;
		        temp = temp->next;
		    }
		
		    cout << "Handphone with Product ID " << product_id << " not found.\n";
		   
		}	
		void buyHandphone(string U_ID){
			string product_id;
			int L_ID,H_ID,O_ID;
			string order_id;
			login_system L;
			int found = 0;
			int buy_qty;
			double total_price;
			ifstream readfile("id_record.txt");
		    if (!readfile) {
		        cout << "Unable to open file Laptop.txt" << endl;
		        exit(0);
		    }
		    readfile >> L_ID >> H_ID >> O_ID;
		    readfile.close();
		    order_id = "ORD" + to_string(O_ID);
			ofstream openfile("purchase_record.txt",ios::app);
			cin.ignore();
			cout<<"Enter the Product ID you want to add to cart:";
			getline(cin,product_id);
			
			temp = head;
		    while (temp != nullptr) {
		        if (temp->P_ID == product_id) {
		        	found = 1;
		        	cout<<"This is the product's details:"<<endl;
		        	cout<<"-------------------------------------------------------"<<endl;
		            cout <<"Product ID: "<<temp->P_ID << "\tModel: " << temp->model << "\tBrand: " << temp->brand
					<< "\tPrice: " << temp->price << "\tRAM: " << temp->RAM << "GB"<<"\tQuantity: " << temp->quantity<<endl;
					
					cout<<"How many you want to buy?";
					cin>>buy_qty;
					while(buy_qty>temp->quantity){
						cout<<"Invalid buy quantity. Please Try Again."<<endl;
						cout<<"How many you want to buy?";
						cin>>buy_qty;
					}
					total_price = buy_qty * temp->price;
					if (!openfile) {
				        cerr << "Error opening file  purchase_record.txt for writing!" << endl;
				        return;
				    }
					openfile << order_id << " " << U_ID << " " <<  temp->P_ID << " " << temp->model << " " << temp->price << " " << buy_qty << " " << total_price << " pending" << endl;
					openfile.close();
					cout<<"Your order successful add to cart"<<endl;
					ofstream openfile("id_record.txt");
				    if (!openfile) {
				        cout << "Unable to open file Laptop.txt" << endl;
				        exit(0);
				    }
				    openfile << L_ID <<" "<< H_ID << " "<< (O_ID+1);
				    openfile.close();
					temp->quantity = temp->quantity - buy_qty;
					
					ofstream outFile("Handphone.txt"); 
				    if (!outFile) {
				        cerr << "Error opening file for writing!" << endl;
				        return;
				    }
				    
				    temp = head;
				    while (temp != nullptr) {
				        outFile << temp->P_ID << " " << temp->model << " " << temp->brand << " "
				                << temp->price << " " << temp->RAM << " " << temp->quantity << endl;
				        temp = temp->next;
				    }
				    outFile.close();
					
		            break;
		        }
		        temp = temp->next;
		    }
		    
		    if(found == 0){
		    	cout<<"Invalid Product ID. Please Try Again."<<endl;
			}
		}
		void updateHandphoneLinkedList(string selected_P_ID, int change_quantity){
			temp = head;
			int found = 0;
			while (temp != nullptr) {
	        if (temp->P_ID == selected_P_ID) {
		            found = 1;
		            if(change_quantity<0){
	        		change_quantity = change_quantity * -1;
	        		temp->quantity += change_quantity;
					}
					else if(change_quantity>=0){
						temp->quantity -= change_quantity;
					}
		            break;
		        }
		        temp = temp->next;
		    }
		
		    if (found==0) {
		        cout << "Product ID " << selected_P_ID << " not found in the linked list!" << endl;
		        return;
		    }
		    ofstream openfile("Handphone.txt");
		    if (!openfile) {
		        cerr << "Error opening Handphone.txt for writing!" << endl;
		        return;
		    }
		
		    temp = head;
		    while (temp != nullptr) {
		        openfile << temp->P_ID << " " 
		                << temp->model << " " 
		                << temp->brand << " "
		                << temp->price << " " 
		                << temp->RAM << " " 
		                << temp->quantity << endl;
		        temp = temp->next;
		    }
		
		    openfile.close();
		    cout<<"Handphone data updated"<<endl;
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
				switch(choice){
					case 1:
						set("user");
						login();
						back = functionMenu();
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
		int functionMenu() {
	        system("cls");
	        int choice;
	        int back = 0;
	        Handphone H;
	        Laptop L;
			
	        while (back == 0) {
	            cout << "-----------------------------" << endl;
	            cout << "     User Function Menu     " << endl;
	            cout << "-----------------------------" << endl;
	            cout << "1. Buy Laptop\n2. Buy Handphone\n3. Edit Laptop Record\n4. Edit Handphone Record\n5. Display Product Available\n6. View Cart";
				cout << "\n7. Search Laptop \n8. Search Handphone\n9. Sort Laptop\n10.Sort Handphone\n11.Cancel Laptop Order\n12.Cancel Handphone Order\n13.Make Payment\n14.Generate Consumption Report\n15.View Consumption Report\n-1. Back to previous" << endl;
	            cout << "Enter your choice:";
	            cin >> choice;
	            switch (choice) {
	                case 1: {
	                    L.display();
	                    L.buyLaptop(getUserID());
	                    break;
	                }
	                case 2: {
	                    H.display();
	                    H.buyHandphone(getUserID());
	                    break;
	                }
	                case 3: {
	                    editLaptopCart(*this);
	                    break;
	                }
	                case 4: {
	                    editHandphoneCart(*this);
	                    break;
	                }
	                case 5: {
	                    L.display();
	                    H.display();
	                    break;
	                }
	                case 6: {
	                    viewCart(*this);
	                    break;
	                }
					case 7: {
	                      
	                    break;
	                }
					case 8: {
	                      
	                    break;
	                }
	                case 9: {
	                      
	                    break;
	                }
	                case 10: {
	                      
	                    break;
	                }
	                case 11:
	                	deleteLaptopCart(*this);
	                	break;
	                case 12:
	                	deleteHandphoneCart(*this);
	                	break;
                	case 13:
	                	makepayment(getUserID());
	                	break;
	                case 14:
	                	consumptionReport(getUserID());
	                	break;
	                case 15:
	                	viewconsumptionReport(getUserID());
	                	break;
	                case -1:
	                    return 0;  
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
	            cout << "1. Add Laptop\n2. Add Handphone\n3. Edit Laptop\n4. Edit Handphone\n5. Display Laptop\n6. Display Handphone";
				cout<<"\n7. Search Laptop \n8. Search Handphone\n9. Sort Laptop\n10.Sort Handphone\n11.Delate Laptop\n12.Delete Handphone\n13.Generate Sales Summary Report\n14.View Sales Summary Report\n-1. Back to previous" << endl;
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
	                case 13:
	                	salesSummaryReport();
	                	break;
	                case 14:
	                	viewsalesSummaryReport();
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

void editHandphoneCart(login_system &user){
	Handphone H;
    purchaseRecord H_record[1000];
    int count = 0;
    ifstream readfile("purchase_record.txt");
    string O_ID, U_ID, P_ID, model, status, cur_U_ID, order_id;
    double price, total_price;
    int quantity, new_quantity, change_quantity;
    int found = 0;
    string selected_P_ID;
    cur_U_ID = user.getUserID();
    if(!readfile){
        cout << "Unable to open file purchase_record.txt" << endl;
        exit(0);
    }
    while (readfile >> O_ID >> U_ID >> P_ID >> model >> price >> quantity >> total_price >> status){
        H_record[count].O_ID = O_ID;
        H_record[count].U_ID = U_ID;
        H_record[count].P_ID = P_ID;
        H_record[count].model = model;
        H_record[count].price = price;
        H_record[count].quantity = quantity;
        H_record[count].total_price = total_price;
        H_record[count].status = status;
        count++;
    }
    readfile.close();
    cout << "Your pending handphone orders:" << endl;
    for(int i = 0; i < count; i++){
        if(H_record[i].U_ID == cur_U_ID && H_record[i].status == "pending" && containH(H_record[i].P_ID)){
            cout << "Order ID: " << H_record[i].O_ID << " Product ID: " << H_record[i].P_ID 
                 << " Model: " << H_record[i].model << " Price: " <<fixed<<setprecision(2)<< H_record[i].price 
                 << " Quantity Purchase: " << H_record[i].quantity 
                 << " Total Price: " << H_record[i].total_price << endl;
        }
    }
    cin.ignore();
    cout << "Enter the Order ID you want to edit: ";
    getline(cin, order_id);
    cout << "Enter the new quantity: ";
    cin >> new_quantity;
    while(new_quantity < 1){
        cout << "Invalid value. Please Try Again. The quantity must be atleast 1." << endl;
        cout<<"If you want to cancel order, please go thought another function."<<endl;
        cout << "Enter the new quantity: ";
        cin >> new_quantity;
    }
    for(int i = 0; i < count; i++){
        if(H_record[i].O_ID == order_id && H_record[i].status == "pending" && containH(H_record[i].P_ID)){
            found = 1;
            selected_P_ID = H_record[i].P_ID;
            change_quantity = new_quantity - H_record[i].quantity;
            H_record[i].quantity = new_quantity;
            H_record[i].total_price = new_quantity * H_record[i].price;
            break;
        }
    }
    if(found == 0){
        cout << "Order ID not found" << endl;
        return;
    }
    ofstream writefile("purchase_record.txt");
    if(!writefile){
        cout << "Unable to open file for writing" << endl;
        return;
    }
    for(int i = 0; i < count; i++){
        writefile << H_record[i].O_ID << " " << H_record[i].U_ID << " " << H_record[i].P_ID << " " 
                  << H_record[i].model << " " << H_record[i].price << " " << H_record[i].quantity << " " 
                  << H_record[i].total_price << " " << H_record[i].status << endl;
    }
    writefile.close();
    H.updateHandphoneLinkedList(selected_P_ID, change_quantity);
    cout << "Order updated successfully!" << endl;
}

void editLaptopCart(login_system &user){
	Laptop L;
    purchaseRecord L_record[1000];
    int count = 0;
    ifstream readfile("purchase_record.txt");
    string O_ID, U_ID, P_ID, model, status, cur_U_ID, order_id;
    double price, total_price;
    int quantity, new_quantity, change_quantity;
    int found = 0;
    string selected_P_ID;
    cur_U_ID = user.getUserID();
    if(!readfile){
        cout << "Unable to open file purchase_record.txt" << endl;
        exit(0);
    }
    while (readfile >> O_ID >> U_ID >> P_ID >> model >> price >> quantity >> total_price >> status){
        L_record[count].O_ID = O_ID;
        L_record[count].U_ID = U_ID;
        L_record[count].P_ID = P_ID;
        L_record[count].model = model;
        L_record[count].price = price;
        L_record[count].quantity = quantity;
        L_record[count].total_price = total_price;
        L_record[count].status = status;
        count++;
    }
    readfile.close();
    cout << "Your pending laptop orders:" << endl;
    for(int i = 0; i < count; i++){
        if(L_record[i].U_ID == cur_U_ID && L_record[i].status == "pending" && containL(L_record[i].P_ID)){
            cout << "Order ID: " << L_record[i].O_ID << " Product ID: " << L_record[i].P_ID 
                 << " Model: " << L_record[i].model << " Price: " <<fixed<<setprecision(2)<< L_record[i].price 
                 << " Quantity Purchase: " << L_record[i].quantity 
                 << " Total Price: " << L_record[i].total_price << endl;
        }
    }
    cin.ignore();
    cout << "Enter the Order ID you want to edit: ";
    getline(cin, order_id);
    cout << "Enter the new quantity: ";
    cin >> new_quantity;
    while(new_quantity < 1){
        cout << "Invalid value. Please Try Again. The quantity must be atleast 1." << endl;
        cout<<"If you want to cancel order, please go thought another function."<<endl;
        cout << "Enter the new quantity: ";
        cin >> new_quantity;
    }
    for(int i = 0; i < count; i++){
        if(L_record[i].O_ID == order_id && L_record[i].status == "pending" && containL(L_record[i].P_ID)){
            found = 1;
            selected_P_ID = L_record[i].P_ID;
            change_quantity = new_quantity - L_record[i].quantity;
            L_record[i].quantity = new_quantity;
            L_record[i].total_price = new_quantity * L_record[i].price;
            break;
        }
    }
    if(found == 0){
        cout << "Order ID not found" << endl;
        return;
    }
    ofstream writefile("purchase_record.txt");
    if(!writefile){
        cout << "Unable to open file for writing" << endl;
        return;
    }
    for(int i = 0; i < count; i++){
        writefile << L_record[i].O_ID << " " << L_record[i].U_ID << " " << L_record[i].P_ID << " " 
                  << L_record[i].model << " " << L_record[i].price << " " << L_record[i].quantity << " " 
                  << L_record[i].total_price << " " << L_record[i].status << endl;
    }
    writefile.close();
    L.updateLaptopLinkedList(selected_P_ID, change_quantity);
    cout << "Order updated successfully!" << endl;
}

void viewCart(login_system &user){
	ifstream readfile("purchase_record.txt");
	string O_ID, U_ID, P_ID, model, status, cur_U_ID, order_id;
	double price, total_price;
	int quantity;
	int found = 0;
	cur_U_ID = user.getUserID();
	if(!readfile){
	cout << "Unable to open file Handphone.txt"<<endl;
	exit(0);
	}
	while (readfile >>O_ID>>U_ID>>P_ID>>model>>price>>quantity>>total_price>>status){
		if(U_ID == cur_U_ID && status == "pending"){
			cout <<"Order ID: "<<O_ID<<" Product ID: "<<P_ID<<" Model: "<<model<<" Price: "<<fixed<<setprecision(2)<<price<<" Quantity Purchase: "<<quantity<<" Total Price: "<<total_price<<endl;
		}
	}
	readfile.close();
}

void deleteHandphoneCart(login_system &user){
	Handphone H;
    purchaseRecord H_record[1000];
    int count = 0;
    ifstream readfile("purchase_record.txt");
    string O_ID, U_ID, P_ID, model, status, cur_U_ID, order_id;
    double price, total_price;
    int quantity, new_quantity, change_quantity;
    int found = 0;
    string selected_P_ID, selected_O_ID;
    cur_U_ID = user.getUserID();
    if(!readfile){
        cout << "Unable to open file purchase_record.txt" << endl;
        exit(0);
    }
    while (readfile >> O_ID >> U_ID >> P_ID >> model >> price >> quantity >> total_price >> status){
        H_record[count].O_ID = O_ID;
        H_record[count].U_ID = U_ID;
        H_record[count].P_ID = P_ID;
        H_record[count].model = model;
        H_record[count].price = price;
        H_record[count].quantity = quantity;
        H_record[count].total_price = total_price;
        H_record[count].status = status;
        count++;
    }
    readfile.close();
    cout << "Your pending handphone orders:" << endl;
    for(int i = 0; i < count; i++){
        if(H_record[i].U_ID == cur_U_ID && H_record[i].status == "pending" && containH(H_record[i].P_ID)){
            cout << "Order ID: " << H_record[i].O_ID << " Product ID: " << H_record[i].P_ID 
                 << " Model: " << H_record[i].model << " Price: " <<fixed<<setprecision(2)<< H_record[i].price 
                 << " Quantity Purchase: " << H_record[i].quantity 
                 << " Total Price: " << H_record[i].total_price << endl;
        }
    }
    cin.ignore();
    cout << "Enter the Order ID you want to delete: ";
    getline(cin, order_id);

    for(int i = 0; i < count; i++){
        if(H_record[i].O_ID == order_id && H_record[i].status == "pending" && containH(H_record[i].P_ID)){
            found = 1;
            selected_O_ID = H_record[i].O_ID;
            selected_P_ID = H_record[i].P_ID;
            change_quantity = -H_record[i].quantity;
            break;
        }
    }
    if(found == 0){
        cout << "Order ID not found" << endl;
        return;
    }
    ofstream writefile("purchase_record.txt");
    if(!writefile){
        cout << "Unable to open file for writing" << endl;
        return;
    }
    for(int i = 0; i < count; i++){
    	if(H_record[i].O_ID != selected_O_ID){
    		writefile << H_record[i].O_ID << " " << H_record[i].U_ID << " " << H_record[i].P_ID << " " 
                  << H_record[i].model << " " << H_record[i].price << " " << H_record[i].quantity << " " 
                  << H_record[i].total_price << " " << H_record[i].status << endl;
		}else{
			continue;
		}
    }
    writefile.close();
    H.updateHandphoneLinkedList(selected_P_ID, change_quantity);
    cout << "Order updated successfully!" << endl;
}

void deleteLaptopCart(login_system &user){
	Laptop L;
    purchaseRecord L_record[1000];
    int count = 0;
    ifstream readfile("purchase_record.txt");
    string O_ID, U_ID, P_ID, model, status, cur_U_ID, order_id;
    double price, total_price;
    int quantity, new_quantity, change_quantity;
    int found = 0;
    string selected_P_ID, selected_O_ID;
    cur_U_ID = user.getUserID();
    if(!readfile){
        cout << "Unable to open file purchase_record.txt" << endl;
        exit(0);
    }
    while (readfile >> O_ID >> U_ID >> P_ID >> model >> price >> quantity >> total_price >> status){
        L_record[count].O_ID = O_ID;
        L_record[count].U_ID = U_ID;
        L_record[count].P_ID = P_ID;
        L_record[count].model = model;
        L_record[count].price = price;
        L_record[count].quantity = quantity;
        L_record[count].total_price = total_price;
        L_record[count].status = status;
        count++;
    }
    readfile.close();
    cout << "Your pending laptop orders:" << endl;
    for(int i = 0; i < count; i++){
        if(L_record[i].U_ID == cur_U_ID && L_record[i].status == "pending" && containL(L_record[i].P_ID)){
            cout << "Order ID: " << L_record[i].O_ID << " Product ID: " << L_record[i].P_ID 
                 << " Model: " << L_record[i].model << " Price: " <<fixed<<setprecision(2)<< L_record[i].price 
                 << " Quantity Purchase: " << L_record[i].quantity 
                 << " Total Price: " << L_record[i].total_price << endl;
        }
    }
    cin.ignore();
    cout << "Enter the Order ID you want to delete: ";
    getline(cin, order_id);

    for(int i = 0; i < count; i++){
        if(L_record[i].O_ID == order_id && L_record[i].status == "pending" && containL(L_record[i].P_ID)){
            found = 1;
            selected_O_ID = L_record[i].O_ID;
            selected_P_ID = L_record[i].P_ID;
            change_quantity = -L_record[i].quantity;
            break;
        }
    }
    if(found == 0){
        cout << "Order ID not found" << endl;
        return;
    }
    ofstream writefile("purchase_record.txt");
    if(!writefile){
        cout << "Unable to open file for writing" << endl;
        return;
    }
    for(int i = 0; i < count; i++){
    	if(L_record[i].O_ID != selected_O_ID){
    		writefile << L_record[i].O_ID << " " << L_record[i].U_ID << " " << L_record[i].P_ID << " " 
                  << L_record[i].model << " " << L_record[i].price << " " << L_record[i].quantity << " " 
                  << L_record[i].total_price << " " << L_record[i].status << endl;
		}else{
			continue;
		}
    }
    writefile.close();
    L.updateLaptopLinkedList(selected_P_ID, change_quantity);
    cout << "Order updated successfully!" << endl;
}

void makepayment(string userID){
    purchaseRecord record[1000];
    int count = 0;
    ifstream readfile("purchase_record.txt");
    string O_ID, U_ID, P_ID, model, status, order_id;
    double price, total_price, confirmed_total_price;
    int quantity, new_quantity;
    int found = 0, price_not_match=0;
    string selected_P_ID;
    if(!readfile){
        cout << "Unable to open file purchase_record.txt" << endl;
        exit(0);
    }
    while (readfile >> O_ID >> U_ID >> P_ID >> model >> price >> quantity >> total_price >> status){
        record[count].O_ID = O_ID;
        record[count].U_ID = U_ID;
        record[count].P_ID = P_ID;
        record[count].model = model;
        record[count].price = price;
        record[count].quantity = quantity;
        record[count].total_price = total_price;
        record[count].status = status;
        count++;
    }
    readfile.close();
    cout << "Your pending orders:" << endl;
    for(int i = 0; i < count; i++){
        if(record[i].U_ID == userID && record[i].status == "pending"){
            cout << "Order ID: " << record[i].O_ID << " Product ID: " << record[i].P_ID 
                 << " Model: " << record[i].model << " Price: " <<fixed<<setprecision(2)<< record[i].price 
                 << " Quantity Purchase: " << record[i].quantity 
                 << " Total Price: " << record[i].total_price << endl;
        }
    }
    cin.ignore();
    cout << "Enter the Order ID you want to pay: ";
    getline(cin, order_id);
    cout << "Enter the total price to confirm: ";
    cin >> confirmed_total_price;
    while(confirmed_total_price < 0){
        cout << "Invalid value. Please Try Again. The quantity must be atleast 1." << endl;
        cout << "Enter the total price to confirm: ";
        cin >> confirmed_total_price;
    }
	ofstream writefile("purchase_record.txt");
    if(!writefile){
        cout << "Unable to open file for writing" << endl;
        return;
    }
    for(int i = 0; i < count; i++){
        if(record[i].O_ID == order_id && record[i].status == "pending" ){
            found = 1;
            if(record[i].total_price == confirmed_total_price){
    		writefile << record[i].O_ID << " " << record[i].U_ID << " " << record[i].P_ID << " " 
                  << record[i].model << " " << record[i].price << " " << record[i].quantity << " " 
                  << record[i].total_price << " paid"<< endl;
			}else{
			writefile << record[i].O_ID << " " << record[i].U_ID << " " << record[i].P_ID << " " 
              << record[i].model << " " << record[i].price << " " << record[i].quantity << " " 
              << record[i].total_price << " "<< record[i].status << endl;
			price_not_match = 1;
			}
			
        }else{
        	writefile << record[i].O_ID << " " << record[i].U_ID << " " << record[i].P_ID << " " 
                  << record[i].model << " " << record[i].price << " " << record[i].quantity << " " 
                  << record[i].total_price << " "<< record[i].status << endl;
		}
    }
    
    if(price_not_match==1){
    	cout<<"Total price not match.Please Try Again."<<endl;
    	return;
	}
    
    if(found == 0){
        cout << "Order ID not found" << endl;
        return;
    }
    writefile.close();
    cout << "Order updated successfully!" << endl;
}

void salesSummaryReport(){
	purchaseRecord record[1000];
    int count = 0, pending_order = 0, paid_order=0, total_amount_sales=0,total_amount_paid_sales=0;
    string line;
    ifstream readfile("purchase_record.txt");
    string O_ID, U_ID, P_ID, model, status, order_id;
    double price, total_price;
    int quantity;
    int found = 0, price_not_match=0;
    string selected_P_ID;
    if(!readfile){
        cout << "Unable to open file purchase_record.txt" << endl;
        exit(0);
    }
    while (readfile >> O_ID >> U_ID >> P_ID >> model >> price >> quantity >> total_price >> status){
        record[count].O_ID = O_ID;
        record[count].U_ID = U_ID;
        record[count].P_ID = P_ID;
        record[count].model = model;
        record[count].price = price;
        record[count].quantity = quantity;
        record[count].total_price = total_price;
        record[count].status = status;
        count++;
    }
    readfile.close();
    for(int i = 0; i < count; i++){
    	total_amount_sales += record[i].total_price;
        if(record[i].status == "pending"){
			pending_order++;
        }else{
        	total_amount_paid_sales += record[i].total_price;
        	paid_order++;
		}
    }
    ofstream openfile("summary_sales_report.txt");
    openfile <<"===   SUMMARY REPORT   === "
    		 <<"\nTotal Records        :" << count
    		 <<"\nPending Bookings     :" << pending_order
    		 <<"\nPaid Bookings        :" << paid_order 
    		 <<"\nTotal Amount Sales   : RM" << total_amount_sales
    		 <<"\nTotal Amount Received: RM" << total_amount_paid_sales <<endl;
    openfile.close();
    cout<<"Report Successful Generated."<<endl;
}

void viewsalesSummaryReport(){
	string line;
	ifstream readfile1("summary_sales_report.txt");
    if (readfile1.is_open()) {
        while (getline(readfile1, line)) {
            cout << line << endl;
        }
        readfile1.close();
    } else {
        cout << "Failed to open the file." << endl;
    }
}

void consumptionReport(string userID){
	purchaseRecord record[1000];
    int count = 0, pending_order = 0, paid_order=0,total_amount_paid_sales=0;
    string line,filename;
    ifstream readfile("purchase_record.txt");
    string O_ID, U_ID, P_ID, model, status, order_id;
    double price, total_price;
    int quantity;
    int found = 0, price_not_match=0;
    string selected_P_ID;
    filename = "Consumption_Report_" + userID+".txt";
    if(!readfile){
        cout << "Unable to open file purchase_record.txt" << endl;
        exit(0);
    }
    while (readfile >> O_ID >> U_ID >> P_ID >> model >> price >> quantity >> total_price >> status){
        record[count].O_ID = O_ID;
        record[count].U_ID = U_ID;
        record[count].P_ID = P_ID;
        record[count].model = model;
        record[count].price = price;
        record[count].quantity = quantity;
        record[count].total_price = total_price;
        record[count].status = status;
        count++;
    }
    readfile.close();
    for(int i = 0; i < count; i++){
    	if(record[i].U_ID == userID){
    		if(record[i].status == "pending"){
				pending_order++;
	        }else{
	        	total_amount_paid_sales += record[i].total_price;
	        	paid_order++;
			}
		}
    }
    ofstream openfile(filename);
    openfile <<"===   SUMMARY REPORT   === "
    		 <<"\nTotal Records        :" << count
    		 <<"\nPending Bookings     :" << pending_order
    		 <<"\nPaid Bookings        :" << paid_order 
    		 <<"\nTotal Amount Paid   : RM" << total_amount_paid_sales <<endl;
    openfile.close();
    cout<<"Report Successful Generated."<<endl;
}

void viewconsumptionReport(string userID){
	purchaseRecord record[1000];
    string line,filename;
    filename = "Consumption_Report_" + userID+".txt";

    ifstream readfile1(filename);
    if (readfile1.is_open()) {
        while (getline(readfile1, line)) {
            cout << line << endl;
        }
        readfile1.close();
    } else {
        cout << "Failed to open the file." << endl;
    }
}

bool checkEmpty(string input){
	for (int i = 0; i < input.length(); i++) {
    if (input[i] == ' ') {
        return true;
    }
	}
	return false;
}

bool containH(string input){
	for (int i = 0; i < input.length(); i++) {
    if (input[i] == 'H') {
        return true;
    }
	}
	return false;
}

bool containL(string input){
	for (int i = 0; i < input.length(); i++) {
    if (input[i] == 'L') {
        return true;
    }
	}
	return false;
}