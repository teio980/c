#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

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
						back = functionMenu();
						break;
					case 2:
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
			Laptop laptop;
			Handphone handphone;
	        while (back == 0) {
	            cout << "-----------------------------" << endl;
	            cout << "     Admin Function Menu     " << endl;
	            cout << "-----------------------------" << endl;
	            cout << "1. Add Laptop\n2. Add Handphone\n3. Edit Laptop\n4. Edit Handphone\n5. Display Laptop\n6. Display Handphone\n7. Search Laptop \n8. Search Handphone\n9. Sort Laptop\n10.Sort Handphone\n-1. Back to previous" << endl;
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
	                    handphone.add_record();  
	                    break;
	                }
					case 8: {
	                    handphone.add_record();  
	                    break;
	                }
	                case 9: {
	                    handphone.add_record();  
	                    break;
	                }
	                case 10: {
	                    handphone.add_record();  
	                    break;
	                }
	                case -1:
	                    return 0;  
	                    break;
	            }
	        }
	        return 0;
	    }
};
void sortLaptop(){
}
void searchLaptop(){
}
void sortHandphone(){
}
void searchHandphone(){
}
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