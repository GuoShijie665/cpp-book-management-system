#include<list>
#include"Book.h"
#include<vector>
#include<iterator>
#include<algorithm>
#include<fstream>
#include<cstdlib>
using namespace std;


void eatline() { while (cin.get() != '\n')continue; }
int main() {
	User user_temp;
	Admin admin_temp;
	char select;
	cout << "Please enter user or admin(user of u,admin of a):";
	while (!(cin >> select) || (select != 'u' && select != 'a'))
	{
		cout << "You enter is error!\n";
		cout << "Please enter again(user of u,admin of a):";
		eatline();
	}
	eatline();
	//用户信息入容器
	
	fstream finout("user_account.txt");
	if (!finout.is_open()) {
		cerr << "The user_account.txt cannot opened.\n";
		exit(EXIT_FAILURE);
	}
	vector<User>vuser;
	while (finout >> user_temp) {
		vuser.push_back(user_temp);
	}
	if (!finout.eof()) {
		cerr << "user_account.txt receive have error.\n";
		exit(EXIT_FAILURE);
	}
	finout.clear();
	
	//管理员账号信息入容器
	fstream finout_admin("admin.txt");
	if (!finout_admin.is_open()) {
		cerr << "The admin.txt cannot opened.\n";
		exit(EXIT_FAILURE);
	}
	vector<Admin>vadmin;
	while (finout_admin >> admin_temp) {
		vadmin.push_back(admin_temp);
	}
	if (!finout_admin.eof()) {
		cerr << "finout.txt receive have error.\n";
		exit(EXIT_FAILURE);
	}
	finout_admin.clear();
	
	//图书入容器
	Book booktemp;
	vector<Book>vBook;
	fstream finout_Book("books.txt");
	if (!finout_Book.is_open()) {
		cerr << "The " << "books.txt cannot opened.\n";
		exit(EXIT_FAILURE);
	}
	
	while (finout_Book >> booktemp) {
		vBook.push_back(booktemp);
	}

	if (!finout_Book.eof()) {
		cerr << "books.txt receive have error.\n";
		exit(EXIT_FAILURE);
	}
	finout_Book.clear();
	
	//借阅信息入容器
	Borrow borrowtemp;
	vector<Borrow>vborrow;
	fstream finout_vborrow("borrows.txt");
	if (!finout_vborrow.is_open()) {
		cerr << "The borrows.txt cannot opened.\n";
		exit(EXIT_FAILURE);
	}
	while (finout_vborrow >> borrowtemp) {
		vborrow.push_back(borrowtemp);
	}
	if (!finout_vborrow.eof()) {
		cerr << "borrows.txt receive have error.\n";
		exit(EXIT_FAILURE);
	}
	finout_vborrow.clear();
	
	//杂项
	Student student_temp;
	string bname;
	string btime_temp;
	vector<Book>::iterator it_book;
	vector<Borrow>::iterator it_vbor;

	if (select == 'u') {
		cout << "Please enter log in or sign in(log in of l,sign in of s):";
		while ((cin >> select)&&(select=='l'||select=='s'))
		{
			eatline();
			if (select == 'l') {
				cout << "Please enter your information.\n";
				user_temp.change();
				auto it_vuser = find_if(vuser.begin(), vuser.end(), [&](const User& u1) {return u1 == user_temp; });
				
				
				if (it_vuser != vuser.end()) {
					cout << "Please enter borrow or give back book:(b of borrow and g of give back):";
					while ((cin >> select) && (select == 'b' || select == 'g'))
					{
						eatline();
						if (select == 'b') {
							
							for (it_book = vBook.begin(); it_book != vBook.end(); ++it_book) {
								it_book->Show();
							}
							cout << "Please enter book's name:\n";
							getline(cin, bname);
							
							for (it_book = vBook.begin(); it_book != vBook.end(); ++it_book) {
								if (it_book->findtool() == bname)break;
							}
							if (it_book != vBook.end() && it_book->bor_book()) {
								cout << "Please enter your information:\n";
								student_temp.change();
								cout << "Please enter borrow time:";
								getline(cin, btime_temp);
								borrowtemp = Borrow(student_temp, (Bookbase&)*it_book, btime_temp);
								vborrow.push_back(borrowtemp);
							}
							else cout << "no have.\n";
						}
						else {
							cout << "Please enter book's name:\n";
							getline(cin, bname);
							vector<Book>::iterator it_book;
							for (it_book = vBook.begin(); it_book != vBook.end(); ++it_book) {
								if (it_book->findtool() == bname)break;
							}
							if (it_book != vBook.end())
							{
								it_book->repay();
							}
							else cout << "No find it.\n";
							cout << "Please enter your information:\n";
							student_temp.change();
							cout << "Please enter borrow time:";
							getline(cin, btime_temp);
							borrowtemp = Borrow(student_temp, (Bookbase&)*it_book, btime_temp);
							it_vbor = remove(vborrow.begin(), vborrow.end(), borrowtemp);
							vborrow.erase(it_vbor, vborrow.end());
						}
						cout << "Please enter continue action:(b of borrow and g of give back,q for quit):";
					}
				}
				else
					cout << "no have your information.\n";
			}
			else{//用户注册
				cout << "Please enter your information:";
				user_temp.change();
				vuser.push_back(user_temp);
			}
			cout << "Please enter your new select(log in of l,sign in of s):";
		}
	}
	else {//管理员登录
		cout << "Please enter log in or sign in(log in of l,sign in of s):";
		while ((cin >> select) && (select == 'l' || select == 's')) {
			eatline();
			if (select == 'l') {
				cout << "Please enter your admin information:\n";
				admin_temp.change();
				auto it_admin =find (vadmin.begin(), vadmin.end(), admin_temp);
				if(it_admin!=vadmin.end()){
					cout << "Please enter your need operate(s for show,a for add,b for amend "
						<< "book information,\nd for delete book,c for delete borrow information"
						<< " ,f for show borrow information and q for quit.):\n";
					string test = "sabdcf";
					while ((cin >> select) && test.find(select) != string::npos) {
						eatline();
						switch (select) {
						case('s'):
							cout << "These are books information:\n";
							for (it_book = vBook.begin(); it_book != vBook.end(); ++it_book) {
								it_book->Show();
							}
							break;
						case'a':
							cout << "Please enter select,y for add new book:\n";
							while ((cin >> select) && (select == 'y')) {
								eatline();
								cout << "Please enter new book information:\n";
								booktemp.change();
								vBook.push_back(booktemp);
								cout << "Continue add?(y or n):";
							}break;
						case'b':cout << "Please enter plan to amend book name:";
							getline(cin, bname);
							for (it_book = vBook.begin(); it_book != vBook.end(); ++it_book) {
								if (it_book->findtool() == bname)break;
							}
							if (it_book != vBook.end())
							{
								it_book->change();
							}
							else cout << "no find the book.\n";
							break;
						case'd':cout << "Please enter plan to delete book name:";
							getline(cin, bname);
							for (it_book = vBook.begin(); it_book != vBook.end(); ++it_book) {
								if (it_book->findtool() == bname)break;
							}
							vBook.erase(remove(vBook.begin(), vBook.end(), *it_book), vBook.end());
							cout << "ok!\n";
							break;
						case'c':cout << "Please enter borrow information:\n";
							borrowtemp.change();
							vborrow.erase(remove(vborrow.begin(), vborrow.end(), borrowtemp), vborrow.end());
							break;
						case'f':cout << "Now show all borrow information:\n";
							for (it_vbor = vborrow.begin(); it_vbor != vborrow.end(); ++it_vbor) {
								it_vbor->Show();
							}
						}
					cout << "Please enter your need operate(s for show,a for add,b for amend "
						<< "book information,\nd for delete book,c for delete borrow information"
						<< " ,f for show borrow information and q for quit.):\n";
					}
				}
				cout << "Your admin account is wrong.Try again:\n";
			}
			else {
				cout << "Please enter admin account information:\n";
				admin_temp.change();
				vadmin.push_back(admin_temp);
			}
			cout << "Please enter log in or sign in(log in of l,sign in of s):";
		}
	}

	for (auto it_user = vuser.begin(); it_user != vuser.end(); ++it_user) {
		finout << *it_user;
	}
	finout.close();
	for (auto it_admin = vadmin.begin(); it_admin != vadmin.end(); ++it_admin) {
		finout_admin << *it_admin;
	}
	finout_admin.close();
	for (it_book = vBook.begin(); it_book != vBook.end(); ++it_book) {
		finout_Book << *it_book;
	}
	finout_Book.close();
	for (it_vbor = vborrow.begin(); it_vbor != vborrow.end(); ++it_vbor) {
		finout_vborrow << *it_vbor;
	}
	finout_vborrow.close();
	cout << "Done.\n";
}
