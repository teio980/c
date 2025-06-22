***README***
***README*** 
***README***

# LK Digital Product Shop   
*A C++ Console-Based E-Commerce System*  
LK Digital Product Shop is an e-commerce system that sells digital products (laptops and handphones), implemented as a C++ console application. System is designed to manage users as per administrator and user access levels.

## Overview  
A digital product management system with:  
- **Admin Panel** (Manage products & check sales)  
- **User Portal** (Explore, purchase & view history)  
- **File-based Database** (No SQL required)  

## Features

### User Features
| Functionality       | Technical Implementation        |
|---------------------|---------------------------------|
| Product Browsing    | Linked list traversal           |
| Cart Management     | Session-based temporary storage |
| Order History       | File-based transaction logs     |

### Admin Features
| Functionality       | Technical Implementation        |
|---------------------|---------------------------------|
| Inventory Control   | CRUD operations via file I/O    |
| Sales Analytics     | Real-time file parsing          |


### Admin Functions  
| Feature               | Description                                 |
|-----------------------|---------------------------------------------|
|    Product Management | Add/delete/edit laptops & phones            |
|    Sales Reports      | View total orders and revenue               |

### User Functions  
| Feature            | Description                                 |
|--------------------|---------------------------------------------|
|    Shopping Cart   | Add/remove items and checkout               |
|    Product Search  | Filter by price/model                       |
|    Order History   | View past purchases                         |

## Data Storage
The system uses **plain text files** as a lightweight database alternative, ensuring portability and simplicity:

### File Structure
data
├──  Laptop.txt # Format: P_ID|Model|Brand|Price|RAM|Quantity
├──  Handphone.txt # Format: P_ID|Model|Brand|Price|RAM|Quantity
├──  user.txt # Format: U_ID|Username|Password|Identity
├──  admin.txt # Format: U_ID|Username|Password|Identity
├──  purchase_record.txt # Format: Order_ID|User_ID|Product_ID|Model|Price|Quantity|Total|Status
└──  id_record.txt # Tracks: Last_Laptop_ID|Last_Phone_ID|Last_Order_ID

### Technical Notes
- **Delimiters**: Uses pipe (`|`) for field separation
- **Encoding**: UTF-8 plain text
- **Backup**: Manual backup recommended 
- **Atomicity**: No built-in transaction rollback 

>  **Why text files?**  
> - Zero database dependencies  
> - Easy debugging with any text editor  
> - Cross-platform compatibility

##  Technical Stack  
```cpp
#include <iostream> 
#include <fstream>  
#include <string>    

## How to Use

### Prerequisites
- C++ compiler (g++/clang++ recommended)
- 10MB free disk space
- Terminal/Command Prompt access

### Running the Program
1. Compile:
   ```bash
   g++ digital_product_shop.cpp -o shop

## Execute:
   ./shop
   
###First Run
The system automatically creates these files:
Project Directory/
├──  user.txt            # User accounts
├──  admin.txt           # Admin accounts
├──  Laptop.txt          # Laptop inventory
├──  Handphone.txt       # Phone inventory
├──  purchase_record.txt # Order history
└──  id_record.txt       # ID counter

###Code Structure
text
 Core/
├──  Product.h           # Base product class
├──  Laptop.h            # Laptop implementation
├──  Handphone.h         # Phone implementation
├──  login_system.h      # Authentication
└──  main.cpp            # Entry point

 Data/                  # Auto-generated
├──  *.txt              # All data files

##Notes：
The system uses console input/output and is designed for single-user operation.

All data persists between sessions via text files.

can you follow This?