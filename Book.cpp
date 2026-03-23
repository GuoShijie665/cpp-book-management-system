#include "Book.h"
using namespace std;

ostream& operator<<(ostream& os, const Student& s1) {
	os << s1.stu_name <<endl;
	os << s1.stu_id << endl;
	return os;
}
istream& operator>>(istream& is, Student& s1){
	getline(is, s1.stu_name);
	is >> s1.stu_id;
	is.get();
	return is;
}
void Student::change() {
	cout << "Please enter student's name:";
	getline(cin, stu_name);
	cout << "Please enter student's id:";
	cin >> stu_id;
	cin.get();
}
void Student::Show()const {
	cout << "Student information:name=" << stu_name << ",id=" << stu_id << endl;
}

void Bookbase::change() {
	cout << "Please enter book name:";
	getline(cin, bookname);
	cout << "Please enter book writer:";
	getline(cin, writer);
}
void Bookbase::Show()const {
	cout << "Book information:book name=" << bookname << ",book writer=" << writer <<", ";
}
Bookbase:: ~Bookbase() {}
ostream& operator<<(ostream& os, const Bookbase& s1) {
	os << s1.bookname << endl;
	os << s1.writer << endl;
	return os;
}
istream& operator>>(istream& is,Bookbase& s1) {
	getline(is, s1.bookname);
	getline(is, s1.writer);
	return is;
}

void Borrow::change() {
	Bookbase::change();
	Student::change();
	cout << "Please enter borrow time:";
	getline(cin, bor_time);
}
void Borrow::Show()const {
	Student::Show();
	Bookbase::Show();
	cout << "borrow time=" << bor_time << endl;
}
ostream& operator<<(ostream& os, const Borrow& s1) {
	os << (Student&)s1;
	os << (Bookbase&)s1;
	os << s1.bor_time << endl;
	return os;

}
istream& operator>>(istream& is, Borrow& s1) {
	is >> (Student&)s1;
	is >> (Bookbase&)s1;
	getline(is, s1.bor_time);
	return is;
}

void Book::change() {
	Bookbase::change();
	cout << "Please enter book price:";
	cin >> price;
	cout << "Please enter book have all number:";
	cin >> number_all;
	cout << "Please enter book have number now:";
	cin >> number_now;
	while (cin.get() != '\n')continue;
}
void Book::Show()const {
	Bookbase::Show();
	cout << "price=" << price << ",total=" << number_all << ",have now=" << number_now << endl;
}
ostream& operator<<(ostream& os, const Book& s1) {
	os << (Bookbase&)s1;
	os << s1.price << ' ' << s1.number_all << ' ' << s1.number_now << endl;
	return os;
 }
istream& operator>>(istream& is, Book& s1) {
	is >> (Bookbase&)s1;
	is >> s1.price >> s1.number_all >> s1.number_now;
	is.get();
	return is;
}

void User::change() {
	cout << "Please enter user name:";
	getline(cin, uname);
	cout << "Please enter user possard:";
	cin >> upossard;
	cin.get();
}
istream& operator>>(istream& is,  User& u1) {
	getline(is, u1.uname);
	is >> u1.upossard;
	is.get();
	return is;
}
void Admin::change() {
	cout << "Please enter admin name:";
	getline(cin, adm_name);
	cout << "Please enter admin possard:";
	cin >> adm_possard;
	cin.get();
}
ostream& operator<<(ostream& os, const Admin& u1) {
	os << u1.adm_name << endl;
	os << u1.adm_possard << endl;
	return os;
}
istream& operator>>(istream& is, Admin& u1) {
	getline(is, u1.adm_name);
	is >> u1.adm_possard;
	is.get();
	return is;
}

bool User::operator==(const User& u1)const {
	return(uname == u1.uname && upossard == u1.upossard);
}

bool Borrow::operator==(const Borrow& b1)const {
	if ((Student&)*this == (Student&)b1) {
		if ((Bookbase&)*this == (Bookbase&)b1) {
			return bor_time == b1.bor_time;
		}
	}
	return false;
}

bool Book::operator==(const Book& b1)const {
	if ((Bookbase&)*this == (Bookbase&)b1) {
		return(price == b1.price);
	}
	return false;
}